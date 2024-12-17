#include <bits/stdc++.h>

using namespace std;

int main() {

  string line;
  map<int,vector<int>> pre;
  map<int,vector<int>> nxt;
  while (getline(cin, line)) {
    if(line == "") break;
    stringstream ss(line);
    int a, b;
    ss >> a;
    char ch;
    ss >> ch;
    ss >> b;
    pre[b].push_back(a);
    nxt[a].push_back(b);
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
    if(safe) continue;

    map<int,int> indeg;
    for(int x : st){
      for(int y : pre[x]){
        if(st.count(y) == 0) continue;
        indeg[x]++;
      }
    }
    queue<int> q;
    for(int x : st){
      if(indeg[x] == 0) q.push(x);
    }
    vector<int> ordered;
    while(!q.empty()) {
      int u = q.front();
      q.pop();
      ordered.push_back(u);
      for(int v : nxt[u]) {
        if(st.count(v) == 0) continue;
        indeg[v]--;
        if(indeg[v] == 0) q.push(v);
      }
    }

    ans += 1LL * ordered[ordered.size()/2];
  }

  cout << ans << "\n";

  return 0;
}