#pragma once

#include <cstddef>

#include "core.hpp"

template<typename T, typename U>
struct TypeList
{
    using Head = T;
    using Tail = U;
};

#define TYPELIST_1(__T1__) TypeList<__T1__, NullType>
#define TYPELIST_2(__T1__, __T2__) TypeList<__T1__, TYPELIST_1(__T2__) >
#define TYPELIST_3(__T1__, __T2__, __T3__) TypeList<__T1__, TYPELIST_2(__T2__, __T3__) >
#define TYPELIST_4(__T1__, __T2__, __T3__, __T4__) TypeList<__T1__, TYPELIST_3(__T2__, __T3__, __T4__) >
#define TYPELIST_5(__T1__, __T2__, __T3__, __T4__, __T5__) TypeList<__T1__, TYPELIST_4(__T2__, __T3__, __T4__, __T5__) >

using SignedIntegrals = TYPELIST_4(signed char, short int, int, long int);
using UnsignedIntegrals = TYPELIST_4(unsigned char, unsigned short int, unsigned int, unsigned long int);

namespace TL
{

    template<class TList>
    struct Length;

    template<>
    struct Length<NullType>
    {
        static constexpr size_t value = 0u;
    };

    template<typename Head, typename Tail>
    struct Length<TypeList<Head, Tail> >
    {
        static constexpr size_t value = 1u + Length<Tail>::value;
    };



    template<class TList, unsigned int index>
    struct At;

    template<typename Head, typename Tail>
    struct At<TypeList<Head, Tail>, 0>
    {
        using Result = Head;
    };

    template<typename Head, typename Tail, unsigned int index>
    struct At<TypeList<Head, Tail>, index>
    {
        using Result = typename At<Tail, index - 1>::Result;
    };



    template<class TList, typename T>
    struct IndexOf;

    template<typename T>
    struct IndexOf<NullType, T>
    {
        static constexpr int value = -1;
    };

    template<typename T, typename Tail>
    struct IndexOf<TypeList<T, Tail>, T>
    {
        static constexpr int value = 0;
    };

    template<typename Head, typename Tail, typename T>
    struct IndexOf<TypeList<Head, Tail>, T>
    {
        static constexpr int value = (IndexOf<Tail, T>::value == -1) ? (-1) : (1 + IndexOf<Tail, T>::value);
    };



    template<class TList, typename T>
    struct Append;

    template<typename T>
    struct Append<NullType, T>
    {
        using Result = TYPELIST_1(T);
    };

    template<typename Head, typename Tail>
    struct Append<NullType, TypeList<Head, Tail> >
    {
        using Result = TypeList<Head, Tail>;
    };

    template<typename Head, typename Tail, typename T>
    struct Append<TypeList<Head, Tail>, T>
    {
        using Result = TypeList<Head, typename Append<Tail, T>::Result>;
    };



    template<class TList, typename T>
    struct Erase;

    template<typename T, typename Tail>
    struct Erase<TypeList<T, Tail>, T>
    {
        using Result = Tail;
    };

    template<typename Head, typename Tail, typename T>
    struct Erase<TypeList<Head, Tail>, T>
    {
        using Result = TypeList<Head, typename Erase<Tail, T>::Result>;
    };



    template<class TList, typename T>
    struct EraseAll;

    template<typename T>
    struct EraseAll<NullType, T>
    {
        using Result = NullType;
    };

    template<typename T, typename Tail>
    struct EraseAll<TypeList<T, Tail>, T>
    {
        using Result = typename EraseAll<Tail, T>::Result;
    };

    template<typename Head, typename Tail, typename T>
    struct EraseAll<TypeList<Head, Tail>, T>
    {
        using Result = TypeList<Head, typename EraseAll<Tail, T>::Result>;
    };



    template<class TList>
    struct NoDuplicates;

    template<>
    struct NoDuplicates<NullType>
    {
        using Result = NullType;
    };

    template<typename Head, typename Tail>
    struct NoDuplicates<TypeList<Head, Tail> >
    {
        using Result = TypeList<Head, typename EraseAll<Head, typename NoDuplicates<Tail>::Result>::Result>;
    };



    template<class TList, typename T, typename U>
    struct Replace;

    template<typename T, typename U>
    struct Replace<NullType, T, U>
    {
        using Result = NullType;
    };

    template<typename T, typename Tail, typename U>
    struct Replace<TypeList<T, Tail>, T, U>
    {
        using Result = TypeList<U, Tail>;
    };

    template<typename Head, typename Tail, typename T, typename U>
    struct Replace<TypeList<Head, Tail>, T, U>
    {
        using Result = TypeList<Head, typename Replace<Tail, T, U>::Result>;
    };

}
