//
// Created by oded on 04/01/18.
//

#ifndef DS_WET_4_TRAININGGROUP_H
#define DS_WET_4_TRAININGGROUP_H


#include <clocale>
#include "Gladiator.h"
#include "CompGlads.h"

class TrainingGroup {
public:
    TrainingGroup(int ID) : ID(ID), numOfGladiators(0), isConquered(false), gladiators(NULL) {
        CompGladsByLevel<Gladiator>* comp_lv = new CompGladsByLevel<Gladiator>();
        gladiators = new SplayRankTree<Gladiator>(comp_lv);
    }

    ~TrainingGroup() {
        delete gladiators;
    }

    /**************NOT FINISHED**********************/
    void insertGladiator(int gladiatorID, int score) {
        Gladiator* new_gladiator = new Gladiator(gladiatorID);
        gladiators->insert(new_gladiator,score);
        /**************NOT FINISHED**********************/
        /**************NOT FINISHED**********************/
        /**************NOT FINISHED**********************/
    }

    bool isLost() {
        return isConquered;
    }

    int getNumOfGladiators() {
        return numOfGladiators;
    }

private:
    int ID;
    int numOfGladiators;
    SplayRankTree<Gladiator>* gladiators;
    bool isConquered;
};


#endif //DS_WET_4_TRAININGGROUP_H
