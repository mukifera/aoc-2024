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
  
  string consume(int n) {
    string ret = "";
    for(int i=0; i<n; i++) {
      ret += consume();
    }
    return ret;
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
    if(peek() == c) {
      consume();
      return true;
    }
    return false;
  }

  bool matches(string sub) {
    if(curr + sub.size() >= s.size()) return false;
    for(int i=0; i<sub.size(); i++) {
      if(s[curr+i] != sub[i]) return false;
    }
    consume(sub.size());
    return true;
  }

  bool atEnd() {
    return curr >= s.size();
  }
};

int main() {

  string line;
  long long ans = 0;
  bool ignore = false;
  while (getline(cin, line)) {
    parser p(line);

    int x, y;
    string num;

    while(!p.atEnd()) {
      if(p.matches("do()")) {
        ignore = false;
        continue;
      }
      if(p.matches("don't()")) {
        ignore = true;
        continue;
      }
      if(!p.matches("mul(")){
        p.consume();
        continue;
      } 

      num = p.consumeNumber();
      if(num.size() < 0 || num.size() > 3) continue;
      x = stoi(num);

      if(!p.matches(',')) continue;

      num = p.consumeNumber();
      if(num.size() < 0 || num.size() > 3) continue;
      y = stoi(num);

      if(!p.matches(')')) continue;

      if(!ignore){
        ans += 1LL * x * y;
      }
    }
  }
  
  cout << ans << "\n";

  return 0;
}