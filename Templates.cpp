merge segments
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i].second;
    }
    sort(a.begin(), a.end());
    vector<pair<int,int>> p;
    int l = a[0].first, r = a[0].second;
    for (auto [f, s]: a) {
        if (f >= l && f <= r) r = max(r, s);
        else {
            p.push_back({l, r});
            l = f, r = s;
        }
    }
    p.push_back({l, r});

nCr
auto powmod = [&] (long long a, long long b) {
    long long res = 1;
    a %= mod;
    for(; b; b >>= 1) {
        if (b & 1) {
            res = (res * a) % mod;
        }
         a = (a * a) % mod;
     }
     return res;
};
auto binom = [&] (int x, int y) {
    return fac[x] * powmod(fac[x - y], mod - 2) % mod;
};


// DSU

struct DSU {
    vector<int> s, p;
    DSU() {}
    DSU(int n) {
        init(n);
    }
    void init(int n) {
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        s.assign(n, 1);
    }
    int find(int v) {
        if (p[v] == v) return v;
        return p[v] = find(p[v]);
    }
    bool same(int a, int b) {
        return find(a) == find(b);
    }
    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (s[a] < s[b]) {
            swap(a, b);
        }
        p[b] = a;
        s[a] += s[b];
    }
};


// Sparese Table
struct SparseTable {
private:
    int n;
    vector<vector<int>> mn;
    vector<vector<int>> mx;      
    vector<int> logVal;          

public:

    SparseTable(const vector<int>& a) {
        n = a.size();
        int maxLog = 32 - __builtin_clz(n); 

        mn.assign(n, vector<int>(maxLog));
        mx.assign(n, vector<int>(maxLog));
        logVal.assign(n + 1, 0);


        for (int i = 2; i <= n; i++)
            logVal[i] = logVal[i / 2] + 1;


        for (int i = 0; i < n; i++) {
            mx[i][0] = a[i];
            mn[i][0] = a[i];
        }


        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
            }
        }

        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int queryMin(int l, int r) {
        int j = logVal[r - l + 1];
        return min(mn[l][j], mn[r - (1 << j) + 1][j]);
    }

    int queryMax(int l, int r) {
        int j = logVal[r - l + 1];
        return max(mx[l][j], mx[r - (1 << j) + 1][j]);
    }
};


// Trie

//mridul1809
#include<bits/stdc++.h>
using namespace std;

class Trie {

public:

	//N is number of possible characters in a string
	const static int N = 26;

	//baseChar defines the base character for possible characters
	//like '0' for '0','1','2'... as possible characters in string 
    const static char baseChar = 'a';

	struct TrieNode
	{
		int next[N];
		//if isEnd is set to true , a string ended here
		bool isEnd;
		//freq is how many times this prefix occurs
    	int freq;

		TrieNode()
		{
			for(int i=0;i<N;i++)
				next[i] = -1;
			isEnd = false;
			freq = 0;
		}
	};

	//the implementation is via vector and each position in this vector
	//is similar as new pointer in pointer type implementation
	vector <TrieNode> tree;

	//Base Constructor
	Trie ()
	{
		tree.push_back(TrieNode());
	}

	//inserting a string in trie
	void insert(const string &s)
    {
        int p = 0;
        tree[p].freq++;
        for(int i=0;i<s.size();i++)
        {
        	// tree[]
            if(tree[p].next[s[i]-baseChar] == -1)
            {
                tree.push_back(TrieNode());
                tree[p].next[s[i]-baseChar] = tree.size()-1;
            }

            p = tree[p].next[s[i]-baseChar];
            tree[p].freq++;
        }
        tree[p].isEnd = true;
    }

    //check if a string exists as prefix
    bool checkPrefix(const string &s)
    {
    	int p = 0;
    	for(int i=0;i<s.size();i++)
    	{
    		if(tree[p].next[s[i]-baseChar] == -1)
    			return false;

    		p = tree[p].next[s[i]-baseChar];
    	}
    	return true;
    }

    //check is string exists
    bool checkString(const string &s)
    {
    	int p = 0;
    	for(int i=0;i<s.size();i++)
    	{
    		if(tree[p].next[s[i]-baseChar] == -1)
    			return false;

    		p = tree[p].next[s[i]-baseChar];
    	}

    	return tree[p].isEnd;
    }

    //persistent insert
    //returns location of new head
    int persistentInsert(int head , const string &s)
    {
    	int old = head;

    	tree.push_back(TrieNode());
    	int now = tree.size()-1;
    	int newHead = now;

    	int i,j;

    	for(i=0;i<s.size();i++)
    	{
    		if(old == -1)
    		{
    			tree.push_back(TrieNode());
    			tree[now].next[s[i]-baseChar] = tree.size() - 1;
    			tree[now].freq++;
    			now = tree[now].next[s[i]-baseChar];
    			continue;
    		}
    		for(j=0;j<N;j++)
    			tree[now].next[j] = tree[old].next[j];
    		tree[now].freq = tree[old].freq;
    		tree[now].isEnd = tree[old].isEnd;

    		tree[now].freq++;
    		
    		tree.push_back(TrieNode());
    		tree[now].next[s[i]-baseChar] = tree.size()-1;

    		old = tree[old].next[s[i]-baseChar];
    		now = tree[now].next[s[i]-baseChar];
    	}

    	tree[now].freq++;
    	tree[now].isEnd = true;

    	return newHead;
    }

    //persistent check prefix
    bool persistentCheckPrefix(int head, const string &s)
    {
    	int p = head;
    	for(int i=0;i<s.size();i++)
    	{
    		if(tree[p].next[s[i]-baseChar] == -1)
    			return false;

    		p = tree[p].next[s[i]-baseChar];
    	}
    	return true;
    }

    //persistent check string
    bool persistentCheckString(int head, const string &s)
    {
    	int p = head;
    	for(int i=0;i<s.size();i++)
    	{
    		if(tree[p].next[s[i]-baseChar] == -1)
    			return false;

    		p = tree[p].next[s[i]-baseChar];
    	}
    	return tree[p].isEnd;
    }
};

string s,temp;
int main()
{
    Trie trie = Trie();

    cout << trie.checkString("hello") << endl;	//output : 0

    trie.insert("hello");

    cout << trie.checkPrefix("hell") << endl;	//output : 1

    cout << trie.checkString("hell") << endl;	//output : 0

    cout << trie.checkString("hello") << endl;	//output : 1


    //Example for persistent trie 
    Trie persistentTrie = Trie();
    vector <int> heads;

    //insert words 
    heads.push_back(0);
    heads.push_back(persistentTrie.persistentInsert(heads[heads.size()-1] , "hello"));
    heads.push_back(persistentTrie.persistentInsert(heads[heads.size()-1] , "world"));
    heads.push_back(persistentTrie.persistentInsert(heads[heads.size()-1] , "persistent"));
    heads.push_back(persistentTrie.persistentInsert(heads[heads.size()-1] , "trie"));

    cout << persistentTrie.persistentCheckString(heads[0] , "hello") << endl;	//output : 0
    cout << persistentTrie.persistentCheckString(heads[1] , "hello") << endl;	//output : 1

    cout << persistentTrie.persistentCheckString(heads[1] , "world") << endl;	//output : 0
    cout << persistentTrie.persistentCheckString(heads[2] , "world") << endl;	//output : 1

    cout << persistentTrie.persistentCheckString(heads[2] , "persistent") << endl;	//output : 0
    cout << persistentTrie.persistentCheckString(heads[3] , "persistent") << endl;	//output : 1

    cout << persistentTrie.persistentCheckString(heads[3] , "trie") << endl;	//output : 0
    cout << persistentTrie.persistentCheckString(heads[4] , "trie") << endl;	//output : 1

    
    return 0;
}


// Combinatorics template

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {
    return (ull)rng() % B;
}
 
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
 
clock_t startTime;
double getCurrentTime() {
    return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}
 
const uint MOD = 1000000007;
template<uint mod = MOD> struct mint { // 1000000007  1000000009
    uint x;
 
    mint() : x(0) {}
    mint(ll _x) {
        _x %= mod;
        if (_x < 0) _x += mod;
        x = _x;
    }
 
    mint& operator += (const mint &a) {
        x += a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    mint& operator -= (const mint &a) {
        x += mod - a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    mint& operator *= (const mint &a) {
        x = (ull)x * a.x % mod;
        return *this;
    }
    mint pow(ll pw) const {
        mint res = 1;
        mint cur = *this;
        while(pw) {
            if (pw & 1) res *= cur;
            cur *= cur;
            pw >>= 1;
        }
        return res;
    }
    mint inv() const {
        assert(x != 0);
        uint t = x;
        uint res = 1;
        while(t != 1) {
            uint z = mod / t;
            res = (ull)res * (mod - z) % mod;
            t = mod - t * z;
        }
        return res;
    }
    mint& operator /= (const mint &a) {
        return *this *= a.inv();
    }
    mint operator + (const mint &a) const {
        return mint(*this) += a;
    }
    mint operator - (const mint &a) const {
        return mint(*this) -= a;
    }
    mint operator * (const mint &a) const {
        return mint(*this) *= a;
    }
    mint operator / (const mint &a) const {
        return mint(*this) /= a;
    }
 
    bool sqrt(mint &res) const {
        if (mod == 2 || x == 0) {
            res = *this;
            return true;
        }
        if (pow((mod - 1) / 2) != 1) return false;
        if (mod % 4 == 3) {
            res = pow((mod + 1) / 4);
            return true;
        }
        int pw = (mod - 1) / 2;
        int K = 30;
        while((1 << K) > pw) K--;
        while(true) {
            mint t = myRand(mod);
            mint a = 0, b = 0, c = 1;
            for (int k = K; k >= 0; k--) {
                a = b * b;
                b = b * c * 2;
                c = c * c + a * *this;
                if (((pw >> k) & 1) == 0) continue;
                a = b;
                b = b * t + c;
                c = c * t + a * *this;
            }
            if (b == 0) continue;
            c -= 1;
            c *= mint() - b.inv();
            if (c * c == *this) {
                res = c;
                return true;
            }
        }
        assert(false);
    }
 
    bool operator == (const mint &a) const {
        return x == a.x;
    }
    bool operator != (const mint &a) const {
        return x != a.x;
    }
    bool operator < (const mint &a) const {
        return x < a.x;
    }
};
template<uint mod = MOD> struct Factorials {
    using Mint = mint<mod>;
    vector<Mint> f, fi;
 
    Factorials() : f(), fi() {}
    Factorials(int n) {
        n += 10;
        f = vector<Mint>(n);
        fi = vector<Mint>(n);
        f[0] = 1;
        for (int i = 1; i < n; i++)
            f[i] = f[i - 1] * i;
        fi[n - 1] = f[n - 1].inv();
        for (int i = n - 1; i > 0; i--)
            fi[i - 1] = fi[i] * i;
    }
 
    Mint C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return f[n] * fi[k] * fi[n - k];
    }
};
 
template<uint mod = MOD> struct Powers {
    using Mint = mint<mod>;
    vector<Mint> p, pi;
 
    Powers() : p(), pi() {}
    Powers(int n, Mint x) {
        n += 10;
        if (x == 0) {
            p = vector<Mint>(n);
            p[0] = 1;
        } else {
            p = vector<Mint>(n);
            pi = vector<Mint>(n);
            p[0] = pi[0] = 1;
            Mint xi = x.inv();
            for (int i = 1; i < n; i++) {
                p[i] = p[i - 1] * x;
                pi[i] = pi[i - 1] * xi;
            }
        }
    }
 
    Mint pow(int n) {
        if (n >= 0)
            return p[n];
        else
            return pi[-n];
    }
};
template<uint mod = MOD> struct Inverses {
    using Mint = mint<mod>;
    vector<Mint> ii;
 
    Inverses() : ii() {}
    Inverses(int n) {
        n += 10;
        ii = vector<Mint>(n);
        ii[1] = 1;
        for (int x = 2; x < n; x++)
            ii[x] = Mint() - ii[mod % x] * (mod / x);
    }
 
    Mint inv(Mint x) {
        assert(x != 0);
        uint t = x.x;
        uint res = 1;
        while(t >= (int)ii.size()) {
            uint z = mod / t;
            res = (ull)res * (mod - z) % mod;
            t = mod - t * z;
        }
        return ii[t] * res;
    }
};
using Mint = mint<>;
 
const int N = 200200;
Factorials F(N);
