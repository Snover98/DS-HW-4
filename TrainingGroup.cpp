//
// Created by oded on 04/01/18.
//

#include "TrainingGroup.h"
//create a new training group with the inputted ID, with 0 glads that has not lost
TrainingGroup::TrainingGroup(int ID) :Hashable(), ID(ID), numOfGladiators(0), isConquered(false), gladiators(NULL) {
    //create the splay rank tree for the group
    CompGladsByScore<Gladiator>* comp_scr = new CompGladsByScore<Gladiator>();
    gladiators = new SplayScoreTree<Gladiator>(comp_scr);
}

TrainingGroup::~TrainingGroup() {
    delete gladiators;
}

//insert the gladiator to the score tree
void TrainingGroup::insertGladiator(Gladiator& glad) {
    ++numOfGladiators;
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