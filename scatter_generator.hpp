#pragma once

#include "typelist.hpp"

template<class TList, template<class> class Unit>
class ScatterGenerator;

template<class T1, class T2, template<class> class Unit>
class ScatterGenerator<TypeList<T1, T2>, Unit> : public ScatterGenerator<T1, Unit>, public ScatterGenerator<T2, Unit>
{
public:
    using TList = TypeList<T1, T2>;
    using LeftBase = ScatterGenerator<T1, Unit>;
    using RightBase = ScatterGenerator<T2, Unit>;
};

template<class AtomicType, template<class> class Unit>
class ScatterGenerator : public Unit<AtomicType>
{
    using LeftBase = Unit<AtomicType>;
};

template<template<class> class Unit>
class ScatterGenerator<NullType, Unit>
{
};
