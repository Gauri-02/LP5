#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

void bubbleSort(vector<int>&arr_copy){
    int n=arr_copy.size();
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1;j++){
            if(arr_copy[j] > arr_copy[j+1]){
                swap(arr_copy[j],arr_copy[j+1]);
            }
        }
    }
}

void PbubbleSort(vector<int>arr){
    int n=arr.size();
    for(int i=0;i<n-1;i++){
        #pragma omp parallel for
        for(int j=0;j<n-1;j++){
            if(arr[j] >arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}

int main(){
    const int size=10000;
    vector<int>arr(size),arr_copy(size);
    
    for(int i=0;i<size;i++){
        arr[i]=rand() %1000;
        arr_copy[i]=arr[i];
    }
    
    auto start=high_resolution_clock::now();
    bubbleSort(arr_copy);
    auto stop=high_resolution_clock::now();
    auto seq_bubble=duration_cast<milliseconds>(stop-start);
    
    cout<<"Sequential bubble sort: "<<seq_bubble.count()<<endl;
    
    start=high_resolution_clock::now();
    PbubbleSort(arr);
    stop=high_resolution_clock::now();
    auto par_bubble=duration_cast<milliseconds>(stop-start);
    
    cout<<"parallel bubble sort: "<<par_bubble.count()<<endl;
    
    
}

