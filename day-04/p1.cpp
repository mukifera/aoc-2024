#include <bits/stdc++.h>

using namespace std;


int main() {

  string line;
  vector<string> grid;
  while (getline(cin, line)) {
    grid.push_back(line);
  }
  
  int moves[8][2] = {{0,1},{0,-1},{1,0},{1,1},{1,-1},{-1,0},{-1,1},{-1,-1}};
  
  int n = grid.size();
  int m = grid[0].size();

  int ans = 0;
  string word = "XMAS";
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      for(int k=0; k<8; k++) {
        int di = moves[k][0];
        int dj = moves[k][1];
        bool good = true;
        for(int l=0, ii=i, jj=j; l<word.size(); l++, ii+=di, jj+=dj) {
          if(ii < 0 || ii >= n || jj < 0 || jj >= m || word[l] != grid[ii][jj]){
            good = false;
            break;
          }
        }
        if(good) ans++;
      }
    }
  }

  cout << ans << "\n";

  return 0;
}