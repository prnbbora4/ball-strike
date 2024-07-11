#include<graphics.h>
#include<windows.h>
#include<math.h>
#include<stdio.h>
#include<iostream>
#include<time.h>
#define ACTIVE 1
#define DEACTIVE 0
time_t timer,timer1,timer2;
double s1,s2;
char msg[120],msg2[120];
char scoreprint[120];
int pocketsize=85,x,y;
void leftoppocket()
    {
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, 0);
    circle(0,0, pocketsize);
    floodfill(pocketsize/2,pocketsize/2, BLUE);
    }
void righttoppocket()
    {
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, 0);
    circle(x,0, pocketsize);
    floodfill(x-pocketsize/2,pocketsize/2, BLUE);
    }
void leftbottompocket()
    {
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, 0);
    circle(0,y,pocketsize);
    floodfill(pocketsize/2,y-pocketsize/2, BLUE);
    setfillstyle(SOLID_FILL,BLACK);
    bar(0,y+1,x,y+45);
    }
void rightbottompocket()
    {
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, 0);
    circle(x,y, pocketsize);
    floodfill(x-pocketsize/2,y-pocketsize/2, BLUE);
    setfillstyle(SOLID_FILL,BLACK);
    bar(0,y+1,x,y+45);
    }
void board()
    {
    //Boundary
    setcolor(BLUE);
    rectangle(0,0,x,y);
    rectangle(1,1,x-1,y-1);
    rectangle(2,2,x-2,y-2);
    rectangle(3,3,x-3,y-3);
    rectangle(4,4,x-4,y-4);

    //Pocket
    leftoppocket();
    righttoppocket();
    leftbottompocket();
    rightbottompocket();
    }



int main()
{
    DWORD screenWidth=GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight=GetSystemMetrics(SM_CYSCREEN);
    initwindow(screenWidth-10, screenHeight-70, "BALLS STRIKE", 0, 5, false, true);
    setbkcolor(GREEN);
    ///ball decleration
    float ballpositionx[10],ballpositiony[10],vcomponentx[10],vcomponenty[10],d=100,cursorstatus[10],deadtime,deadtimedecrease;
    int clrall=0,lefttime=40,color[10],rp,p,score,overlap,overlap1,overlap2,balldistance;
    float angleofmovement[10],friction=0.003,velocity[10];
    char a='g';
    x=getmaxx();
    y=getmaxy();
    y=y-45;
    ///initializing color and cursorstatus
    for(int i=0; i<9; i++)
    {
        cursorstatus[i]=ACTIVE;
        color[i]=i+1;
        if(i==1)
            color[i]=999;
    }
    //initializing ball position
    ballpositionx[0]=(x/2)+300;
    ballpositiony[0]=y/2;
    angleofmovement[0]=0;

    ballpositionx[1]=(x/2)+100;
    ballpositiony[1]=(y/2);
    angleofmovement[1]=0;

    ballpositionx[2]=(x/2);
    ballpositiony[2]=(y/2)-60;
    angleofmovement[2]=0;

    ballpositionx[3]=(x/2);
    ballpositiony[3]=(y/2)+60;
    angleofmovement[3]=0;

    ballpositionx[4]=(x/2)-100;
    ballpositiony[4]=(y/2)-100;
    angleofmovement[4]=0;

    ballpositionx[5]=(x/2)-100;
    ballpositiony[5]=(y/2);
    angleofmovement[5]=0;

    ballpositionx[6]=(x/2)-100;
    ballpositiony[6]=(y/2)+100;
    angleofmovement[6]=0;

    ballpositionx[7]=(x/2)-200;
    ballpositiony[7]=(y/2)-50;
    angleofmovement[7]=0;

    ballpositionx[8]=(x/2)-200;
    ballpositiony[8]=(y/2)+50;
    angleofmovement[8]=0;

    int ballselection=0;

    ///Boundary
    cleardevice();
    board();

    ///ball and line print in main screen
    setcolor(7);
    line(ballpositionx[ballselection]+32*cos(angleofmovement[ballselection]),ballpositiony[ballselection]-32*sin(angleofmovement[ballselection]),ballpositionx[ballselection]+(32+d)*cos(angleofmovement[ballselection]),ballpositiony[ballselection]-(32+d)*sin(angleofmovement[ballselection]));
    setcolor(0);
    for(int i=0; i<9; i++)
    {
        setfillstyle(1,color[i]);
        fillellipse(ballpositionx[i],ballpositiony[i],30,30);
    }

    char i;
    for(a='g'; a!=' ';)
    {
       clrall=1;
       for(i=0;i<9;i++)
       {
        if(cursorstatus[i]==ACTIVE)
        clrall=0;
       }
       if(clrall==1)
       goto scoremenu;
        board();
        setcolor(0);
        for(int i=0; i<9; i++)
        {
            setfillstyle(1,color[i]);
            fillellipse(ballpositionx[i],ballpositiony[i],30,30);
        }
        setfillstyle(1,color[ballselection]);
        fillellipse(ballpositionx[ballselection],ballpositiony[ballselection],30,30);

        for(a='g'; ((a!='5')&&(a!=' '));)
        {
            fflush(stdin);
            settextjustify(1,2);
            ///checking cursor status
            if(cursorstatus[ballselection]==DEACTIVE)
            ballselection=0;

            ///printing the strike
            setcolor(7);
            line(ballpositionx[ballselection]+32*cos(angleofmovement[ballselection]),ballpositiony[ballselection]-32*sin(angleofmovement[ballselection]),ballpositionx[ballselection]+(32+d)*cos(angleofmovement[ballselection]),ballpositiony[ballselection]-(32+d)*sin(angleofmovement[ballselection]));


            ///strike rotation

            i=kbhit();
            if(timer)
            {
            time(&timer2);
            s2 = difftime(timer2,timer1);
            if(s2>=1)
            {
            timer1=timer2;
            s1=difftime(timer2,timer);
            sprintf(msg,"TIME LEFT= %.f",lefttime-s1);
            sprintf(scoreprint,"YOUR SCORE= %d",score);
            sprintf(msg2,"%s                                                              %s",msg,scoreprint);
            setcolor(BLUE);
            //outtextxy(x+100,y+15,msg);
            //outtextxy(x-400,y+15,scoreprint);
            outtextxy(x/2,y+15,msg2);
            if(s1==lefttime)
            goto scoremenu;
            }
            }
            if (i!=0)
            {
                a=getch();
            }

            if ((a=='7')||(a=='9')||(a=='4')||(a=='6')||(a=='8')||(a=='2')||(a=='r'))
            {
                setcolor(GREEN);
                line(ballpositionx[ballselection]+32*cos(angleofmovement[ballselection]),ballpositiony[ballselection]-32*sin(angleofmovement[ballselection]),ballpositionx[ballselection]+(32+d)*cos(angleofmovement[ballselection]),ballpositiony[ballselection]-(32+d)*sin(angleofmovement[ballselection]));
                if (a=='7')
                {
                    if(ballselection==0)
                        ballselection=8;
                    else
                        ballselection--;
                    if(cursorstatus[ballselection]==DEACTIVE)
                    {
                        while(cursorstatus[ballselection]==DEACTIVE)
                        {
                            if(ballselection==0)
                                ballselection=8;
                            else
                                ballselection--;
                        }
                    }
                }
                if (a=='9')
                {


                    if(ballselection==8)
                        ballselection=0;
                    else
                        ballselection++;
                    if(cursorstatus[ballselection]==DEACTIVE)
                    {
                        while(cursorstatus[ballselection]==DEACTIVE)
                        {

                            if(ballselection==8)
                                ballselection=0;
                            else
                                ballselection++;
                        }
                    }
                }
                if (a=='6')
                {
                    angleofmovement[ballselection]=angleofmovement[ballselection]+0.05;
                }
                if (a=='4')
                {
                    angleofmovement[ballselection]=angleofmovement[ballselection]-0.05;
                }
                if (a=='8')
                {
                    d=d+2;
                }
                if (a=='2')
                {
                    d=d-2;
                }
                if (d<=0)d=1;
                if (d>=300)d=300;

                ///reseting the board
                if (a=='r')
                {
                    reset1:
                    timer=NULL;
                    score=0;
                    cleardevice();
                    board();
                    ballselection=0;
                    for(int p=0; p<9; p++)
                    {
                        cursorstatus[p]=ACTIVE;
                    }
                        ballpositionx[0]=(x/2)+300;
                        ballpositiony[0]=y/2;
                        angleofmovement[0]=0;

                        ballpositionx[1]=(x/2)+100;
                        ballpositiony[1]=(y/2);
                        angleofmovement[1]=0;

                        ballpositionx[2]=(x/2);
                        ballpositiony[2]=(y/2)-60;
                        angleofmovement[2]=0;

                        ballpositionx[3]=(x/2);
                        ballpositiony[3]=(y/2)+60;
                        angleofmovement[3]=0;

                        ballpositionx[4]=(x/2)-100;
                        ballpositiony[4]=(y/2)-100;
                        angleofmovement[4]=0;

                        ballpositionx[5]=(x/2)-100;
                        ballpositiony[5]=(y/2);
                        angleofmovement[5]=0;

                        ballpositionx[6]=(x/2)-100;
                        ballpositiony[6]=(y/2)+100;
                        angleofmovement[6]=0;

                        ballpositionx[7]=(x/2)-200;
                        ballpositiony[7]=(y/2)-50;
                        angleofmovement[7]=0;

                        ballpositionx[8]=(x/2)-200;
                        ballpositiony[8]=(y/2)+50;
                        angleofmovement[8]=0;

                }
                a='g';


                ///ball
                setcolor(0);
                for(int i=0; i<9; i++)
                {
                    setfillstyle(1,color[i]);
                    fillellipse(ballpositionx[i],ballpositiony[i],30,30);
                }
                setfillstyle(1,color[ballselection]);
                fillellipse(ballpositionx[ballselection],ballpositiony[ballselection],30,30);
                setcolor(7);
                line(ballpositionx[ballselection]+32*cos(angleofmovement[ballselection]),ballpositiony[ballselection]-32*sin(angleofmovement[ballselection]),ballpositionx[ballselection]+(32+d)*cos(angleofmovement[ballselection]),ballpositiony[ballselection]-(32+d)*sin(angleofmovement[ballselection]));

            }
            if(a==' ')
                return 0;
        }
        ///clear the initial ball after changing striker
        setcolor(GREEN);
        line(ballpositionx[ballselection]+32*cos(angleofmovement[ballselection]),ballpositiony[ballselection]-32*sin(angleofmovement[ballselection]),ballpositionx[ballselection]+(32+d)*cos(angleofmovement[ballselection]),ballpositiony[ballselection]-(32+d)*sin(angleofmovement[ballselection]));
        setfillstyle(1,GREEN);
        fillellipse(ballpositionx[ballselection],ballpositiony[ballselection],30,30);

        ///converting speeed and angle to its component vector
        velocity[ballselection]=d;
        angleofmovement[ballselection]=angleofmovement[ballselection]+3.1416;
        vcomponentx[ballselection]=velocity[ballselection]*cos(angleofmovement[ballselection]);
        vcomponenty[ballselection]=velocity[ballselection]*sin(angleofmovement[ballselection]);
        deadtime=0.3;
        deadtimedecrease=-0.0001;
        rp=0;
        if(!timer){
        score=0;
        time(&timer);
        time(&timer1);
        }
        overlap=0;
        while(velocity[ballselection]>=0.05&&(deadtime!=0))
        {
            time(&timer2);
            s2 = difftime(timer2,timer1);
            if(s2>=1)
            {
            timer1=timer2;
            s1=difftime(timer2,timer);
            sprintf(msg,"TIME LEFT= %.f",lefttime-s1);
            sprintf(scoreprint,"YOUR SCORE= %d",score);
            sprintf(msg2,"%s                                                              %s",msg,scoreprint);
            setcolor(BLUE);

            outtextxy(x/2,y+15,msg2);
            if(s1==lefttime)
            goto scoremenu;
            }

            ///erasing ball after strike each instance
            setcolor(GREEN);
            setfillstyle(1,GREEN);
            fillellipse(ballpositionx[ballselection],ballpositiony[ballselection],30,30);

            ///new coordinates of ball[ballselection]
            ballpositionx[ballselection]=ballpositionx[ballselection]+vcomponentx[ballselection]*deadtime;
            ballpositiony[ballselection]=ballpositiony[ballselection]-vcomponenty[ballselection]*deadtime;
            if(deadtime>0)
            {
                deadtime=deadtime+deadtimedecrease;
                deadtimedecrease=deadtimedecrease-0.0001;
            }
            if(deadtime<0)deadtime=0;

            ///bouncing ball start
            if ((ballpositionx[ballselection]<34)||(ballpositionx[ballselection]>x-34))
            {   overlap=0;
                if (ballpositionx[ballselection]<34)
                {
                    ballpositionx[ballselection]=35;
                }
                if (ballpositionx[ballselection]>x-34)
                {
                    ballpositionx[ballselection]=x-35;
                }
                vcomponentx[ballselection]=-vcomponentx[ballselection]*0.8;
                velocity[ballselection]=sqrt((vcomponentx[ballselection]*vcomponentx[ballselection])+(vcomponenty[ballselection]*vcomponenty[ballselection]));
                angleofmovement[ballselection]=fabs(atan(vcomponenty[ballselection]/vcomponentx[ballselection]));
                if (vcomponenty[ballselection]<34)
                {
                    angleofmovement[ballselection]=-angleofmovement[ballselection];
                }
                if (vcomponentx[ballselection]<34)
                {
                    angleofmovement[ballselection]=3.1416-angleofmovement[ballselection];
                }
            }
            if ((ballpositiony[ballselection]<34)||(ballpositiony[ballselection]>y-34))
            {overlap=0;
                if (ballpositiony[ballselection]<34)
                {
                    ballpositiony[ballselection]=35;
                }
                if (ballpositiony[ballselection]>y-34)
                {
                    ballpositiony[ballselection]=y-35;
                }
                vcomponenty[ballselection]=-vcomponenty[ballselection]*0.8;
                velocity[ballselection]=sqrt((vcomponentx[ballselection]*vcomponentx[ballselection])+(vcomponenty[ballselection]*vcomponenty[ballselection]));
                angleofmovement[ballselection]=fabs(atan(vcomponenty[ballselection]/vcomponentx[ballselection]));
                if (vcomponenty[ballselection]<34)
                {
                    angleofmovement[ballselection]=-angleofmovement[ballselection];
                }
                if (vcomponentx[ballselection]<34)
                {
                    angleofmovement[ballselection]=3.1416-angleofmovement[ballselection];
                }
            }
            ///bouncing ball stop


            ///decreasing of velocity due to friction
            velocity[ballselection]=velocity[ballselection]-friction;
            /// ball printer
            setcolor(0);
            for(int i=0; i<9; i++)
            {
                setfillstyle(1,color[i]);
                fillellipse(ballpositionx[i],ballpositiony[i],30,30);
            }
            setfillstyle(1,color[ballselection]);
            fillellipse(ballpositionx[ballselection],ballpositiony[ballselection],30,30);

            Sleep(30);

            /// board reprinter
            if(ballpositionx[ballselection]<75&&ballpositiony[ballselection]<75)
            {
                cursorstatus[ballselection]=DEACTIVE;
                setfillstyle(SOLID_FILL,GREEN);
                cleardevice();
                board();
                velocity[ballselection]=0;
                ballpositionx[ballselection]=-2000;
                ballpositiony[ballselection]=-2000;
                outtextxy(x/2,y+15,msg2);
                if(ballselection!=1 && ballselection!=3 && ballselection!=6)
                score=score+10;
                if(ballselection==1 || ballselection==3 || ballselection==6)
                score=score-5;

            }
            else if(ballpositionx[ballselection]<75&&ballpositiony[ballselection]>y-75)
            {
                cursorstatus[ballselection]=DEACTIVE;
                cleardevice();
                board();
                velocity[ballselection]=0;
                ballpositionx[ballselection]=-2000;
                ballpositiony[ballselection]=2000;
                outtextxy(x/2,y+15,msg2);
                if(ballselection!=1 && ballselection!=3 && ballselection!=6)
                score=score+10;
                if(ballselection==1 || ballselection==3 || ballselection==6)
                score=score-5;
            }
            else if(ballpositionx[ballselection]>x-75&&ballpositiony[ballselection]>y-75)
            {
                cleardevice();
                cursorstatus[ballselection]=DEACTIVE;
                board();
                velocity[ballselection]=0;
                ballpositionx[ballselection]=2000;
                ballpositiony[ballselection]=2000;
                if(ballselection!=1 && ballselection!=3 && ballselection!=6)
                score=score+10;
                if(ballselection==1 || ballselection==3 || ballselection==6)
                score=score-5;
                outtextxy(x/2,y+15,msg2);
            }
            else if(ballpositionx[ballselection]>x-75&&ballpositiony[ballselection]<75)
            {
                cleardevice();
                board();
                cursorstatus[ballselection]=DEACTIVE;
                velocity[ballselection]=0;
                ballpositionx[ballselection]=2000;
                ballpositiony[ballselection]=-2000;
                if(ballselection!=1 && ballselection!=3 && ballselection!=6)
                score=score+10;
                if(ballselection==1 || ballselection==3 || ballselection==6)
                score=score-5;
                outtextxy(x/2,y+15,msg2);
            }
            else if(ballpositionx[ballselection]<38||ballpositionx[ballselection]>x-38||ballpositiony[ballselection]<38||ballpositiony[ballselection]>y-38)
            {
                board();
                outtextxy(x/2,y+15,msg2);
            }
            else if(rp>=40)
            {
                board();
                outtextxy(x/2,y+15,msg2);
                rp=0;
            }
            else
                rp++;
         for(overlap1=0;overlap1<9;overlap1++)
         {
            if(overlap1!=ballselection){
            balldistance=sqrt(pow(ballpositionx[ballselection]-ballpositionx[overlap1],2)+pow(ballpositiony[ballselection]-ballpositiony[overlap1],2));
            if(balldistance<50&&overlap==0)
             {
                score=score-5;
                overlap=1;}
                   }

         }

        }
    }
return 0;
scoremenu:
cleardevice();
setfillstyle(SOLID_FILL,BLACK);
bar(0,0,x,y+45);
sprintf(scoreprint,"YOU HAVE SCORED= %d",score);
setcolor(RED);
settextjustify(1,1);
outtextxy(x/2,y/2,scoreprint);
delay(5000);
goto reset1;
return 0;
}
