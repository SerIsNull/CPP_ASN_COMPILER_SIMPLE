# include <fixture_test.h>

namespace token_stream_test
{
    // Try ti open some input src files.asn for testing
    token_stream_test::asn_files::asn_files() noexcept(false)
        : valid_tokens
          {
              // str number 1. INTEGER_TYPE.asn
              {asn_compiler::token_types_t::allias_type, "Temperature_t", 1},
              {asn_compiler::token_types_t::oper, "::=", 1},
              {asn_compiler::token_types_t::type, "INTEGER", 1},
              {asn_compiler::token_types_t::semicolon, ";", 1},

              // str number 2. INTEGER_TYPE.asn
              {asn_compiler::token_types_t::identificator, "TemperatureToday", 2},
              {asn_compiler::token_types_t::allias_type, "Temperature_t", 2},
              {asn_compiler::token_types_t::oper, "::=", 2},
              {asn_compiler::token_types_t::literal, "-2", 2},
              {asn_compiler::token_types_t::semicolon, ";", 2},
          }
    {
        try
        {
            // Check that all files exist
            for( const auto& path : paths)
                if(!fs::exists(path, ec))
                    throw fs::filesystem_error("Fixture asn_files : there're weren't exist!!!", ec);

        }
        catch(const fs::filesystem_error& err)
        {
            std::cerr << "err " << err.code() << " " << err.what() << '\n';
        }
        // Open all the src files.asn for testing
        for( const auto& path : paths)
            files.emplace_back(path, std::ios_base::in | std::ios_base::out);
    }
} // namespace


