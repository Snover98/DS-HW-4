//
// Created by Assaf-Haik-Barouch on 06/01/2018.
//

#ifndef DS_WET_4_FUNCSLIB_H
#define DS_WET_4_FUNCSLIB_H


namespace funcsLib{
    int closestPowerOfTwo(int n);

    template <typename T>
    void swap(T &n1, T &n2) // Note the &
    {
        T temp=n1; // Note use the type T
        n1=n2;
        n2=temp;
    }
}

#endif //DS_WET_4_FUNCSLIB_H
