# pragma once

# include <gtest/gtest.h>
# include <filesystem>
# include <fstream>
# include <vector>
# include <system_error>
# include <memory>

namespace asn_test
{
    namespace fs = std::filesystem;

    class asn_files : public ::testing::Test
    {
        public:
            using paths_t = std::vector<fs::path>;
            using files_t = std::vector<std::unique_ptr<std::fstream>>;
            static inline paths_t paths;
            files_t files;
        protected:
            asn_files() noexcept(false);
        private:
            std::error_code ec;
    };
} // end namespace test


