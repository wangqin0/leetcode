#include <iostream>
#include <vector>
#include <string>
#include <gtest/gtest.h>

import ListNode;

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) { return true; }
        }
        return false;
    }
};

// Helper function to create a linked list from a vector
ListNode* createLinkedList(const std::vector<int>& values, int pos = -1) {
    if (values.empty()) return nullptr;

    std::vector<ListNode*> nodes;
    for (int val : values) {
        nodes.push_back(new ListNode(val));
    }
    
    for (size_t i = 0; i < nodes.size() - 1; i++) {
        nodes[i]->next = nodes[i + 1];
    }
    
    // Create cycle if pos is valid
    if (pos >= 0 && pos < (int)nodes.size()) {
        nodes.back()->next = nodes[pos];
    }
    
    return nodes[0];
}

// Helper function to clean up memory of a linked list
void deleteLinkedList(ListNode* head) {
    if (!head) return;
    
    // If there's a cycle, break it first
    ListNode* slow = head;
    ListNode* fast = head;
    bool hasCycle = false;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            hasCycle = true;
            break;
        }
    }
    
    if (hasCycle) {
        // Break the cycle
        ListNode* entry = head;
        while (entry != slow) {
            entry = entry->next;
            slow = slow->next;
        }
        
        // Find the node pointing to entry
        ListNode* temp = entry;
        while (temp->next != entry) {
            temp = temp->next;
        }
        temp->next = nullptr;
    }
    
    // Now free memory
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

class LinkedListCycleTest : public ::testing::Test {
protected:
    Solution solution;
};

TEST_F(LinkedListCycleTest, EmptyList) {
    // Test case 1: Empty list
    ListNode* head = nullptr;
    EXPECT_FALSE(solution.hasCycle(head));
}

TEST_F(LinkedListCycleTest, SingleNodeNoCycle) {
    // Test case 2: Single node without cycle
    ListNode* head = createLinkedList({1}, -1);
    EXPECT_FALSE(solution.hasCycle(head));
    deleteLinkedList(head);
}

TEST_F(LinkedListCycleTest, SingleNodeWithSelfCycle) {
    // Test case 3: Single node with self-cycle
    ListNode* head = createLinkedList({1}, 0);
    EXPECT_TRUE(solution.hasCycle(head));
    deleteLinkedList(head);
}

TEST_F(LinkedListCycleTest, TwoNodesNoCycle) {
    // Test case 4: Two nodes without cycle
    ListNode* head = createLinkedList({1, 2}, -1);
    EXPECT_FALSE(solution.hasCycle(head));
    deleteLinkedList(head);
}

TEST_F(LinkedListCycleTest, TwoNodesWithCycle) {
    // Test case 5: Two nodes with cycle
    ListNode* head = createLinkedList({1, 2}, 0);
    EXPECT_TRUE(solution.hasCycle(head));
    deleteLinkedList(head);
}

TEST_F(LinkedListCycleTest, MultipleNodesNoCycle) {
    // Test case 6: Multiple nodes without cycle
    ListNode* head = createLinkedList({3, 2, 0, -4}, -1);
    EXPECT_FALSE(solution.hasCycle(head));
    deleteLinkedList(head);
}

TEST_F(LinkedListCycleTest, MultipleNodesWithCycleToFirst) {
    // Test case 7: Multiple nodes with cycle to first node
    ListNode* head = createLinkedList({3, 2, 0, -4}, 0);
    EXPECT_TRUE(solution.hasCycle(head));
    deleteLinkedList(head);
}

TEST_F(LinkedListCycleTest, MultipleNodesWithCycleToMiddle) {
    // Test case 8: Multiple nodes with cycle to middle node
    ListNode* head = createLinkedList({3, 2, 0, -4}, 1);
    EXPECT_TRUE(solution.hasCycle(head));
    deleteLinkedList(head);
}

TEST_F(LinkedListCycleTest, MultipleNodesWithCycleToLast) {
    // Test case 9: Multiple nodes with cycle to last-1 node
    ListNode* head = createLinkedList({3, 2, 0, -4}, 2);
    EXPECT_TRUE(solution.hasCycle(head));
    deleteLinkedList(head);
}

TEST_F(LinkedListCycleTest, LongListNoCycle) {
    // Test case 10: Long list without cycle
    std::vector<int> longList;
    for (int i = 0; i < 1000; i++) {  // Reduced from 10000 for performance
        longList.push_back(i);
    }
    ListNode* head = createLinkedList(longList, -1);
    EXPECT_FALSE(solution.hasCycle(head));
    deleteLinkedList(head);
}

TEST_F(LinkedListCycleTest, LongListWithCycleToStart) {
    // Test case 11: Long list with cycle to start
    std::vector<int> longList;
    for (int i = 0; i < 1000; i++) {  // Reduced from 10000 for performance
        longList.push_back(i);
    }
    ListNode* head = createLinkedList(longList, 0);
    EXPECT_TRUE(solution.hasCycle(head));
    deleteLinkedList(head);
}

TEST_F(LinkedListCycleTest, LongListWithCycleToMiddle) {
    // Test case 12: Long list with cycle to middle
    std::vector<int> longList;
    for (int i = 0; i < 1000; i++) {  // Reduced from 10000 for performance
        longList.push_back(i);
    }
    ListNode* head = createLinkedList(longList, 500);
    EXPECT_TRUE(solution.hasCycle(head));
    deleteLinkedList(head);
}