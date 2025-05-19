export module ListNode;

export struct ListNode {
    int val = 0;
    ListNode *next = nullptr;

    ListNode(int val = 0, ListNode* next = nullptr) : val(val), next(next) {}
};
