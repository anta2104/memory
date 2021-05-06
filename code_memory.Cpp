#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
//#include "draw.h"
using namespace std;


const int SCREEN_WIDTH = 1000;

const int SCREEN_HEIGHT = 800;

const int r_pad=100,c_pad=70;

const int sizew=6;// 8

const int sizeh=4;//6

int matrix_number=sizew*sizeh;

const int number_max=4;


const int number_image=(sizeh * sizew)/ number_max;
const int cell_size=(SCREEN_WIDTH-2*r_pad)/sizew;

const string WINDOW_TITLE = "Memmory";

void logSDLError(std::ostream& os,const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void waitUntilKeyPressed();

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void load_image1(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,SDL_Rect* sourceRect,SDL_Rect* desRect,string s);

void load_image2(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Texture* texture,SDL_Rect* sourceRect,SDL_Rect* desRect,string s);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

void draw(int x);

void draw2(int x , int y, int z , int t, int k);

void setup(int x);

void drawend(string s);

void setup(int x);

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* surface;
SDL_Texture* texture;
SDL_Rect sourceRect;
SDL_Rect desRect;

struct coordinates
{
    int x,y;
};

 vector<vector<int> > matrix(sizeh+2,vector<int>(sizew+2,0));


int main(int argc,char* argv[])
{
    srand(time(NULL));

    initSDL(window, renderer);
  //  SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);

    SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);


    SDL_Texture *background1 = loadTexture("background1.bmp", renderer);
    renderTexture(background1, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    int heart=15;
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    setup(heart);

    SDL_RenderPresent(renderer);
    SDL_Event e;
    coordinates Turn[2];
    int sum=0,Count=-1;



    while (true)
    {

        SDL_Delay(10);
        if ( SDL_WaitEvent(&e) == 0) continue;

        if (e.type == SDL_QUIT) quitSDL(window , renderer);

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;

        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT ){

            int x = floor(double(e.button.y-c_pad) / cell_size)+1;
            int y = floor(double(e.button.x-r_pad) / cell_size)+1;

            int tam1=e.button.x;
            int tam2=e.button.y;
            if (heart==0 ||sum==matrix_number){
                if (tam1<=SCREEN_WIDTH/2 && tam1>=SCREEN_WIDTH/3 && tam2>=600 && tam2<=700 )
                   {
                        SDL_RenderClear(renderer);

                        heart=15;
                        setup(heart);
                        sum=0;
                        Count=-1;
                        SDL_RenderPresent(renderer);
                        continue;
                   }

            else  if (tam1>=SCREEN_WIDTH/2 && tam1<=(SCREEN_WIDTH/3)*2 && tam2>=600 && tam2<=700) quitSDL(window, renderer);

            else continue;
            }

            if (Count==0 && (x<1 || x>sizeh || y<1 || y>sizew || matrix[x][y]==0))
            {
                draw(heart);

                Count=-1;
            }

           if (x>=1 && x<=sizeh && y>=1 && y<=sizew && matrix[x][y]!=0)

           {
               Count++;
               Turn[Count].x=x;
               Turn[Count].y=y;


                if (Count==0)  {draw2(Turn[Count].x,Turn[Count].y,-1,-1,heart);


                SDL_RenderPresent(renderer);}


                 if (Count==1 && Turn[0].x==Turn[1].x && Turn[0].y==Turn[1].y)
                {

                    Count=0;
                }
                else if (Count==1 && matrix[Turn[0].x][Turn[0].y] == matrix[Turn[1].x][Turn[1].y])
                {
                    draw2(Turn[0].x,Turn[0].y,Turn[1].x, Turn[1].y,heart);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(500);
                    matrix[Turn[0].x][Turn[0].y]=0;
                    matrix[Turn[1].x][Turn[1].y]=0;
                    draw(heart);
                    SDL_RenderPresent(renderer);
                    sum +=2;
                    if (sum==matrix_number) drawend("win_1.bmp");
                    Count=-1;

                }
                else


                if (Count==1 && matrix[Turn[0].x][Turn[0].y]!=matrix[Turn[1].x][Turn[1].y])
                {
                     heart--;
                     draw2(Turn[0].x,Turn[0].y,Turn[1].x, Turn[1].y,heart);
                    // SDL_RenderPresent(renderer);

                     SDL_RenderPresent(renderer);
                     SDL_Delay(500);
                     draw(heart);

                     SDL_RenderPresent(renderer);
                     if (heart==0)   drawend("you_lose.bmp");
                     Count=-1;
                }


           }


           if (heart==0 || sum==matrix_number) drawend("return.bmp");

     }




    }
    //waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;


}
/****************************************************/
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

void setup(int x)
{
  /* SDL_RenderClear(renderer);
   SDL_Texture *background = loadTexture("anh_nen_01.bmp", renderer);
   renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
   SDL_Texture *image= loadTexture("heart.bmp",renderer);
   renderTexture(image,renderer,0,0,50,50);
   SDL_Texture *image1=loadTexture("dau_x2.bmp",renderer);
    renderTexture(image1,renderer,70,25,25,25);*/
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

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
    SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
    //(ảnh sẽ co dãn cho khớp với kích cỡ mới)
	SDL_RenderCopy(ren, tex, NULL, &dst);
}
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
	//Khởi tạo là nullptr để tránh lỗi 'dangling pointer'
	SDL_Texture *texture = nullptr;
	//Nạp ảnh từ tên file (với đường dẫn)
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//Nếu không có lỗi, chuyển đổi về dạng texture and và trả về
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Đảm bảo việc chuyển đổi không có lỗi
		if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}
/****************************************************************/
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    /*window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);*/

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    //Khi thÃ´ng thÆ°á»ng cháº¡y vá»›i mÃ´i trÆ°á»ng bÃ¬nh thÆ°á»ng á»Ÿ nhÃ

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //Khi cháº¡y á»Ÿ mÃ¡y thá»±c hÃ nh WinXP á»Ÿ trÆ°á»ng (mÃ¡y áº£o)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    if(SDL_Init(SDL_INIT_AUDIO)==-1)
    {
        printf("SDL_Init: %s\n", SDL_GetError());
        exit(1);
    }


}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
    if ( SDL_WaitEvent(&e) != 0 &&
    (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
    return;
    SDL_Delay(100);
    }
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
//    TTF_Quit();
}



