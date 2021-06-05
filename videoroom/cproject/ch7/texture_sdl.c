/*演示sdl窗口创建和渲染
 *clang -g -o texture_sdl texture_sdl.c `pkg-config --cflags --libs sdl2`
/.texture_sdl 
 * */
#include <SDL.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int quit = 1;

    SDL_Event event;

    SDL_Window *window = NULL;

    SDL_Renderer *render = NULL;

    SDL_Texture *texture;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    SDL_Log("HHH--");

    window = SDL_CreateWindow("my SDL2 Window",
            200,
            400,
            640,
            480,
            SDL_WINDOW_SHOWN);

    if(!window){
        printf("Failed t create window!");
        goto __EXIT;
    }

    render = SDL_CreateRenderer(window, -1, 0);

    if(!render){
         SDL_Log("Failed to Create Render!");
         goto __DWINDOW;
    }

    

    texture = SDL_CreateTexture(render, 
            SDL_PIXELFORMAT_RGBA8888, 
            SDL_TEXTUREACCESS_TARGET,
            640,
            480);
    if(!texture){
        SDL_Log("Failed to create Texture!");
        goto __RENDER;
    }
    //SDL_Delay(30000);
    do{
       // SDL_WaitEvent(&event); // 有事件才触发绘制
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                quit = 0;
                break;
            default:
                SDL_Log("event type is %d", event.type);
        }

        SDL_Rect rect;
        rect.w = 30;
        rect.h = 30;
        rect.x = rand() % 600;
        rect.y = rand() % 450;

        // 设置纹理
        SDL_SetRenderTarget(render, texture);
        SDL_SetRenderDrawColor(render, 255,0,0,0);
        SDL_RenderClear(render);
        // 绘制rect
        SDL_RenderDrawRect(render, &rect);
        SDL_SetRenderDrawColor(render, 0,0,255,0);
        SDL_RenderFillRect(render, &rect);

        SDL_SetRenderTarget(render, NULL);
        SDL_RenderCopy(render,texture,NULL,NULL);

        SDL_RenderPresent(render);

    }while(quit);

    SDL_DestroyTexture(texture);

__RENDER:
    SDL_DestroyRenderer(render);

__DWINDOW:
    SDL_DestroyWindow(window);

__EXIT:
    SDL_Quit();
    return 0;
}
