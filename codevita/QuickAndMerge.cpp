#include<bits/stdc++.h>
using namespace std;
using namespace chrono;

int partition(vector<int>& quickSortArr, int lo, int hi){
    int i = lo-1;
    int pivot = quickSortArr[hi];

    for(int j = lo;j < hi;j++){
        if(quickSortArr[j] < pivot){
            i++;
            swap(quickSortArr[i], quickSortArr[j]);
        }
    }

    swap(quickSortArr[i+1], quickSortArr[hi]);
    return i+1;
}
void quickSort(vector<int>& quickSortArr, int lo, int hi){
    if(lo < hi){
        int pi = partition(quickSortArr, lo, hi);
        quickSort(quickSortArr, lo, pi-1);
        quickSort(quickSortArr, pi+1, hi);
    }
}

vector<int> generateRandomArray(int n, int minVal, int maxVal){
    vector<int> quickSortArr(n);

    for(int i = 0;i < n;i++){
        quickSortArr[i] = rand()%(maxVal-minVal+1) + 1;
    }

    return quickSortArr;
}

void merge(vector<int>& mergeSortArr, int lo, int mid, int hi){
    int n1 = mid-lo+1;
    int n2 = hi-mid;

    vector<int>L(n1);
    vector<int>R(n2);

    for(int i = 0;i < n1;i++){
        L[i] = mergeSortArr[lo + i];
    }
    for(int i = 0;i < n2;i++){
        R[i] = mergeSortArr[mid + i + 1];
    }

    int i = 0;
    int j = 0;
    int k = lo;

    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            mergeSortArr[k++] = L[i++];
        }
        else{
            mergeSortArr[k++] = R[j++];
        }
    }

    while(i < n1){
        mergeSortArr[k++] = L[i++];
    }
    while(j < n2){
        mergeSortArr[k++] = R[j++];
    }
}
void mergeSort(vector<int>& mergeSortArr, int lo, int hi){
    if(lo < hi){
        int mid = lo + (hi-lo)/2;

        mergeSort(mergeSortArr, lo, mid);
        mergeSort(mergeSortArr, mid+1, hi);

        merge(mergeSortArr, lo, mid, hi);
    }
}

int main(){
    const int n = 500;
    const int minVal = 1;
    const int maxVal = 10000;

    srand(time(0));

    vector<int> arr = generateRandomArray(n, minVal, maxVal);

    vector<int> quickSortArr = arr;

    cout<<"Original array is : "<<endl;
    for(int i = 0;i < quickSortArr.size();i++){
        cout<<quickSortArr[i]<<" ";
    }
    cout<<endl;

    auto start = high_resolution_clock::now();
    quickSort(quickSortArr, 0, n-1);
    auto stop = high_resolution_clock::now();

    cout<<"Sorted array is : "<<endl;
    for(int i = 0;i < quickSortArr.size();i++){
        cout<<quickSortArr[i]<<" ";
    }
    cout<<endl;


    auto quickSortDuration = duration_cast<nanoseconds>(stop - start);

    cout<<"Quick Sort completed in "<<quickSortDuration.count()<<" nanoseconds"<<endl;


    vector<int> mergeSortArr = arr;

    start = high_resolution_clock::now();

    mergeSort(mergeSortArr, 0, n-1);

    stop = high_resolution_clock::now();

    auto mergeSortDuration = duration_cast<nanoseconds>(stop - start);
    cout<<"MergeSort completed in "<<mergeSortDuration.count()<<" nanoseconds"<<endl;

    // Compare Results
    cout << "\nComparison:" << endl;
    cout << "QuickSort Time: " << quickSortDuration.count() << " nanoseconds" << endl;
    cout << "MergeSort Time: " << mergeSortDuration.count() << " nanoseconds" << endl;

    return 0;
}