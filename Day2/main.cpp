#include<bits/stdc++.h>
using namespace std;    

/*顺序查找（带哨兵*/

int linearSearch(const vector<int>& arr, int key) {
    if (arr.empty()) {
        return -1;
    }

    vector<int> temp(arr.size() + 1);
    for (int i = 0; i < (int)arr.size(); ++i) {
        temp[i + 1] = arr[i];
    }

    temp[0] = key; // 哨兵
    int i = (int)arr.size();
    while (temp[i] != key) {
        --i;
    }

    return i == 0 ? -1 : i - 1; // 转回原数组下标
}
/*二分查找（前提数组已排序）不适应于链表*/
int binarySearch(const vector<int>& arr, int key) { 
    int left = 0, right = arr.size() - 1; // 定义左右指针
    while (left <= right) {
        int mid = left + (right - left) / 2; // 计算中间索引
        if (arr[mid] == key) {
            return mid; // 返回目标元素的索引
        } else if (arr[mid] < key) {
            left = mid + 1; // 搜索右半部分
        } else {
            right = mid - 1; // 搜索左半部分
        }
    }
    return -1; // 未找到目标元素
}   

/*分块查找（块间有序，块内可无序）*/
int blockSearch(const vector<int>& arr, int key, int blockSize) {
    if (arr.empty() || blockSize <= 0) {
        return -1;
    }

    int n = (int)arr.size();
    int blockCount = (n + blockSize - 1) / blockSize;
    int targetBlock = -1;

    for (int b = 0; b < blockCount; ++b) {
        int start = b * blockSize;
        int end = min(start + blockSize, n) - 1;
        int blockMax = arr[start];
        for (int i = start + 1; i <= end; ++i) {
            blockMax = max(blockMax, arr[i]);
        }

        if (key <= blockMax) {
            targetBlock = b;
            break;
        }
    }

    if (targetBlock == -1) {
        return -1;
    }

    int start = targetBlock * blockSize;
    int end = min(start + blockSize, n) - 1;
    for (int i = start; i <= end; ++i) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}   

signed main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // 顺序/二分示例数组（整体有序）
    int key = 5; // 顺序/二分查找目标元素

    vector<int> blockArr = {3, 1, 4, 9, 7, 8, 12, 10, 11};
    int blockSize = 3; // 每块3个元素，块内无序，块最大值依次为4,9,12
    int blockKey = 7;  // 分块查找目标元素

    int index1 = linearSearch(arr, key);
    cout << "顺序查找: 元素 " << key << " 在索引 " << index1 << " 处找到" << endl;

    int index2 = binarySearch(arr, key);
    cout << "二分查找: 元素 " << key << " 在索引 " << index2 << " 处找到" << endl;

    int index3 = blockSearch(blockArr, blockKey, blockSize);
    cout << "分块查找: 元素 " << blockKey << " 在索引 " << index3 << " 处找到" << endl;

    return 0;
}