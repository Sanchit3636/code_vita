#include<bits/stdc++.h>
using namespace std;

int partition(vector<int>& arr, int lo, int hi){
    int pivot = arr[hi];
    int i = lo - 1;

    for(int j = lo;j < hi;j++){
        if(arr[j] < pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i+1], arr[hi]);
    return i+1;
}
int randomizedQuickPartition(vector<int>& arr, int lo, int hi){
    int randomIdx = lo + rand()%(hi - lo + 1);

    swap(arr[randomIdx], arr[hi]);
    return partition(arr, lo, hi);
}

void randomizedQuickSort(vector<int>& arr, int lo, int hi){
    if(lo < hi){
        int pi = randomizedQuickPartition(arr, lo, hi);
        randomizedQuickSort(arr, lo, pi-1);
        randomizedQuickSort(arr, pi+1, hi);
    }
}
int main(){
    vector<int> arr = {10, 7, 8, 9, 1, 5, 6};

    int n = arr.size();

    srand(time(0));

    cout<<"Original array: ";
    for(auto num : arr){
        cout<<num<<" ";
    }

    cout<<endl;

    randomizedQuickSort(arr, 0, n-1);

    cout<<"Sorted Array: ";
    for(auto num : arr){
        cout<<num<<" ";
    }
    cout<<endl;

    return 0;
}