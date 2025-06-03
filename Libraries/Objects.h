#pragma once

class Object{
    private:
        int pos_x;
        int pos_y;
        bool inverted_movement;
        bool move;
    public:
        void setPosition(int pos_x,int pos_y); //Set functions
        void set_X(int pos_x);
        void set_Y(int pos_y);
        void set_InvertedMovement(bool inverted_movement);
        void set_Move(bool move);

        int get_X(); //Get methods
        int get_Y();
        bool get_InvertedMovement();
        bool get_Move();

        void generate_Space(); //This function generate a space in the same position of the object

        void change_X(int value); //Changes the values of x and y
        void change_Y(int value);
};

class Bullet : public Object{
    private:
        const wchar_t _character = L'●';
        int dir; //0 = up, 1 = down, 2 = left, 3 = right, 4 = up-left, 5 = up-right, 6 = down-left, 7 = down-right
        int life_span;
        bool _delete;
    public:
        Bullet(int pos_x, int pos_y, int dir, int life_span, bool _delete);

        void set_Dir(int dir); //Set functions
        void set_LifeSpan(int life_span);
        void set_Delete(bool _delete);

        void change_LifeSpan(int value); //This function change the life span of the bullet

        wchar_t get_Character();  //Get methdos
        int get_Dir();
        int get_LifeSpan();
        bool get_Delete();
};

class Player : public Object{
    private:
        static const wchar_t _characters[8];
        int dir; //0 = up, 1 = down, 2 = left, 3 = right, 4 = up-left, 5 = up-right, 6 = down-left, 7 = down-right
        int shoot_delay;
        int current_shoot_delay;
        int ammo;
        int walking_delay;
        int current_walking_delay;
        bool action;
    public:
        void set_Dir(int dir); //Set functions
        void set_Shootdelay(int shoot_delay);
        void set_CurrentShootdelay(int current_shoot_delay);
        void set_Ammo(int ammo);
        void set_WalkingDelay(int walking_delay);
        void set_CurrentWalkingDelay(int current_walking_delay);
        void set_Action(bool action);

        void change_Ammo(int value);
        void change_CurrentShootdelay(int value);
        void change_CurrentWalkingdelay(int value);

        int get_Shootdelay(); //Get methdos
        int get_CurrentShootdelay();
        wchar_t get_Character();
        int get_Dir();
        int get_Ammo();
        int get_WalkingDelay();
        int get_CurrentWalkingDelay();
        bool get_Action();
};

class Door : public Object{
    private:
        int id_trigger;
        int index;
        bool opend;
        static const wchar_t character;
    public:
        Door(int pos_x, int pos_y, int id_trigger, int index, bool opend);

        void set_IdTrigger(int id_trigger);
        void set_Open(bool opend);

        int get_IdTrigger();
        bool get_Open();
        int get_Index();
        wchar_t get_Character();
};

class Ammo : public Object{
    private:
        int ammo;
        static const wchar_t charcater;
        bool empty;
    public:
        Ammo(int pos_x, int pos_y, int ammo, bool empty);

        void set_Ammo(int ammo);
        void set_Empty(bool empty);

        int get_Ammo();
        wchar_t get_Character();
        bool get_Empty();
};

class Trigger : public Object{
    private:
        int id_action;
    public:
        Trigger(int pos_x, int pos_y, int id_action);

        void set_IdAction(int id_action);

        int get_IdAction();
};

class Collider : public Object{
    private:
        bool isSolid;
        int type;
    public:
        Collider(int pos_x, int pos_y, bool isSolid, int type);

        void set_Solid(bool isSolid);
        void set_Type(int type);

        bool get_Solid();
        int get_Type();
};