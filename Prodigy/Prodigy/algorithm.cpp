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
#include <numeric>
#include <list>
#include <string>
using namespace std;
// ListNode
struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(nullptr){}
};
class Algorithm{
public:
    /********************* 数组 ******************************/
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
    //17. gas stattion 24/12/2016
    int gasStation(vector<int>& gas, vector<int>& cost){
        int j = -1;
        int total = 0;
        int sum = 0;
        for(int i = 0;i < gas.size(); i++){
            sum += gas[i] - cost[i];
            total += gas[i] - cost[i];
            if(sum < 0){
                j = i;
                sum = 0;
            }
        }
        return total >= 0 ? j+1 :  -1;
    }
    //18. allocate candy 24/12/2016
    int candy(vector<int>& rating){
        const int n = int(rating.size());
        vector<int> increment(n);
        for(int i = 1, inc = 1; i < n; i++){
            if(rating[i] > rating[i-1])
                // increment[i] = max(inc++, increment[i]);
                increment[i] = inc++ ;
            else
                inc = 1;
        }
        for(int i = n-2, inc = 1; i >= 0; i--){
            if(rating[i] > rating[i+1]){
                // increment[i] = max(inc++,increment[i]);
                increment[i] = inc++ ;
            }else{ inc = 1;}
        }
        return accumulate(&increment[0], &increment[0]+n, n);
    }
    //19. single number 24/12/2016
    int findSingleNum(vector<int>& nums){
        int x = 0;
        for(auto i: nums){
            x ^= i;
        }
        return x;
    }
    //20. find the missing one (sorted array) 24/12/2016
    int findTheMissing(vector<int>& nums){
        int i = int(nums.size()) + 1;
        return find(nums.begin(),i,1);
    }
    int find(vector<int>::iterator it, int size, int begin)
    {   int result = begin;
        int x = 0;
        auto this_start = it;
        while(it != this_start + size/2){
            int tmp = result;
            if(*it < begin + size/2){
                tmp = result ^ *it;
            }
            x ^= tmp;
            result++;
            it++;
        }
        if(!*it) return result;
        if(x != 0) return x;
        else{return find(it, size - size/2, result);}
    }
    //21. single numbers from 3* 24/12/2016
    int findSingleFrom3(vector<int>& nums){
        int result = 0;
        const int bits = sizeof(int)*8;
        vector<int> count(bits);
        for(int i = 0; i < nums.size(); i++){
            for(int j = 0; j < bits; j++)
            {
                count[j] += (nums[i] >> j) & 1;
                count[j] %= 3;
            }
        }
        for(int i = 0; i< bits; i++){
            result += count[i] << i;
        }
        return result;
    }
    /******************** 单链表 ******************************/
    //22. add Two Nums 24/12/2016
    ListNode *addTwoNumbers(ListNode *L1, ListNode* L2){
        int carry = 0;
        ListNode dummy(-1);
        ListNode *prev = &dummy;
        for(ListNode *pa = L1, *pb = L2;
            pa != nullptr || pb != nullptr;
            pa = pa == nullptr ? nullptr : pa->next,
            pb = pb == nullptr ? nullptr : pb->next,
            prev = prev->next
            ){
            const int ai = pa == nullptr? 0 : pa->val;
            const int bi = pb == nullptr? 0 : pb->val;
            const int value = (ai + bi + carry)% 10;
            carry = (ai + bi + carry)/10;
            prev -> next = new ListNode(value);
        }
        if(carry>0){
            prev->next = new ListNode(carry);
        }
        return dummy.next;
    }
    //23. partition a List 24/12/2016
    ListNode *partition(ListNode *head, int x){
        ListNode left_dummy(-1);
        ListNode right_dummy(-1);
        auto left_prev = &left_dummy;
        auto right_prev = &right_dummy;
        for(auto cur = head; cur; cur = cur->next){
            if(cur->val < x){
                left_prev->next = cur;
                left_prev = cur;
            }
            if(cur->val > x){
                right_prev->next = cur;
                right_prev = cur;
            }
        }
        left_prev->next = right_dummy.next;
        right_prev->next = nullptr;
        return left_dummy.next;
    }
    //24. remove duplicates from sorted list 25/12/2016
    ListNode *remove(ListNode *head){
        if(!head || !head->next) return head;
        ListNode dummy = ListNode(-1);
        dummy.next = head;
        recur(&dummy,head);
        return dummy.next;
    }
    //25. remove duplicates and self from sorted list 25/12/2016
    ListNode *removeDandS(ListNode *head){
        if(!head || !head->next) return head;
        ListNode *p = head->next;
        if(p->val == head->val){
            ListNode *tmp = p;
            p = p->next;
            delete tmp;
            delete head;
            return removeDandS(p);
        }else{
            head->next = removeDandS(p->next);
            return head;
        }
    }
    //26. Rotate List 25/12/2016
    ListNode *rotateList(ListNode*head, int k){
        if(!head || !head->next) return head;
        ListNode *p = head;
        int len = 1;
        while(p->next){
            len++;
            p = p->next;
        }
        k = len - k%len;
        head = p->next;
        for(int step = 0; step < k; step++){
            p = p -> next;
        }
        head = p->next;
        p->next = nullptr;
        return head;
    }
    //27. remove nth node from end of the list 25/12/2016
    ListNode *delenth(ListNode *head, int n){
        ListNode dummy = ListNode(-1);
        dummy.next = head;
        ListNode *p = &dummy, *q = &dummy;
        for(int i = 0; i < n; i++){
            q = q->next;
        }
        while(q->next){
            p = p->next;
            q = q->next;
        }
        ListNode *tmp = p->next;
        p->next = p->next->next;
        delete tmp;
        return dummy.next;
    }
    //28. swap nodes in pair 25/12/2016
    ListNode *swapList(ListNode *head){
        if(!head || !head->next) return head;
        ListNode dummy = ListNode(-1);
        dummy.next = head;
        for(ListNode *prev = &dummy,
            *cur = prev->next,
            *next = cur == nullptr ? nullptr : cur->next;
            next;
            cur = prev->next,
            next = cur ? cur->next : nullptr
            ){
            prev->next = next;
            cur->next = next->next;
            next->next = cur;
            prev = cur;
        }
        return dummy.next;
    }
    //29. reverse Kgroup 25/12/2016
    ListNode *reverseKgroup(ListNode *head, int k){
        if(!head || !head->next || k < 2) return head;
        ListNode *new_group = head;
        for(int i = 0; i < k; i++){
            if(new_group->next){
                new_group = new_group->next;
            }else{
                return head;
            }
        }
        ListNode *new_group_head = reverseKgroup(new_group, k);
        ListNode *prev = NULL,*cur = head;
        while(cur != new_group){
            ListNode *next = cur->next;
            cur->next = prev ? prev : new_group_head;
            prev = cur;
            cur = next;
        }
        return prev;
    }
    //30. check Cycle 25/12/2016
    bool isCycle(ListNode *head){
        ListNode *slow = head,*fast = head;
        while(fast && fast->next){
            fast = fast->next->next;
            slow = slow->next;
            if(slow == fast) return  true;
        }
        return false;
    }
    //31. linked list cycle(find the cycle begin point) 25/12/2016
    ListNode *findCyclePoint(ListNode *head){
        ListNode *fast = head, *slow = head;
        while(fast && fast->next){
            fast = fast->next->next;
            slow = slow->next;
            while(fast == slow){
                ListNode *slow2 = head;
                while(slow != slow2){
                    slow = slow->next;
                    slow2 = slow2->next;
                }
                return slow2;
            }
        }
        return nullptr;
    }
    //32. reordered List 25/12/2016
    ListNode *reorder(ListNode *head){
        if(!head || !head->next) return head;
        ListNode dummy = ListNode(-1);
        dummy.next = head;
        ListNode *slow = head, *fast = head, *prev = nullptr;
        while(fast && fast->next){
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        prev->next = nullptr;
        slow = reverseHalf(slow);
        ListNode *cur = head;
        //merge lists
        while(cur->next)
        {
            ListNode *tmp = cur->next;
            cur->next = slow;
            slow = slow->next;
            cur->next->next = tmp;
            cur = tmp;
        }
        cur->next = slow;
        return dummy.next;
    }
    
    ListNode *reverseHalf(ListNode *head){
        ListNode *prev = head;
        for(ListNode *cur = head->next, *next = cur->next;
            cur;
            ){
            cur->next = prev;
            prev = cur;
            cur = next;
            next = next ? next->next : nullptr;
        }
        head->next = nullptr;
        return prev;
    }
    //private methods
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
    //34. remove duplicates from sorted list 25/12/2016
    static void recur(ListNode *prev, ListNode *cur){
        if(cur == nullptr) return;
        if(prev->val == cur->val){
            prev->next = cur->next;
            delete cur;
            recur(prev,prev->next);
        }else{
            recur(prev->next,cur->next);
        }
    }
/******************** 字符串 ******************************/
    //36. palindroma 25/12/2016
    bool isPalindraoma(string s){
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        int left = 0;
        int right = int(s.size() - 1);
        while(left < right){
            if(!isalnum(s[left])) left++;
            else if(!isalnum(s[right])) right--;
            else if(s[left] != s[right]) return false;
            else{left++; right--;}
        }
        return true;
    }
    //37. Implement strStr 25/12/2016
    int strStr(string &haystatck, string &niddle){
        if(niddle.empty()) return 0;
        const int n = int(haystatck.size() - niddle.size() +1);
        for(int i = 0; i < n; i++){
            int j = i;
            int k =0;
            while(j < haystatck.size() && k < niddle.size() && haystatck[j] == niddle[k]){
                j++;
                k++;
            }
            if(k == niddle.size()) return i;
        }
        return -1;
    }
    //38. atoi 26/12/2016
    int myAtoi(string &s){
        int num = 0;
        int sign = 1;
        int i = 0;
        const int size = int(s.size());
        while(s[i] == ' ' && i < size) i++;
        if(s[i] == '-') {sign = -1;i++;}
        else if (s[i] == '+') {sign = 1;i++;}
        for(;i < size; i++){
            if(s[i] < '0' || s[i] > '9') break;
            if(num > INT_MAX/10 || (num == INT_MAX/10 && s[i] - '0' > INT_MAX%10))
               return sign == 1 ? INT_MAX : INT_MIN;
            num = num*10 + s[i] - '0';
        }
        return num*sign;
    }
    //39. addBinary 26/12/2016
    string addBinary(string a,string b){
        string result;
        int carry = 0;
        const size_t size = a.size() > b.size() ? a.size() : b.size();
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        for(size_t i; i < size; i++){
            const int ai = i < a.size() ? a[i] - '0' : 0;
            const int bi = i < b.size() ? b[i] - '0' : 0;
            const int val = (ai + bi + carry)%10;
            carry = (ai + bi + carry)/10;
            result.insert(result.begin(), val + '0');
        }
        if(carry == 1) result.insert(result.begin(), '1');
        return result;
    }
    //40. longest palindromic substr 26/12/2016
    string longestPalindormicSub(const string &s){
        size_t maxLen = 1;
        size_t start = 0;
        const size_t n = s.size();
        bool f[n][n];
        fill_n(&f[0][0], n*n, false);
        for(size_t i = 0;i < n; i++){
            f[i][i] = true;
            for(size_t j = 0; j < i; j++){
                f[j][i] = (s[i] == s[j] && ((i - j < 2) || f[j+1][i-1]));
                if(f[j][i] && maxLen < (i - j + 1)){
                    maxLen = i -j + 1;
                    start = j;
                }
            }
        }
        return s.substr(start,maxLen);
    }
    //41. longest common prefix 26/12/2016
    string prefix(vector<string> &strs){
        if(strs.empty()) return "";
        const size_t nums = strs.size();
        const size_t strSize = strs[0].size();
        for(size_t i = 0; i < strSize; i++){
            for(size_t j = 0; j < nums; j++){
                if(strs[j][i] != strs[0][i]) return strs[0].substr(0,i);
            }
        }return strs[0];
    }
    //42. anagrams 26/12/2016
    vector<string> anagram(vector<string>& strs){
        vector<string> result;
        unordered_map<string, vector<string>> record;
        for(auto &str : strs){
            string key = str;
            sort(key.begin(),key.end());
            record[key].push_back(str);
        }
        for(auto it = record.cbegin(); it!=record.cend();it++){
            if(it->second.size() > 1) result.insert(result.end(), it->second.begin(),it->second.end());
        }
        return result;
    }
    //43. length of last word 26/12/2016
    size_t lengthOfLastWord(string& str){
        auto first = find_if(str.rbegin(),str.rend(),::isalpha);
        auto last = find_if_not(first,str.rend(),::isalpha);
        return distance(first, last);
    
    }
};
//35. LRUCache 25/12/2016
class LRUCache{
private:
    struct Node{
        int key;
        int value;
        Node(int key, int value): key(key),value(value){}
    };
    int capacity;
    list<Node> lrulist;
    unordered_map<int, list<Node>::iterator> lrumap;
public:
    LRUCache(int capacity):capacity(capacity){}
    int get(int key){
        if(lrumap.find(key) == lrumap.end()) return -1;
        lrulist.splice(lrulist.begin(),lrulist,lrumap[key]);
        lrumap[key] = lrulist.begin();
        return lrumap[key]->value;
    }
    void set(int key, int value){
        if(lrumap.find(key) == lrumap.end()){
            if(sizeof(lrulist) == capacity){
                lrulist.pop_back();
                lrumap.erase(lrulist.back().key);
            }
            lrulist.push_front(Node(key,value));
            lrumap[key] = lrulist.begin();
        }else{
            lrulist.splice(lrulist.begin(), lrulist,lrumap[key]);
            lrumap[key] = lrulist.begin();
            lrumap[key]->value = value;
        }
    }
    
};
int main(int argc, const char * argv[]) {
    //    Algorithm algorithm;
    //    vector<int> A={1,2,3,4,5,7,8,9};
    //    cout<<algorithm.findTheMissing(A)<<endl;
//    cout<<sizeof(int)<<endl;
//    LRUcache A(10);
    string s = "qdqdqdq";
    return 0;
    
}
