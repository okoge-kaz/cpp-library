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
using lll = __int128_t;

struct edge {
    int from; int to; ll w;
    edge(int from, int to, ll w) : from(from), to(to), w(w) {}
};

// verify https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_C
// LCA Lowest Common Ancestor 計算量 O(N log(K)) = O(N log(N))
class LCA {
    private:
        vector<vector<int>>parent; // ダブリングを用いた parent[k][u] := uの2^k先の親 
        vector<int>depth;// 根からの深さ（距離)

        // 重みつき
        bool is_dijkstra = false;
        int N; vector<ll>dist;

        void init(const vector<vector<int>> &G, int root=0){
            int V = (int)G.size();
            int K = 1;
            while((1<<K) < V) K++;
            // assign 指定サイズまで動的確保
            parent.assign(K,vector<int>(V,-1));
            depth.assign(V,-1);
            dfs(G, root, -1, 0);// 根の深さは0とする
            for(int k=0;k+1<K;k++){
                for(int v=0;v<V;v++){
                    if(parent[k][v]<0) parent[k+1][v] = -1;// v の 2^k 先の親が存在しないとき、当然 2^(k+1)先にも存在しない
                    else{
                        parent[k+1][v] = parent[k][parent[k][v]];// ダブリング 
                    }
                }
            }
        }
        void dfs(const vector<vector<int>> &G, int v, int p, int d){
            parent[0][v] = p;
            depth[v] = d;
            for(int nv:G[v]){
                if(nv!=p) dfs(G, nv, v, d+1);// 親への逆流を防ぐ
            }
        }
    public:
        LCA(const vector<vector<int>> &G, int root = 0) { init(G, root); }
        int query(int u, int v){
            // 2頂点のLCA(Lowest Common Ancestor)を求める
            if(depth[u] < depth[v]) swap(u,v);// uの方が深いとして考える
            int K = (int)parent.size();
            // LCAまでの距離を同じにする
            for(int k=0;k<K;k++){
                if((depth[u]-depth[v]) & (1<<k)){
                    u = parent[k][u];
                }
            }
            // 二分探索でLCAを求める
            if(u==v) return u;
            for(int k=K-1;k>=0;k--){
                if(parent[k][u]!=parent[k][v]){
                    // 深さを揃えたのでいずれ同じ頂点に到達する
                    u = parent[k][u];
                    v = parent[k][v];
                }
            }
            return parent[0][u];
        }
        int get_dist(int u,int v){
            // LCAを用いた２頂点間距離 重みなし
            return depth[u] + depth[v] - 2 * depth[query(u,v)];
        }
        ll get_distance(int u,int v){
            // LCAを用いた2頂点間距離 重みあり
            // 計算量 ダイクストラを用いるので O(N log(N)) 初回のみ
            if(is_dijkstra==false){
                cerr << "please call dikstra member function" << endl;
                assert(0 && "please call dikstra member function");
            }
            return dist[u]+dist[v] - 2*dist[query(u,v)];
        }
        bool is_on_path(int u, int v, int a){
            // 頂点aが、頂点uと頂点vとの間のパス上にある
            return (get_dist(u,a)+get_dist(a,v) == get_dist(u,v));
        }
        void dijkstra(const vector<vector<edge>> &g){
            // dijkstra
            int root = 0;// init関数にて設定した根頂点(適時変える)
            N = (int)g.size();
            dist.assign(N,INF); dist[root] = 0;
            priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> que;
            que.push(pair(dist[root],root));

            while(!que.empty()){
                auto[d,v]= que.top(); que.pop();
                if(d>dist[v])continue;
                for(auto e:g[v]){
                    if(chmin(dist[e.to],dist[v]+e.w)){
                        que.push(pair(dist[e.to],e.to));
                    }
                }
            }
            is_dijkstra = true; 
        }
};


int main(){
    int N; cin >> N;
    vector<vector<int>>G(N);
    vector<vector<edge>>g(N);
    for(int i=0;i<N-1;i++){// O(N)
        int u,v; ll w;
        cin >> u >> v >> w;
        --u,--v;
        G[u].push_back(v); G[v].push_back(u);
        g[u].emplace_back(edge(u,v,w));
        g[v].emplace_back(edge(v,u,w));
    }
    LCA lca(G); // N log(N)
    lca.dijkstra(g);// N log(N)
    ll ans = 0;
    for(int i=0;i<N-1;i++){
        for(int j=i+1;j<N;j++){
            ans += lca.get_distance(i,j);// O(1)
        }
    }
    cout << ans << endl;
}