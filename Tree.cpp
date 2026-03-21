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
vector<int> ans;
stack<TreeNode*> st;
TreeNode* cur = root;

while (cur || !st.empty()) {

    // 1. Go as left as possible
    while (cur) {
        st.push(cur);
        cur = cur->left;
    }

    // 2. Process node
    cur = st.top();
    st.pop();
    ans.push_back(cur->val);

    // 3. Move to right subtree
    cur = cur->right;
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
