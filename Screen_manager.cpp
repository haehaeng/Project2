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
#include <cctype>

#include "unit.h"


#include "enemy.h"
#include "enemy_1n.h"
#include "enemy_2r.h"
#include "enemy_3s.h"
#include "enemy_4d.h"
#include "enemy_5a.h"
#include "enemy_6b.h"

#include "item.h"
#include "Levelup_bullet.h"
#include "Powerup_bullet.h"
#include "Heal_pack.h"

#include "Screen_manager.h"

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

    int shot_frame, create_frame, check_frame;
    shot_frame = this->my_plane.shot_frame_my_plane;
    create_frame = this->my_plane.create_frame_my_plane;
    check_frame = this->my_plane.check_frame_my_plane;
    
    while ((curr_frame-create_frame)/shot_frame - check_frame > 0){ //bullet create
        Bullet bullet = Bullet(this->my_plane.y-1+shot_frame, this->my_plane.x, check_frame);
        bullet.level = my_plane.level;
        bullet.power = my_plane.power;
        this->my_plane.bullet.push_back(bullet);
        
        //boss 'b' bullet create
        for(auto iter = enemies.begin(); iter!=enemies.end();iter++)
        {
            if(tolower((*iter)->content) == 'b'){
                Enemy_bullet bullet = Enemy_bullet((*iter)->y, (*iter)->x, curr_frame, (*iter)->create_frame_enemy, (*iter)->damage, (*iter)->content,0);
                enemy_bullets.push_back(bullet);
                if(check_frame%4==1 || check_frame%4==2){
                    Enemy_bullet bullet = Enemy_bullet((*iter)->y, (*iter)->x-1, curr_frame, (*iter)->create_frame_enemy, (*iter)->damage, (*iter)->content,0);
                    enemy_bullets.push_back(bullet);
                }
                else{
                    Enemy_bullet bullet = Enemy_bullet((*iter)->y, (*iter)->x+1, curr_frame, (*iter)->create_frame_enemy, (*iter)->damage, (*iter)->content,0);
                    enemy_bullets.push_back(bullet);
                }
                
            }
        }


        if(bullet.power){
            if(my_plane.x>1){
                Bullet bullet = Bullet(this->my_plane.y-1+shot_frame, this->my_plane.x-1, check_frame);
                bullet.level = my_plane.level;
                bullet.power = my_plane.power;
                this->my_plane.bullet.push_back(bullet);
            }
            if(my_plane.x<58){
                Bullet bullet = Bullet(this->my_plane.y-1+shot_frame, this->my_plane.x+1, check_frame);
                bullet.level = my_plane.level;
                bullet.power = my_plane.power;
                this->my_plane.bullet.push_back(bullet);
            }

        }

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
                board[iter->y][iter->x]=iter->get_symbol();
                iter++;
            }
        }
        this->my_plane.check_frame_my_plane+=1;
        check_frame++;
    
    //Enemy_bullet printing part
    for (auto iter=enemy_bullets.begin();iter!=enemy_bullets.end();){
        switch(iter->moving_type){
        case 0:
            if(iter->y == 28){
                board[iter->y][iter->x]=' ';
                enemy_bullets.erase(iter);
            }
            else{
                board[iter->y][iter->x]=' ';
                iter->y ++;
                board[iter->y][iter->x]='*';
                iter++;
            }
            break;
        case 1:
            if(iter->y == 28||iter->x == 1){
                board[iter->y][iter->x]=' ';
                enemy_bullets.erase(iter);
            }
            else{
                board[iter->y][iter->x]=' ';
                iter->y +=1;
                iter->x -=1;
                board[iter->y][iter->x]='*';
                iter++;
            }
            break;
        case 2:
            if(iter->y == 28 || iter->x == 58){
                board[iter->y][iter->x]=' ';
                enemy_bullets.erase(iter);
            }
            else{
                board[iter->y][iter->x]=' ';
                iter->y +=1;
                iter->x +=1;
                board[iter->y][iter->x]='*';
                iter++;
            }
            break;


        }
        
    }
    }   

    //Units printing part
    for (auto iter=items.begin(); iter!=items.end();)
    {
        board[(**iter).y][(**iter).x] = (**iter).content;
        iter++;
    }

    for (auto iter=enemies.begin(); iter!=enemies.end();)
    {
        if((**iter).y >= 29 ||(**iter).x <= 0 )
        {
            board[(**iter).y][(**iter).x]=' ';
            enemies.erase(iter);
        }
        else{
            board[(**iter).y][(**iter).x]=(**iter).content;
            iter++;
        }
    }
    //Unit printing part ends

    // Unit moving part & Enemy Bullet Creating
    for (auto iter=enemies.begin(); iter!=enemies.end();){
        bool erased = false;
        if((*iter)->speed!=0){
            while ((curr_frame-(*iter)->create_frame_enemy)/((*iter)->speed) - (*iter)->check_frame_enemy > 0){
                board[(*iter)->y][(*iter)->x] = ' ';
                if((*iter)->y < height-2){
                    //Bullet Generation (after move)
                    if((((*iter)->content == 's')||(*iter)->content == 'S') && ((*iter)->y<height-3)){
                        Enemy_bullet bullet = Enemy_bullet((*iter)->y+1, (*iter)->x, curr_frame, (*iter)->create_frame_enemy, (*iter)->damage, (*iter)->content,0);
                        enemy_bullets.push_back(bullet);
                    }
                    if((((*iter)->content == 'd')||(*iter)->content == 'D') && ((*iter)->y<height-3)){
                        if((*iter)->x < 30){
                        Enemy_bullet bullet = Enemy_bullet((*iter)->y+1, (*iter)->x, curr_frame, (*iter)->create_frame_enemy, (*iter)->damage, (*iter)->content,1);
                        enemy_bullets.push_back(bullet);
                        }   
                        else{
                        Enemy_bullet bullet = Enemy_bullet((*iter)->y+1, (*iter)->x, curr_frame, (*iter)->create_frame_enemy, (*iter)->damage, (*iter)->content,2);
                        enemy_bullets.push_back(bullet);
                        }
                    }
                    (*iter)->y+=1;
                    board[(*iter)->y][(*iter)->x] = (*iter)->content;
                    (*iter)->check_frame_enemy++;
                }
                else{
                    enemies.erase(iter);
                    erased = true;
                    break;
                }
            }
        }
        if(!erased){
            iter++;
        }        
    }
    // Unit moving part ends

    // Unit buff
    for (auto iter=enemies.begin(); iter!=enemies.end();iter++){
        if ((*iter)->content =='a' || (*iter)->content == 'A')
        {
            while ((curr_frame-(*iter)->create_frame_enemy)/6 - (*iter)->check_frame_enemy > 0)
            {
                for (auto it = enemies.begin(); it != enemies.end(); it++){
                    if((*it)->create_frame_enemy != (*iter)->create_frame_enemy){
                        if((*it)->y-(*iter)->y<4 && (*iter)->y-(*it)->y <4){
                            if((*it)->x-(*iter)->x<4 && (*iter)->x-(*it)->x <4){    
                                (*it)->content = toupper((*it)->content);
                                (*it)->damage ++;
                            }
                        }
                    }
                }
                (*iter)->check_frame_enemy += 1;
            }
        }    
    }

    //my_plane have to be printed always.
    board[this->my_plane.y][this->my_plane.x]='M';
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

void Screen_manager::generate_event(){
    
    //Events Generation part
    while (frame_event[num_event_occured]!=0 && frame_event[num_event_occured] <= curr_frame)
    {   
        switch(type_event[num_event_occured]){
            //enemies
            case 'n':{
                enemy_1n* enemy_1 = new enemy_1n(y_event[num_event_occured], x_event[num_event_occured], frame_event[num_event_occured]);
                enemies.push_back(enemy_1);
                break;
                }
            case 'r':{
                enemy_2r* enemy_2 = new enemy_2r(y_event[num_event_occured], x_event[num_event_occured], frame_event[num_event_occured]);
                enemies.push_back(enemy_2);
                break;
                }
            case 's':{
                enemy_3s* enemy_3 = new enemy_3s(y_event[num_event_occured], x_event[num_event_occured], frame_event[num_event_occured]);
                enemies.push_back(enemy_3);
                break;
                }
            case 'd':{
                enemy_4d* enemy_4 = new enemy_4d(y_event[num_event_occured], x_event[num_event_occured], frame_event[num_event_occured]);
                enemies.push_back(enemy_4);
                break;
                }
            case 'a':{
                enemy_5a* enemy_5 = new enemy_5a(y_event[num_event_occured], x_event[num_event_occured], frame_event[num_event_occured]);
                enemies.push_back(enemy_5);
                break;
                }
            case 'b':{
                enemy_6b* enemy_6 = new enemy_6b(y_event[num_event_occured], x_event[num_event_occured], frame_event[num_event_occured]);
                enemies.push_back(enemy_6);
                break;
                }
            //items
            case 'P':{
                Powerup_bullet* powerup_bullet = new Powerup_bullet(y_event[num_event_occured], x_event[num_event_occured], frame_event[num_event_occured]);
                items.push_back(powerup_bullet);
                break;
                }
            case 'L':{
                Levelup_bullet* levelup_bullet = new Levelup_bullet(y_event[num_event_occured], x_event[num_event_occured], frame_event[num_event_occured]);
                items.push_back(levelup_bullet);
                break;
                }
            case 'H':{
                Heal_pack* heal_pack = new Heal_pack(y_event[num_event_occured], x_event[num_event_occured], frame_event[num_event_occured]);
                items.push_back(heal_pack);
                break;
            }


            default:{
                break;
                }
        }
            num_event_occured++;   
    }
    //Each event is stored in proper vector.
    //Envents Generation part ends
}


void Screen_manager::interaction(){
    //between my_plane and enemies.
    for (auto iter=enemies.begin(); iter!=enemies.end();){
        //1 check per frame
        if(((*iter)->y == this->my_plane.y) && ((*iter)->x == this->my_plane.x)){
            my_plane.hp--;
        }
        iter++;
    }
    //between my_plane and Enemy_bullet
    for (auto iter=enemy_bullets.begin(); iter!=enemy_bullets.end();){
        if(iter->x == my_plane.x && iter->y == my_plane.y){
            my_plane.hp -= iter->damage;
            enemy_bullets.erase(iter);
        }
        else{
            iter++;
        }
    }
    //between my_plane and items
    for (auto iter=items.begin(); iter!=items.end();){
        if(((*iter)->y == this->my_plane.y) && ((*iter)->x == this->my_plane.x)){
            switch((*iter)->content){
                case 'P':
                    if(!my_plane.power){
                        my_plane.power = true;
                    }
                    break;

                case 'L':
                    if(my_plane.level <3){
                    my_plane.level++;
                    }
                    break;

                case 'H':
                    my_plane.hp += 3;
                    break;
                default:
                    break;
            }
            items.erase(iter);
        }
        else{
        iter++;
        }
    }
   
    //between enemy and bullets
    for(auto enem=enemies.begin(); enem !=enemies.end();){
        for(auto iter=this->my_plane.bullet.begin(); iter<this->my_plane.bullet.end();){       
            if( iter->x == (*enem)->x && iter->y == (*enem)->y){
                (*enem)->hp -= iter->level;
                this->my_plane.bullet.erase(iter); // 적에게 맞은 bullet은 사라짐.
            }
            else{
                iter++;
            }
        }
        if ((*enem)->hp<=0){
            switch(tolower((*enem)->content)){
                case 'n':
                    my_plane.kills[0]++;
                    break;
                case 'r':
                    my_plane.kills[1]++;
                    break;
                case 's':
                    my_plane.kills[2]++;
                    break;
                case 'd':
                    my_plane.kills[3]++;
                    break;
                case 'a':
                    my_plane.kills[4]++;
                    break;
                case 'b':
                    my_plane.kills[5]++;
                    break;
            }
            my_plane.score += (*enem)->score;
            board[(*enem)->y][(*enem)->x] = ' ';
            enemies.erase(enem);
        }
        else{
        enem++;
        }
    }
}

bool Screen_manager::check_finish(bool all_enemy){
    if(this->my_plane.hp <= 0){
        return true;
    }
    else if(all_enemy && enemies.empty()){
        return true;
    }
    else{
        return false;
    }
}


void Screen_manager::printend(){
    cout << "Your score is " << my_plane.score << "(n : " << my_plane.kills[0] <<\
    " , r : " << my_plane.kills[1] << " , s : " << my_plane.kills[2] << " , d : " << \
    my_plane.kills[3] << " , a : " << my_plane.kills[4] << " , b : " << my_plane.kills[5] << ")" << endl;
    cout << "Your hp is " << my_plane.hp << endl;
}