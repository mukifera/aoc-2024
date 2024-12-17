#include <bits/stdc++.h>

using namespace std;

int main() {

  string line;
  map<int,vector<int>> pre;
  while (getline(cin, line)) {
    if(line == "") break;
    stringstream ss(line);
    int a, b;
    ss >> a;
    char ch;
    ss >> ch;
    ss >> b;
    pre[b].push_back(a);
  }
  
  long long ans = 0;
  while (getline(cin, line)) {
    stringstream ss(line);
    vector<int> pages;
    set<int> st;
    int x; ss >> x;
    pages.push_back(x);
    st.insert(x);
    char ch;
    while(ss >> ch) {
      ss >> x;
      pages.push_back(x);
      st.insert(x);
    }

    map<int, bool> vis;
    bool safe = true;
    for(int x : pages) {
      bool good = true;
      for(int y : pre[x]){
        if(!st.count(y)) continue;
        if(!vis[y]) {
          good = false;
          break;
        }
      }
      if(!good) {
        safe = false;
        break;
      }
      vis[x] = true;
    }
    if(!safe) continue;

    ans += 1LL * pages[pages.size()/2];
  }

  cout << ans << "\n";

  return 0;
}