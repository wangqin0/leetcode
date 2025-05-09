#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// Solution

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int anchor = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {
                nums[anchor++] = nums[i];
            }
        }
        return anchor;
    }
};


// Intuition

/*

Copy when neccessary.

*/


// Test

int main() {
    Solution sol;

    // Test Case 1: Basic case
    vector<int> nums1 = {3, 2, 2, 3};
    int val1 = 3;
    int expected_k1 = 2;
    vector<int> expected_nums1 = {2, 2}; // The first k elements should match this
    int k1 = sol.removeElement(nums1, val1);
    assert(k1 == expected_k1);
    for (int i = 0; i < k1; ++i) {
        assert(nums1[i] == expected_nums1[i]);
    }
    cout << "Test Case 1 Passed" << endl;

    // Test Case 2: No elements to remove
    vector<int> nums2 = {0, 1, 2, 2, 3, 0, 4, 2};
    int val2 = 5;
    int expected_k2 = 8;
    vector<int> expected_nums2 = {0, 1, 2, 2, 3, 0, 4, 2};
    int k2 = sol.removeElement(nums2, val2);
    assert(k2 == expected_k2);
    for (int i = 0; i < k2; ++i) {
        assert(nums2[i] == expected_nums2[i]);
    }
    cout << "Test Case 2 Passed" << endl;

    // Test Case 3: All elements to remove
    vector<int> nums3 = {7, 7, 7, 7};
    int val3 = 7;
    int expected_k3 = 0;
    vector<int> expected_nums3 = {};
    int k3 = sol.removeElement(nums3, val3);
    assert(k3 == expected_k3);
    // No elements to check in expected_nums3
    cout << "Test Case 3 Passed" << endl;

    // Test Case 4: Empty vector
    vector<int> nums4 = {};
    int val4 = 0;
    int expected_k4 = 0;
    vector<int> expected_nums4 = {};
    int k4 = sol.removeElement(nums4, val4);
    assert(k4 == expected_k4);
    // No elements to check in expected_nums4
    cout << "Test Case 4 Passed" << endl;

    cout << "All basic tests passed!" << endl;

    return 0; // Indicate successful execution

}
