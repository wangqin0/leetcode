#include <gtest/gtest.h>
#include <vector>
#include <optional>
#include <queue>

import TreeNode;

using namespace std;

class Solution {
public:
    int ans = 0;

    int pathSum(TreeNode* root, int sum) {
        if (!root) { return 0; }

        dfs(root, sum);
        pathSum(root->left,  sum);
        pathSum(root->right, sum);
        return ans;
    }

    void dfs(TreeNode* root, long sum){
        if (!root) { return; }
        if (root->val == sum) { ans++; }
        dfs(root->left,  sum - root->val);
        dfs(root->right, sum - root->val);
    }
};

// Helper to build a tree from level-order vector (use nullopt for missing nodes)
TreeNode* buildTree(const vector<optional<int>>& vals) {
    if (vals.empty() || !vals[0].has_value()) return nullptr;
    TreeNode* root = new TreeNode(vals[0].value());
    queue<TreeNode*> q;
    q.push(root);
    size_t i = 1;
    while (i < vals.size()) {
        TreeNode* cur = q.front(); q.pop();
        if (i < vals.size() && vals[i].has_value()) {
            cur->left = new TreeNode(vals[i].value());
            q.push(cur->left);
        }
        ++i;
        if (i < vals.size() && vals[i].has_value()) {
            cur->right = new TreeNode(vals[i].value());
            q.push(cur->right);
        }
        ++i;
    }
    return root;
}

void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// --- TESTS ---

TEST(PathSumDFS, EmptyTree) {
    Solution sol;
    EXPECT_EQ(sol.pathSum(nullptr, 5), 0);
}

TEST(PathSumDFS, SingleNodeHit) {
    TreeNode* t = new TreeNode(7);
    Solution sol;
    EXPECT_EQ(sol.pathSum(t, 7), 1);
    deleteTree(t);
}

TEST(PathSumDFS, SingleNodeMiss) {
    TreeNode* t = new TreeNode(7);
    Solution sol;
    EXPECT_EQ(sol.pathSum(t, 5), 0);
    deleteTree(t);
}

TEST(PathSumDFS, StraightLine) {
    // 1 -> 2 -> 3 -> 4 (all right children)
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n2 = new TreeNode(2);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* n4 = new TreeNode(4);
    n1->right = n2; n2->right = n3; n3->right = n4;
    Solution sol;
    // Only one path sums to 6: 1→2→3
    EXPECT_EQ(sol.pathSum(n1, 6), 1);
    deleteTree(n1);
}

TEST(PathSumDFS, NegativeValues) {
    //   -2
    //     \
    //     -3
    TreeNode* root = buildTree({-2, nullopt, -3});
    Solution sol;
    EXPECT_EQ(sol.pathSum(root, -5), 1);
    deleteTree(root);
}

TEST(PathSumDFS, ClassicExample) {
    //      10
    //    /    \
    //   5     -3
    //  / \      \
    // 3   2     11
    /// \   \
    //3 -2   1
    vector<optional<int>> vals = {
        10,
        5,    -3,
        3, 2, nullopt, 11,
        3,-2,nullopt, 1
    };
    TreeNode* root = buildTree(vals);
    Solution sol;
    // Paths summing to 8: 5→3, 5→2→1, 10→-3→11
    EXPECT_EQ(sol.pathSum(root, 8), 3);
    deleteTree(root);
}

TEST(PathSumDFS, AllZeros) {
    //      0
    //    /   \
    //   0     0
    //  / \
    // 0   0
    vector<optional<int>> vals = {0, 0, 0, 0, 0};
    TreeNode* root = buildTree(vals);
    Solution sol;
    // There are 11 downward paths summing to 0 in this tree
    EXPECT_EQ(sol.pathSum(root, 0), 11);
    deleteTree(root);
}