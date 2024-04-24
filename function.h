# ifndef _FUNCITON__H_
# define _FUNCITON__H_

# include "game.h"
# include "pieces.h"
# include "screen.h"

bool checkInButton(Pos mouseClick, int x, int y){
    if(mouseClick.x >= x && mouseClick.y >= y && mouseClick.x <= x+BUTTON_WIDTH && mouseClick.y <= y+BUTTON_HEIGHT){
        return true;
    }
    return false;
}

bool checkInJump(Pos mouseClick, int x, int y){
    if(mouseClick.x >= x && mouseClick.y >= y && mouseClick.x <= x+JUMP_WIDTH && mouseClick.y <= y+JUMP_HEIGHT){
        return true;
    }
    return false;
}

void handleEvent(Game &game, Pos &mouse, Screen &screen){
    game.get_pos = false;
    SDL_Event e;
    Pos mouseClick;
    SDL_PollEvent(&e);
    SDL_GetMouseState(&mouse.x, &mouse.y);
    switch(e.type){
    case SDL_QUIT:
        game.running = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        SDL_GetMouseState(&mouseClick.x, &mouseClick.y);
        game.get_pos = true;
        break;
    }

    switch(game.page){
    case PAGE_MENU:
        game.last_page = game.page;
        if(checkInButton(mouseClick, 896, 0) == true){
            game.page = PAGE_INFO;
            break;
        }
        if(checkInButton(mouseClick, 448, 480) == true){
            game.running = false;
            break;
        }
        if(checkInButton(mouseClick, 448, 400) == true){
            game.page = PAGE_SETTING;
            break;
        }
        if(checkInButton(mouseClick, 448, 320) == true){
            game.page = PAGE_START;
            break;
        }
        break;
    case PAGE_INFO:
        if(checkInButton(mouseClick, 896, 0) == true){
            game.page = game.last_page;
            break;
        }
        break;
    case PAGE_START:
        if(checkInButton(mouseClick, 896, 0) == true){
            game.page = game.last_page;
            break;
        }
        if(checkInButton(mouseClick, 448, 480) == true){
            game.page = PAGE_GAME;
            game.regism = 0;
            break;
        }
        if(checkInButton(mouseClick, 448, 400) == true){
            game.page = PAGE_GAME;
            game.regism = 1;
            break;
        }
        if(checkInButton(mouseClick, 448, 320) == true){
            game.page = PAGE_GAME;
            game.regism = 2;
            break;
        }
        break;
    case PAGE_SETTING:
        if(checkInButton(mouseClick, 896, 0) == true){
            game.page = game.last_page;
            break;
        }
        if(checkInJump(mouseClick, 576, 128) == true){
            if(game.demo_board == BOARD_BLACK){
                game.demo_board += 12;
            }
            game.demo_board--;
            if(game.unlock_board[game.demo_board-8] == 1){
                game.board = game.demo_board;
            }
            SDL_DestroyTexture(screen.board_game);
            screen.board_game = screen.loadTexture(game.board_color[game.demo_board-8].first.c_str());
        }
        if(checkInJump(mouseClick, 898, 128) == true){
            if(game.demo_board == BOARD_WHITE){
                game.demo_board -= 12;
            }
            game.demo_board++;
            if(game.unlock_board[game.demo_board-8] == 1){
                game.board = game.demo_board;
            }
            SDL_DestroyTexture(screen.board_game);
            screen.board_game = screen.loadTexture(game.board_color[game.demo_board-8].first.c_str());
        }
        if(checkInJump(mouseClick, 576, 192) == true){
            if(game.pieces_p1 == PIECES_BLACK){
                game.pieces_p1 +=12;
            }
            game.pieces_p1--;

        }
        if(checkInJump(mouseClick, 898, 192) == true){
            if(game.pieces_p1 == PIECES_PURPLE){
                game.pieces_p1 -=12;
            }
            game.pieces_p1++;
        }
        if(checkInJump(mouseClick, 576, 256) == true){
            if(game.pieces_p2 == PIECES_BLACK){
                game.pieces_p2 +=12;
            }
            game.pieces_p2--;
        }
        if(checkInJump(mouseClick, 898, 256) == true){
            if(game.pieces_p2 == PIECES_PURPLE){
                game.pieces_p2 -=12;
            }
            game.pieces_p2++;
        }
        if(checkInJump(mouseClick, 576, 320) == true){
            game.back_track--;
        }
        if(checkInJump(mouseClick, 898, 320) == true){
            game.back_track++;
        }
        break;
    case PAGE_GAME:
        game.last_page = game.page;
        SDL_DestroyTexture(screen.board_game);
        screen.board_game = screen.loadTexture(game.board_color[game.board-8].first.c_str());
        if(mouseClick.x >= 572 && mouseClick.y >= 22 && mouseClick.x <= 590 && mouseClick.y <= 40){
            game.page = PAGE_SETTING;
        }
        break;
    }
}

void update(Game &game){
    switch(game.page){
    case PAGE_MENU:
        break;
    case PAGE_INFO:
        break;
    case PAGE_START:
        break;
    case PAGE_SETTING:
        break;
    case PAGE_GAME:
        break;
    }
}

void render(Game &game, Screen &screen, Pos mouse){
    SDL_RenderClear(screen.renderer);
    if(game.get_pos == true){
        screen.playChunk(screen.notify, 0);
    }
    switch(game.page){
    case PAGE_MENU:
        screen.renderTexture(screen.background, 0, 0);
        for(int i=0; i<3; i++){
            int n = checkInButton(mouse, 448, 320+80*i)? 128: 0;
            Rect rect_in(n, 64*i, BUTTON_WIDTH, BUTTON_HEIGHT);
            Rect rect_out(448, 320+80*i, BUTTON_WIDTH, BUTTON_HEIGHT);
            screen.renderTexture(screen.button, rect_in, rect_out);
        }
        for(int i=0; i<1; i++){
            int n = checkInButton(mouse, 896, 0)? 128: 0;
            Rect rect_in(n, 192, BUTTON_WIDTH, BUTTON_HEIGHT);
            Rect rect_out(896, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
            screen.renderTexture(screen.button, rect_in, rect_out);
        }
        break;
    case PAGE_INFO:
        {
        screen.renderTexture(screen.background, 0, 0);
        for(int i=0; i<1; i++){
            int n = checkInButton(mouse, 896, 0)? 384: 256;
            Rect rect_in(n, 192, BUTTON_WIDTH, BUTTON_HEIGHT);
            Rect rect_out(896, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
            screen.renderTexture(screen.button, rect_in, rect_out);
        }
        break;
        }
    case PAGE_START:
        {
        screen.renderTexture(screen.background, 0, 0);
        for(int i=0; i<3; i++){
            int n = checkInButton(mouse, 448, 320+80*i)? 384: 256;
            Rect rect_in(n, 64*i, BUTTON_WIDTH, BUTTON_HEIGHT);
            Rect rect_out(448, 320+80*i, BUTTON_WIDTH, BUTTON_HEIGHT);
            screen.renderTexture(screen.button, rect_in, rect_out);
        }
        for(int i=0; i<1; i++){
            int n = checkInButton(mouse, 896, 0)? 384: 256;
            Rect rect_in(n, 192, BUTTON_WIDTH, BUTTON_HEIGHT);
            Rect rect_out(896, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
            screen.renderTexture(screen.button, rect_in, rect_out);
        }
        break;
        }
    case PAGE_SETTING:
        {
        screen.renderTexture(screen.setting, 0, 0);
        for(int i=0; i<1; i++){
            int n = checkInButton(mouse, 896, 0)? 384: 256;
            Rect rect_in(n, 192, BUTTON_WIDTH, BUTTON_HEIGHT);
            Rect rect_out(896, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
            screen.renderTexture(screen.button, rect_in, rect_out);
        }
        for(int i=0; i<4; i++){
            Rect rect_in(0, 60, JUMP_WIDTH, JUMP_HEIGHT);
            Rect rect_out(576, 128+64*i, JUMP_WIDTH, JUMP_HEIGHT);
            screen.renderTexture(screen.volume_icon, rect_in, rect_out);
        }
        for(int i=0; i<4; i++){
            Rect rect_in(23, 60, JUMP_WIDTH, JUMP_HEIGHT);
            Rect rect_out(898, 128+64*i, JUMP_WIDTH, JUMP_HEIGHT);
            screen.renderTexture(screen.volume_icon, rect_in, rect_out);
        }
        for(int i=0; i<1; i++){
            Rect rect_in(64, 64, 400, 400);
            Rect rect_out(128, 128, 384, 384);
            screen.renderTexture(screen.board_game, rect_in, rect_out);
        }
        for(int i=0; i<1; i++){
            int n = ((game.unlock_board[game.demo_board-8] == 1)? 0: 32);
            Rect rect_in(0, n, 256, 32);
            Rect rect_out(608, 96, 288, 64);
            screen.renderTexture(screen.unlock, rect_in, rect_out);
        }
        for(int i=0; i<12; i++){
            std::cout << game.unlock_board[i] << " ";
        }
        std::cout << std::endl;
        break;
        }
    case PAGE_GAME:
        {
        screen.renderTexture(screen.board_game, 0, 0);
        break;
        }
    }
    SDL_RenderPresent(screen.renderer);
}

# endif // _FUNCITON__H_
