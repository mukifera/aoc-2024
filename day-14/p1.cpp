#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int W = 101;
const int H = 103;

int main() {

  string line;
  
  int quad[2][2] = {{0, 0}, {0, 0}};
  while (getline(cin, line)) {
    stringstream ss(line);
    ll px, py, vx, vy;
    ss >> px >> py >> vx >> vy;
    
    for(int i=0; i<100; i++) {
      px = (px+vx+W)%W;
      py = (py+vy+H)%H;
    }


    if(px == W/2 || py == H/2) continue;
    int i = 0, j = 0;
    if(px>W/2) i = 1;
    if(py>H/2) j = 1;

    ++quad[i][j];

  }

  ll ans = 1LL * quad[0][0] * quad[0][1] * quad[1][0] * quad[1][1];
  cout << ans << "\n";

  return 0;
}