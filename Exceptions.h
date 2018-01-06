//
// Created by oded on 04/01/18.
//

#ifndef DS_WET_4_EXCEPTIONS_H
#define DS_WET_4_EXCEPTIONS_H

#include <stdexcept>

namespace DSExceptions {
    class ElementNotFound : public std::runtime_error {
    public:
        ElementNotFound() : std::runtime_error("Element not found") {}
    };
    class TrainingGroupNotFound : public std::runtime_error {
    public:
        TrainingGroupNotFound() : std::runtime_error("Element not found") {}
    };
    class TrainingGroupAlreadyIn : public std::runtime_error {
    public:
        TrainingGroupAlreadyIn() : std::runtime_error("Element is already in") {}
    };
    class NotEnoughGladiatorsInTrainingGroup : public std::runtime_error {
    public:
        NotEnoughGladiatorsInTrainingGroup() : std::runtime_error("Element is already in") {}
    };
    class GladiatorNotFound : public std::runtime_error {
    public:
        GladiatorNotFound() : std::runtime_error("Element not found") {}
    };
    class GladiatorAlreadyIn : public std::runtime_error {
    public:
        GladiatorAlreadyIn() : std::runtime_error("Element is already in") {}
    };
    class NotEnoughGladiatorsToFight : public std::runtime_error {
    public:
        NotEnoughGladiatorsToFight() : std::runtime_error("Element is already in") {}
    };
    class ColiseumIsEmpty : public std::runtime_error {
    public:
        ColiseumIsEmpty() : std::runtime_error("Element is already in") {}
    };
    class TrainingGroupLost : public std::runtime_error {
    public:
        TrainingGroupLost() : std::runtime_error("Element is already in") {}
    };

}

#endif //DS_WET_4_EXCEPTIONS_H
