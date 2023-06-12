#ifndef ENEMY_4D_H
#define ENEMY_4D_H

#include "enemy.h"

class enemy_4d: public enemy
{
    public:
    enemy_4d(int y_value, int x_value, int frame_value):enemy(y_value, x_value, frame_value, 5, 3, 4, 'd') {}
       
    private:
    
};

#endif