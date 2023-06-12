#ifndef BULLET_H
#define BULLET_H

#include <stdio.h>
#include <locale.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <chrono>
#include <vector>

class Bullet{
    public:
        Bullet(int y_value, int x_value, int frame_value) \
        : y(y_value), x(x_value), create_frame_bullet(frame_value) {};
        int damage=1;
        int y, x;
        int create_frame_bullet; //initialize when it creates
        int check_frame_bullet;
        int level=1;
        bool power = false;
        
        char get_symbol(){
            switch(this->level){
                case 1:{
                    return '\'';
                    break;
                }
                case 2:{
                    return '^';
                    break;
                }
                case 3:{
                    return '!';                        
                    break;
                }
                default:
                    return '\'';
                    break;
            }
        }
};

class Enemy_bullet{
    public:
    Enemy_bullet(int y_, int x_, int frame_, int enemy_frame_, int damage_, char enemy_type_, int moving_type_)\
    : y(y_), x(x_), frame_value(frame_), enemy_frame_value(enemy_frame_), damage(damage_), enemy_type(enemy_type_), moving_type(moving_type_){}
    int y, x;
    int frame_value;
    int enemy_frame_value;
    int damage;
    char enemy_type;
    int moving_type; // 0 -> downward straight, 1 -> left diagonally. 2-> right diagonally
    private:
};

#endif