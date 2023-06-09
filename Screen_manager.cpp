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
#include "Screen_manager.h"
#include "enemy_1n.h"
#include "enemy_2r.h"
#include "enemy_3s.h"
#include "enemy_4d.h"
#include "enemy_5a.h"
using namespace std;

//move cursor
void cursorYX(int y, int x)
{
    COORD pos;
    pos.X = x;        
    pos.Y = y;            
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Screen_manager::render(){
    for(int j=0; j<height; j++){
        for(int i=0; i<width; i++){
            cursorYX(j, i);
            printf("%c", board[j][i]);
        }
    }
}

//print sharing things.
void Screen_manager::print_share(){
    //wall
    {
    for(int i=0; i<width; i++){board[height-1][i]='w';}
    for(int j=0; j<height; j++){board[j][0]='w'; board[j][width-1]='w';}
    }

    //Bullet part
    {
    int shot_frame, create_frame, check_frame;
    shot_frame = this->my_plane.shot_frame_my_plane;
    create_frame = this->my_plane.create_frame_my_plane;
    check_frame = this->my_plane.check_frame_my_plane;
    while ((curr_frame-create_frame)/shot_frame - check_frame > 0){ //bullet create
        Bullet bullet = Bullet(this->my_plane.y-1+shot_frame, this->my_plane.x, check_frame);
        this->my_plane.bullet.push_back(bullet);

        for(auto iter=this->my_plane.bullet.begin(); iter<this->my_plane.bullet.end(); ){
            if(iter->y<=0){
                board[iter->y][iter->x]=' ';
                this->my_plane.bullet.erase(iter);
            }
            else{
                if(iter!=(this->my_plane.bullet.end()-1) && curr_frame!=1){
                    board[iter->y][iter->x]=' ';
                }
                iter->y -= shot_frame;
                board[iter->y][iter->x]='\'';
                iter++;
            }
        }
        this->my_plane.check_frame_my_plane+=1;
        check_frame++;
    }
    //Bullet part ends
    }
    //Events Generation part
    {
    while ( frame_event[num_event_occured] <= curr_frame)
    {
        switch(type_event[num_event_occured]){
            //enemies
            case 'n':
                enemy_1n* enemy_1 = new enemy_1n(y_event[num_event_occured], x_event[num_event_occured], frame_event[num_event_occured]);
                enemies.push_back(enemy_1);
                break;
            case 'r':
                enemy_2r* enemy_2 = new enemy_2r(y_event[num_event_occured], x_event[num_event_occured], frame_event[num_event_occured]);
                enemies.push_back(enemy_2);
                break;
            case 's':
                enemy_3s* enemy_3 = new enemy_3s(y_event[num_event_occured], x_event[num_event_occured], frame_event[num_event_occured]);
                enemies.push_back(enemy_3);
                break;
            case 'd':
                enemy_4d* enemy_4 = new enemy_4d(y_event[num_event_occured], x_event[num_event_occured], frame_event[num_event_occured]);
                enemies.push_back(enemy_4);
                break;
            case 'a':
                enemy_5a* enemy_5 = new enemy_5a(y_event[num_event_occured], x_event[num_event_occured], frame_event[num_event_occured]);
                enemies.push_back(enemy_5);
                break;
        
            //items
            case 'P':
                break;
            case 'L':
                break;
    }

    }
    //Each event is stored in proper vector.
    //Envents Generation part ends
    }
    //Enemy printing part
    for (auto iter=enemies.begin(); iter<enemies.end();)
    {
        if((**iter).x <= 0)
        {
            board[(**iter).y][(**iter).x]=' ';
            enemies.erase(iter);
        }
        else{
            board[(**iter).y][(**iter).x]=(**iter).content;
        }
    }

    //Enemy part ends



}

//print when key didn't pressed
void Screen_manager::print(){
    board[this->my_plane.y][this->my_plane.x]='M';

    print_share();
}

//print when key pressed
void Screen_manager::print(int ch){ //ascii
    if(ch=='d'){ //right
        if(this->my_plane.y >=0 && this->my_plane.y <(height-1) && this->my_plane.x >0 && this->my_plane.x < (width-2)){
            board[this->my_plane.y][this->my_plane.x]=' ';
            this->my_plane.x +=1;
            board[this->my_plane.y][this->my_plane.x]='M';
        }
    }
    else if(ch=='a'){ //left
        if(this->my_plane.y >=0 && this->my_plane.y <(height-1) && this->my_plane.x >1 && this->my_plane.x < (width-1)){
            board[this->my_plane.y][this->my_plane.x]=' ';
            this->my_plane.x -=1;
            board[this->my_plane.y][this->my_plane.x]='M';
        }
    }
    else if(ch=='w'){ //up
        if(this->my_plane.y >0 && this->my_plane.y <(height-1) && this->my_plane.x >0 && this->my_plane.x < (width-1)){
            board[this->my_plane.y][this->my_plane.x]=' ';
            this->my_plane.y -=1;
            board[this->my_plane.y][this->my_plane.x]='M';
        }
    }
    else if(ch=='s'){ //down
        if(this->my_plane.y >=0 && this->my_plane.y <(height-2) && this->my_plane.x >0 && this->my_plane.x < (width-1)){
            board[this->my_plane.y][this->my_plane.x]=' ';
            this->my_plane.y +=1;
            board[this->my_plane.y][this->my_plane.x]='M';
        }    
    }

    print_share();
}