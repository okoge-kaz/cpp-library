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
// 全面的なverifyは行っていない 9/18 std::complexを用いる方が汎用的?
// ベクトルライブラリ
class Point {
    public:
        ld x; ld y;
        Point(ld _x, ld _y) : x(_x), y(_y) {}
        ld length(){ return sqrt(x*x+y*y); }
        ld length_square(){ return x*x+y*y; }
        ld dot(const Point &point){// 内積
            // 同じ型のベクトル
            return (x*point.x + y*point.y);
        }
        Point normarized(){ return Point(x/length(), y/length()); }// 単位ベクトルにする
        ld distance_from(const Point &point){
            // 距離を返す
            return sqrt( (point.x-x)*(point.x-x) + (point.y-y)*(point.y-y) );
        }
        Point operator+() {// 単項の演算子
            return *this;
        }
        Point operator-() {// 単項の演算子
            return {-x, -y};
        }
        Point normal_unit_vector() {
            // 単位法線ベクトル
            return {-y/length(), x/length()};
        }
        // 演算子
        // 2項演算子
        Point operator+ (const Point &point) {
            return {x + point.x, y + point.y};
        }
        Point operator- (const Point &point) {
            return {x - point.x, y - point.y};
        }
        template<typename S> Point operator* (const S k) {
            // 定数倍 ここがバグの元かも
            return { x*k, y*k };
        }
        template<typename S> Point operator/ (const S k) {
            // 定数割 ここがバグの元かも
            return { x/k, y/k };
        }
        // 複合代入演算子
        Point& operator+= (const Point& point) {
            x += point.x; y += point.y;
            return *this;
        }
        Point& operator-= (const Point& point) {
            x -= point.x; y -= point.y;
            return *this;
        }
        template<typename S> Point& operator*= (const S k) {
            x *= k; y *= k;
            return *this;
        }
        template<typename S> Point& operator/= (const S k) {
            x /= k; y /= k;
            return *this;
        }
};
int main(){
    Point vec(3,5);
    cout << vec.x << " " << vec.y << endl;
    vec +=  Point(4,8);
    cout << vec.x << " " << vec.y << endl;
    vec -= Point(5,3);
    cout << vec.x << " " << vec.y << endl;
    vec = vec * 7;
    cout << vec.x << " " << vec.y << endl;
    vec /= 7;
    cout << vec.x << " " << vec.y << endl;
    
    cout << vec.distance_from(Point(0,3)) << endl;
    vec -= Point(0,3);
    cout << vec.length_square() << endl;
    vec = vec.normarized();
    cout << vec.x << " " << vec.y << endl;

}
// projection 射影

// reflection 反転