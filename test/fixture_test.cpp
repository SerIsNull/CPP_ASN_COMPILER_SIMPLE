# include <fixture_test.h>

// Open src asn file to testing my compiler
asn_test::asn_src_file::asn_src_file(asn_test::fs::path path_to_src)
{
    if(fs::exists(path_to_src))
        std::clog << "FILE IS EXIST!\n";
}

// There are getters for TLV.
asn_test::tlv_type::type_t asn_test::tlv_type::get_type() const
{
    return "INTEGER";
}

asn_test::tlv_type::length_t asn_test::tlv_type::get_length() const
{
    return 1;
}

asn_test::tlv_type::value_t asn_test::tlv_type::get_value() const
{
    return "-2";
}

