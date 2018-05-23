#ifndef VECTORMAP_CPP
#define VECTORMAP_CPP

#include <stdexcept>
#include <vector>

/**
 * @class VectorMap VectorMap.hpp
 * @brief A map with vector storage.
 * 
 * @todo Move all function implementations out of class declaration.
 * @todo Implement all map functions.
 */
template<class k, class v>
class VectorMap
{
public:
	using map_type       = std::vector<std::pair<k, v>>;
	using key_type       = k;
	using mapped_type    = v;
	using iterator       = typename map_type::iterator;
	using const_iterator = typename map_type::const_iterator;
	using size_type      = typename map_type::size_type;
	
	
	iterator begin() noexcept;
	const_iterator begin() const noexcept;
	const_iterator cbegin() const noexcept;
	
	iterator end() noexcept;
	const_iterator end() const noexcept;
	const_iterator cend() const noexcept;
	
	
	bool empty() const noexcept;
	
	size_type size() const noexcept;
	size_type max_size() const noexcept;
	
	
	void clear() noexcept
	{ storage.clear(); }
	
	template<class... Args>
	std::pair<iterator, bool> emplace(Args&&... args)
	{
		storage.emplace_back(std::forward<Args>(args)...);
		return make_pair(--storage.end(), true);
	}
	
	iterator erase(const_iterator pos)
	{ return storage.erase(pos); }
	iterator erase(const_iterator first, const_iterator last)
	{ return storage.erase(first, last); }
	size_type erase(const key_type &key)
	{
		size_type count = 0;
		for (auto it = storage.begin(); it != storage.end(); ++it) {
			if (it->first == key) {
				it = storage.erase(it);
				--it;
				count++;
			}
		}
		return count;
	}
	
	mapped_type& at(const key_type &key)
	{
		for (auto& p : storage) {
			if (p.first == key) {
				return p.second;
			}
		}
		
		throw std::out_of_range("Key not found.");
	}

	const mapped_type& at(const key_type &key) const
	{ return at(key); }
	mapped_type& operator[](const key_type &key)
	{
		for (auto p : storage) {
			if (p.first == key) {
				return p.second;
			}
		}
		
		empace(key, mapped_type());
		return at(key);
	}
	
	size_type count(const key_type &key)
	{
		size_type count;
		for (auto p : storage) {
			if (p.first == key) {
				count++;
			}
		}
		return count;
	}
	
	iterator find(const key_type &key)
	{
		for (auto it = storage.begin(); it != storage.end(); ++it) {
			if (it->first == key) {
				return it;
			}
		}
	}

	const_iterator find(const key_type &key) const
	{
		for (auto it = storage.cbegin(); it != storage.cend(); ++it) {
			if (it->first == key) {
				return it;
			}
		}
	}
	
private:
	map_type storage;
};

// Implementation

#define VECTORMAP_DEC \
	template<class key_t, class value_t> \
	auto VectorMap<key_t, value_t>

VECTORMAP_DEC::begin() noexcept -> iterator
{ return storage.begin(); }

VECTORMAP_DEC::begin() const noexcept -> const_iterator
{ return storage.begin(); }

VECTORMAP_DEC::cbegin() const noexcept -> const_iterator
{ return storage.cbegin(); }

VECTORMAP_DEC::end() noexcept -> iterator
{ return storage.end(); }

VECTORMAP_DEC::end() const noexcept -> const_iterator
{ return storage.end(); }

VECTORMAP_DEC::cend() const noexcept -> const_iterator
{ return storage.cend(); }

VECTORMAP_DEC::empty() const noexcept -> bool
{ return storage.empty(); }

VECTORMAP_DEC::size() const noexcept -> size_type
{ return storage.size(); }

VECTORMAP_DEC::max_size() const noexcept -> size_type
{ return storage.max_size(); }

#endif // VECTORMAP_CPP
