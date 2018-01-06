//
// Created by Assaf-Haik-Barouch on 06/01/2018.
//

#ifndef DS_WET_4_BINSCORETREE_H
#define DS_WET_4_BINSCORETREE_H

#include "genericFunction.h"
#include "TreeNode.h"
#include "funcsLib.h"


template<class T>
class BinScoreTree {
protected:
    //tree root
    ScoreTreeNode<T>* root;

    //comparison function
    Compare<T>& comp;

    /* * * * * * * * * * * * *\
    |* CLASS INNER FUNCTIONS *|
    \* * * * * * * * * * * * */
    //switch the info of two nodes
    void switchNodes(ScoreTreeNode<T>* t1, ScoreTreeNode<T>* t2);

    //find the node with the inputted info. returns the closest node if the info is not in the tree
    ScoreTreeNode<T>* findNode(T& info, ScoreTreeNode<T>* start);

    //find the maximal node of the sub-tree start
    ScoreTreeNode<T>* findMaxNode(ScoreTreeNode<T>* start);

    //find the minimal node of the sub-tree start
    ScoreTreeNode<T>* findMinNode(ScoreTreeNode<T>* start);

    //insert a node into the sub-tree 'start'
    void insertNode(ScoreTreeNode<T>* t, ScoreTreeNode<T>* start);
    //insert info into the tree and return it's node
    ScoreTreeNode<T>* insertInfo(T& info);

    //update score_sum and subtree_size all the way up
    void updateParents(ScoreTreeNode<T>* t, bool is_added);

    //remove a node
    void removeNode(ScoreTreeNode<T>* t);

    //removing all nodes + deleting all inner info
    void removeAllNodesAndDeleteInfo(ScoreTreeNode<T>* p);

    //removing all nodes without deleting the info inside the nodes
    void removeAllNodes(ScoreTreeNode<T>* p);

    //the recursive functions that run a function recursively in a certain order (regarding all the orders)
    void recursiveInorder(ScoreTreeNode<T>* p, Func<T>& func);

    void recursivePreorder(ScoreTreeNode<T>* p, Func<T>& func);

    void recursivePostorder(ScoreTreeNode<T>* p, Func<T>& func);

    void recursiveInverseOrder(ScoreTreeNode<T>* p, Func<T>& func);

public:
    //normal constructor
    BinScoreTree(Compare<T>* c) : root(NULL), comp(*c) {}

    ~BinScoreTree();

    //Checks if the tree is empty
    bool isEmpty() const { return root == NULL; }

    //find node with relevant info. returns NULL if there is none
    virtual T* find(T& info);

    //find node with highest info value the tree. returns NULL if there is none
    virtual T* findMax();

    //find node with lowest info value the tree. returns NULL if there is none
    virtual T* findMin();

    //insert node with relevant info. returns NULL if there it already exists
    virtual void insert(T& info);

    //removes the node with relevant info. returns false if it doesn't exist, true otherwise.
    virtual bool remove(T& info);

    //remove all nodes from binary tree
    void removeAll();

    //remove all nodes from binary tree and deletes  the info too (assuming the
    // info was allocated using 'new' - we delete the info using 'delete'
    void removeAllAndDeleteInfo();


    //different orders to run a function on the tree's nodes
    void Inorder(Func<T>& func);

    void Preorder(Func<T>& func);

    void Postorder(Func<T>& func);

    void InverseOrder(Func<T>& func);
};

template<class T>
BinScoreTree<T>::~BinScoreTree(){
    //empty the tree and delete the comparison functor
    removeAll();
    delete &comp;
}

template<class T>
T* BinScoreTree<T>::find(T& info) {
    //check if the tree is empty
    if(isEmpty()){
        return NULL;
    }

    //search for a node with the info
    ScoreTreeNode<T>* found = findNode(info, root);
    //if the found node was the correct one
    if(comp(found->info, info) == 0){
        return &(found->info);
    }

    //otherwise, there is no node with the info
    return NULL;
}

template<class T>
T* BinScoreTree<T>::findMax() {
    //check if the tree is empty
    if(isEmpty()){
        return NULL;
    }
    return &(findMaxNode(root)->info);
}

template<class T>
T* BinScoreTree<T>::findMin() {
    //check if the tree is empty
    if(isEmpty()){
        return NULL;
    }
    return &(findMinNode(root)->info);
}

template<class T>
void BinScoreTree<T>::insert(T& info) {
    //use the inner function
    insertInfo(info);
}

template<class T>
bool BinScoreTree<T>::remove(T& info) {
    //the info cannot be in the tree if it's empty
    if(isEmpty()) {
        return false;
    }

    //find the node
    ScoreTreeNode<T>* t = findNode(info, root);

    //if the info is not in the tree
    if(comp(info, t->info) != 0){
        return false;
    }

    //remove t
    removeNode(t);
    return true;
}

template<class T>
void BinScoreTree<T>::removeAll() {
    //use the recursive function
    removeAllNodes(root);
    root = NULL;
}

template<class T>
void BinScoreTree<T>::removeAllNodes(ScoreTreeNode<T>* p) {
    //check for NULL pointer
    if (p == NULL){
        return;
    }

    //remove for the left and right children
    removeAllNodes(p->left);
    removeAllNodes(p->right);

    //delete the node
    delete p;
}

template<class T>
void BinScoreTree<T>::removeAllAndDeleteInfo() {
    //use the recursive function
    removeAllNodesAndDeleteInfo(root);
    root = NULL;
}

template<class T>
void BinScoreTree<T>::removeAllNodesAndDeleteInfo(ScoreTreeNode<T>* p) {
    //check for NULL pointer
    if(p == NULL){
        return;
    }

    //remove for the left and right children
    removeAllNodesAndDeleteInfo(p->left);
    removeAllNodesAndDeleteInfo(p->right);

    //delete the node and it's info
    delete &(p->info);
    delete p;
}

template<class T>
void BinScoreTree<T>::Inorder(Func<T>& func) {
    //use the recursive function
    recursiveInorder(root, func);
}

template<class T>
void BinScoreTree<T>::recursiveInorder(ScoreTreeNode<T>* p, Func<T>& func) {
    //check for NULL pointer
    if (p == NULL){
        return;
    }

    //do for the left, then this, then the right
    recursiveInorder(p->left, func);
    func(p->info);
    recursiveInorder(p->right, func);
}

template<class T>
void BinScoreTree<T>::Postorder(Func<T>& func) {
    //use the recursive function
    recursivePostorder(root, func);
}

template<class T>
void BinScoreTree<T>::recursivePostorder(ScoreTreeNode<T>* p, Func<T>& func) {
    //check for NULL pointer
    if (p == NULL){
        return;
    }

    //do for the left, then the right, then this
    recursivePostorder(p->left, func);
    recursivePostorder(p->right, func);
    func(p->info);
}

template<class T>
void BinScoreTree<T>::Preorder(Func<T>& func) {
    //use the recursive function
    recursivePreorder(root, func);
}

template<class T>
void BinScoreTree<T>::recursivePreorder(ScoreTreeNode<T>* p, Func<T>& func) {
    //check for NULL pointer
    if (p == NULL){
        return;
    }

    //do for this, then the left, then the right,
    func(p->info);

    recursivePreorder(p->left, func);

    recursivePreorder(p->right, func);
}

template<class T>
void BinScoreTree<T>::InverseOrder(Func<T>& func){
    //use the recursive function
    recursiveInverseOrder(root, func);
}

template<class T>
void BinScoreTree<T>::recursiveInverseOrder(ScoreTreeNode<T>* p, Func<T>& func) {
    //check for NULL pointer
    if (p == NULL){
        return;
    }

    //do for the right, then this, then the left
    recursiveInverseOrder(p->right, func);
    func(p->info);
    recursiveInverseOrder(p->left, func);
}

template<class T>
void BinScoreTree<T>::switchNodes(ScoreTreeNode<T> *t1, ScoreTreeNode<T> *t2) {
    //switch left children
    if(t1->left != NULL){
        //update with removal and then switch
        updateParents(t1->left, false);
        t1->left->parent = t2;

        //now update for the new parents
        updateParents(t1->left, true);
    }
    if(t2->left != NULL){
        //update with removal and then switch
        updateParents(t2->left, false);
        t2->left->parent = t1;

        //now update for the new parents
        updateParents(t2->left, true);
    }
    funcsLib::swap(t1->left, t2->left);

    //switch right children
    if(t1->right != NULL){
        //update with removal and then switch
        updateParents(t1->right, false);
        t1->right->parent = t2;

        //now update for the new parents
        updateParents(t1->right, true);
    }
    if(t2->right != NULL){
        //update with removal and then switch
        updateParents(t2->right, false);
        t2->right->parent = t1;

        //now update for the new parents
        updateParents(t2->right, true);
    }
    funcsLib::swap(t1->right, t2->right);


    //update with removal and then switch
    updateParents(t1, false);
    updateParents(t2, false);
    //switch parents
    if(t1->parent != NULL){
        if(t1->parent->right == t1){
            t1->parent->right = t2;
        } else{
            t1->parent->left = t2;
        }
    }
    if(t2->parent != NULL){
        if(t2->parent->right == t2){
            t2->parent->right = t1;
        } else{
            t2->parent->left = t1;
        }
    }
    funcsLib::swap(t1->parent, t2->parent);
    //now update for the new parents
    updateParents(t1, true);
    updateParents(t2, true);

    //if one of them is the root, change the root
    if(root == t1){
        root = t2;
    } else if(root == t2){
        root = t1;
    }
}

template<class T>
ScoreTreeNode<T>* BinScoreTree<T>::findNode(T &info, ScoreTreeNode<T> *start){
    ScoreTreeNode<T>* curr = start;

    while(curr != NULL) {
        //if this is the node
        if(comp(info, curr->info) == 0) {
            return curr;
        }
        //if the info is less, go right if possible
        if(comp(info, curr->info) > 0) {
            if(curr->right == NULL){//if there is no node with the info, return the closet one possible
                return curr;
            } else {
                curr = curr->right;
            }
        } else {//else, go left if possible
            if(curr->left == NULL){//if there is no node with the info, return the closet one possible
                return curr;
            } else {
                curr = curr->left;
            }
        }
    }
    //if none of the above happened, the info isn't in the tree
    return NULL;
}

template<class T>
ScoreTreeNode<T>* BinScoreTree<T>::findMaxNode(ScoreTreeNode<T> *start){
    //check for NULL pointer
    if(isEmpty()){
        return NULL;
    }

    //start from the start
    ScoreTreeNode<T>* curr = start;

    //go as far right as possible
    while (curr->right != NULL) {
        curr = curr->right;
    }
    return curr;
}

template<class T>
ScoreTreeNode<T>* BinScoreTree<T>::findMinNode(ScoreTreeNode<T> *start){
    //check for NULL pointer
    if(isEmpty()){
        return NULL;
    }

    //start from the start
    ScoreTreeNode<T>* curr = start;

    //go as far left as possible
    while (curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

template<class T>
void BinScoreTree<T>::insertNode(ScoreTreeNode<T> *t, ScoreTreeNode<T> *start){
    //find the closest node
    ScoreTreeNode<T>* closest = findNode(t->info, start);

    //if the there is no node with the same info
    if(comp(t->info, closest->info) != 0){
        if(comp(t->info, closest->info) < 0){  //if it should be to the left of the closest
            closest->left = t;
        } else {    //if it should be to the right of the closest
            closest->right = t;
        }
        t->parent = closest;
        //update the parents' info
        updateParents(t, true);
    } else {    //if there is another node with the same info, put this node to the right of it
        if(closest->right == NULL){ //if the closest node has no right child
            closest->right = t;
            t->parent = closest;
            //update the parents' info
            updateParents(t, true);
        } else {    //otherwise, insert t to the right of the closest
            insertNode(t, closest->right);
        }
    }
}
//update the node's parent when adding/removing it
//is_added==true when we are adding, and is_added==false when we are removing
template<class T>
void BinScoreTree<T>::updateParents(ScoreTreeNode<T>* t, bool is_added){
    //the score we'll add to each parent
    int added_score = t->info.getScore();
    int added_size = 1;

    //if the node is being removed
    if(!is_added){
        added_score *= -1;
        added_size *= -1;
    }

    //var for current parent
    ScoreTreeNode<T>* cur_parent = t->parent;

    //until you get to the root (including), do the following
    while(cur_parent != NULL){
        //update score_sum and subtree size
        cur_parent->score_sum += added_score;
        cur_parent->subtree_size += added_size;

        //move to the next parent
        cur_parent = cur_parent->parent;
    }
}

template<class T>
ScoreTreeNode<T>* BinScoreTree<T>::insertInfo(T &info){
    //create the node
    ScoreTreeNode<T>* t = new ScoreTreeNode<T>(info);

    //If this is an empty tree
    if(isEmpty()) {
        root = t;
        return t;
    }

    insertNode(t, root);
    return t;
}

template<class T>
void BinScoreTree<T>::removeNode(ScoreTreeNode<T> *t){
    //if the node is a leaf
    if(t->right == NULL && t->left == NULL){
        //update the parent's values before removal
        updateParents(t, false);

        //remove the node from it's parent, if it has one
        if(t->parent != NULL){
            if(t->parent->left == t){
                t->parent->left = NULL;
            } else {
                t->parent->right = NULL;
            }
        } else {
            root = NULL;
        }

        //delete the node
        t->parent = NULL;
        delete t;

        return;
    }

    //if the node only has one child (if we got here we know that it has children)
    if(t->left == NULL || t->right == NULL) {
        //update the parent's values before removal
        updateParents(t, false);

        //save the child
        ScoreTreeNode<T> *child = (t->left != NULL) ? t->left : t->right;

        //replace the node with it's child in its parent, if it has one
        if(t->parent != NULL){
            if (t->parent->left == t) {
                t->parent->left = child;
            } else {
                t->parent->right = child;
            }
        } else {
            root = child;
        }

        child->parent = t->parent;

        //delete the node
        t->left = NULL;
        t->right = NULL;
        t->parent = NULL;
        delete t;

        return;
    }

    //if the node has 2 children (happens if we got here)
    //find the following node
    ScoreTreeNode<T>* t_follower = findMinNode(t->right);
    //switch between them
    switchNodes(t, t_follower);

    //remove t again
    removeNode(t);
}


#endif //DS_WET_4_BINSCORETREE_H
