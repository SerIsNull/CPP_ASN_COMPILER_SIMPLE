#include <lexical_rules.h>

namespace asn_compiler
{
    void IRules::throw_away(std::stringstream &buf, std::size_t n)
    {
        buf.seekp(buf.tellg());
        while(n--) buf.put(' ');
        buf.seekg(buf.tellp());
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
        buf.seekg(old_p);
        return std::nullopt;
    }

    std::optional<IRules::val_pos_t> oper_rules::check(std::stringstream & buf)
    {   
        std::cerr << "check_rules_for_oper_type\n";
        std::cerr << "!in buf == " << buf.str() << '\n';
        token_t::pos_t old_p {buf.tellg()};
        token_t::value_t tok_val;
        if(buf >> tok_val)
        {
            for(const auto & value : values)
            {
                if(tok_val == value)
                {
                    buf.seekg(old_p);
                    throw_away(buf, value.size());
                    std::cerr << "buf == " << buf.str() << '\n';
                    return {{value, old_p}};
                }
            }
        }
        // some operators wasn't found. Return old state
        buf.seekg(old_p);
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
        buf.seekg(old_p);
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
            buf.seekg(old_p);
            return {{{1,value},p}};
        }
        throw std::runtime_error("str doesn't have any semicolon like \";\"");
    return std::nullopt;
    }
} // end namespace
