//-----------------------------------------------
//给你一个 非空 整数数组 nums ，除了某个元素只出现一次以外，其余每个元素均出现两次。
//找出那个只出现了一次的元素。
//你必须设计并实现线性时间复杂度的算法来解决此问题，且该算法只使用常量额外空间。
//示例 1 ：
//输入：nums = [2, 2, 1]
//输出：1
//示例 2 ：
//输入：nums = [4, 1, 2, 1, 2]
//输出：4
//示例 3 ：
//输入：nums = [1]
//输出：1
//
//class Solution {
//public:
//    int singleNumber(vector<int>& nums) {
//        int ret = 0;
//
//        for (auto e : nums)
//        {
//            ret ^= e;
//        }
//
//        return ret;
//    }
//};




//-----------------------------------------------
//给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。
//在「杨辉三角」中，每个数是它左上方和右上方的数的和。
//示例 1:
//输入: numRows = 5
//输出 : [[1], [1, 1], [1, 2, 1], [1, 3, 3, 1], [1, 4, 6, 4, 1]]
//示例 2 :
//输入 : numRows = 1
//输出 : [[1]]
//
//class Solution {
//public:
//    vector<vector<int>> generate(int numRows) {
//        vector<vector<int>> vv;
//        vv.resize(numRows);
//
//        for (size_t i = 0; i < vv.size(); ++i)
//        {
//            vv[i].resize(i + 1, 0);
//            vv[i][0] = vv[i][vv[i].size() - 1] = 1;
//        }
//
//        for (size_t i = 0; i < vv.size(); ++i)
//        {
//            for (size_t j = 0; j < vv[i].size(); ++j)
//            {
//                if (vv[i][j] == 0)
//                {
//                    vv[i][j] = vv[i - 1][j - 1] + vv[i - 1][j];
//                }
//            }
//        }
//
//        return vv;
//    }
//};




//-----------------------------------------------
//给你一个整数数组 nums，除某个元素仅出现一次外，其余每个元素都恰出现三次。
//请你找出并返回那个只出现了一次的元素。
//你必须设计并实现线性时间复杂度的算法且不使用额外空间来解决此问题。
//示例 1：
//输入：nums = [2, 2, 3, 2]
//输出：3
//示例 2：
//输入：nums = [0, 1, 0, 1, 0, 1, 99]
//输出：99
//
//class Solution {
//public:
//    int singleNumber(vector<int>& nums) {
//        int ans = 0;
//
//        for (int i = 0; i < 32; ++i)
//        {
//            int total = 0;
//
//            for (auto e : nums)
//            {
//                total += ((e >> i) & 1);
//            }
//
//            if (total % 3)
//            {
//                ans |= (1 << i);
//            }
//        }
//
//        return ans;
//    }
//};




//-----------------------------------------------
//给一个长度为 n 的数组，数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
//例如输入一个长度为9的数组[1, 2, 3, 2, 2, 2, 5, 4, 2]。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。
//
//数据范围：n≤50000，数组中元素的值：0≤val≤10000
//要求：空间复杂度：O(1)，时间复杂度：O(n)

class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        if (numbers.size() < 2)
        {
            return numbers[0];
        }

        sort(numbers.begin(), numbers.end());

        int cnt = 1;
        int i = 0;
        for (i = 1; i < numbers.size(); ++i)
        {
            if (numbers[i] == numbers[i - 1])
            {
                ++cnt;
            }
            else
            {
                cnt = 1;
            }

            if (cnt > (numbers.size() / 2))
            {
                break;
            }
        }

        return numbers[i];
    }
};