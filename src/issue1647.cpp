#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minDeletions(string s) {

        map<string, int> myMap;

        for (char c : s) {
            string singleCharString(1, c);
            myMap[singleCharString] ++;
        }

        vector<int> letter_num(myMap.size(), 0);
        int count = 0;
        for (const auto& pair : myMap) {
            //std::cout << pair.first << ": " << pair.second << std::endl;
            
            letter_num[count] = pair.second;
            count ++;
            
        }

        int return_num = 0;
        sort(letter_num.begin(), letter_num.end(), std::greater<int>());
        for(int i=1; i<myMap.size(); i++)
        {
            while(letter_num[i] >= letter_num[i-1] && letter_num[i]!=0)
            {
                letter_num[i] --;
                return_num ++;
            }
        }



        return return_num;
    }
};




int main()
{
    string s = "ceabaacb";

    Solution method;
    int res = method.minDeletions(s);

    
    cout << res << endl;
    
    return 0;
}







