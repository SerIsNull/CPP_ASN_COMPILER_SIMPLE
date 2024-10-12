#ifndef __LEXICAL_RULES_HPP__
#define __LEXICAL_RULES_HPP__
#include <token.h>

namespace asn_compiler
{
    // This is basic type for all the token type
    class IRules
    {
        public:
        using val_pos_t = std::pair<token_t::value_t, token_t::pos_t>;
        IRules() = default;
        IRules(const IRules & ) = delete;
        IRules & operator=(const IRules & ) = delete;
        IRules(IRules && ) = delete;
        IRules & operator=(IRules && ) = delete;
        virtual ~IRules() = default;

        virtual std::optional<val_pos_t> check(std::stringstream &) = 0;
        protected:
        void throw_away(std::stringstream &buf, std::size_t n);
    };

    // There are rules for the token type: "type"
    class type_rules : public IRules
    {
        public:
        type_rules() = default;
        virtual ~type_rules() override {}
        virtual std::optional<val_pos_t> check(std::stringstream & buf) override final;
        private:
        std::array<token_t::value_t,2> values{{"INTEGER","OCTET STRING"}};
    };

    // There are rules for the token type: "operators"
    class oper_rules: public IRules
    {
        public:
        oper_rules() = default;
        virtual ~oper_rules() override {}
        virtual std::optional<val_pos_t> check(std::stringstream & buf) override final;
        private:
        std::array<token_t::value_t,1> values{{"::="}};       
    };

    // There are rules for the token type : "allias_type"
    class allias_rules : public IRules
    {
        public:
        allias_rules() = default;
        virtual ~allias_rules() override {}
        virtual std::optional<val_pos_t> check(std::stringstream & buf) override final;
    };

    // There are rules for the token type : "semicolon"
    class semicolon_rules : public IRules
    {
        public:
        semicolon_rules() = default;
        virtual ~semicolon_rules() override {}
        virtual std::optional<val_pos_t> check(std::stringstream & buf) override final;
        private:
        token_t::value_t::value_type value{';'};
    };
} // end namespace
# endif // end of header guard

