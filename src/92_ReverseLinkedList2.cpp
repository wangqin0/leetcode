#include "gtest/gtest.h"
#include <vector>
#include <iostream> // For potential debugging, not strictly needed for gtest

// Definition of ListNode
// Assuming 'import ListNode;' from your code means something like this.
// If ListNode is in a separate header, you'd #include "ListNode.h"
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Your Solution class (comments removed from within this class)
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        int begin = left;
        int end_exclusive = right + 1;

        if (!head || begin >= end_exclusive || left > right) {
            return head;
        }

        ListNode dummy(-1, head);
        ListNode* curr = &dummy;
        
        for (int i = 0; i < begin - 1; i++) {
            if (!curr->next) return head;
            curr = curr->next;
        }

        ListNode* reversed_segment_tail = curr->next;
        ListNode* probe = curr->next;

        int num_nodes_in_segment = right - left + 1;
        
        for (int i = 0; i < num_nodes_in_segment; ++i) {
            if (!probe) break;
            ListNode* next_node_to_process = probe->next;

            probe->next = curr->next;
            curr->next = probe;

            probe = next_node_to_process;
        }

        if (reversed_segment_tail) {
            reversed_segment_tail->next = probe;
        }
        
        return dummy.next;
    }
};


// Helper function to create a list from a vector
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

// Helper function to convert list to vector
std::vector<int> listToVector(ListNode* head) {
    std::vector<int> vec;
    ListNode* current = head;
    while (current != nullptr) {
        vec.push_back(current->val);
        current = current->next;
    }
    return vec;
}

// Helper function to delete a list
void deleteList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* next_node = current->next;
        delete current;
        current = next_node;
    }
}

// Test fixture for common setup/teardown
class ReverseBetweenTest : public ::testing::Test {
protected:
    Solution sol;
    ListNode* head = nullptr; // Test case will set this up

    // Per-test clean-up
    void TearDown() override {
        deleteList(head);
        head = nullptr; // Important to reset for the next test
    }
};

// Test Cases

TEST_F(ReverseBetweenTest, EmptyList) {
    head = nullptr; // Already null by default, but explicit for clarity
    ListNode* result = sol.reverseBetween(head, 1, 1);
    EXPECT_EQ(result, nullptr);
    // head is still nullptr, TearDown handles it
}

TEST_F(ReverseBetweenTest, SingleNodeList) {
    head = createList({10});
    ListNode* result = sol.reverseBetween(head, 1, 1);
    std::vector<int> expected_vec = {10};
    EXPECT_EQ(listToVector(result), expected_vec);
    head = result; // The ownership of the list nodes is passed to 'head' for TearDown
}

TEST_F(ReverseBetweenTest, LeftEqualsRight) {
    head = createList({1, 2, 3, 4, 5});
    ListNode* result = sol.reverseBetween(head, 2, 2); // Reverse segment of 1 node
    std::vector<int> expected_vec = {1, 2, 3, 4, 5};
    EXPECT_EQ(listToVector(result), expected_vec);
    head = result;
}

TEST_F(ReverseBetweenTest, ReverseEntireList) {
    head = createList({1, 2, 3, 4, 5});
    ListNode* result = sol.reverseBetween(head, 1, 5);
    std::vector<int> expected_vec = {5, 4, 3, 2, 1};
    EXPECT_EQ(listToVector(result), expected_vec);
    head = result;
}

TEST_F(ReverseBetweenTest, ReverseEntireTwoNodeList) {
    head = createList({1, 2});
    ListNode* result = sol.reverseBetween(head, 1, 2);
    std::vector<int> expected_vec = {2, 1};
    EXPECT_EQ(listToVector(result), expected_vec);
    head = result;
}

TEST_F(ReverseBetweenTest, ReversePrefix) {
    head = createList({1, 2, 3, 4, 5});
    ListNode* result = sol.reverseBetween(head, 1, 3); // Reverse 1,2,3 -> 3,2,1
    std::vector<int> expected_vec = {3, 2, 1, 4, 5};
    EXPECT_EQ(listToVector(result), expected_vec);
    head = result;
}

TEST_F(ReverseBetweenTest, ReverseSuffix) {
    head = createList({1, 2, 3, 4, 5});
    ListNode* result = sol.reverseBetween(head, 3, 5); // Reverse 3,4,5 -> 5,4,3
    std::vector<int> expected_vec = {1, 2, 5, 4, 3};
    EXPECT_EQ(listToVector(result), expected_vec);
    head = result;
}

TEST_F(ReverseBetweenTest, ReverseMiddle) {
    head = createList({1, 2, 3, 4, 5, 6, 7});
    ListNode* result = sol.reverseBetween(head, 3, 5); // Reverse 3,4,5 -> 5,4,3
    std::vector<int> expected_vec = {1, 2, 5, 4, 3, 6, 7};
    EXPECT_EQ(listToVector(result), expected_vec);
    head = result;
}

TEST_F(ReverseBetweenTest, LeftGreaterThanActualRight) {
    // Test case where original 'left > right' (e.g. reverseBetween(head, 3, 1))
    head = createList({1, 2, 3, 4, 5});
    ListNode* result = sol.reverseBetween(head, 3, 1);
    std::vector<int> expected_vec = {1, 2, 3, 4, 5}; // Should be unchanged
    EXPECT_EQ(listToVector(result), expected_vec);
    head = result; // Result is original head in this case
}

TEST_F(ReverseBetweenTest, LeftEqualsOneAndRightEqualsOneOnLongerList) {
    head = createList({1, 2, 3});
    ListNode* result = sol.reverseBetween(head, 1, 1);
    std::vector<int> expected_vec = {1, 2, 3};
    EXPECT_EQ(listToVector(result), expected_vec);
    head = result;
}

TEST_F(ReverseBetweenTest, ReverseTwoElementsInMiddle) {
    head = createList({1, 2, 3, 4, 5});
    ListNode* result = sol.reverseBetween(head, 2, 3); // Reverse 2,3 -> 3,2
    std::vector<int> expected_vec = {1, 3, 2, 4, 5};
    EXPECT_EQ(listToVector(result), expected_vec);
    head = result;
}

TEST_F(ReverseBetweenTest, ReverseTwoElementsAtStart) {
    head = createList({1, 2, 3, 4, 5});
    ListNode* result = sol.reverseBetween(head, 1, 2); // Reverse 1,2 -> 2,1
    std::vector<int> expected_vec = {2, 1, 3, 4, 5};
    EXPECT_EQ(listToVector(result), expected_vec);
    head = result;
}

TEST_F(ReverseBetweenTest, ReverseTwoElementsAtEnd) {
    head = createList({1, 2, 3, 4, 5});
    ListNode* result = sol.reverseBetween(head, 4, 5); // Reverse 4,5 -> 5,4
    std::vector<int> expected_vec = {1, 2, 3, 5, 4};
    EXPECT_EQ(listToVector(result), expected_vec);
    head = result;
}

TEST_F(ReverseBetweenTest, ListWithDuplicatesSubsegmentIsPalindrome) {
    // Reversing a subsegment that is a palindrome of values
    head = createList({1, 2, 3, 2, 4, 5}); // Reverse 2,3,2 (indices 2,3,4)
    ListNode* result = sol.reverseBetween(head, 2, 4); // Segment (2 -> 3 -> 2) reversed is (2 -> 3 -> 2)
    std::vector<int> expected_vec = {1, 2, 3, 2, 4, 5};
    EXPECT_EQ(listToVector(result), expected_vec);
    head = result;
}

TEST_F(ReverseBetweenTest, ListWithDuplicatesGeneral) {
    // Reversing a subsegment with duplicates that results in a changed order
    head = createList({1, 2, 3, 4, 2, 5}); // Reverse nodes at indices 2,3,4,5 (values 2,3,4,2)
                                       // Original: 1 -> [2 -> 3 -> 4 -> 2_b] -> 5
                                       // Reversed: 1 -> [2_b -> 4 -> 3 -> 2] -> 5
    ListNode* result = sol.reverseBetween(head, 2, 5);
    std::vector<int> expected_vec = {1, 2, 4, 3, 2, 5};
    EXPECT_EQ(listToVector(result), expected_vec);
    head = result;
}

TEST_F(ReverseBetweenTest, LeftOutOfLowerBoundValidRange) {
    // This test ensures robustness for left values that might be too large.
    // The safety check `if (!curr->next) return head;` handles this.
    head = createList({1,2,3});
    ListNode* result = sol.reverseBetween(head, 5, 6); // left is out of bounds (too large)
    std::vector<int> expected_oob = {1,2,3};
    EXPECT_EQ(listToVector(result), expected_oob); // Should be unchanged
    head = result;
}

TEST_F(ReverseBetweenTest, RightOutOfUpperBound) {
    // This test ensures robustness for right values that extend beyond the list.
    // The safety check `if (!probe) break;` handles this.
    head = createList({1,2,3,4,5});
    ListNode* result = sol.reverseBetween(head, 3, 7); // right is out of bounds
    // Expected behavior: reverses from node 3 to the end of the list.
    // Segment to reverse: 3 -> 4 -> 5. Reversed: 5 -> 4 -> 3.
    std::vector<int> expected_vec = {1, 2, 5, 4, 3};
    EXPECT_EQ(listToVector(result), expected_vec);
    head = result;
}
