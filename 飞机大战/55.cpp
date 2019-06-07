//操作说明
// w控制飞机向上移动，s控制飞机向下移动，a控制飞机向左移动，d控制飞机向右移动,j发射子弹,空格为觉醒
//分数每增加4速度提升一点当分数达到16时敌机速度达到极限
//飞机有5点血量，血量为零游戏结束
//飞机有15个大招，（全屏）


#include <iostream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
using namespace std;
int bullet_x,bullet_y;      //子弹位置;
int position_x,position_y;  //飞机位置
int dj_x,dj_y;              //敌机位置 
int hight,width;            //游戏画面的高和宽
int fraction;               //游戏分数
int blood;                  //飞机血量
int v1;                     //敌机速度放慢倍数
int bj;                     //用来判断每次增加完敌机速度后敌机分数是否提升
int big_move;               //大招标记变量（当其值为1时说明发动了大招做出相关更新）
int b_move_num;             //大招数目
void initi();
void show();
void withinput();
int withoutinput();
void gotoxy(int x,int y);
int main()
{



	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态

	initi();
	while(1)
	{
		show();
		int mm=withoutinput();
		if(mm==1)
		{
			show();
			cout<<endl<<setw(15)<<"GAME OVER!"<<endl;
			break;
		}
		withinput();
	}
	return 0;
}
void initi()
{
	hight=25;
	width=114;
	position_x=23;
	position_y=50;
	
	dj_x=1;
	dj_y=rand()*2%114;
	bullet_y=position_y;
	fraction=0;
	blood=5;
	v1=15;
	big_move=0;
	b_move_num=15;
}
void show()                      //打印图像
{
	gotoxy(0,0);                 //进行清屏
	if(position_x<1)             //把飞机的移动控制在游戏界面内
		position_x++;
	else if(position_x>hight)
		position_x--;
	if(position_y<0)
		position_y=position_y+2;
	else if(position_y>width)
		position_y=position_y-2;
	for(int i=1;i<=hight;i++)    //分别打印游戏界面上的没一点,
	{
		for(int j=1;j<=width;j++)
		{
			if(big_move==0||b_move_num==0)        //当觉醒数目等于零或没有发动觉醒时正常打印
			{
				if(((i==position_x&&j==position_y)||(i==position_x+1&&j>=position_y-2&&j<=position_y+2)||(i==position_x+2&&(j==position_y-1||j==position_y+1)))&&fraction>10) 
					cout<<"*";
				else if((i==position_x&&j==position_y)&&fraction<=10)
					cout<<"*";
				/*
				else if(i==position_x+1&&j>=position_y-2&&j<=position_y+2)
					cout<<"*";
				else if(i==position_x+2&&(j==position_y-1||j==position_y+1))
					cout<<"*";
					*/
				else if(i==bullet_x&&j==bullet_y) //显示子弹
					cout<<"|";
				else if(i==dj_x&&j==dj_y)          //显示敌机
					cout<<"#";
				else
					cout<<" ";                    //显示空格
			}
			else if(big_move==1&&b_move_num>0)    //当觉醒数目大于零时触动技能
			{
				if(i==position_x&&j==position_y)
					cout<<"*";
				else
					cout<<"@";
			}
		}
		cout<<endl;                           
	}
	for(int i=1;i<=114;i++)
		cout<<"-";
	cout<<endl<<setw(20)<<"得分为："<<fraction<<setw(20)<<"血量为："<<blood<<setw(20)<<"觉醒数目:"<<b_move_num;
}

int withoutinput()                //与输入无关的更新（发射后子弹的移动，敌机的移动，当子弹射中敌机后的更新）
{
	
	if(((dj_x==bullet_x||dj_x==bullet_x-1)&&dj_y==bullet_y)||(big_move==1&&b_move_num>0))     //当子弹和敌机的坐标一样是对二者进行更新(或者是子弹即将打到敌机时)
	{                                                          //如果不判断子弹在敌机前的情况则敌机与子弹同时移动就不会更新了
		bullet_x=0;
		dj_x=1;
		dj_y=rand()*2%114;
		fraction++;
		bj=0;
		big_move=0;
	}


	if(bullet_x>=1)              //当子弹打到游戏界面顶部是停止移动，子弹随之消失
		bullet_x=bullet_x-1;


	


	static int speed=0;    //利用静态变量让敌机速度放慢n倍
	if(fraction%5==0&&fraction!=0&&v1>4&&bj==0)//分数每增加5，敌机的速度就增加
	{
	    bj=1;
		v1=v1-4;
		speed=v1;
	}
	
	if(speed<v1)       
		speed++;
	else if(speed==v1)
	{
	    if(dj_x<hight)
		    dj_x++;
	    else
	    {
		    dj_x=1;
		    dj_y=rand()*2%114;
	    }
		speed=0;
	}
	if(dj_x==position_x&&dj_y==position_y)  //当敌机与战机坐标一样时血量减一
	{
		blood--;                            //随之耙敌机位置更新
		dj_x=1;
		dj_y=rand()*2%114;
	}
	if(blood==0)                            //当血量的值为0时，返回1使程序结束
		return 1;
	else
		return 0;
}


void withinput()             //与输入有关的操作（飞机的移动，子弹的发射位置）
{
	char n;
	if(kbhit())                  //当按键时才执行
	{
		n=getch();
		if(n=='w')
			position_x--;
		else if(n=='s')
			position_x++;
		else if(n=='a')
			position_y=position_y-2;
		else if(n=='d')
			position_y=position_y+2;
		else if(n=='j')
		{
			bullet_y=position_y;
			bullet_x=position_x-1;
		}
		else if(n==' ')
		{
			big_move=1;
			if(b_move_num>0)
				b_move_num--;
		}
	}
}
void gotoxy(int x,int y)                //清屏函数
{
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(handle,pos);
}
