# ifndef _GAME__H_
# define _GAME__H_

# include "index.h"

void entryUnlock(bool *a, int line, int n){
    std::string x;
    std::ifstream fileInput("res//txt//Unlock.txt");
    if(fileInput.is_open()){
        for(int i=0; i<line; i++){
            fileInput >> x;
        }
        fileInput.close();
    } else {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Can't open file unlock");
    }
    for(int i=0; i<n; i++){
        a[i] = (int)(x[i]);
    }
}

void exportUnlock(bool *a, int line, int n){
    std::string x;
    for(int i=0; i<n; i++){
        x += (char)(a[i]);
    }
    std::ofstream fileOutput("res//txt//Unlock.txt");
    if(fileOutput.is_open()){
        for(int i=0; i<line; i++){
            fileOutput << x;
        }
        fileOutput.close();
    } else {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Can't open file unlock");
    }
}

struct Game{
    bool running;
    int page;
    int last_page;
    int regism;
    bool get_pos;
    std::vector<std::pair<std::string, std::string>> board_color{12};
    bool unlock_board[12];
    int board;
    int demo_board;
    std::vector<std::string> pieces_name{12};
    bool unlock_pieces_p1[12];
    int pieces_p1;
    int demo_pieces_p1;
    bool unlock_pieces_p2[12];
    int pieces_p2;
    int demo_pieces_p2;
    std::vector<std::pair<std::string, std::string>> background_song{17};
    bool unlock_back_track[17];
    int back_track;
    int demo_back_track;
    std::vector<std::vector<int>> pos_v1{200, std::vector<int>{64}};
    int pos_v2[8][8];
    int move_count;
    void init(){
        running = true;
        page = PAGE_MENU;
        last_page = PAGE_MENU;
        regism = REGISM_1P;
        get_pos = false;
        board_color = {{"res//img//Board_Black.img", "BLACK"},
                       {"res//img//Board_Brown.img", "BROWN"},
                       {"res//img//Board_Denim.img", "DENIM"},
                       {"res//img//Board_Gold.img", "GOLD"},
                       {"res//img//Board_Green.img", "GREEN"},
                       {"res//img//Board_Grey.img", "GREY"},
                       {"res//img//Board_Irish.img", "IRISH"},
                       {"res//img//Board_Neon.img", "NEON"},
                       {"res//img//Board_Pink.img", "PINK"},
                       {"res//img//Board_Purple.img", "PURPLE"},
                       {"res//img//Board_Sky.img", "SKY"},
                       {"res//img//Board_White.img", "WHITE"}};
        entryUnlock(unlock_board, 1, 12);
        board = BOARD_BROWN;
        demo_board = BOARD_BROWN;

        pieces_name = {"BLACK", "WHITE", "ASH", "GREY", "PINK", "RED", "ORANGE", "YELLOW", "GREEN", "BLUE", "NEON","PURPLE"};
        entryUnlock(unlock_pieces_p1, 2, 12);
        pieces_p1 = PIECES_WHITE;
        demo_pieces_p1 = PIECES_WHITE;
        entryUnlock(unlock_pieces_p2, 3, 12);
        pieces_p2 = PIECES_BLACK;
        demo_pieces_p2 = PIECES_BLACK;

        background_song = {{"res//sound//#ATBE.mp3", "Âm thầm bên em"},
                           {"res//sound//#BDTNR.mp3", "Buông đôi tay nhau ra"},
                           {"res//sound//#CND.mp3", "Chạy ngay đi"},
                           {"res//sound//#CTCHT.mp3", "Chúng ta của hiện tại"},
                           {"res//sound//#CTCTL.mp3", "Chúng ta của tương lai"},
                           {"res//sound//#CTKTVN.mp3", "Chúng ta không thuộc về nhau"},
                           {"res//sound//#ECNHQ.mp3", "Em của ngày hôm qua"},
                           {"res//sound//#HTCA.mp3", "Hãy trao cho anh"},
                           {"res//sound//#KPDVD.mp3", "Không phải dạng vừa đâu"},
                           {"res//sound//#LNLYE.mp3", "Làm người luôn yêu em"},
                           {"res//sound//#LT.mp3", "Lạc trôi"},
                           {"res//sound//#MMW.mp3", "Making My Way"},
                           {"res//sound//#MRMSC.mp3", "Muộn rồi mà sao còn"},
                           {"res//sound//#MS_No14.mp3", "Moonlight Sonata No14"},
                           {"res//sound//#NAXD.mp3", "Nắng ấm xa dần"},
                           {"res//sound//#NNCA.mp3", "Nơi này có anh"},
                           {"res//sound//#TNOAA.mp3", "There no one at all"}};
        entryUnlock(unlock_back_track, 4, 17);
        back_track = TRACK_NONE;
        demo_back_track = TRACK_NONE;

    }

//    void tranToPosV2(){
//        int pos_count =0;
//        for(int i=0; i<8; i++){
//            for(int j=0; j<8; j++){
//                pos_v2[i][j] = pos_v1[move_count][pos_count];
//                pos_count ++;
//            }
//        }
//    }
//
//    void tranToPosV1(){
//        move_count++;
//        int pos_count =0;
//        for(int i=0; i<8; i++){
//            for(int j=0; j<8; j++){
//                pos_v1[move_count][pos_count] = pos_v2[i][j];
//                pos_count++;
//            }
//        }
//    }

    void quit(){
        for(int i=0; i <= move_count; i++){
            pos_v1[i].clear();
        }
        pos_v1.clear();
    }
};

# endif // _GAME__H_
