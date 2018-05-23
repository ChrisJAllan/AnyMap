#include "AutoMap.hpp"

#include <assert.h>
#include <iostream>
#include <type_traits>
#include <unordered_map>
#include <vector>

using namespace std;

class foo { public: bool operator==(const foo &) { return true; } };

int main(int, char**)
{
	{
		static_assert(
			is_same<AutoMap<string, string>, unordered_map<string, string>>::value,
			"String AutoMap is not a hash map."
		);
		AutoMap<string, string> smap;
		smap.emplace("Hello", "World");
		assert(smap.size() == 1);
		assert(smap["Hello"] == "World");
		
		AutoMap<string, int> simap;
		simap.emplace("test", 42);
		assert(simap.at("test") == 42);
		
		static_assert(
			is_same<AutoMap<foo, string>::map_type, vector<pair<foo, string>>>::value,
			"Foo AutoMap is not a vector map."
		);
		foo f;
		AutoMap<foo, string> fmap;
		fmap.emplace(f, "test");
		assert(fmap.at(f) == "test");
	}
	cout << "All tests completed successfully." << endl;
}
