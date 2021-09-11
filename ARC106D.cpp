#include <bits/stdc++.h>
#define _GLIBCXX_DEBUG
using namespace std;
typedef long long ll;
typedef long double ld;
const long long INF = 1LL << 60;
const ll mod = 998244353;
const ll MOD = 1000000007;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }
// 累積和系統の問題のもっとも一般的な問題をライブラリ化したものが本回答である。
// 問題: https://atcoder.jp/contests/arc106/tasks/arc106_d
// 解説：https://atcoder.jp/contests/arc106/editorial/238

ll combination(ll n,ll k){
    if(n<k){
        return 0;
    }
    else if(k==0){
        return 1;
    }
    else{
        ll res = 1;
        for(ll i=0;i<k;i++){
            res = (res * (n-i))/(i+1);
        }
        return res;
    }
}
int main(){
    
}