//����˵��
// w���Ʒɻ������ƶ���s���Ʒɻ������ƶ���a���Ʒɻ������ƶ���d���Ʒɻ������ƶ�,j�����ӵ�,�ո�Ϊ����
//����ÿ����4�ٶ�����һ�㵱�����ﵽ16ʱ�л��ٶȴﵽ����
//�ɻ���5��Ѫ����Ѫ��Ϊ����Ϸ����
//�ɻ���15�����У���ȫ����


#include <iostream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
using namespace std;
int bullet_x,bullet_y;      //�ӵ�λ��;
int position_x,position_y;  //�ɻ�λ��
int dj_x,dj_y;              //�л�λ�� 
int hight,width;            //��Ϸ����ĸߺͿ�
int fraction;               //��Ϸ����
int blood;                  //�ɻ�Ѫ��
int v1;                     //�л��ٶȷ�������
int bj;                     //�����ж�ÿ��������л��ٶȺ�л������Ƿ�����
int big_move;               //���б�Ǳ���������ֵΪ1ʱ˵�������˴���������ظ��£�
int b_move_num;             //������Ŀ
void initi();
void show();
void withinput();
int withoutinput();
void gotoxy(int x,int y);
int main()
{



	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬

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
void show()                      //��ӡͼ��
{
	gotoxy(0,0);                 //��������
	if(position_x<1)             //�ѷɻ����ƶ���������Ϸ������
		position_x++;
	else if(position_x>hight)
		position_x--;
	if(position_y<0)
		position_y=position_y+2;
	else if(position_y>width)
		position_y=position_y-2;
	for(int i=1;i<=hight;i++)    //�ֱ��ӡ��Ϸ�����ϵ�ûһ��,
	{
		for(int j=1;j<=width;j++)
		{
			if(big_move==0||b_move_num==0)        //��������Ŀ�������û�з�������ʱ������ӡ
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
				else if(i==bullet_x&&j==bullet_y) //��ʾ�ӵ�
					cout<<"|";
				else if(i==dj_x&&j==dj_y)          //��ʾ�л�
					cout<<"#";
				else
					cout<<" ";                    //��ʾ�ո�
			}
			else if(big_move==1&&b_move_num>0)    //��������Ŀ������ʱ��������
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
	cout<<endl<<setw(20)<<"�÷�Ϊ��"<<fraction<<setw(20)<<"Ѫ��Ϊ��"<<blood<<setw(20)<<"������Ŀ:"<<b_move_num;
}

int withoutinput()                //�������޹صĸ��£�������ӵ����ƶ����л����ƶ������ӵ����ел���ĸ��£�
{
	
	if(((dj_x==bullet_x||dj_x==bullet_x-1)&&dj_y==bullet_y)||(big_move==1&&b_move_num>0))     //���ӵ��͵л�������һ���ǶԶ��߽��и���(�������ӵ������򵽵л�ʱ)
	{                                                          //������ж��ӵ��ڵл�ǰ�������л����ӵ�ͬʱ�ƶ��Ͳ��������
		bullet_x=0;
		dj_x=1;
		dj_y=rand()*2%114;
		fraction++;
		bj=0;
		big_move=0;
	}


	if(bullet_x>=1)              //���ӵ�����Ϸ���涥����ֹͣ�ƶ����ӵ���֮��ʧ
		bullet_x=bullet_x-1;


	


	static int speed=0;    //���þ�̬�����õл��ٶȷ���n��
	if(fraction%5==0&&fraction!=0&&v1>4&&bj==0)//����ÿ����5���л����ٶȾ�����
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
	if(dj_x==position_x&&dj_y==position_y)  //���л���ս������һ��ʱѪ����һ
	{
		blood--;                            //��֮�ҵл�λ�ø���
		dj_x=1;
		dj_y=rand()*2%114;
	}
	if(blood==0)                            //��Ѫ����ֵΪ0ʱ������1ʹ�������
		return 1;
	else
		return 0;
}


void withinput()             //�������йصĲ������ɻ����ƶ����ӵ��ķ���λ�ã�
{
	char n;
	if(kbhit())                  //������ʱ��ִ��
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
void gotoxy(int x,int y)                //��������
{
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(handle,pos);
}
