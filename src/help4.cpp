// 还差capacity删除没完成

#include <iostream>
#include <string>

#include <vector>
#include <set>
#include <unordered_map>
#include <chrono>

#include <sstream>

using namespace std;

struct NeighborData {
    int localCell;
    int neighborCell;
    int useCount;
    time_t lastUsed;

    NeighborData(int localCell, int neighborCell, int useCount, time_t lastUsed)
        : localCell(localCell), neighborCell(neighborCell), useCount(useCount), lastUsed(lastUsed) {}

    // 用于std::set排序的比较函数
    bool operator<(const NeighborData& other) const {
        if (useCount == other.useCount)
            return lastUsed < other.lastUsed;
        return useCount < other.useCount;
    }
};

int main() {

    std::string line;
    int capacity = 0;
    //std::getline(std::cin, line);
    unordered_map<int, set<NeighborData>::iterator> cellMap;
    std::set<NeighborData> dataSet;

    while (getline(cin, line)) {
        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "capacity:") {
            cin >> capacity;
            cout << "Capacity set to " << capacity << endl;
        } else if (command == "write:") {
            int numWrites;
            cin >> numWrites;
            for (int i = 0; i < numWrites; ++i) {
                int localCell, neighborCell; // 读取下一行作为write的数据
                cin >> localCell >> neighborCell;

                auto it = cellMap.find(localCell);
                int evercount = 0;
                if (it != cellMap.end()) {
                    // 如果存在，先从set中删除旧的数据
                    evercount = it->second->useCount;
                    dataSet.erase(it->second);
                }
                // 插入或更新数据到set中，并更新map中的迭代器
                auto insertResult = dataSet.insert(NeighborData(localCell, neighborCell, evercount+1, std::time(nullptr)));
                cellMap[localCell] = insertResult.first;

            }
            cout << "Write completed!" << endl;
        } else if (command == "read:") {
            int localCell;
            cin >> localCell;
            // 这里可以添加处理read操作的代码
            auto it = cellMap.find(localCell);
            if (it == cellMap.end()) {
                cerr << "Can't find read!" << endl;
            }
            NeighborData readCell = *(it->second);
            dataSet.erase(it->second);

            readCell.useCount ++;
            readCell.lastUsed = std::time(nullptr);

            
            // 插入或更新数据到set中，并更新map中的迭代器
            auto insertResult = dataSet.insert(readCell);
            cellMap[localCell] = insertResult.first;


            cout << "Reading " << readCell.neighborCell << endl;
        } else if (command == "query:") {
            int localCell;
            cin >> localCell;
            auto it = cellMap.find(localCell);
            if (it != cellMap.end()) {
                const NeighborData& data = *(it->second);
                cout << "Localcell: " << data.localCell << ", Neighborcell: " << data.neighborCell
                     << ", Use Count: " << data.useCount << ", Last Used: " << data.lastUsed << endl;
            } else {
                cout << "Localcell " << localCell << " not found." << endl;
            }
        }

    }

    


    return 0;
}