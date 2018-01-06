//
// Created by oded on 04/01/18.
//

#include "TrainingGroup.h"
TrainingGroup::TrainingGroup(int ID) : ID(ID), numOfGladiators(0), isConquered(false), gladiators(NULL) {
    CompGladsByLevel<Gladiator>* comp_lv = new CompGladsByLevel<Gladiator>();
    gladiators = new SplayRankTree<Gladiator>(comp_lv);
}

TrainingGroup::~TrainingGroup() {
    delete gladiators;
}
/**************NOT FINISHED**********************/
void TrainingGroup::insertGladiator(int gladiatorID, int score) {
    Gladiator* new_gladiator = new Gladiator(gladiatorID);
    gladiators->insert(new_gladiator,score);
    /**************NOT FINISHED**********************/
    /**************NOT FINISHED**********************/
    /**************NOT FINISHED**********************/
}

bool TrainingGroup::isLost() {
    return isConquered;
}

int TrainingGroup::getNumOfGladiators() {
    return numOfGladiators;
}