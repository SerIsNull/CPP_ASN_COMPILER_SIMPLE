# include <gtest/gtest.h>
# include <fixture_test.h>
# include <token_stream.h>
#include <ios>

using src_files = token_stream_test::asn_files;

auto print_dbg
{
    [](const asn_compiler::token_t & tok)->void
    {
        using std::literals::string_view_literals::operator""sv;
        using namespace asn_compiler;
        using enum asn_compiler::token_types_t;
        std::clog << std::setw(40) << std::setfill('=') << '\n';
        std::clog.fill(' ');
        std::string_view tok_type;
        switch(tok.type)
        {
            case type:
                tok_type = "TYPE"sv;
                break;
            case oper:
                tok_type = "OPERATOR"sv;
                break;
            case semicolon:
                tok_type = "SEMICOLON"sv;
                break;
            case allias_type:
                tok_type = "ALLIAS"sv;
                break;
            case literal:
                tok_type = "LITERAL"sv;
                break;
            case identificator:
                tok_type = "IDENTIFICATOR"sv;
                break;
            default:
                tok_type = "UNKNOWN"sv;
        } // switch
        // Table print 
        std::clog << std::setw(20) << std::left << "> TOKEN VALUE" << std::setw(5) << ':' << std::right << std::setw(15) << tok.value << '\n';
        std::clog << std::setw(20) << std::left << "> TOKEN TYPE"  << std::setw(5) << ':' << std::right << std::setw(15) << tok_type << '\n';
        std::clog << std::setw(20) << std::left << "> TOKEN LINE NUMBER" << std::setw(5) << ':' << std::right << std::setw(15) << tok.line_n << '\n';
        std::clog << std::setw(20) << std::left << "> TOKEN POS NUMBER" << std::setw(5) << ':' << std::right << std::setw(15) << tok.pos_n << '\n';
        std::clog << std::setw(40) << std::setfill('=') << '\n';
    }
};
            
TEST_F(src_files, token_stream_t_return_valid_token)
{
    asn_compiler::token_stream_t ts(std::move(files[0]));

    asn_compiler::token_t tok;

    for(std::size_t i{0}; i < 4; i++)
    {
        ts >> tok;
        print_dbg(tok);
    }

    EXPECT_TRUE(false);
}


