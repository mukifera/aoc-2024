#include <bits/stdc++.h>

using namespace std;

int main() {

  string line;
  vector<string> grid;
  map<char,vector<pair<int,int>>> mp;
  while (getline(cin, line)) {
    for(int i=0; i<line.size(); i++) {
      char c = line[i];
      if(c == '.') continue;
      mp[c].push_back({grid.size(), i});
    }
    grid.push_back(line);
  }
  
  set<pair<int,int>> st;
  for(pair<char,vector<pair<int,int>>> p : mp) {
    vector<pair<int,int>> vec = p.second;
    int n = vec.size();
    for(int i=0; i+1<n; i++) {
      for(int j=i+1; j<n; j++){
        st.insert(vec[i]);
        st.insert(vec[j]);
        pair<int,int> diff = {vec[i].first-vec[j].first, vec[i].second-vec[j].second};
        pair<int,int> x = {vec[i].first, vec[i].second};
        while(true){
          x = {x.first + diff.first, x.second + diff.second};
          if(x.first < 0 || x.first >= grid.size() || x.second < 0 || x.second >= grid[0].size()) break;
          st.insert(x);
        }
        x = {vec[j].first, vec[j].second};
        while(true){
          x = {x.first - diff.first, x.second - diff.second};
          if(x.first < 0 || x.first >= grid.size() || x.second < 0 || x.second >= grid[0].size()) break;
          st.insert(x);
        }
      }
    }
  }

  cout << st.size() << '\n';

  return 0;
}