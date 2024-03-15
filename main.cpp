#include <SDL.h>
#include <SDL_image.h>
#include <bits/stdc++.h>
using namespace std;
SDL_Renderer *renderer=nullptr;
bool run=true;
vector<vector<int>>tilemap={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,2,3,2,0,0,0,0,0,0,0,0,1,2,3,2,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,3,2,1,2,1,2,3,3,2,0,0,0,0,0,0,1,3,2,2,3,1,3},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,5,5,5,5,5,5,5},
    {0,0,4,0,0,0,4,0,0,0,0,4,0,0,0,0,0,0,1,5,5,5,5,5,5,5,5},
    {1,2,3,1,3,1,1,2,1,3,1,1,2,1,3,1,2,1,3,1,1,2,1,3,1,2,1}};
    bool checkcondition(SDL_Rect& object1,SDL_Rect& object2)
{
    int l1=object1.x;
    int r1=object1.x +object1.w;
    int t1=object1.y;
    int b1=object1.y +object1.h;
    int l2=object2.x;
    int r2=object2.x +object2.w;
    int t2=object2.y;
    int b2=object2.y +object2.h;
    bool xoverlap=(r1>l2)&&(r2>l1);
    bool yoverlap=(b1>t2)&& (b2>t1);
    return xoverlap&&yoverlap;
}
class Baseobject
{
public:
    Baseobject(){tex=nullptr;rect.x=0;rect.y=0;}
    void setrect(int x,int y,int w,int h)
    {
        rect.x=x;
        rect.y=y;
        rect.w=w;
        rect.h=h;
    }
    void loadtexture(char *path)
    {
        SDL_Surface *surface=IMG_Load(path);

        tex=SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);
    }
    void loadtexture(char *path,int a,int b,int c)
    {
        SDL_Surface *surface=IMG_Load(path);
        SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,a,b,c));
        tex=SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);
    }
    SDL_Rect &getrect(){return rect;}
    void setrender()
    {
        SDL_RenderCopy(renderer,tex,NULL,&rect);
    }
    void setrender(SDL_Rect rect1)
    {
        SDL_RenderCopy(renderer,tex,&rect1,&rect);
    }
protected:
    SDL_Texture *tex;
    SDL_Rect rect;
};
class Mapp :public Baseobject
{
public:
    Mapp(){tex=nullptr;rect.w=60;rect.h=60;}
    void setrect(int y,int x)
    {
        rect.x=x*60;
        rect.y=y*60;
    }
    void setrect(int x)
    {
        if(x>=480&&x<=1020) rect.x=valx*60-x+480;
    }
     void setrect1(int x,int y,int w,int h)
    {
        rect1.x=x;
        rect1.y=y;
        rect1.w=w;
        rect1.h=h;
    }
    SDL_Rect &getrect1(){return rect1;}
    void updatemap(int x)
    {
        if(x<=1020&&x>=480) rect.x=x-480;
    }
    void setxy(int y_,int  x_){valx=x_;valy=y_;}
    void settouch(bool a){touch=a;}
    int &getvalx(){return valx;}
    int &getvaly(){return valy;}
    bool &gettouch(){return touch;}
protected:
    SDL_Rect rect1;
    bool touch;
    int valx;
    int valy;
};
class Shoot :public Baseobject
{
public:
    Shoot(){tex=nullptr;}
    void setmove(bool a){
        if(a==true&&rect.x<=1620)
        {running=a;}}
    void myhandlemove()
    {
        if(running==true)
        {
            rect.x+=10;
             if(rect.x>=1080)
            {
                running=false;
            }
        }
    }
    void yourhandmove()
    {
        if(running==true)
        {
            rect.x-=8;
             if(rect.x<=0)
            {
                running=false;
            }
        }
    }
    bool getstatus(){return running;}

protected:
    bool running=false;

};
class Enemy:public Baseobject
{
public:
    Enemy(){tex=nullptr;rect.x=1024;rect.y=0;}
    void handlerun()
    {
        x_val=-5;
        rect.x+=x_val;
        if(rect.x<=0)  {rect.x=1024;rect.y=rand()%3*160+120;}
         loadtexture("roi.png",238,243,250);
    }
    void reset()
    {
        rect.x=1080+300;
        rect.y=rand()%3*160+120;
        loadtexture("roi.png",238,243,250);
    }
    void initshoot(Shoot *shoot){
        shoot->setrect(rect.x,rect.y+15,30,30);
        shoot->loadtexture("png/Kunai.png");
        shoot->setmove(true);
        shootlist.push_back(shoot);}
    void handleshoot()
    {
        for(int i=0;i<shootlist.size();i++)
       {Shoot*shoot = shootlist[i];
        if (shoot->getstatus()==true)
       {
          shoot->yourhandmove();
       }
       else
       {
           shoot->setrect(rect.x,rect.y+15,10,10);
           shoot->setmove(true);
       }
       }

    }
    vector<Shoot*> &getshootlist(){return shootlist;}

protected:
    int x_val;
    int y_val;
    vector<Shoot*>shootlist;
    int loadimage;
};
class Mainobject:public Baseobject
{
public:
    Mainobject(){x_val=0;y_val=0;tex=nullptr;rect.x=0;rect.y=0;is_ground=false; speedfall=1;isright=true;numberpicture=0;namepicture="png/";status=0;}
    void setshootlist(vector<Shoot*>shoot){shootlist=shoot;}
    vector<Shoot*> &getshootlist(){return shootlist;}
    void uppos(){x_pos=rect.x;y_pos=rect.y;}
    void checkmap(Mapp mapp)
{
    if (mapp.gettouch())
    {
        is_ground = false;
        int valx = mapp.getvalx();
        int valy = mapp.getvaly();
        int rect_x1 = x_pos;
        int rect_x2 = x_pos + rect.w-1;
        int rect_y1 = y_pos;
        int rect_y2 = y_pos + rect.h-1;
        int x1= rect_x1 / 60;
        int x2=rect_x2/60;
        int y1=rect_y1/60;
        int y2=rect_y2/60;
        if ((x1==valx || x2 == valx)&&y2==valy) {
            if (y_val>0) {y_val = 0;is_ground = true;
            y_pos = y2 * 60 - rect.h;
        }}
        else if ((x1==valx|| x2== valx)&&y1==valy) {
            if (y_val < 0) {y_val = 0;y_pos = y1 * 60;}
        }
        if (y1 ==valy&& x2 == valx) {
            if (x_val > 0) {x_val = 0;x_pos = x2 * 60- rect.w;
        }}
        else if ( y1 == valy&& x1 == valx) {
            if (x_val < 0){ x_val = 0;x_pos = x1 * 60;}
        }
    }
}
    void freefall()
    {
        if(is_ground==false)
        {
            y_val+=speedfall;
            y_pos+=y_val;
            static int ii=1;
            ii++;
            if(ii%30==0) speedfall+=1;
            if(speedfall>=9) speedfall=9;
        }
        else speedfall=1;
    }
    void handleevent()
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                run=false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                     case SDLK_w:
                        y_val-=15;
                        break;
                    case SDLK_s:
                        y_val+=15;
                        if(y_val>15) y_val=15;
                        break;
                    case SDLK_d:
                        x_val+=15;
                        isright=true;
                        break;
                    case SDLK_a:
                        x_val-=15;
                        isright=false;
                        break;
                    case SDLK_q:
                        {Shoot *shoot=new Shoot();
                        shoot->setrect(rect.x+30,rect.y+30,40,20);
                        shoot->loadtexture("png/Kunai.png");
                        shoot->setmove(true);
                        shootlist.push_back(shoot);
                        break;}
                }

                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_w:
                        y_val=0;
                        break;
                    case SDLK_s:
                        y_val=0;
                        break;
                    case SDLK_d:
                        x_val=0;
                        break;
                    case SDLK_a:
                        x_val=0;
                        break;
                    default:
                        break;
                }
                break;
        }
        x_pos+=x_val;
        if(x_pos>=1620-50) x_pos=1620-50;
        else if(x_pos<=0)  x_pos=0;
        y_pos+=y_val;
        if(y_pos>600-50) y_pos=600-50;
        else if(y_pos<0)  y_pos=0;
    }
    void handle()
    {
        if(x_pos<490) rect.x=x_pos;
        else if(x_pos>1030) rect.x=x_pos-540;
        else rect.x=490;
        if(y_pos>540-50) y_pos=540-50;
        rect.y=y_pos;
        if(rect.y<0) rect.y=0;
    }
   /* void setstate()
    {
        if()
    }*/
    void setisground(bool a){is_ground=a;}
    int getxpos(){return x_pos;}
    int getypos(){return y_pos;}
    int getyval(){return y_val;}
    int getxval(){return x_val;}
    bool getisground(){return is_ground;}
    bool &getisright(){return isright;}

protected:
    int x_val;
    int y_val;
    vector<Shoot*>shootlist;
    int x_pos;
    int y_pos;
    bool is_ground;
    int speedfall;
    bool isright;
    int numberpicture;
    int status;
    string namepicture;
};
int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Init(SDL_INIT_EVERYTHING);
    bool isground=false;
    SDL_Window*window=SDL_CreateWindow("GAME",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1080,600,SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    SDL_Surface *surface=IMG_Load("anh.png");
    SDL_Texture *tex=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    vector<Mapp>mapp;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<27;j++)
        {
            Mapp setmap;
            setmap.setrect(i,j);
            setmap.setxy(i,j);
            setmap.loadtexture("map.png");
            if(tilemap[i][j]==1)
            {
                setmap.setrect1(16,16,16,16);
                setmap.settouch(true);
                mapp.push_back(setmap);
            }
            else if(tilemap[i][j]==2)
            {
                setmap.setrect1(48,16,16,16);
                setmap.settouch(true);
                mapp.push_back(setmap);
            }
            else if(tilemap[i][j]==3)
            {
                setmap.setrect1(80,16,16,16);
                setmap.settouch(true);
                mapp.push_back(setmap);
            }
            else if(tilemap[i][j]==4)
            {
                setmap.setrect1(16,112,16,16);
                setmap.settouch(false);
                mapp.push_back(setmap);
            }
            else if(tilemap[i][j]==5)
            {
                setmap.setrect1(112,16,16,16);
                setmap.settouch(false);
                mapp.push_back(setmap);
            }
        }
    }
    Mainobject mainot;
    mainot.setrect(400,400,50,50);
    mainot.uppos();
    mainot.loadtexture("main.png");
    Enemy *enemys=new Enemy[5];
    for(int e=0;e<5;e++)
    {
       Enemy *enemy=(enemys+e);
       enemy->setrect(1620+e*350,rand()%3*160+120,40,40);
       enemy->loadtexture("roi.png",238,243,250);
       // enemy->initshoot(new Shoot());
    }
    SDL_Rect rect1{0,0,1620,600};
    SDL_Rect rect2{1620,0,1620,600};
    while(run)
    {
        SDL_RenderClear(renderer);
        rect1.x-=1;
        rect2.x-=1;
        SDL_RenderCopy(renderer,tex,NULL,&rect1);
        SDL_RenderCopy(renderer,tex,NULL,&rect2);
        if(rect1.x<=-1620) rect1.x=1620;
        if(rect2.x<=-1620) rect2.x=1620;
        mainot.handleevent();
        for(int i=0;i<mapp.size();i++)
        {
            mainot.checkmap(mapp[i]);
            if(mainot.getisground()==true) isground=true;
            int xpos=mainot.getxpos();
            mapp[i].updatemap(xpos);
            mapp[i].setrect(xpos);
            mapp[i].setrender(mapp[i].getrect1());

        }
        mainot.setisground(isground);
        mainot.freefall();
        mainot.handle();
        isground=false;
        vector<Shoot*>& shootlist = mainot.getshootlist();
          for (int i=0;i<shootlist.size();)
    {
         Shoot* shoot = shootlist[i];
       if (shoot->getstatus()==true)
       {
          shoot->myhandlemove();
          shoot->setrender();
              for(int i2=0;i2<5;i2++)
          {
              Enemy *enemy=(enemys+i2);
              bool kt2=checkcondition(shoot->getrect(),enemy->getrect());
              if(kt2==true)
              {
                  enemy->reset();
                  delete shoot;
                  shootlist.erase(shootlist.begin() + i);
                  i2==5;
              }
          }
          i++;
       }
       else
       {
          delete shoot;
          shootlist.erase(shootlist.begin() + i);
       }
    }

      for(int e=0;e<5;e++)
      {
        Enemy *enemy=(enemys+e);
        enemy->handlerun();
        //enemy->handleshoot();
        enemy->setrender();}/*
        bool kt=checkcondition(mainot.getrect(),enemy->getrect());
        if(kt==true)
        {
            return 1;
        }
        vector<Shoot*>& shootlist1 = enemy->getshootlist();
        for(int ii=0;ii<enemy->getshootlist().size();ii++)
        {
            Shoot *shoot1=shootlist1[ii];
            bool kt1=checkcondition(mainot.getrect(),shoot1->getrect());
            if(kt1==true)
            {
                return 1;
            }
        }
      }*/
        mainot.setrender();
        SDL_RenderPresent(renderer);
    }
    return 0;
}
