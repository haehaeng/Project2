#ifndef ENEMY_5A_H
#define ENEMY_5A_H

#include "enemy.h"

class enemy_5a: public enemy
{
    public:
    enemy_5a(int y_value, int x_value, int frame_value):enemy(y_value, x_value, frame_value, 8, 0, 5) {}
    char content = 'a';

    private:
    
};

#endif