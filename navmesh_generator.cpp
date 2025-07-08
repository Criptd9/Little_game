#include <iostream>
#include <vector>
#include "Libraries/CustomFunctions.h"

#define MAP_WIDTH 17 //The size of the map minus 1
#define MAP_HEIGHT 17

using namespace std;

struct Cell{
    int id; //The id of the cell
    enum types{OBSTACLE_CELL = 1, WALKABLE_CELL = 0}; //The cell can be of two types, walkable or not
    types type; //The type of the current cell
    int pos_x, pos_y; //The coordinates of the cell
    int g_cost, h_cost, f_cost; //g_cost = The distance of the cell from the starting cell; h_cost = The distance of the cell from the ending cell; f_cost = the sum of the ghost and the h_cost
    int parent_cell; //This is the id of the cell where it originated
};

int map[MAP_HEIGHT][MAP_WIDTH] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, //The map
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

vector<Cell*>PathFinder(Cell* starting_cell, Cell* ending_cell, vector<Cell*>cells){ //This procedure returns the path from the starting cell to the ending cell
    vector<Cell*>path; //The path that will be returned

    vector<Cell*>cells_finded; //The surrounding cells found

    vector<Cell*>cells_explored; //The cells that were already explored

    bool path_finded = false;

    Cell* current_cell = new Cell; //From this cell we'll calculate the rest of them
    current_cell = starting_cell;
    cells_explored.push_back(current_cell);

    do{
        int init_pos_x = current_cell->pos_x - 1; //We start to see all the closest cells to the current one by starting from the top left cell
        int init_pos_y = current_cell->pos_y - 1;

        bool cells_calculated = false;

        do{
            Cell* new_cell = new Cell;
            bool obstacle = false;

            for(Cell* t_cell : cells){ //We see if the cell that we are searching is an obstacle or not
                if(init_pos_x == t_cell->pos_x && init_pos_y == t_cell->pos_y && t_cell->type == t_cell->WALKABLE_CELL){ //
                    new_cell = t_cell;
                    break;
                }
                else if(init_pos_x == t_cell->pos_x && init_pos_y == t_cell->pos_y && t_cell->type == t_cell->OBSTACLE_CELL){
                    obstacle = true;
                    break;
                }
            }

            if(!obstacle){ //If it isn't an obstacle, we start to calculate all the values of the cell
                int current_pos_x = init_pos_x;
                int current_pos_y = init_pos_y;

                bool cell_reached = false;

                new_cell->g_cost = 0; //We reset the values of the cell to be sure that the calculations'll be right
                new_cell->h_cost = 0;
                new_cell->f_cost = 0;

                //We calculate the g-cost of the cell
                do{
                    bool x_changed = false; //If both variabiles remain the same, it means that we've arrived to the starting cell, if one of them is true it means that we've moved vertically or horizzontally and if both are true we've moved diagonally
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

                //We calculate the h-cost of the cell
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

                //We calculate the f-cost of the cell
                new_cell->f_cost = new_cell->g_cost + new_cell->h_cost;

                //We assign the parent cell (so the current one) to this cell
                if(!cells_finded.empty()){
                    bool cell_f = false;
                    
                    //First we see if the cell was already calculated and if the new f-cost is more advantageous than the old one, if so we assign the parent cell, otherwise the simple skip the cell
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

                    //If the cell calculated was not present already in the fined cells, then we assign the id of the current cell as the parent of the new cell and we add the new cell to the cells found
                    if(!cell_f){
                        new_cell->parent_cell = current_cell->id;
                        cells_finded.push_back(new_cell);
                    }
                }
                else{
                    //This section is the same as the other one, except that here we simple assign to the discovered cells the new one
                    new_cell->parent_cell = current_cell->id;
                    cells_finded.push_back(new_cell);
                }
                
                //Now we simple update the position of the initial position of the cell, until we reach the last one nearby
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
            //Otherwise we simple change cell
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

        //We sort all the funded cells by their f-cost, from the lowest to the highest, we use an bubble sort to do the job
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

        //Now we'll choose the next current cell by their f-cost or by their h-cost (it depends)
        current_cell = new Cell;

        bool cell_f = false;

        //First we choose a cell from the discovered ones and make sure to take only one of them that isn't already explored
        for(Cell* i_cell : cells_finded){
            for(Cell* j_cell : cells_explored){
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

        //Then we start to search for the best "looking" cell, by seeing the one with the best f-cost or the best h-cost
        for(Cell* i_cell : cells_finded){
            //If the f-cost of the cell is major of the f-cost of the cell that we are analyzing, we simple choose the new one as the current cell by always making sure that the cell founded isn't already explored
            if(current_cell->f_cost > i_cell->f_cost){
                for(Cell* j_cell : cells_explored){
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
            //If the f-costs are the same, we apply the same reasoning of before but for the h-cost
            if(current_cell->f_cost == i_cell->f_cost){
                if(current_cell->h_cost > i_cell->h_cost){
                    for(Cell* j_cell : cells_explored){
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

        //After all of that, we simple assign at the explored cells the current cell
        cells_explored.push_back(current_cell);

        /*system("cls");

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
        system("pause");*/

        //If the h-cost of the current cell is 0, it means that we've reached the final cell
        if(current_cell->h_cost == 0){
            path_finded = true;
            bool path_created = false;

           //We start from the current cell to see all the parents of the cells to arrive at the first one
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

    return path; //We return the path
}

int main(){
    vector<Cell*>cells;

    int id = 0;

    //We start to create every cell
    for(int i=0;i<MAP_HEIGHT;i++){
        for(int j=0;j<MAP_WIDTH;j++){
            Cell* cell = new Cell;

            cell->id = id;
            id++;

            if(map[i][j] == 0){
                cell->type = cell->WALKABLE_CELL;
            }
            else{
                cell->type = cell->OBSTACLE_CELL;
            }

            cell->pos_x = j;
            cell->pos_y = i;

            cell->g_cost = 0;
            cell->h_cost = 0;
            cell->f_cost = 0;

            cell->parent_cell = cell->id;

            cells.push_back(cell);
        }
    }

    //The starting cell and the ending cell (just for debugging)
    Cell* starting_cell = new Cell;
    Cell* ending_cell = new Cell;

    starting_cell->id = 263;
    ending_cell->id = 93;

    //We find the starting cell and the ending cell inside the map by their ids (just for debugging)
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

    //We print the map before the path (just for debugging)
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

    //We print the map before the path (just for debugging)
    vector<Cell*>path;

    path = PathFinder(starting_cell, ending_cell, cells);

    system("cls");

    //We print every cell of the path generated (just for debugging)
    for(Cell* t_cell: path){
        cout<<"Cell id:"<<t_cell->id<<" Cell type:"<<t_cell->type<<" Cell pos_X:"<<t_cell->pos_x<<" Cell pos_Y:"<<t_cell->pos_y<<" Cell G-cost:"<<t_cell->g_cost<<" Cell H-cost:"<<t_cell->h_cost<<" Cell F-cost:"<<t_cell->f_cost<<" Cell Parent:"<<t_cell->parent_cell<<"\n\n";
    }

    //We print the map but this time with the path printed (just for debugging)
    for(int i=0;i<MAP_HEIGHT;i++){
        for(int j=0;j<MAP_WIDTH;j++){
            for(Cell* t_cell : path){
                if(ending_cell->pos_x == j && ending_cell->pos_y == i){
                    cout<<"B";
                    j++;
                }
                if(t_cell->pos_x == j && t_cell->pos_y == i){
                    cout<<"o";
                    j++;
                }
            }
            if(starting_cell->pos_x == j && starting_cell->pos_y == i){
                cout<<"A";
                j++;
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