#include <iostream>
#include <vector>
#include "Libraries/CustomFunctions.h"

#define MAP_WIDTH 17 //The size of the map minus 1
#define MAP_HEIGHT 17

using namespace std;

struct Cell{
    int id;
    int type;
    int pos_x, pos_y;
    int g_cost, h_cost, f_cost;
    int parent_cell;
};

int map[MAP_HEIGHT][MAP_WIDTH] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

vector<Cell*>PathFinder(Cell* starting_cell, Cell* ending_cell, vector<Cell*>cells){
    vector<Cell*>path;

    vector<Cell*>cells_finded;

    vector<Cell*>cells_selected;

    bool path_finded = false;

    Cell* current_cell = new Cell;
    current_cell = starting_cell;
    cells_selected.push_back(current_cell);

    do{
        int init_pos_x = current_cell->pos_x - 1;
        int init_pos_y = current_cell->pos_y - 1;

        bool cells_calculated = false;

        do{
            Cell* new_cell = new Cell;
            bool wall = false;

            for(Cell* t_cell : cells){
                if(init_pos_x == t_cell->pos_x && init_pos_y == t_cell->pos_y && t_cell->type == 0){
                    new_cell = t_cell;
                    break;
                }
                else if(init_pos_x == t_cell->pos_x && init_pos_y == t_cell->pos_y && t_cell->type == 1){
                    wall = true;
                    break;
                }
            }

            if(!wall){
                int current_pos_x = init_pos_x;
                int current_pos_y = init_pos_y;

                bool cell_reached = false;

                new_cell->g_cost = 0;
                new_cell->h_cost = 0;
                new_cell->f_cost = 0;

                do{
                    bool x_changed = false;
                    bool y_changed = false;

                    if(current_pos_x > starting_cell->pos_x){
                        current_pos_x--;
                        x_changed = true;
                    }
                    else if(current_pos_x < starting_cell->pos_x){
                        current_pos_x++;
                        x_changed = true;
                    }

                    if(current_pos_y > starting_cell->pos_y){
                        current_pos_y--;
                        y_changed = true;
                    }
                    else if(current_pos_y < starting_cell->pos_y){
                        current_pos_y++;
                        y_changed = true;
                    }

                    if(!x_changed && !y_changed){
                        cell_reached = true;
                    }
                    if(x_changed && !y_changed || !x_changed && y_changed){
                        new_cell->g_cost += 10;
                    }
                    if(x_changed && y_changed){
                        new_cell->g_cost += 14;
                    }

                }while(!cell_reached);

                cell_reached = false;

                current_pos_x = init_pos_x;
                current_pos_y = init_pos_y;

                do{
                    bool x_changed = false;
                    bool y_changed = false;

                    if(current_pos_x > ending_cell->pos_x){
                        current_pos_x--;
                        x_changed = true;
                    }
                    else if(current_pos_x < ending_cell->pos_x){
                        current_pos_x++;
                        x_changed = true;
                    }

                    if(current_pos_y > ending_cell->pos_y){
                        current_pos_y--;
                        y_changed = true;
                    }
                    else if(current_pos_y < ending_cell->pos_y){
                        current_pos_y++;
                        y_changed = true;
                    }

                    if(!x_changed && !y_changed){
                        cell_reached = true;
                    }
                    if(x_changed && !y_changed || !x_changed && y_changed){
                        new_cell->h_cost += 10;
                    }
                    if(x_changed && y_changed){
                        new_cell->h_cost += 14;
                    }
                }while(!cell_reached);

                new_cell->f_cost = new_cell->g_cost + new_cell->h_cost;

                if(!cells_finded.empty()){
                    bool cell_f = false;
                    
                    for(int i=0;i<cells_finded.size();i++){
                        if(new_cell->id == cells_finded[i]->id){
                            cell_f = true;
                            if(new_cell->f_cost < cells_finded[i]->f_cost){
                                new_cell->parent_cell = current_cell->id;
                                cells_finded[i] = new_cell;
                            }
                            break;
                        }
                    }

                    if(!cell_f){
                        new_cell->parent_cell = current_cell->id;
                        cells_finded.push_back(new_cell);
                    }
                }
                else{
                    new_cell->parent_cell = current_cell->id;
                    cells_finded.push_back(new_cell);
                }
                
                init_pos_x++;
                if(init_pos_x == current_cell->pos_x && init_pos_y == current_cell->pos_y){
                    init_pos_x++;
                }
                if(init_pos_x > current_cell->pos_x + 1){
                    init_pos_x = current_cell->pos_x - 1;
                    init_pos_y++;
                }
                if(init_pos_y > current_cell->pos_y + 1){
                    cells_calculated = true;
                }
            }
            else{
                init_pos_x++;
                if(init_pos_x == current_cell->pos_x && init_pos_y == current_cell->pos_y){
                    init_pos_x++;
                }
                if(init_pos_x > current_cell->pos_x + 1){
                    init_pos_x = current_cell->pos_x - 1;
                    init_pos_y++;
                }
                if(init_pos_y > current_cell->pos_y + 1){
                    cells_calculated = true;
                }
            }

        }while(!cells_calculated);

        for(int i=0;i<cells_finded.size();i++){
            for(int j=0;j<cells_finded.size();j++){
                if(cells_finded[i]->f_cost > cells_finded[j]->f_cost){
                    Cell* a_cell = new Cell;
                    a_cell = cells_finded[j];
                    cells_finded[j] = cells_finded[i];
                    cells_finded[i] = a_cell;
                }
            }
        }

        current_cell = new Cell;

        bool cell_f = false;

        for(Cell* i_cell : cells_finded){
            for(Cell* j_cell : cells_selected){
                if(i_cell == j_cell){
                    cell_f = true;
                    break;
                }
            }
            if(!cell_f){
                current_cell = i_cell;
                break;
            }
            else{
                cell_f = false;
                continue;
            }
        }

        for(Cell* i_cell : cells_finded){
            if(current_cell->f_cost > i_cell->f_cost){
                for(Cell* j_cell : cells_selected){
                    if(i_cell == j_cell){
                        cell_f = true;
                        break;
                    }
                }
                if(!cell_f){
                    current_cell = i_cell;
                }
                else{
                    cell_f = false;
                    continue;
                }
            }
            if(current_cell->f_cost == i_cell->f_cost){
                if(current_cell->h_cost > i_cell->h_cost){
                    for(Cell* j_cell : cells_selected){
                        if(i_cell == j_cell){
                            cell_f = true;
                            break;
                        }
                    }
                    
                    if(!cell_f){
                        current_cell = i_cell;
                    }
                    else{
                        cell_f = false;
                        continue;
                    }
            }
            }
        }

        cells_selected.push_back(current_cell);

        system("cls");

        for(int i=0;i<MAP_HEIGHT;i++){
            for(int j=0;j<MAP_WIDTH;j++){
                if(starting_cell->pos_x == j && starting_cell->pos_y == i){
                    cout<<"A";
                    j++;
                }
                if(ending_cell->pos_x == j && ending_cell->pos_y == i){
                    cout<<"B";
                    j++;
                }
                for(Cell* t_cell : cells_finded){
                    if(current_cell->pos_x == j && current_cell->pos_y == i){
                        cout<<"C";
                        j++;
                    }
                    if(t_cell->pos_x == j && t_cell->pos_y == i){
                        cout<<"$";
                        j++;
                    }
                }
                if(map[i][j] == 0){
                    cout<<" ";
                }
                if(map[i][j] == 1){
                    cout<<"#";
                }
            }
            cout<<""<<endl;
        }

        cout<<"\n";
        for(Cell* t_cell : cells_finded){
            cout<<"Cell id:"<<t_cell->id<<" Cell type:"<<t_cell->type<<" Cell pos_X:"<<t_cell->pos_x<<" Cell pos_Y:"<<t_cell->pos_y<<" Cell G-cost:"<<t_cell->g_cost<<" Cell H-cost:"<<t_cell->h_cost<<" Cell F-cost:"<<t_cell->f_cost<<" Cell Parent:"<<t_cell->parent_cell<<"\n\n";
        }

        cout<<"Current cell:"<<current_cell->id<<endl;
        system("pause");

        if(current_cell->h_cost == 0){
            path_finded = true;
            bool path_created = false;

            do{
                path.push_back(current_cell);
                for(Cell* t_cell : cells_finded){
                    if(t_cell->id == current_cell->parent_cell){
                        current_cell = t_cell;
                        break;
                    }
                }

                if(current_cell == starting_cell){
                    path_created = true;
                }

            }while(!path_created);
        }

    }while(!path_finded);

    return path;
}

int main(){
    vector<Cell*>cells;

    int id = 0;

    for(int i=0;i<MAP_HEIGHT;i++){
        for(int j=0;j<MAP_WIDTH;j++){
            Cell* cell = new Cell;

            cell->id = id;
            id++;

            cell->type = map[i][j];

            cell->pos_x = j;
            cell->pos_y = i;

            cell->g_cost = 0;
            cell->h_cost = 0;
            cell->f_cost = 0;

            cell->parent_cell = cell->id;

            cells.push_back(cell);
        }
    }

    Cell* starting_cell = new Cell;
    Cell* ending_cell = new Cell;

    starting_cell->id = 263;
    ending_cell->id = 93;

    for(Cell* t_cell : cells){
        if(starting_cell->id == t_cell->id){
            starting_cell = t_cell;
            break;
        }
    }
    for(Cell* t_cell : cells){
        if(ending_cell->id == t_cell->id){
            ending_cell = t_cell;
            break;
        }
    }

    for(int i=0;i<MAP_HEIGHT;i++){
        for(int j=0;j<MAP_WIDTH;j++){
            if(starting_cell->pos_x == j && starting_cell->pos_y == i){
                cout<<"A";
                j++;
            }
            if(ending_cell->pos_x == j && ending_cell->pos_y == i){
                cout<<"B";
                j++;
            }
            if(map[i][j] == 0){
                cout<<" ";
            }
            if(map[i][j] == 1){
                cout<<"#";
            }
        }
        cout<<"\n";
    }

    system("pause");

    vector<Cell*>path;

    path = PathFinder(starting_cell, ending_cell, cells);

    system("cls");

    for(Cell* t_cell: path){
        cout<<"Cell id:"<<t_cell->id<<" Cell type:"<<t_cell->type<<" Cell pos_X:"<<t_cell->pos_x<<" Cell pos_Y:"<<t_cell->pos_y<<" Cell G-cost:"<<t_cell->g_cost<<" Cell H-cost:"<<t_cell->h_cost<<" Cell F-cost:"<<t_cell->f_cost<<" Cell Parent:"<<t_cell->parent_cell<<"\n\n";
    }

    for(int i=0;i<MAP_HEIGHT;i++){
        for(int j=0;j<MAP_WIDTH;j++){
            if(starting_cell->pos_x == j && starting_cell->pos_y == i){
                cout<<"A";
                j++;
            }
            if(ending_cell->pos_x == j && ending_cell->pos_y == i){
                cout<<"B";
                j++;
            }
            for(Cell* t_cell : path){
                if(t_cell->pos_x == j && t_cell->pos_y == i){
                    cout<<"$";
                    j++;
                }
            }
            if(map[i][j] == 0){
                cout<<" ";
            }
            if(map[i][j] == 1){
                cout<<"#";
            }
        }
        cout<<""<<endl;
    }

    cout<<"\n";

    system("pause");

    return 0;
}