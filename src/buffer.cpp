#include<buffer.h>
#include <sstream>

namespace asn_compiler
{
    buffer_t::buffer_t(token_t::value_t && str)
        : std::stringstream(str) {}

    bool buffer_t::eof() const
    {
        if(this->std::stringstream::eof()) return true;
        for(auto ch : this->std::stringstream::str())
        {
            if(!std::isspace(ch))
                return false;
        }
    return true;
    }

    void buffer_t::skip_ws() noexcept
    {
        char ch{'\0'};
        while(this->std::stringstream::get(ch) and std::isspace(ch)) {}
        this->std::stringstream::putback(ch);
    }

    void 
}
