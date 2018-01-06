//
// Created by oded on 04/01/18.
//

#include "Coliseum.h"

Coliseum::Coliseum(int* trainingGroupsIDs, int numOfGroups) {
    CompGladsByID<Gladiator>* comp_id = new CompGladsByID<Gladiator>();
    gladiators = new SplayTree<Gladiator>(comp_id);

    trainingHeap = new MinHeap(trainingGroupsIDs,numOfGroups);

    CompGladsByLevel<Gladiator>* comp_lvl = new CompGladsByLevel<Gladiator>();
    trainingTable = new HashTable<TrainingGroup>(trainingGroupsIDs,numOfGroups,comp_lvl);
}

Coliseum::~Coliseum() {
    gladiators->removeAllAndDeleteInfo();
    delete gladiators;
    delete trainingHeap;
    delete trainingTable;
}

void Coliseum::addTrainingGroupToColiseum(int trainingGroupID) {
    //check if the training group is already in the coliseum
    TrainingGroup* group = trainingTable->find(trainingGroupID);

    if(group != NULL) {
        throw TrainingGroupAlreadyIn();
    }

    //add the new training group to the table
    trainingTable->addElement(trainingGroupID);

    //add the new training group to the heap
    trainingHeap->insert(trainingGroupID);
}

void Coliseum::addGladiatorToColiseum(int trainingGroup,int gladiatorID,int score) {
    //check if the training group exists
    TrainingGroup* group = trainingTable->find(trainingGroup);

    if(group == NULL) {
        throw TrainingGroupNotFound();
    }

    //check if the gladiator exists
    Gladiator* new_gladiator = new Gladiator(gladiatorID);

    Gladiator* found_gladiator = gladiators->find(*new_gladiator);
    if(found_gladiator != NULL && found_gladiator->getID()==gladiatorID) {
        delete new_gladiator;
        throw GladiatorAlreadyIn();
    }

    //add the new gladiator to its group
    group->insertGladiator(gladiatorID,score);

    //add the new gladiator to the tree of all gladiators
    gladiators->insert(*new_gladiator);
}

void Coliseum::groupsFight(int trainingGroup1,int k1,int trainingGroup2,int k2) {
    //check if the training groups exists
    TrainingGroup* group1 = trainingTable->find(trainingGroup1);
    TrainingGroup* group2 = trainingTable->find(trainingGroup2);

    if(group1 == NULL || group2 == NULL) {
        throw TrainingGroupNotFound();
    }

    //check if we have enough gladiators in each group in order to fight
    int numOfGlads1 = group1->getNumOfGladiators();
    int numOfGlads2 = group2->getNumOfGladiators();

    if(numOfGlads1 < k1 || numOfGlads2 < k2) {
        throw NotEnoughGladiatorsToFight();
    }

    //check if one of the groups (or both) lost in a fight already
    //(and thus cant fight anymore)
    if(group1->isLost() || group2->isLost()) {
        throw TrainingGroupLost();
    }

    //get sums of the top k1/k2 gladiators for each group
    int groupBiggerSum1 = group1->getBiggerSum(k1);
    int groupBiggerSum2 = group1->getBiggerSum(k2);

    int minGroupInHeap = trainingHeap->find_min();

    /**check who won and update the loosing group.
    Also, if the looser was also the minimal in the Heap,
    we delete the minimal from the heap **/
    if(groupBiggerSum1 > groupBiggerSum2) {
        group2->lost();
        if(minGroupInHeap==trainingGroup2) {
            trainingHeap->del_min();
        }
    } else if(groupBiggerSum1 < groupBiggerSum2) {
        group1->lost();
        if(minGroupInHeap==trainingGroup1) {
            trainingHeap->del_min();
        }
    } else { //if both groups had the same sum, we need to choose the group
        // with bigger ID as the looser
        if(trainingGroup1 > trainingGroup2) {
            group1->lost();
            if(minGroupInHeap==trainingGroup1) {
                trainingHeap->del_min();
            }
        } else {
            group2->lost();
            if(minGroupInHeap==trainingGroup2) {
                trainingHeap->del_min();
            }
        }
    }
}

void Coliseum::getMinGroup(int* trainingGroup) {
    //check if a group exists in the heap of not conquered groups
    if(trainingHeap->isEmpty()) {
        throw ColiseumIsEmpty();
    } else { //put the minimal group inside the given pointer
        *trainingGroup = trainingHeap->find_min();
    }
}
