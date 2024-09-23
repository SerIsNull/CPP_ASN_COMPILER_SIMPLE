# ifndef __TOKEN_STREAM_T__
# define __TOKEN_STREAM_T__

# include <iostream>
# include <sstream>
# include <fstream>
# include <token.h>

namespace asn_compiler
{
    class token_stream_t
    {
        public:
        token_stream_t() = default;
        token_stream_t(const token_stream_t& ) = delete;
        token_stream_t(token_stream_t && ) = delete;
        token_stream_t& operator=(const token_stream_t& ) = delete;
        token_stream_t& operator=(token_stream_t&& ) = delete;

        // Interface for the syntax analizer
        // This method for getting one token
        token_t get() const noexcept;
        // This method for comeback one token 
        void putback() noexcept;

        // This method for take source_file.asn
        void operator<<( std::ifstream & ) noexcept;

        // This method for getting one token
        private:
        std::streampos pos_n {0};
        std::size_t    line_n{0};
        std::stringstream buf;
        token_t token;   
    };
} // end namespace

# endif // end header-guard

