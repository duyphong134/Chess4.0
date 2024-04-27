# ifndef _GAME__H_
# define _GAME__H_

# include "index.h"

void entryUnlock(int a[], int line, int size_a){
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
    for(int i=0; i<size_a; i++){
        a[i] = (int)(x[i])- 48;
    }
}

void exportUnlock(int a[], int line, int size_a){
    std::string x;
    for(int i=0; i<size_a; i++){
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

void entryRiddle(char a[], char number, int size_a){
    std::string x;
    std::ifstream fileInput("res//txt//Riddle.txt");
    if(fileInput.is_open()){
        while(x[0] != number){
            fileInput >> x;
        }
        fileInput >> x;
        fileInput.close();
    } else {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Can't open file unlock");
    }
    for(int i=0; i<size_a; i++){
        a[i] = x[i];
    }
}

struct Game{
    bool running;
    bool get_pos;
    int page;
    int last_page;
    int regism;
    std::vector<std::pair<std::string, std::string>> board_color{  {"res//image//Board_Black.png", "BLACK"},
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
    int unlock_board[12];
    int board;
    int demo_board;
    std::vector<std::string> pieces_name{"BLACK", "WHITE", "ASH", "GREY", "PINK", "RED", "ORANGE", "YELLOW", "GREEN", "BLUE", "NEON","PURPLE"};
    int pieces_p1;
    int demo_pieces_p1;
    int unlock_pieces_p1[12];
    int pieces_p2;
    int demo_pieces_p2;
    int unlock_pieces_p2[12];
    std::vector<std::pair<std::string, std::string>> background_song{  {"res//sound//#ATBE.mp3", "Am tham ben em"},
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
    int back_track;
    int demo_back_track;
    int unlock_back_track[17];
    int back_track_volume;
    int mix_volume;
    char pos_v1[200][64];
    int pos_v2[8][8];
    int move_count;
    bool pos_1_choosed;
    bool pos_2_choosed;

    void init(){
        running = true;
        get_pos = false;
        page = PAGE_MENU;
        last_page = PAGE_MENU;
        regism = REGISM_1P;
        board = BOARD_BROWN;
        demo_board = BOARD_BROWN;
        entryUnlock(unlock_board, 1, 12);
        pieces_p1 = PIECES_WHITE;
        demo_pieces_p1 = PIECES_WHITE;
        entryUnlock(unlock_pieces_p1, 2, 12);
        pieces_p2 = PIECES_BLACK;
        demo_pieces_p2 = PIECES_BLACK;
        entryUnlock(unlock_pieces_p2, 3, 12);
        back_track = TRACK_ATBE;
        demo_back_track = TRACK_ATBE;
        entryUnlock(unlock_back_track, 4, 17);
        back_track_volume = 128;
        mix_volume = 128;

        entryRiddle(pos_v1[0], '0', 64);
        tranToPosV2();
        move_count =0;
        pos_1_choosed = false;
        pos_2_choosed = false;
    }

    void tranToPosV2(){
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                switch(pos_v1[move_count][i*8+j]){
                case 'p':
                    pos_v2[i][j] = -1;
                    break;
                case 'P':
                    pos_v2[i][j] = 1;
                    break;
                case 'n':
                    pos_v2[i][j] = -2;
                    break;
                case 'N':
                    pos_v2[i][j] = 2;
                    break;
                case 'b':
                    pos_v2[i][j] = -3;
                    break;
                case 'B':
                    pos_v2[i][j] = 3;
                    break;
                case 'r':
                    pos_v2[i][j] = -4;
                    break;
                case 'R':
                    pos_v2[i][j] = 4;
                    break;
                case 'q':
                    pos_v2[i][j] = -5;
                    break;
                case 'Q':
                    pos_v2[i][j] = 5;
                    break;
                case 'k':
                    pos_v2[i][j] = -6;
                    break;
                case 'K':
                    pos_v2[i][j] = 6;
                    break;
                default:
                    pos_v2[i][j] = 0;
                    break;
                }
            }
        }
    }

    void tranToPosV1(){
        move_count++;
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                switch(pos_v2[i][j]){
                case -1:
                    pos_v1[move_count][i*8+j] = 'p';
                    break;
                case 1:
                    pos_v1[move_count][i*8+j] = 'P';
                    break;
                case -2:
                    pos_v1[move_count][i*8+j] = 'n';
                    break;
                case 2:
                    pos_v1[move_count][i*8+j] = 'N';
                    break;
                case -3:
                    pos_v1[move_count][i*8+j] = 'b';
                    break;
                case 3:
                    pos_v1[move_count][i*8+j] = 'B';
                    break;
                case -4:
                    pos_v1[move_count][i*8+j] = 'r';
                    break;
                case 4:
                    pos_v1[move_count][i*8+j] = 'R';
                    break;
                case -5:
                    pos_v1[move_count][i*8+j] = 'q';
                    break;
                case 5:
                    pos_v1[move_count][i*8+j] = 'Q';
                    break;
                case -6:
                    pos_v1[move_count][i*8+j] = 'k';
                    break;
                case 6:
                    pos_v1[move_count][i*8+j] = 'K';
                    break;
                default:
                    pos_v2[i][j] = 0;
                    break;
                }
            }
        }
    }

    void quit(){
        board_color.clear();
        pieces_name.clear();
        background_song.clear();
    }
};

# endif // _GAME__H_
