#ifndef HEAL_PACK_H
#define HEAL_PACK_H

#include "item.h"

class Heal_pack: public item{
    public:
    Heal_pack(int y_, int x_, int frame_):item(y_, x_, frame_, 'H'){}

    private:

};


#endif