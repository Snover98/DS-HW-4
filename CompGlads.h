//
// Created by oded on 04/01/18.
//

#ifndef DS_WET_4_COMPGLADS_H
#define DS_WET_4_COMPGLADS_H

#include "genericFunction.h"

template<class T>
class CompGladsByID : public Compare<T>{
public:
    /*****************COMPARISON************************
     * Compares the the inputted Gladiators by their IDs
     * return values:
     * if the ids are the same, 0
     * if g1.id < g2.id, -1
     * if g1.id > g2.id, 1
     **************************************************/
    virtual int operator()(T& g1, T& g2) {
        if(g1.getID() == g2.getID()){
            return 0;
        }

        return (g1.getID() < g2.getID())? -1: 1;
    }
};

template<class T>
class CompGladsByScore : public CompGladsByID<T>{
public:
    /*****************COMPARISON************************
     * Compares the the inputted Gladiators by their Levels.
     * If they have the same level, they are compared by id IN REVERSE
     * return values:
     * if g1.level < g2.level, -1
     * if g1.level > g2.level, 1
     * if g1.level == g2.level and g1.id < g2.id, -1
     * if g1.level == g2.level and g1.id > g2.id, 1
     * if g1.level == g2.level and g1.id == g2.id, 0
     **************************************************/
    int operator()(T &g1, T& g2) {
        if(g1.getScore() == g2.getScore()){
            return CompGladsByID<T>::operator()(g1, g2);
        }

        return (g1.getScore() < g2.getScore())? -1: 1;
    }
};

#endif //DS_WET_4_COMPGLADS_H
