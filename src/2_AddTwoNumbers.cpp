#include <iostream>
#include <vector>
#include <gtest/gtest.h>

import ListNode;

using namespace std;

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy;
        ListNode* l = &dummy;

        int carry = 0;
        while (l1 || l2 || carry) {
            if (l1) { carry += l1->val; l1 = l1->next; }
            if (l2) { carry += l2->val; l2 = l2->next; }

            l->next = new ListNode(carry % 10);
            l = l->next;
            carry /= 10;
        }

        return dummy.next;
    }
};

// Helper function to create a linked list from a vector
ListNode* createLinkedList(const vector<int>& nums) {
    ListNode dummy;
    ListNode* current = &dummy;
    
    for (int num : nums) {
        current->next = new ListNode(num);
        current = current->next;
    }
    
    return dummy.next;
}

// Helper function to print a linked list
void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
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

class AddTwoNumbersTest : public ::testing::Test {
protected:
    Solution solution;
    
    void TearDown() override {
        // Clean up is handled in each test
    }
};

TEST_F(AddTwoNumbersTest, BasicAddition) {
    // 2->4->3 (342) + 5->6->4 (465) = 7->0->8 (807)
    ListNode* l1 = createLinkedList({2, 4, 3});
    ListNode* l2 = createLinkedList({5, 6, 4});
    ListNode* expected = createLinkedList({7, 0, 8});
    
    ListNode* result = solution.addTwoNumbers(l1, l2);
    
    EXPECT_TRUE(areEqual(result, expected));
    
    freeList(l1);
    freeList(l2);
    freeList(result);
    freeList(expected);
}

TEST_F(AddTwoNumbersTest, DifferentLengthLists) {
    // 9->9 (99) + 1 (1) = 0->0->1 (100)
    ListNode* l1 = createLinkedList({9, 9});
    ListNode* l2 = createLinkedList({1});
    ListNode* expected = createLinkedList({0, 0, 1});
    
    ListNode* result = solution.addTwoNumbers(l1, l2);
    
    EXPECT_TRUE(areEqual(result, expected));
    
    freeList(l1);
    freeList(l2);
    freeList(result);
    freeList(expected);
}

TEST_F(AddTwoNumbersTest, ZeroValues) {
    // 0 (0) + 0 (0) = 0 (0)
    ListNode* l1 = createLinkedList({0});
    ListNode* l2 = createLinkedList({0});
    ListNode* expected = createLinkedList({0});
    
    ListNode* result = solution.addTwoNumbers(l1, l2);
    
    EXPECT_TRUE(areEqual(result, expected));
    
    freeList(l1);
    freeList(l2);
    freeList(result);
    freeList(expected);
}

TEST_F(AddTwoNumbersTest, CarryPropagation) {
    // 9->9->9 (999) + 9->9->9 (999) = 8->9->9->1 (1998)
    ListNode* l1 = createLinkedList({9, 9, 9});
    ListNode* l2 = createLinkedList({9, 9, 9});
    ListNode* expected = createLinkedList({8, 9, 9, 1});
    
    ListNode* result = solution.addTwoNumbers(l1, l2);
    
    EXPECT_TRUE(areEqual(result, expected));
    
    freeList(l1);
    freeList(l2);
    freeList(result);
    freeList(expected);
}

TEST_F(AddTwoNumbersTest, OneEmptyList) {
    ListNode* l1 = createLinkedList({1, 2, 3});
    ListNode* l2 = nullptr;
    ListNode* expected = createLinkedList({1, 2, 3});
    
    ListNode* result = solution.addTwoNumbers(l1, l2);
    
    EXPECT_TRUE(areEqual(result, expected));
    
    freeList(l1);
    freeList(result);
    freeList(expected);
}