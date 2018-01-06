#include <iostream>
#include "minHeap.h"

void swap1(int* i,int* j) {
    int n = *i;
    *i=*j;
    *j=n;
}

void sift_down(int first, int last, int* arr) {
    for (int r = first; r <= last/2;){
        if (2*r == last){ /* r has one child at 2*r  */
            if (arr[r] > arr[2*r])
                swap1(arr+r,arr+2*r);
        }
        else {/* r has two children at 2*r and 2*r+1  */
            if (arr[r]  >  arr[2*r] && arr[2*r] <=  arr[2*r+1]){
                swap1(arr+r, arr+2*r);
                r *= 2;
            }
            else if (arr[r] > arr[2*r + 1] && arr[2*r + 1] <= arr[2*r]){
                swap1(arr+r, arr+2*r+1);
                r *= 2*r+1;
            }
            else break;
        }
    }
}

void print_arr(int* arr, int n) {
    for(int i=0;i<n;i++) {
        cout << arr[i] << " ";
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;


    int arr2[] = {6,8,12,17,0,3,10,4,5,2};
    MinHeap heap1(arr2,10);
    heap1.insert(1);
    heap1.insert(100);
    heap1.insert(50);
    heap1.insert(75);
    heap1.insert(63);
    heap1.insert(70);
    heap1.insert(55);
    heap1.insert(52);
    heap1.insert(60);
    heap1.insert(90);
    heap1.insert(80);
    heap1.insert(85);

/**
    //print_arr(arr2, 10);
    sift_down(2,10,arr2);
    //print_arr(arr2, 10);
    sift_down(1,10,arr2);
    //print_arr(arr2, 10);
    sift_down(0,10,arr2);
    print_arr(arr2, 10); **/

    return 0;
}