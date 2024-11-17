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
        rules{{std::make_unique<semicolon_rules>(), std::make_unique<type_rules>(), std::make_unique<oper_rules>(), std::make_unique<allias_rules>()}}
    {
        std::cerr << "token_stream_t::ctor(): The initialization was successful!" << '\n';
        ss_buf.setstate(std::ios_base::eofbit);
    }

    token_t::value_t token_stream_t::get_next_line()
    {
        token_t::value_t str{};
        // save pos before reading
        pos_file = src_f.tellg();
        std::getline(src_f, str, '\n');
        if(!str.empty())
            line_num++;
        return str;
    }

    token_t::value_t token_stream_t::read_new_buf()
    {
        if(!src_f.eof())
        {
            ss_buf.clear();
            return get_next_line();
        }
        ss_buf.setstate(std::ios_base::eofbit);
    }

    void token_stream_t::skeep_spaces() noexcept
    {
        char ch{'\0'};
        while(ss_buf.get(ch) and std::isspace(ch)) {}
        ss_buf.putback(ch);
    }

    void token_stream_t::putback(token_t::value_t)
    {
        return;
    }

    void token_stream_t::operator>>(token_t & out_token) noexcept
    {
        while(!src_f.eof() or !ss_buf.eof())
        {
            // fill the buffer
            if(ss_buf.eof())
            {
                std::cerr << "======= buffer is empty! Fill it!\n";
                ss_buf.str(std::move(read_new_buf()));
                std::cerr << "======= after fill buffer == " << ss_buf.str() << '\n';
            }
            
            skeep_spaces();

            for ( auto it {rules.begin()}; it != rules.end(); ++it)
            {
                if (auto val_type_pos = (*it)->check(ss_buf);
                val_type_pos )
                {
                    std::cerr << "-->Rest of buffer == " << ss_buf.str() << '\n';
                    out_token.value  = val_type_pos->val;
                    out_token.type   = val_type_pos->type;
                    out_token.pos_n  = val_type_pos->pos;
                    out_token.line_n = line_num;
                    return;
                }
            }
            return;
/*
            
            // check the rules
            if(auto val_type_pos = check(semicolon_rules());
                    val_pos.has_value())
            {
                std::cerr << "=============================================\n";
                std::cerr << "!!!token type = semicolon \n";
                std::cerr << "rest getting pos for lexical analizer == " << ss_buf.tellg() << '\n';
                std::cerr << "rest put pos for lexical analizer == " << ss_buf.tellp() << '\n';
                std::cerr << "=============================================\n";
                return;
            }
            else if(auto val_pos = check(allias_rules());
                    val_pos.has_value())
            {
                std::cerr << "=============================================\n";
                std::cerr << "!!!token type = allias type \n";
                out_token.type   = token_types_t::allias_type;
                out_token.line_n = line_num;
                out_token.value  = val_pos->first;
                out_token.pos_n  = val_pos->second;
                std::cerr << "rest getting pos for lexical analizer == " << ss_buf.tellg() << '\n';
                std::cerr << "rest put pos for lexical analizer == " << ss_buf.tellp() << '\n';
                std::cerr << "=============================================\n";
                return;
            }
            else if(auto val_pos = check(oper_rules());
                    val_pos.has_value())
            {
                std::cerr << "=============================================\n";
                std::cerr << "!!!token type = oper \n";
                out_token.type   = token_types_t::oper;
                out_token.line_n = line_num;
                out_token.value  = val_pos->first;
                out_token.pos_n  = val_pos->second;
                std::cerr << "rest getting pos for lexical analizer == " << ss_buf.tellg() << '\n';
                std::cerr << "rest put pos for lexical analizer == " << ss_buf.tellp() << '\n';
                std::cerr << "=============================================\n";
                return;
            }
            else if(auto val_pos = check(type_rules());
                    val_pos.has_value())
            {
                std::cerr << "=============================================\n";
                std::cerr << "!!!token type = type \n";
                out_token.type   = token_types_t::type;
                out_token.line_n = line_num;
                out_token.value  = val_pos->first;
                out_token.pos_n  = val_pos->second;
                std::cerr << "rest getting pos for lexical analizer == " << ss_buf.tellg() << '\n';
                std::cerr << "rest put pos for lexical analizer == " << ss_buf.tellp() << '\n';
                std::cerr << "=============================================\n";
                return;
            }
            else
            {
                return;
            } */
        }// while
    }
}// end namespace 
