#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string.h>

using namespace std;

long long K, P, N, M;

long long f(long long n) {
  if (n == 0) return 1;
  if (n == 1) return P;
  long long t = f(n / 2);
  t = (t * t) % M;
  return (t * f(n % 2)) % M;
}

int main() {
  cin >> K >> P >> N;
  N *= 10;
  M = 1e9 + 7;

  int ans = (K * f(N)) % M;
  cout << ans << '\n';
  return 0;
}