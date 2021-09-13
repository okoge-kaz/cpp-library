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

// 2つの図形が同一であるかを判定する問題の時は片方を固定して、もう片方を回転させる。
// どちらとも回転させては意味がない。(やりがち)

// 数字列ではなく、2次元の文字列を回転させる関数
// 計算量 0(N^2) N:= int(S.size())
vector<string> rotate(const vector<string> &S){
    // 図形を左に90度回転する関数
    vector<string> res(int(S[0].size()));
    for(int w=0;w<int(S[0].size());w++){
        for(int h=int(S.size())-1;h>=0;h--){
            res[w].push_back(S[h][w]);
        }
    }
    return res;
}

vector<vector<int>> rotate(const vector<vector<int>> &S){
    // 行列を転置する
    vector<vector<int>> res(int(S[0].size()));
    for(int w=0;w<int(S[0].size());w++){
        for(int h=int(S.size()-1);h>=0;h--){
            res[w].push_back(S[h][w]);
        }
    }
    return res;
}