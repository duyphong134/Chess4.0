# include "function.h"

void wait(){
    SDL_Event e;
    bool quit = false;
    while(!quit){
        SDL_PollEvent(&e);
        switch(e.type){
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            quit = true;
            break;
        }
    }
}

int main(int argc, char *argv[]){
    Screen screen;
    screen.init();

    Game game;
    game.init();

    Uint32 frame_start;
    Uint32 frame_time;

    Pos mouse;
    Pos mouseClick;
    Pieces piece;
//    for(int i=0; i<64; i++){
//        std::cout << game.pos_v1[game.move_count][i] << " ";
//        if(i %8==7){
//            std::cout << std::endl;
//        }
//    }
//    std::cout << std::endl;
//    for(int i=0; i<8; i++){
//        for(int j=0; j<8; j++){
//            std::cout << game.pos_v2[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//    std::cout << std::endl;
    while(game.running == true){
        frame_start = SDL_GetTicks();

        handleEvent(game, mouse, mouseClick);

        update(game, screen, mouseClick, piece);

        render(game, screen, mouse);

        frame_time = SDL_GetTicks() - frame_start;
        if(FRAME_DELAY >frame_time){
            SDL_Delay(FRAME_DELAY - frame_time);
        }
    }
    game.quit();
    screen.quit();
//    return 0;
}
