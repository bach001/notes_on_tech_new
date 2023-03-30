/*
* File:   template_test.cc
* Author: bach
*
* Created on March 30, 2023, 4:04 AM
*/

#include <type_traits>

// using the default template parameter
static_assert(std::is_same_v<std::enable_if<true>::type, void> == 1);

template <typename> struct void_type { typedef void type; };

template<typename T, typename X = void>
struct test { };

template<typename T>
struct test<T, typename void_type<T>::type> {
   typedef T type;
};

struct S { int foo; };

// see https://en.cppreference.com/w/cpp/language/sfinae
// Notes: currently partial specialization SFINAE is not
// formally supported by the standard (see also CWG issue 2054),
// however, LFTS requires it works since version 2 (see also detection idiom).
static_assert(std::is_same_v<test<S>::type, S> == 1);
static_assert(std::is_same_v<test<decltype(std::declval<S>().foo)>::type, int> == 1);

int main() { return 0; }
