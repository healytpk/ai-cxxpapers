#include "ai.hpp"
#include <cassert>                  // assert
#include <cstdio>
#include <cstdlib>                  // EXIT_FAILURE
#include <cstring>
#include <iostream>                 // cin   ------------------------------------- REMOVE THIS
#include <string>                   // string
#include <vector>                   // vector
#include "llama.h"
#include "Auto.h"

using std::string, std::vector;

constexpr char model_path[] = "/var/snap/ollama/common/models/blobs/sha256-6340dc3229b0d08ea9cc49b75d4098702983e17b4c096d57afbbf2ffc813f2be";

void AImanager::Reset(void)
{
    std::lock_guard mylock( this->mtx );  // might throw if mutex malfunctions

    try { if ( smpl  ) llama_sampler_free(smpl ); } catch(...){}
    try { if ( ctx   ) llama_free        (ctx  ); } catch(...){}
    try { if ( model ) llama_model_free  (model); } catch(...){}

    smpl  = nullptr;
    ctx   = nullptr;
    model = nullptr;
}

AImanager::~AImanager(void) noexcept
{
    try { this->Reset(); } catch(...) {}
}

bool AImanager::Init(void)
{
    std::lock_guard mylock( this->mtx );

    // only print errors
    llama_log_set([](enum ggml_log_level level, char const *const text, void*)
      {
        if ( level >= GGML_LOG_LEVEL_ERROR ) fprintf(stderr, "%s", text);
      }, nullptr);

    ggml_backend_load_all();

    llama_model_params model_params = llama_model_default_params();
    model_params.n_gpu_layers = m_ngl;

    model = llama_model_load_from_file(model_path, model_params);
    if ( nullptr == model )
    {
        fprintf(stderr , "%s: error: unable to load model\n" , __func__);
        return false;
    }

    vocab = llama_model_get_vocab(model);
    if ( nullptr == vocab )
    {
        fprintf(stderr , "%s: error: unable to get vocabulary from model\n" , __func__);
        return false;
    }

    // initialize the context
    llama_context_params ctx_params = llama_context_default_params();
    ctx_params.n_ctx   = m_n_ctx;
    ctx_params.n_batch = m_n_ctx;

    ctx = llama_init_from_model(model, ctx_params);
    if ( nullptr == ctx )
    {
        fprintf(stderr , "%s: error: failed to create the llama_context\n" , __func__);
        return false;
    }

    // initialize the sampler
    smpl = llama_sampler_chain_init(llama_sampler_chain_default_params());
    if ( nullptr == smpl )
    {
        fprintf(stderr , "%s: error: failed to create the llama_sampler\n" , __func__);
        return false;
    }

    llama_sampler_chain_add(smpl, llama_sampler_init_min_p(0.05f, 1));
    llama_sampler_chain_add(smpl, llama_sampler_init_temp(0.8f));
    llama_sampler_chain_add(smpl, llama_sampler_init_dist(LLAMA_DEFAULT_SEED));

    return true;
}

int AImanager::OtherFunction(void)
{
    std::lock_guard mylock( this->mtx );

    // helper function to evaluate a prompt and generate a response
    auto generate = [&](const string & prompt)
      {
        string response;

        bool const is_first = (0 == llama_kv_self_used_cells(ctx));

        // tokenize the prompt
        int const n_prompt_tokens = -llama_tokenize(vocab, prompt.c_str(), prompt.size(), NULL, 0, is_first, true);
        vector<llama_token> prompt_tokens(n_prompt_tokens);
        if (llama_tokenize(vocab, prompt.c_str(), prompt.size(), prompt_tokens.data(), prompt_tokens.size(), is_first, true) < 0) GGML_ABORT("failed to tokenize the prompt\n");

        // prepare a batch for the prompt
        llama_batch batch = llama_batch_get_one(prompt_tokens.data(), prompt_tokens.size());
        llama_token new_token_id;
        for (; /* ever */ ;)
        {
            // check if we have enough space in the context to evaluate this batch
            int const n_ctx = llama_n_ctx(ctx);
            int const n_ctx_used = llama_kv_self_used_cells(ctx);
            if ( (n_ctx_used + batch.n_tokens) > n_ctx )
            {
                printf("\033[0m\n");
                fprintf(stderr, "context size exceeded\n");
                exit(0);
            }

            if ( llama_decode(ctx, batch) ) GGML_ABORT("failed to decode\n");

            // sample the next token
            new_token_id = llama_sampler_sample(smpl, ctx, -1);

            // is it an end of generation?
            if (  llama_vocab_is_eog(vocab, new_token_id)  ) break;

            // convert the token to a string, print it and add it to the response
            char buf[256];
            int const n = llama_token_to_piece(vocab, new_token_id, buf, sizeof(buf), 0, true);
            if (n < 0) GGML_ABORT("failed to convert token to piece\n");

            string piece(buf, n);
            printf("%s", piece.c_str());
            fflush(stdout);
            response += piece;

            // prepare the next batch with the sampled token
            batch = llama_batch_get_one(&new_token_id, 1);
        }

        return response;
    };

    class vector_llama_chat_message : public vector<llama_chat_message> {
    public:
        ~vector_llama_chat_message(void) noexcept
        {
            // free resources
            for ( auto &msg : *this ) std::free(  const_cast<char*>(msg.content)  );
        }
    };

    vector_llama_chat_message messages;
    vector<char> formatted( llama_n_ctx(ctx) );
    int prev_len = 0;
    for (; /* ever */ ;)
    {
        // get user input
        printf("\033[32m> \033[0m");
        string user;
        std::getline(std::cin, user);

        if ( user.empty() ) break;

        char const *const tmpl = llama_model_chat_template(model, /* name */ nullptr);

        // add the user input to the message list and format it
        messages.push_back(  {  "user", strdup(user.c_str())  }  );
        int new_len = llama_chat_apply_template(tmpl, messages.data(), messages.size(), true, formatted.data(), formatted.size());
        if ( new_len > (int)formatted.size() )
        {
            formatted.resize(new_len);
            new_len = llama_chat_apply_template(tmpl, messages.data(), messages.size(), true, formatted.data(), formatted.size());
        }
        if ( new_len < 0 )
        {
            fprintf(stderr, "failed to apply the chat template\n");
            return EXIT_FAILURE;
        }

        // remove previous messages to obtain the prompt to generate the response
        string prompt(formatted.begin() + prev_len, formatted.begin() + new_len);

        // generate a response
        printf("\033[33m");
        string response = generate(prompt);
        printf("\n\033[0m");

        // add the response to the messages
        messages.push_back(  { "assistant", strdup(response.c_str()) }  );
        prev_len = llama_chat_apply_template(tmpl, messages.data(), messages.size(), false, nullptr, 0);
        if ( prev_len < 0 )
        {
            fprintf(stderr, "failed to apply the chat template\n");
            return EXIT_FAILURE;
        }
    }

    return 0;
}
