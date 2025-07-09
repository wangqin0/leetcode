// watering_plants_test.cpp

#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution {
public:
    int wateringPlants(vector<int>& plants, int capacity) {
        // assuming capacity >= elem in plants
        int w = capacity;
        int res = plants.size();
        for (size_t i = 0; i < plants.size(); i++) {
            if (w < plants[i]) {
                res += (i + i);
                w = capacity;
            }
            w -= plants[i];
        }
        return res;
    }
};

TEST(WateringPlantsTest, NoPlants) {
    Solution sol;
    vector<int> plants;
    EXPECT_EQ(sol.wateringPlants(plants, 10), 0);
}

TEST(WateringPlantsTest, SinglePlantNoRefill) {
    Solution sol;
    vector<int> plants = {3};
    EXPECT_EQ(sol.wateringPlants(plants, 5), 1);
}

TEST(WateringPlantsTest, TwoPlantsNoRefill) {
    Solution sol;
    vector<int> plants = {1, 2};
    EXPECT_EQ(sol.wateringPlants(plants, 3), 2);
}

TEST(WateringPlantsTest, TwoPlantsOneRefill) {
    Solution sol;
    vector<int> plants = {2, 3};
    // Step-by-step:
    // start with w=3, res=2
    // i=0: w>=2 → w=1
    // i=1: w<3 → res+=2*1=2 → res=4; w=3; w-=3 → w=0
    EXPECT_EQ(sol.wateringPlants(plants, 3), 4);
}

TEST(WateringPlantsTest, ManyPlantsMultipleRefills) {
    Solution sol;
    vector<int> plants = {1, 1, 1, 1};
    // Each plant requires a refill except the first.
    // Expected total steps = 16
    EXPECT_EQ(sol.wateringPlants(plants, 1), 16);
}

TEST(WateringPlantsTest, ExampleFromProblem) {
    Solution sol;
    vector<int> plants = {2, 2, 5, 2, 1};
    // From the problem statement, the correct answer is 15
    EXPECT_EQ(sol.wateringPlants(plants, 6), 15);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
