# include <gtest/gtest.h>

int main(int carg, char **argv)
{
   ::testing::InitGoogleTest(&carg, argv);
   return RUN_ALL_TESTS(); 
}
