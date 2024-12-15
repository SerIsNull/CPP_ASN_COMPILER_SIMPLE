#ifndef __LEXICAL_RULES_HPP__
#define __LEXICAL_RULES_HPP__
#include <token.h>

namespace asn_compiler
{
    // This is basic type for all the rules
    class IRules
    {
        public:
        using res_t = struct { token_t::value_t val; token_t::type_t type; token_t::pos_t pos;};
        IRules() = default;
        IRules(const IRules & ) = delete;
        IRules & operator=(const IRules & ) = delete;
        IRules(IRules && ) = delete;
        IRules & operator=(IRules && ) = delete;
        virtual ~IRules() = default;
        virtual std::optional<res_t> check(std::stringstream & ) = 0;

        protected:
        void throw_away(std::stringstream & , std::size_t ) noexcept;
        void set_pos(std::stringstream & , token_t::pos_t ) noexcept;
    };

    // This is a rule for the token type: "type"
    class type_rules : public IRules
    {
        public:
        type_rules() = default;
        virtual ~type_rules() override {}
        virtual std::optional<res_t> check(std::stringstream & ) override final;
        private:
        std::array<token_t::value_t,2> values{{"INTEGER","OCTET STRING"}};
    };

    // This is a rule for the token type: "operators"
    class oper_rules: public IRules
    {
        public:
        oper_rules() = default;
        virtual ~oper_rules() override {}
        virtual std::optional<res_t> check(std::stringstream & ) override final;
        private:
        std::array<token_t::value_t,1> values{{"::="}};
    };

    // This is a rule for the token type : "allias_type"
    class allias_rules : public IRules
    {
        public:
        allias_rules() = default;
        virtual ~allias_rules() override {}
        virtual std::optional<res_t> check(std::stringstream & ) override final;
    };

    // This is a rule for the token type : "semicolon"
    class semicolon_rules : public IRules
    {
        public:
        semicolon_rules() = default;
        virtual ~semicolon_rules() override {}
        virtual std::optional<res_t> check(std::stringstream & ) override final;
        private:
        token_t::value_t value{";"};
    };
} // end namespace
# endif // end of header guard

