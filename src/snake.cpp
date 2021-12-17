#include "Board.h"

constexpr int SCREEN_FPS = 100;
constexpr int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

int main()
{
    srand (time(NULL));
    cout<<"snake\n";

    Board board;
    cout<<board;

    MySDL::create_window("snake",600,600);
    bool running=true;
    while (running)
    {
        int ticks_start=SDL_GetTicks();
        SDL_Event e;
        while( SDL_PollEvent(&e))
        {
            switch(e.type)
            {
            case SDL_QUIT:        running = false;       break;
            case SDL_WINDOWEVENT: sdl()->handleEvent(e); break;
            }
        }

        SDL_RenderClear(sdl()->renderer());
        board.draw(window_param());
        board.step();
        SDL_SetRenderDrawColor(sdl()->renderer(),0,0,0,255); // black background
        SDL_RenderPresent(sdl()->renderer());
        int frame_ticks=SDL_GetTicks()-ticks_start;
        if( frame_ticks < SCREEN_TICKS_PER_FRAME ) SDL_Delay( SCREEN_TICKS_PER_FRAME - frame_ticks ); // delay for right framerate
    }
    
    return 0;
}
