//
//  main.cpp
//  Prodigy
//
//  Created by 吉安 on 22/12/2016.
//  Copyright © 2016 An Ji. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class Algorithm{
public:
    // 1. remove (k)duplicats from sorted array  22/12/2016
    int removeDuplicates(vector<int>& nums, int k){
        if(nums.empty()) return 0;
        int index = k;
        for(int i=k;i<nums.size();i++){
            if(nums[index-k] != nums[i]){
                nums[index++] = nums[i];
            }
        }
        return index;
    }
    //2. search in a rotated sorted array 22/12/2016
    int search(vector<int>& nums, int target){
        int first = 0,last = int(nums.size());
        while(first != last){
            const int mid = first + (last-first)/2;
            if(nums[mid] == target) return mid;
            if(nums[first] < nums[mid]){
                if(target >= nums[first] && target < nums[mid]){
                    last = mid;
                }else{
                    first = mid + 1;
                }
            }else{
                if(target > nums[mid] && target  < nums[last-1])
                {
                    first = mid + 1;
                }else{
                    last = mid;
                }
            }
        }
        return -1;
    }
    //3. find median from two sorted array O(log(m+n)) 22/12/2016
    int findMedianFromTwoSortedArray(const vector<int>& A, const vector<int>& B){
        const int m = int(A.size());
        const int n = int(B.size());
        int total = m+n;
        if (total &0x1) return find_kth(A.begin(), m, B.begin(), n, total/2+1);
        else return (find_kth(A.begin(), m, B.begin(), n, total/2)+find_kth(A.begin(), m, B.begin(), n, total/2+1))/2;
    }
    //4. find longest consecutive 22/12/2016
    int longestConsecutive(const vector<int>& nums){
        int longest = 0;
        unordered_map<int, bool>used;
        for(auto i: nums) used[i] = false;
        for(auto i: nums){
            if(used[i]) continue;
            int length = 1;
            for(int j = i+1; used.find(j) != used.end(); j++){
                length++;
            }
            for(int j=i-1; used.find(j) != used.end(); j--){
                length--;
            }
            longest = max(longest,length);
        }
        return longest;
    }
    //5. Two Sum 22/12/2016
    vector<int> twoSum(vector<int>& nums, int target){
        vector<int> result;
        unordered_map<int, int>mapping;
        for(int i= 0;i<nums.size();i++){mapping[nums[i]] = i;}
        for(int i= 0;i<nums.size();i++)
        {
            int gap = target - i;
            if(mapping.find(gap) != mapping.end() && mapping[gap] > i){
                result.push_back(i+1);
                result.push_back(mapping[gap]+1);
                break;
            }
        }
        return result;
    }
    //6. Three Sum 22/12/2016
    vector<vector<int>> threeSum(vector<int>& nums){
        vector<vector<int>> result;
        const int target = 0;
        if(nums.size() < 2) return result;
        auto last = nums.end();
        for(auto i = nums.begin(); i < last - 2; i++){
            auto j = i+1;
            if(i>nums.begin() && *i == *(i-1)) continue;
            auto k = last-1;
            while(j<k){
                if((*i + *j + *k)< target){
                    j++;
                    while(*j == *(j-1) && j<k) j++;
                }else if((*i + *j + *k) > target){
                    k--;
                    while(*k == *(k+1) && j<k) k--;
                }else{
                    result.push_back({*i,*j,*k});
                    j++;
                    k--;
                    while(*j == *(j-1) && *k == *(k+1) && j<k) j++;
                }
            }
        }
        return result;
    }
    //private method
private:
    //3. find median from two sorted array O(log(m+n)) 22/12/2016
    static int find_kth(vector<int>::const_iterator A, int m, vector<int>::const_iterator B, int n, int k){
        if(m>n) return find_kth(B, n, A, m, k);
        if(m == 0) return *(B+k-1);
        if(k == 1) return min(*A,*B);
        int ia = min(k/2,m), ib = k - ia;
        if(*(A+ia-1) < *(B+ib-1))
            return find_kth(A+ia, m-ia, B, n, k-ia);
        else if(*(A+ia-1) > *(B+ib-1))
            return find_kth(A, m, B+ib, n-ib, k-ib);
        else
            return A[ia-1];
    }
};

int main(int argc, const char * argv[]) {
//    Algorithm algorithm;
    vector<int> A={3,23,12,3,24,33,2};
//    sort(A.begin(),A.end());
    for(auto i : A){
        cout<<i<<endl;
    }
    return 0;
}
