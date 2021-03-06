/*演示sdl窗口创建和渲染
 *clang -g -o first_sdl first_sdl.c `pkg-config --cflags --libs sdl2`
 *./first_sdl 
 * */
#include <SDL.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;

    SDL_Renderer *render = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("my SDL2 Window",
            200,
            200,
            640,
            480,
            SDL_WINDOW_SHOWN);

    if(!window){
        printf("Failed to create window!");
        goto __EXIT;
    }

    render = SDL_CreateRenderer(window, -1, 0);

    if(!render){
         SDL_Log("Failed to Create Render!");
         goto __DWINDOW;
    }

    SDL_SetRenderDrawColor(render, 255, 0, 0, 200);

    SDL_RenderClear(render);

    SDL_RenderPresent(render); // 展示窗口

    SDL_Delay(30000);

__DWINDOW:
    SDL_DestroyWindow(window);

__EXIT:
    SDL_Quit();
    return 0;
}
