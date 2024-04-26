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
    for(int i=0; i<12; i++){
        std::cout << game.unlock_board[i] << " ";
    }
    std::cout << std::endl;
    for(int i=0; i<12; i++){
        std::cout << game.unlock_pieces_p1[i] << " ";
    }
    std::cout << std::endl;
    for(int i=0; i<12; i++){
        std::cout << game.unlock_pieces_p2[i] << " ";
    }
    std::cout << std::endl;
    for(int i=0; i<17; i++){
        std::cout << game.unlock_back_track[i] << " ";
    }
    std::cout << std::endl;
    while(game.running == true){
        frame_start = SDL_GetTicks();

        handleEvent(game, mouse, screen);

        update(game);

        render(game, screen, mouse);

        frame_time = SDL_GetTicks() - frame_start;
        if(FRAME_DELAY >frame_time){
            SDL_Delay(FRAME_DELAY - frame_time);
        }
    }
    game.quit();
    screen.quit();
    return 0;
}
