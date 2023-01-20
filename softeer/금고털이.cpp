#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

struct Data {
	int m;
	int p;
};

int main() {
	int W, N;
	cin >> W >> N;

	vector<Data> obj(N);
	for (int i = 0; i < N; ++i) {
		cin >> obj[i].m >> obj[i].p;
	}

	sort(obj.begin(), obj.end(), [](Data d1, Data d2) -> bool {
		return d1.p > d2.p;
	});

	int ans = 0;
	for (int i = 0; i < N; ++i) {
		if (W == 0) break;
		int w = min(W, obj[i].m);
		ans += w * obj[i].p;
		W -= w;
	}

	cout << ans << '\n';
	return 0;
}