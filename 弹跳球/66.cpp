
//  弹跳球
//操作说明
//游戏难度分为 简单，普通，困难，地狱  四个级别(难度越高挡板越短)
//通过a向左移动  b向右移动
//有5滴血量，有五次小球没接着就会结束游戏,每接一次小球就会加一分，分数每增加5分小球的速度就会增加一点(但不是无限制增加)
/*
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
using namespace std;
int hight,width;        //游戏画面的高和宽
int guard_x;            //挡板的x坐标
int guard_y_left;       //挡板的左边界
int guard_y_right;      //挡板的右边界
int fraction;           //游戏得分
int blood;              //血量
int vole;               //挡板每次移动的步长

int bj_hilo;            //标记是向下移动还是向上移动
int bj_leri;            //标记是向左移动还是向右移动
int bobble_x;           //小球的x坐标
int bobble_y;           //小球的y坐标
int bjv;                //判断每次增加完小球的速度之后分数是否增加
int v1;                 //小球的放慢倍数


void initi(int);           //初始化参数
void show();            //打印图像
int withoutinput();    //处理与输入无关的的更新
void withinput();       //处理与输入有关的更新
void p_game_over();     //打印游戏结束界面;


void gotoxy(int x,int y); //清屏函数
void HANDLEh();           //隐藏控制台输入光标



int main()
{
	HANDLEh();               //隐藏控制台输入光标
	int h;
	cout<<endl<<endl<<endl<<endl<<endl<<endl;
	cout<<"                                        **********************************"<<endl;
	cout<<"                                        *                                *"<<endl;
	cout<<"                                        *            趣味反弹球          *"<<endl;
	cout<<"                                        *                                *"<<endl;
	cout<<"                                        **********************************"<<endl;
	cout<<"                                        1.简单"<<endl;
	cout<<"                                        2.普通"<<endl;
	cout<<"                                        3.困难"<<endl;
	cout<<"                                        4.地狱"<<endl;
	cout<<"                                        请选择难度：";
	cin>>h;
	initi(h);
	while(1)
	{
		show();
		h=withoutinput();
		if(h==0)
		{
			break;
			p_game_over();
		}
		withinput();
	}
	return 0;
}
void initi(int h)
{
	hight=25;
	width=115;
	guard_x=24;
	guard_y_left=39+h*4;
	guard_y_right=59;
	vole=2;
	fraction=0;
	blood=5;
	v1=8;
	bjv=1;


	bobble_x=1;
	bobble_y=rand()%width;
	bj_hilo=0;         //0为向下移动
	bj_leri=0;         //0为向右移动
}
void show()
{
	gotoxy(0,0);
	for(int i=1;i<=hight;i++)
	{
		for(int j=1;j<=width;j++)
		{
			if(i==guard_x&&j>=guard_y_left&&j<=guard_y_right)
				cout<<"*";
			else if(i==bobble_x&&j==bobble_y)
				cout<<"O";
			else
				cout<<" ";
		}
		cout<<"|"<<endl;
	}
	for(int i=1;i<=width;i++)
		cout<<"-";
	cout<<"|"<<endl<<setw(20)<<"得分:"<<fraction<<setw(20)<<"血量:"<<blood<<endl;
}
int withoutinput()               //与输入无关的更新
{
	static int speed=0;            //使小球的移动速度下降为挡板的四倍 （其意思是执行四次更新才让小球执行一次更新，相当于降低四倍速度）
	
	if(fraction%5==0&&fraction!=0&&bjv==0&&v1>2) //分数每增加5小球速度就提升;
	{
		v1=v1-2;
		bjv=1;
		speed=v1;
	}
	if(speed<v1)
		speed++;
	else if(speed==v1)          
	{
		if(bj_hilo==0)
		{
			if(bobble_x<hight)
				bobble_x++;
			else if(bobble_x==hight)
			{
				bobble_x=1;
				bobble_y=rand()%width;
				bj_hilo=0;
				blood--;
			}
		}
		else if(bj_hilo==1)
		{
			if(bobble_x>1)
				bobble_x--;
			else if(bobble_x==1)
			{
				bj_hilo=0;
				bobble_x++;
			}
		}
		if(bj_leri==1)
		{
			if(bobble_y>=3)
				bobble_y=bobble_y-2;
			else if(bobble_y==1)
			{
				bj_leri=0;
				bobble_y=bobble_y+2;
			}
			else if(bobble_y==2)      //因为小球自生成以后每次y坐标都是两个单位两个单位的移动，有可能其会向左移动到2位置如此应该增加一个判断（bug）
				bobble_y--;
		}
		else if(bj_leri==0)
		{
			if(bobble_y<=width-2)
				bobble_y=bobble_y+2;
			else
			{
				bj_leri=1;
				bobble_y=bobble_y-2;
			}
		}
		speed=0;
	
		if(bobble_x+1==guard_x&&bobble_y>=guard_y_left&&bobble_y<=guard_y_right)
		{
			fraction++;
			bjv=0;
			bj_hilo=1;
		}
		
	}
	return blood;
}



void withinput()                   //与输入有关的更新
{
	char n;
	if(kbhit())
	{
		n=getch();
		if(n=='a')
		{
			guard_y_left=guard_y_left-vole;
			guard_y_right=guard_y_right-vole;
		}
		else if(n=='d')
		{
			guard_y_left=guard_y_left+vole;
		    guard_y_right=guard_y_right+vole;
		}


		if(guard_y_left<1)                     //控制挡板在游戏界面内运动
		{
			guard_y_left=guard_y_left+vole;
			guard_y_right=guard_y_right+vole;
		}
		else if(guard_y_right>width)
		{
			guard_y_left=guard_y_left-2;
			guard_y_right=guard_y_right-2;
		}
	}
}



void p_game_over()
{
	gotoxy(0,0);
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
	cout<<"                              GAME  OVER"<<endl;
	cout<<"                               游戏结束"<<endl;
	cout<<endl<<endl;
	cout<<"                           你的游戏得分为:"<<fraction<<endl;
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


















