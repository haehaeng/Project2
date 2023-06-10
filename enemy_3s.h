#ifndef ENEMY_3S_H
#define ENEMY_3S_H

#include "enemy.h"

class enemy_3s: public enemy
{
    public:
    enemy_3s(int y_value, int x_value, int frame_value):enemy(y_value, x_value, frame_value, 4, 9, 3, 's') {}

    private:
    
};

#endif