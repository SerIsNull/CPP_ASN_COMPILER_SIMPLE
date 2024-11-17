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
        token_stream_t(const token_stream_t& ) = delete;
        token_stream_t(token_stream_t && ) = delete;
        token_stream_t& operator=(const token_stream_t& ) = delete;
        token_stream_t& operator=(token_stream_t&& ) = delete;

        //Types
        using rules_t = std::array<std::unique_ptr<IRules>,4>;

        // Interface for the syntax analizer
        // This method for getting one token
        token_t get() const noexcept;
        // This method for comeback one token 
        void putback() noexcept;

        // This method of start of lexical analize
        void operator>>(token_t & ) noexcept;

        private:
        // This method sets buff from src file.asn
        token_t::value_t read_new_buf();
        // This method for getting next line from src file
        token_t::value_t get_next_line();
        // This method skeeps spaces
        void skeep_spaces() noexcept;
        // This method for returning word or line into the src file
        void putback(token_t::value_t );

        std::fstream      src_f;
        std::streampos    pos_file{0};
        std::streamsize   line_num{0};
        std::stringstream ss_buf;
        std::streampos    pos_buf{0};
        token_t           token;
        rules_t rules;

    };
} // end namespace

# endif // end header-guard

