#include <iostream>
#include <vector>
#include <gtest/gtest.h>

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
class RemoveElementTest : public ::testing::Test {
protected:
    Solution sol;
};

TEST_F(RemoveElementTest, BasicCase) {
    // Test Case 1: Basic case
    vector<int> nums = {3, 2, 2, 3};
    int val = 3;
    int expected_k = 2;
    vector<int> expected_nums = {2, 2}; // The first k elements should match this
    
    int k = sol.removeElement(nums, val);
    
    EXPECT_EQ(k, expected_k);
    for (int i = 0; i < k; ++i) {
        EXPECT_EQ(nums[i], expected_nums[i]);
    }
}

TEST_F(RemoveElementTest, NoElementsToRemove) {
    // Test Case 2: No elements to remove
    vector<int> nums = {0, 1, 2, 2, 3, 0, 4, 2};
    int val = 5;
    int expected_k = 8;
    vector<int> expected_nums = {0, 1, 2, 2, 3, 0, 4, 2};
    
    int k = sol.removeElement(nums, val);
    
    EXPECT_EQ(k, expected_k);
    for (int i = 0; i < k; ++i) {
        EXPECT_EQ(nums[i], expected_nums[i]);
    }
}

TEST_F(RemoveElementTest, AllElementsToRemove) {
    // Test Case 3: All elements to remove
    vector<int> nums = {7, 7, 7, 7};
    int val = 7;
    int expected_k = 0;
    
    int k = sol.removeElement(nums, val);
    
    EXPECT_EQ(k, expected_k);
}

TEST_F(RemoveElementTest, EmptyVector) {
    // Test Case 4: Empty vector
    vector<int> nums = {};
    int val = 0;
    int expected_k = 0;
    
    int k = sol.removeElement(nums, val);
    
    EXPECT_EQ(k, expected_k);
}

TEST_F(RemoveElementTest, OneElementToRemove) {
    // Additional test case: One element to remove from the middle
    vector<int> nums = {1, 2, 3, 4, 5};
    int val = 3;
    int expected_k = 4;
    vector<int> expected_nums = {1, 2, 4, 5};
    
    int k = sol.removeElement(nums, val);
    
    EXPECT_EQ(k, expected_k);
    for (int i = 0; i < k; ++i) {
        EXPECT_EQ(nums[i], expected_nums[i]);
    }
}
