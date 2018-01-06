//
// Created by oded on 05/01/18.
//
#include "minHeap.h"

MinHeap::MinHeap(int* arr, int n) : heap(new int[2*n+1]), heapSize(2*n+1), numOfInputs(n) {
    make_heap(arr,n);
}
MinHeap::~MinHeap() {
    delete[] heap;
}

int MinHeap::find_min() {
    return heap[1];
}

void MinHeap::sift_up(int last) {
    int inserted = heap[last];
    int r = last;

    while(heap[1] != inserted && heap[r/2] > inserted) {
        swap(heap + r,heap + r/2);
        r /= 2;
    }
}

void MinHeap::sift_down(int first, int last) {
    for (int r = first; r <= last/2;){
        if (2*r == last){ /* r has one child at 2*r  */
            if (heap[r] > heap[2*r]) {
                swap(heap + r, heap + 2 * r);
            }
            r *= 2;
        } else {/* r has two children at 2*r and 2*r+1  */
            if (heap[r]  >  heap[2*r] && heap[2*r] <=  heap[2*r+1]){
                swap(heap+r, heap+2*r);
                r *= 2;
            }
            else if (heap[r] > heap[2*r + 1] && heap[2*r + 1] <= heap[2*r]){
                swap(heap+r, heap+2*r+1);
                r = r*2+1;

            }
            else break;
        }
    }
}

void MinHeap::swap(int* i,int* j) {
    int n = *i;
    *i=*j;
    *j=n;
}

void MinHeap::make_heap(int* arr, int n) {
    //we first insert all the given values to the heap array
    for(int i=0;i<n;i++) {
        heap[i+1]=arr[i];
    }

    //then we sift up from the lowest subtrees to the top
    for(int i=n/2;i>0;i--) {
        sift_down(i,n);
    }
}

void MinHeap::insert(int x) {
    //the new value is inserted to the end of the heap array
    heap[++numOfInputs] = x;

    //the new value is then sifted up to its right location in the heap
    sift_up(numOfInputs);

    //we resize the heap if it became full
    if(numOfInputs==heapSize) {
        resize_heap(heapSize*2);
    }
}

void MinHeap::del_min() {
    //swapping head of heap (one to delete) with the end of the heap array
    swap(heap+1,heap+numOfInputs);
    --numOfInputs; //"deleting" the old head of heap (by lowering counter)

    //sift down the new head to its right position in the heap
    sift_down(1,numOfInputs);

    if(numOfInputs<=(heapSize/4)) {
        resize_heap(heapSize/2);
    }
}

void MinHeap::resize_heap(int newSize) {
    int* new_heap = new int[newSize];

    //copying the old heap to the new heap
    for(int i=1;i<=numOfInputs;i++) {
        new_heap[i] = heap[i];
    }

    //deleting old heap and storing new pointer to current heap
    delete[] heap;
    heap = new_heap;
    heapSize=newSize; //updating the heap size
}