#pragma once

template<typename... Types>
class Tuple;

template<>
class Tuple<> {};

template<typename HeadType, typename... TailTypes>
class Tuple<HeadType, TailTypes...> : Tuple<TailTypes...>
{
    template<size_t I, typename H, typename... T>
    friend struct Getter;
public:
    using ValueType = HeadType;
    using BaseType = Tuple<TailTypes...>;
    explicit Tuple(const HeadType& head, const TailTypes&... tail) 
        : Tuple<TailTypes...>(tail...), m_head(head) {}
private:
    HeadType m_head;
};

template<size_t INDEX, typename HeadType, typename... TailTypes>
struct Getter
{
    using ReturnType = typename Getter<INDEX - 1, HeadType, TailTypes...>::ValueType;
    static ReturnType& get(Tuple<HeadType, TailTypes...>& tuple) noexcept
    {
        return Getter<INDEX - 1, TailTypes...>::get(tuple);
    }
};

template<typename HeadType, typename... TailTypes>
struct Getter<0u, HeadType, TailTypes...>
{
    using ReturnType = typename Getter<0u, HeadType, TailTypes...>::ValueType;
    static ReturnType& get(Tuple<HeadType, TailTypes...>& tuple) noexcept
    {
        return tuple.m_head;
    }
};
