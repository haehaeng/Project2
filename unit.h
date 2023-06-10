#ifndef UNIT_H
#define UNIT_H
#include <iostream>

 class unit
 {
    public:
    unit(int y_value, int x_value, int frame_value, char content_value) \
    : y(y_value), x(x_value), create_frame_enemy(frame_value), content(content_value) {};

    int y,x; //position
    int create_frame_enemy; //initialize when it creates
    int check_frame_enemy = 0;
    char content;

    private:
 
 
 };

 #endif