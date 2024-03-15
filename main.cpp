#include <SDL.h>
#include <SDL_image.h>
#include <bits/stdc++.h>
using namespace std;
SDL_Renderer *renderer=nullptr;
bool run=true;
int score=0;
vector<vector<int>>tilemap={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,3,2,1,2,1,0,0,0,0,0,0,0,2,3,1,3,3,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,0,0,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,3,2,1,2,1,2,3,3,2,1,3,2,2,3,1,3,3,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,4,0,0,4,0,0,0,4,0,0,0,4,0,0,0,0,0,0,0,0},
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
    Enemy(){tex=nullptr;rect.x=1024;rect.y=0;frame=0;slowspeed=0;touch=false;}
    void handlerun()
    {
        x_val=-5;
        slowspeed+=1;
        if(slowspeed==120) slowspeed=0;
        if(slowspeed%4==0) frame+=1;
        rect.x+=x_val;
        if(rect.x<=0)  {rect.x=1024;rect.y=((rand()%3)*3+2)*60+10;score++;touch=false;}
        setrectimage();
    }
    void reset()
    {
        score+=2;
        rect.x=1080+300;
        rect.y=((rand()%3)*3+2)*60+10;
        touch=false;
    }
    void initshoot(Shoot *shoot){
        shoot->setrect(rect.x,rect.y+15,30,30);
        shoot->loadtexture("Kunai.png");
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
    SDL_Rect &getrectimage(){return rect1;}
    bool &gettouch(){return touch;}
    void setrectimage()
    {
        rect1.w=53;
        rect1.h=57;
        rect1.y=0;
        int i=frame%3;
        rect1.x=i*53;

    }
    vector<Shoot*>&getshootlist(){return shootlist;}
    void settouch(bool a){touch=a;}


protected:
    int x_val;
    int y_val;
    vector<Shoot*>shootlist;
    SDL_Rect rect1;
    int frame;
    int slowspeed;
    bool touch;

};
class Mainobject:public Baseobject
{
public:
    enum Doing
    {
        DUNG=0,
        CHAY=1,
        NHAY=2,
        ROI=3,
        CHEO=4,
        DAU=5,
        NEM=6,
    };
    Mainobject(){x_val=0;y_val=0;tex=nullptr;rect.x=0;rect.y=0;is_ground=false; speedfall=1;isright=true;status=0;frame=0;statusbefore=-1;cheo=false;numbercheo=0;fixerror=false;hp=3;mana=8;}
    void setshootlist(vector<Shoot*>shoot){shootlist=shoot;}
    vector<Shoot*> &getshootlist(){return shootlist;}
    void uppos(){x_pos=rect.x;y_pos=rect.y;}
    void checkmap(vector<vector<int>>mapp)
{

        x_pos+=x_val;
        if(x_pos>=1620-50) x_pos=1620-50;
        else if(x_pos<=0)  x_pos=0;
        y_pos+=y_val;
        if(y_pos>600-50) y_pos=600-50;
        else if(y_pos<0)  y_pos=0;
        is_ground=false;
        int rect_x1 = x_pos;
        int rect_x2 = x_pos + rect.w;
        int rect_y1 = y_pos;
        int rect_y2 = y_pos + rect.h;
        int x1= rect_x1/60;
        int x2=(rect_x2-1)/60;
        int y1=rect_y1/60;
        int y2=(rect_y2-1)/60;
        if(cheo==true)
        {
            if(((mapp[y2][x2]!=0&&mapp[y2][x2]!=4)||(mapp[y2][x1]!=0&&mapp[y2][x1]!=4))&&fixerror==true||numbercheo>0)
            {
               if(y2*60-50+1==491)
               {y_pos=y2*60-50+1;
                is_ground=true;
                cheo=false;numbercheo=0;
                fixerror=false;
                }
               else
               {
                   if(statusbefore!=CHEO)
                   {numbercheo=(y2+1);}
                   is_ground=true;
                   if(y_pos<numbercheo*60)
                   {
                       is_ground=true;
                       y_val=2;
                       x_val=0;
                       y_pos+=y_val;
                       status=CHEO;
                   }
                   else {cheo=false;numbercheo=0;fixerror=false;}

               }
            }
            else
          {
             if((mapp[y1][x1]!=0&&mapp[y1][x1]!=4)||(mapp[y1][x2]!=0&&mapp[y1][x2]!=4)||numbercheo<0)
            {
               if(statusbefore!=CHEO)
                {numbercheo=-(y1-1);}
               if(y_pos>-numbercheo*60+10)
               {
                   is_ground=true;
                   y_val=-2;
                   x_val=0;
                   y_pos+=y_val;;
                   status=CHEO;
               }
               else{
                cheo=false;
                numbercheo=0;
               }
            }
            else
            {
                cheo=false;
                numbercheo=0;
                y_pos-=y_val;
                y_val=0;
            }
          }
        }
        else{
        if((mapp[y2][x2]!=0&&mapp[y2][x2]!=4)||(mapp[y2][x1]!=0&&mapp[y2][x1]!=4))
            {
               y_pos=y2*60-50+1;
               is_ground=true;
               if(y_val>0) y_val=0;
            }
        if(y_val<0)
        {
             if((mapp[y1][x1]!=0&&mapp[y1][x1]!=4)||(mapp[y1][x2]!=0&&mapp[y1][x2]!=4))
            {
               y_pos=(y1+1)*60;
               y_val=0;
            }
        }
        if(x_val>0)
        {
             if((mapp[y1][x2]!=0&&mapp[y1][x2]!=4))
            {
               x_pos=x2*60-50+1;
               x_val=0;
            }
        }
        else if(x_val<0)
        {
             if((mapp[y1][x1]!=0&&mapp[y1][x1]!=4))
            {
               x_pos=(x1+1)*60;
               x_val=0;
            }
        }
        }
}
    void freefall()
    {
        if(is_ground==false)
        {
            y_val+=speedfall;
            static int ii=1;
            ii++;
            if(ii==160) ii=0;
            if(ii%80==0) speedfall+=1;
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
                        if(keypress.find(SDLK_w)==keypress.end()) keypress[SDLK_w] =0;
                        if(keypress[SDLK_w]<10)
                        {y_val-=15;
                        if(y_val<=-60) y_val=-59;}
                        break;
                    case SDLK_s:
                       if(keypress.find(SDLK_s)==keypress.end()) keypress[SDLK_s] =0;
                        if(keypress[SDLK_s]<1000)
                        {y_val+=15;
                        if(y_val>=60) y_val=59;}
                        break;
                    case SDLK_d:
                        if(keypress.find(SDLK_d) ==keypress.end()) keypress[SDLK_d] =0;
                        if(keypress[SDLK_d]<1000)
                        {x_val+=15;if(x_val>=60) x_val=59;
                        isright=true;}
                        break;
                    case SDLK_a:
                       if(keypress.find(SDLK_a) ==keypress.end()) keypress[SDLK_a] =0;
                        if(keypress[SDLK_a]<1000)
                        {x_val-=15;if(x_val<=-60) x_val=-59;
                        isright=false;}
                        break;
                    case SDLK_q:
                        if(keypress.find(SDLK_q) ==keypress.end()) keypress[SDLK_q] =0;
                        if(keypress[SDLK_w]<1000)
                        {if(mana>=1)
                        {
                        status=NEM;
                        isright=true;
                        Shoot *shoot=new Shoot();
                        shoot->setrect(rect.x+30,rect.y+30,40,20);
                        shoot->loadtexture("Kunai.png");
                        shoot->setmove(true);
                        shootlist.push_back(shoot);
                        mana--;}
                        break;
                        }
                        break;
                    case SDLK_f:
                         if(keypress.find(SDLK_f) ==keypress.end()) keypress[SDLK_f] =0;
                        if(keypress[SDLK_f]<1000)
                          {cheo=true;
                          fixerror=true;}
                          break;
                    case SDLK_e:
                           if(keypress.find(SDLK_e) ==keypress.end()) keypress[SDLK_e] =0;
                           if(keypress[SDLK_e]<1000)
                            {cheo=true;
                            y_val-=10;
                            if(y_val>=-80) y_val=-79;}
                            break;
                }

                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_w:
                        keypress.erase(SDLK_w);
                        y_val=0;
                        break;
                    case SDLK_s:
                        keypress.erase(SDLK_s);
                        y_val=0;
                        break;
                    case SDLK_d:
                        keypress.erase(SDLK_d);
                        x_val=0;
                        break;
                    case SDLK_a:
                        keypress.erase(SDLK_a);
                        x_val=0;
                        break;
                    case SDLK_e:
                        keypress.erase(SDLK_e);
                        y_val=0;
                        break;
                    case SDLK_f:
                        keypress.erase(SDLK_f);
                        y_val=0;
                        break;
                    case SDLK_q:
                        keypress.erase(SDLK_q);
                        status=DUNG;
                        break;
                    default:
                        break;
                }
                break;
        }
        for(auto&[key,time]:keypress)
        {
            time +=5;
        }
    }
    void handle()
    {
        setstatus();
        setrectimage();
        if(x_pos<490) rect.x=x_pos;
        else if(x_pos>1030) rect.x=x_pos-540;
        else rect.x=490;
        if(y_pos>540-50+1) y_pos=540-50-1;
        rect.y=y_pos;
        if(rect.y<0) rect.y=0;
        setmana();
    }
    void setisground(bool a){is_ground=a;}
    int &getxpos(){return x_pos;}
    int getypos(){return y_pos;}
    int getyval(){return y_val;}
    int getxval(){return x_val;}
    bool getisground(){return is_ground;}
    bool &getisright(){return isright;}
    void setstatus()
    {

        if(status==CHEO&&numbercheo!=0||status==DAU||status==NEM){;}
        else if(is_ground==true&&x_val==0) status=DUNG;
        else if(is_ground==true&&x_val!=0) status=CHAY;
        else if(is_ground==false&&y_val>0) status= ROI;
        else if(is_ground==false&&y_val<0) status= NHAY;
        if(statusbefore!=status)
        {
            frame=0;
            slowspeed=0;
        }
        statusbefore=status;
    }
    void setstatusdau()
    {
        status=DAU;
    }
    SDL_Rect getrectimage()
    {
        return rect1;
    }
    void setrectimage()
    {
        rect1.w=33;
        rect1.h=33;
        if(isright==true) rect1.y=0;
        else rect1.y=33;
        if(status==DUNG)
        {
            slowspeed+=1;
            if(slowspeed==120) slowspeed=0;
            if(slowspeed%4==0) frame++;
            int i=frame%4;
            rect1.x=i*33;
        }
        else if(status==CHAY)
        {
            slowspeed+=1;
            if(slowspeed==120) slowspeed=0;
            if(slowspeed%5==0) frame++;
            int i=frame%5;
            rect1.x=(i+4)*33;
        }
        else if(status==NHAY)
        {
            slowspeed+=1;
            if(slowspeed==120) slowspeed=0;
            if(slowspeed%6==0) frame++;
            if(frame>=2) rect1.x=10*33;
            else rect1.x=9*33;
        }
        else if(status==ROI)
        {
            slowspeed+=1;
            if(slowspeed==120) slowspeed=0;
            if(slowspeed%4==0) frame++;
            int i=frame%2;
            rect1.x=(i+11)*33;
        }
        else if(status==CHEO)
        {
            slowspeed+=1;
            if(slowspeed==120) slowspeed=0;
            if(slowspeed%3==0) frame++;
            int i=frame%3;
            rect1.x=(i+13)*33;
        }
        else if(status==DAU)
        {
            slowspeed+=1;
            if(slowspeed==120) slowspeed=0;
            if(slowspeed%30==0) frame++;
            if(frame>=3) rect1.x=17*33;
            else rect1.x=16*33;
        }
        else if(status==NEM)
        {
            slowspeed+=1;
            if(slowspeed==120) slowspeed=0;
            if(slowspeed%30==0) frame++;
            int i=frame%2;
            rect1.x=(i+7)*33;
        }
    }
    void setmana()
    {
        mana+=0.001;
        if(mana>=8) mana=8;
    }
    void sethp(bool a)
    {
        if(a==true) hp+=1;
        else hp--;
        if(hp>3) hp=3;
    }
    float &getmana(){return mana;}
    int &gethp(){return hp;}
    int &getstatus(){return status;}
    void resetstatus()
    {
        status=DUNG;
    }
    void addmana()
    {
        mana+=2;
        if(mana>8) mana=8;
    }


protected:
    int x_val;
    int y_val;
    vector<Shoot*>shootlist;
    int x_pos;
    int y_pos;
    bool is_ground;
    int speedfall;
    bool isright;
    int status;
    int statusbefore;
    int slowspeed;
    SDL_Rect rect1;
    bool cheo;
    int numbercheo;
    int frame;
    bool fixerror;
    int hp;
    float mana;
    unordered_map<SDL_Keycode, float> keypress;
};
class Item :public Baseobject
{
public:
    Item(){display=false;rect.h=40;rect.w=40,rect.x=0;rect.y=0;slowspeed=0;rect1.w=21;rect1.h=21;rect1.y=0;frame=0;x_pos=0;}
    void setrectitemload(int x)
    {
        if(x>=490&&x<=1030) rect.x=x_pos-x+490;
        else if(x<490) rect.x=x_pos;
        else rect.x=x_pos-540;
    }
    void setrectitem()
    {
        rect.y=((rand()%3)*3+2)*60;
        rect.x=(rand()%12+6)*60;
        x_pos=rect.x;
    }
    void setrectitem(int x)
    {
        rect.y=((rand()%3)*3+2)*60;
        if(x>=490&&x<=1030)
        {rect.x=(rand()%12+6)*60-x+490;
        x_pos=rect.x+x-490;}
        else if(x<490) rect.x=(rand()%12+6)*60;
        else rect.x=(rand()%12+6)*60-540;
    }
    void setdisplay()
    {
        display =false;
    }
    bool &getdisplay()
    {
        return display;
    }
    SDL_Rect &getrect1(){return rect1;}
    void setrectimage()
    {
       slowspeed++;
       if(slowspeed==150) slowspeed=0;
       if(slowspeed%30==0) frame++;
       int i=frame%7;
       rect1.x=i*21;
    }
    void setdisplayscreen()
    {
        if(display==false){
        static int i=1;
        i++;
        if(i%1000==0) {display=true;i=1;}
        }
    }
    void reset(int x)
    {
        setdisplay();
        setrectitem(x);
    }
protected:
    bool display;
    SDL_Rect rect1;
    int slowspeed;
    int frame;
    int x_pos;
};
class Bar:public Baseobject
{
public:
    Bar(){rect1.x=0;rect1.y=0;}
    void setrect(int number,int x,int y)
    {
        rect.x=x;
        rect.y=y;
        if(number==3) {rect.h=48;rect1.h=250;}
        else {rect.h=18;rect1.h=225;}
    }
    void setrectw(int x)
    {
       rect1.w=x*315;
       rect.w=48*x;
    }
    void setrectw(float x)
    {
        rect1.w=225*x;
        rect.w=18*x;
    }
    SDL_Rect getrect1(){return rect1;}
protected:
    SDL_Rect rect1;
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
        }
    }
    Bar healthbar;
    healthbar.loadtexture("heart.png");
    healthbar.setrect(3,100,50);
    Bar manabar;
    manabar.loadtexture("mana.png",255,255,255);
    manabar.setrect(8,100,100);
    Baseobject avatar;
    avatar.loadtexture("avartar.png");
    avatar.setrect(35,30,75,75);
    Mainobject mainot;
    mainot.setrect(400,200,50,50);
    mainot.uppos();
    mainot.loadtexture("main.png");
    Enemy *enemys=new Enemy[5];
    for(int e=0;e<5;e++)
    {
       Enemy *enemy=(enemys+e);
       enemy->setrect(1620+e*350,((rand()%3)*3+2)*60+10,40,40);
       enemy->loadtexture("roi.png");
    }
    SDL_Rect rect1{0,0,1620,600};
    SDL_Rect rect2{1620,0,1620,600};
    vector<Item>item;
    for(int i=0;i<2;i++)
    {
        Item setitem;
        setitem.loadtexture("cherry.png");
        setitem.setrectitem();
        item.push_back(setitem);
    }
    while(run)
    {
        int i1=SDL_GetTicks();
        SDL_RenderClear(renderer);
        rect1.x-=1;
        rect2.x-=1;
        SDL_RenderCopy(renderer,tex,NULL,&rect1);
        SDL_RenderCopy(renderer,tex,NULL,&rect2);
        if(rect1.x<=-1620) rect1.x=1620;
        if(rect2.x<=-1620) rect2.x=1620;
        mainot.handleevent();
        mainot.freefall();
        mainot.checkmap(tilemap);
        mainot.handle();
        for(int i=0;i<mapp.size();i++)
        {   int xpos=mainot.getxpos();
            mapp[i].updatemap(xpos);
            mapp[i].setrect(xpos);
            mapp[i].setrender(mapp[i].getrect1());

        }
        for(int i=0;i<item.size();i++)
        {   int xpos=mainot.getxpos();
            item[i].setdisplayscreen();
            if(item[i].getdisplay()==true){
            item[i].setrectimage();
            item[i].setrectitemload(xpos);
            bool a=checkcondition(mainot.getrect(),item[i].getrect());
            if(a==true) {item[i].reset(xpos);mainot.sethp(true);mainot.addmana();}
            else {item[i].setrender(item[i].getrect1());}}

        }
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
        enemy->setrender(enemy->getrectimage());
        bool kt=checkcondition(mainot.getrect(),enemy->getrect());
        if(kt==true)
        {
            mainot.setstatusdau();
            if(enemy->gettouch()==false)
            {mainot.sethp(false);
            enemy->settouch(true);}
        }

      }
        mainot.handle();
        avatar.setrender();
        int hp=mainot.gethp();
        healthbar.setrectw(hp);
        float mana=mainot.getmana();
        manabar.setrectw(mana);
        healthbar.setrender(healthbar.getrect1());
        manabar.setrender(manabar.getrect1());
        mainot.setrender(mainot.getrectimage());
        SDL_RenderPresent(renderer);
        if(mainot.getstatus()==5) mainot.resetstatus();
        if(hp<=0) {
                SDL_Delay(3000);
                return 0;
        }
        int i2=SDL_GetTicks();
        if(i2-i1<1000/60)
        {
            SDL_Delay(100/6-i2+i1);
        }

    }
    return 0;
}
