// max seg tree
struct SegTree {
    int n;
    vector<int> t;

    SegTree(int _n) : n(_n), t(4 * n, INT_MIN) {}

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2, tl, tm);
            build(a, v * 2 + 1, tm + 1, tr);
            t[v] = max(t[v * 2], t[v * 2 + 1]);
        }
    }

    int query(int v, int tl, int tr, int l, int r) {
        if (l > r) return INT_MIN;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return max(
            query(v * 2, tl, tm, l, min(r, tm)),
            query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r)
        );
    }

    void update(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            t[v] = val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) update(v * 2, tl, tm, pos, val);
            else update(v * 2 + 1, tm + 1, tr, pos, val);
            t[v] = max(t[v * 2], t[v * 2 + 1]);
        }
    }
};


// HLD for max Tree

struct HLD {
    int n;
    vector<vector<int>> adj;

    vector<int> parent, depth, heavy, head, pos, subsize;
    vector<int> vals, base;
    int cur_pos;

    SegTree *seg;

    HLD(int _n) : n(_n) {
        adj.resize(n);
        parent.resize(n);
        depth.resize(n);
        heavy.assign(n, -1);
        head.resize(n);
        pos.resize(n);
        subsize.resize(n);
        vals.resize(n);
        base.resize(n);
        cur_pos = 0;
        seg = nullptr;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void updateNode(int v, char c) {
        vals[v] = c;
        seg->update(1, 0, n - 1, pos[v], c);
    }

    int dfs(int v, int p) {
        parent[v] = p;
        subsize[v] = 1;
        int maxSize = 0;
        for (int u : adj[v]) {
            if (u == p) continue;
            depth[u] = depth[v] + 1;
            int sz = dfs(u, v);
            subsize[v] += sz;
            if (sz > maxSize) {
                maxSize = sz;
                heavy[v] = u;
            }
        }
        return subsize[v];
    }

    void decompose(int v, int h) {
        head[v] = h;
        pos[v] = cur_pos;
        base[cur_pos++] = vals[v];
        if (heavy[v] != -1) decompose(heavy[v], h);
        for (int u : adj[v]) {
            if (u == parent[v] || u == heavy[v]) continue;
            decompose(u, u);
        }
    }

    void build(int root = 0) {
        cur_pos = 0;
        dfs(root, -1);
        decompose(root, root);
        seg = new SegTree(n);
        seg->build(base, 1, 0, n - 1);
    }

    int queryPath(int u, int v) {
        int res = INT_MIN;
        // we are performing this operation till both u and v belong to the same chain
        while (head[u] != head[v]) {
            
            // we are swapping the node and chosing the node that is deeper in tree
            if (depth[head[u]] > depth[head[v]]) swap(u, v);

            // computing the query for whole chain 
            int cur = seg->query(1, 0, n - 1, pos[head[v]], pos[v]);
            
            res = max(res, cur);

            // moving to different chain (parent chain of the head of current chain)
            v = parent[head[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);

        // once they belong to same chain we performed the range query from u to v
        res = max(res, seg->query(1, 0, n - 1, pos[u], pos[v]));
        return res;
    }
};
