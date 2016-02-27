#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>

char ch;
int maxx, maxy, gridx, gridy, x, y, st=120, end=60;
int gd=DETECT, gm;
int score, rep=0, death, dir;
int map[20][19];
float offset;

void kill();

void initialize()
{
	int i, j;
	int m[20][19]={
{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
{0,1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,1,0},
{0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0},
{0,0,0,0,1,0,0,0,2,0,2,0,0,0,1,0,0,0,0},
{0,1,1,1,1,0,2,2,2,2,2,2,2,0,1,1,1,1,0},
{0,1,0,0,1,0,2,0,0,2,0,0,2,0,1,0,0,1,0},
{0,1,1,1,1,0,2,0,2,2,2,0,2,0,1,1,1,1,0},
{0,1,0,0,1,0,2,0,0,0,0,0,2,0,1,0,0,1,0},
{0,1,1,1,1,0,2,2,2,2,2,2,2,0,1,1,1,1,0},
{0,0,0,0,1,0,2,0,0,0,0,0,2,0,1,0,0,0,0},
{0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0},
{0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1,0},
{0,1,1,0,1,1,1,1,1,2,1,1,1,1,1,0,1,1,0},
{0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0},
{0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0},
{0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	for (i=0; i<20; i++)
		for (j=0; j<19; j++)
			map[i][j]= m[i][j];
	
	x=9, y=14, score= 0, death=0, dir=0, st=120, end=60;
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	maxx=getmaxx();
	maxy=getmaxy();
	gridx=ceil(maxx/19);
	gridy=ceil(maxy/20);
	offset=(maxx%19)/2;
}

void start()
{
	setcolor(YELLOW);
	setfillstyle(SOLID_FILL, YELLOW);
	sector(maxx/2, maxy/2-50, 330, 30, 20, 20);
	outtextxy(maxx/2-25, maxy/2, "PacMan");
	outtextxy(maxx/2-84, maxy-50, "Press any key to start");
	getch();
	cleardevice();
	outtextxy(maxx/2-42, 120, "INSTRUCTIONS");
	outtextxy(maxx/2-130, 180, "Your aim is to eat all the pellets");
	outtextxy(maxx/2-120, 220, "But be careful! You must avoid");
	outtextxy(maxx/2-123, 240, "the ghosts trying to catch you!");
	outtextxy(maxx/2-86, 320, "Use WASD to change directions");
	outtextxy(maxx/2-96, maxy-50, "Press any key to continue");
	getch();	
}

void slice(int x, int y, int sangle, int eangle, int rad)
	{
	int i,j;
	if(sangle>eangle){
	circle(x,y,rad);
	floodfill(x,y,YELLOW);
	setcolor(getbkcolor());
	setfillstyle(SOLID_FILL,getbkcolor());
	pieslice(x,y,eangle,sangle,rad);
	setcolor(YELLOW);
	}
	else{
	setfillstyle(SOLID_FILL, YELLOW);
	sector(x,y,sangle,eangle,rad,rad);
	}
	}
	
void show()
{
	int i,j;
	clrscr();
	cleardevice();
	for (i=0; i<20; i++)
	{	for (j=0; j<19; j++)
		{
		switch(map[i][j])
		{
		case 0:
		setfillstyle(SOLID_FILL, BLUE);
		bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
		break;
		case 1:
		setcolor(WHITE);
		circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 2);
		break;
		case 2:
		setfillstyle(SOLID_FILL, BLACK);
		bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
		break;
		}
	}
	}
	setfillstyle(SOLID_FILL, YELLOW);
	setcolor(YELLOW);
	slice(gridx*x+gridx/2+offset, gridy*y+gridy/2, st, end, gridy/2-2);
	printf("\t\t\t\tPress Esc to Pause\t\t\t\t", score);
}

void update(int l, int m)
{
	int i,j;
	for (i=(m-1); i<=(m+1); i++)
	{	for (j=(l-1); j<=(l+1); j++)
		{
		switch(map[i][j])
		{
		case 1:
		setcolor(WHITE);
		circle(j*gridx+gridx/2+offset, i*gridy+gridy/2, 2);
		break;
		case 2:
		setfillstyle(SOLID_FILL, BLACK);
		bar(j*gridx+1+offset, i*gridy+1, (j+1)*gridx+offset, (i+1)*gridy);
		break;
		}
	}
	}
	setfillstyle(SOLID_FILL, YELLOW);
	setcolor(YELLOW);
	slice(gridx*x+gridx/2+offset, gridy*y+gridy/2, st, end, gridy/2-2);
}

void main()
{
	char c, c_old;
	initialize();
	if (rep==0)
		start();
	show();
	delay(500);
	while(1)
	{
	delay(250);
	while (kbhit())
	{	
		c= getch();
		if (c=='w'||c=='W')
		{
			dir=0;			
		}
		else if (c=='s'||c=='S')
		{
			dir=1;
		}
		else if (c=='a'||c=='A')
		{
			dir=2;
		}
		else if (c=='d'||c=='D')
		{
			dir=3;
		}
		else if (c==27)
			kill();
		else if (c=='~') /*test key for debug*/
			score=149;
		else if (c=='!') /*test key for debug*/
			death=1;
		
	}
	if (dir==0)
		{
			if (map[y-1][x]==1)
			{
				y--;
				map[y][x]=2;
				score++;
			}
			else if (map[y-1][x]==2)
			{
				y--;
			}
			st=120, end=60;
		}
		else if (dir==1)
		{
			if (map[y+1][x]==1)
			{
				y++;
				map[y][x]=2;
				score++;
			}
			else if (map[y+1][x]==2)
			{
				y++;
			}
			st=300, end=240;
		}
		else if (dir==2)
		{
			if (map[y][x-1]==1)
			{
				x--;
				map[y][x]=2;
				score++;
			}
			else if (map[y][x-1]==2)
			{
				x--;
			}
			st=210, end=150;
		}
		else if (dir==3)
		{
			if (map[y][x+1]==1)
			{
				x++;
				map[y][x]=2;
				score++;
			}
			else if (map[y][x+1]==2)
			{
				x++;
			}
			st=30, end=330;
		}
		update(x,y);
		if (score==150)
		{
			delay(500);
			kill();
		}
	}
}

void kill()
{
	clrscr();
	cleardevice();
	if (score==150)
	{
		outtextxy(maxx/2-40, maxy/2-50, "YOU WIN!");
		outtextxy(maxx/2-180, maxy-50, "(Press Spacebar to play again, Esc to exit)");
	}
	else if (death==1)
	{
		outtextxy(maxx/2-46, maxy/2-50, "GAME OVER!");
		outtextxy(maxx/2-190, maxy-50, "(Press Spacebar to start new game, Esc to exit)");
		printf(" Your score: %3d", score);
	}
	else
	{
		outtextxy(maxx/2-46, maxy/2-50, "GAME PAUSED");
		outtextxy(maxx/2-240, maxy-50, "(Press P to resume, Spacebar to start new game, Esc to exit)");
		printf(" Your score: %3d", score);
	}
	delay(750);
	while(1)
	{	ch=getch();
		if (ch==' ')
		{
			rep=1;
			main();
		}
		else if (ch==27) 
			exit(1);
		else if (ch=='p'||ch=='P')
			break;
	}
}