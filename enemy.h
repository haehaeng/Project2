#ifndef ENEMY_H
#define ENEMY_H

#include "unit.h"
#include <vector>
#include "Bullet.h"
 class enemy :public unit
 {
    public:
    enemy(int y_, int x_, int frame_, int hp_, int speed_, int score_, char content_) \
    : unit(y_, x_, frame_, content_),hp(hp_),speed(speed_),score(score_) {};
      
    virtual void duty(){};
    int hp;
    int speed;
    int score;
    int damage;
    
    private:
 
 
 };

 #endif