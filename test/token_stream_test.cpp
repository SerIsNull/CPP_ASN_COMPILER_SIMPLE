# include <gtest/gtest.h>
# include <fixture_test.h>
# include <token_stream.h>

using src_files = token_stream_test::asn_files;

auto print_dbg
{
    [](const asn_compiler::token_t & tok)->void
    {
        std::clog << "token value = " << tok.value  << '\n';
        std::clog << "token pos   = " << tok.pos_n  << '\n';
        std::clog << "token line  = " << tok.line_n << '\n';
        switch(tok.type)
        {
            case asn_compiler::token_types_t::allias_type :
                std::cerr << "token type  = " << "allias type\n";
                break;
            case asn_compiler::token_types_t::type : 
                std::cerr << "token type  = " << "type\n";
                break;
            case asn_compiler::token_types_t::oper :
                std::cerr << "token type  = " << "oper\n";
                break;
            case asn_compiler::token_types_t::semicolon :
                std::cerr << "token type  = " << "semicolon\n";
                break;
            default:
                std::cerr << "token type  = " << "unknown\n";
        }
    }
};


TEST_F(src_files, token_stream_t_return_valid_)
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


