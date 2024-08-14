# pragma once

# include <gtest/gtest.h>
# include <filesystem>
# include <string_view>
# include <fstream>

namespace asn_test
{
    namespace fs = std::filesystem;

    class asn_src_file : public ::testing::Test
    {
        protected:
            asn_src_file(fs::path pth = "./asn_src_file.asn");
    };

    class tlv_type : public ::testing::Test
    {
        protected:
            tlv_type() = default;
        public:
            using type_t   = std::string_view;
            using length_t = std::size_t;
            using value_t  = std::string_view;

            type_t get_type() const;
            length_t get_length() const;
            value_t get_value() const;
    };
} // end namespace test


