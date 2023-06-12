#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

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
#include "My_plane.h"
#include "unit.h"
#include "enemy.h"
#include "item.h"


using namespace std;

//Screen manager.
class Screen_manager{
    public:
        int frame_length=100000; //each frame's length == 0.1sec(10,000 microseconds)
        int curr_frame=0; //1frame=0.1sec
        int num_event_occured=0; //track the number of event occured _ 20230609
        vector<enemy*> enemies;
        vector<item*> items;

        int y, x;
        int width=60;
        int height=30;
        int frame_event[300]={0,}, y_event[300]={0,}, x_event[300]={0,};
        char type_event[300] = {' ',};

        void print(int ascii);
        void print();
        void print_share();
        void render();
        
        void generate_event();
        void interaction();
        bool check_finish(bool all_enemy);
        char board[30][60]={'a'};

        void printend();
        My_plane my_plane = My_plane(height-2, 1, 0);
};
#endif