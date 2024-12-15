# ifndef __TOKEN_STREAM_T__
# define __TOKEN_STREAM_T__
#include <functional>
# include <iostream>
# include <sstream>
# include <fstream>
# include <token.h>
# include <optional>
# include <lexical_rules.h>
# include <memory>

namespace asn_compiler
{
    class token_stream_t
    {
        public:
        token_stream_t(std::fstream && );
        token_stream_t(const token_stream_t & ) = delete;
        token_stream_t(token_stream_t && ) = delete;
        token_stream_t & operator=(const token_stream_t & ) = delete;
        token_stream_t & operator=(token_stream_t && ) = delete;

        //Rules for the each token
        using rules_t = std::array<std::unique_ptr<IRules>, 4>;

        // This method of start of lexical analize
        // and getting result token
        token_stream_t & operator>>(token_t & ) noexcept;
        operator bool() const;

        private:
        // This method for getting next line from src file
        token_t::value_t read_new_line();
        // This method skeeps spaces
        void skip_ws() noexcept;

        bool is_empty() const;

        std::fstream      src_f;
        std::streampos    pos_file{0};
        std::streamsize   line_num{0};
        std::stringstream ss_buf;
        std::streampos    pos_buf{0};
        token_t           token;
        rules_t           rules;
    };
} // end namespace

# endif // end header-guard

