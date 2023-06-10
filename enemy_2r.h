#ifndef ENEMY_2R_H
#define ENEMY_2R_H

#include "enemy.h"

class enemy_2r: public enemy
{
    public:
    enemy_2r(int y_value, int x_value, int frame_value):enemy(y_value, x_value, frame_value, 5, 3, 2, 'r') {}

    private:
    
};

#endif