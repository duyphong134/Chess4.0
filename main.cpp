# include "function.h"

int main(int argc, char *argv[]){
    Screen screen;
    screen.init();

    Game game;
    game.init();

    Uint32 frame_start;
    Uint32 frame_time;

    Pos mouse;
    for(int i=0; i<12; i++){
        std::cout << game.unlock_board[i] <<" ";
    }
    std::cout << std::endl;
    while(game.running == true){
        frame_start = SDL_GetTicks();

        handleEvent(game, mouse, screen);

        update(game);

        render(game, screen, mouse);
//        for(int i=0; i<12; i++){
//            std::cout << game.unlock_board[i] << " ";
//        }
//        std::cout << std::endl;
        frame_time = SDL_GetTicks() - frame_start;
        if(FRAME_DELAY >frame_time){
            SDL_Delay(FRAME_DELAY - frame_time);
        }
    }

    game.quit();
    screen.quit();
    return 0;
}
