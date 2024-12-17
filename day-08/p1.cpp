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
        pair<int,int> diff = {vec[i].first-vec[j].first, vec[i].second-vec[j].second};
        pair<int,int> x = {vec[i].first + diff.first, vec[i].second + diff.second};
        pair<int,int> y = {vec[j].first - diff.first, vec[j].second - diff.second};
        if(x.first >= 0 && x.first < grid.size() && x.second >= 0 && x.second < grid[0].size()) st.insert(x);
        if(y.first >= 0 && y.first < grid.size() && y.second >= 0 && y.second < grid[0].size()) st.insert(y);
      }
    }
  }

  cout << st.size() << '\n';

  return 0;
}