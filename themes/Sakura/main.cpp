#include <iostream>
#include<vector>
using namespace std;


// 快速排序
// 一次排序
int count = 0;
int sort(int start, int end,vector<int> &a) {
    int low = start;
    int high =end;
        // 找到左边第一个大于a[start] 右边第一个小于a[start]
    int key =a[low];
    while(low < high) {
        while(low < high && a[high] > key) {
            high--;
        }
        while(low < high && a[low] < key) {
            low++;
        }
        if(a[low] == a[high]){
            low++;
        }
        // 然后做位置交换
        int tmp = a[low];
        a[low] = a[high];
        a[high] = tmp;
        count++;
    }
    return low;
}

void quick_sort(int start, int end, vector<int> &a) {
    if(start >= end) {
        return;
    }
    int i = sort(start, end, a);
    quick_sort(start, i-1, a);
    quick_sort(i+1, end, a);
}





int main()
{
    vector<int> a = {3,2,3,1,45,56,12};
    quick_sort(0, a.size()-1, a);
    cout << count << "前面是数" << endl;
    cout << "Hello World!" << endl;
    cout << "wo";
    return 0;
}
