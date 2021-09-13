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
// 図形が同一であるか判定する。
// verified: https://atcoder.jp/contests/abc218/tasks/abc218_c

bool isSame(const vector<string> &S, const vector<string> &T){
    // . # で表される図形が同じかどうかを判定する。ただし図形は # からなるとする。
    // 計算量 O(N^2) (ただし N :=  max( S.size(), T.size() ) )
    auto find_left_top = [](const vector<string> &S) -> pair<int,int> {
        int h = int(S.size());
        int w = int(S[0].size());
        for(int i=0;i<h;i++) for(int j=0;j<w;j++){
            if(S[i][j] == '#'){
                return pair(i,j);// 0-index
            }
        }
    };
    auto [si,sj] = find_left_top(S);
    auto [ti,tj] = find_left_top(T);
    int offset_i = ti - si;
    int offset_j = tj - sj;
    int h = int(S.size()); int w = int(S[0].size()); 
    for(int i=0;i<h;i++) for(int j=0;j<w;j++){
        int ii = i + offset_i; int jj = j + offset_j;
        if(0 <= ii && ii < h && 0 <= jj && jj < w){
            if(S[i][j] != T[ii][jj]) return false;
        }
        else{
            if(S[i][j]=='#') return false;
        }
    }
    return true;
}