# include <gtest/gtest.h>
# include <fixture_test.h>
# include <token_stream.h>

using src_files = token_stream_test::asn_files;

auto print_dbg
{
    [](const asn_compiler::token_t & tok)->void
    {
        using std::literals::string_view_literals::operator""sv;
        using namespace asn_compiler;
        using enum asn_compiler::token_types_t;
        std::clog << std::setw(40) << std::setfill('=') << '\n';
        for( auto name : {"Token value"sv, "Token type"sv, "Token pos"sv})
        {
            std::variant<token_t::type_t, token_t::value_t, token_t::pos_t, token_t::line_t> value;
            if ( name == "Token value"sv)
                value = tok.value;
            else if (name == "Token pos"sv)
                value = tok.pos_n;
            else
                value = std::get<token_t::type_t>(value) == allias_type ? "Allias"   :
                        std::get<token_t::type_t>(value) == type        ? "Type"     :
                        std::get<token_t::type_t>(value) == oper        ? "Operator" : "Semicolon";

            std::clog << '|' << std::setw(20) << std::setfill(' ') << 
            std::left << name << " :" << std::setw(20);
            if      (std::holds_alternative<token_t::type_t>(value) ) std::clog << std::to_string(std::get<token_t::type_t>(value));
            else if (std::holds_alternative<token_t::value_t>(value)) std::clog << std::get<token_t::value_t>(value);
            else if (std::holds_alternative<token_t::pos_t>(value)  ) std::clog << std::get<token_t::pos_t>(value);
            else std::clog << std::get<token_t::line_t>(value); 
            std::clog << "|\n";
            std::clog << std::setw(40) << std::setfill('_') << '\n';
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


