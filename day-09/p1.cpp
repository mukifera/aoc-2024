#include <bits/stdc++.h>

using namespace std;

int main() {

  string line;
  cin >> line;

  int id = 0;
  vector<int> disk;
  vector<stack<int>> inds;
  for(int i=0; i<line.size(); i++) {
    int len = (int)(line[i] - '0');
    if(i%2==0){
      inds.emplace_back();
      for(int j=0; j<len; j++) {
        inds[id].push(disk.size());
        disk.push_back(id);
      }
      id++;
    }else{
      for(int j=0; j<len; j++) disk.push_back(-1);
    }
  }

  long long ans = 0;

  for(int i=0; i<disk.size(); i++) {
    int j = inds.size()-1;
    if(inds.size() == 0 || inds[j].top() < i) break;
    if(disk[i] == -1) {
      swap(disk[i], disk[inds[j].top()]);
      inds[j].pop();
      if(inds[j].empty()) inds.pop_back();
    }
    ans += 1LL * i * disk[i];
  }

  cout << ans << "\n";

  return 0;
}