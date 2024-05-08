# ifndef _PIECES__H_
# define _PIECES__H_

std::string tranToNoteCrood(int x, int y){
    std::string s;
    s += (char)(y+97);
    s += (char)(56-x);
    return s;
}

void tranToCrood(int &x, int &y, std::string s){
    y = (int)(s[0])-97;
    x= 56- (int)(s[1]);
}

bool checkPieceMove(std::string s, std::pair<std::string, std::string> move_note[], int move_count){
    for(int i=1; i<=move_count; i++){
        if(s == move_note[i].first){
            return true;
        }
    }
    return false;
}

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
    int dis_x =0;
    int dis_y =0;
    std::string enable_note[32];
    int enable_count;

    void evaluateDistant(bool &x){
        if(dis_x == (pos2.y-pos1.y)*64 && dis_y == (pos2.x-pos1.x)*64){
            x = false;
        }else{
        dis_x += (pos2.y-pos1.y)*4;
        dis_y += (pos2.x-pos1.x)*4;
        }
    }

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
            get_pawn_special = false;
            if(game.pos_v2[pos1.x-game.pos_v2[pos1.x][pos1.y]][pos1.y]* game.pos_v2[pos1.x][pos1.y] == 0){
                enable[pos1.x-game.pos_v2[pos1.x][pos1.y]][pos1.y] = true;
                if(game.pos_v2[pos1.x-2*game.pos_v2[pos1.x][pos1.y]][pos1.y]* game.pos_v2[pos1.x][pos1.y] == 0 && pos1.x == (4-(1-5*game.pos_v2[pos1.x][pos1.y])/2)){
                    enable[pos1.x-2*game.pos_v2[pos1.x][pos1.y]][pos1.y] = true;
                }
            }
            if(game.pos_v2[pos1.x-game.pos_v2[pos1.x][pos1.y]][pos1.y-1]* game.pos_v2[pos1.x][pos1.y] <0){
                enable[pos1.x-game.pos_v2[pos1.x][pos1.y]][pos1.y-1] = true;
            }
            if(game.pos_v2[pos1.x-game.pos_v2[pos1.x][pos1.y]][pos1.y+1]* game.pos_v2[pos1.x][pos1.y] <0){
                enable[pos1.x-game.pos_v2[pos1.x][pos1.y]][pos1.y+1] = true;
            }
            if(pos1.x == (3+(1-game.pos_v2[pos1.x][pos1.y])/2)){
                if(game.move_note[game.move_count].second == tranToNoteCrood(pos1.x, pos1.y+1) && game.move_note[game.move_count].first == tranToNoteCrood(pos1.x-2*game.pos_v2[pos1.x][pos1.y], pos1.y+1)){
                    enable[pos1.x-game.pos_v2[pos1.x][pos1.y]][pos1.y+1] = true;
                }
                if(game.move_note[game.move_count].second == tranToNoteCrood(pos1.x, pos1.y-1) && game.move_note[game.move_count].first == tranToNoteCrood(pos1.x-2*game.pos_v2[pos1.x][pos1.y], pos1.y-1)){
                    enable[pos1.x-game.pos_v2[pos1.x][pos1.y]][pos1.y-1] = true;
                }
            }
            break;
        case 2:
        case -2:
            for(int i=0; i<8; i++){
                for(int j=0; j<8; j++){
                    if(((pos1.x -i)*(pos1.x-i)+(pos1.y -j)*(pos1.y -j)) == 5 && pos1.x != i && pos1.y != j && game.pos_v2[i][j]* game.pos_v2[pos1.x][pos1.y] <= 0){
                        enable[i][j] = true;
                    }
                }
            }
            break;
        case 3:
        case -3:
            for(int i=1; i<8; i++){
                if(north_east == false && pos1.x+i<8 && pos1.y-i>=0 && game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x+i][pos1.y-i] <=0){
                    enable[pos1.x+i][pos1.y-i] = true;
                    if(game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x+i][pos1.y-i] <0){
                        north_east = true;
                    }
                } else {
                    north_east = true;
                }
                if(north_west == false && pos1.x-i>=0 && pos1.y-i>=0 && game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x-i][pos1.y-i] <=0){
                    enable[pos1.x-i][pos1.y-i] = true;
                    if(game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x-i][pos1.y-i] <0){
                        north_west = true;
                    }
                } else {
                    north_west = true;
                }
                if(south_east == false && pos1.x+i<8 && pos1.y+i<8 && game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x+i][pos1.y+i] <=0){
                    enable[pos1.x+i][pos1.y+i] = true;
                    if(game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x+i][pos1.y+i] <0){
                        south_east = true;
                    }
                } else {
                    south_east = true;
                }
                if(south_west == false && pos1.x-i>=0 && pos1.y+i<8 && game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x-i][pos1.y+i] <=0){
                    enable[pos1.x-i][pos1.y+i] = true;
                    if(game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x-i][pos1.y+i] <0){
                        south_west = true;
                    }
                } else {
                    south_west = true;
                }
            }
            break;
        case 4:
        case -4:
            for(int i=1; i<8; i++){
                if(east == false && pos1.x+i<8 && game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x+i][pos1.y] <=0){
                    enable[pos1.x+i][pos1.y]= true;
                    if(game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x+i][pos1.y] <0){
                        east = true;
                    }
                } else {
                    east = true;
                }
                if(west == false && pos1.x-i>=0 && game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x-i][pos1.y] <=0){
                    enable[pos1.x-i][pos1.y] = true;
                    if(game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x-i][pos1.y] <0){
                        west = true;
                    }
                } else {
                    west = true;
                }
                if(north == false && pos1.y-i>=0 && game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x][pos1.y-i] <=0){
                    enable[pos1.x][pos1.y-i] = true;
                    if(game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x][pos1.y-i] <0){
                        north = true;
                    }
                } else {
                    north = true;
                }
                if(south == false && pos1.y+i<8 && game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x][pos1.y+i] <=0){
                    enable[pos1.x][pos1.y+i] = true;
                    if(game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x][pos1.y+i] <0){
                        south = true;
                    }
                } else {
                    south = true;
                }
            }
            break;
        case 5:
        case -5:
            for(int i=1; i<8; i++){
                if(north_east == false && pos1.x+i<8 && pos1.y-i>=0 && game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x+i][pos1.y-i] <=0){
                    enable[pos1.x+i][pos1.y-i] = true;
                    if(game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x+i][pos1.y-i] <0){
                        north_east = true;
                    }
                } else {
                    north_east = true;
                }
                if(north_west == false && pos1.x-i>=0 && pos1.y-i>=0 && game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x-i][pos1.y-i] <=0){
                    enable[pos1.x-i][pos1.y-i] = true;
                    if(game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x-i][pos1.y-i] <0){
                        north_west = true;
                    }
                } else {
                    north_west = true;
                }
                if(south_east == false && pos1.x+i<8 && pos1.y+i<8 && game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x+i][pos1.y+i] <=0){
                    enable[pos1.x+i][pos1.y+i] = true;
                    if(game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x+i][pos1.y+i] <0){
                        south_east = true;
                    }
                } else {
                    south_east = true;
                }
                if(south_west == false && pos1.x-i>=0 && pos1.y+i<8 && game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x-i][pos1.y+i] <=0){
                    enable[pos1.x-i][pos1.y+i] = true;
                    if(game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x-i][pos1.y+i] <0){
                        south_west = true;
                    }
                } else {
                    south_west = true;
                }
                if(east == false && pos1.x+i<8 && game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x+i][pos1.y] <=0){
                    enable[pos1.x+i][pos1.y]= true;
                    if(game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x+i][pos1.y] <0){
                        east = true;
                    }
                } else {
                    east = true;
                }
                if(west == false && pos1.x-i>=0 && game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x-i][pos1.y] <=0){
                    enable[pos1.x-i][pos1.y] = true;
                    if(game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x-i][pos1.y] <0){
                        west = true;
                    }
                } else {
                    west = true;
                }
                if(north == false && pos1.y-i>=0 && game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x][pos1.y-i] <=0){
                    enable[pos1.x][pos1.y-i] = true;
                    if(game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x][pos1.y-i] <0){
                        north = true;
                    }
                } else {
                    north = true;
                }
                if(south == false && pos1.y+i<8 && game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x][pos1.y+i] <=0){
                    enable[pos1.x][pos1.y+i] = true;
                    if(game.pos_v2[pos1.x][pos1.y]*game.pos_v2[pos1.x][pos1.y+i] <0){
                        south = true;
                    }
                } else {
                    south = true;
                }
            }
            break;
        case 6:
        case -6:
            castle = false;
            for(int i=0; i<8; i++){
                for(int j=0; j<8; j++){
                    if((((pos1.x -i)*(pos1.x-i)+(pos1.y -j)*(pos1.y -j)) == 1 || ((pos1.x -i)*(pos1.x-i)+(pos1.y -j)*(pos1.y -j)) == 2) && game.pos_v2[i][j]* game.pos_v2[pos1.x][pos1.y] <= 0){
                        enable[i][j] = true;
                    }
                    if(checkPieceMove("e1", game.move_note, game.move_count) == false && checkPieceMove("h1", game.move_note, game.move_count) == false && game.pos_v2[pos1.x][pos1.y+1] == 0 && game.pos_v2[pos1.x][pos1.y+2] == 0){
                        enable[pos1.x][pos1.y+2] = true;
                    }
                    if(checkPieceMove("e1", game.move_note, game.move_count) == false && checkPieceMove("a1", game.move_note, game.move_count) == false && game.pos_v2[pos1.x][pos1.y-1] == 0 && game.pos_v2[pos1.x][pos1.y-2] == 0 && game.pos_v2[pos1.x][pos1.y-3] == 0){
                        enable[pos1.x][pos1.y-2] = true;
                    }
                    if(checkPieceMove("e8", game.move_note, game.move_count) == false && checkPieceMove("h8", game.move_note, game.move_count) == false && game.pos_v2[pos1.x][pos1.y+1] == 0 && game.pos_v2[pos1.x][pos1.y+2] == 0){
                        enable[pos1.x][pos1.y+2] = true;
                    }
                    if(checkPieceMove("e8", game.move_note, game.move_count) == false && checkPieceMove("a8", game.move_note, game.move_count) == false && game.pos_v2[pos1.x][pos1.y-1] == 0 && game.pos_v2[pos1.x][pos1.y-2] == 0 && game.pos_v2[pos1.x][pos1.y-3] == 0){
                        enable[pos1.x][pos1.y-2] = true;
                    }
                }
            }
            break;
        }

        enable_count =0;
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                if(enable[i][j] == true){
                    enable_note[enable_count] = tranToNoteCrood(i, j);
                    enable_count++;
                }
            }
        }
    }
};

# endif // _PIECES__H_
