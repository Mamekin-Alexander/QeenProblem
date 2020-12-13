#include <iostream>
#include "Type_calculations.h"

/*--------------Initial class-----------------*/
template <int32_t N, bool persp, int32_t depth, class ...Args>
struct Tree {};
/*---------------------------------------------*/


template <int32_t N, int32_t depth, int32_t Iter, class... Args>
struct Checker {};

template <int32_t N, int32_t depth, int32_t Iter, class LastChosen, class Head, class... Args>
struct Checker<N, depth, Iter, LastChosen, Head, Args...>
{
	static const bool OK = Checker <N, depth, Iter + 1, LastChosen, Args...>::OK && (!Equal<LastChosen, Head>::result) &&
		(!Equal< Number<LastChosen::value-Head::value>, Number<Iter>>::result) && 
		(!Equal< Number<Head::value-LastChosen::value>, Number<Iter>>::result);
};

//If we are out of range in Tree - chain is not perspective
template <int32_t N, int32_t depth, int32_t Iter, class Head, class... Args>
struct Checker<N, depth, Iter, Number<N + 1>, Head, Args...>
{
	static const bool OK = false;
};


//there is only LastChosen queen left - stop, return true
template <int32_t N, int32_t depth, int32_t Iter, class LastChosen>
struct Checker<N, depth, Iter, LastChosen>
{
	static const bool OK = true;
};

template <int32_t N, int32_t Iter, class LastChosen>
struct Checker<N, 1, Iter, LastChosen>
{
	static const bool OK = true;
};

template <int32_t N, int32_t Iter>
struct Checker<N, 1, Iter, Number<N+1>>
{
	static const bool OK = false;
};


/*---------Generating state tree-------------*/
template <int32_t N, bool Persp, int32_t depth, int32_t lastChosen, class ...Args>
struct Tree<N, Persp, depth, Number<lastChosen>, Args...> {
	static const bool DepthPersp = Persp && Checker<N, depth + 1, 1 , Number<1>, Number<lastChosen>, Args...>::OK;
	static const bool WidthPersp = Checker<N, depth, 1, Number<lastChosen+1>, Args...>::OK;
	static const int32_t resultWidth = Tree<N, WidthPersp, depth, Number<lastChosen + 1>, Args... >::result;
	static const int32_t resultDepth = Tree<N, DepthPersp, depth + 1, Number<1>, Number<lastChosen>, Args...>::result;
	static const int32_t result = resultDepth + resultWidth;
};


//If chain is not perspective and we can't move in width - stop
template <int32_t N, int32_t depth, class ...Args>
struct Tree<N, false, depth, Number<N>, Args...> {
	static const int32_t result = 0;
};

//If chain is not perspective and we crossed the border - stop
template <int32_t N, int32_t depth, class ...Args>
struct Tree<N, false, depth, Number<N+1>, Args...> {
	static const int32_t result = 0;
};
//If chain is not perspective but we can move in width - move only in width
template <int32_t N, int32_t depth, int32_t lastChosen, class ...Args>
struct Tree<N, false, depth, Number<lastChosen>, Args...> {
	static const bool WidthPersp = Checker<N, depth, 1, Number<lastChosen + 1>, Args...>::OK;
	static const int32_t result = Tree<N, WidthPersp, depth, Number<lastChosen + 1>, Args... >::result;
};

//If chain is perspective and desk is complete - we found solution, stop
template <int32_t N, int32_t lastChosen, class ...Args>
struct Tree<N, true, N, Number<lastChosen>,  Args...>
{
	static const int32_t result = 1;
};

/*---------------------------------------*/






int main()
{
	constexpr int32_t N = 8;
	std::cout << Tree<N, true, 1, Number<1>>::result;
	//std::cout << Abs<Number<1>>::result::value;
}
