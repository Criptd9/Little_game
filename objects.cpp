#include <iostream>
#include "Libraries/CustomFunctions.h"
#include "Libraries/Objects.h"

//Object
void Object::setPosition(int pos_x,int pos_y){
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}
void Object::set_X(int pos_x){
    this->pos_x = pos_x;
}
void Object::set_Y(int pos_y){
    this->pos_y = pos_y;
}
void Object::set_InvertedMovement(bool inverted_movement){
    this->inverted_movement = inverted_movement;
}
void Object::set_Move(bool move){
    this->move = move;
}
int Object::get_X(){
    return this->pos_x;
}
int Object::get_Y(){
    return this->pos_y;
}
bool Object::get_InvertedMovement(){
    return this->inverted_movement;
}
bool Object::get_Move(){
    return this->move;
}
void Object::change_X(int value){
    if(!get_InvertedMovement()){
        this->pos_x += value;
    }
    else{
        this->pos_x -= value;
    }
}
void Object::change_Y(int value){
    if(!get_InvertedMovement()){
        this->pos_y += value;
    }
    else{
        this->pos_y -= value;
    }
}
void Object::generate_Space(){
    int pos_x, pos_y;

    pos_x = this->pos_x;
    pos_y = this->pos_y;

    gotoxy(pos_x,pos_y); std::wcout<<" ";
}

//Bullet
Bullet::Bullet(int pos_x, int pos_y,int dir, int life_span, bool _delete){
    setPosition(pos_x,pos_y);
    this->dir = dir;
    this->life_span = life_span;
    this->_delete = _delete;
}
void Bullet::set_Dir(int dir){
    this->dir = dir;
}
void Bullet::set_LifeSpan(int life_span){
    if(life_span < 0){
        life_span = 5;
    }
    this->life_span = life_span;
}
void Bullet::set_Delete(bool _delete){
    this->_delete = _delete;
}
void Bullet::change_LifeSpan(int value){
    this->life_span += value;
}
wchar_t Bullet::get_Character(){
    return this->_character;
}
int Bullet::get_Dir(){
    return this->dir;
}
int Bullet::get_LifeSpan(){
    return this->life_span;
}
bool Bullet::get_Delete(){
    return this->_delete;
}

//Player
const wchar_t Player::_characters[8] = {L'▲', L'◥', L'►', L'◢',L'▼',L'◣',L'◄',L'◤'};
void Player::set_Dir(int dir){
    this->dir = dir;
}
void Player::set_Shootdelay(int shoot_delay){
    this->shoot_delay = shoot_delay;
    this->current_shoot_delay = shoot_delay;
}
void Player::set_CurrentShootdelay(int current_shoot_delay){
    if(current_shoot_delay > this->shoot_delay){
        current_shoot_delay = this->shoot_delay;
    }
    this->current_shoot_delay = current_shoot_delay;
}
void Player::set_Ammo(int ammo){
    this->ammo = ammo;
}
void Player::set_Action(bool action){
    this->action = action;
}
void Player::change_Ammo(int value){
    this->ammo+=value;
}
void Player::set_WalkingDelay(int walking_delay){
    this->walking_delay = walking_delay;
    this->current_walking_delay = walking_delay;
}
void Player::set_CurrentWalkingDelay(int current_walking_delay){
    if(current_walking_delay > this->walking_delay){
        current_walking_delay = this->walking_delay;
    }
    this->current_walking_delay = current_walking_delay;
}
void Player::change_CurrentShootdelay(int value){
    if(this->current_shoot_delay < this->shoot_delay){
        this->current_shoot_delay += value;
    }
}
void Player::change_CurrentWalkingdelay(int value){
    if(this->current_walking_delay < this->walking_delay){
        this->current_walking_delay += value;
    }
}
int Player::get_Shootdelay(){
    return this->shoot_delay;
}
int Player::get_CurrentShootdelay(){
    return this->current_shoot_delay;
}
int Player::get_Dir(){
    return this->dir;
}
wchar_t Player::get_Character(){
    return this->_characters[this->dir];
}
int Player::get_Ammo(){
    return this->ammo;
}
int Player::get_WalkingDelay(){
    return this->walking_delay;
}
int Player::get_CurrentWalkingDelay(){
    return this->current_walking_delay;
}
bool Player::get_Action(){
    return this->action;
}

//Door
const wchar_t Door::character = L'░';
Door::Door(int pos_x, int pos_y, int id_trigger, int index, bool opend){
    setPosition(pos_x,pos_y);
    this->id_trigger = id_trigger;
    this->index = index;
    this->opend = opend;
}
void Door::set_IdTrigger(int id_trigger){
    this->id_trigger = id_trigger;
}
void Door::set_Open(bool opend){
    this->opend = opend;
}
int Door::get_IdTrigger(){
    return this->id_trigger;
}
bool Door::get_Open(){
    return this->opend;
}
int Door::get_Index(){
    return this->index;
}
wchar_t Door::get_Character(){
    return this->character;
}

//Ammo
const wchar_t Ammo::charcater = L'■';
Ammo::Ammo(int pos_x, int pos_y, int ammo, bool empty){
    setPosition(pos_x,pos_y);
    this->ammo = ammo;
    this->empty = empty;
}
void Ammo::set_Ammo(int ammo){
    this->ammo = ammo;
}
void Ammo::set_Empty(bool empty){
    this->empty = empty;
}
int Ammo::get_Ammo(){
    return this->ammo;
}
wchar_t Ammo::get_Character(){
    return this->charcater;
}
bool Ammo::get_Empty(){
    return this->empty;
}

//Trigger
Trigger::Trigger(int pos_x, int pos_y, int id_action){
    setPosition(pos_x,pos_y);
    this->id_action = id_action;
}
void Trigger::set_IdAction(int id_action){
    this->id_action = id_action;
}
int Trigger::get_IdAction(){
    return this->id_action;
}

//Collider
Collider::Collider(int pos_x, int pos_y, bool isSolid, int type){
    setPosition(pos_x,pos_y);
    this->isSolid = isSolid;
    this->type = type;
}
void Collider::set_Solid(bool isSolid){
    this->isSolid = isSolid;
}
void Collider::set_Type(int type){
    this->type = type;
}
bool Collider::get_Solid(){
    return this->isSolid;
}
int Collider::get_Type(){
    return this->type;
}