#include "gtest/gtest.h"
# include <fixture_test.h>
# include <gtest/gtest.h>
# include <iostream>


int main(int carg, char **argv)
{
    std::cout << "\t===> count files for testing = " << carg << '\n';
    // 0 - is a name of programm
    for(std::size_t i{1}; i < carg; i++)
    {
        std::cout << "\t===> put path["<< i << "] for testing  == " << argv[i] << '\n';
        token_stream_test::asn_files::paths.emplace_back(argv[i]);
    }

   ::testing::InitGoogleTest(&carg, argv);
   return RUN_ALL_TESTS();
}
