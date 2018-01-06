//
// Created by Assaf-Haik-Barouch on 06/01/2018.
//

#ifndef DS_WET_4_HASHTABLE_H
#define DS_WET_4_HASHTABLE_H

#include "linkedList.h"

//all used T must have the method int hash()
template<typename T>
class HashTable{
private:
    List<T>* table;
    int size;

    int closestTen(int n);

public:
    HashTable(int n):size(n), table(NULL){
        table = new List<T>[closestTen(size)];
    }





};

//find closet (and bigger) power of 10
template<typename T>
int HashTable<T>::closestTen(int n) {
    int closest = 1;
    while(closest < n){
        closest *= 10;
    }

    return closest;
}


#endif //DS_WET_4_HASHTABLE_H
