#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if(n==0) return 0;

        int left = 0;
        int right = n - 1;

        int leftMax = height[left];
        int rightMax = height[right];

        int totalWater = 0;

        while ( left < right ) {
            if (height[left]< height[right]){
                leftMax = max(leftMax ,height[left]);
                totalWater += leftMax - height[left];
                left++;
            } else {
                rightMax = max(rightMax, height[right]);
                totalWater += rightMax - height[right];
                right--;
            }
        }
        
        return totalWater;
    }
};