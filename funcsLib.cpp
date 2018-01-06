//
// Created by Assaf-Haik-Barouch on 06/01/2018.
//

//find closet (and bigger) power of 2
int closestPowerOfTwo(int n) {
    int closest = 1;
    while(closest < n){
        closest *= 2;
    }

    return closest;
}