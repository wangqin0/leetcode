#include <vector>
#include <iostream>
#include <format>
#include <cassert> // Include for assertions

using namespace std;


// Solution

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i1 = m - 1, i2 = n - 1, i = m + n - 1;
        while (i1 >= 0 && i2 >= 0) {
            if (nums1[i1] > nums2[i2]) {
                nums1[i--] = nums1[i1--]; 
            } else {
                nums1[i--] = nums2[i2--]; 
            }
        }
        while (i2 >= 0) {
            nums1[i--] = nums2[i2--];
        }
    }
};

// Intuition

/*

- Use the space at the end of nums1

*/

// Test

// Helper function to print vectors for debugging (optional)
void printVector(const string& name, const vector<int>& vec) {
    cout << name << ": [";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << (i == vec.size() - 1 ? "" : ", ");
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;

    // Test Case 1: Basic merge
    vector<int> nums1_1 = {1, 2, 3, 0, 0, 0};
    int m1 = 3;
    vector<int> nums2_1 = {2, 5, 6};
    int n1 = 3;
    vector<int> expected1 = {1, 2, 2, 3, 5, 6};
    sol.merge(nums1_1, m1, nums2_1, n1);
    assert(nums1_1 == expected1);
    cout << "Test Case 1 Passed" << endl;

    // Test Case 2: nums2 is empty
    vector<int> nums1_2 = {1};
    int m2 = 1;
    vector<int> nums2_2 = {};
    int n2 = 0;
    vector<int> expected2 = {1};
    sol.merge(nums1_2, m2, nums2_2, n2);
    assert(nums1_2 == expected2);
    cout << "Test Case 2 Passed" << endl;

    // Test Case 3: nums1 is conceptually empty (m=0)
    vector<int> nums1_3 = {0};
    int m3 = 0;
    vector<int> nums2_3 = {1};
    int n3 = 1;
    vector<int> expected3 = {1};
    sol.merge(nums1_3, m3, nums2_3, n3);
    assert(nums1_3 == expected3);
    cout << "Test Case 3 Passed" << endl;

    // Test Case 4: All elements of nums2 are smaller
    vector<int> nums1_4 = {4, 5, 6, 0, 0, 0};
    int m4 = 3;
    vector<int> nums2_4 = {1, 2, 3};
    int n4 = 3;
    vector<int> expected4 = {1, 2, 3, 4, 5, 6};
    sol.merge(nums1_4, m4, nums2_4, n4);
    assert(nums1_4 == expected4);
    cout << "Test Case 4 Passed" << endl;

    cout << "All basic tests passed!" << endl;

    return 0; // Indicate successful execution
}