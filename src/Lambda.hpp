//TODO rename include guard!!!
#ifndef WorldCloud__LAMBDA_HPP_
#define WorldCloud__LAMBDA_HPP_

#include <functional>
#include <type_traits>
#include <utility>

template<typename F>
struct ResultOf {
	typedef decltype(&F::operator()) memfun;
//	typedef F memfun;
	typedef typename std::result_of<memfun>::type type;
};

//template<typename F>
//struct Lambda {
//	//typedef typename ResultOf<F>::type result_type;
//	typedef decltype(f()) result_type;
//	Lambda(F f) : f(f) {}
//
//	template<typename... Args>
//	result_type operator()(Args... args) { return f(std::forward<Args>(args)...); }
//
//	F f;
//};

auto l = [] { return 5; };
int ll() { return 4; }

static_assert(std::is_same<int, ResultOf<decltype(l)>::type>::value, "oops");
static_assert(std::is_same<
		decltype(&decltype(l)::operator()),
		int (decltype(l)::*)() const
		>::value, "oops2");

static_assert(std::is_same<
		decltype(std::declval<decltype(l)>()()),
		int>::value, "oops2");

//static_assert(std::is_same<
//		std::result_of<decltype(&decltype(l)::operator())>::type,
//		int>::value, "oops3");


#endif /* WorldCloud__LAMBDA_HPP_ */
