//
// Created by Assaf-Haik-Barouch on 06/01/2018.
//

#ifndef DS_WET_4_HASHTABLE_H
#define DS_WET_4_HASHTABLE_H

#include "linkedList.h"
#include "Hashable.h"
#include "funcsLib.h"

//all used T must have the method int hash()
template<typename T>
class HashTable{
private:
    //the array having the table, each cell has a list of elements
    List<T>* table;
    //the size of the table. always a power of 2
    int size;
    //the number of elements in the table. we will rehash if it's equal to the size
    int num_of_elements;

    void reHash();

    int hashFunc(int hash);

public:
    //make a table with a size that's the closest power of 10 to n
    HashTable(int n):size(funcsLib::closestPowerOfTwo(n)), table(NULL), num_of_elements(0){
        table = new List<T>[size];
    }

    ~HashTable();

    T* findElement(int hash);
    T* findElement(T& info);

    void addElement(T& e);

    int getSize(){
        return size;
    }

    int getNumOfElements(){
        return num_of_elements;
    }




};
template<typename T>
HashTable<T>::~HashTable(){
    delete[] table;
}

template<typename T>
int HashTable<T>::hashFunc(int hash){
    return hash%size;
}

//find an element by it's hash value
//return NULL if the element is not there
template<typename T>
T* HashTable<T>::findElement(int hash) {
    //find the correct cell for the element
    List<T>& cell = table[hashFunc(hash)];

    //if there are no elements in the cell, return NULL
    if(cell.getSize() == 0){
        return NULL;
    }

    //find the element in the cell that has the unique hash value
    typename List<T>::Iterator found = cell.find(Equals<T>(hash));

    //if the iterator points to the cell's list end, the element is not in the table
    if(found == cell.end()){
        //if the element is not in the table, return NULL
        return NULL;
    }

    //otherwise, the correct element was found, so return it
    return &(*found);
}

//find an element
//return NULL if the element is not there
template<typename T>
T* HashTable<T>::findElement(T &info) {
    //just use the function with the hash value
    return findElement(info.hash());
}

//add an element to the table
template<typename T>
void HashTable<T>::addElement(T &e) {
    //find the correct cell for the element
    List<T>& cell = table[hashFunc(e.hash())];


    //insert the element to the end of the cell's list
    cell.insert(&e);

    //update number of elements
    ++num_of_elements;

    //if the table has as many elements as it's size, reHash (resize and stuff)
    if(num_of_elements == size){
        reHash();
    }
}

//resize the table by increasing the size by 2
template<typename T>
void HashTable<T>::reHash() {
    //save the old table array and the old size
    List<T>* old_table_array = table;
    int old_size = size;

    //increase the size by 2 times and create a new array
    size *= 2;
    table = new List<T>[size];

    //for each cell in the old table
    for(int i=0; i<old_size; i++){
        //for each element in the cell
        for(typename List<T>::Iterator it = old_table_array[i].begin(); it != old_table_array[i].end(); it++){
            //add the element to the new table
            addElement(*it);
        }
    }

    //after moving everything to the new array, destroy the old one
    delete[] old_table_array;
}


#endif //DS_WET_4_HASHTABLE_H
