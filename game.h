# ifndef _GAME__H_
# define _GAME__H_

# include "index.h"

void entryUnlock(std::vector<int> &a, int line, int n){
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
        a[i] = (int)(x[i])- 48;
        std::cout << x[i] << " ";
    }
    std::cout << x << std::endl;
}

void exportUnlock(std::vector<int> a, int line, int n){
    std::string x;
    for(int i=0; i<n; i++){
        x += (char)(a[i]+48);
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

void entryRiddle(std::vector<char> &a, int line, int n){
    std::string x;
    std::ifstream fileInput("res//txt//Riddle.txt");
    if(fileInput.is_open()){
        for(int i=0; i<line; i++){
            fileInput >> x;
        }
        fileInput.close();
    } else {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Can't open file unlock");
    }
    for(int i=0; i<n; i++){
        a[i] = (int)(x[i])- 48;
        std::cout << x[i] << " ";
    }
    std::cout << x << std::endl;
}

void exportRiddle(std::vector<char> a, int line, int n){
    std::string x;
    for(int i=0; i<n; i++){
        x += (char)(a[i]+48);
    }
    std::ofstream fileOutput("res//txt//Riddle.txt");
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
    bool get_pos;
    int page;
    int last_page;
    int regism;
    std::vector<std::pair<std::string, std::string>> board_color{12};
    std::vector<int> unlock_board{12};
    int board;
    int demo_board;
    std::vector<std::string> pieces_name{12};
    int pieces_p1;
    int demo_pieces_p1;
    std::vector<int> unlock_pieces_p1{12};
    int pieces_p2;
    int demo_pieces_p2;
    std::vector<int> unlock_pieces_p2{12};
    std::vector<std::pair<std::string, std::string>> background_song{17};
    int back_track;
    int demo_back_track;
    std::vector<int> unlock_back_track{17};
    int back_track_volume;
    int mix_volume;
    std::vector<std::vector<int>> pos_v1{200, std::vector<int>{64}};
    int pos_v2[8][8];
    int move_count;
    void init(){
        running = true;
        get_pos = false;
        page = PAGE_MENU;
        last_page = PAGE_MENU;
        regism = REGISM_1P;
        board_color = {{"res//image//Board_Black.png", "BLACK"},
                       {"res//image//Board_Brown.png", "BROWN"},
                       {"res//image//Board_Denim.png", "DENIM"},
                       {"res//image//Board_Gold.png", "GOLD"},
                       {"res//image//Board_Green.png", "GREEN"},
                       {"res//image//Board_Grey.png", "GREY"},
                       {"res//image//Board_Irish.png", "IRISH"},
                       {"res//image//Board_Neon.png", "NEON"},
                       {"res//image//Board_Pink.png", "PINK"},
                       {"res//image//Board_Purple.png", "PURPLE"},
                       {"res//image//Board_Sky.png", "SKY"},
                       {"res//image//Board_White.png", "WHITE"}};
        board = BOARD_BROWN;
        demo_board = BOARD_BROWN;
//        entryUnlock(unlock_board, 1, 12);

        pieces_name = {"BLACK", "WHITE", "ASH", "GREY", "PINK", "RED", "ORANGE", "YELLOW", "GREEN", "BLUE", "NEON","PURPLE"};
        pieces_p1 = PIECES_WHITE;
        demo_pieces_p1 = PIECES_WHITE;
//        entryUnlock(unlock_pieces_p1, 2, 12);
        pieces_p2 = PIECES_BLACK;
        demo_pieces_p2 = PIECES_BLACK;
//        entryUnlock(unlock_pieces_p2, 3, 12);

        background_song = {{"res//sound//#ATBE.mp3", "Am tham ben em"},
                           {"res//sound//#BDTNR.mp3", "Buong doi tay nhau ra"},
                           {"res//sound//#CND.mp3", "Chay ngay di"},
                           {"res//sound//#CTCHT.mp3", "Chung ta cua hien tai"},
                           {"res//sound//#CTCTL.mp3", "Chung ta cua tuong lai"},
                           {"res//sound//#CTKTVN.mp3", "Chung ta khong thuoc ve nhau"},
                           {"res//sound//#ECNHQ.mp3", "Em cua ngay hom qua"},
                           {"res//sound//#HTCA.mp3", "Hay trao cho anh"},
                           {"res//sound//#KPDVD.mp3", "Khong phai dang vua dau"},
                           {"res//sound//#LNLYE.mp3", "Lam nguoi luon yeu em"},
                           {"res//sound//#LT.mp3", "Lac troi"},
                           {"res//sound//#MMW.mp3", "Making My Way"},
                           {"res//sound//#MRMSC.mp3", "Muon roi ma sao con"},
                           {"res//sound//#MS_No14.mp3", "Moonlight Sonata No14"},
                           {"res//sound//#NAXD.mp3", "Nang am xa dan"},
                           {"res//sound//#NNCA.mp3", "Noi nay co anh"},
                           {"res//sound//#TNOAA.mp3", "There no one at all"}};
        back_track = TRACK_ATBE;
        demo_back_track = TRACK_ATBE;
        entryUnlock(unlock_board, 1, 12);
        entryUnlock(unlock_pieces_p1, 2, 12);
        entryUnlock(unlock_pieces_p2, 3, 12);
        entryUnlock(unlock_back_track, 4, 17);
        back_track_volume = 128;
        mix_volume = 128;

        move_count =0;
    }

    void tranToPosV2(){
        int pos_count =0;
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                pos_v2[i][j] = pos_v1[move_count][pos_count];
                pos_count ++;
            }
        }
    }

    void tranToPosV1(){
        move_count++;
        int pos_count =0;
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                pos_v1[move_count][pos_count] = pos_v2[i][j];
                pos_count++;
            }
        }
    }

    void quit(){
        board_color.clear();
        unlock_board.clear();
        pieces_name.clear();
        unlock_pieces_p1.clear();
        unlock_pieces_p2.clear();
        background_song.clear();
        unlock_back_track.clear();
        for(int i=0; i <= move_count; i++){
            pos_v1[i].clear();
        }
        pos_v1.clear();
    }
};

# endif // _GAME__H_
