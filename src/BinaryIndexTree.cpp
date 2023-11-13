#include <vector>

class BinaryIndexTree {
protected:
    inline int lowbit(int x) {
        return x & (-x);
    }
public:
    std::vector<int> tree;

    BinaryIndexTree(const std::vector<int> &nums) {
        tree.resize(nums.size()+1);
        for(int i = 0; i < nums.size(); i++) {
            update(i, nums[i]);
        }
    }

    inline int query(int n) // 前n项和
    {
        int ans = 0;
        for (int pos = n; pos; pos -= lowbit(pos))
            ans += tree[pos];
        return ans;
    }
    inline int query(int a, int b) // 左闭右闭
    {
        return query(b + 1) - query(a);
    }
    inline void update(int index, int val)
    {
        int num = query(index + 1) - query(index);
        int x = val - num;
        for (int pos = index+1; pos < tree.size(); pos += lowbit(pos))
            tree[pos] += x;
    }
};

