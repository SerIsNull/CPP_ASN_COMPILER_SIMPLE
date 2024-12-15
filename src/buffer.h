#ifndef __BUFFER_H__
#define __BUFFER_H__
#include <sstream>
#include<token.h>

namespace asn_compiler
{
    class buffer_t : protected std::stringstream
    {
        public:
        buffer_t( token_t::value_t && );
        bool eof() const;
        void skip_ws() noexcept;
        token_t::value_t get_token();
        //void save_pos();
        //void restore_pos();
        //void throw_token();
    };
}
#endif
