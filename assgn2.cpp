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


void merge(vector<int> &arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            ++i;
        }
        else
        {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void parallelMergeSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

#pragma omp parallel sections
        {
#pragma omp section
            parallelMergeSort(arr, l, m);

#pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
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
    
     start = high_resolution_clock::now();
    parallelMergeSort(arr, 0, size - 1);
    stop = high_resolution_clock::now();
    auto par_duration_merge = duration_cast<milliseconds>(stop - start);
    
}

