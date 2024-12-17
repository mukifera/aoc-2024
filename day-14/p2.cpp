#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int W = 101;
const int H = 103;

struct info {
  int bot;
  ll t;
  ll cycle;
};

int moves[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};

ll rec(int i, info eq, map<int,vector<info>>& node2bots, set<int>& vis) {
  if(i == 9) return eq.t;
  ll ret = 1e18;
  for(info inf : node2bots[i]) {
    if(vis.count(inf.bot)) continue;
    vis.insert(inf.bot);
    info nxt;
    ll gcd = __gcd(eq.t, inf.t);
    nxt.t = (eq.t / gcd) * (inf.t / gcd);
    gcd = __gcd(eq.cycle, inf.cycle);
    nxt.t = (eq.cycle / gcd) * (inf.cycle / gcd);
    ret = min(ret, rec(i+1, nxt, node2bots, vis));
    vis.erase(inf.bot);
  }
  return ret;
}

ll tree_time(int x, int y, vector<vector<vector<info>>>& super) {
  if(y+2 >= H) return 1e18;
  // vector<int> deg(256, 0);
  // map<int,vector<int>> bot2nodes;
  map<int,vector<info>> node2bots;
  ll cnt = 0;
  for(int i=0, k=0; i<3; i++){
    for(int j=y-i; j<=y+i; j++,k++){
      if(super[i][j].size()==0) return 1e18;
      // deg[k] = super[i][j].size();
      cnt += super[i][j].size();
      for(info inf : super[i][j]){
        // bot2nodes[inf.bot].push_back(k);
        node2bots[k].push_back(inf);
      }
    }
  }
  set<int> vis;
  return rec(0, {0, 1, 1}, node2bots, vis);
}


int main() {

  string line;
  
  vector<vector<ll>> bots;
  vector<vector<vector<info>>> super(H, vector<vector<info>>(W));
  vector<int> cycles;
  while (getline(cin, line)) {
    stringstream ss(line);
    ll px, py, vx, vy;
    ss >> px >> py >> vx >> vy;
    vx = (vx+W)%W;
    vy = (vy+H)%H;
    bots.push_back({px, py, vx, vy});
    int i = 0;
    do{
      i++;
      px = (px+vx)%W;
      py = (py+vy)%H;
      super[py][px].push_back({(int)bots.size()-1, i, -1});
    }while(px != bots.back()[0] && py != bots.back()[1]);
    cycles.push_back(i);
  }

  ll tar = bots.size() / 2;
  if(tar+tar < bots.size()) ++tar;

  for(int i=0; i<H; i++){
    // string s = "";
    for(int j=0; j<W; j++){
      for(int k=0; k<super[i][j].size(); k++){
        super[i][j][k].cycle = cycles[super[i][j][k].bot];
      }
      // if(super[i][j].size() == 0) s += '.';
      // else s += '#';
    }
    // cout << s << "\n";
  }

  ll ans = 1e18;
  for(int i=0; i<H; i++){
    for(int j=0; j<W; j++){
      ans = min(ans, tree_time(j, i, super));
      cout << i << " " << j << "\n";
    }
  }
  cout << ans << "\n";

  return 0;
}