#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int N, T;
char dir[] = { 'R', 'T', 'L', 'B' };

struct its {
	its(int p, char d, int time) {
		pos = p;
		dir = d;
		t = time;
	}

	int pos;
	char dir;
	int t;
};

int dirIndex(char d) {
	for (int i = 0; i < 4; ++i)
		if (dir[i] == d) return i;
	return -1;
}

// 1 <= n <= 12
vector<pair<int, int>> signalByIndex(int n, char& d) {
	vector<pair<int, int>> v;  // (x, y) 순서
	d = dir[(n - 1) % 4];

	if (n < 5) {
		if (n % 4 != 0) v.push_back({ 0, -1 });
		if (n % 4 != 3) v.push_back({ 1, 0 });
		if (n % 4 != 2) v.push_back({ 0, 1 });
		if (n % 4 != 1) v.push_back({ -1, 0 });
		return v;
	}

	if (n % 4 == 1) {
		v.push_back({ 1, 0 });
		v.push_back({ 0, n == 5 ? -1 : 1 });
	}
	if (n % 4 == 2) {
		v.push_back({ 0, -1 });
		v.push_back({ n == 6 ? -1 : 1, 0 });
	}
	if (n % 4 == 3) {
		v.push_back({ -1, 0 });
		v.push_back({ 0, n == 7 ? 1 : -1 });
	}
	if (n % 4 == 0) {
		v.push_back({ 0, 1 });
		v.push_back({ n == 8 ? 1 : -1, 0 });
	}
	return v;
}

int main() {
	cin >> N >> T;
	vector<vector<int>> sig(N * N, vector<int>(4));
	for (int i = 0; i < N * N; ++i) {
		for (int j = 0; j < 4; ++j) {
			cin >> sig[i][j];
		}
	}

	vector<vector<vector<int>>> dt(N * N, vector<vector<int>>(4, vector<int>(4)));

	set<int> ans;
	ans.insert(0);

	queue<its> que;
	que.push(its(0, 'T', T));

	while (!que.empty()) {
		its cur = que.front();
		que.pop();
		int n = cur.pos;
		int t = cur.t;
		if (t <= 0) continue;

		// 4가지 상황을 모두 고려하는 것이 아닌, time에 의존하여 특정 케이스만 처리해야함.
		//for (int i = 0; i < 4; ++i) {}

		char d;
		vector<pair<int, int>> vp = signalByIndex(sig[n][(T - t) % 4], d);
		ans.insert(n);
		if (cur.dir != d) {
			continue;
		}

		for (auto a : vp) {
			int dx = a.first;
			int dy = a.second;

			if (n % N == 0 && dx < 0 || n % N == N - 1 && dx > 0 || n / N == 0 && dy < 0 || n / N == N - 1 && dy > 0)
				continue;
			int next_n = n + dx + dy * N;
			if (next_n < 0 || next_n >= N * N) continue;

			char new_dir = dx ? (dx == 1 ? 'R' : 'L') : 0;
			if (new_dir == 0)
				new_dir = dy == 1 ? 'B' : 'T';
			int next_t = t - 1;

			int dir_idx = dirIndex(new_dir);
			if (dt[next_n][dir_idx][(T - next_t) % 4] == 0)
			{
				ans.insert(next_n);
				dt[next_n][dir_idx][(T - next_t) % 4] = 1;
				if (next_t > 0)
					que.push(its(next_n, new_dir, next_t));

			}
		}
	}

	cout << ans.size() << "\n";
	return 0;
}