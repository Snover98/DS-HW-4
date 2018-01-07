//
// Created by oded on 04/01/18.
//

#ifndef DS_WET_4_TREENODE_H
#define DS_WET_4_TREENODE_H


#include <clocale>

//node struct
template<class T>
struct TreeNode {
public:
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    T& info;

    TreeNode(T& t): parent(NULL), left(NULL), right(NULL), info(t){}
    ~TreeNode(){
        parent = NULL;
        left = NULL;
        right = NULL;
    }
};

//score node struct
template<class T>
struct ScoreTreeNode{
public:
    ScoreTreeNode* parent;
    ScoreTreeNode* left;
    ScoreTreeNode* right;
    T& info;
    int score_sum;
    int subtree_size;

    ScoreTreeNode(T& t):parent(NULL), left(NULL), right(NULL), info(t), score_sum(t.getScore()), subtree_size(1){}

    ~ScoreTreeNode(){
        parent = NULL;
        left = NULL;
        right = NULL;
    }

    void recalcFields();
};

//recalculate score_sum and subtree_size
template<class T>
void ScoreTreeNode<T>::recalcFields() {
    int right_sum = 0;
    int left_sum = 0;
    int right_subtr_size = 0;
    int left_subtr_size = 0;

    //if there is a right son, take it's fields
    if(right != NULL){
        right_sum = right->score_sum;
        right_subtr_size = right->subtree_size;
    }

    //if there is a left son, take it's fields
    if(left != NULL){
        left_sum = left->score_sum;
        left_subtr_size = left->subtree_size;
    }

    //recalculate the fields
    score_sum = info.getScore() + right_sum + left_sum;
    subtree_size = 1 + right_subtr_size + left_subtr_size;
}

#endif //DS_WET_4_TREENODE_H
