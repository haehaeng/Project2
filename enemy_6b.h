#ifndef ENEMY_6B_H
#define ENEMY_6B_H

#include "enemy.h"

class enemy_6b: public enemy
{
    public:
    enemy_6b(int y_value, int x_value, int frame_value):enemy(y_value, x_value, frame_value, 20, 0, 10, 'B') {}
       
    private:
    
};

#endif