//
// Created by oded on 04/01/18.
//

#include "Coliseum.h"

Coliseum::Coliseum(int* trainingGroupsIDs, int numOfGroups) {
    //create a tree for all gladiators
    CompGladsByID<Gladiator>* comp_id = new CompGladsByID<Gladiator>();
    gladiators = new SplayTree<Gladiator>(comp_id);

    //create a minHeap with all of the ids
    trainingHeap = new MinHeap(trainingGroupsIDs,numOfGroups);

    //create a hash table for the training groups
    trainingTable = new HashTable<TrainingGroup>(numOfGroups);

    //insert empty groups with the ids in the array
    initTrainingGroups(trainingGroupsIDs, numOfGroups);
}

Coliseum::~Coliseum() {
    delete trainingHeap;
    delete trainingTable;
    gladiators->removeAllAndDeleteInfo();
    delete gladiators;
}

void Coliseum::addTrainingGroupToColiseum(int trainingGroupID) {
    //check if the training group is already in the coliseum
    TrainingGroup* group = trainingTable->findElement(trainingGroupID);

    if(group != NULL) {
        throw TrainingGroupAlreadyIn();
    }

    //create the new group
    TrainingGroup* new_group = new TrainingGroup(trainingGroupID);

    //add the new training group to the table
    trainingTable->addElement(*new_group);

    //add the new training group to the heap
    trainingHeap->insert(trainingGroupID);
}

void Coliseum::addGladiatorToColiseum(int trainingGroup,int gladiatorID,int score) {
    //check if the training group exists
    TrainingGroup* group = trainingTable->findElement(trainingGroup);

    if(group == NULL) {
        throw TrainingGroupNotFound();
    }

    //check if the gladiator exists
    Gladiator* new_gladiator = new Gladiator(gladiatorID, score);

    Gladiator* found_gladiator = gladiators->find(*new_gladiator);
    if(found_gladiator != NULL && found_gladiator->getID()==gladiatorID) {
        delete new_gladiator;
        throw GladiatorAlreadyIn();
    }

    //add the new gladiator to its group
    group->insertGladiator(*new_gladiator);

    //add the new gladiator to the tree of all gladiators
    gladiators->insert(*new_gladiator);
}

void Coliseum::groupsFight(int trainingGroup1, int k1, int trainingGroup2, int k2) {
    //check if the training groups exists
    TrainingGroup* group1 = trainingTable->findElement(trainingGroup1);
    TrainingGroup* group2 = trainingTable->findElement(trainingGroup2);

    if(group1 == NULL || group2 == NULL) {
        throw TrainingGroupNotFound();
    }

    //check if we have enough gladiators in each group in order to fight
    if(group1->getNumOfGladiators() < k1 || group2->getNumOfGladiators() < k2) {
        throw NotEnoughGladiatorsToFight();
    }

    //check if one of the groups (or both) lost in a fight already
    //(and thus cant fight anymore)
    if(group1->hasLost() || group2->hasLost()) {
        throw TrainingGroupLost();
    }

    //check who the loser group is
    TrainingGroup* loser = findLoserGroup(group1, k1, group2, k2);

    //update its state
    loser->lostBattle();

    //update the id heap
    updateIdHeap();

}

TrainingGroup* Coliseum::findLoserGroup(TrainingGroup* group1, int k1, TrainingGroup* group2, int k2) {
    //get sums of the top k1/k2 gladiators for each group
    int groupBiggerSum1 = group1->getScoreSum(k1);
    int groupBiggerSum2 = group2->getScoreSum(k2);

    //set loser group (defaults to group1, but will be updated later)
    TrainingGroup* loser = group1;

    //check who won
    if(groupBiggerSum1 > groupBiggerSum2) {
        loser = group2;
    } else if(groupBiggerSum1 < groupBiggerSum2) {
        loser = group1;
    } else { //if both groups had the same sum, we need to choose the group
        // with bigger ID as the looser
        if (group1->getID() > group2->getID()) {
            loser = group1;
        } else {
            loser = group2;
        }
    }

    return loser;
}

void Coliseum::updateIdHeap() {
    //make sure that the minimum of the heap was not defeated
    //as long as the heap is not empty and the training group whose id is the minimal one was defeated
    while(!trainingHeap->isEmpty() &&
            (trainingTable->findElement(trainingHeap->getMin()))->hasLost()){
        //delete the minimal id if its group was defeated
        trainingHeap->delMin();
    }
}

void Coliseum::getMinGroup(int* trainingGroup) {
    //check if a group exists in the heap of not conquered groups
    if(trainingHeap->isEmpty()) {
        throw ColiseumIsEmpty();
    } else { //put the minimal group inside the given pointer
        *trainingGroup = trainingHeap->getMin();
    }
}

//add training groups with the ids in the array
void Coliseum::initTrainingGroups(int *trainingGroupsIDs, int numOfGroups) {
    //for each id in the array
    for(int i = 0; i < numOfGroups; i++){
        //create a group with the id
        TrainingGroup* group = new TrainingGroup(trainingGroupsIDs[i]);

        //add the group to the hash table
        trainingTable->addElement(*group);
    }
}
