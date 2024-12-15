# include <fstream>
# include <sstream>
# include <token.h>
# include <token_stream.h>
# include <lexical_rules.h>

namespace asn_compiler
{
    token_stream_t::token_stream_t(std::fstream && src_file)
        : src_f {src_file.is_open() ?
            std::move(src_file) :
            throw std::runtime_error("The file wasn't opened!")},
        pos_file {src_file.tellg()},
        line_num {0},
        pos_buf  {0},
        rules
        {
            {
                std::make_unique<semicolon_rules>(),
                std::make_unique<type_rules>(),
                std::make_unique<oper_rules>(),
                std::make_unique<allias_rules>()
            }
        }
    {
        std::cerr << "token_stream_t::ctor(): The initialization was successful!" << '\n';
        ss_buf.setstate(std::ios_base::eofbit);
    }

    bool token_stream_t::is_empty() const 
    {
            for( char ch : ss_buf.str() )
            {
                if(ch != 0x20)
                    return false;
            }
            return true;
    }

    token_stream_t::operator bool() const
    {
       return !ss_buf.eof() or is_empty();
    }

    token_t::value_t token_stream_t::read_new_line()
    {
        if(!src_f.eof())
        {
            ss_buf.clear();
            token_t::value_t str{};
            // save pos before reading
            pos_file = src_f.tellg();
            std::getline(src_f, str, '\n');
            if(!str.empty())
            {
                line_num++;
                return str;
            }
        }
        std::clog << "eof()" << '\n';
        return {};
    }

    void token_stream_t::skip_ws() noexcept
    {
        char ch{'\0'};
        while(ss_buf.get(ch) and std::isspace(ch)) {}
        ss_buf.putback(ch);
    }

    token_stream_t & token_stream_t::operator>>(token_t & out_token) noexcept
    {
        while(!ss_buf.eof() or !src_f.eof())
        {
            // fill the buffer
            if(ss_buf.eof() or is_empty())
            {
                std::cerr << "======= buffer is empty! Fill it!\n";
                ss_buf.str(std::move(read_new_line()));
                std::cerr << "======= after fill buffer == " << ss_buf.str() << '\n';
            }
            
            skip_ws();

            for ( auto it { rules.begin()}; it != rules.end(); ++it )
            {
                if (auto val_type_pos = (*it)->check(ss_buf); val_type_pos )
                {
                    std::cerr << "=======> Rest of buffer == " << ss_buf.str() << '\n';
                    out_token.value  = val_type_pos->val;
                    out_token.type   = val_type_pos->type;
                    out_token.pos_n  = val_type_pos->pos;
                    out_token.line_n = line_num;
                    return *this;
                }
            } // end rules
            return *this;
        }// end while
    return *this;
    }
}// end namespace 
