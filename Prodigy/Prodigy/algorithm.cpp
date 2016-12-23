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
        sort(nums.begin(),nums.end());
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
    //7. Three Sum Closet 23/12/2016
    int threeSumCloset(vector<int>& nums, int target){
        int result = 0;
        int sum = 0;
        sort(nums.begin(), nums.end());
        int min_gap = INT_MAX;
        for(auto i = nums.begin(); i != prev(nums.end(),2); i++){
            auto j = next (i);
            auto k = prev(nums.end());
            while(j<k){
                sum = *j + *k + *i;
                int gap = abs(sum - target);
                if (gap < min_gap){
                    min_gap = gap;
                    result = sum;
                }
                if(sum<target) j++;
                else k--;
            }
            
        }
        return result;
    }
    //8. Remove Element 23/12/2016
    int removeElement(vector<int>& nums, int target){
        int index = 0;
        for(int i=0;i<nums.size();i++){
            if(target != nums[i]){
                nums[index++] = nums[i];
            }
        }
        return index;
    }
    //9. Next Permutation 23/12/2016
    void nextPermutation(vector<int>& nums){
        next_permutation(nums.begin(), nums.end());
    }
    template<typename BitiIt>
    bool next_permutation(BitiIt first,BitiIt last){
        const auto rfirst = reverse_iterator<BitiIt>(last);
        const auto rlast = reverse_iterator<BitiIt>(first);
        auto pivot = next(rfirst);
        while(pivot != rlast && *pivot > *prev(pivot)){
            ++pivot;
        }
        while(pivot == rlast){
            reverse(rfirst, rlast);
            return false;
        }
        auto change = find_if(rfirst, pivot, bind1st(less<int>(), *pivot));
        swap(*pivot, *change);
        reverse(rfirst, pivot);
        return true;
    }
    //10. valid sudoku 23/12/2016
    bool isValidSudoku(const vector<vector<int>>& board){
        bool used[9];
        for(int i= 0; i < 9; i++){
            fill(used, used+9, false);
            //check rows
            for(int j = 0; j < 9; j++){
                if(!check(board[i][j],used)) return false;
            }
            fill(used, used+9, false);
            //check columns
            for(int j = 0; j < 9; j++){
                if(!check(board[j][i],used)) return false;
            }
        }
        //check little 9-box
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                fill(used, used+9, false);
                for(int r = i*3; r < i*3+3; r++){
                    for(int c = j*3; c < j*3+3; j++){
                        if(!check(board[r][c],used)) return false;
                    }
                }
            }
        }
        return true;
    }
    bool check(char ch, bool used[9]){
        if(ch == '.') return true;
        if(used[ch - '1']) return false;
        return used[ch - '1'] = true;
    }
    //11. trapping rain water 23/12/2016
    int trapWater(vector<int>& nums){
        int sum = 0;
        const int n = int(nums.size());
        vector<int>max_left(n);
        vector<int>max_right(n);
        for(int i = 1;i < n; i++){
            max_left[i] = max(max_left[i-1],nums[i-1]);
            max_right[n-i-1] = max(max_right[n-i],nums[n-i]);
        }
        for(int i = 1; i < n-1; i++){
            int height = min(max_right[i],max_left[i]);
            if(height > nums[i])
                sum += height - nums[i];
        }
        return sum;
    }
    
    //12. rotate image 23/12/2016
    void rotate(vector<vector<int>> &matrix){
        const int n = int(matrix.size());
        for(int i = 0; i < n/2; i++){
            for(int j = 0; j < n; j++){
                swap(matrix[i][j],matrix [n-i-1][j]);
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                swap(matrix[i][j],matrix[j][i]);
            }
        }
    }
    //13. plus one 23/12/2016
    void plusOne(vector<int>& digits){
        int c = 1;
        for(auto it = digits.rbegin(); it != digits.rend(); it++){
            *it += c;
            c = *it/10;
            *it %= 10;
        }
        if(c>0){digits.insert(digits.begin(), 1);}
    }
    //14. climb stairs 23/12/2016
    int climbStairs(int n){
        int prev = 0;
        int cur = 1;
        for(int i = 1; i <= n; i++){
            int tem = cur;
            cur += prev;
            prev = tem;
        }
        return cur;
    }
    //15. generate gray code 23/12/2016
    vector<int> grayCode(int n){
        vector<int> result;
        const int size = 1 << n;
        result.reserve(size);
        for(int i = 0; i<size; i++){
            result.push_back(binary_to_gray(i));
        }
        return result;
    }
    //16. setZeros 23/12/2016
    void setZeros(vector<vector<int>>& matrix){
        const size_t rows = matrix.size();
        const size_t columns = matrix[0].size();
        bool row_has_zero = false;
        bool column_has_zero = false;
        for(size_t i = 0; i < rows; i++)
        {
            if(matrix[i][0] == 0)
            {
            row_has_zero = true;
                break;
            }
        }
        for(size_t i = 0; i < columns; i++)
        {
            if(matrix[0][i] == 0)
            {
                column_has_zero = true;
                break;
            }
        }
        for(size_t i = 1; i < rows; i++){
            for(size_t j = 1; j < columns; j++){
                if(matrix[i][j] == 0){
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        for(size_t i = 1; i < rows; i++){
            for(size_t j = 1; j< columns; j++){
                if(matrix[i][0] == 0 || matrix[0][j] == 0){
                    matrix[i][j] = 0;
                }
            }
        }
        if(row_has_zero){
            for(size_t i = 0; i < rows; i++){
                matrix[i][0] = 0;
            }
        }
        if(column_has_zero){
            for(size_t i = 0; i < columns; i++){
                matrix[0][i] = 0;
            }
        }
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
    static int binary_to_gray(int i){
        return i ^ (i >> 1);
    }
};

int main(int argc, const char * argv[]) {
    Algorithm algorithm;
    vector<int> A={0,1,0,2,1,0,1,3,2,1,2,1};
    cout<<algorithm.trapWater(A)<<endl;
 
    return 0;

}
