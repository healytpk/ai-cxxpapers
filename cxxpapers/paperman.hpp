#ifndef HEADER_INCLUSION_GUARD_152435324534432523636246673685785
#define HEADER_INCLUSION_GUARD_152435324534432523636246673685785

#include <cstdint>                                 // int32_t
#include <filesystem>                              // path
#include <map>                                     // map
#include <mutex>                                   // mutex
#include <string_view>                             // string_view
#include <vector>                                  // vector

struct Paper {

    unsigned num, rev;

    bool operator<(Paper const other) const noexcept
    {
        return (num < other.num) || ( (num == other.num) && (rev < other.rev) );
    }

    char const *str(void) const noexcept
    {
        static thread_local char s[] = "PxxxxRxx";

        s[1] = '0' + num / 1000u % 10u;
        s[2] = '0' + num / 100u % 10u;
        s[3] = '0' + num / 10u % 10u;
        s[4] = '0' + num / 1u % 10u;

        if ( rev < 10u )
        {
            s[6] = '0' + rev;
            s[7] = '\0';
        }
        else
        {
            s[6] = '0' + rev / 10u % 10u;
            s[7] = '0' + rev / 1u % 10u;
            s[8] = '\0';
        }

        return s;
    }
};


class PaperManager {
protected:
    std::mutex mtx;
    std::filesystem::path path_to_papers_directory;
    std::map< Paper, std::vector< std::int32_t > > tokens;

public:
    PaperManager(std::string_view const arg_path_to_papers_directory) noexcept(false)
     : path_to_papers_directory(arg_path_to_papers_directory) {}

    void LoadAllTokens(void) noexcept(false);
};

#endif
