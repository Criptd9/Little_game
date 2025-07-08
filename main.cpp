#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <chrono>
#include <vector>
#include <io.h>
#include <fcntl.h>
#include <ctime>
#include "Libraries/CustomFunctions.h"
#include "Libraries/Objects.h"

#define N_MENU_OPTIONS 3

#define UP_ARROW_KEY 72 //All the ASCII codes of the keys
#define DOWN_ARROW_KEY 80
#define LEFT_ARROW_KEY 75
#define RIGHT_ARROW_KEY 77
#define ENTER_KEY 13
#define ESC_KEY 27
#define SPACE_KEY 32
#define UPPER_Q_KEY 81
#define LOWER_Q_KEY 113
#define UPPER_E_KEY 69
#define LOWER_E_KEY 101 
#define UPPER_W_KEY 87
#define LOWER_W_KEY 119
#define UPPER_S_KEY 83
#define LOWER_S_KEY 115

#define MAP_WIDTH 81 //The size of the map minus 1
#define MAP_HEIGHT 21

using namespace std;

int map[MAP_HEIGHT][MAP_WIDTH] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1},
                                  {1,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,1},
                                  {1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

//This function makes sure that the user wants really to quit a task
void exit_screen(int current_option, char key, bool &run){
    wstring options[2] = {L"Yes",L"No"};
    current_option = 0;
    bool run_1 = true;

    while(run_1){
        system("cls"); //Clears the window every time

        wcout<<L"Are you sure to quit?\n\n";

        for(int i=0;i<2;i++){ //Print every option available and which is selected
            if(i == current_option){
                wcout<<L"     "<<options[i]<<" <--"<<endl;
            }
            else{
                wcout<<L"     "<<options[i]<<endl;
            }
        }

        wcout<<L"\nPress the arrows 'up' and 'down' to select an option.\nPress enter to confirm an option.\n";

        key = _getch(); //Waits an input from the keyboard

        switch(key){ //The logic part of the menù
            case UP_ARROW_KEY:
                current_option--;
                if(current_option < 0){
                    current_option = 1;
                }
                break;
            case DOWN_ARROW_KEY:
                current_option++;
                if(current_option > 1){
                    current_option = 0;
                }
                break;
            case ENTER_KEY:
                switch(current_option){
                    case 0:
                        run_1 = false;
                        run = false;
                        break;
                    case 1:
                        run_1 = false;
                        break;
                }
        }
    }

    system("cls");
}

//This function sees all the input of the player
void input_function(char key, bool &run, Player &player, bool &render_map, vector<Bullet*>&bullets){
    if(_kbhit()){
        key = _getch();

        switch(key){
            case UPPER_W_KEY:
                key = LOWER_W_KEY;
                break;
            case UPPER_S_KEY:
                key = LOWER_S_KEY;
                break;
            case UPPER_E_KEY:
                key = LOWER_E_KEY;
                break;
        }

        switch(key){
            case RIGHT_ARROW_KEY:
                player.set_Dir(player.get_Dir()+1);
                if(player.get_Dir() > 7){
                    player.set_Dir(0);
                }
                break;
            case LEFT_ARROW_KEY:
                player.set_Dir(player.get_Dir()-1);
                if(player.get_Dir() < 0){
                    player.set_Dir(7);
                }
                break;
            case LOWER_W_KEY:
                player.set_InvertedMovement(false);
                player.set_Move(true);
                break;
            case LOWER_S_KEY:
                player.set_InvertedMovement(true);
                player.set_Move(true);
                break;
            case LOWER_E_KEY:
                player.set_Action(true);
                break;
                
            case SPACE_KEY:
                if(player.get_CurrentShootdelay() == player.get_Shootdelay() && player.get_Ammo() > 0){
                    Bullet* bullet = new Bullet(player.get_X(),player.get_Y(),player.get_Dir(),20,false);
                    bullet->set_InvertedMovement(false);
                    bullet->set_Move(true);
                    bullets.push_back(bullet);

                    player.set_CurrentShootdelay(0);
                    player.change_Ammo(-1);
                }
                break;
            case ESC_KEY:
                exit_screen(0,key,run);
                render_map = true;
                break;
        }
    }
}

//This function renders the map
void render_map_function(){
    for(int i=0;i<MAP_HEIGHT;i++){
        for(int j=0;j<MAP_WIDTH;j++){
            gotoxy(j,i);
            if(map[i][j] == 1){
                wcout<<L"▓";
            }
            else{
                wcout<<L" ";
            }
        }
    }
}

//This function renders the player, the UI and all the other objects
void render_function(Player player, vector<Bullet*>bullets, vector<Door*>doors, vector<Ammo*>ammos){
    gotoxy(player.get_X(),player.get_Y());
    wcout<<player.get_Character();

    if(!bullets.empty()){
        for(Bullet* t_bullet : bullets){
            gotoxy(t_bullet->get_X(),t_bullet->get_Y());
            wcout<<t_bullet->get_Character();
        }
    }

    for(Ammo* ammo : ammos){
        gotoxy(ammo->get_X(),ammo->get_Y());
        if(!ammo->get_Empty()){
            wcout<<ammo->get_Character();
        }
        else{
            if(player.get_X() != ammo->get_X() && player.get_Y() != ammo->get_Y()){
                wcout<<" ";
            }
        }
    }

    for(Door* t_door : doors){
        gotoxy(t_door->get_X(),t_door->get_Y());
        if(!t_door->get_Open()){
            wcout<<t_door->get_Character();
        }
        else if(t_door->get_Open()){
            if(player.get_X() != t_door->get_X() && player.get_Y() != t_door->get_Y()){
                wcout<<" ";
            }
        }
    }

    gotoxy(82,0);
    wcout<<L"                         ";

    gotoxy(82,0);
    wcout<<L"player coordinates("<<player.get_X()<<";"<<player.get_Y()<<")";

    gotoxy(0, MAP_HEIGHT + 1);
    wcout<<L"Press 'esc' to quit the game.";

    gotoxy(MAP_WIDTH - 15, MAP_HEIGHT + 1);
    wcout<<L"        ";

    gotoxy(MAP_WIDTH - 15, MAP_HEIGHT + 1);
    wcout<<L"Ammo:"<<player.get_Ammo();

    int dir = 90;

    gotoxy(MAP_WIDTH - 15,MAP_HEIGHT + 2);
    wcout<<L"                ";

    gotoxy(0,MAP_HEIGHT + 2);
    for(int i=0;i<player.get_Dir(); i++){
        dir-=45;
        if(dir == 0){
            dir = 360;
        }
    }
    gotoxy(MAP_WIDTH - 15,MAP_HEIGHT + 2);
    wcout<<L"Direction:"<<dir<<L"°";
}

//This function updates every frame of the game
void update_function(char key){
    system("cls");

    bool run = true;
    bool render_map = true;

    const int ammo_spawn_patterns[4][4] = {{0,1,2,3},{2,0,1,3},{2,3,0,1},{0,2,3,1}};
    int current_ammo_spawn_pattern = rand() % 4;
    int current_box_ammo = 0;

    const int max_ammo = 30;

    Player player;
    player.setPosition(40,10);
    player.set_Shootdelay(7);
    player.set_Ammo(max_ammo);
    player.set_Dir(0);
    player.set_InvertedMovement(false);
    player.set_Move(false);
    player.set_WalkingDelay(2);
    player.set_Action(false);

    vector<Collider*>colliders;
    vector<Bullet*>bullets;
    vector<Trigger*>triggers;
    vector<Door*>doors;
    vector<Ammo*>boxes_ammo;

    const int ammo_timer = 300;
    int current_ammo_timer = ammo_timer;

    for(int i=0;i<MAP_HEIGHT;i++){
        for(int j=0;j<MAP_WIDTH;j++){
            Collider* collider;
            Trigger* trigger;
            Ammo* box_ammo;

            if(map[i][j] == 3){
                trigger = new Trigger(j,i,0);
                triggers.push_back(trigger);
            }
            
            if(map[i][j] == 4){
                box_ammo = new Ammo(j,i,5,true);
                boxes_ammo.push_back(box_ammo);
            }

            if(map[i][j] == 1 || map[i][j] == 2){
                collider = new Collider(j,i,true,map[i][j]);
                colliders.push_back(collider);
            }
        }
    }

    triggers[0]->set_IdAction(0);
    triggers[2]->set_IdAction(0);

    triggers[1]->set_IdAction(1);
    triggers[3]->set_IdAction(1);

    triggers[4]->set_IdAction(2);
    triggers[6]->set_IdAction(2);

    triggers[5]->set_IdAction(3);
    triggers[7]->set_IdAction(3);

    int index = 0;

    for(int i=0;i<colliders.size();i++){
        Door* door;
        if(colliders[i]->get_Type() == 2){
            door = new Door(colliders[i]->get_X(),colliders[i]->get_Y(),triggers[index]->get_IdAction(),i,false);
            doors.push_back(door);
            index++;
        }
    }

    while(run){
        input_function(key, run, player, render_map, bullets);
        if(run){
            player.change_CurrentShootdelay(1);
            player.change_CurrentWalkingdelay(1);

            if(current_ammo_timer > 0){
                current_ammo_timer--;
            }
            else{
                boxes_ammo[ammo_spawn_patterns[current_ammo_spawn_pattern][current_box_ammo]]->set_Empty(false);
                current_box_ammo++;
                current_ammo_timer = ammo_timer;
            }

            if(current_box_ammo > 3){
                current_box_ammo = 0;
                current_ammo_spawn_pattern = rand() % 4;
            }

            if(player.get_Move() && player.get_CurrentWalkingDelay() == player.get_WalkingDelay()){
                player.generate_Space();
                switch(player.get_Dir()){
                    case 0:
                        player.change_Y(-1);
                        break;
                    case 1:
                        player.change_X(1);
                        player.change_Y(-1);
                        break;
                    case 2:
                        player.change_X(1);
                        break;
                    case 3:
                        player.change_X(1);
                        player.change_Y(1);
                        break;
                    case 4:
                        player.change_Y(1);
                        break;
                    case 5:
                        player.change_X(-1);
                        player.change_Y(1);
                        break;
                    case 6:
                        player.change_X(-1);
                        break;
                    case 7:
                        player.change_X(-1);
                        player.change_Y(-1);
                        break;
                }
                player.set_Move(false);
                player.set_CurrentWalkingDelay(0);
            }

            if(!bullets.empty()){
                for(int i=bullets.size()-1;i>=0;i--){
                    if(bullets[i]->get_LifeSpan() <= 0){
                        bullets[i]->set_Delete(true);
                    }
                    if(!bullets[i]->get_Delete()){
                        bullets[i]->generate_Space();
                        switch(bullets[i]->get_Dir()){
                            case 0:
                                bullets[i]->change_Y(-1);
                                bullets[i]->change_LifeSpan(-2);
                                break;
                            case 1:
                                bullets[i]->change_X(1);
                                bullets[i]->change_Y(-1);
                                bullets[i]->change_LifeSpan(-2);
                                break;
                            case 2:
                                bullets[i]->change_X(1);
                                bullets[i]->change_LifeSpan(-1);
                                break;
                            case 3:
                                bullets[i]->change_X(1);
                                bullets[i]->change_Y(1);
                                bullets[i]->change_LifeSpan(-2);
                                break;
                            case 4:
                                bullets[i]->change_Y(1);
                                bullets[i]->change_LifeSpan(-2);
                                break;
                            case 5:
                                bullets[i]->change_X(-1);    
                                bullets[i]->change_Y(1);
                                bullets[i]->change_LifeSpan(-2);
                                break;
                            case 6:
                                bullets[i]->change_X(-1);
                                bullets[i]->change_LifeSpan(-1);
                                break;
                            case 7:
                                bullets[i]->change_X(-1);
                                bullets[i]->change_Y(-1);
                                bullets[i]->change_LifeSpan(-2);
                                break;
                        }
                    }
                    else{
                        bullets[i]->generate_Space();
                        delete bullets[i];
                        bullets.erase(bullets.begin() + i);
                    }
                }
            }

            for(Ammo* box_ammo : boxes_ammo){
                if(player.get_X() == box_ammo->get_X() && player.get_Y() == box_ammo->get_Y() && !box_ammo->get_Empty() && player.get_Ammo() != max_ammo){
                    box_ammo->set_Empty(true);
                    player.change_Ammo(box_ammo->get_Ammo());
                    if(player.get_Ammo() > max_ammo){
                        player.set_Ammo(max_ammo);
                    }
                }
            }

            for(Trigger* t_trigger : triggers){
                if(player.get_X() == t_trigger->get_X() && player.get_Y() == t_trigger->get_Y() && player.get_Action()){
                    for(Door* t_door : doors){
                        if(!t_door->get_Open() && t_door->get_IdTrigger() == t_trigger->get_IdAction()){
                            t_door->generate_Space();
                            t_door->set_Open(true);
                            colliders[t_door->get_Index()]->set_Solid(false);
                        }
                    }
                }
            }

            for(Collider* t_collider : colliders){
                if(t_collider->get_Solid()){
                    if(player.get_X() == t_collider->get_X() && player.get_Y() == t_collider->get_Y()){
                        switch(player.get_Dir()){
                            case 0:
                                player.change_Y(1);
                                break;
                            case 1:
                                player.change_X(-1);
                                player.change_Y(1);
                                break;
                            case 2:
                                player.change_X(-1);
                                break;
                            case 3:
                                player.change_X(-1);
                                player.change_Y(-1);
                                break;
                            case 4:
                                player.change_Y(-1);
                                break;
                            case 5:
                                player.change_X(1);
                                player.change_Y(-1);
                                break;
                            case 6:
                                player.change_X(1);
                                break;
                            case 7:
                                player.change_X(1);
                                player.change_Y(1);
                                break;
                        }
                    }
                    if(!bullets.empty()){
                        for(int i=bullets.size()-1;i>=0;i--){
                            if(bullets[i]->get_X() == t_collider->get_X() && bullets[i]->get_Y() == t_collider->get_Y()){
                                switch(bullets[i]->get_Dir()){
                                    case 0:
                                        bullets[i]->change_Y(1);
                                        break;
                                    case 1:
                                        bullets[i]->change_X(-1);
                                        bullets[i]->change_Y(1);
                                        break;
                                    case 2:
                                        bullets[i]->change_X(-1);
                                        break;
                                    case 3:
                                        bullets[i]->change_X(-1);
                                        bullets[i]->change_Y(-1);
                                        break;
                                    case 4:
                                        bullets[i]->change_Y(-1);
                                        break;
                                    case 5:
                                        bullets[i]->change_X(1);    
                                        bullets[i]->change_Y(-1);
                                        break;
                                    case 6:
                                        bullets[i]->change_X(1);
                                        break;
                                    case 7:
                                        bullets[i]->change_X(1);
                                        bullets[i]->change_Y(1);
                                        break;
                                }

                                bullets[i]->set_Delete(true);
                            }
                        }
                    }
                }
            }

            if(player.get_Action()){
                player.set_Action(false);
            }

            if(render_map){
                render_map_function();
                render_map = false;
            }
            render_function(player,bullets,doors,boxes_ammo);
        }

        this_thread::sleep_for(chrono::milliseconds(20));
    }
}

int main(){
    _setmode(_fileno(stdout), _O_U16TEXT);
    setColor(10);
    setFontSize_Function();
    fullscreen_Function();
    srand(time(NULL));

    bool run = true; //When true, the program is running

    wstring options[N_MENU_OPTIONS] = {L"Play",L"Info",L"Exit"}; //All the options of the menù
    int current_option = 0; //The current option selected
    char key; //This variabile stores the key currentlly pressed

    while(run){
        system("cls"); //Clears the window every time
        wcout<<L"Little Game\n\n";

        for(int i=0;i<N_MENU_OPTIONS;i++){ //Print every option available and which is selected
            if(i == current_option){
                wcout<<L"     "<<options[i]<<" <--"<<endl;
            }
            else{
                wcout<<L"     "<<options[i]<<endl;
            }
        }

        wcout<<L"\nPress the arrows 'up' and 'down' to select an option.\nPress enter to confirm an option.\n";

        key = _getch(); //Waits an input from the keyboard

        switch(key){ //The logic part of the menù
            case UP_ARROW_KEY:
                current_option--;
                if(current_option < 0){
                    current_option = N_MENU_OPTIONS - 1;
                }
                break;
            case DOWN_ARROW_KEY:
                current_option++;
                if(current_option > N_MENU_OPTIONS - 1){
                    current_option = 0;
                }
                break;
            case ENTER_KEY:
                switch(current_option){
                    case 0:
                        update_function(key);
                        break;
                    case 2:
                        exit_screen(current_option,key,run);
                        break;
                }
        }
    }

    system("exit");

    return 0;
}