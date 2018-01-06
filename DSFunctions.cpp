//
// Created by oded on 04/01/18.
//

#include "Coliseum.h"
#include "Exceptions.h"
#include "minHeap.h"
#include "library2.h"

using namespace DSExceptions;

void* init(int n, int* trainingGroupsIDs) {
    if(n<2 || trainingGroupsIDs==NULL)
        return NULL;

    void* DS;

    try {
        DS = new Coliseum(trainingGroupsIDs,n);
    } catch(std::bad_alloc& e) {
        DS = NULL;
    }

    return DS;
}

StatusType addTrainingGroup (void* DS, int trainingGroupID) {
    if(DS==NULL || trainingGroupID < 0) return INVALID_INPUT;

    Coliseum* coliseum = static_cast<Coliseum*>(DS);

    try {
        coliseum->addTrainingGroupToColiseum(trainingGroupID);
    } catch(std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    } catch(TrainingGroupAlreadyIn& e) {
        return FAILURE;
    } catch(std::exception& e) {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType addGladiator(void* DS, int gladiatorID, int score, int trainingGroup) {
    if(trainingGroup<0 || DS==NULL || gladiatorID<0 || score<0) return  INVALID_INPUT;

    Coliseum* coliseum = static_cast<Coliseum*>(DS);

    try {
        coliseum->addGladiatorToColiseum(trainingGroup,gladiatorID,score);
    } catch(std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    } catch(GladiatorAlreadyIn& e) {
        return FAILURE;
    } catch(TrainingGroupNotFound& e) {
        return FAILURE;
    } catch(std::exception& e) {
    return FAILURE;
    }

    return SUCCESS;
}

StatusType trainingGroupFight (void* DS, int trainingGroup1, int trainingGroup2, int k1, int k2) {
    if(DS==NULL || k1<=0 || k2<=0 || trainingGroup1<0 || trainingGroup2<0) return  INVALID_INPUT;

    if(trainingGroup1==trainingGroup2)
        return  FAILURE;

    Coliseum* coliseum = static_cast<Coliseum*>(DS);

    try {
        coliseum->groupsFight(trainingGroup1,k1,trainingGroup2,k2);
    } catch(std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    } catch(TrainingGroupNotFound& e) {
        return FAILURE;
    } catch(NotEnoughGladiatorsToFight& e) {
        return FAILURE;
    } catch(TrainingGroupLost& e) {
        return FAILURE;
    } catch(std::exception& e) {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType getMinTrainingGroup (void* DS, int* trainingGroup) {
    if(DS==NULL || trainingGroup==NULL) return INVALID_INPUT;

    Coliseum* coliseum = static_cast<Coliseum*>(DS);

    try {
        coliseum->getMinGroup(trainingGroup);
    } catch(ColiseumIsEmpty& e){
        return FAILURE;
    } catch(std::exception& e) {
        return FAILURE;
    }

    return SUCCESS;
}

void quit(void** DS) {
    if(DS==NULL || *DS==NULL) return;

    Coliseum* coliseum = static_cast<Coliseum*>(*DS);

    delete coliseum;
    *DS = NULL;
}

