

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>

#include <unordered_map>
using namespace std;



class Solution {
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        vector<int> return_vec;
        //int return_vec[n][n] = {0};

        vector<vector<int> > graph(n, vector<int>(n,0));
        for(auto pair:edges)
        {
            int a = pair[0], b = pair[1];
            graph[b-1][a-1] ++;
            graph[a-1][b-1] ++;
        }

        vector<vector<int> > table(n, vector<int>(n,0));
        for(int i=0; i<n-1; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                int sum = 0;
                for(int k=0; k<n; k++)
                    sum += graph[i][k] + graph[j][k];
                table[i][j] = sum - graph[i][j];
                //table[j][i] = table[i][j];
            }
        }


        for(int query_value:queries)
        {
            int answer = 0;
            for(int i=0; i<n-1; i++)
            {
                for(int j=i+1; j<n; j++)
                {
                    if(query_value < table[i][j])
                        answer ++;
                }
            }
            return_vec.push_back(answer);
        }



        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
                cout<< table[i][j] << " ";
            cout<<endl;
        }
            

        return return_vec;
    }

    
    vector<int> countPairs_2(int n, vector<vector<int>>& edges, vector<int>& queries) {
        vector<int> degree(n);
        unordered_map<int, int> cnt;
        for (auto edge : edges) {
            int x = edge[0] - 1, y = edge[1] - 1;
            if (x > y) {
                swap(x, y);
            }
            degree[x]++;
            degree[y]++;
            cnt[x * n + y]++;
        }

        vector<int> arr = degree;
        vector<int> ans;
        sort(arr.begin(), arr.end());
        for (int bound : queries) {
            int total = 0;
            for (int i = 0; i < n; i++) {
                int j = upper_bound(arr.begin() + i + 1, arr.end(), bound - arr[i]) - arr.begin();
                total += n - j;
            }
            for (auto it = cnt.begin(); it != cnt.end(); ++it) {
                int val = it->first;
                int freq = it->second;
                
                int x = val / n;
                int y = val % n;
                
                if (degree[x] + degree[y] > bound && degree[x] + degree[y] - freq <= bound) {
                    total--;
                }
            }

            ans.emplace_back(total);
        }

        return ans;
    }

};





int main()
{
    int n = 4;
    vector<vector<int>> edges = {{1,2},{2,4},{1,3},{2,3},{2,1}};
    vector<int> queries = {2,3};

    Solution method;
    vector<int> res = method.countPairs_2(n, edges, queries);

    for (auto i : res)
    {
            cout << i << " ";
    }
    
    return 0;
}


