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
// verified https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/2/GRL_2_A
// Minimum Spanning Tree 最小全域木 クラスカル法
// 注意: 無向グラフに適応すること
struct edge {
    int from; int to; ll w;
    edge(int from, int to, ll w) : from(from), to(to), w(w) {}
};
template<typename T>
class UnionFind {
    private:
        vector<T>par, siz, depth;// 親ノード、要素数、深さ
        void init(T N){
            par.assign(N,-1); siz.assign(N,1); depth.assign(N,1);
        }
    public:
        UnionFind(T N) { init(N); }
        T root(T x){// 根を求める
            if(par[x]==-1) return x;
            else return par[x] = root(par[x]);// 経路圧縮
        }
        bool issame(T x,T y){
            return root(x)==root(y);
        }
        bool unite(T x, T y){
            x = root(x), y = root(y);// x,yの値まで移動する
            if(x==y) return false;
            if(depth[x]<depth[y]) swap(x,y);// 常にxの方が深い
            if(depth[x]==depth[y]) depth[x]++;
            par[y] = x; siz[x] += siz[y];
            return true;
        }
        T size(T x){
            return siz[root(x)];// xを含むグループのサイズ
        }
        T deep(ll x){
            return depth[root(x)];
        }
};
bool comp_e(const edge &e1, const edge &e2) { return e1.w < e2.w; } // 辺を直接比較するための関数
class Kruskal {
    private:
        ll sum;
        vector<edge>edges;
        int V;// 頂点数
        void init(){
            sort(edges.begin(), edges.end(), comp_e); // 辺の重みでソート
            UnionFind uf(V);
            sum = 0;
            for (auto e : edges) {
                if (!uf.issame(e.from, e.to)) { // 閉路にならなければ加える
                    uf.unite(e.from, e.to);
                    sum += e.w;
                }
            }
        }
    public:
        Kruskal(const vector<edge> &edges_, int V_) : edges(edges_), V(V_) { init(); }
        ll get_sum(){
            return sum;
        }
};
int main(){
    int V,E; cin >> V >> E;
    vector<edge>edges;
    for(int i=0;i<E;i++){
        int s,t; ll w; cin >> s >> t >> w;
        edges.emplace_back(edge(s,t,w));// push_back or emplace_back にしないで直接アクセスedges[i] = edge(...)とするとバグる
    }
    Kruskal krs(edges, V);
    cout << krs.get_sum() << endl;
}