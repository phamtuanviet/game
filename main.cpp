#include <SDL.h>
#include<SDL_image.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Không thể khởi tạo SDL: " << SDL_GetError() << std::endl;
        return 1;
    }


    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Không thể tạo cửa sổ: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "Không thể tạo renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    bool running = true;
    SDL_Event event;
    SDL_Texture *tex=IMG_LoadTexture(renderer,"cute.jpg");
    SDL_Rect rect;
    int ngu=0;
    rect.h=30;rect.w=30;
    rect.x=ngu;
    rect.y=0;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }


        // Xử lý game ở đây

        // Xóa màn hình



            rect.x+=5;
            rect.y+=5;
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer,tex,NULL,&rect);
            SDL_RenderPresent(renderer);
            if (rect.x>=640){rect.x=-5;};
            if (rect.y>=480){rect.y=-5;};


    }

    // Dọn dẹp
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
