#pragma once
#include <stdint.h>
template <int32_t I>
struct Number {
	static const int32_t value = I;
};

template<class U>
struct Increment {};
template <int32_t I>
struct Increment< Number<I> > {
	typedef Number<I + 1> result;
};

template<class U>
struct IsNegative {};

template <int32_t I>
struct IsNegative< Number<I> > {
	static const bool result = (I>0) ? false: true;
};

template<class U, bool isNeg>
struct Abs {
};

template <int32_t I>
struct Abs< Number<I>,  true > {
	typedef Number<-I> result;
};
template <int32_t I>
struct Abs< Number<I>, false > {
	typedef Number<I> result;
};

template <class U, class V>
struct Sum
{};
template <int32_t L, int32_t R>
struct Sum<Number<L>, Number<R>>
{
	typedef Number<L + R> result;
};

template <class U, class V>
struct Minus{
	typedef Number<1> result;
};

template <int32_t L, int32_t R>
struct Minus<Number<L>, Number<R>>
{
	typedef Number<L - R> result;
};

template <class U, class V>
struct Equal
{};
template <int32_t L, int32_t R>
struct Equal<Number<L>, Number<R>>
{
	static const bool result = (L == R);
};