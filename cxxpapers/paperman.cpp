#include "paperman.hpp"
#include <cassert>                                  // assert
#include <cstddef>                                  // size_t
#include <fstream>                                  // ifstream
#include <regex>                                    // regex_match
#include <string>                                   // stoul, string

using std::int32_t;
using std::size_t;
using std::string;

namespace fs = std::filesystem;

void PaperManager::LoadAllTokens(void) noexcept(false)
{
    assert( tokens.empty() );

    std::regex pattern(R"(p(\d{4})r(\d{1,2})\.tokens)");

    for ( auto const &e : fs::directory_iterator(this->path_to_papers_directory) )
    {
        if ( false == e.is_regular_file() ) continue;

        fs::path const path = e.path();
        string const filename = path.filename().string();

        std::smatch m;
        if ( false == std::regex_match(filename, m, pattern) ) continue;

        Paper paper( std::stoul(m[1]), std::stoul(m[2]) );

        std::ifstream f(path, std::ios::binary);
        if ( ! f ) throw "Failed to open token file";

        // Determine file size
        f.seekg(0, std::ios::end);
        size_t const count_bytes = f.tellg();
        f.seekg(0, std::ios::beg);

        if ( 0u != (count_bytes % sizeof(int32_t)) ) throw "Token file has invalid size";

        size_t const count = count_bytes / sizeof(int32_t);
        this->tokens[paper].resize(count);

        f.read(reinterpret_cast<char*>(&tokens[paper].front()), count_bytes);

        if ( ! f ) throw "Failed to read from token file";
    }
}
