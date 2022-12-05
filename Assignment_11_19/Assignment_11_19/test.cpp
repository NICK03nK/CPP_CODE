//-----------------------------------------------
//给你一个升序排列的数组nums，请你原地删除重复出现的元素，使每个元
//素只出现一次，返回删除后数组的新长度。元素的相对顺序应该保持一致。
//示例 1：
//输入：nums = [1, 1, 2]
//输出：2, nums = [1, 2, _]
//解释：函数应该返回新的长度 2 ，并且原数组 nums 的前两个元素被修改为 1, 2。
//不需要考虑数组中超出新长度后面的元素。
//示例 2：
//输入：nums = [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]
//输出：5, nums = [0, 1, 2, 3, 4]
//解释：函数应该返回新的长度 5 ， 并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4。
//不需要考虑数组中超出新长度后面的元素。
//
//class Solution {
//public:
//    int removeDuplicates(vector<int>& nums) {
//        vector<int>::iterator it = nums.begin() + 1;
//        while (it != nums.end())
//        {
//            if (*it == *(it - 1))
//            {
//                it = nums.erase(it);
//            }
//            else
//            {
//                ++it;
//            }
//        }
//
//        return nums.size();
//    }
//};




//-----------------------------------------------
//给你一个整数数组 nums，其中恰好有两个元素只出现一次，其
//余所有元素均出现两次。 找出只出现一次的那两个元素。
//你可以按任意顺序返回答案。
//示例 1：
//输入：nums = [1, 2, 1, 3, 2, 5]
//输出：[3, 5]
//解释：[5, 3] 也是有效的答案。
//示例 2：
//输入：nums = [-1, 0]
//输出：[-1, 0]
//示例 3：
//输入：nums = [0, 1]
//输出：[1, 0]
//
//class Solution {
//public:
//    vector<int> singleNumber(vector<int>& nums) {
//        int ret = 0;
//        for (auto e : nums)
//        {
//            ret ^= e;
//        }
//
//        int index = 0;
//        for (int i = 0; i < 32; ++i)
//        {
//            if ((ret >> i) & 1)
//            {
//                index = i;
//                break;
//            }
//        }
//
//        int type1 = 0, type2 = 0;
//        for (auto e : nums)
//        {
//            if ((e >> index) & 1)
//            {
//                type1 ^= e;
//            }
//            else
//            {
//                type2 ^= e;
//            }
//        }
//
//        return { type1, type2 };
//    }
//};




//-----------------------------------------------
//给定一个仅包含数字 2 - 9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
//给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
//示例 1：
//输入：digits = "23"
//输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]
//示例 2：
//输入：digits = ""
//输出：[]
//示例 3：
//输入：digits = "2"
//输出：["a", "b", "c"]
//
//class Solution {
//    string _numStr[10] = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
//public:
//    void combine(string& digits, int i, vector<string>& vComb, string str)
//    {
//        if (i == digits.size())
//        {
//            vComb.push_back(str);
//
//            return;
//        }
//
//        int num = digits[i] - '0';
//        for (auto e : _numStr[num])
//        {
//            combine(digits, i + 1, vComb, str + e);
//        }
//    }
//
//    vector<string> letterCombinations(string digits) {
//        vector<string> vComb;
//
//        if (digits.empty())
//        {
//            return vComb;
//        }
//
//        string str;
//
//        combine(digits, 0, vComb, str);
//
//        return vComb;
//    }
//};