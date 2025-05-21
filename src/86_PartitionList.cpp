import ListNode;

#include "gtest/gtest.h"
#include <vector>
#include <algorithm>

// Solution class as provided by the user
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode left, *l = &left;
        ListNode right, *r = &right;
        ListNode* curr = head;

        ListNode* l_last = l; // This variable is present in the provided code but unused in its logic
        while (curr) {
            if (curr->val < x) {
                l->next = curr;
                l = l->next;
            } else {
                r->next = curr;
                r = r->next;
            }
            curr = curr->next;
        }
        l->next = right.next;
        r->next = nullptr;
        return left.next;
    }
};

// Helper functions (assuming ListNode is defined via 'import ListNode;')
// and has members: int val; ListNode* next;
// and constructors like ListNode(int val) and ListNode(int val, ListNode* next)
ListNode* createList(const std::vector<int>& vals) {
    if (vals.empty()) {
        return nullptr;
    }
    ListNode* head = new ListNode(vals[0]);
    ListNode* current = head;
    for (size_t i = 1; i < vals.size(); ++i) {
        current->next = new ListNode(vals[i]);
        current = current->next;
    }
    return head;
}

std::vector<int> listToVector(ListNode* head) {
    std::vector<int> vec;
    ListNode* current = head;
    while (current) {
        vec.push_back(current->val);
        current = current->next;
    }
    return vec;
}

void deleteList(ListNode* head) {
    ListNode* current = head;
    while (current) {
        ListNode* node_to_delete = current;
        current = current->next;
        delete node_to_delete;
    }
}

// Test Fixture
class PartitionTest : public ::testing::Test {
protected:
    Solution sol;
};

TEST_F(PartitionTest, EmptyList) {
    ListNode* head = nullptr;
    ListNode* result = sol.partition(head, 0);
    EXPECT_EQ(listToVector(result), (std::vector<int>{}));
    deleteList(result);
}

TEST_F(PartitionTest, SingleNodeLessThanX) {
    ListNode* head = createList({1});
    ListNode* result = sol.partition(head, 2);
    EXPECT_EQ(listToVector(result), (std::vector<int>{1}));
    deleteList(result);
}

TEST_F(PartitionTest, SingleNodeEqualToX) {
    ListNode* head = createList({2});
    ListNode* result = sol.partition(head, 2);
    EXPECT_EQ(listToVector(result), (std::vector<int>{2}));
    deleteList(result);
}

TEST_F(PartitionTest, SingleNodeGreaterThanX) {
    ListNode* head = createList({3});
    ListNode* result = sol.partition(head, 2);
    EXPECT_EQ(listToVector(result), (std::vector<int>{3}));
    deleteList(result);
}

TEST_F(PartitionTest, AllNodesLessThanX) {
    ListNode* head = createList({1, 2, 0});
    ListNode* result = sol.partition(head, 3);
    EXPECT_EQ(listToVector(result), (std::vector<int>{1, 2, 0}));
    deleteList(result);
}

TEST_F(PartitionTest, AllNodesGreaterThanOrEqualToX) {
    ListNode* head = createList({5, 4, 3});
    ListNode* result = sol.partition(head, 3);
    EXPECT_EQ(listToVector(result), (std::vector<int>{5, 4, 3}));
    deleteList(result);
}

TEST_F(PartitionTest, Example1FromLeetcode) {
    ListNode* head = createList({1, 4, 3, 2, 5, 2});
    ListNode* result = sol.partition(head, 3);
    EXPECT_EQ(listToVector(result), (std::vector<int>{1, 2, 2, 4, 3, 5}));
    deleteList(result);
}

TEST_F(PartitionTest, Example2FromLeetcode) {
    ListNode* head = createList({2, 1});
    ListNode* result = sol.partition(head, 2);
    EXPECT_EQ(listToVector(result), (std::vector<int>{1, 2}));
    deleteList(result);
}

TEST_F(PartitionTest, PivotSmallerThanAllElements) {
    ListNode* head = createList({3, 1, 2, 5});
    ListNode* result = sol.partition(head, 0);
    EXPECT_EQ(listToVector(result), (std::vector<int>{3, 1, 2, 5}));
    deleteList(result);
}

TEST_F(PartitionTest, PivotLargerThanAllElements) {
    ListNode* head = createList({3, 1, 2, 5});
    ListNode* result = sol.partition(head, 6);
    EXPECT_EQ(listToVector(result), (std::vector<int>{3, 1, 2, 5}));
    deleteList(result);
}

TEST_F(PartitionTest, AlreadyPartitioned) {
    ListNode* head = createList({1, 2, 4, 5});
    ListNode* result = sol.partition(head, 3);
    EXPECT_EQ(listToVector(result), (std::vector<int>{1, 2, 4, 5}));
    deleteList(result);
}

TEST_F(PartitionTest, ReversePartitioned) {
    ListNode* head = createList({5, 4, 2, 1});
    ListNode* result = sol.partition(head, 3);
    EXPECT_EQ(listToVector(result), (std::vector<int>{2, 1, 5, 4}));
    deleteList(result);
}

TEST_F(PartitionTest, MixedElementsWithPivotValuePresent) {
    ListNode* head = createList({3, 5, 8, 5, 10, 2, 1});
    ListNode* result = sol.partition(head, 5);
    EXPECT_EQ(listToVector(result), (std::vector<int>{3, 2, 1, 5, 8, 5, 10}));
    deleteList(result);
}

TEST_F(PartitionTest, PivotIsMinValueInList) {
    ListNode* head = createList({5, 2, 8, 2, 10, 1});
    ListNode* result = sol.partition(head, 1);
    EXPECT_EQ(listToVector(result), (std::vector<int>{5, 2, 8, 2, 10, 1})); // No elements < 1
    deleteList(result);
}

TEST_F(PartitionTest, PivotIsMaxValueInList) {
    ListNode* head = createList({5, 2, 8, 2, 10, 1});
    ListNode* result = sol.partition(head, 10);
    // Expected: 5->2->8->2->1 (all < 10) then 10
    EXPECT_EQ(listToVector(result), (std::vector<int>{5, 2, 8, 2, 1, 10}));
    deleteList(result);
}