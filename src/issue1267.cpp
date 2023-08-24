

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>

#include <unordered_map>

using namespace std;



class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int sum=0;

        int rownum = grid.size();
        int colnum = grid[0].size();
        unordered_map<int, int> cnt;
        for (int i=0; i<rownum; i++)
        {
            for(int j=0; j<colnum; j++)
            {
                if(grid[i][j] != 0)
                    cnt[i*colnum + j] = 1;
            }
        }

        for(auto it = cnt.begin(); it!=cnt.end(); it++)
        {
            int key = it->first;
            int val = it->second;
            if (val == 0)
                continue;
            int i=key/colnum;
            int j=key%colnum;


            int each_sum = 0;
            int self = 0;
            for(int jj=0; jj<colnum; jj++)
            {
                if(jj == j)
                    continue;
                if(grid[i][jj] != 0)
                {
                    if(cnt[i*colnum + jj] != 0)
                    {
                        each_sum ++;
                        cnt[i*colnum + jj] = 0;
                    }
                    self = 1;
                }
            }
            for(int ii=0; ii<rownum; ii++)
            {
                if(ii == i)
                    continue;
                if(grid[ii][j] != 0)
                {
                    if(cnt[ii*colnum + j] != 0)
                    {
                        each_sum ++;
                        cnt[ii*colnum + j] = 0;
                    }
                    self = 1;
                }
            }
            
            each_sum += self;
            it->second = 0;

            sum += each_sum;
        }
        return sum;

    }
};









int main()
{
    vector<vector<int>> grid = {{1,0},{1,1}};

    Solution method;
    int res = method.countServers(grid);

    
            cout << res << " ";
    
    
    return 0;
}

