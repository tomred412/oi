class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<vector<int>> result;

        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
                unordered_set<int> mark;
            for (int j = i + 1; j < nums.size(); j++) {
                int good = -nums[j] - nums[i];

                if (mark.count(good) > 0) {
                    result.push_back({nums[i], nums[j], good});
                    while (j + 1 < nums.size() && nums[j] == nums[j + 1]) {
                        j++;
                    }
                }
                mark.insert(nums[j]);
            }
        }
        
        return result;
    }
};
