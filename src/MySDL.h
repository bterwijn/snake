#ifndef MYSDL_H_INCLUDED
#define MYSDL_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>

#include <stdlib.h>
#include <iostream>
#include <string>

class MySDL
{
public:

    // using Singleton Design Pattern
    static MySDL* create_window(std::string title="MyWindow",
                           int width=640,
                           int height=480,
                           std::string font="/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf",
                           unsigned fontSize=28)
    {
        if (_instance==NULL)
            _instance=new MySDL(title,width,height,font,fontSize);
        return _instance;
    }

    static void destroy_window()
    {
        if (_instance!=NULL)
        {
            delete _instance;
            _instance=NULL;
        }
    }

    static MySDL* get_window()
    {   return _instance; }

    SDL_Window* window()
    { return _window;}
    
    SDL_Surface* surface()
    { return _surface;}
    
    SDL_Renderer* renderer()
    { return _renderer;}
        
    TTF_Font *font()
    { return _font;}

    int width()
    { return _width;}

    int height()
    { return _height;}

    void getSize(int& w,int& h)
    { w=_width;h=_height;}

    SDL_Point size()
    {
        SDL_Point p={_width,_height};
        return p;
    }

    SDL_Rect rect()
    {
        SDL_Rect r={0,0,_width,_height};
        return r;
    }
    
    void handleEvent(SDL_Event& e)
    {
        switch( e.window.event )
        {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                _width=e.window.data1;
                _height=e.window.data2;
            break;
        }
    }
    
private:
    SDL_Window* _window=NULL;
    SDL_Surface* _surface=NULL;
    SDL_Renderer* _renderer=NULL;
    TTF_Font *_font=NULL;
    int _width,_height;
    
    static MySDL* _instance;

    MySDL(std::string title,int width,int height,
          std::string font,unsigned fontSize)
    {
        _width=width;
        _height=height;
        if (SDL_Init(SDL_INIT_VIDEO)<0)
        { std::cerr<<"SDL, failed to SDL_Init: "<<SDL_GetError()<<std::endl;exit(1);}
        if ((_window=SDL_CreateWindow(title.c_str(),
                                      SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED,
                                      _width,
                                      _height,
                                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE))==NULL)
        { std::cerr<<"SDL, failed to SDL_CreateWindow: "<<SDL_GetError()<<std::endl;exit(1);}
        if ((_surface=SDL_GetWindowSurface(_window))==NULL)
        { std::cerr<<"SDL, failed to SDL_GetWindowSurface: "<<SDL_GetError()<<std::endl;exit(1);}
        if ((_renderer=SDL_CreateRenderer(_window,-1,SDL_RENDERER_ACCELERATED))==NULL)
        { std::cerr<<"SDL, failed to SDL_CreateRenderer: "<<SDL_GetError()<<std::endl;exit(1);}
        int imgFlags = IMG_INIT_PNG;
        if (!( IMG_Init( imgFlags ) & imgFlags ) )
        { std::cerr<<"IMG, failed to IMG_Init: "<<IMG_GetError()<<std::endl;exit(1);}
        if (TTF_Init()<0)
        { std::cerr<<"TTF, failed to TTF_Init: "<<TTF_GetError()<<std::endl;exit(1);}
        if (font.length()>0)
        {
            if ((_font=TTF_OpenFont(font.c_str(),fontSize))==NULL)
            { std::cerr<<"TTF, failed to TTF_OpenFont: "<<TTF_GetError()<<std::endl;exit(1);}
        }
        std::cout<<"MySDL initialized"<<std::endl;
    }

    ~MySDL()
    {
        TTF_CloseFont(_instance->_font);
        SDL_DestroyRenderer(_instance->_renderer);
        SDL_DestroyWindow(_instance->_window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        std::cout<<"MySDL destroyed"<<std::endl;
    }
    
    MySDL(const MySDL &) { }
    MySDL& operator=(const MySDL &) { return *this; }
};
MySDL* MySDL::_instance=NULL;

MySDL* sdl()
{   return MySDL::get_window(); }

typedef Uint32 Col;
Col MyColor(Uint8 r,Uint8 g,Uint8 b,Uint8 a)
{
    Uint8 c[]={r,g,b,a};
    return *((Col*)c);
}
    
class MyTexture
{
public:
    MyTexture(std::string filename)
    {
        if (sdl())
        {
            SDL_Surface* surface;
            if ((surface=IMG_Load(filename.c_str()))==NULL)
            { std::cerr<<"IMG, failed to IMG_Load: "<<IMG_GetError()<<std::endl;exit(1);}
            makeTexture(surface);
            SDL_FreeSurface(surface);
        }
    }
    
    MyTexture(std::string text,SDL_Color color)
    {
        if (sdl())
        {
            SDL_Surface* surface;
            if ((surface=TTF_RenderText_Solid(sdl()->font(),text.c_str(),color))==NULL)
            { std::cerr<<"TTF, failed to TTF_RenderText_Solid: "<<TTF_GetError()<<std::endl;exit(1);}
            makeTexture(surface);
            SDL_FreeSurface(surface);
        }
    }

    ~MyTexture()
    {
        SDL_DestroyTexture(_texture);
    }

    SDL_Texture* operator()()
    { return _texture;}
    
    int width()
    { return w;}
    
    int height()
    { return h;}

    SDL_Rect size()
    {
        SDL_Rect rect={0,0,w,h};
        return rect;
    }

    int w,h; // public, as done for surfaces
private:

    void makeTexture(SDL_Surface* surface)
    {
        if (sdl())
        {
            w=surface->w;
            h=surface->h;
            if ((_texture=SDL_CreateTextureFromSurface(sdl()->renderer(),surface))==NULL)
            { std::cerr<<"SDL, failed to SDL_CreateTextureFromSurface: "<<SDL_GetError()<<std::endl;exit(1);}
        }
    }
    
    SDL_Texture* _texture;
};

#endif
