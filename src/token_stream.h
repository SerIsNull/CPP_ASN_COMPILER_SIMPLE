# pragma once
# include <sstream>

namespace asn_compiler
{
    class token_stream
    {
        public:
        token_stream() = default;
        token_stream(const token_stream& ) = delete;
        token_stream(token_stream && ) = delete;
        token_stream& operator=(const token_stream& ) = delete;
        token_stream& operator=(token_stream&& ) = delete;

        void operator<<(const std::fstream & ) const;

        private:
        std::stringstream ss;
    };
}
