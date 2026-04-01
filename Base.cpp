#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
template<class A,class B> ostream& operator<<(ostream& o,const pair<A,B>& p){return o<<"{"<<p.first<<","<<p.second<<"}";}
template<class T> ostream& operator<<(ostream& o,const vector<T>& v){o<<"[ ";for(auto&i:v)o<<i<<" ";return o<<"]";}
template<class T> ostream& operator<<(ostream& o,const vector<vector<T>>& g){o<<"{\n";for(size_t i=0;i<g.size();++i)o<<"  "<<i<<" --> "<<g[i]<<"\n";return o<<"}";}
template<class T> ostream& operator<<(ostream& o,const set<T>& v){o<<"{ ";for(auto&i:v)o<<i<<" ";return o<<"}";}
template<class T> ostream& operator<<(ostream& o,const multiset<T>& v){o<<"{ ";for(auto&i:v)o<<i<<" ";return o<<"}";}
template<class K,class V> ostream& operator<<(ostream& o,const map<K,V>& v){o<<"{ ";for(auto&i:v)o<<i.first<<":"<<i.second<<" ";return o<<"}";}
template<class... A> void bug__(A&&... a){((cerr<<a<<" "),...);cerr<<"\n";}
#define bug(x...) bug__(x)
#define safe bug("safe")
#else
#define bug(x...) void(0)
#define safe void(0)
#endif
 
using ll = long long;
// #define int ll
 
#define rep(i,a,b) for (int i = (a); i <= (b); i++)
#define per(i,b,a) for (int i = (b); i >= (a); i--)
#define rf(i,b)    for (int i = (b - 1); i >= 0; i--)
#define inp(a)     for (auto &x : a) cin >> x;
#define op(v,l,r)  rep(_i,(l),(r)) cout << (v)[_i] << " \n"[_i==(r)];
#define fr(i,b)    for (int i = 0; i < (b); i++)
#define pb         push_back
#define pob        pop_back
#define eb         emplace_back
#define F          first
#define S          second
#define bg         begin()
#define ed         end()
#define endl       "\n"
#define sp         " "
#define ins        insert
#define all(x)     x.bg, x.ed
#define z(x)       int(x.size())
 
#define pi   pair<int,int>
#define vpi  vector<pi>
#define vi   vector<int>
#define vb   vector<bool>
#define vbb  vector<vb>
#define vii  vector<vi>
#define vipi vector<pi> 

void solve() {}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
