#include <lexical_rules.h>

namespace asn_compiler
{
    void IRules::throw_away(std::stringstream &buf, token_t::pos_t start_pos, std::size_t n) noexcept
    {
        buf.seekp(start_pos);
        while(n--) buf.put(' ');
        buf.seekg(buf.tellp());
    }

    void IRules::restore_state(std::stringstream &buf, token_t::pos_t old_pos) noexcept
    {
      if(!buf) buf.clear(); 
      buf.seekg(old_pos);
      buf.seekp(old_pos);
    }
    
    std::optional<IRules::val_type_pos_t> type_rules::check(std::stringstream & buf)
    {
        std::cerr << "=In check_rules_for_type\n";
        token_t::pos_t old_pos {buf.tellg()};
        token_t::value_t tok_val{}, assign_op{};
        if(buf >> tok_val)
        {
            for(const auto & value : values)
            {
                if(tok_val == value)
                {
                    std::cerr << "Yay. This is TYPE\n";
                    throw_away(buf, old_pos, tok_val.size());
                    return {{tok_val, token_t::type_t::type, old_pos}};
                }
            }
        }
        restore_state(buf, old_pos);
        return std::nullopt;
    }

    std::optional<IRules::val_type_pos_t> oper_rules::check(std::stringstream & buf)
    {   
        std::cerr << "=In check_rules_for_oper_type\n";
        token_t::pos_t old_pos {buf.tellg()};
        token_t::value_t tok_val{};

        if(buf >> tok_val)
        {
            for(const auto & value : values)
            {
                if(tok_val == value)
                {
                    std::cerr << "Yay. This is OPER\n";
                    throw_away(buf, old_pos, value.size());
                    return {{tok_val, token_t::type_t::oper, old_pos}};
                }
            }
        }
        restore_state(buf, old_pos);
        return std::nullopt;
    }

    std::optional<IRules::val_type_pos_t> allias_rules::check(std::stringstream & buf)
    {
        std::cerr << "=In check_rules_for_allias_type\n";
        // allias or type must be before operator ::=   
        token_t::pos_t old_pos {buf.tellg()};
        token_t::value_t tok_val{}, assign_op{};
        if(buf >> tok_val and buf >> assign_op and assign_op == "::=" )
        {
            std::cerr << "Yay. This is ALLIAS\n";
            throw_away(buf, old_pos, tok_val.size());
            return {{tok_val, token_t::type_t::allias_type, old_pos}};
        }
        restore_state(buf, old_pos);
        return std::nullopt;
    }

    std::optional<IRules::val_type_pos_t> semicolon_rules::check(std::stringstream & buf)
    {
        std::cerr << "=In check_rules_for_semicolon\n";
        token_t::pos_t old_pos {buf.tellg()};
        token_t::value_t tok_val{};
        // move to the end
        buf.seekg(-1, std::ios_base::end);
        std::streampos end_pos {buf.tellg()};

        if(buf >> tok_val and tok_val == value)
        {
            std::cerr << "Yay. This is SEMICOLON\n";
            restore_state(buf, end_pos);
            throw_away(buf, end_pos, 1);
            restore_state(buf, old_pos);
            return {{tok_val, token_t::type_t::semicolon, end_pos}};
        }
        restore_state(buf, old_pos);
        return std::nullopt;
    }
} // end namespace
