#include <bits/stdc++.h>

using namespace std;

struct parser{
  string s;
  int curr = 0;

  parser(string line) {
    s = line;
  } 

  char consume() {
    return s[curr++];
  }

  string consumeNumber() {
    string num = "";
    while(isdigit(peek())) {
      num += consume();
    }
    return num;
  }

  char peek() {
    return s[curr];
  }

  bool matches(char c) {
    if(atEnd()) return false;
    return consume() == c;
  }

  bool matches(string sub) {
    for(char c : sub) {
      if(!matches(c)) return false;
    }
    return true;
  }

  bool atEnd() {
    return curr >= s.size();
  }
};

int main() {

  string line;
  long long ans = 0;
  while (getline(cin, line)) {
    parser p(line);

    int x, y;
    string num;

    while(!p.atEnd()) {
      if(!p.matches("mul(")) continue;

      num = p.consumeNumber();
      if(num.size() < 0 || num.size() > 3) continue;
      x = stoi(num);

      if(!p.matches(',')) continue;

      num = p.consumeNumber();
      if(num.size() < 0 || num.size() > 3) continue;
      y = stoi(num);

      if(!p.matches(')')) continue;

      ans += 1LL * x * y;
    }
  }
  
  cout << ans << "\n";

  return 0;
}