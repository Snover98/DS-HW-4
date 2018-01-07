//
// Created by Assaf-Haik-Barouch on 06/01/2018.
//

#ifndef DS_WET_4_HASHABLE_H
#define DS_WET_4_HASHABLE_H

class Hashable{
public:
    Hashable(){}

    virtual int hash(){
        return 0;
    }
};

template <typename T>
class Equals{
private:
    const int hash;
public:
    Equals(int h):hash(h){}

    const bool operator()(T& t) const{
        return (t.hash() == hash);
    }

};


#endif //DS_WET_4_HASHABLE_H
