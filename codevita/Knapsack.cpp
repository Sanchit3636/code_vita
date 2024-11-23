#include<iostream>
using namespace std;


int max(int a, int b){
    return (a > b) ? a : b;
}

int matrix(int w[], int p[], int n ,int cap){
    int mat[n+1][cap+1];

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= cap; j++){
            if(i == 0 || j == 0){
                mat[i][j] = 0;
            }

            else if(w[i-1] <= j){
               mat[i][j] = max(mat[i-1][j] , p[i-1]+mat[i-1][j-w[i-1]]);
            }
            else{
                mat[i][j] = mat[i-1][j];
            }
            cout << mat[i][j] << " ";
        }
        cout<<endl;
    }
    int profit = 0;
    int i = n;
    int j = cap;
    while(i > 0 && j > 0){
        if(mat[i][j] != mat[i-1][j]){
            profit += p[i-1];
            j -= w[i-1];
        }
        i--;
    }
    cout<<"Max Profit: "<<profit<<endl;
    return mat[n][cap];
}
  
int main(){
    int n ;
    cout<<"Enter number of weights: ";
    cin>>n;
    int w[n];
    cout<<"Enter value of weights: ";
    for(int i = 0; i < n; i++){
        cin>>w[i];
    }
        
    int p[n];
        cout<<"Enter value of profit: ";
    for(int i = 0; i < n; i++){
        cin>>p[i];
    }
    matrix( w, p, n, 5);
    return 0;
}
