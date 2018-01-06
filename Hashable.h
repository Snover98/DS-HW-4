//
// Created by Assaf-Haik-Barouch on 06/01/2018.
//

#ifndef DS_WET_4_HASHABLE_H
#define DS_WET_4_HASHABLE_H

class Hashable{
    Hashable();

    virtual bool operator==(const Hashable& h){
        return true;
    }

    virtual int hash(){
        return 0;
    }
};

template <typename T>
class Equals{
private:
    int hash;
public:
    Equals(int h):hash(h){}

    bool operator()(T& t){
        return (t.hash() == hash);
    }

};


#endif //DS_WET_4_HASHABLE_H
