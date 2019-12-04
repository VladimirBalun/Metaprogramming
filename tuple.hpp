#pragma once

template<typename... Types>
struct Tuple;

template<>
struct Tuple<> {};

template<typename HeadType, typename... TailTypes>
struct Tuple<HeadType, TailTypes...> : Tuple<TailTypes...>
{
    Tuple(const HeadType& head, const TailTypes&... tails)
        : Tuple<TailTypes...>(tails...), m_head(head) {}
    using ValueType = HeadType;
    using BaseType  = Tuple<TailTypes...>;
    HeadType m_head;
};

namespace details
{

    template<size_t INDEX, typename HeadType, typename... TailTypes>
    struct Getter
    {
        static constexpr size_t PREVIOUS_INDEX = INDEX - 1u;
        using ReturnType = typename Getter<PREVIOUS_INDEX, TailTypes...>::ReturnType;
        static ReturnType& get(Tuple<HeadType, TailTypes...>& tuple)
        {
            return Getter<PREVIOUS_INDEX, TailTypes...>::get(tuple);
        }
    };

    template<typename HeadType, typename... TailTypes>
    struct Getter<0u, HeadType, TailTypes...>
    {
        using ReturnType = typename Tuple<HeadType, TailTypes...>::ValueType;
        static ReturnType& get(Tuple<HeadType, TailTypes...>& tuple)
        {
            return tuple.m_head;
        }
    };

}

template<size_t INDEX, typename HeadType, typename... TailTypes>
typename details::Getter<INDEX, HeadType, TailTypes...>::ReturnType& get(Tuple<HeadType, TailTypes...>& tuple)
{
    return details::Getter<INDEX, HeadType, TailTypes...>::get(tuple);
}