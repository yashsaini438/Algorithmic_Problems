// Link: "https://leetcode.com/problems/maximum-subarray-sum-after-at-most-k-swaps/description/"

class Solution {
public:
    long long maxSum(vector<int>& nums, int k) {
        int n = nums.size();
        long long ans = -1e15;
        if(k==0 || n==1){
            long long sum = 0;
            for(int i=0;i<n;i++){
                sum+=nums[i];
                ans = max(ans,sum);

                if(sum<0)   sum=0;
            }
            return ans;
        }

        vector<long long> prefix(n+1,0);

        long long swapMoreThanNegative = 0;
        int count = 0;

        for(int i=0;i<n;i++){
            if(nums[i]>0){
                swapMoreThanNegative += nums[i];
            }else{
                count++;
            }

            prefix[i+1] = prefix[i] + nums[i];
            ans = max(ans,nums[i]*1LL);
        }

        if(count<=k){
            return swapMoreThanNegative;
        }

        vector<vector<long long>> dp(n,vector<long long>(n,0));

        for(int i=0;i<n;i++){
            priority_queue<int> MaxHeapforInside;
            long long penalty = 0;
            for(int j=i;j<n;j++){
                if(nums[j]>=0)  dp[i][j] = penalty;
                else{
                    if(MaxHeapforInside.size()<k){
                        MaxHeapforInside.push(nums[j]);
                        penalty+=nums[j];
                        dp[i][j] = penalty;
                    }else{
                        if(nums[j]<MaxHeapforInside.top()){
                            penalty -= MaxHeapforInside.top();
                            MaxHeapforInside.pop();
                            MaxHeapforInside.push(nums[j]);
                            penalty += nums[j];
                            dp[i][j] = penalty;
                        }
                    }
                }
            }
        }

        for(int i=0;i<n;i++){
            priority_queue<int,vector<int>,greater<int>> MinHeapForOutside;
            
            long long advantage = 0;
            for(int j=0;j<i;j++){
                if(nums[j]<0)   continue;

                if(MinHeapForOutside.size()<k){
                    advantage += nums[j];
                    MinHeapForOutside.push(nums[j]);
                }else{
                    if(MinHeapForOutside.top()<nums[j]){
                        advantage -= MinHeapForOutside.top();
                        MinHeapForOutside.pop();
                        advantage += nums[j];
                        MinHeapForOutside.push(nums[j]);
                    }
                }
            }

            for(int j=n-1;j>i;j--){
                long long cur = prefix[j+1] - prefix[i];
                cur -= dp[i][j];
                cur += advantage;

                if(nums[j]<0)   continue;

                if(MinHeapForOutside.size()<k){
                    advantage += nums[j];
                    MinHeapForOutside.push(nums[j]);
                }else{
                    if(MinHeapForOutside.top()<nums[j]){
                        advantage -= MinHeapForOutside.top();
                        MinHeapForOutside.pop();
                        MinHeapForOutside.push(nums[j]);
                        advantage += nums[j];
                    }
                }
                ans = max(ans,cur);
            }
        }
        return ans;
    }
};