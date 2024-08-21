# include <fixture_test.h>
# include <gtest/gtest.h>
# include <iostream>


int main(int carg, char **argv)
{
    std::cout << "cnt arg == " << carg << '\n';
    for(std::size_t i{1}; i < carg; i++)
    {
        std::clog << "path = " << argv[i] << '\n';
        asn_test::asn_files::paths.emplace_back(argv[i]);
    }

   ::testing::InitGoogleTest(&carg, argv);

   return RUN_ALL_TESTS(); 
}
