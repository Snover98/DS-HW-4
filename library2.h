//
// Created by oded on 05/01/18.
//

#ifndef DS_WET_4_LIBRARY2_H
#define DS_WET_4_LIBRARY2_H

#ifdef __cplusplus
extern "C" {
#endif

/* Return Values
* ----------------------------------- */
typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;

/* Required Interface for the Data Structure
* -----------------------------------------*/

void* init(int n, int *trainingGroupsIDs);

StatusType addTrainingGroup(void *DS, int trainingGroupID);

StatusType addGladiator(void *DS, int gladiatorID, int score, int trainingGroup);

StatusType trainingGroupFight(void *DS, int trainingGroup1, int trainingGroup2, int k1, int k2);

StatusType getMinTrainingGroup(void *DS, int *trainingGroup);

/* Description:   Quits and deletes the database.
*                DS should be set to NULL.
* Input:         DS - A pointer to the data structure.
* Output:        None.
* Return Values: None.
*/
void quit(void** DS);

#ifdef __cplusplus
}
#endif


#endif //DS_WET_4_LIBRARY2_H
