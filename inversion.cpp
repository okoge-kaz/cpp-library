#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
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
// バブルソートの交換回数である転倒数をfenwick_treeで求める
// 参考: https://scrapbox.io/pocala-kyopro/%E8%BB%A2%E5%80%92%E6%95%B0
// verified: https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_j

template<typename T>
ll inversion(vector<T> &vec){
    // vector を受け取って転倒数をlong longで返す
    ll ans = 0; int size = (int)vec.size();
    // 座標圧縮
    vector<T>sorted_vec = vec;
    sort(sorted_vec.begin(),sorted_vec.end());
    vector<int>index(size);
    for(int i=0;i<size;i++){
        index[i] = lower_bound(sorted_vec.begin(),sorted_vec.end(),vec[i])-sorted_vec.begin();
    }
    // fenwick_tree
    atcoder::fenwick_tree<T> fw(size);
    for(int i=0;i<size;i++){
        ans += i - fw.sum(0,index[i]);
        fw.add(index[i],1);
    }
    return ans;
}
int main(){
    int n; cin >> n;
    vector<ll>a(n); for(ll &e:a) cin >> e;
    cout << inversion(a) << endl;
}