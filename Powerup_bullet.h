#ifndef POWERUP_BULLET_H
#define POWERUP_BULLET_H

#include "item.h"

class Powerup_bullet: public item
{
    public:
    Powerup_bullet(int y_value, int x_value, int frame_value):item(y_value, x_value, frame_value,'P') {}
    

    private:
    
};

#endif