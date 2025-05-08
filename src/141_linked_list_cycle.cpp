#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() = default;
    ListNode(int x) : val(x), next(nullptr) {}
};

int main() {
    ListNode n;
    std::cout << "complete\n";
    return 0;
}
