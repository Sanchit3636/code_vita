#include<bits/stdc++.h>
#include<thread>
#include<vector>

using namespace std;

// void multiplyElement(int row, int col, vector<vector<int>>& matA, vector<vector<int>>& matB, vector<vector<int>>& result){
void multiplyElement(int row, int col, const std::vector<std::vector<int>>& matA, 
                  const std::vector<std::vector<int>>& matB, 
                  std::vector<std::vector<int>>& result){

    int sum = 0;

    for(int i = 0;i < matB.size();i++){
        sum += (matA[row][i] * matB[i][col]);
    }

    result[row][col] = sum;

}

int main(){
    cout<<"........................................................"<<endl;
    cout<<"..........Matrix Multiplication using Multithreading...."<<endl;
    cout<<"........................................................"<<endl;

    int rowsA, colsA, colsB;
    cout<<"Enter the number of rows for Matrix A: ";
    cin >> rowsA;
    cout<<"Enter the columns for Matrix A (and rows for Matrix B): ";
    cin >> colsA;
    cout<<"Enter the number of columns for Matrix B: ";
    cin >> colsB;

    vector<vector<int>> matA(rowsA, vector<int>(colsA));
    vector<vector<int>> matB(colsA, vector<int>(colsB));

    vector<vector<int>> result(rowsA, vector<int>(colsB, 0));

    cout<<"Enter the elements of Matrix A: "<<endl;
    for(int i = 0;i < rowsA;i++){
        for(int j = 0;j < colsA;j++){
            cin >> matA[i][j];
        }
    }
    
    cout<<"Enter the elements of Matrix B: "<<endl;
    for(int i = 0;i < colsA;i++){
        for(int j = 0;j < colsB;j++){
            cin >> matB[i][j];
        }
    }
    vector<thread> threads;

    for(int i = 0;i < rowsA;i++){
        for(int j = 0;j < colsB;j++){
            threads.emplace_back(multiplyElement, i, j, std::cref(matA), std::cref(matB), std::ref(result));
        }
    }

    for(auto &t : threads){
        if(t.joinable()){
            t.join();
        }
    }

    cout<<"................................................................................."<<endl;
    cout<<"Resultant Matrix: "<<endl;

    for(int i = 0;i < rowsA;i++){
        for(int j = 0;j < colsB;j++){
            cout<<result[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<".................................................................."<<endl;

    return 0;
}