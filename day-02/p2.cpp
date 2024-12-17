#include <bits/stdc++.h>

using namespace std;

bool isInc(const vector<int>& report) {
  for(int i=1; i<report.size(); ++i){
    if(report[i-1] >= report[i]) return false;
  }
  return true;
}

bool isDec(const vector<int>& report) {
  for(int i=1; i<report.size(); ++i){
    if(report[i-1] <= report[i]) return false;
  }
  return true;
}

bool isSafe(const vector<int>& report) {
  int n = report.size();
  int diff = 0;
  for(int i=1; i<n; ++i) {
    diff = abs(report[i-1]-report[i]);
    if(diff < 1 || diff > 3) return false;
  }

  return isInc(report) || isDec(report);
}

int main() {

  string line;
  int ans = 0;
  int x;
  while (getline(cin, line)) {
    stringstream ss(line);
    vector<int> report;
    while(ss >> x) {
      report.push_back(x);
    }
    if(isSafe(report)){
      ++ans;
      continue;
    }
    for(int i=0; i<report.size(); i++){
      int x = report[i];
      report.erase(report.begin()+i);
      if(isSafe(report)){
        ++ans;
        break;
      }
      report.insert(report.begin()+i, x);
    }
  }
  
  cout << ans << "\n";

  return 0;
}