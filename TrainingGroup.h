//
// Created by oded on 04/01/18.
//

#ifndef DS_WET_4_TRAININGGROUP_H
#define DS_WET_4_TRAININGGROUP_H


#include <clocale>
#include "Gladiator.h"
#include "CompGlads.h"
#include "Hashable.h"
#include "binScoreTree.h"

class TrainingGroup : public Hashable{
private:
    int ID;
    int numOfGladiators;
    /***************************************/
    /**TODO: Change back to SplayRankTree **/
    /***************************************/
    BinScoreTree<Gladiator>* gladiators;
    bool isConquered;

public:
    TrainingGroup(int ID);

    ~TrainingGroup();

    void insertGladiator(Gladiator& glad);

    bool hasLost();

    int getNumOfGladiators();

    int getID();

    int hash();

    void lostBattle();

    int getScoreSum(int num_of_top);


};


#endif //DS_WET_4_TRAININGGROUP_H
