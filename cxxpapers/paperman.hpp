#ifndef HEADER_INCLUSION_GUARD_152435324534432523636246673685785
#define HEADER_INCLUSION_GUARD_152435324534432523636246673685785

#include <cassert>                                 // assert
#include <cstdint>                                 // int32_t
#include <filesystem>                              // path
#include <map>                                     // map
#include <mutex>                                   // mutex
#include <string_view>                             // string_view
#include <utility>                                 // pair
#include <vector>                                  // vector

struct Paper {

    unsigned num, rev;

    bool operator<(Paper const other) const noexcept
    {
        return (num < other.num) || ( (num == other.num) && (rev < other.rev) );
    }

    char const *str(void) const noexcept;
};


class PaperManager {
protected:
    std::mutex mtx;
    std::filesystem::path path_to_papers_directory;
    std::map< Paper, std::vector< std::int32_t > > tokens;

public:
    PaperManager(std::string_view const arg_path_to_papers_directory) noexcept(false)
     : path_to_papers_directory(arg_path_to_papers_directory) {}

    void LoadAllTokensFromAllPapers(void) noexcept(false);

    std::size_t size(void) const noexcept { return this->tokens.size(); }

    std::pair< Paper, std::vector< std::int32_t > const * >GetPaper(std::size_t);

    std::size_t TokenCount(std::size_t) noexcept;
};

#endif
