
//  ������
//����˵��
//��Ϸ�Ѷȷ�Ϊ �򵥣���ͨ�����ѣ�����  �ĸ�����(�Ѷ�Խ�ߵ���Խ��)
//ͨ��a�����ƶ�  b�����ƶ�
//��5��Ѫ���������С��û���žͻ������Ϸ,ÿ��һ��С��ͻ��һ�֣�����ÿ����5��С����ٶȾͻ�����һ��(����������������)
/*
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
using namespace std;
int hight,width;        //��Ϸ����ĸߺͿ�
int guard_x;            //�����x����
int guard_y_left;       //�������߽�
int guard_y_right;      //������ұ߽�
int fraction;           //��Ϸ�÷�
int blood;              //Ѫ��
int vole;               //����ÿ���ƶ��Ĳ���

int bj_hilo;            //����������ƶ����������ƶ�
int bj_leri;            //����������ƶ����������ƶ�
int bobble_x;           //С���x����
int bobble_y;           //С���y����
int bjv;                //�ж�ÿ��������С����ٶ�֮������Ƿ�����
int v1;                 //С��ķ�������


void initi(int);           //��ʼ������
void show();            //��ӡͼ��
int withoutinput();    //�����������޹صĵĸ���
void withinput();       //�����������йصĸ���
void p_game_over();     //��ӡ��Ϸ��������;


void gotoxy(int x,int y); //��������
void HANDLEh();           //���ؿ���̨������



int main()
{
	HANDLEh();               //���ؿ���̨������
	int h;
	cout<<endl<<endl<<endl<<endl<<endl<<endl;
	cout<<"                                        **********************************"<<endl;
	cout<<"                                        *                                *"<<endl;
	cout<<"                                        *            Ȥζ������          *"<<endl;
	cout<<"                                        *                                *"<<endl;
	cout<<"                                        **********************************"<<endl;
	cout<<"                                        1.��"<<endl;
	cout<<"                                        2.��ͨ"<<endl;
	cout<<"                                        3.����"<<endl;
	cout<<"                                        4.����"<<endl;
	cout<<"                                        ��ѡ���Ѷȣ�";
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
	bj_hilo=0;         //0Ϊ�����ƶ�
	bj_leri=0;         //0Ϊ�����ƶ�
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
	cout<<"|"<<endl<<setw(20)<<"�÷�:"<<fraction<<setw(20)<<"Ѫ��:"<<blood<<endl;
}
int withoutinput()               //�������޹صĸ���
{
	static int speed=0;            //ʹС����ƶ��ٶ��½�Ϊ������ı� ������˼��ִ���Ĵθ��²���С��ִ��һ�θ��£��൱�ڽ����ı��ٶȣ�
	
	if(fraction%5==0&&fraction!=0&&bjv==0&&v1>2) //����ÿ����5С���ٶȾ�����;
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
			else if(bobble_y==2)      //��ΪС���������Ժ�ÿ��y���궼��������λ������λ���ƶ����п�����������ƶ���2λ�����Ӧ������һ���жϣ�bug��
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



void withinput()                   //�������йصĸ���
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


		if(guard_y_left<1)                     //���Ƶ�������Ϸ�������˶�
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
	cout<<"                               ��Ϸ����"<<endl;
	cout<<endl<<endl;
	cout<<"                           �����Ϸ�÷�Ϊ:"<<fraction<<endl;
}




void gotoxy(int x,int y)                //��������
{
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(handle,pos);
}
void HANDLEh()                         //���ؿ���̨���
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
}

*/


















