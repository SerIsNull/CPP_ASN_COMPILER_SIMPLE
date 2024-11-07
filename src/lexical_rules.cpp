#include <lexical_rules.h>

namespace asn_compiler
{
    void IRules::throw_away(std::stringstream &buf, std::size_t n)
    {
        buf.seekp(buf.tellg());
        while(n--) buf.put(' ');
        buf.seekg(buf.tellp());
    }

    void IRules::restore_state(std::stringstream &buf, token_t::pos_t old_pos) noexcept
    {
      if(!buf) buf.clear(); 
      buf.seekg(old_pos);
      buf.seekp(old_pos);
    }
    
    std::optional<IRules::val_pos_t> type_rules::check(std::stringstream & buf)
    {
        std::cerr << "check_rules_for_type\n";
        token_t::pos_t old_p {buf.tellg()};
        token_t::value_t tok_val, assign_op;
        std::cerr << "buff == " << buf.str() << '\n';
        if(buf >> tok_val)
        {
            for(const auto & value : values)
            {
                if(tok_val == value)
                {
                    buf.seekg(old_p);
                    throw_away(buf, tok_val.size());
                    return {{tok_val, old_p}};
                }
            }
        }
        restore_state(buf, old_p);
        return std::nullopt;
    }

    std::optional<IRules::val_pos_t> oper_rules::check(std::stringstream & buf)
    {   
        std::cerr << "check_rules_for_oper_type\n";
        std::cerr << "input in operator buf == " << buf.str() << '\n';
        token_t::pos_t old_p {buf.tellg()};
        std::cerr << "pos for reading == " << old_p << '\n';
        token_t::value_t tok_val;
        if(buf >> tok_val)
        {
            std::cerr << "tok_val in oper == " << tok_val << '\n';
            for(const auto & value : values)
            {
                if(tok_val == value)
                {
                    buf.seekg(old_p);
                    std::cerr << "Try to throw away " << value.size() << " elements!\n";
                    throw_away(buf, value.size());
                    std::cerr << "buf == " << buf.str() << '\n';
                    std::cerr << "pos reading after throw away " << buf.tellg() << '\n';
                    return {{value, old_p}};
                }
            }
        }
        restore_state(buf, old_p);
        return std::nullopt;
    }

    std::optional<IRules::val_pos_t> allias_rules::check(std::stringstream & buf)
    {
        std::cerr << "check_rules_for_allias_type\n";
        // allias or type must be before operator ::=   
        token_t::pos_t old_p {buf.tellg()};
        token_t::value_t tok_val, assign_op;
        if(buf >> tok_val && buf >> assign_op)
        {
            if(assign_op == "::=")
            {
                buf.seekg(old_p);
                throw_away(buf, tok_val.size());
                std::cerr << "!buf == " << buf.str() << '\n';
                return {{tok_val, old_p}};
            }
        }
        restore_state(buf, old_p);
        return std::nullopt;
    }

    std::optional<IRules::val_pos_t> semicolon_rules::check(std::stringstream & buf)
    {
        // move to the end
        std::cerr << "check_rules_for_semicolon\n";
        token_t::pos_t old_p {buf.tellg()};
        buf.seekg(-1, std::ios_base::end);
        std::streampos p {buf.tellg()};

        if(buf.peek() == value)
        {
            throw_away(buf, 1);
            std::cerr << "pos get before throw ==" << buf.tellg() << '\n';
            buf.seekg(old_p);
            std::cerr << "pos get after throw ==" << buf.tellg() << '\n';
            return {{{1,value},p}};
        }
        restore_state(buf, old_p);
        return std::nullopt;
    }
} // end namespace
