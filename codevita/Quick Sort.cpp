#include<bits/stdc++.h>
using namespace std;
using namespace chrono;

int partition(vector<int>& arr, int lo, int hi){
    int pivot = arr[hi];

    int i = lo-1;

    for(int j = lo;j < hi;j++){
        if(arr[j] < pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i+1], arr[hi]);

    return i+1;
}

void quickSort(vector<int>& arr, int lo, int hi){
    if(lo < hi){
        int pi = partition(arr, lo, hi);
        quickSort(arr, lo, pi-1);
        quickSort(arr, pi+1, hi);
    }
}

vector<int> generateRandomArray(int n, int minVal, int maxVal){
    vector<int> arr(n);

    for(int i = 0;i < n;i++){
        arr[i] = rand()%(maxVal-minVal+1) + minVal;
    }

    return arr;
}

int main(){
    const int n = 500;

    const int minVal = 0;
    const int maxVal = 10000;

    srand(time(0));

    vector<int> arr = generateRandomArray(n, minVal, maxVal);
    cout<<"Orignal array is : "<<endl;
    for(int i = 0;i < arr.size();i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    auto start = high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<nanoseconds>(stop - start);
    cout<<"Sorted array is : "<<endl;
    for(int i = 0;i < arr.size();i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    cout<<"QuickSort completed in "<<duration.count()<<" nanoseconds."<<endl;
    return 0;
}