//
// Created by oded on 04/01/18.
//

#ifndef DS_WET_4_COLISEUM_H
#define DS_WET_4_COLISEUM_H


#include "minHeap.h"
#include "TrainingGroup.h"
#include "splayTree.h"
#include "Exceptions.h"

using namespace DSExceptions;

class Coliseum {
public:
    //inits the coliseum (the whole system)
    Coliseum(int* trainingGroupsIDs, int numOfGroups);

    //deletes the coliseum (the whole system)
    ~Coliseum();

    //adds a group to the coliseum
    void addTrainingGroupToColiseum(int trainingGroupID);

    //adds a gladiator to the coliseum
    void addGladiatorToColiseum(int trainingGroup,int gladiatorID,int score);

    //activates a fight between two groups and updates the coliseum
    void groupsFight(int trainingGroup1,int k1,int trainingGroup2,int k2);

    //returns the minimal group ID in the coliseum that did no lose in any fight
    void getMinGroup(int* trainingGroup);
private:
    MinHeap* trainingHeap;
    HashTable<TrainingGroup>* trainingTable;
    SplayTree<Gladiator>* gladiators;
};


#endif //DS_WET_4_COLISEUM_H
