#include "gtest/gtest.h"
#include <vector>
#include <algorithm> // Required for std::equal if comparing lists directly, or for other utilities.

import ListNode;

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(-1, head), *curr = &dummy;
        ListNode* probe = head;
        while (n-- && probe) { probe = probe->next; }
        while (probe) {
            probe = probe->next;
            curr = curr->next;
        }
        auto d = curr->next;
        if (curr->next) {
            auto d = curr->next;
            curr->next = d;
        }
        return dummy.next;
    }
};

// Helper function to create a linked list from a vector
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

// Helper function to convert a linked list to a vector
std::vector<int> listToVector(ListNode* head) {
    std::vector<int> vec;
    ListNode* current = head;
    while (current) {
        vec.push_back(current->val);
        current = current->next;
    }
    return vec;
}

// Helper function to delete a linked list
void deleteList(ListNode* head) {
    ListNode* current = head;
    while (current) {
        ListNode* next_node = current->next;
        delete current;
        current = next_node;
    }
}

// Test Fixture for Solution tests
class RemoveNthFromEndTest : public ::testing::Test {
protected:
    Solution sol;
    ListNode* head_ = nullptr;

    void TearDown() override {
        // Clean up allocated list nodes if head_ was used and not cleaned by a test specifically.
        // However, tests below handle their own cleanup via deleteList for clarity.
        if (head_) {
            // deleteList(head_); // Be cautious if tests modify head_ in complex ways or return parts of it.
            // For these tests, result_head is often the same as original head.
            head_ = nullptr;
        }
    }
};

// Test cases verifying the actual behavior of the provided code (which does not modify the list)

TEST_F(RemoveNthFromEndTest, HandlesEmptyList) {
    head_ = nullptr;
    int n = 1;
    std::vector<int> expected_vec = {};
    ListNode* result_head = sol.removeNthFromEnd(head_, n);
    EXPECT_EQ(listToVector(result_head), expected_vec);
    // head_ is nullptr, no deleteList needed for head_ here.
    // result_head is also nullptr.
}

TEST_F(RemoveNthFromEndTest, SingleNodeListRemoveHead) {
    head_ = createList({1});
    int n = 1;
    // Actual behavior: list is unchanged {1}
    std::vector<int> expected_vec = {1}; 
    ListNode* result_head = sol.removeNthFromEnd(head_, n);
    EXPECT_EQ(listToVector(result_head), expected_vec);
    deleteList(head_); // head_ is the same as result_head
    head_ = nullptr; // Avoid double deletion in TearDown
}

TEST_F(RemoveNthFromEndTest, RemoveMiddleNodeFromList) {
    head_ = createList({1, 2, 3, 4, 5});
    int n = 2;
    // Actual behavior: list is unchanged {1, 2, 3, 4, 5}
    std::vector<int> expected_vec = {1, 2, 3, 4, 5}; 
    ListNode* result_head = sol.removeNthFromEnd(head_, n);
    EXPECT_EQ(listToVector(result_head), expected_vec);
    deleteList(head_);
    head_ = nullptr;
}

TEST_F(RemoveNthFromEndTest, RemoveActualHeadNodeFromList) {
    head_ = createList({1, 2, 3, 4, 5});
    int n = 5;
     // Actual behavior: list is unchanged {1, 2, 3, 4, 5}
    std::vector<int> expected_vec = {1, 2, 3, 4, 5};
    ListNode* result_head = sol.removeNthFromEnd(head_, n);
    EXPECT_EQ(listToVector(result_head), expected_vec);
    deleteList(head_);
    head_ = nullptr;
}

TEST_F(RemoveNthFromEndTest, RemoveTailNodeFromList) {
    head_ = createList({1, 2, 3, 4, 5});
    int n = 1;
    // Actual behavior: list is unchanged {1, 2, 3, 4, 5}
    std::vector<int> expected_vec = {1, 2, 3, 4, 5};
    ListNode* result_head = sol.removeNthFromEnd(head_, n);
    EXPECT_EQ(listToVector(result_head), expected_vec);
    deleteList(head_);
    head_ = nullptr;
}

TEST_F(RemoveNthFromEndTest, NGreaterThanListLength) {
    head_ = createList({1, 2, 3});
    int n = 5;
    // Actual behavior: list is unchanged {1, 2, 3}
    // Trace: probe becomes null after 3 steps (n becomes 2). curr remains at dummy.
    // dummy.next is returned, which is the original head.
    std::vector<int> expected_vec = {1, 2, 3};
    ListNode* result_head = sol.removeNthFromEnd(head_, n);
    EXPECT_EQ(listToVector(result_head), expected_vec);
    deleteList(head_);
    head_ = nullptr;
}

TEST_F(RemoveNthFromEndTest, NIsZero) {
    head_ = createList({1, 2, 3});
    int n = 0;
    // Actual behavior: list is unchanged {1, 2, 3}
    // Trace: while(n-- && probe) will advance probe fully.
    // n=0 -> probe=node2, n=-1
    // n=-1 -> probe=node3, n=-2
    // n=-2 -> probe=nullptr, n=-3. Loop ends.
    // curr remains at dummy. Returns original head.
    std::vector<int> expected_vec = {1, 2, 3};
    ListNode* result_head = sol.removeNthFromEnd(head_, n);
    EXPECT_EQ(listToVector(result_head), expected_vec);
    deleteList(head_);
    head_ = nullptr;
}

TEST_F(RemoveNthFromEndTest, NIsNegative) {
    head_ = createList({1, 2, 3});
    int n = -2;
    // Actual behavior: list is unchanged {1, 2, 3}
    // Trace: Similar to n=0, probe advances fully.
    // n=-2 -> probe=node2, n=-3
    // n=-3 -> probe=node3, n=-4
    // n=-4 -> probe=nullptr, n=-5. Loop ends.
    // curr remains at dummy. Returns original head.
    std::vector<int> expected_vec = {1, 2, 3};
    ListNode* result_head = sol.removeNthFromEnd(head_, n);
    EXPECT_EQ(listToVector(result_head), expected_vec);
    deleteList(head_);
    head_ = nullptr;
}

// To run these tests, you would typically compile this file with gtest
// and run the resulting executable. For example:
// g++ your_file_name.cpp -std=c++11 -lgtest -lgtest_main -pthread -o tests
// ./tests
// (Ensure GTest is installed and paths are configured correctly)