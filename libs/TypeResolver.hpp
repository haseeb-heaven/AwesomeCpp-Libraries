#ifndef TYPERESOLVER_HPP
#define TYPERESOLVER_HPP

/*
Info: C++ Data type resolve in Compile-Time using T-Template and RunTime using TypeId.
Author: Haseeb Mir @2022.
*/
#include <iostream>     // For input/output operations
#include <list>         // For doubly-linked list container
#include <map>          // For associative array container
#include <string>       // For string manipulation
#include <typeinfo>     // For type information
#include <string_view>  // For lightweight string-like objects
#include <array>        // For fixed-size array container
#include <utility>      // For various utility components
using std::string;

class TypeResolver
{
private:
    template <std::size_t... Idxs>
    static constexpr auto substring_as_array(std::string_view str, std::index_sequence<Idxs...>)
    {
        return std::array{str[Idxs]..., '\n'};
    }

    template <typename T>
    static constexpr auto type_name_array()
    {
#if defined(__clang__)
        constexpr auto prefix = std::string_view{"[T = "};
        constexpr auto suffix = std::string_view{"]"};
        constexpr auto function = std::string_view{__PRETTY_FUNCTION__};
#elif defined(__GNUC__)
        constexpr auto prefix = std::string_view{"with T = "};
        constexpr auto suffix = std::string_view{"]"};
        constexpr auto function = std::string_view{__PRETTY_FUNCTION__};
#elif defined(_MSC_VER)
        constexpr auto prefix = std::string_view{"type_name_array<"};
        constexpr auto suffix = std::string_view{">(void)"};
        constexpr auto function = std::string_view{__FUNCSIG__};
#else
#error Unsupported compiler
#endif

        constexpr auto start = function.find(prefix) + prefix.size();
        constexpr auto end = function.rfind(suffix);

        static_assert(start < end);

        constexpr auto name = function.substr(start, (end - start));
        return substring_as_array(name, std::make_index_sequence<name.size()>{});
    }

    template <typename T>
    struct type_name_holder
    {
        using type_name_array_type = decltype(type_name_array<T>());
        static inline constexpr type_name_array_type value = type_name_array<T>();
    };

public:
    template <typename T>
    static constexpr auto resolveDataType() -> std::string_view
    {
        constexpr auto &value = type_name_holder<T>::value;
        return std::string_view{value.data(), value.size()};
    }

    template <typename T>
    void resolveDataType(T type)
    {
        auto name = typeid(type).name();
        string cmd_str = "echo '" + string(name) + "' | c++filt -t";
        system(cmd_str.c_str());
    }
};

#endif // TYPERESOLVER_HPP
