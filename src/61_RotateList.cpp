import ListNode;

#include "gtest/gtest.h"
#include <vector>
#include <algorithm>

// Solution class as provided by the user
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        ListNode dummy(-1, head), *curr = &dummy;
        int n = 0;
        while (curr && curr->next) {
            curr = curr->next;
            n++;
        }
        if (n == 0) { return nullptr; }
        k %= n;
        k = n - k; // k now represents the number of nodes in the first segment,
                   // or steps from dummy to reach the new tail.

        ListNode* last = curr; // original tail
        curr = &dummy;         // reset curr to find the new tail

        // move curr to the node that will be the new tail
        while (k--) { curr = curr->next; }
        
        last->next = dummy.next;  // connect original tail to original head
        dummy.next = curr->next;  // new head is the node after the new tail
        curr->next = nullptr;     // new tail points to null

        return dummy.next;
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
class RotateRightTest : public ::testing::Test {
protected:
    Solution sol;
};

TEST_F(RotateRightTest, EmptyList) {
    ListNode* head = nullptr;
    ListNode* result = sol.rotateRight(head, 1);
    EXPECT_EQ(listToVector(result), (std::vector<int>{}));
    deleteList(result);
}

TEST_F(RotateRightTest, SingleNodeAnyK) {
    ListNode* head1 = createList({1});
    ListNode* result1 = sol.rotateRight(head1, 0);
    EXPECT_EQ(listToVector(result1), (std::vector<int>{1}));
    deleteList(result1);

    ListNode* head2 = createList({1});
    ListNode* result2 = sol.rotateRight(head2, 1);
    EXPECT_EQ(listToVector(result2), (std::vector<int>{1}));
    deleteList(result2);

    ListNode* head3 = createList({1});
    ListNode* result3 = sol.rotateRight(head3, 5);
    EXPECT_EQ(listToVector(result3), (std::vector<int>{1}));
    deleteList(result3);
}

TEST_F(RotateRightTest, KIsZero) {
    ListNode* head = createList({1, 2, 3, 4, 5});
    ListNode* result = sol.rotateRight(head, 0);
    EXPECT_EQ(listToVector(result), (std::vector<int>{1, 2, 3, 4, 5}));
    deleteList(result);
}

TEST_F(RotateRightTest, KLessThanLength) {
    ListNode* head = createList({1, 2, 3, 4, 5});
    ListNode* result = sol.rotateRight(head, 2);
    EXPECT_EQ(listToVector(result), (std::vector<int>{4, 5, 1, 2, 3}));
    deleteList(result);
}

TEST_F(RotateRightTest, KEqualsLength) {
    ListNode* head = createList({1, 2, 3, 4, 5});
    ListNode* result = sol.rotateRight(head, 5);
    EXPECT_EQ(listToVector(result), (std::vector<int>{1, 2, 3, 4, 5}));
    deleteList(result);
}

TEST_F(RotateRightTest, KGreaterThanLength) {
    ListNode* head = createList({1, 2, 3, 4, 5});
    ListNode* result = sol.rotateRight(head, 7); // 7 % 5 = 2
    EXPECT_EQ(listToVector(result), (std::vector<int>{4, 5, 1, 2, 3}));
    deleteList(result);
}

TEST_F(RotateRightTest, KIsMultipleOfLength) {
    ListNode* head1 = createList({1, 2, 3});
    ListNode* result1 = sol.rotateRight(head1, 3);
    EXPECT_EQ(listToVector(result1), (std::vector<int>{1, 2, 3}));
    deleteList(result1);

    ListNode* head2 = createList({1, 2, 3});
    ListNode* result2 = sol.rotateRight(head2, 6);
    EXPECT_EQ(listToVector(result2), (std::vector<int>{1, 2, 3}));
    deleteList(result2);
}

TEST_F(RotateRightTest, TwoNodesK1) {
    ListNode* head = createList({1, 2});
    ListNode* result = sol.rotateRight(head, 1);
    EXPECT_EQ(listToVector(result), (std::vector<int>{2, 1}));
    deleteList(result);
}

TEST_F(RotateRightTest, TwoNodesK3) {
    ListNode* head = createList({1, 2});
    ListNode* result = sol.rotateRight(head, 3); // 3 % 2 = 1
    EXPECT_EQ(listToVector(result), (std::vector<int>{2, 1}));
    deleteList(result);
}

TEST_F(RotateRightTest, ExampleFromProblemDescription1) {
    ListNode* head = createList({0, 1, 2});
    ListNode* result = sol.rotateRight(head, 4); // 4 % 3 = 1, expected [2,0,1]
    EXPECT_EQ(listToVector(result), (std::vector<int>{2,0,1}));
    deleteList(result);
}

TEST_F(RotateRightTest, ExampleFromProblemDescription2) {
    ListNode* head = createList({1,2,3});
    ListNode* result = sol.rotateRight(head, 2000000000); // Large k
    // 2000000000 % 3 = (2*10^9) % 3. Sum of digits 2. So 2*10^9 % 3 = 2.
    // Rotate by 2: [2,3,1]
    EXPECT_EQ(listToVector(result), (std::vector<int>{2,3,1}));
    deleteList(result);
}