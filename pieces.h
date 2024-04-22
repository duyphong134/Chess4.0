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
    int x, y;
    void getCoord(Pos pos){
        x = pos.y/64-1;
        y = pos.x/64-1;
    }
};

# endif // _PIECES__H_
