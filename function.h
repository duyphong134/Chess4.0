# ifndef _FUNCITON__H_
# define _FUNCITON__H_

# include "game.h"
# include "pieces.h"
# include "screen.h"

bool checkEndGame(Game &game){
    bool black = false;
    bool white = false;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(game.pos_v2[i][j] == 6){
                white = true;
            }
            if(game.pos_v2[i][j] == -6){
                black = true;
            }
            if(black == true && white == true){
                return false;
            }
        }
    }
    return true;
}

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

void handleEvent(Game &game, Pos &mouse, Pos &mouseClick){
    SDL_Event e;
    SDL_PollEvent(&e);
    SDL_GetMouseState(&mouse.x, &mouse.y);
    game.get_pos = false;
    switch(e.type){
    case SDL_QUIT:
        game.running = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        SDL_GetMouseState(&mouseClick.x, &mouseClick.y);
        std::cout <<mouseClick.x << " " << mouseClick.y <<std::endl;
        game.get_pos = true;
        break;
    }
}

void update(Game &game, Screen &screen, Pos &mouseClick, Pieces &piece){
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
            game.regism = REGISM_RIDDLE;
            break;
        }
        if(checkInButton(mouseClick, 448, 400) == true && game.get_pos == true){
            game.page = PAGE_GAME;
            game.regism = REGISM_2P;
            break;
        }
        if(checkInButton(mouseClick, 448, 320) == true && game.get_pos == true){
            game.page = PAGE_GAME;
            game.regism = REGISM_1P;
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
        }
        if(checkInButton(mouseClick, 672, 96) && game.get_pos == true){
            game.unlock_board[game.demo_board-8] = 1;
        }
        if(game.unlock_board[game.demo_board-8] == 1){
            game.board = game.demo_board;
        }

        if(checkInJump(mouseClick, 576, 192) == true && game.get_pos == true){
            if(game.demo_pieces_p1 == PIECES_BLACK){
                game.demo_pieces_p1 +=12;
            }
            game.demo_pieces_p1--;
            SDL_DestroyTexture(screen.pieces_p1_name);
            screen.pieces_p1_name = screen.createText(game.pieces_name[game.demo_pieces_p1-20].c_str(), screen.font, screen.color);
        }
        if(checkInJump(mouseClick, 898, 192) == true && game.get_pos == true){
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
        }
        if(checkInJump(mouseClick, 898, 256) == true && game.get_pos == true){
            if(game.demo_pieces_p2 == PIECES_PURPLE){
                game.demo_pieces_p2 -=12;
            }
            game.demo_pieces_p2++;
            SDL_DestroyTexture(screen.pieces_p2_name);
            screen.pieces_p2_name = screen.createText(game.pieces_name[game.demo_pieces_p2-20].c_str(), screen.font, screen.color);
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
        if(mouseClick.x >= 715 && mouseClick.y >= 495 && mouseClick.x <= 795 && mouseClick.y <= 545 && game.get_pos == true){
            if(game.move_count >0){
                game.move_count--;
                game.tranToPosV2();
            }
        }
        if(mouseClick.x >= 808 && mouseClick.y >= 495 && mouseClick.x <= 888 && mouseClick.y <= 545 && game.get_pos == true){
            if(game.move_count <game.cur_move_count){
                game.move_count++;
                game.tranToPosV2();
            }
        }
        if(mouseClick.x >= 900 && mouseClick.y >= 495 && mouseClick.x <= 980 && mouseClick.y <= 545 && game.get_pos == true){

        }
        if(mouseClick.x >= 64 && mouseClick.y >= 64 && mouseClick.x <= 576 && mouseClick.y <= 576 && game.get_pos == true){
            switch(game.regism){
            case REGISM_1P:
                if(game.chose_piece == false){
                    piece.Pos1GetCoord(mouseClick);
                    if(game.pos_v2[piece.pos1.x][piece.pos1.y]>0){
                        game.chose_piece = true;
                        piece.init(game);
                    }
                } else{
                    if(game.chose_piece == true){
                        piece.Pos2GetCoord(mouseClick);
                        if(piece.enable[piece.pos2.x][piece.pos2.y] == true){
                            if(piece.get_pawn_special == true){
                                game.pos_v2[piece.pos2.x][piece.pos2.y] = game.pos_v2[piece.pos1.x][piece.pos1.y];
                                game.pos_v2[piece.pos1.x][piece.pos1.y] = 0;
                                game.pos_v2[piece.pos2.x-game.pos_v2[piece.pos2.x][piece.pos2.y]][piece.pos2.y] =0;
                            }else {
                                if(piece.castle == true){
                                    game.pos_v2[piece.pos2.x][piece.pos2.y] = game.pos_v2[piece.pos1.x][piece.pos1.y];
                                    game.pos_v2[piece.pos1.x][piece.pos1.y] = 0;
                                    if(piece.pos2.y- piece.pos1.y ==2 && piece.pos2.x == piece.pos2.y){
                                        game.pos_v2[piece.pos2.x][piece.pos2.y-1] = game.pos_v2[piece.pos2.x][piece.pos2.y+1];
                                        game.pos_v2[piece.pos2.x][piece.pos2.y+1] = 0;
                                    } else {
                                        game.pos_v2[piece.pos2.x][piece.pos2.y+1] = game.pos_v2[piece.pos2.x][piece.pos2.y-2];
                                        game.pos_v2[piece.pos2.x][piece.pos2.y-2] = 0;
                                    }
                                } else {
                                    game.pos_v2[piece.pos2.x][piece.pos2.y] = game.pos_v2[piece.pos1.x][piece.pos1.y];
                                    game.pos_v2[piece.pos1.x][piece.pos1.y] = 0;
                                }
                            }
                            if(piece.pos2.x == (4-(1-7*game.pos_v2[piece.pos2.x][piece.pos2.y])/2) && (game.pos_v2[piece.pos2.x][piece.pos2.y] == 1 || game.pos_v2[piece.pos2.x][piece.pos2.y] == -1)){
                                game.pos_v2[piece.pos2.x][piece.pos2.y] *=5;
                            }
                            game.tranToPosV1();
                            game.move_note[game.move_count] = {tranToNoteCrood(piece.pos1.x, piece.pos1.y), tranToNoteCrood(piece.pos2.x, piece.pos2.y)};
                            game.is_move = true;
                        }
                        game.chose_piece = false;
                    }
                }
                break;
            case REGISM_2P:
                std::cout << game.move_count << " " << game.cur_move_count << std::endl;
                std::cout << game.chose_piece << " " << piece.castle << " " << piece.get_pawn_special << std::endl;
                if(game.chose_piece == false){
                    int n = ((game.move_count %2) ==0)? 1: -1;
                    piece.Pos1GetCoord(mouseClick);
                    if(game.pos_v2[piece.pos1.x][piece.pos1.y]*n>0){
                        game.chose_piece = true;
                        piece.init(game);
                    }
                } else{
                    if(game.chose_piece == true){
                        piece.Pos2GetCoord(mouseClick);
                        if(piece.enable[piece.pos2.x][piece.pos2.y] == true){
                            if(abs(game.pos_v2[piece.pos1.x][piece.pos1.y])==1 && abs(game.pos_v2[piece.pos2.x-game.pos_v2[piece.pos2.x][piece.pos2.y]][piece.pos2.y])==1){
                                piece.get_pawn_special = true;
                            }
                            if(abs(piece.pos2.y - piece.pos1.y)==2 && abs(game.pos_v2[piece.pos1.x][piece.pos1.y])==6){
                                piece.castle= true;
                            }
                            if(piece.get_pawn_special == true){
                                game.pos_v2[piece.pos2.x][piece.pos2.y] = game.pos_v2[piece.pos1.x][piece.pos1.y];
                                game.pos_v2[piece.pos1.x][piece.pos1.y] = 0;
                                game.pos_v2[piece.pos2.x-game.pos_v2[piece.pos2.x][piece.pos2.y]][piece.pos2.y] =0;
                            }else {
                                if(piece.castle == true){
                                    game.pos_v2[piece.pos2.x][piece.pos2.y] = game.pos_v2[piece.pos1.x][piece.pos1.y];
                                    game.pos_v2[piece.pos1.x][piece.pos1.y] = 0;
                                    if(piece.pos2.y- piece.pos1.y ==2 && piece.pos2.x == piece.pos2.y){
                                        game.pos_v2[piece.pos2.x][piece.pos2.y-1] = game.pos_v2[piece.pos2.x][piece.pos2.y+1];
                                        game.pos_v2[piece.pos2.x][piece.pos2.y+1] = 0;
                                    } else {
                                        game.pos_v2[piece.pos2.x][piece.pos2.y+1] = game.pos_v2[piece.pos2.x][piece.pos2.y-2];
                                        game.pos_v2[piece.pos2.x][piece.pos2.y-2] = 0;
                                    }
                                } else {
                                    game.pos_v2[piece.pos2.x][piece.pos2.y] = game.pos_v2[piece.pos1.x][piece.pos1.y];
                                    game.pos_v2[piece.pos1.x][piece.pos1.y] = 0;
                                }
                            }
                            if((piece.pos2.x == 0 || piece.pos2.x == 7)&& (game.pos_v2[piece.pos2.x][piece.pos2.y] == 1 || game.pos_v2[piece.pos2.x][piece.pos2.y] == -1)){
                                game.pos_v2[piece.pos2.x][piece.pos2.y] *=5;
                            }
                            game.tranToPosV1();
                            game.move_note[game.move_count] = {tranToNoteCrood(piece.pos1.x, piece.pos1.y), tranToNoteCrood(piece.pos2.x, piece.pos2.y)};
                            game.is_move = true;
                        }
                        game.chose_piece = false;
                    }
                }
                break;
            case REGISM_RIDDLE:
                if(game.chose_piece == false){
                    piece.Pos1GetCoord(mouseClick);
                    if(game.pos_v2[piece.pos1.x][piece.pos1.y]>0){
                        game.chose_piece = true;
                        piece.init(game);
                    }
                } else{
                    if(game.chose_piece == true){
                        piece.Pos2GetCoord(mouseClick);
                        if(piece.enable[piece.pos2.x][piece.pos2.y] == true){
                            if(piece.get_pawn_special == true){
                                game.pos_v2[piece.pos2.x][piece.pos2.y] = game.pos_v2[piece.pos1.x][piece.pos1.y];
                                game.pos_v2[piece.pos1.x][piece.pos1.y] = 0;
                                game.pos_v2[piece.pos2.x-game.pos_v2[piece.pos2.x][piece.pos2.y]][piece.pos2.y] =0;
                            }else {
                                if(piece.castle == true){
                                    game.pos_v2[piece.pos2.x][piece.pos2.y] = game.pos_v2[piece.pos1.x][piece.pos1.y];
                                    game.pos_v2[piece.pos1.x][piece.pos1.y] = 0;
                                    if(piece.pos2.y- piece.pos1.y ==2 && piece.pos2.x == piece.pos2.y){
                                        game.pos_v2[piece.pos2.x][piece.pos2.y-1] = game.pos_v2[piece.pos2.x][piece.pos2.y+1];
                                        game.pos_v2[piece.pos2.x][piece.pos2.y+1] = 0;
                                    } else {
                                        game.pos_v2[piece.pos2.x][piece.pos2.y+1] = game.pos_v2[piece.pos2.x][piece.pos2.y-2];
                                        game.pos_v2[piece.pos2.x][piece.pos2.y-2] = 0;
                                    }
                                } else {
                                    game.pos_v2[piece.pos2.x][piece.pos2.y] = game.pos_v2[piece.pos1.x][piece.pos1.y];
                                    game.pos_v2[piece.pos1.x][piece.pos1.y] = 0;
                                }
                            }
                            if(piece.pos2.x == (4-(1-7*game.pos_v2[piece.pos2.x][piece.pos2.y])/2) && (game.pos_v2[piece.pos2.x][piece.pos2.y] == 1 || game.pos_v2[piece.pos2.x][piece.pos2.y] == -1)){
                                game.pos_v2[piece.pos2.x][piece.pos2.y] *=5;
                            }
                            game.tranToPosV1();
                            game.move_note[game.move_count] = {tranToNoteCrood(piece.pos1.x, piece.pos1.y), tranToNoteCrood(piece.pos2.x, piece.pos2.y)};
                            game.is_move = true;
                        }
                        game.chose_piece = false;
                    }
                }
                break;
            }
        }
        if(checkEndGame(game) == true){
            game.running = false;
        }
        break;
    }
}

void render(Game &game, Screen &screen, Pos &mouse, Pieces &piece){
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
            Rect rect_in(64, 64, 384, 384);
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

        for(int i=0; i< 6; i++){
            for(int j=0; j<6; j++){
                if(game.pos_v2[i][j] != 0){
                    int n = (game.pos_v2[i][j] >0)? (game.demo_pieces_p1-20): (game.demo_pieces_p2-20);
                    Rect rect_in((abs(game.pos_v2[i][j])-1)*128, 128*n, 128, 128);
                    Rect rect_out((j+2)*64, (i+2)*64, 64, 64);
                    screen.renderTexture(screen.pieces, rect_in, rect_out);
                }
            }
        }
        break;
    case PAGE_GAME:
        screen.renderTexture(screen.board_game, 0, 0);
        for(int i=0; i< 8; i++){
            for(int j=0; j<8; j++){
                if(i == piece.pos1.x && j == piece.pos1.y && game.is_move == true){
                    piece.evaluateDistant(game.is_move);
                    int n = (game.pos_v2[piece.pos1.x][piece.pos1.y] >0)? (game.pieces_p1-20): (game.pieces_p2-20);
                    Rect rect_in((abs(game.pos_v2[piece.pos1.x][piece.pos1.y])-1)*128, 128*n, 128, 128);
                    Rect rect_out((piece.pos1.x+1)*64+piece.dis_x, (piece.pos1.y+1)*64+piece.dis_y, 64, 64);
                    screen.renderTexture(screen.pieces, rect_in, rect_out);
                } else {
                    if(game.pos_v2[i][j] != 0){
                        int n = (game.pos_v2[i][j] >0)? (game.pieces_p1-20): (game.pieces_p2-20);
                        Rect rect_in((abs(game.pos_v2[i][j])-1)*128, 128*n, 128, 128);
                        Rect rect_out((j+1)*64, (i+1)*64, 64, 64);
                        screen.renderTexture(screen.pieces, rect_in, rect_out);
                    }
                    if(game.chose_piece == true){
                        if(piece.enable[i][j] == true ){
                            if(game.pos_v2[i][j] ==0){
                                Rect rect_in(64, 0, 64, 64);
                                Rect rect_out((j+1)*64, (i+1)*64, 64, 64);
                                screen.renderTexture(screen.move_light, rect_in, rect_out);
                            } else {
                                Rect rect_in(0, 0, 64, 64);
                                Rect rect_out((j+1)*64, (i+1)*64, 64, 64);
                                screen.renderTexture(screen.move_light, rect_in, rect_out);
                            }
                        }
                    }
                }
            }
        }
        break;
    }
    SDL_RenderPresent(screen.renderer);
}


# endif // _FUNCITON__H_
