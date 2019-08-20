#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

int main()
{
	std::vector<int> v = { 5, 2, 1, 3, 4, 2, 2, 4, 5, 5 };

	std::sort(v.begin(), v.end());
	v.erase(std::unique(v.begin(), v.end()), v.end());

	for (auto it = v.cbegin(); it != v.cend(); ++it)
		std::cout << *it << ' ';

	return 0;
}
