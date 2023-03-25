#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string.h>
#include <functional>

using namespace std;

int M, N;
vector<string> dna;
vector<string> superDna;
vector<int> ans;

const string invalid = "0";
const string init = "";


string genDna(int state) {
  if (superDna[state] != init) return superDna[state];

  int pos = 0;
  int n = state;
  while ((n % 2) == 0) {
    n /= 2;
    ++pos;
  }

  string s = genDna(state - (1 << pos));
  string t = dna[pos];

  for (int i = 0; i < M; ++i) {
    if (s[i] == t[i] || t[i] == '.') continue;
    if (s[i] == '.') s[i] = t[i];
    if (s[i] != t[i]) return superDna[state] = invalid;
  }
  return superDna[state] = s;
}


int genAns(int state) {
  if (superDna[state] != invalid) return ans[state] = 1;
  if (ans[state] < N + 1) return ans[state];

  int n = state;
  int pos = 0;
  vector<int> pos_arr;
  while (n) {
    if (n % 2) pos_arr.push_back(pos);
    ++pos;
    n /= 2;
  }

  // increment
  for (int i = 1; i < 1 << (pos_arr.size() - 1); ++i) {
    int t = 0;
    int j = i;
    pos = 0;
    while (j) {
      if (j % 2) t += 1 << pos_arr[pos];
      ++pos;
      j /= 2;
    }
    ans[state] = min(ans[state], genAns(t) + genAns(state - t));
  }
  return ans[state];
}


int main() {
  cin >> N >> M;
  
  dna.resize(N);
  for (int i = 0; i < N; ++i)
    cin >> dna[i];

  superDna.resize(1 << N);
  superDna[0] = string(M, '.');
  for (int i = 1; i < (1 << N); ++i)
    genDna(i);

  ans.resize(1 << N, N + 1);
  for (int i = 1; i < (1 << N); ++i)
    genAns(i);

  cout << ans[(1 << N) - 1];
  return 0;
}

//int main() {
//  cin >> N >> M;
//  list.resize(N);
//  used.resize(N);
//
//  for (int i = 0; i < N; ++i) {
//    cin >> list[i];
//  }
//
//  int ans = 0;
//  for (int i = 0; i < N; ++i) {
//    if (used[i]) continue;
//    used[i] = true;
//    ++ans;
//
//    string s = list[i];
//    for (int j = i + 1; j < N; ++j) {
//      if (used[j]) continue;
//
//      string s1 = s;
//      string s2 = list[j];
//      bool cover = true;
//
//      for (int k = 0; k < M; ++k) {
//        if (s1[k] == s2[k] || s2[k] == '.') continue;
//        if (s1[k] == '.') {
//          s1[k] = s2[k];
//          continue;
//        }
//
//        cover = false;
//        break;
//      }
//
//      if (!cover) continue;
//      s = s1;
//      used[j] = true;
//    }
//  }
//
//  cout << ans;
//  return 0;
//  // counter-case : "a.", ".b", "aa", "bb"
//}