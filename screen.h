# ifndef _SCREEN__H_
# define _SCREEN__H_

# include "index.h"

struct Rect{
    int x, y, w, h;

    Rect(int x_, int y_, int w_, int h_){
        x = x_;
        y = y_;
        w = w_;
        h = h_;
    }
};

struct Screen{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *background, *setting, *button, *volume_chart, *board_game, *pieces, *move_light, *unlock, *volume_icon, *board_name, *pieces_p1_name, *pieces_p2_name, *back_track_name, *info;
    Mix_Chunk *notify, *move_self, *capture;
    Mix_Music *sound_track;
    TTF_Font *font;
    SDL_Color color = {255, 0, 0, 255};

    void init(){
        if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "SDL_Init" , SDL_GetError());
        }

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == nullptr){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create_Window" , SDL_GetError());
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(renderer == nullptr){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create_Renderer" , SDL_GetError());
        }

        if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "IMG_Init" , SDL_GetError());
        }

        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "MIX_Init" , SDL_GetError());
        }

        if( TTF_Init() == -1) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "TTF_Init" , SDL_GetError());
        }

        background = loadTexture("res//image//Background.png");
        setting = loadTexture("res//image//Setting.png");
        volume_chart = loadTexture("res//image//Volume_Chart.png");
        button = loadTexture("res//image//Button.png");
        board_game = loadTexture("res//image//Board_Brown.png");
        pieces = loadTexture("res//image//Pieces.png");
        move_light = loadTexture("res//image//Move_Light.png");
        unlock = loadTexture("res//image//Unlock.png");
        volume_icon = loadTexture("res//image//Volume_Icon.png");
        info = loadTexture("res//image//Info.png");

        notify = loadChunk("res//sound//notify.mp3");
        move_self = loadChunk("res//sound//move_self.mp3");
        capture = loadChunk("res//sound//capture.mp3");
        sound_track = loadMusic("res//sound//#ATBE.mp3");

        font = loadFont("res//font//Arial_Bold.ttf", 20);
        board_name = createText("BROWN", font, color);
        pieces_p1_name = createText("WHITE", font, color);
        pieces_p2_name = createText("BLACK", font, color);
        back_track_name = createText("Am tham ben em", font, color);
    }

    SDL_Texture *loadTexture(const char *filename){
        SDL_Surface *surface = IMG_Load(filename);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if(texture == NULL){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "loadTexture", SDL_GetError());
        }
        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y){
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void renderTexture(SDL_Texture *texture, Rect rect_in, Rect rect_out){
        SDL_Rect srcrect;
        srcrect.x = rect_in.x;
        srcrect.y = rect_in.y;
        srcrect.w = rect_in.w;
        srcrect.h = rect_in.h;

        SDL_Rect dstrect;
        dstrect.x = rect_out.x;
        dstrect.y = rect_out.y;
        dstrect.w = rect_out.w;
        dstrect.h = rect_out.h;

        SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
    }

    Mix_Chunk* loadChunk(const char* path) {
        Mix_Chunk* gChunk = Mix_LoadWAV(path);
        if(gChunk == nullptr){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "loadChunk", SDL_GetError());
        }
        return gChunk;
    }

    Mix_Music *loadMusic(const char* path){
        Mix_Music *gMusic = Mix_LoadMUS(path);
        if(gMusic == NULL){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "loadMusic", SDL_GetError());
        }
        return gMusic;
    }

    void playChunk(Mix_Chunk* gChunk, int loop) {
        if(gChunk != nullptr) {
            Mix_PlayChannel( -1, gChunk, loop );
        }
    }

    void playMusic(Mix_Music *gMusic, int loop){
        if (gMusic == nullptr){
            return;
        }
        Mix_PlayMusic(sound_track, -1);
    }

    TTF_Font* loadFont(const char* path, int size_font) {
        TTF_Font* gFont = TTF_OpenFont( path, size_font );
        if (gFont == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "loadFont", TTF_GetError());
        }
    }

    SDL_Texture* createText(const char* text, TTF_Font* font, SDL_Color textColor){
        SDL_Surface* textSurface = TTF_RenderText_Solid( font, text, textColor );
        if( textSurface == nullptr ){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "loadText", TTF_GetError());
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "loadTextTexture", TTF_GetError());
        }
        SDL_FreeSurface( textSurface );
        return texture;
    }

    void quit(){
        SDL_DestroyTexture(board_name);
        board_name = nullptr;
        SDL_DestroyTexture(pieces_p1_name);
        pieces_p1_name = nullptr;
        SDL_DestroyTexture(pieces_p2_name);
        pieces_p2_name = nullptr;
        SDL_DestroyTexture(back_track_name);
        back_track_name = nullptr;
        TTF_CloseFont(font);
        font = nullptr;
        TTF_Quit();

        Mix_FreeChunk(notify);
        notify = nullptr;
        Mix_FreeChunk(move_self);
        move_self = nullptr;
        Mix_FreeChunk(capture);
        capture = nullptr;
        Mix_FreeMusic(sound_track);
        sound_track = nullptr;
        Mix_Quit();

        SDL_DestroyTexture(background);
        background = nullptr;
        SDL_DestroyTexture(setting);
        setting = nullptr;
        SDL_DestroyTexture(volume_chart);
        volume_chart = nullptr;
        SDL_DestroyTexture(button);
        button = nullptr;
        SDL_DestroyTexture(board_game);
        board_game = nullptr;
        SDL_DestroyTexture(pieces);
        pieces = nullptr;
        SDL_DestroyTexture(move_light);
        move_light = nullptr;
        SDL_DestroyTexture(unlock);
        unlock = nullptr;
        SDL_DestroyTexture(volume_icon);
        volume_icon = nullptr;
        SDL_DestroyTexture(info);
        info = nullptr;
        IMG_Quit();

        SDL_DestroyWindow(window);
        window = nullptr;

        SDL_DestroyRenderer(renderer);
        renderer = nullptr;

        SDL_Quit();
    }
};

# endif // _SCREEN__H_
