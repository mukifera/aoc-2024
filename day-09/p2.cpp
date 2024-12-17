#include <bits/stdc++.h>

using namespace std;

int main() {

  string line;
  cin >> line;

  long long ans = 0;

  vector<pair<int,int>> files, gaps;
  for(int i=0, j=0; i<line.size(); j+=(int)(line[i]-'0'), i++){
    if(i%2==0) files.push_back({j, (int)(line[i]-'0')});
    else gaps.push_back({j, (int)(line[i]-'0')});
  }

  for(int id=0; id<files.size(); id++) {
    int j = files[id].first;
    int len = files[id].second;
    ans += 1LL * (j+j+len-1) * len * id / 2;
  }

  for(int id=files.size()-1; id>=0; id--) {
    int j = files[id].first;
    int len = files[id].second;
    for(int i=0; i<gaps.size(); i++){
      if(gaps[i].first > j) break;
      if(gaps[i].second < len) continue;
      ans -= 1LL * (j+j+len-1) * len * id / 2;
      ans += 1LL * (gaps[i].first+gaps[i].first+len-1) * len * id / 2;

      gaps[i].first += len;
      gaps[i].second -= len;
      break;
    }
  }

  cout << ans << "\n";

  return 0;
}