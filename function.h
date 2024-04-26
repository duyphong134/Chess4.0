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
    SDL_Event e;
    Pos mouseClick;
    SDL_PollEvent(&e);
    SDL_GetMouseState(&mouse.x, &mouse.y);
    game.get_pos = false;
    switch(e.type){
    case SDL_QUIT:
        game.running = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        SDL_GetMouseState(&mouseClick.x, &mouseClick.y);
        std::cout << mouseClick.x << " " << mouseClick.y << std::endl;
        game.get_pos = true;
        break;
    }

    switch(game.page){
    case PAGE_MENU:
        game.last_page = game.page;
        if(checkInButton(mouseClick, 896, 0) == true && game.get_pos == true){
            game.page = PAGE_INFO;
            break;
        }
        if(checkInButton(mouseClick, 448, 480) == true && game.get_pos == true){
            game.running = false;
            break;
        }
        if(checkInButton(mouseClick, 448, 400) == true && game.get_pos == true){
            game.page = PAGE_SETTING;
            break;
        }
        if(checkInButton(mouseClick, 448, 320) == true && game.get_pos == true){
            game.page = PAGE_START;
            break;
        }
        break;
    case PAGE_INFO:
        if(checkInButton(mouseClick, 896, 0) == true && game.get_pos == true){
            game.page = game.last_page;
            break;
        }
        break;
    case PAGE_START:
        if(checkInButton(mouseClick, 896, 0) == true && game.get_pos == true){
            game.page = game.last_page;
            break;
        }
        if(checkInButton(mouseClick, 448, 480) == true && game.get_pos == true){
            game.page = PAGE_GAME;
            game.regism = 0;
            break;
        }
        if(checkInButton(mouseClick, 448, 400) == true && game.get_pos == true){
            game.page = PAGE_GAME;
            game.regism = 1;
            break;
        }
        if(checkInButton(mouseClick, 448, 320) == true && game.get_pos == true){
            game.page = PAGE_GAME;
            game.regism = 2;
            break;
        }
        break;
    case PAGE_SETTING:
        Mix_VolumeMusic(game.back_track_volume);
        Mix_VolumeChunk(screen.notify, game.mix_volume);
        Mix_VolumeChunk(screen.capture, game.mix_volume);
        Mix_VolumeChunk(screen.move_self, game.mix_volume);
        if(checkInButton(mouseClick, 896, 0) == true && game.get_pos == true){
            game.page = game.last_page;
            SDL_DestroyTexture(screen.board_game);
            screen.board_game = screen.loadTexture(game.board_color[game.board-8].first.c_str());
            SDL_DestroyTexture(screen.back_track_name);
            screen.back_track_name = screen.createText(game.background_song[game.demo_back_track-32].second.c_str(), screen.font, screen.color);
            break;
        }

        if(checkInJump(mouseClick, 576, 128) == true && game.get_pos == true){
            if(game.demo_board == BOARD_BLACK){
                game.demo_board += 12;
            }
            game.demo_board--;
            SDL_DestroyTexture(screen.board_game);
            screen.board_game = screen.loadTexture(game.board_color[game.demo_board-8].first.c_str());
            SDL_DestroyTexture(screen.board_name);
            screen.board_name = screen.createText(game.board_color[game.demo_board-8].second.c_str(), screen.font, screen.color);
            std::cout << game.board << " " << game.demo_board << std::endl;
        }
        if(checkInJump(mouseClick, 898, 128) == true && game.get_pos == true){
            if(game.demo_board == BOARD_WHITE){
                game.demo_board -= 12;
            }
            game.demo_board++;
            SDL_DestroyTexture(screen.board_game);
            screen.board_game = screen.loadTexture(game.board_color[game.demo_board-8].first.c_str());
            SDL_DestroyTexture(screen.board_name);
            screen.board_name = screen.createText(game.board_color[game.demo_board-8].second.c_str(), screen.font, screen.color);
            std::cout << game.board << " " << game.demo_board << std::endl;
        }
        if(checkInButton(mouseClick, 672, 96) && game.get_pos == true){
            game.unlock_board[game.demo_board-8] = 1;
        }
        if(game.unlock_board[game.demo_board-8] == 1){
            game.board = game.demo_board;
        }

        if(checkInJump(mouseClick, 576, 192) == true && game.get_pos == true){
            std::cout << game.pieces_p1 << " " << game.demo_pieces_p1 << std::endl;
            if(game.demo_pieces_p1 == PIECES_BLACK){
                game.demo_pieces_p1 +=12;
            }
            game.demo_pieces_p1--;
            SDL_DestroyTexture(screen.pieces_p1_name);
            screen.pieces_p1_name = screen.createText(game.pieces_name[game.demo_pieces_p1-20].c_str(), screen.font, screen.color);
        }
        if(checkInJump(mouseClick, 898, 192) == true && game.get_pos == true){
            std::cout << game.pieces_p1 << " " << game.demo_pieces_p1 << std::endl;
            if(game.demo_pieces_p1 == PIECES_PURPLE){
                game.demo_pieces_p1 -=12;
            }
            game.demo_pieces_p1++;
            SDL_DestroyTexture(screen.pieces_p1_name);
            screen.pieces_p1_name = screen.createText(game.pieces_name[game.demo_pieces_p1-20].c_str(), screen.font, screen.color);
        }
        if(checkInButton(mouseClick, 672, 160) && game.get_pos == true){
            game.unlock_pieces_p1[game.demo_pieces_p1-20] = 1;
        }
        if(game.unlock_pieces_p1[game.demo_pieces_p1-20] == 1){
            game.pieces_p1 = game.demo_pieces_p1;
        }

        if(checkInJump(mouseClick, 576, 256) == true && game.get_pos == true){
            if(game.demo_pieces_p2 == PIECES_BLACK){
                game.demo_pieces_p2 +=12;
            }
            game.demo_pieces_p2--;
            SDL_DestroyTexture(screen.pieces_p2_name);
            screen.pieces_p2_name = screen.createText(game.pieces_name[game.demo_pieces_p2-20].c_str(), screen.font, screen.color);
            std::cout << game.pieces_p2 << " " << game.demo_pieces_p2 << std::endl;
        }
        if(checkInJump(mouseClick, 898, 256) == true && game.get_pos == true){
            if(game.demo_pieces_p2 == PIECES_PURPLE){
                game.demo_pieces_p2 -=12;
            }
            game.demo_pieces_p2++;
            SDL_DestroyTexture(screen.pieces_p2_name);
            screen.pieces_p2_name = screen.createText(game.pieces_name[game.demo_pieces_p2-20].c_str(), screen.font, screen.color);
            std::cout << game.pieces_p2 << " " << game.demo_pieces_p2 << std::endl;
        }
        if(checkInButton(mouseClick, 672, 224) && game.get_pos == true){
            game.unlock_pieces_p2[game.demo_pieces_p2-20] = 1;
        }
        if(game.unlock_pieces_p2[game.demo_pieces_p2-20] == 1){
            game.pieces_p2 = game.demo_pieces_p2;
        }

        if(checkInJump(mouseClick, 576, 320) == true && game.get_pos == true){
            if(game.demo_back_track == TRACK_ATBE){
                game.demo_back_track += 17;
            }
            game.demo_back_track--;
            SDL_DestroyTexture(screen.back_track_name);
            screen.back_track_name = screen.createText(game.background_song[game.demo_back_track-32].second.c_str(), screen.font, screen.color);
            Mix_FreeMusic(screen.sound_track);
            screen.sound_track = screen.loadMusic(game.background_song[game.demo_back_track-32].first.c_str());
            std::cout << game.back_track << " " << game.demo_back_track << std::endl;
        }
        if(checkInJump(mouseClick, 898, 320) == true && game.get_pos == true){
            if(game.demo_back_track == TRACK_TNOAA){
                game.demo_back_track -= 17;
            }
            game.demo_back_track++;
            SDL_DestroyTexture(screen.back_track_name);
            screen.back_track_name = screen.createText(game.background_song[game.demo_back_track-32].second.c_str(), screen.font, screen.color);
            Mix_FreeMusic(screen.sound_track);
            screen.sound_track = screen.loadMusic(game.background_song[game.demo_back_track-32].first.c_str());
            std::cout << game.back_track << " " << game.demo_back_track << std::endl;
        }
        if(checkInButton(mouseClick, 672, 288) && game.get_pos == true){
            game.unlock_back_track[game.demo_back_track-32] = 1;
            screen.playMusic(screen.sound_track, -1);
        }
        if(game.unlock_back_track[game.demo_back_track-32] == 1){
            game.back_track = game.demo_back_track;
        }

        if(mouseClick.x >= 640 && mouseClick.y >= 384 && mouseClick.x <= 896 && mouseClick.y <= 404 && game.get_pos == true){
            game.back_track_volume = (mouseClick.x-634)/4*2;
        }
        if(mouseClick.x >= 640 && mouseClick.y >= 448 && mouseClick.x <= 896 && mouseClick.y <= 468 && game.get_pos == true){
            game.mix_volume = (mouseClick.x-634)/4*2;
        }
        break;
    case PAGE_GAME:
        game.last_page = game.page;

        if(mouseClick.x >= 572 && mouseClick.y >= 22 && mouseClick.x <= 590 && mouseClick.y <= 40 && game.get_pos == true){
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

void render(Game &game, Screen &screen, Pos &mouse){
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
            screen.renderTexture(screen.board_name, 704, 112);
            int n = ((game.unlock_board[game.demo_board-8] == 1)? 0: 32);
            Rect rect_in(0, n, 256, 32);
            Rect rect_out(608, 96, 288, 64);
            screen.renderTexture(screen.unlock, rect_in, rect_out);
        }
        for(int i=0; i<1; i++){
            screen.renderTexture(screen.pieces_p1_name, 704, 176);
            int n = ((game.unlock_pieces_p1[game.demo_pieces_p1-20] == 1)? 0: 32);
            Rect rect_in(0, n, 256, 32);
            Rect rect_out(608, 160, 288, 64);
            screen.renderTexture(screen.unlock, rect_in, rect_out);
        }
        for(int i=0; i<1; i++){
            screen.renderTexture(screen.pieces_p2_name, 704, 240);
            int n = ((game.unlock_pieces_p2[game.demo_pieces_p2-20] == 1)? 0: 32);
            Rect rect_in(0, n, 256, 32);
            Rect rect_out(608, 224, 288, 64);
            screen.renderTexture(screen.unlock, rect_in, rect_out);
        }
        for(int i=0; i<1; i++){
            screen.renderTexture(screen.back_track_name, 608, 304);
            int n = ((game.unlock_back_track[game.demo_back_track-32] == 1)? 0: 32);
            Rect rect_in(0, n, 256, 32);
            Rect rect_out(608, 288, 288, 64);
            screen.renderTexture(screen.unlock, rect_in, rect_out);
        }

        for(int i=0; i<2; i++){
            Rect rect_in(40, 0, 256, 32);
            Rect rect_out(640, 384+ 64*i, 256, 32);
            screen.renderTexture(screen.volume_chart, rect_in, rect_out);
        }
        for(int i=0; i<1; i++){
            Rect rect_in(0, 0, 32, 32);
            Rect rect_out(629+game.back_track_volume*2, 384, 32, 32);
            screen.renderTexture(screen.volume_chart, rect_in, rect_out);
        }
        for(int i=0; i<1; i++){
            Rect rect_in(0, 0, 32, 32);
            Rect rect_out(629+game.mix_volume*2, 448, 32, 32);
            screen.renderTexture(screen.volume_chart, rect_in, rect_out);
        }
        for(int i=0; i<1; i++){
            Rect rect_in(0, 0, 36, 30);
            if(game.back_track_volume> 96){
                rect_in.x += 36;
            } else {
                if(game.back_track_volume >32 && game.back_track_volume <= 96){
                    rect_in.x += 36;
                    rect_in.y += 30;
                } else {
                    if(game.back_track_volume >0 && game.back_track_volume <= 32){
                        rect_in.y += 30;
                    }
                }
            }
            Rect rect_out(593, 384, 36, 30);
            screen.renderTexture(screen.volume_icon, rect_in, rect_out);
        }
        for(int i=0; i<1; i++){
            Rect rect_in(0, 0, 36, 30);
            if(game.mix_volume > 96){
                rect_in.x += 36;
            } else {
                if(game.mix_volume >32 && game.mix_volume <= 96){
                    rect_in.x += 36;
                    rect_in.y += 30;
                } else {
                    if(game.mix_volume >0 && game.mix_volume <= 32){
                        rect_in.y += 30;
                    }
                }
            }
            Rect rect_out(593, 448, 36, 30);
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
