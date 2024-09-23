#include <token.h>
# include <token_stream.h>

void asn_compiler::token_stream_t::operator<<(std::ifstream &src_file) noexcept
{
    // Pos for getting token
    pos_n  = src_file.tellg();
    line_n = 1;

    while(!src_file.eof() and token.type != token_types::unknown)
    {
        std::clog << "token_stream_t::operator << " << '\n';
        src_file.get();
    }
}



