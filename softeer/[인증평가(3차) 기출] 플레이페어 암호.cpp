#include <iostream>
#include <string>
#include <map>


using namespace std;


char key_tbl[5][5];
string new_msg("");
map<char, int> key_map;


void makeKeyTable(string key) {
  bool visit[26] = { 0, };
  visit['J' - 'A'] = true;
  int c = 0;

  for (int i = 0; i < key.size(); ++i) {
    if (visit[key[i] - 'A']) continue;
    visit[key[i] - 'A'] = true;
    key_tbl[c / 5][c % 5] = key[i];
    key_map[key[i]] = c++;
  }

  if (c == 25) return;

  for (int i = 0; i < 26; ++i) {
    if (visit[i]) continue;
    key_tbl[c / 5][c % 5] = 'A' + i;
    key_map['A' + i] = c++;
  }
}


void makeNewMsg(string msg) {
  new_msg.resize(msg.size() * 2);
  int c = 0;
  for (int i = 0; i < msg.size(); ) {
    char cur = msg[i];
    new_msg[i + c] = cur;

    if (++i == msg.size()) {
      new_msg[i + c++] = 'X';
      break;
    }

    int j = i + c;

    char next = msg[i];
    if (cur == next) {
      next = cur != 'X' ? 'X' : 'Q';
      ++c;
    }
    else {
      ++i;
    }

    new_msg[j] = next;
  }

  new_msg.resize(msg.size() + c);
}


string solve() {
  string answer(new_msg);
  int c = 0;
  for (int i = 0; i < new_msg.size(); ) {
    char val[] = { new_msg[i++], new_msg[i++] };
    if (val[0] < 'A') return answer;

    int rank[] = { key_map[val[0]], key_map[val[1]] };
    int row[] = { rank[0] / 5, rank[1] / 5 };
    int col[] = { rank[0] % 5, rank[1] % 5 };

    if (row[0] == row[1]) {
      answer[c++] = key_tbl[row[0]][(++col[0]) % 5];
      answer[c++] = key_tbl[row[1]][(++col[1]) % 5];
      continue;
    }

    if (col[0] == col[1]) {
      answer[c++] = key_tbl[++row[0] % 5][col[0]];
      answer[c++] = key_tbl[++row[1] % 5][col[1]];
      continue;
    }

    answer[c++] = key_tbl[row[0]][col[1]];
    answer[c++] = key_tbl[row[1]][col[0]];
  }
  return answer;
}


int main() {
  string msg, key;
  cin >> msg >> key;

  makeKeyTable(key);
  makeNewMsg(msg);

  cout << solve() << "\n";
  return 0;
}