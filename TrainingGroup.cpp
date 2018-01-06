//
// Created by oded on 04/01/18.
//

#include "TrainingGroup.h"
//create a new training group with the inputted ID, with 0 glads that has not lost
TrainingGroup::TrainingGroup(int ID) : ID(ID), numOfGladiators(0), isConquered(false), gladiators(NULL) {
    //create the splay rank tree for the group
    CompGladsByLevel<Gladiator>* comp_lv = new CompGladsByLevel<Gladiator>();
    gladiators = new SplayRankTree<Gladiator>(comp_lv);
}

TrainingGroup::~TrainingGroup() {
    delete gladiators;
}
/**************NOT FINISHED**********************/
//insert the gladiator to the score tree
void TrainingGroup::insertGladiator(Gladiator& glad) {
    gladiators->insert(glad);
}

int TrainingGroup::getScoreSum(int num_of_top) {
    return gladiators->getScoreSum(num_of_top);
}

bool TrainingGroup::hasLost() {
    return isConquered;
}

int TrainingGroup::getNumOfGladiators() {
    return numOfGladiators;
}

int TrainingGroup::getID(){
    return ID;
}

int TrainingGroup::hash(){
    return getID();
}

void TrainingGroup::lostBattle() {
    isConquered = true;
}