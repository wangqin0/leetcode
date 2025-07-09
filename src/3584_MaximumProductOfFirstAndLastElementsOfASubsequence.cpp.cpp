#include <gtest/gtest.h>
#include <vector>
#include <stdexcept>

using namespace std;

class Solution {
public:
    long long maximumProduct(vector<int>& nums, int m) {
        if (nums.size() < m) throw out_of_range("maximumProduct");
        long long maxPos = nums[0];
        long long minNeg = nums[0];
        long long res = max(nums[m - 1] * maxPos, nums[m - 1] * minNeg);
        for (size_t i = m; i < nums.size(); i++) {
            maxPos = max(maxPos, 1ll * nums[i - m + 1]);
            minNeg = min(minNeg, 1ll * nums[i - m + 1]);
            res = max({ res, nums[i] * maxPos, nums[i] * minNeg });
        }
        return res;
    }
};

TEST(MaximumProductTest, SizeLessThanMThrows) {
    Solution sol;
    vector<int> v{1, 2};
    EXPECT_THROW(sol.maximumProduct(v, 3), out_of_range);
}

TEST(MaximumProductTest, AllPositiveM2) {
    Solution sol;
    vector<int> v{1, 2, 3, 4, 5};
    // Pairs with index gap ≥1: max is 5*4 = 20 for m=2
    EXPECT_EQ(sol.maximumProduct(v, 2), 20);
}

TEST(MaximumProductTest, AllPositiveM3) {
    Solution sol;
    vector<int> v{1, 2, 3, 4, 5};
    // Pairs with index gap ≥2: max is 5*3 = 15
    EXPECT_EQ(sol.maximumProduct(v, 3), 15);
}

TEST(MaximumProductTest, AllNegative) {
    Solution sol;
    vector<int> v{-1, -2, -3, -4};
    // Pairs with index gap ≥1: max is (-4)*(-3) = 12
    EXPECT_EQ(sol.maximumProduct(v, 2), 12);
}

TEST(MaximumProductTest, MixedValues) {
    Solution sol;
    vector<int> v{0, -1, 2, -3, 4};
    // For m=2, best is 4*2 = 8
    EXPECT_EQ(sol.maximumProduct(v, 2), 8);
}

TEST(MaximumProductTest, MEqualsOne) {
    Solution sol;
    vector<int> v{3, -2, 5};
    // m=1 allows pairing each with itself or earlier; code yields max(v)^2 = 5*5 = 25
    EXPECT_EQ(sol.maximumProduct(v, 1), 25);
}

TEST(MaximumProductTest, MEqualsSize) {
    Solution sol;
    vector<int> v{3, -2, 5};
    // Only pair is first and last: 5*3 = 15
    EXPECT_EQ(sol.maximumProduct(v, 3), 15);
}

TEST(MaximumProductTest, AllEqualDuplicates) {
    Solution sol;
    vector<int> v{2, 2, 2, 2};
    // Any valid pair product = 4
    EXPECT_EQ(sol.maximumProduct(v, 2), 4);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
