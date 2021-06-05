/*演示sdl窗口创建和渲染
 *clang -g -o event_sdl event_sdl.c `pkg-config --cflags --libs sdl2`
/.event_sdl 
 * */
#include <SDL.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int quit = 1;

    SDL_Event event;

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

    SDL_SetRenderDrawColor(render, 0, 255, 0, 50);

    SDL_RenderClear(render);

    SDL_RenderPresent(render); // 展示窗口

    //SDL_Delay(30000);
    do{
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                quit = 0;
                break;
            default:
                SDL_Log("event type is %d", event.type);
        }
    }while(quit);

__DWINDOW:
    SDL_DestroyWindow(window);

__EXIT:
    SDL_Quit();
    return 0;
}
