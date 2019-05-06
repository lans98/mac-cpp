#ifndef MAC_EXCEPT_HPP
#define MAC_EXCEPT_HPP

#include <string>
#include <exception>

#define strify(a) #a

#define define_exception(name, description) \
    struct name : public exception { \
        const char* what() const noexcept {\
            return strify(description);\
        }\
    }

#define TODO(reason) throw NotImplemented(reason);

namespace mac {
    using namespace std;

    define_exception(
            NoSolutions, 
            System does not have solutions);

    define_exception(
            InfiniteSolutions, 
            System might have infinite solutions);

    define_exception(
            EmptyArgument, 
            One argument or more are empty!);

    define_exception(
            UnderdeterminedOrOverdetermined, 
            The resulting system is underdetermined or overdetermined);

    define_exception(
            IncorrectDimensionParameter,
            The parameter given has incorrect dimension);

    define_exception(
            NotConfigured,
            This object is not fully configured!);

    class NotImplemented : public exception {
    private:
        string reason;

    public:
        NotImplemented(string reason): reason(move(reason)) {}
        
        const char* what() const noexcept {
            return ("Feature not implemented, reason = { " + reason  + " }").c_str();
        }
    };
}

#endif
