#ifndef LEVELUP_BULLET_H
#define LEVELUP_BULLET_H

#include "item.h"

class Levelup_bullet: public item
{
    public:
    Levelup_bullet(int y_value, int x_value, int frame_value):item(y_value, x_value, frame_value,'L') {}


    private:
    
};

#endif