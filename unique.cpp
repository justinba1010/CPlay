#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void) {
  vector<int> numbers = {1,2,3,4,5,11,1,2,3,4,5};
  sort(numbers.begin(), numbers.end());
  do {
    for (auto v : numbers) cout << v << " ";
    cout << endl;
  } while (std::next_permutation(numbers.begin(), numbers.end()));
  return 0;
}
