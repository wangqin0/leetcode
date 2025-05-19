#include <gtest/gtest.h>
#include <vector>
#include <unordered_map>

struct Node {
    int val;
    struct Node *next;
    struct Node *random;
    
    Node() : val(0), next(nullptr), random(nullptr) {}
    Node(int x) : val(x), next(nullptr), random(nullptr) {}
    Node(int x, Node* next, Node* random) : val(x), next(next), random(random) {}
};

class Solution {
public:
    Node* copyRandomList(Node* head) {

        // copy node
        Node *curr = head;
        while (curr) {
            curr->next = new Node(curr->val, curr->next, nullptr);

            curr = curr->next->next;
        }

        // copy random
        curr = head;
        while (curr) {
            if (curr->random) { curr->next->random = curr->random->next; }
            curr = curr->next->next;
        }

        // split
        curr = head;
        Node dummy;
        Node *d = &dummy;
        while (curr) {
            d->next = curr->next;
            d = d->next;

            curr->next = curr->next->next;
            curr = curr->next;
        }

        return dummy.next;
    }
};

// Helper function to build a linked list with random pointers
std::vector<Node*> buildLinkedList(const std::vector<int>& values, const std::vector<int>& randomIndices) {
    std::vector<Node*> nodes;
    
    // Create nodes
    for (int val : values) {
        nodes.push_back(new Node(val));
    }
    
    // Connect next pointers
    for (size_t i = 0; i < nodes.size() - 1; i++) {
        nodes[i]->next = nodes[i + 1];
    }
    
    // Set random pointers
    for (size_t i = 0; i < nodes.size(); i++) {
        if (i < randomIndices.size() && randomIndices[i] != -1 && randomIndices[i] < nodes.size()) {
            nodes[i]->random = nodes[randomIndices[i]];
        }
    }
    
    return nodes;
}

// Helper to check if two linked lists with random pointers are equal in structure
bool areLinkedListsEqual(Node* list1, Node* list2, std::unordered_map<Node*, Node*>& mapping) {
    Node* curr1 = list1;
    Node* curr2 = list2;
    
    while (curr1 != nullptr && curr2 != nullptr) {
        // Check value
        if (curr1->val != curr2->val) {
            return false;
        }
        
        // Map original node to copy node
        mapping[curr1] = curr2;
        
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    
    // Both should be null at this point
    return curr1 == nullptr && curr2 == nullptr;
}

// Helper to check if random pointers are correctly copied
bool areRandomPointersCorrect(Node* list1, Node* list2, std::unordered_map<Node*, Node*>& mapping) {
    Node* curr1 = list1;
    Node* curr2 = list2;
    
    while (curr1 != nullptr) {
        if ((curr1->random == nullptr && curr2->random != nullptr) || 
            (curr1->random != nullptr && curr2->random == nullptr)) {
            return false;
        }
        
        if (curr1->random != nullptr && mapping[curr1->random] != curr2->random) {
            return false;
        }
        
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    
    return true;
}

// Helper to clean up the linked list
void cleanupLinkedList(std::vector<Node*>& nodes) {
    for (Node* node : nodes) {
        delete node;
    }
    nodes.clear();
}

// Test cases
TEST(CopyRandomListTest, EmptyList) {
    Solution solution;
    Node* result = solution.copyRandomList(nullptr);
    ASSERT_EQ(result, nullptr);
}

TEST(CopyRandomListTest, SingleNode) {
    std::vector<Node*> nodes = buildLinkedList({1}, {-1});
    
    Solution solution;
    Node* result = solution.copyRandomList(nodes[0]);
    
    // Verify result is not null and different from original
    ASSERT_NE(result, nullptr);
    ASSERT_NE(result, nodes[0]);
    
    // Verify value and pointers
    ASSERT_EQ(result->val, 1);
    ASSERT_EQ(result->next, nullptr);
    ASSERT_EQ(result->random, nullptr);
    
    // Cleanup
    delete result;
    cleanupLinkedList(nodes);
}

TEST(CopyRandomListTest, MultipleNodesWithRandomPointers) {
    // Create a list: 1->2->3->4->5 with various random pointers
    // Random pointers: 1->3, 2->1, 3->5, 4->2, 5->null
    std::vector<Node*> nodes = buildLinkedList({1, 2, 3, 4, 5}, {2, 0, 4, 1, -1});
    
    Solution solution;
    Node* result = solution.copyRandomList(nodes[0]);
    
    // Verify structure and random pointers
    std::unordered_map<Node*, Node*> mapping;
    ASSERT_TRUE(areLinkedListsEqual(nodes[0], result, mapping));
    ASSERT_TRUE(areRandomPointersCorrect(nodes[0], result, mapping));
    
    // Cleanup original list
    cleanupLinkedList(nodes);
    
    // Cleanup result list
    Node* curr = result;
    while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
}

// Main function to run the tests
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
