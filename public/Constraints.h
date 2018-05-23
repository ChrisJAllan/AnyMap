#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

namespace constraints
{

using namespace std;

/**
 * @class is_hashable
 * @brief Hashable type constraint.  Checks for the existence of `std::hash<T>`.
 * 
 * `is_hashable<T>` is either `std::true_type` or `std::false_type`.
 */

inline namespace helpers {
template<class T> true_type  hashable_helper(const T&, const typename hash<T>::result_type* = nullptr);
template<class T> false_type hashable_helper(...);
}

template<typename T>
using is_hashable = decltype(hashable_helper<T>(declval<T>()));

/**
 * @class is_lt_comparable
 * @brief Less-than comparable constraint.
 * 
 * `is_lt_comparable<T>` is either `std::true_type` or `std::false_type`.
 */

inline namespace helpers {
template<class T> true_type  lt_comp_helper(const T&, decltype(declval<T>() < declval<T>())* = nullptr);
template<class T> false_type lt_comp_helper(...);
}

template<class T>
using is_lt_comparable = decltype(lt_comp_helper<T>(declval<T>()));

/**
 * @class is_eq_comparable
 * @brief Equal comparable constraint.
 * 
 * `is_eq_comparable<T>` is either `std::true_type` or `std::false_type`.
 */

inline namespace {
template<class T> true_type  eq_comparable(const T&, decltype(declval<T>() == declval<T>())* = nullptr);
template<class T> false_type eq_comparable(...);
}

template<class T>
using is_eq_comparable = decltype(eq_comparable<T>(declval<T>()));

} // namespace constraints

#endif // CONSTRAINTS_H
