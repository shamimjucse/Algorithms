#include<bits/stdc++.h>
using namespace std;

int main()
{
	vector<int> v = { 5, 2, 1, 3, 4, 2, 2, 4, 5, 5 };

	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());

	for (auto it = v.cbegin(); it != v.cend(); ++it)
		cout << *it << ' ';
	return 0;
}
/*A const_iterator is an iterator that points to const content.
  This iterator can be increased and decreased (unless it is itself
  also const), just like the iterator returned by vector::begin,
  but it cannot be used to modify the contents it points to, even
  if the vector object is not itself const.
*/
