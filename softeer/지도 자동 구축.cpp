#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;


int main() {
  int N;
  cin >> N;

  int n = (1 << N) + 1;
  cout << n * n << '\n';
  return 0;
}