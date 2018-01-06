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
};


#endif //DS_WET_4_TREENODE_H
