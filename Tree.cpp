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
