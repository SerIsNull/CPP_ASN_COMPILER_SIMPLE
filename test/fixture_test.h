# pragma once
# include <gtest/gtest.h>
# include <filesystem>
# include <fstream>
# include <vector>
# include <system_error>
# include <token.h>

namespace token_stream_test
{
    namespace fs = std::filesystem;

    // Butch of files for testing.
    // ALl paths set in the tests/CmakeListst.txt
    class asn_files : public ::testing::Test
    {
        public:
            using paths_t = std::vector<fs::path>;
            using files_t = std::vector<std::fstream>;
            using valid_tokens_t = std::vector<asn_compiler::token_t>;
            static inline paths_t paths;
            files_t files;
            valid_tokens_t valid_tokens;
        protected:
            asn_files() noexcept(false);
        private:
            std::error_code ec;
    };
} // end namespace


