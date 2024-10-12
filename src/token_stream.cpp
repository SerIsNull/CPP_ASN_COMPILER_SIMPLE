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
        pos_buf  {0}
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

    void token_stream_t::putback(token_t::value_t)
    {
        return;
    }

    std::optional<std::pair<token_t::value_t,token_t::pos_t>> token_stream_t::check_rules_for(token_t::type_t tok_type)
    {
        using enum token_types_t;

        switch(tok_type)
        {
            case allias_type:
            {
                allias_rules rules;
                return rules.check(ss_buf);      
            }
            case type:
            {
                type_rules rules;
                return rules.check(ss_buf);
            }
            // need to pass one word
            case oper:
            {
                oper_rules rules;
                return rules.check(ss_buf);
            }
            case semicolon:
            {
                semicolon_rules rules;
                return rules.check(ss_buf);
            }
        }
        return std::nullopt; 
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
                std::cerr << "======= buf : " << ss_buf.str() << '\n';
            }
            
            // check the rules

            if(auto val_pos = check_rules_for(token_types_t::semicolon);
                    val_pos.has_value())
            {
                std::cerr << "=============================================\n";
                std::cerr << "!!!token type = semicolon \n";
                out_token.type   = token_types_t::semicolon;
                out_token.line_n = line_num;
                out_token.pos_n  = val_pos->second;
                out_token.value  = val_pos->first;
                std::cerr << "rest getting pos for lexical analizer == " << ss_buf.tellg() << '\n';
                std::cerr << "rest put pos for lexical analizer == " << ss_buf.tellp() << '\n';
                std::cerr << "=============================================\n";
                return;
            }
            else if(auto val_pos = check_rules_for(token_types_t::allias_type);
                    val_pos.has_value())
            {
                std::cerr << "=============================================\n";
                std::cerr << "!!!token type = allias type \n";
                out_token.type   = token_types_t::allias_type;
                out_token.line_n = line_num;
                out_token.pos_n  = val_pos->second;
                out_token.value  = val_pos->first;
                std::cerr << "rest getting pos for lexical analizer == " << ss_buf.tellg() << '\n';
                std::cerr << "rest put pos for lexical analizer == " << ss_buf.tellp() << '\n';
                std::cerr << "=============================================\n";
                return;
            }
            else if(auto val_pos = check_rules_for(token_types_t::oper);
                    val_pos.has_value())
            {
                std::cerr << "=============================================\n";
                std::cerr << "!!!token type = oper \n";
                out_token.type   = token_types_t::oper;
                out_token.line_n = line_num;
                out_token.pos_n  = val_pos->second;
                out_token.value  = val_pos->first;
                std::cerr << "rest getting pos for lexical analizer == " << ss_buf.tellg() << '\n';
                std::cerr << "rest put pos for lexical analizer == " << ss_buf.tellp() << '\n';
                std::cerr << "=============================================\n";
                return;
            }
            else if(auto val_pos = check_rules_for(token_types_t::type);
                    val_pos.has_value())
            {
                std::cerr << "=============================================\n";
                std::cerr << "!!!token type = type \n";
                out_token.type   = token_types_t::type;
                out_token.line_n = line_num;
                out_token.pos_n  = val_pos->second;
                out_token.value  = val_pos->first;
                std::cerr << "rest getting pos for lexical analizer == " << ss_buf.tellg() << '\n';
                std::cerr << "rest put pos for lexical analizer == " << ss_buf.tellp() << '\n';
                std::cerr << "=============================================\n";
                return;
            }
            else
            {
                return;
            }
        }
    }
}// end namespace 
