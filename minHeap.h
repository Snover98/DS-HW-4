//
// Created by oded on 04/01/18.
//

#ifndef DS_WET_4_MINHEAP_H
#define DS_WET_4_MINHEAP_H

#include <iostream>

using namespace std;

class MinHeap {
public:
    MinHeap(int* arr, int n);
    ~MinHeap();

    //returns the minimal value in the heap
    int find_min();

    //inserts a new value to the heap
    void insert(int x);

    //deletes the minimal value in the heap
    void del_min();

    bool isEmpty() { return numOfInputs==0; }

    //for debugging
    void print_heap() {
        for(int i=1;i<=numOfInputs;i++) {
            int x = heap[i];
            cout << heap[i] << " ";
        }
    }

private:
    //sifts up a value in the heap after its insertion
    void sift_up(int last);

    //sift down after make_heap or deletion of a value from the heap
    void sift_down(int first, int last);

    //swaps two int pointers
    void swap(int* i,int* j);

    //makes the heap with a given array and its size
    void make_heap(int* arr, int n);

    //resizing the heap in case of heap overflow or heap underuse
    void resize_heap(int newSize);

    int* heap;
    int heapSize;
    int numOfInputs;
};

#endif //DS_WET_4_MINHEAP_H
