#include <string>
#include <vector>

class StringHash
{
	public:
	size_t operator()(const std::string& key)
	{
		size_t hash = 0;
		for(auto c: key)
			hash = hash * 63 + c;
		return hash;
	}
};

template<typename K, typename V, typename Hash>
class HashMap
{
	class Bucket
	{
		public:
		K key;
		V value;
		size_t h;
		Bucket *next;
	};

	std::vector<Bucket*> buckets;
	Hash hash;
	size_t _size;
	
	Bucket* find(const K& key)
	{
		size_t h = hash(key);
		size_t idx = h % buckets.size();
		Bucket *ptr = buckets[idx];
		while(ptr != nullptr)
		{
			if (ptr->h == h && ptr->key == key)
				break;
		}
		return ptr;
	}


	// makes sure that the structure can hold size elements
	// without exceeding the load factor;
	void ensure(size_t s)
	{
		if (buckets.size() / 2 < s)
		{
			//buckets.resize(primegreaterthan(buckets.size()*2 + 1));

			// more work to do here
		}
	}

	Bucket *insert(const K& key)
	{
		ensure(size() + 1);
		Bucket *ptr = new Bucket;
		ptr->h = hash(key);
		ptr->key = key;

		size_t idx = ptr->h % buckets.size();
		ptr->next = buckets[idx];
		buckets[idx] = ptr;
		_size++;

		return ptr;
	}

	public:

	HashMap() : buckets(13)
	{
	}

	~HashMap()
	{
		// needs to free everything
	}

	size_t size()
	{
		return _size;
	}

	void insert(const K& key, const V& value)
	{
		Bucket *ptr = find(key);
		if (ptr == nullptr)
			ptr = insert(key);
		ptr ->value = value;
	}

	V& operator[](const K& key)
	{
		Bucket *ptr = find(key);
		if (ptr != nullptr)
			return ptr->value;

		ptr = insert(key);
		return ptr->value;
	}
};

