import ListNode;

#include "gtest/gtest.h"
#include <vector>
#include <algorithm> // For potential use with std::vector, not strictly needed by basic helpers

// Solution class as provided by the user
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy(-1, head), *curr = &dummy;
        while (curr && curr->next && curr->next->next) {
            ListNode* anchor = curr->next;

            ListNode* probe = anchor->next;
            bool dup = false;
            while (probe && probe->val == anchor->val) {
                anchor->next = probe->next;
                delete probe;
                probe = anchor->next;

                dup = true;
            }
            if (dup) {
                curr->next = anchor->next;
                delete anchor;
                anchor = curr->next;
            } else {
                curr = curr->next;
            }
        }
        return dummy.next;
    }
};

// Helper function to create a linked list from a vector.
// Assumes 'ListNode' is defined (e.g., via 'import ListNode;')
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

// Helper function to convert a linked list to a vector.
std::vector<int> listToVector(ListNode* head) {
    std::vector<int> vec;
    ListNode* current = head;
    while (current) {
        vec.push_back(current->val);
        current = current->next;
    }
    return vec;
}

// Helper function to delete remaining nodes of a linked list.
void deleteList(ListNode* head) {
    ListNode* current = head;
    while (current) {
        ListNode* node_to_delete = current;
        current = current->next;
        delete node_to_delete;
    }
}

// Test Fixture
class DeleteDuplicatesIITest : public ::testing::Test {
protected:
    Solution sol;
};

TEST_F(DeleteDuplicatesIITest, EmptyList) {
    ListNode* head = nullptr;
    ListNode* result = sol.deleteDuplicates(head);
    EXPECT_EQ(listToVector(result), (std::vector<int>{}));
    deleteList(result);
}

TEST_F(DeleteDuplicatesIITest, SingleNode) {
    ListNode* head = createList({1});
    ListNode* result = sol.deleteDuplicates(head);
    EXPECT_EQ(listToVector(result), (std::vector<int>{1}));
    deleteList(result);
}

TEST_F(DeleteDuplicatesIITest, NoDuplicatesSimple) {
    ListNode* head = createList({1, 2, 3});
    ListNode* result = sol.deleteDuplicates(head);
    EXPECT_EQ(listToVector(result), (std::vector<int>{1, 2, 3}));
    deleteList(result);
}

TEST_F(DeleteDuplicatesIITest, AllNodesAreDuplicatesOfOneValue) {
    ListNode* head = createList({1, 1, 1});
    ListNode* result = sol.deleteDuplicates(head);
    EXPECT_EQ(listToVector(result), (std::vector<int>{}));
    deleteList(result);
}

TEST_F(DeleteDuplicatesIITest, AllNodesAreDuplicatesMultipleValues) {
    ListNode* head = createList({1, 1, 2, 2});
    ListNode* result = sol.deleteDuplicates(head);
    EXPECT_EQ(listToVector(result), (std::vector<int>{}));
    deleteList(result);
}

TEST_F(DeleteDuplicatesIITest, DuplicatesAtBeginning) {
    ListNode* head = createList({1, 1, 2, 3});
    ListNode* result = sol.deleteDuplicates(head);
    EXPECT_EQ(listToVector(result), (std::vector<int>{2, 3}));
    deleteList(result);
}

TEST_F(DeleteDuplicatesIITest, DuplicatesAtEnd) {
    ListNode* head = createList({1, 2, 3, 3});
    ListNode* result = sol.deleteDuplicates(head);
    EXPECT_EQ(listToVector(result), (std::vector<int>{1, 2}));
    deleteList(result);
}

TEST_F(DeleteDuplicatesIITest, DuplicatesInMiddle) {
    ListNode* head = createList({1, 2, 2, 3, 4});
    ListNode* result = sol.deleteDuplicates(head);
    EXPECT_EQ(listToVector(result), (std::vector<int>{1, 3, 4}));
    deleteList(result);
}

TEST_F(DeleteDuplicatesIITest, MixedDuplicatesLeadingToNonEmpty) {
    ListNode* head = createList({1, 1, 1, 2, 3, 3, 4, 5, 5, 5});
    ListNode* result = sol.deleteDuplicates(head);
    EXPECT_EQ(listToVector(result), (std::vector<int>{2, 4}));
    deleteList(result);
}

TEST_F(DeleteDuplicatesIITest, ListBecomesEmptyAfterProcessingTwoSameNodes) {
    ListNode* head = createList({1, 1});
    ListNode* result = sol.deleteDuplicates(head);
    EXPECT_EQ(listToVector(result), (std::vector<int>{}));
    deleteList(result);
}

TEST_F(DeleteDuplicatesIITest, MoreComplexMiddleDuplicates) {
    ListNode* head = createList({1, 2, 3, 3, 4, 4, 5});
    ListNode* result = sol.deleteDuplicates(head);
    EXPECT_EQ(listToVector(result), (std::vector<int>{1, 2, 5}));
    deleteList(result);
}

TEST_F(DeleteDuplicatesIITest, NoDuplicatesLongerList) {
    ListNode* head = createList({1, 2, 3, 4, 5, 6});
    ListNode* result = sol.deleteDuplicates(head);
    EXPECT_EQ(listToVector(result), (std::vector<int>{1, 2, 3, 4, 5, 6}));
    deleteList(result);
}

TEST_F(DeleteDuplicatesIITest, SequenceOfThreeThenUnique) {
    ListNode* head = createList({1,1,1,2});
    ListNode* result = sol.deleteDuplicates(head);
    EXPECT_EQ(listToVector(result), (std::vector<int>{2}));
    deleteList(result);
}

TEST_F(DeleteDuplicatesIITest, UniqueThenSequenceOfThree) {
    ListNode* head = createList({1,2,2,2});
    ListNode* result = sol.deleteDuplicates(head);
    EXPECT_EQ(listToVector(result), (std::vector<int>{1}));
    deleteList(result);
}

TEST_F(DeleteDuplicatesIITest, TwoUniqueNodesLoopEdgeCase) {
    ListNode* head = createList({1, 2});
    ListNode* result = sol.deleteDuplicates(head);
    EXPECT_EQ(listToVector(result), (std::vector<int>{1, 2}));
    deleteList(result);
}