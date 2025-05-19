#include <vector>
#include <iostream>
#include <gtest/gtest.h>

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

class MergeSortedArrayTest : public ::testing::Test {
protected:
    Solution sol;
};

TEST_F(MergeSortedArrayTest, BasicMerge) {
    // Test Case 1: Basic merge
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    int m = 3;
    vector<int> nums2 = {2, 5, 6};
    int n = 3;
    vector<int> expected = {1, 2, 2, 3, 5, 6};
    
    sol.merge(nums1, m, nums2, n);
    
    EXPECT_EQ(nums1, expected);
}

TEST_F(MergeSortedArrayTest, Nums2Empty) {
    // Test Case 2: nums2 is empty
    vector<int> nums1 = {1};
    int m = 1;
    vector<int> nums2 = {};
    int n = 0;
    vector<int> expected = {1};
    
    sol.merge(nums1, m, nums2, n);
    
    EXPECT_EQ(nums1, expected);
}

TEST_F(MergeSortedArrayTest, Nums1ConceptuallyEmpty) {
    // Test Case 3: nums1 is conceptually empty (m=0)
    vector<int> nums1 = {0};
    int m = 0;
    vector<int> nums2 = {1};
    int n = 1;
    vector<int> expected = {1};
    
    sol.merge(nums1, m, nums2, n);
    
    EXPECT_EQ(nums1, expected);
}

TEST_F(MergeSortedArrayTest, AllElementsOfNums2Smaller) {
    // Test Case 4: All elements of nums2 are smaller
    vector<int> nums1 = {4, 5, 6, 0, 0, 0};
    int m = 3;
    vector<int> nums2 = {1, 2, 3};
    int n = 3;
    vector<int> expected = {1, 2, 3, 4, 5, 6};
    
    sol.merge(nums1, m, nums2, n);
    
    EXPECT_EQ(nums1, expected);
}

TEST_F(MergeSortedArrayTest, AllElementsOfNums2Larger) {
    // Test Case 5: All elements of nums2 are larger
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    int m = 3;
    vector<int> nums2 = {4, 5, 6};
    int n = 3;
    vector<int> expected = {1, 2, 3, 4, 5, 6};
    
    sol.merge(nums1, m, nums2, n);
    
    EXPECT_EQ(nums1, expected);
}

TEST_F(MergeSortedArrayTest, Nums1Empty) {
    // Test Case 6: nums1 has no elements
    vector<int> nums1 = {0, 0, 0};
    int m = 0;
    vector<int> nums2 = {1, 2, 3};
    int n = 3;
    vector<int> expected = {1, 2, 3};
    
    sol.merge(nums1, m, nums2, n);
    
    EXPECT_EQ(nums1, expected);
}