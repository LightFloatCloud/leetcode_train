#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        std::sort(candidates.begin(), candidates.end());

        int current_solution = 0;
        vector<vector<int>> return_vec;

        

        int current_numindex = 0;
        int rest_num = target;
        while(current_numindex < candidates.size())
        {
            vector<int> current_vec;
            int current_num = candidates[current_numindex];

            if(current_num > rest_num)
            {
                current_numindex ++;
                continue;
            }
            else if(current_num == rest_num)
            {
                current_numindex ++;
                current_vec.push_back(current_num);
                return_vec.push_back(current_vec);
                return return_vec;
            }
            else
            {
                current_numindex ++;

                std::vector<int> new_candidates(candidates.begin() + current_numindex, candidates.end());
                //new_candidates.erase(new_candidates.begin()+current_numindex);
                vector<vector<int>> last_return_vec = combinationSum2(new_candidates, target-current_num);
                

                //插入本递归的数
                for(auto each_return_vec_it=last_return_vec.begin(); each_return_vec_it!=last_return_vec.end(); each_return_vec_it++)
                {
                    (*each_return_vec_it).push_back(current_num);
                    std::sort((*each_return_vec_it).begin(), (*each_return_vec_it).end());
                }

                return_vec.insert(return_vec.end(), last_return_vec.begin(), last_return_vec.end());

                int repeat_num = 0;
                for(auto i:new_candidates)
                {
                    if(current_num == i)
                        repeat_num++;
                    else
                        break;
                }
                current_numindex += repeat_num;
                
            }
        }
        //将重复的数据移到后面
        std::sort(return_vec.begin(), return_vec.end());
        vector<vector<int>>::iterator ite = unique(return_vec.begin(), return_vec.end());
        //删除重复的元素
        return_vec.erase(ite, return_vec.end());

        return return_vec;
    }
};

int main()
{
    vector<int> candidates = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    int target = 27;

    Solution method;
    vector<vector<int>> res = method.combinationSum2(candidates, target);

    for (auto i : res)
    {
        for(auto ii:i)
            cout << ii <<" ";

        cout << endl;
    }
    return 0;
}

