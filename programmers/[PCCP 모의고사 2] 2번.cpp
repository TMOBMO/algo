#include <string>
#include <vector>
#include <queue>
#include <numeric>

using namespace std;

int solution(vector<int> ability, int number) {
  int sum = accumulate(ability.begin(), ability.end(), 0);
  priority_queue<int, vector<int>, greater<int>> pq(ability.begin(), ability.end());
  while (number--) {
    int c1 = pq.top(); pq.pop();
    int c2 = pq.top(); pq.pop();
    pq.push(c1 + c2);
    pq.push(c1 + c2);
    sum += c1 + c2;
  }
  return sum;
}