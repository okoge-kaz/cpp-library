#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const long long INF = 1LL << 60;
const int inf = (1 << 30);
const ll mod = 998244353;
const ll MOD = 1000000007;
const ld PI = acos(-1.0L);
int dy[] = {1, 0, -1, 0}, dx[] = {0, -1, 0, 1};
int dy8[] = {1, 1, 0, -1, -1, -1, 0, 1}, dx8[] = {0, -1, -1, -1, 0, 1, 1, 1};
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }
// LowLink 橋/間接点を効率的に求めるアルゴリズム
// 計算量 O(V+E)

// 参考: https://algo-logic.info/bridge-lowlink/
// 参考: https://ei1333.github.io/luzhiled/snippets/graph/lowlink.html
// briges: verified https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_B
// aps: verified https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_A

class LowLink{
    // aps, bridges はsortされていない
    private:
        const vector<vector<int>> &G;
        // used: 使用済みかどうか, ord: dfsで頂点を訪れた順番, low: 
        vector<bool> used; vector<int> ord, low;
        vector<int>aps;// 間接点の集合
        vector<pair<int,int>>bridges;// 橋の集合

        int dfs(int cv, int k, int par=-1){
            // cv: 探索中の頂点, k: dfsで何番目に探索するか, par: 親頂点
            used[cv] = true;
            ord[cv] = k++;
            low[cv] = ord[cv];
            bool is_aps = false;// 間接点かどうか
            int cnt = 0;// 子の数
            for(int nv:G[cv]){
                if(used[nv]){
                    // 後退辺のとき
                    if(nv==par) continue;// 逆流を防ぐ
                    chmin(low[cv],ord[nv]);
                }
                else{
                    cnt++;
                    k = dfs(nv, k, cv);
                    chmin(low[cv],low[nv]);
                    if(par != -1 && ord[cv] <= low[nv]) is_aps = true;
                    if(ord[cv] < low[nv]) bridges.emplace_back(min(cv, nv),max(cv, nv));
                    // u,v のpairは u < v となるようにしておく
                }
            }
            if(par == -1 && cnt >= 2) is_aps = true;
            
            if(is_aps){
                aps.push_back(cv);//間接点
            }
            return k;
        }
    public:
        LowLink(const vector<vector<int>> &G_) : G(G_) {
            used.assign(int(G.size()),0);
            ord.assign(int(G.size()),0);
            low.assign(int(G.size()),0);
            int k = 0;
            for(int i=0;i<int(G.size());i++){
                if(!used[i]) k = dfs(i, k);
            }
        }
        vector<int> get_aps(){
            // 間接点: articulation pointsを返す
            // 注意: apsは未sort
            return aps;
        }
        vector<pair<int,int>> get_bridge(){
            // 橋: bridgeを返す
            // 注意 bridgesは未sort
            return bridges;
        }
};
int main(){
    int V,E; cin >> V >> E;
    vector<vector<int>>G(V);
    for(int i=0;i<E;i++){
        int s,t; cin >> s >> t;
        G[s].push_back(t); G[t].push_back(s);
    }
    LowLink lw(G);
    vector<int>aps = lw.get_aps();
    sort(aps.begin(),aps.end());
    for(int v:aps) cout << v << endl;
}