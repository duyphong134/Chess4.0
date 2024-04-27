# ifndef _PIECES__H_
# define _PIECES__H_

struct Pos{
    int x, y;
    void getPos(int x_, int y_){
        x = x_;
        y = y_;
    }
};

struct Pieces{
    Pos pos1;
    Pos pos2;
    bool enable[8][8];
    bool get_pawn_special;
    bool castle;

    void Pos1GetCoord(Pos pos){
        pos1.x = pos.y/64-1;
        pos1.y = pos.x/64-1;
    }

    void Pos2GetCoord(Pos pos){
        pos2.x = pos.y/64-1;
        pos2.y = pos.x/64-1;
    }

    void init(Game &game){
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                enable[i][j] = false;
            }
        }
        bool north = false;
        bool west = false;
        bool south = false;
        bool east = false;
        bool north_west = false;
        bool north_east = false;
        bool south_west = false;
        bool south_east = false;

        switch(game.pos_v2[pos1.x][pos1.y]){
        case 1:
        case -1:
            break;
        case 2:
        case -2:
            for(int i = 0; i<8; i++){
                for(int j=0; j<8; j++){
                    if(((pos1.x -i)*(pos1.x-i)+(pos1.y -j)*(pos1.y -j)) == 5 && pos1.x != i && pos1.y != j && game.pos_v2[i][j]* game.pos_v2[pos1.x][pos1.y] <= 0){
                        enable[i][j] = true;
                    }
                }
            }
            break;
        case 3:
        case -3:
            break;
        case 4:
        case -4:
            break;
        case 5:
        case -5:
            break;
        case 6:
        case -6:
            break;
        }
    }
};

# endif // _PIECES__H_
