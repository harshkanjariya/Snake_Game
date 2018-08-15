#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<windows.h>
void gotoxy(int x,int y)
{
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
static int gmovr,f,mscr,levno=1;
struct cord
{
   int x;
   int y;
}hd,fd;
struct cord t[3072];
void headr(int,int);
void headl(int,int);
void headu(int,int);
void headd(int,int);
void food();
void gameover();

int main()
{
 	int gd=0,gm,i;
 	char arr[20],lev[10];
 	char mn=72,ch=77;
 	int b,x=200,y=250,paus=0;
 	{
 		FILE *fp;
 		fp=fopen("snake.dat","r");
		if(fp!=NULL)
		{
			fgets(lev,6,fp);
			fscanf(fp,"%d",&levno);
			fscanf(fp,"%d",&mscr);
		}
		else
		{
			fp=fopen("snake.dat","w");
			mscr=0;
			levno=1;
		}
		fclose(fp);
	}
	initgraph(&gd,&gm,"");
 	hd.x=100;
 	hd.y=100;
 	f=2;
 	fd.x=(9999+rand())%640;
 	fd.y=(10003+rand())%480;
 	while(1)
 	{
 		setfillstyle(1,15);
 		circle(200,200,10);
		circle(200,250,10);
		circle(200,300,10);
		circle(200,350,10);
		settextstyle(3,0,5);
		outtextxy(200,110,"SNAKE");
		settextstyle(1,0,2);
		outtextxy(250,190,"start game");
		outtextxy(250,240,"instructions");
		outtextxy(250,290,"about");
		outtextxy(250,340,"exit");
		if(mn==80 && y==300)y=350;
		else if(mn==80 && y==250)y=300;
		else if(mn==80 && y==200)y=250;
		else if(mn==80 && y==350)y=200;
		if(mn==72 && y==200)y=350;
		else if(mn==72 && y==250)y=200;
		else if(mn==72 && y==300)y=250;
		else if(mn==72 && y==350)y=300;
		setcolor(15);
		floodfill(x,y,15);
		if(mn==13 && y==300)
		{
			int i=480;
			cleardevice();
			while(!kbhit())
			{
				setcolor(0);
				outtextxy(250,i,"Snake Game");
				outtextxy(275,i+30,"Made By");
				outtextxy(220,i+60,"Harsh Kanjariya");
				i--;
				setcolor(15);
				outtextxy(250,i,"Snake Game");
				outtextxy(275,i+30,"Made By");
				outtextxy(220,i+60,"Harsh Kanjariya");
				delay(50);
			}
			ch=getch();
			if(i<=10 && ch==96)
			{
				cleardevice();
				outtextxy(50,200,"Contact:7802004735");
				outtextxy(50,230,"Email:harshgkanjariya2468@gmail.com");
				getch();
				ch=77;
			}
		}
		if(mn==13 && y==250)
		{
			cleardevice();
			settextstyle(1,0,2);
			rectangle(90,100,550,200);
			outtextxy(100,110,"use arrow keys to move snake");
			outtextxy(105,160,"press space to pause game");
			sprintf(arr,"Max score: %d",mscr);
			outtextxy(110,210,arr);
			mn=getch();
			y=200;
		}
		if(mn==13 && y==350)
		exit(0);
		mn=getch();
		if(mn==13 && y==200)
		{
			mn=20; 
			cleardevice();
			sprintf(arr,"Level %d",levno);
			outtextxy(260,210,arr); 
			delay(2000); 
			cleardevice();
			ch=77;
		}
		while(mn==20)
		{
			if(b==1 && ch==80)ch=72;
			if(b==2 && ch==72)ch=80;
			if(b==3 && ch==75)ch=77;
			if(b==4 && ch==77)ch=75;
			switch(ch)
			{
				case 72:while(!kbhit())
						{
							for(i=f;i>0;i--)
							{
								t[i].x=t[i-1].x;
								t[i].y=t[i-1].y;
							}
							t[0].x=hd.x;
							t[0].y=hd.y;
							hd.y-=10;
							gameover();
							if(gmovr==1)break;
							food();
							setfillstyle(1,0);
							bar(t[f].x,t[f].y,t[f].x+10,t[f].y+10);
							setfillstyle(1,15);
							for(i=0;i<f;i++)
								bar(t[i].x,t[i].y,t[i].x+10,t[i].y+10);
							bar(hd.x,hd.y+5,hd.x+10,hd.y+10);
							headu(hd.x+5,hd.y+5);
							delay(100);
						}
						b=1;
						if(gmovr==1)b=5;
						break;
				case 80:while(!kbhit())
						{
							for(i=f;i>0;i--)
							{
								t[i].x=t[i-1].x;
								t[i].y=t[i-1].y;
							}
							t[0].x=hd.x;
							t[0].y=hd.y;
							hd.y+=10;
							gameover();
							if(gmovr==1)break;
							food();
							setfillstyle(1,0);
							bar(t[f].x,t[f].y,t[f].x+10,t[f].y+10);
							setfillstyle(1,15);
							for(i=0;i<f;i++)
								bar(t[i].x,t[i].y,t[i].x+10,t[i].y+10);
							bar(hd.x,hd.y,hd.x+10,hd.y+5);
							headd(hd.x+5,hd.y+5);
							delay(100);
						}	
						b=2;
						if(gmovr==1)b=5;
						break;
				case 77:while(!kbhit())
						{
							for(i=f;i>0;i--)
							{
								t[i].x=t[i-1].x;
								t[i].y=t[i-1].y;
							}
							t[0].x=hd.x;
							t[0].y=hd.y;
							hd.x+=10;
							gameover();
							if(gmovr==1)break;
							food();
							setfillstyle(1,0);
							bar(t[f].x,t[f].y,t[f].x+10,t[f].y+10);
							setfillstyle(1,15);
							for(i=0;i<f;i++)
								bar(t[i].x,t[i].y,t[i].x+10,t[i].y+10);
							bar(hd.x,hd.y,hd.x+5,hd.y+10);
							headr(hd.x+5,hd.y+5);
							delay(100);
						}
						b=3;
						if(gmovr==1)b=5;
						break;
				case 75:while(!kbhit())
						{
							for(i=f;i>0;i--)
							{
								t[i].x=t[i-1].x;
								t[i].y=t[i-1].y;
							}
							t[0].x=hd.x;
							t[0].y=hd.y;
							hd.x-=10;
							gameover();
							if(gmovr==1)break;
							food();
							setfillstyle(1,0);
							bar(t[f].x,t[f].y,t[f].x+10,t[f].y+10);
							setfillstyle(1,15);
							for(i=0;i<f;i++)
								bar(t[i].x,t[i].y,t[i].x+10,t[i].y+10);
							bar(hd.x+5,hd.y,hd.x+10,hd.y+10);
							headl(hd.x+5,hd.y+5);
							delay(100);
						}	
						b=4;
						if(gmovr==1)b=5;
						break;
				default:paus=1;
			}
			rand();
			if(b==5)break;
			if(paus==0)
				ch=getch();
			else
			{
				paus=0;
				if(b==1)ch=72;
				if(b==2)ch=80;
				if(b==3)ch=77;
				if(b==4)ch=75;
			}
		}
		if(b==5)
		{
			cleardevice();
			outtextxy(200,175,"GAME OVER!");
			sprintf(arr,"score: %d",f-2);
			outtextxy(200,195,arr);
			if(f-2>mscr)
			{
				mscr=f-2;
				if(f-2>100)levno++;
 				FILE *fp;
 				fp=fopen("snake.dat","w");
				fprintf(fp,"Level %d %d",levno,f-2);
				fclose(fp);
			}
			sprintf(arr,"All time best score: %d",mscr);
			outtextxy(200,215,arr);
			outtextxy(200,250,"Press ESC To Main Menu");
			b=0;
			upar:
			mn=getch();
			if(mn!=27)goto upar;
			mn=72;
			f=2;
			y=250;
			gmovr=0;
			ch=77;
			hd.x=100;
			hd.y=100;
			fd.x=(10000+(rand()*hd.y))%630;
			fd.y=(10000+(rand()*hd.x))%470;
		}
		cleardevice();
 	}
}
void gameover()
{
  	int i;
  	for(i=f;i>=0;i--)
  	{
  		if((hd.x<t[i].x+5 && hd.x+5>t[i].x && hd.y<t[i].y+5 && hd.y+5>t[i].y) || hd.x<0 || hd.y<0 || hd.x>620 || hd.y>460)
   		{gmovr=1;}
  	}	
}

void food()
{
  	if(hd.x<fd.x+5 && hd.x+5>fd.x && hd.y<fd.y+5 && hd.y+5>fd.y)
  	{
  		setfillstyle(1,0);
  		bar(fd.x,fd.y,fd.x+10,fd.y+10);
  		do
  		{
  			fd.x=(rand()+100000)*10%630;
  			fd.y=(rand()+100000)*10%470;
  		}while(fd.x<0 || fd.y<0 || fd.x>620 || fd.y>460);
  		f++;
  	}
  	setfillstyle(1,15);
  	bar(fd.x,fd.y,fd.x+10,fd.y+10);
}

void headr(int x,int y)
{
	circle(x,y,5);
	floodfill(x,y,15);
	setfillstyle(1,0);
	bar(x,y-3,x+2,y-1);
	bar(x,y+1,x+2,y+3);
}

void headl(int x,int y)
{
	circle(x,y,5);
	floodfill(x-1,y,15);
	setfillstyle(1,0);
	bar(x-1,y-3,x-3,y-1);
	bar(x-1,y+1,x-3,y+3);
}

void headu(int x,int y)
{
	circle(x,y,5);
	floodfill(x,y-1,15);
	setfillstyle(1,0);
	bar(x-3,y-3,x-1,y-1);
	bar(x+1,y-3,x+3,y-1);
}

void headd(int x,int y)
{
	circle(x,y,5);
	floodfill(x,y+1,15);
	setfillstyle(1,0);
	bar(x-3,y+1,x-1,y+3);
	bar(x+1,y+1,x+3,y+3);
}
