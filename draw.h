#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include<bits/stdc++.h>
#include<SDL.h>

#include<SDL_image.h>
using namespace std;
void draw(int x);

void draw2(int x , int y, int z , int t, int k);

void drawsetting(int x);
//void setup(int x);

void drawend(string s);
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void waitUntilKeyPressed();

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void load_image1(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,SDL_Rect* sourceRect,SDL_Rect* desRect,string s);

void load_image2(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,SDL_Rect* sourceRect,SDL_Rect* desRect,string s);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);


#endif // DRAW_H_INCLUDED
