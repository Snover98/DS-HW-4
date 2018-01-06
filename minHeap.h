//
// Created by oded on 04/01/18.
//

#ifndef DS_WET_4_MINHEAP_H
#define DS_WET_4_MINHEAP_H

#include <iostream>

using namespace std;

class MinHeap {
private:
    int* heap;
    int heap_size;
    int num_of_elements;

    //sifts up a value in the heap after its insertion
    void siftUp(int last);

    //sift down after make_heap or deletion of a value from the heap
    void siftDown(int first, int last);

    //swaps two int pointers
    void swap(int* i,int* j);

    //makes the heap with a given array and its size
    void makeHeap(int* arr, int n);

    //resizing the heap in case of heap overflow or heap underuse
    void resizeHeap(int newSize);

public:
    MinHeap(int* arr, int n);
    ~MinHeap();

    //returns the minimal value in the heap
    int getMin();

    //inserts a new value to the heap
    void insert(int x);

    //deletes the minimal value in the heap
    void delMin();

    bool isEmpty();

    //for debugging
    void printHeap() {
        for(int i=1;i<=num_of_elements;i++) {
            int x = heap[i];
            cout << heap[i] << " ";
        }
    }
};

#endif //DS_WET_4_MINHEAP_H
