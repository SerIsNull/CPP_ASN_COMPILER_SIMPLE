# ifndef __TOKEN_STREAM_T__
# define __TOKEN_STREAM_T__
# include <iostream>
# include <sstream>
# include <fstream>
# include <token.h>
# include <optional>

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
        // This method for returning word or line into the src file
        void putback(token_t::value_t );
        // This metod for checkin rules for each token
        std::optional<std::pair<token_t::value_t, token_t::pos_t>> check_rules_for(token_t::type_t);

        std::fstream      src_f;
        std::streampos    pos_file{0};
        std::streamsize   line_num{0};
        std::stringstream ss_buf;
        std::streampos    pos_buf{0};
        token_t           token;
    };
} // end namespace

# endif // end header-guard

