#ifndef HEADER_INCLUSION_GUARD_8737664168229829598674325825449484157496285664353554
#define HEADER_INCLUSION_GUARD_8737664168229829598674325825449484157496285664353554

#include <cstring>                       // strcpy, strlen
#include <type_traits>                   // decay, is_same
#include <vector>                        // vector

class CopyArgcArgv {
protected:
    std::vector<char*> myvec;
public:
    template<typename... Ts>
    requires ( ( std::is_same_v< std::decay_t<Ts>, char* > || std::is_same_v< std::decay_t<Ts>, char const* > ) && ... )
    CopyArgcArgv(int const argc, char **const argv, Ts&&... extras) : myvec( argc + sizeof...(extras) )
    {
        int i = 0;
        for ( ; i < argc; ++i )
        {
            this->myvec[i] = new char[ std::strlen(argv[i]) + 1u /* for null terminator */ ];
            std::strcpy( this->myvec[i], argv[i] );
        }

        auto mylambda = [this,&i](char const *const p)
          {
            this->myvec[i] = new char[ std::strlen(p) + 1u /* for null terminator */ ];
            std::strcpy( this->myvec[i], p );
            ++i;
          };

        (  mylambda(extras), ...  );
    }

    int argc(void) const noexcept
    {
        return myvec.size();
    }

    char **argv(void) const noexcept
    {
        return const_cast<char**>( &myvec.front() );
    }

    ~CopyArgcArgv(void) noexcept
    {
        for ( auto const e : this->myvec )
        {
            delete [] e;
        }
    }
};

#endif

