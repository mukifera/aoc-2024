#include <bits/stdc++.h>

using namespace std;

int main() {

  string line;
  vector<int> a, b;
  int x, y;
  while (getline(cin, line)) {
    stringstream ss(line);
    ss >> x >> y;
    a.push_back(x);
    b.push_back(y);
  }

  map<int,int> hist;
  for(int x : b) ++hist[x];
  
  long long ans = 0;
  for (int i=0; i<a.size(); i++){
    ans += 1LL * a[i] * hist[a[i]];
  }
  cout << ans << "\n";

  return 0;
}