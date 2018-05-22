#ifndef AUTOMAP_H
#define AUTOMAP_H

#include "Constraints.h"
#include "VectorMap.hpp"

#include <map>
#include <unordered_map>

namespace engine2
{

/**
 * A map that automaticaly selects hash, tree, or vector storage based on key
 * type.
 */

inline namespace automap_impl {

using namespace std;
using namespace engine2::constraints;

template<class key_t, class value_t>
auto map_t() -> typename enable_if<
	is_hashable<key_t>::value,
	unordered_map<key_t, value_t>
>::type;

template<class key_t, class value_t>
auto map_t() -> typename enable_if<
	!is_hashable<key_t>::value && is_lt_comparable<key_t>::value,
	map<key_t, value_t>
>::type;

template<class key_t, class value_t>
auto map_t() -> typename enable_if<
	!is_hashable<key_t>::value && !is_lt_comparable<key_t>::value && is_eq_comparable<key_t>::value,
	VectorMap<key_t, value_t>
>::type;

template<class key_t, class value_t>
auto map_t() -> typename enable_if<
	!is_hashable<key_t>::value && !is_lt_comparable<key_t>::value && !is_eq_comparable<key_t>::value,
	void
>::type;

}

template<class key_t, class value_t>
using AutoMap = decltype(map_t<key_t, value_t>());

}

#endif // AUTOMAP_H
