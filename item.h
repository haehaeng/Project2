#ifndef ITEM_H
#define ITEM_H

#include "unit.h"

class item : public unit
{
    public:
    item(int y_, int x_, int frame_, char content_):unit(y_, x_, frame_, content_){}
    
    private:

};

#endif