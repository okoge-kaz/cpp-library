#include <bits/stdc++.h>
#define _GLIBCXX_DEBUG
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

struct edge {
    int from; int to; ll w;
    edge(int from, int to, ll w) : from(from), to(to), w(w) {}
};
using Graph = vector<vector<edge>>;

// 経路復元
vector<ll> get_path(const vector<ll> &prev, ll g){
    // 方針としては、終点g から始点 sまで逆に辿る
    vector<ll> path;
    for(int cur = g; cur != -1;cur = prev[cur]){
        // -1 (= 始点)に戻るまで、prevで逆に戻る
        path.push_back(cur);
    }
    reverse(path.begin(),path.end());
    return path;
}

int main(){
    // 頂点数、辺数、始点
    int N, M, s;
    cin >> N >> M >> s;
    // 終点がある場合は、下の最短経路復元用の関数の上のg (=終点)を編集すること
    
    // グラフ
    Graph G1(N);
    for(int i=0;i<M;i++){
        int a,b,w;
        cin >> a >> b >> w;
        // 0-indexed --a,--b;
        G1[a].push_back(edge(a,b,w));// 有向グラフなので
    }

    // ダイクストラ法
    vector<ll> dist1(N,INF);
    dist1[s] = 0;// 始点
    vector<ll> prev1(N,-1);// 経路復元
    
    // (d[v], v)のペアを要素としたヒープをつくる
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> que1;
    // priority_queue は通常、大きい順になるので、greaterによって逆順にしている
    // vector<pair<ll,int>> は逆順にするときに必要な処理:詳細はAPG4b
    que1.push(make_pair(dist1[s], s));

    // ダイクストラ法の反復を開始
    while(!que1.empty()){
        // v: 使用済みでない頂点のうち d[v]が最小
        // d: vに対するキー値
        int v = que1.top().second;
        ll d = que1.top().first;
        que1.pop();

        // d > dist[v] は、(d,v)がゴミであることを表す = 最短経路でないもの
        if(d > dist1[v]) continue;

        // 頂点v を始点とした各辺を緩和
        for(auto e:G1[v]){
            if(chmin(dist1[e.to],dist1[v] + e.w)){
                // 更新があるならヒープに新たに挿入
                que1.push(make_pair(dist1[e.to],e.to));
                // 経路復元用
                prev1[e.to] = v;// vを通って e.toに辿り着いた
            }
        }
    }

    // 結果出力
    for(int v=0;v<N;v++){
        if(dist1[v] < INF) cout << dist1[v] << endl;
        else cout << "INF" << endl;
    }

    // 最短経路復元
    // ゴールをg とする。
    ll g;
    auto ans = get_path(prev1, g);// ans は vector 
    // prev は前に定義した vector , gはgoal
}