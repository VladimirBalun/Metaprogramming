#pragma once

#include "typelist.hpp"

template<
    class TList,
    template<class AtomicType, class Base> class Unit,
    class Root = EmptyType>
class LinearGenerator;

template<
    class T1,
    class T2,
    template<class, class> class Unit,
    class Root>
class LinearGenerator<TypeList<T1, T2>, Unit, Root>
    : public Unit<T1, LinearGenerator<T2, Unit, Root> >s
{
};

template<
    class T,
    template<class, class> class Unit,
    class Root>
class LinearGenerator<TYPELIST_1(T), Unit, Root>
    : public Unit<T, Root>
{
};
