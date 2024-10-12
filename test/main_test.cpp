#include "gtest/gtest.h"
# include <fixture_test.h>
# include <gtest/gtest.h>
# include <iostream>


int main(int carg, char **argv)
{
    std::cout << "==== The test for token_stream_t started!!! ===\n";
    std::cout << "\t=== Count files for compile = " << carg << '\n';
    for(std::size_t i{1}; i < carg; i++)
    {
        std::cout << "\t===path["<< i << "] : " << argv[i] << '\n';
        token_stream_test::asn_files::paths.emplace_back(argv[i]);
    }

   ::testing::InitGoogleTest(&carg, argv);
   return RUN_ALL_TESTS();
}
