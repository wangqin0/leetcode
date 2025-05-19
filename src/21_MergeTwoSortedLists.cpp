#include <iostream>
#include <vector>
#include <gtest/gtest.h>

import ListNode;

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy;
        ListNode* l = &dummy;

        while (l1 && l2) {
            if (l1->val < l2->val) {
                l->next = l1;
                l1 = l1->next;
            } else {
                l->next = l2;
                l2 = l2->next;
            }
            l = l->next;
        }
        if (l1) {
            l->next = l1;
        } else {
            l->next = l2;
        }
        
        return dummy.next;
    }
};

// Helper function to create a linked list from a vector
ListNode* createLinkedList(const std::vector<int>& nums) {
    ListNode dummy;
    ListNode* current = &dummy;
    
    for (int num : nums) {
        current->next = new ListNode(num);
        current = current->next;
    }
    
    return dummy.next;
}

// Helper function to compare two linked lists
bool areEqual(ListNode* l1, ListNode* l2) {
    while (l1 && l2) {
        if (l1->val != l2->val) return false;
        l1 = l1->next;
        l2 = l2->next;
    }
    return !l1 && !l2; // Both should be null
}

// Helper function to free memory
void freeList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

class MergeTwoSortedListsTest : public ::testing::Test {
protected:
    Solution solution;
    
    void TearDown() override {
        // Clean up is handled in each test
    }
};

TEST_F(MergeTwoSortedListsTest, BasicMerge) {
    // [1,2,4] + [1,3,4] = [1,1,2,3,4,4]
    ListNode* l1 = createLinkedList({1, 2, 4});
    ListNode* l2 = createLinkedList({1, 3, 4});
    ListNode* expected = createLinkedList({1, 1, 2, 3, 4, 4});
    
    ListNode* result = solution.mergeTwoLists(l1, l2);
    
    EXPECT_TRUE(areEqual(result, expected));
    
    freeList(result);
    freeList(expected);
}

TEST_F(MergeTwoSortedListsTest, FirstListEmpty) {
    ListNode* l1 = nullptr;
    ListNode* l2 = createLinkedList({1, 3, 4});
    ListNode* expected = createLinkedList({1, 3, 4});
    
    ListNode* result = solution.mergeTwoLists(l1, l2);
    
    EXPECT_TRUE(areEqual(result, expected));
    
    freeList(result);
    freeList(expected);
}

TEST_F(MergeTwoSortedListsTest, SecondListEmpty) {
    ListNode* l1 = createLinkedList({1, 2, 4});
    ListNode* l2 = nullptr;
    ListNode* expected = createLinkedList({1, 2, 4});
    
    ListNode* result = solution.mergeTwoLists(l1, l2);
    
    EXPECT_TRUE(areEqual(result, expected));
    
    freeList(result);
    freeList(expected);
}

TEST_F(MergeTwoSortedListsTest, BothListsEmpty) {
    ListNode* l1 = nullptr;
    ListNode* l2 = nullptr;
    
    ListNode* result = solution.mergeTwoLists(l1, l2);
    
    EXPECT_EQ(result, nullptr);
}

TEST_F(MergeTwoSortedListsTest, DifferentLengthLists) {
    ListNode* l1 = createLinkedList({1, 3, 5, 7, 9});
    ListNode* l2 = createLinkedList({2, 4, 6});
    ListNode* expected = createLinkedList({1, 2, 3, 4, 5, 6, 7, 9});
    
    ListNode* result = solution.mergeTwoLists(l1, l2);
    
    EXPECT_TRUE(areEqual(result, expected));
    
    freeList(result);
    freeList(expected);
}
