// BFS traversal
queue<TreeNode*> q;
q.push(root);
while (!q.empty()) {
    int n = q.size();
    for (int i = 0; i < n; i++) {
        TreeNode* cur = q.front();
        q.pop();
        // do something
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

// Inorder traversal using stack and pointers
// https://leetcode.com/problems/all-elements-in-two-binary-search-trees/
vector<int> ans;
stack<TreeNode*> st;
TreeNode* cur = root;

while (cur || !st.empty()) {

    // 1. Go as left as possible
    while (cur) {
        st.push(cur);
        cur = cur->left;
    }

    // at this point current is null and top element contains the number we need to process

    // 2. Process node
    cur = st.top();
    st.pop();
    ans.push_back(cur->val);

    // 3. Move to right subtree
    // we do this directly to make sure that if right tree is null then while loop will not run and it will take another element from the stack
    // if we null check the right then cur might still be on the top stack element that is not null, then it will go into left tree repeating the process so we null it intentionally
    cur = cur->right;

    // Right child exists: cur is non-null, so the outer while continues, and Phase 1 dives left into that right subtree.
    // Right child is null: cur = nullptr. The inner while(cur) loop is skipped entirely, and we go straight to st.top() to backtrack up the tree.
}

// morris traversal 
while (true) {
    if (cur != NULL) {
        s.push(cur);
        cur = cur->left;
    }
    else {
        if (s.empty()) break;
        cur = s.top();
        s.pop();
        l.push_back(cur->val);
        cur = cur->right;
    }
}

// Keeping the stack upto a specific node
// https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/
// The general way (like morris traversal) does not give stack path towards desired node.
stack<TreeNode*> s;
auto f = [&] (auto&& self, TreeNode* node) {
    if (!node) return false;
    s.push(node);
    if (node == target) return true;       
    if (self(self, node->left) || self(self, node->right)) return true;
    s.pop();
    return false;
};
f(f, root);

// when calculating views, we can either go for bfs or dfs traversal
// incase of dfs, we use coordinate system and for the cases where two different nodes have same coordinates we look for the order of traversal to make decision

// right view https://leetcode.com/problems/binary-tree-right-side-view/


/////////////////////////////////////////////////// DEBUG ///////////////////////////////////////////////////////////

// stack print of TreeNode while keep it intact

void prt(stack<TreeNode*>& s) {
    if (s.empty()) return;
    TreeNode* x = s.top();
    s.pop();
    cout << x->val << " ";
    prt(s);
    s.push(x);  // restore
}
