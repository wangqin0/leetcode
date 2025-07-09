#include <iostream>
#include <algorithm>
#include <vector>
#include <gtest/gtest.h>

using namespace std;


template<typename ForwardIt, typename T>
ForwardIt lower_bound_(ForwardIt begin, ForwardIt end, T target)
{
    while (begin != end) {
        auto mid = begin + (end - begin) / 2;
        if (*mid < target) {
            begin = mid + 1;
        } else {
            end = mid;
        }
    }
    return begin;
}

template<typename ForwardIt, typename T>
ForwardIt upper_bound_(ForwardIt begin, ForwardIt end, T target)
{
    while (begin != end) {
        auto mid = begin + (end - begin) / 2;
        if (*mid <= target) {
            begin = mid + 1;
        } else {
            end = mid;
        }
    }
    return begin;}

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int lower = lower_bound_(nums.begin(), nums.end(), target) - nums.begin();
        int upper = upper_bound_(nums.begin(), nums.end(), target) - nums.begin();
        if (lower >= upper) { return { -1, -1 }; }
        return { lower, upper - 1 };
    }
};

// Test fixtures for searchRange

TEST(SearchRangeTest, EmptyVector) {
    Solution sol;
    vector<int> nums;
    auto res = sol.searchRange(nums, 5);
    EXPECT_EQ(res, vector<int>({-1, -1}));
}

TEST(SearchRangeTest, SingleElementFound) {
    Solution sol;
    vector<int> nums = {5};
    auto res = sol.searchRange(nums, 5);
    EXPECT_EQ(res, vector<int>({0, 0}));
}

TEST(SearchRangeTest, SingleElementNotFound) {
    Solution sol;
    vector<int> nums = {3};
    auto res = sol.searchRange(nums, 5);
    EXPECT_EQ(res, vector<int>({-1, -1}));
}

TEST(SearchRangeTest, NoTargetInMultipleElements) {
    Solution sol;
    vector<int> nums = {1, 2, 4, 6, 7};
    auto res = sol.searchRange(nums, 5);
    EXPECT_EQ(res, vector<int>({-1, -1}));
}

TEST(SearchRangeTest, SingleTargetAtBeginning) {
    Solution sol;
    vector<int> nums = {2, 3, 4, 5};
    auto res = sol.searchRange(nums, 2);
    EXPECT_EQ(res, vector<int>({0, 0}));
}

TEST(SearchRangeTest, SingleTargetAtEnd) {
    Solution sol;
    vector<int> nums = {1, 2, 3, 5};
    auto res = sol.searchRange(nums, 5);
    EXPECT_EQ(res, vector<int>({3, 3}));
}

TEST(SearchRangeTest, MultipleTargetsContinuous) {
    Solution sol;
    vector<int> nums = {1, 2, 2, 2, 3, 4};
    auto res = sol.searchRange(nums, 2);
    EXPECT_EQ(res, vector<int>({1, 3}));
}

TEST(SearchRangeTest, AllElementsAreTarget) {
    Solution sol;
    vector<int> nums = {7, 7, 7, 7};
    auto res = sol.searchRange(nums, 7);
    EXPECT_EQ(res, vector<int>({0, 3}));
}

TEST(SearchRangeTest, TargetInMiddle) {
    Solution sol;
    vector<int> nums = {1, 3, 5, 5, 5, 8};
    auto res = sol.searchRange(nums, 5);
    EXPECT_EQ(res, vector<int>({2, 4}));
}

TEST(SearchRangeTest, NegativeValues) {
    Solution sol;
    vector<int> nums = {-3, -2, -2, 0, 1};
    auto res = sol.searchRange(nums, -2);
    EXPECT_EQ(res, vector<int>({1, 2}));
}

// Edge case: unsorted vector (behavior undefined but should still run)
TEST(SearchRangeTest, UnsortedVector) {
    Solution sol;
    vector<int> nums = {5, 2, 3, 2, 5};
    auto res = sol.searchRange(nums, 2);
    // lower_bound_ on unsorted may give unpredictable result; check bounds safety
    EXPECT_TRUE(res[0] >= 0 && res[0] < nums.size());
    EXPECT_TRUE(res[1] >= -1 && res[1] < nums.size());
}