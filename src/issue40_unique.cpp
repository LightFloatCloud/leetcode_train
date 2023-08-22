


////////vector 删除重复组合


#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
    vector<vector<int>> res = {{1,3,2},{5,6,4},{2,3,4},{1,2,3},{1,2,3},{4,5,6}};

    
    //将数据进行排序
    sort(res.begin(), res.end());

    //打印vector的内容
    for (auto i : res)
    {
        for(auto ii:i)
            cout << ii <<" ";

        cout << endl;
    }

    //将重复的数据移到后面
    vector<vector<int>>::iterator ite = unique(res.begin(), res.end());
    cout << "unique res size:" << res.size() << endl;

    //删除重复的元素
    res.erase(ite, res.end());
    cout << "erase res size:" << res.size() << endl;

    //打印vector的内容
    for (auto i : res)
    {
        for(auto ii:i)
            cout << ii <<" ";

        cout << endl;
    }
cout << endl;
    vector<vector<int>> new_candidates(res.begin() + 2, res.end());

    for (auto i : new_candidates)
    {
        for(auto ii:i)
            cout << ii <<" qaq ";

        cout << endl;
    }
    return 0;
}
