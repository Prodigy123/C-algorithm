//
//  main.cpp
//  Prodigy
//
//  Created by 吉安 on 22/12/2016.
//  Copyright © 2016 An Ji. All rights reserved.
//

#include <iostream>
#include <vector>
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
};



int main(int argc, const char * argv[]) {
    
    
    std::cout << "Hello, World!\n";
    return 0;
}
