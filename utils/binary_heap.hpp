#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iterator>
#include <bitset>
#include <exception>
#include <typeinfo>
#include <type_traits>
template <typename T,typename C=std::less<T>>
class binary_heap
{
	C comp = C();
	const size_t maxsize = 4096;
	allocator<T> loc;
	T* arr;
	size_t heapSize = 0;

public:
	binary_heap()
	{
		arr = loc.allocate(maxsize + 1);
	}

	size_t size()const noexcept
	{
		return heapSize;
	}

	void decrease_key(size_t root)
	{
		int largest = root;
		if (root * 2 <= heapSize && comp(arr[root * 2], arr[root])  )
			largest = root * 2;

		if (root * 2 + 1 <= heapSize &&comp( arr[root * 2 + 1] , arr[largest]))
			largest = 2 * root + 1;

		if (largest == root)return;
		swap(arr[root], arr[largest]);
		decrease_key(largest);
	}

	void buildheap()
	{
		for (int i = heapSize / 2; i > 0; --i)
		{
			decrease_key(i);
		}
	}

	T pop()
	{
		auto m = std::move(arr[1]);
		swap(arr[1], arr[heapSize]);
		heapSize--;
		decrease_key(1);
		return m;
	}

	void increase_key(size_t i, T newvalue)
	{
		arr[i] = newvalue;
		while (i > 1 && comp(arr[i], arr[i / 2] ) )
		{
			swap(arr[i], arr[i / 2]);
			i /= 2;
		}
	}

	void insert(T value)
	{
		heapSize++;
		arr[heapSize] = value;
		increase_key(heapSize, value);
	}
};