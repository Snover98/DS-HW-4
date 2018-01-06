//
// Created by oded on 04/01/18.
//

#ifndef DS_WET_4_TRAININGGROUP_H
#define DS_WET_4_TRAININGGROUP_H


#include <clocale>
#include "Gladiator.h"
#include "CompGlads.h"

class TrainingGroup {
private:
    int ID;
    int numOfGladiators;
    SplayRankTree<Gladiator>* gladiators;
    bool isConquered;

public:
    TrainingGroup(int ID);

    ~TrainingGroup();

    void insertGladiator(int gladiatorID, int score);

    bool isLost();

    int getNumOfGladiators();


};


#endif //DS_WET_4_TRAININGGROUP_H
