#include "draw.h"
using namespace std;
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* surface;
SDL_Texture* texture;
SDL_Rect sourceRect;
SDL_Rect desRect;
const int SCREEN_WIDTH = 1000;

const int SCREEN_HEIGHT = 800;

const int r_pad=100,c_pad=70;

const int sizew=6;// 8

const int sizeh=4;//6

int matrix_number=sizew*sizeh;

const int number_max=4;
vector<vector<int> > matrix(sizeh+2,vector<int>(sizew+2,0));
const int number_image=(sizeh * sizew)/ number_max;
const int cell_size=(SCREEN_WIDTH-2*r_pad)/sizew;

const string WINDOW_TITLE = "Memmory";

void drawsetting(int x)
    {
    stringstream sss;
    sss << x;
    string s="so"+sss.str();
    SDL_RenderClear(renderer);
    SDL_Texture *background = loadTexture("anh_nen_01.bmp", renderer);
    renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Texture *image= loadTexture("heart.bmp",renderer);
    renderTexture(image,renderer,0,0,50,50);
    SDL_Texture *image1=loadTexture("dau_x2.bmp",renderer);
    renderTexture(image1,renderer,70,20,25,25);
    SDL_Texture *image2=loadTexture(s+".bmp",renderer);
    renderTexture(image2,renderer,100,0,50,50);

    }

void draw(int x)
{
    drawsetting(x);
    for (int i=1;i<=sizeh;i++)
        for (int j=1;j<=sizew;j++)
        if (matrix[i][j]!=0)
        {
            desRect.x=r_pad+(j-1)*cell_size;
            desRect.y=c_pad+(i-1)*cell_size;
            desRect.w=cell_size-10;
            desRect.h=cell_size-10;
            load_image2(renderer,surface,texture,NULL,&desRect,"hoi_cham.bmp");
        }

}
void draw2(int x,  int y ,int z , int t  ,int k)
{
     drawsetting(k);
     for (int i=1;i<=sizeh;i++)
        for (int j=1;j<=sizew;j++)
        if (i==x && j==y )
        {
            stringstream ss;
            ss<<matrix[i][j];
            desRect.x=r_pad+(j-1)*cell_size;
            desRect.y=c_pad+(i-1)*cell_size;
            desRect.w=cell_size-10;
            desRect.h=cell_size-10;
            load_image1(renderer,surface,texture,NULL,&desRect,ss.str()+".bmp");
        }

        else if (i==z && j==t)
        {
             stringstream ss;
            ss<<matrix[i][j];
            desRect.x=r_pad+(j-1)*cell_size;
            desRect.y=c_pad+(i-1)*cell_size;
            desRect.w=cell_size-10;
            desRect.h=cell_size-10;
            load_image1(renderer,surface,texture,NULL,&desRect,ss.str()+".bmp");
    }
        else if (matrix[i][j] != 0 )
        {
            desRect.x=r_pad+(j-1)*cell_size;
            desRect.y=c_pad+(i-1)*cell_size;
            desRect.w=cell_size-10;
            desRect.h=cell_size-10;
            load_image2(renderer,surface,texture,NULL,&desRect,"hoi_cham.bmp");

        }

}


void drawend( string s)
{

    SDL_Texture *image = loadTexture(s, renderer);
    renderTexture(image, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent(renderer);
    SDL_Delay(1200);
    //quitSDL(window, renderer);
}
void setup(int x)
{

   drawsetting(x);
   vector<int> arr(number_image+1,number_max);
   for (int i=1;i<=sizeh;i++)
        for (int j=1;j<=sizew;j++)
        {
            int temp;
            do temp=rand()%number_image+1;
            while (arr[temp]==0);
            matrix[i][j]=temp;
            arr[temp]--;

            desRect.x=r_pad+(j-1)*cell_size;
            desRect.y=c_pad+(i-1)*cell_size;
            desRect.w=cell_size-10;
            desRect.h=cell_size-10;
            load_image2(renderer,surface,texture,NULL,&desRect,"hoi_cham.bmp");
        }
}

void load_image2(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,SDL_Rect* sourceRect,SDL_Rect* desRect,string s)
{
    surface= SDL_LoadBMP(s.c_str());
    texture=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    SDL_RenderCopy(renderer,texture,sourceRect,desRect);


}

void load_image1(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,SDL_Rect* sourceRect,SDL_Rect* desRect,string s)
{
    s="image"+s;
    surface= SDL_LoadBMP(s.c_str());
    texture=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    SDL_RenderCopy(renderer,texture,sourceRect,desRect);

}
