#include <fixture_test.h>
#include <buffer.h>

using tests_asn_compiler = asn_compiler_test::fixture;

TEST_F(tests_asn_compiler, buffer_t_eof_return_not_eof)
{
    asn_compiler::buffer_t buf{"Hello word, this is a test!"};
    bool expected {false};
    bool actual { buf.eof() };
    EXPECT_TRUE(expected == actual);
}

TEST_F(tests_asn_compiler, buffer_t_eof_return_fake_eof)
{
    asn_compiler::buffer_t buf{"\x20\x20\x20"};
    bool expected {true};
    bool actual { buf.eof() };
    EXPECT_TRUE(expected == actual);
}
