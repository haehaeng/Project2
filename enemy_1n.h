#ifndef ENEMY_1N_H
#define ENEMY_1N_H

#include "enemy.h"

class enemy_1n: public enemy
{
    public:
    enemy_1n(int y_value, int x_value, int frame_value):enemy(y_value, x_value, frame_value, 10, 0, 1,'n') {}
    
    private:

};

#endif