// 定义“压缩字符串”：把“aabcccccaaa”处理，压缩为“a2bc5a3",返回字符串长度7
// 现在在此基础之前，先删掉k个字符，再字符串压缩，返回压缩后的字符串的最小长度

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

// 压缩字符串函数
int compressString(const std::string& s) {
    int n = s.size();
    if (n == 0) return 0;

    std::string compressed;
    int count = 1;
    for (int i = 1; i < n; ++i) {
        if (s[i] == s[i - 1]) {
            count++;
        } else {
            compressed += s[i - 1];
            if (count > 1) compressed += std::to_string(count);
            count = 1;
        }
    }
    compressed += s[n - 1];
    if (count > 1) compressed += std::to_string(count);

    return compressed.size();
}

int minCompressedLength(const std::string& s, int k) {
    int n = s.size();
    if (k == 0) return compressString(s);
    if (k >= n) return 0;

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, INT_MAX));
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            // 对于每个字符 s[i]，我们可以选择删除它或保留它

            // 如果删除 s[i]，则 dp[i][j] = dp[i-1][j-1]
            if (j > 0) {
                dp[i][j] = std::min(dp[i][j], dp[i - 1][j - 1]);
            }
            // 用于统计重复字符的数量
            int count = 0;
            for (int m = i; m > 0; --m) {
                if (s[m - 1] == s[i - 1]) {
                    count++;
                } else {
                    break;
                }
            }
            // 如果保留 s[i]，我们需要计算从 i 开始的最长连续相同字符的长度，并更新 dp 表
            if (dp[i - count][j] != INT_MAX) {
                dp[i][j] = std::min(dp[i][j], dp[i - count][j] + 1 + (count > 1 ? (int)std::to_string(count).size() : 0));
            }
        }
    }

    return dp[n][k];
}

std::string minCompressedString(std::string& s, int k) {
    int n = s.size();
    if (k == 0) return s;
    if (k >= n) return 0;
// std::string(n+1, '0')
    std::vector<std::vector<std::string>> dp(n + 1, std::vector<std::string>(k + 1, std::string(n+1, '0')));
    dp[0][0] = "";

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            // 对于每个字符 s[i]，我们可以选择删除它或保留它

            // 如果删除 s[i]，则 dp[i][j] = dp[i-1][j-1]
            if (j > 0) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            // 用于统计重复字符的数量
            int count = 0;
            for (int m = i; m > 0; --m) {
                if (s[m - 1] == s[i - 1]) {
                    count++;
                } else {
                    break;
                }
            }
            // 如果保留 s[i]，我们需要计算从 i 开始的最长连续相同字符的长度，并更新 dp 表
            if(i - count < j) {
                continue;
            }
            // if (dp[i - count][j].size() != n+1) 
            {
                std::string compressed = dp[i - count][j] +  s[i - 1] + (count > 1 ? std::to_string(count) : "");
                if(compressed.size() < dp[i][j].size())
                    dp[i][j] = compressed;
            }

        }
    }

    return dp[n][k];
}
int main() {
    std::string input = "aabcccccaaa";
    std::cout << "Length of compressed string: " << compressString(input) << std::endl;
    int k = 3; // 删除 k 个字符

    int minLength = minCompressedLength(input, k);
    std::cout << "Minimum length of compressed string after removing " << k << " characters: " << minLength << std::endl;
    std::cout << "Minimum string:"  << minCompressedString(input, k) << std::endl;

    return 0;
}