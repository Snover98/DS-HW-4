//
// Created by oded on 04/01/18.
//

#include "Gladiator.h"

Gladiator::Gladiator(int ID, int score) : ID(ID), score(score) {}

int Gladiator::getID() {
    return ID;
}

int Gladiator::getScore() {
    return score;
}
