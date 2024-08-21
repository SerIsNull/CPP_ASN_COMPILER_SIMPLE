# include <fixture_test.h>

namespace asn_test
{
    // Open src asn file to testing my compiler
    asn_files::asn_files() noexcept(false)
    {
        try
        {
            // Check that all files exist
            for( const auto& path : asn_files::paths)
                if(!fs::exists(path, ec))
                    throw fs::filesystem_error("src files for test was't exist!!!", ec);

        }
        catch(const fs::filesystem_error& err)
        {
            std::cerr << "err " << err.code() << " " << err.what() << '\n';
        }

        // Open all the files
        for( const auto& path : asn_files::paths)
            files.emplace_back(std::make_unique<std::fstream>(path, std::ios_base::in));
    }

    
} // namespace


