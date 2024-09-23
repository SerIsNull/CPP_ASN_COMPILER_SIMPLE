# include <fixture_test.h>

namespace token_stream_test
{
    // Try ti open some input src files.asn for testing
    token_stream_test::asn_files::asn_files() noexcept(false)
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
            files.emplace_back(path);
    }
} // namespace


