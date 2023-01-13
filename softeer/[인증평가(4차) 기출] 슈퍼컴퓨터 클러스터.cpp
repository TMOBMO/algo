#include <iostream>
#include <vector>

using namespace std;


bool f(vector<int>& A, long long B, long long n) {
  for (auto a : A) {
    if (a < n) B -= (n - a) * (n - a);
    if (B < 0) return false;
  }
  return true;
}


int main(void)
{
  long long N, B;
  cin >> N >> B;

  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];

  long long right = 2e9;
  long long left = 1;

  while (left < right) {
    long long m = (left + right + 1) / 2;

    if (f(A, B, m)) left = m;
    else right = m - 1;
  }

  cout << right << '\n';
  return 0;
}