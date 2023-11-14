
// 一个图中连通三元组的最小度数

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;


class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) { 
        int res = -1;
        int group_num = 0;
        vector<vector<int> > res_vec;

        
        std::vector<int> degree(n, 0);
        vector<vector<char>> graph(n,vector<char>(n,0));
        for(auto pair:edges)
        {
            int u = pair[0]-1, v = pair[1]-1;
            if(u>=v)
            {
                swap(u,v);
            }
            graph[u][v] = 1;
            
            degree[u]++;
            degree[v]++;
        }

        
        for(int i=0; i<graph.size(); i++)
        {
            for(int j=i+1; j<graph[i].size(); j++)
            {
                if(!graph[i][j])
                    continue;
                for(int k=j+1; k<graph[j].size(); k++)
                {
                    if(!graph[j][k])
                        continue;
                    if(graph[i][k])
                    {
                        group_num ++;
                        cout << i+1 <<" "<<j+1<<" "<<k+1<<endl;
                        res_vec.push_back(std::vector<int>{i,j,k});
                    }
                }
            }
        }
        int min_degree = INT_MAX;
        if(group_num)
        {
            for(vector<int> group:res_vec)
            {
                min_degree = min(min_degree, degree[group[0]] + degree[group[1]] + degree[group[2]] - 6);
            }
            res = min_degree;
        }

        return res;
    }

    int minTrioDegree2(int n, vector<vector<int>>& edges) {
        int res = -1;
        int group_num = 0;
        vector<vector<int> > res_vec;

        SparseGraph graph(n);
        for(auto pair:edges)
        {
            graph.addEdge(pair[0]-1, pair[1]-1);
        }

        
        for(int i=0; i<graph.List.size(); i++)
        {
            for(int j:graph.List[i])
            {
                for(int k:graph.List[j])
                {
                    //sort(graph.List[i].begin(), graph.List[i].end());
                    bool exists = std::binary_search(graph.List[i].begin(), graph.List[i].end(), k);
                    if(exists)
                    {
                        group_num ++;
                        cout << i+1 <<" "<<j+1<<" "<<k+1<<endl;
                        res_vec.push_back(std::vector<int>{i,j,k});
                    }
                }
            }
        }
        int min_degree = INT_MAX;
        if(group_num)
        {
            for(vector<int> group:res_vec)
            {
                min_degree = min(min_degree, graph.degree[group[0]] + graph.degree[group[1]] +graph.degree[group[2]] - 6);
            }
            res = min_degree;
        }

        return res;
    }


    class SparseGraph{
    public:
        int V; // Number of vertices
        std::vector<std::vector<int>> List;
        std::vector<int> degree;
        SparseGraph(int numVertices) : V(numVertices) {
            List.resize(V);
            degree.resize(V);
        }

        void addEdge(int u, int v) {
            if(u>v)
            {
                int temp=u;
                u=v;
                v=temp;
            }
            auto insertPos = std::lower_bound(List[u].begin(), List[u].end(), v);
            List[u].insert(insertPos, v);
            //List[u].push_back(v);
            degree[u]++;
            degree[v]++;
        }

    };

};






int main()
{
    int n = 6;
    vector<vector<int>> edges = {{1,2},{1,3},{3,2},{4,1},{5,2},{3,6}};
    Solution method;
    int res = method.minTrioDegree(n, edges);

    
    cout << res << endl;
    
    return 0;
}




