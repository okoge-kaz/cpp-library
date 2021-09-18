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
// verified https://atcoder.jp/contests/abc057/tasks/abc057_c

// 約数全列挙
vector<ll> enum_divisors(ll n){
    // 計算量 O(√n)
    vector<ll> res;
    for(ll i=1;i*i<=n;i++){
        if(n % i == 0){
            res.push_back(i);
            // 平方数の場合は重複が生じうるので
            if(n/i != i) res.push_back(n/i);
        }
    }
    sort(res.begin(),res.end());
    return res;
}
// 数字の桁数を返す
int digit(ll n){
    if(n==0) return 1;// 0は1桁とでる。
    int res = 0;
    while(n){
        res++;
        n /= 10;
    }
    return res;
}

int main(){
    ll n; cin >> n;
    auto vec = enum_divisors(n); int size = int(vec.size());
    int ans = inf;
    for(int i=0;i<=(size/2);i++){
        chmin(ans,max(digit(vec[i]),digit(vec[size-1-i])));
    }
    cout << ans << endl;
}