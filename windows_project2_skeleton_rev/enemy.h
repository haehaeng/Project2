#ifndef ENEMY_H
#define ENEMY_H

 class enemy
 {
    public:
    enemy(int y_value, int x_value, int frame_value) \
    : y(y_value), x(x_value), create_frame_enemy(frame_value) {};

    int y,x; //position
    int hp;
    int speed;
    int score;
    int create_frame_enemy; //initialize when it creates
    int check_frame_enemy = 0;
 
    private:
 
 
 };

 #endif