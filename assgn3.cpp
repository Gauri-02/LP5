#include<bits/stdc++.h>
#include<omp.h>

using namespace std;
using namespace std::chrono;

const int arr_size=10;
 vector<int>arr(arr_size);

int pMinVal(){
    //int n=arr.size();
    int result=arr[0];
    #pragma omp parallel for reduction(min : result)
    for(int i=0;i<arr_size;i++){
        if(result>arr[i])result=arr[i];
    }
    return result;
}

int pMaxValue(){
    int result=arr[0];
    #pragma omp parallel for reduction(max: result)
    for(int i=0;i<arr_size;i++){
        if(result < arr[i])result=arr[i];
    }
    return result;
}

int Sum(){
    int result=0;
    #pragma omp parallel for reduction(sum: result)
    for(int i=0;i<arr_size;i++){
        result+=arr[i];
    }
    return result;
}

double Average(){
    double result=0.0;
    int sum=Sum();
    result=sum/arr_size;
    return result;
}

int main(){
    for(int i=0;i<arr_size;i++){
        arr[i]=rand()%10;
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    cout<<"minVal= "<<pMinVal()<<endl;
    cout<<"Maximum value: "<<pMaxValue()<<endl;
    cout<<"Sum is : "<<Sum()<<endl;
    cout<<"Average is "<<Average()<<endl;
    
}

