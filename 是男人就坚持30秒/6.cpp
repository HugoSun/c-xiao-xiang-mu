
//是男人就坚持三十秒
//操作说明
//通过控制小人的移动来躲避障碍物  a 向左移动，d 向右移动
//随着秒数的增加障碍物的移动会越来越快
//坚持30秒游戏胜利，否则游戏失败
/*
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

int hight,width;                //游戏界面的大小     
int people_x,people_y;          //所控制物体的位置坐标
int enemy_x[10];                //障碍物的x坐标
int enemy_y[10];                //障碍物的y坐标
int v1;                         //障碍物放慢的倍数
int bj;                         

void initi();
void show(long);
void withinput();
int withoutinput(long);

void gotoxy(int x,int y);
void HANDLEh();
int main()
{
	HANDLEh();
	long t=time(NULL);
	int o;
	initi();
	while(1)
	{
		show(t);
		o=withoutinput(t);
		if(o==1)
			break;
		withinput();
	}
	return 0;
}

void initi()
{
	hight=25;
	width=114;
	people_x=24;
	people_y=59;
	v1=10;
	for(int i=0;i<=9;i++)
	{
		enemy_x[i]=rand()%22;
		enemy_y[i]=rand()%114;
	}
}
void show(long t)
{
	
	gotoxy(0,0);
	for(int i=1;i<=hight;i++)
	{
		for(int j=1;j<=width;j++)
		{
			if(i==enemy_x[0]&&j==enemy_y[0])
				cout<<"#";
			else if(i==enemy_x[1]&&j==enemy_y[1])
				cout<<"#";
			else if(i==enemy_x[2]&&j==enemy_y[2])
				cout<<"#";
			else if(i==enemy_x[3]&&j==enemy_y[3])
				cout<<"#";
			else if(i==enemy_x[4]&&j==enemy_y[4])
				cout<<"#";
			else if(i==enemy_x[5]&&j==enemy_y[5])
				cout<<"#";
			else if(i==enemy_x[6]&&j==enemy_y[6])
				cout<<"#";
			else if(i==enemy_x[7]&&j==enemy_y[7])
				cout<<"#";
			else if(i==enemy_x[8]&&j==enemy_y[8])
				cout<<"#";
			else if(i==enemy_x[9]&&j==enemy_y[9])
				cout<<"#";
			else if(i==people_x&&j==people_y)
				cout<<"@";
			else 
				cout<<" ";
		}
		cout<<endl;
	}
	cout<<"时间："<<(time(NULL)-t)<<"秒"<<endl;
}

void withinput()
{
	char n;
	if(kbhit())
	{
		n=getch();
		if(n=='w')
			people_x--;
		else if(n=='s')
			people_x++;
		else if(n=='a')
			people_y--;
		else if(n=='d')
			people_y++;
		if(people_x<1)
			people_x++;
		else if(people_x>hight)
			people_x--;
		if(people_y<1)
			people_y++;
		else if(people_y>width)
			people_y--;
	}

}
int withoutinput(long t)
{
	int yy=2;                                        //来标记是否结束游戏
	for(int i=0;i<=9;i++)
	{
		if(enemy_x[i]==people_x&&enemy_y[i]==people_y)
		{
			system("cls");
			cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
			cout<<"                                   GAME OVER！"<<endl;
			cout<<endl;
			cout<<"                                 连30秒都坚持不了!"<<endl;
			yy=1;
			break;
		}
		
	}
	if((time(NULL)-t)==30)
	{
		
		system("cls");
		cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
		cout<<"                                    恭喜你成为30秒真男人!"<<endl;
		yy=1;
	}




	static int speed=0;
	if(time(NULL)-t%8==0&&time(NULL)-t!=0&&v1>1)
	{
		v1=v1-3;
		speed=v1;
	}
	if(speed<v1)
		speed++;
	else if(speed==v1)
	{
	    for(int i=0;i<=9;i++)
		{
			if(enemy_x[i]<people_x)
				enemy_x[i]++;
			else if(enemy_x[i]>people_x)
				enemy_x[i]--;
			if(enemy_y[i]<people_y)
				enemy_y[i]=enemy_y[i]+2;
			else if(enemy_y[i]>people_y)
				enemy_y[i]=enemy_y[i]-2;
		}
		speed=0;
	}




	return yy;

}

void gotoxy(int x,int y)                //清屏函数
{
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(handle,pos);
}
void HANDLEh()                         //隐藏控制台光标
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}
*/


