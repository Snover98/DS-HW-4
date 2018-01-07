//
// Created by Assaf-Haik-Barouch on 07/01/2018.
//

#ifndef DS_WET_4_SPLAYSCORETREE_H
#define DS_WET_4_SPLAYSCORETREE_H

//
// Created by oded on 04/01/18.
//

#ifndef DS_WET_4_SPLAYTREE_H
#define DS_WET_4_SPLAYTREE_H

#include "binScoreTree.h"
#include "TreeNode.h"

template <class T>
class SplayScoreTree: public BinScoreTree<T>{
private:
    //the rolls used in the splay
    //when t's parent is the root and t is a left son
    void zig(ScoreTreeNode<T>* t);
    //when t's parent is the root and t is a right son
    void zag(ScoreTreeNode<T>* t);
    //t is the left son of a left son
    void zigZig(ScoreTreeNode<T>* t);
    //t is the right son of a right son
    void zagZag(ScoreTreeNode<T>* t);
    //t is the right son of a left son
    void zigZag(ScoreTreeNode<T>* t);
    //t is the left son of a right son
    void zagZig(ScoreTreeNode<T>* t);
    //the splay - moving a node to the root
    void splay(ScoreTreeNode<T>* t);

public:
    SplayScoreTree(Compare<T>* c):BinScoreTree<T>(c){}

    //find node with relevant info. returns NULL if there is none
    T* find(T& info);

    //find node with highest info value the tree. returns NULL if there is none
    T* findMax();

    //find node with lowest info value the tree. returns NULL if there is none
    T* findMin();

    //insert node with relevant info. returns NULL if there it already exists
    void insert(T& info);

    //removes the node with relevant info. returns false if it doesn't exist, true otherwise.
    bool remove(T& info);
//
//    //join two trees, where every node in tree2 has a higher info value than those in this tree
//    void join(SplayScoreTree tree2);
//
//    //split the tree in accordance to the inserted pivot
//    SplayScoreTree split(T& pivot);
};

template<class T>
T* SplayScoreTree<T>::find(T& info){
    //if the tree is empty, return NULL
    if(this->isEmpty()){
        return NULL;
    }

    //find the node or the closest one in value if it does not exist
    ScoreTreeNode<T>* found = this->findNode(info, this->root);

    //move the found node to the root
    splay(found);

    //if it has the correct info, return it
    if(this->comp(info, found->info) == 0){
        return &(found->info);
    }

    //otherwise, it was not found so return NULL
    return NULL;
}

template<class T>
T* SplayScoreTree<T>::findMax() {
    //return NULL if the tree is empty
    if(this->isEmpty()){
        return NULL;
    }

    //find the max node
    ScoreTreeNode<T>* max_node = this->findMaxNode(this->root);

    //move the max node to the root
    splay(max_node);

    //return the max info
    return &(max_node->info);
}

template<class T>
T* SplayScoreTree<T>::findMin() {
    //return NULL if the tree is empty
    if(this->isEmpty()){
        return NULL;
    }

    //find the min node
    ScoreTreeNode<T>* min_node = this->findMinNode(this->root);

    //move the min node to the root
    splay(min_node);

    //return the min info
    return &(min_node->info);
}

template<class T>
void SplayScoreTree<T>::insert(T &info) {
    //insert the info and splay the node
    splay(this->insertInfo(info));
}

template<class T>
bool SplayScoreTree<T>::remove(T& info){
    //if the tree is empty, the info is not there
    if(this->isEmpty()){
        return false;
    }

    //find the closest node and splay it
    ScoreTreeNode<T>* closest = this->findNode(info, this->root);
    splay(closest);

    //now that the closest is in the root, remove normally
    return BinScoreTree<T>::remove(info);
}

//when t's parent is the root and t is a left son
template<class T>
void SplayScoreTree<T>::zig(ScoreTreeNode<T>* x){
    ScoreTreeNode<T>* y = x->parent;

    //move x's right subtree to the parent
    if(x->right != NULL) {
        x->right->parent = y;
    }

    y->left = x->right;


    //change x's parent, it's the new root
    x->parent = NULL;

    //make x the former parent's parent
    y->parent = x;
    x->right = y;

    //update the additional fields from lowest node to highest node
    y->recalcFields();
    x->recalcFields();
}

//when x's parent is the root and x is a right son
template<class T>
void SplayScoreTree<T>::zag(ScoreTreeNode<T>* x){
    ScoreTreeNode<T>* y = x->parent;

    //move x's left subtree to the parent's right
    if(x->left != NULL) {
        x->left->parent = y;
    }
    y->right = x->left;

    //change x's parent, it's the new root
    x->parent = NULL;

    //make x the former parent's parent
    y->parent = x;
    x->left = y;

    //update the additional fields from lowest node to highest node
    y->recalcFields();
    x->recalcFields();
}

//x is the left son of a left son
template<class T>
void SplayScoreTree<T>::zigZig(ScoreTreeNode<T>* x){
    ScoreTreeNode<T>* y = x->parent;
    ScoreTreeNode<T>* z = y->parent;

    //make sure that the grandparent's parent is now x's parent (only make it x's parent if it's NULL)
    x->parent = z->parent;
    if(z->parent != NULL &&
       z->parent->left == z){
        z->parent->left = x;
    } else if(z->parent != NULL){
        z->parent->right = x;
    }

    //move the parent's right son to the grandparent's left son
    if(y->right != NULL) {
        y->right->parent = z;
    }
    z->left = y->right;

    //move x's right son to the parent's left son
    if(x->right != NULL) {
        x->right->parent = y;
    }

    y->left = x->right;

    //make the former y x's right son
    y->parent = x;
    x->right = y;

    //make the former grandparent the former parent's right son
    z->parent = y;
    y->right = z;

    //update the additional fields from lowest node to highest node
    z->recalcFields();
    y->recalcFields();
    x->recalcFields();
}

//x is the right son of a right son
template<class T>
void SplayScoreTree<T>::zagZag(ScoreTreeNode<T>* x){
    ScoreTreeNode<T>* y = x->parent;
    ScoreTreeNode<T>* z = y->parent;

    //make sure that the grandparent's parent is now x's parent (only make it x's parent if it's NULL)
    x->parent = z->parent;
    if(z->parent != NULL &&
       z->parent->left == z){
        z->parent->left = x;
    } else if(z->parent != NULL){
        z->parent->right = x;
    }

    //move the parent's left son to the grandparent's right son
    if(y->left != NULL) {
        y->left->parent = z;
    }
    z->right = y->left;

    //move x's left son to the parent's right son
    if(x->left != NULL) {
        x->left->parent = y;
    }
    y->right = x->left;

    //make the former parent x's left son
    y->parent = x;
    x->left = y;

    //make the former grandparent the former parent's left son
    z->parent = y;
    y->left = z;

    //update the additional fields from lowest node to highest node
    z->recalcFields();
    y->recalcFields();
    x->recalcFields();
}

//x is the right son of a left son
template<class T>
void SplayScoreTree<T>::zigZag(ScoreTreeNode<T>* x){
    ScoreTreeNode<T>* y = x->parent;
    ScoreTreeNode<T>* z = y->parent;

    //make sure that the grandparent's parent is now x's parent (only make it x's parent if it's NULL)
    x->parent = z->parent;
    if(z->parent != NULL &&
       z->parent->left == z){
        z->parent->left = x;
    } else if(z->parent != NULL){
        z->parent->right = x;
    }

    //move x's left son to the parent's right son
    if(x->left != NULL) {
        x->left->parent = y;
    }
    y->right = x->left;

    //move x's right son to the grandparent's left son
    if(x->right != NULL) {
        x->right->parent = z;
    }
    z->left = x->right;

    //make the former parent into x's left son
    y->parent = x;
    x->left = y;

    //make the former grandparent into x's right son
    z->parent = x;
    x->right = z;

    //update the additional fields from lowest node to highest node
    z->recalcFields();
    y->recalcFields();
    x->recalcFields();
}

//x is the left son of a right son
template<class T>
void SplayScoreTree<T>::zagZig(ScoreTreeNode<T>* x){
    ScoreTreeNode<T>* y = x->parent;
    ScoreTreeNode<T>* z = y->parent;

    //make sure that the grandparent's parent is now x's parent (only make it x's parent if it's NULL)
    x->parent = z->parent;
    if(z->parent != NULL &&
       z->parent->left == z){
        z->parent->left = x;
    } else if(z->parent != NULL){
        z->parent->right = x;
    }

    //move x's right son to the parent's left son
    if(x->right != NULL) {
        x->right->parent = y;
    }
    y->left = x->right;

    //move x's left son to the grandparent's right son
    if(x->left != NULL) {
        x->left->parent = z;
    }
    z->right = x->left;

    //make the former parent into x's right son
    y->parent = x;
    x->right = y;

    //make the former grandparent into x's left son
    z->parent = x;
    x->left = z;

    //update the additional fields from lowest node to highest node
    z->recalcFields();
    y->recalcFields();
    x->recalcFields();
}

//the splay - moving a node to the root
template<class T>
void SplayScoreTree<T>::splay(ScoreTreeNode<T>* t){
    //as long as t is not the root
    while(t->parent != NULL){
        if(t->parent->left == t){//if t is a left son
            if(t->parent->parent == NULL){//if t's parent is the root, zig
                zig(t);
            } else if(t->parent->parent->left == t->parent){//if t is the left son of a left son zigZig
                zigZig(t);
            } else{//if t is the left son of a right son zagZig
                zagZig(t);
            }
        } else{//if t is right son
            if(t->parent->parent == NULL){//if t's parent is the root, zag
                zag(t);
            } else if(t->parent->parent->right == t->parent){//if t is the right son of a right son zagZag
                zagZag(t);
            } else{//if t is the right son of a left son zigZag
                zigZag(t);
            }
        }
    }

    //update the root
    this->root = t;
}

#endif //DS_WET_4_SPLAYTREE_H




#endif //DS_WET_4_SPLAYSCORETREE_H
