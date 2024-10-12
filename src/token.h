# ifndef __TOKEN_T_HPP__
# define __TOKEN_T_HPP__
# include <sstream>
# include <string>
# include <optional>
# include <array>
# include <iostream>

namespace asn_compiler
{
    // There are types for all the tokens
    enum class token_types_t
    {
        oper,
        type,
        allias_type,
        literal,
        identificator,
        semicolon,
        unknown
    };

    // This is the output from token_stream
    // and input for the syntaxis analizer.
    class token_t
    {
        public:
            using type_t  = token_types_t;
            using value_t = std::string;
            using pos_t   = std::streampos;
            type_t          type;
            std::string     value {""};
            std::streamsize line_n{0};
            std::streampos  pos_n{0};
    };
} // end namespace
# endif // end header-guard
