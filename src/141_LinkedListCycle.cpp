#include <iostream>
#include <vector>
#include <string>

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

// Utility function to run a test case
void runTest(const std::string& testName, const std::vector<int>& values, int pos, bool expected) {
    Solution solution;
    ListNode* head = createLinkedList(values, pos);
    bool result = solution.hasCycle(head);
    
    std::cout << testName << ": ";
    if (result == expected) {
        std::cout << "PASSED" << std::endl;
    } else {
        std::cout << "FAILED (Expected: " << (expected ? "true" : "false") 
                  << ", Got: " << (result ? "true" : "false") << ")" << std::endl;
    }
    
    deleteLinkedList(head);
}

int main() {
    // Test case 1: Empty list
    runTest("Test 1: Empty list", {}, -1, false);
    
    // Test case 2: Single node without cycle
    runTest("Test 2: Single node without cycle", {1}, -1, false);
    
    // Test case 3: Single node with self-cycle
    runTest("Test 3: Single node with self-cycle", {1}, 0, true);
    
    // Test case 4: Two nodes without cycle
    runTest("Test 4: Two nodes without cycle", {1, 2}, -1, false);
    
    // Test case 5: Two nodes with cycle
    runTest("Test 5: Two nodes with cycle", {1, 2}, 0, true);
    
    // Test case 6: Multiple nodes without cycle
    runTest("Test 6: Multiple nodes without cycle", {3, 2, 0, -4}, -1, false);
    
    // Test case 7: Multiple nodes with cycle to first node
    runTest("Test 7: Multiple nodes with cycle to first", {3, 2, 0, -4}, 0, true);
    
    // Test case 8: Multiple nodes with cycle to middle node
    runTest("Test 8: Multiple nodes with cycle to middle", {3, 2, 0, -4}, 1, true);
    
    // Test case 9: Multiple nodes with cycle to last node
    runTest("Test 9: Multiple nodes with cycle to last-1", {3, 2, 0, -4}, 2, true);
    
    // Test case 10: Long list without cycle
    std::vector<int> longList;
    for (int i = 0; i < 10000; i++) {
        longList.push_back(i);
    }
    runTest("Test 10: Long list without cycle", longList, -1, false);
    
    // Test case 11: Long list with cycle to start
    runTest("Test 11: Long list with cycle to start", longList, 0, true);
    
    // Test case 12: Long list with cycle to middle
    runTest("Test 12: Long list with cycle to middle", longList, 5000, true);
    
    return 0;
}