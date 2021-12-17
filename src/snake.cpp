#include "Board.h"

int main()
{
    cout<<"snake\n";

    Board<10,10> board;
    cout<<board;

    MySDL::create_window("snake",600,600);
    bool running=true;
    while (running)
    {
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
        board.draw();
        SDL_SetRenderDrawColor(sdl()->renderer(),0,0,0,255); // black background
        SDL_RenderPresent(sdl()->renderer());
    }
    
    return 0;
}
