//
// Created by oded on 05/01/18.
//
#include "minHeap.h"
#include "funcsLib.h"

MinHeap::MinHeap(int* arr, int n) : heap(NULL), heap_size(funcsLib::closestPowerOfTwo(n)+1), num_of_elements(n) {
    heap = new int[heap_size];
    makeHeap(arr,n);
}
MinHeap::~MinHeap() {
    delete[] heap;
}

int MinHeap::getMin() {
    return heap[1];
}

void MinHeap::siftUp(int last) {
    int inserted = heap[last];
    int r = last;

    while(heap[1] != inserted && heap[r/2] > inserted) {
        swap(heap + r,heap + r/2);
        r /= 2;
    }
}

void MinHeap::siftDown(int first, int last) {
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

void MinHeap::makeHeap(int* arr, int n) {
    //we first insert all the given values to the heap array
    for(int i=0;i<n;i++) {
        heap[i+1] = arr[i];
    }

    //then we sift up from the lowest subtrees to the top
    for(int i=n/2;i>0;i--) {
        siftDown(i,n);
    }
}

void MinHeap::insert(int x) {
    //the new value is inserted to the end of the heap array
    heap[++num_of_elements] = x;

    //the new value is then sifted up to its right location in the heap
    siftUp(num_of_elements);

    //we resize the heap if it became full
    if(num_of_elements == heap_size-1) {
        resizeHeap(heap_size*2);
    }
}

void MinHeap::delMin() {
    //swapping head of heap (one to delete) with the end of the heap array
    swap(heap+1,heap+num_of_elements);
    --num_of_elements; //"deleting" the old head of heap (by lowering counter)

    //sift down the new head to its right position in the heap
    siftDown(1,num_of_elements);

    //resize if we have too much empty space
    if(num_of_elements<=(heap_size/4)) {
        resizeHeap(heap_size/2+1);
    }
}

void MinHeap::resizeHeap(int newSize) {
    int* new_heap = new int[newSize];

    //copying the old heap to the new heap
    for(int i=1;i<=num_of_elements;i++) {
        new_heap[i] = heap[i];
    }

    //deleting old heap and storing new pointer to current heap
    delete[] heap;
    heap = new_heap;
    heap_size = newSize; //updating the heap size
}

bool MinHeap::isEmpty() {
    return (num_of_elements == 0);
}

void MinHeap::printHeap() {
    for(int i=1;i<=num_of_elements;i++) {
        int x = heap[i];
        cout << heap[i] << " ";
    }
}