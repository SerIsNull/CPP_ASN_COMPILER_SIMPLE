# ifndef __TOKEN_T__
# define __TOKEN_T__
# include <string>

namespace asn_compiler
{
    // It's the type for all the tokens
    enum class token_types
    {
        oper,
        type,
        allias_type,
        literal,
        identificator,
        semicolon,
        unknown
    };

    // This class is a token.
    // It's output for the lexical analizer
    // and input for the syntaxis analizer.
    class token_t
    {
        public:
            token_types    type;
            std::string    value {""};
            std::streampos pos_n {0};
            std::size_t    line_n{0};
    };
} // end namespace
# endif // end header-guard
