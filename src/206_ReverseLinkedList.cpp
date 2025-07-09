#include <iostream>
#include <gtest/gtest.h>

import ListNode;

using namespace std;

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode dummy(-1, nullptr);
        ListNode *curr = &dummy;
        while (head)
        {
            ListNode *next = head->next;
            head->next = dummy.next;
            dummy.next = head;

            head = next;
        }
        return dummy.next;
    }
};

// Helper to build linked list from vector
ListNode* buildList(const std::vector<int>& vals) {
    ListNode* head = nullptr;
    for (auto it = vals.rbegin(); it != vals.rend(); ++it) {
        head = new ListNode(*it, head);
    }
    return head;
}

// Helper to collect list values into vector
std::vector<int> toVector(ListNode* head) {
    std::vector<int> result;
    for (ListNode* p = head; p != nullptr; p = p->next) {
        result.push_back(p->val);
    }
    return result;
}

// Helper to delete list and free memory
void deleteList(ListNode* head) {
    while (head) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

// Test cases
TEST(ReverseListTest, HandlesEmptyList) {
    Solution sol;
    ListNode* head = nullptr;
    EXPECT_EQ(sol.reverseList(head), nullptr);
}

TEST(ReverseListTest, HandlesSingleElement) {
    Solution sol;
    ListNode* head = new ListNode(1);
    ListNode* res = sol.reverseList(head);
    ASSERT_NE(res, nullptr);
    EXPECT_EQ(res->val, 1);
    EXPECT_EQ(res->next, nullptr);
    deleteList(res);
}

TEST(ReverseListTest, HandlesTwoElements) {
    Solution sol;
    ListNode* head = buildList({1, 2});
    ListNode* res = sol.reverseList(head);
    std::vector<int> output = toVector(res);
    EXPECT_EQ(output, std::vector<int>({2, 1}));
    deleteList(res);
}

TEST(ReverseListTest, HandlesMultipleElements) {
    Solution sol;
    ListNode* head = buildList({1, 2, 3, 4, 5});
    ListNode* res = sol.reverseList(head);
    std::vector<int> output = toVector(res);
    EXPECT_EQ(output, std::vector<int>({5, 4, 3, 2, 1}));
    deleteList(res);
}

TEST(ReverseListTest, HandlesPalindrome) {
    Solution sol;
    ListNode* head = buildList({1, 2, 3, 2, 1});
    ListNode* res = sol.reverseList(head);
    std::vector<int> output = toVector(res);
    EXPECT_EQ(output, std::vector<int>({1, 2, 3, 2, 1}));
    deleteList(res);
}

TEST(ReverseListTest, HandlesNegativeValues) {
    Solution sol;
    ListNode* head = buildList({-1, -2, -3});
    ListNode* res = sol.reverseList(head);
    std::vector<int> output = toVector(res);
    EXPECT_EQ(output, std::vector<int>({-3, -2, -1}));
    deleteList(res);
}