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

void handleEvent(Game &game, Pos &mouse){
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
            game.demo_board--;
            if(game.unlock_board[game.board] == true){
                game.board = game.demo_board;
            }
        }
        if(checkInJump(mouseClick, 898, 128) == true){
            game.demo_board++;
            if(game.unlock_board[game.demo_board] == true){
                game.board = game.demo_board;
            }
        }
        if(checkInJump(mouseClick, 576, 192) == true){
            game.demo_pieces_p1--;
            if(game.unlock_board[game.demo_pieces_p1] == true){
                game.pieces_p1 = game.demo_pieces_p1;
            }
        }
        if(checkInJump(mouseClick, 898, 192) == true){
            game.demo_pieces_p1++;
            if(game.unlock_board[game.demo_pieces_p1] == true){
                game.pieces_p1 = game.demo_pieces_p1;
            }
        }
        if(checkInJump(mouseClick, 576, 256) == true){
            game.demo_pieces_p2--;
            if(game.unlock_board[game.demo_pieces_p2] == true){
                game.pieces_p2 = game.demo_pieces_p2;
            }
        }
        if(checkInJump(mouseClick, 898, 256) == true){
            game.demo_pieces_p2++;
            if(game.unlock_board[game.demo_pieces_p2] == true){
                game.pieces_p2 = game.demo_pieces_p2;
            }
        }
        if(checkInJump(mouseClick, 576, 320) == true){
            game.demo_back_track--;
            if(game.unlock_board[game.demo_back_track] == true){
                game.back_track = game.demo_back_track;
            }
        }
        if(checkInJump(mouseClick, 898, 320) == true){
            game.demo_back_track++;
            if(game.unlock_board[game.demo_back_track] == true){
                game.back_track = game.demo_back_track;
            }
        }
        break;
    case PAGE_GAME:
        game.last_page = game.page;
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

void render(Game game, Screen screen, Pos mouse){
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
        screen.renderTexture(screen.background, 0, 0);
        for(int i=0; i<1; i++){
            int n = checkInButton(mouse, 896, 0)? 384: 256;
            Rect rect_in(n, 192, BUTTON_WIDTH, BUTTON_HEIGHT);
            Rect rect_out(896, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
            screen.renderTexture(screen.button, rect_in, rect_out);
        }
        break;
    case PAGE_START:
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
    case PAGE_SETTING:
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
            Rect rect_in(30, 60, JUMP_WIDTH, JUMP_HEIGHT);
            Rect rect_out(898, 128+64*i, JUMP_WIDTH, JUMP_HEIGHT);
            screen.renderTexture(screen.volume_icon, rect_in, rect_out);
        }
        break;
    case PAGE_GAME:
        screen.renderTexture(screen.board_game, 0, 0);
        break;
    }
    SDL_RenderPresent(screen.renderer);
}

# endif // _FUNCITON__H_
