#include <mutex>                       // mutex

struct llama_context;
struct llama_model;
struct llama_sampler;
struct llama_vocab;

class AImanager {
protected:
    llama_model       *model = nullptr;
    llama_sampler     *smpl  = nullptr;
    llama_context     *ctx   = nullptr;
    llama_vocab const *vocab = nullptr;

    int m_ngl   =   99;
    int m_n_ctx = 2048;

    std::mutex mtx;

public:

    ~AImanager(void) noexcept;

    bool Init(void);
    void Reset(void);
    int OtherFunction(void);
};
