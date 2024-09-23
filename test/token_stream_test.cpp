# include <gtest/gtest.h>
# include <fixture_test.h>
# include <token_stream.h>

using src_files = token_stream_test::asn_files;

TEST_F(src_files, token_stream_t_return_valid_)
{
    asn_compiler::token_stream_t ts;
    ts << files[0];
    EXPECT_TRUE(false);
}


