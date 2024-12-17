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

  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  
  int ans = 0;
  for (int i=0; i<a.size(); i++){
    ans += abs(a[i] - b[i]);
  }
  cout << ans << "\n";

  return 0;
}