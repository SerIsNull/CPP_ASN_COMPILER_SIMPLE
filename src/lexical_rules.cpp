#include <lexical_rules.h>

namespace asn_compiler
{
    void IRules::set_pos(std::stringstream & buf, token_t::pos_t p) noexcept
    {
      buf.seekg(p);
      buf.seekp(p);
    }

    void IRules::throw_away(std::stringstream & buf, std::size_t n) noexcept
    {
        while(n--) buf.put(0x20);
        set_pos(buf, buf.tellp());
    }

    std::optional<IRules::res_t> type_rules::check(std::stringstream & buf)
    {
        std::cerr << "\t========> In check_rules_for_type\n";
        token_t::pos_t old_pos {buf.tellg()};
        token_t::value_t tok_val{};
        if(buf >> tok_val)
        {
            for(const auto & value : values)
            {
                if(tok_val == value)
                {
                    std::cerr << "\t========> Yay. This is TYPE\n";
                    set_pos(buf, old_pos);
                    throw_away(buf, tok_val.size());
                    return {{tok_val, token_t::type_t::type, old_pos}};
                }
            }
            buf.clear();
            set_pos(buf, old_pos);
        }
        return std::nullopt;
    }

    std::optional<IRules::res_t> oper_rules::check(std::stringstream & buf)
    {   
        std::cerr << "\t========> In check_rules_for_oper_type\n";
        token_t::pos_t old_pos {buf.tellg()};
        token_t::value_t tok_val{};

        if(buf >> tok_val)
        {
            for(const auto & value : values)
            {
                if(tok_val == value)
                {
                    std::cerr << "\t========> Yay. This is OPER\n";
                    set_pos(buf, old_pos);
                    throw_away(buf, value.size());
                    return {{tok_val, token_t::type_t::oper, old_pos}};
                }
            }
            buf.clear();
            set_pos(buf, old_pos);
        }
        return std::nullopt;
    }

    std::optional<IRules::res_t> allias_rules::check(std::stringstream & buf)
    {
        std::cerr << "\t========> In check_rules_for_allias_type\n";
        // allias or type must be before operator ::=   
        token_t::pos_t old_pos {buf.tellg()};
        token_t::value_t tok_val{}, assign_op{};
        if(buf >> tok_val and buf >> assign_op and assign_op == "::=") 
        {
            std::cerr << "\t========> Yay. This is ALLIAS\n";
            set_pos(buf, old_pos);
            throw_away(buf, tok_val.size());
            return {{tok_val, token_t::type_t::allias_type, old_pos}};
        }
        buf.clear();
        set_pos(buf, old_pos);
        return std::nullopt;
    }

    std::optional<IRules::res_t> semicolon_rules::check(std::stringstream & buf)
    {
        std::cerr << "\t========> In check_rules_for_semicolon\n";
        token_t::pos_t old_pos {buf.tellg()};
        token_t::value_t tok_val{};
        // move to the end
        buf.seekg(-1, std::ios_base::end);
        std::streampos end_pos {buf.tellg()};

        if(buf >> tok_val and tok_val == value)
        {
            std::cerr << "\t========> Yay. This is SEMICOLON\n";
            buf.clear();
            set_pos(buf, end_pos);
            throw_away(buf, 1);
            //buf.clear();
            set_pos(buf, old_pos);
            return {{tok_val, token_t::type_t::semicolon, end_pos}};
        }
        buf.clear();
        set_pos(buf, old_pos);
        return std::nullopt;
    }
} // end namespace
