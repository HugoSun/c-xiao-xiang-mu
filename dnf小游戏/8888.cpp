#include <graphics.h>
#include <Windows.h>
#include <iostream>
#include <conio.h>
#pragma comment(lib, "MSIMG32.LIB")   //�ܵ���TransparentBlt��������͸��ͼƬ�ĵ���
#pragma comment(lib,"Winmm.lib")      //�ܲ�������


int hight,width;                //��Ϸҳ��Ĵ�С
MOUSEMSG mousemsg;               //������꽻��

IMAGE img_background1;           //����1ͼƬ
IMAGE img_initi;                 //��ʼͼƬ
IMAGE img_begin;                 //��ʼͼƬ
IMAGE img_mousemsg;              //���ͼƬ


IMAGE img_people11;              //��������1ͼƬ����(�ƶ��뾲ֹ״̬)
IMAGE img_people12;              //����״̬
IMAGE img_people13;              //��ͨ����״̬
IMAGE img_people14;              //����ն
IMAGE img_people15;              //�߲�����
IMAGE img_people16;              //ͻ��
IMAGE img_people17;              //��Ծ
IMAGE img_people18;              //��ɽն
IMAGE img_people19;              //Ѫɫ����



int people1_x,people1_y;          //����1����Ϸ��������ʾ�ľ�������
int people1_xx,people1_yy;        //����1��ʾ����ͼƬ���������
int people13_xx,people13_yy;        //��ͨ�������������
int gbls;                           //�粼�ֵ���Ŀ

struct gebulin                          //�粼��
{
    IMAGE img_monstre1;             //�粼�ֹ���(����״̬)
	IMAGE img_monstre2;             //�粼������״̬
	int monstre1_x,monstre1_y;       //�粼�ֹ�������Ϸ����ʾ�ľ�������
	int monstre1_xx,monstre1_yy;     //�粼�ֹ�����ʾ����ͼƬ���������;
	int monstre2_xx,monstre2_yy;   //�粼�ֹ�������ʱ��ʾ���������
	int monstre_blood;               //�粼�ֹ����Ѫ��
	int monstre_bj;              //�粼�ֹ���1��Ǳ�����������ǹ�����µ�״̬��0��ֹ���߶�,1���չ�,2���չ���
};


int people1_bj;                  //����1��Ǳ���1������������������ʲô״̬��0��ֹ���߶���1���չ���2���չ���

char technical;                //����ϴ������ü���        

void initi(gebulin gbl[]);
void show(int time,gebulin gbl[]);           //��ʾ����,time��������˼Ϊ��������ʱ��
void withoutinput(gebulin gbl[]);            //�������޹صĸ���
void withinput(gebulin gbl[]);              //�������йصĸ���


void monstre_gbl(gebulin gbl[],int gbl_n);           //�粼�����͵Ĺ����״̬����



int main()
{	

	gebulin  gbl[100];        //����100���粼��                
	initi(gbl);
	initgraph(width,hight);        //������Ϸ�����С

	mciSendString(L"open E:\\dnf\\ϵͳ\\��ʼ.mp3 alias bkmusic",NULL,0,NULL);
	mciSendString(L"play bkmusic repeat",NULL,0,NULL);
	putimage(0,0,&img_initi);
	Sleep(5000);
	
	while(1)
	{
		
		mousemsg=GetMouseMsg();        //��ȡ�����Ϣ,���ı�����ͼ��
	    putimage(0,0,&img_begin);
		TransparentBlt(GetImageHDC(NULL),mousemsg.x-7,mousemsg.y-7,30,30,GetImageHDC(&img_mousemsg),0,0,30,30,RGB(0,0,0));
		if(mousemsg.x>460&&mousemsg.x<660&&mousemsg.y>310&&mousemsg.y<380&&mousemsg.uMsg==WM_LBUTTONDOWN)
		{
			mciSendString(L"close bkmusic",NULL,0,NULL);   //�رտ�ʼ����
			mciSendString(L"open E:\\dnf\\ϵͳ\\����֮��.mp3 alias bkmusic",NULL,0,NULL);   //������֮����������
	        mciSendString(L"play bkmusic repeat",NULL,0,NULL);
			while(1)
			{
				show(70,gbl);
				withoutinput(gbl);
				withinput(gbl);
			}
		}
	}
	getch();


	
	closegraph();
	return 0;
} 
void initi(gebulin gbl[])
{
	width=1200;
	hight=600;
	loadimage(&img_background1,_T("E:\\dnf\\ϵͳ\\����1.jpg")); //������1ͼƬ�������
	loadimage(&img_initi,_T("E:\\dnf\\ϵͳ\\��ʼ.png")); //��ʼͼƬ
	loadimage(&img_begin,_T("E:\\dnf\\ϵͳ\\��ʼ����.png"));//��ʼͼƬ
	loadimage(&img_mousemsg,_T("E:\\dnf\\ϵͳ\\���.png"));//���ͼƬ

	loadimage(&img_people11,_T("E:\\dnf\\Ů��\\��ֹ�߶�.png")); //��ͼƬ��image�������,
	loadimage(&img_people12,_T("E:\\dnf\\Ů��\\����.jpg")); //������ͼƬ�������
	loadimage(&img_people13,_T("E:\\dnf\\Ů��\\�չ�.png")); //����ͨ�����������
	loadimage(&img_people14,_T("E:\\dnf\\Ů��\\����ն.png")); //����ն
	loadimage(&img_people15,_T("E:\\dnf\\Ů��\\�߲�����.png"));//�߲�����
	loadimage(&img_people16,_T("E:\\dnf\\Ů��\\ͻ��.png"));   //ͻ��
	loadimage(&img_people17,_T("E:\\dnf\\Ů��\\��Ծ.png"));   //��Ծ
	loadimage(&img_people18,_T("E:\\dnf\\Ů��\\��ɽն.png")); //��ɽն
	loadimage(&img_people19,_T("E:\\dnf\\Ů��\\Ѫɫ����.png"));//Ѫɫ����

	gbls=5;
	for(int i=0;i<=gbls-1;i++)
	{
		loadimage(&gbl[i].img_monstre1,_T("E:\\dnf\\�粼��\\����.png"));   //��������
		loadimage(&gbl[i].img_monstre2,_T("E:\\dnf\\�粼��\\����.png"));   //��������
		
		gbl[i].monstre1_xx=0;
		gbl[i].monstre1_yy=0;
		gbl[i].monstre2_yy=0;
		gbl[i].monstre2_xx=0;
		gbl[i].monstre_blood=70;          //�粼�ֹ���Ѫ����ʼֵΪ70����;
		gbl[i].monstre_bj=0;

	}
	

	people1_x=0;
	people1_y=400;
	people1_xx=0;
	people1_yy=0;

	people13_xx=0;
	people13_yy=0;
	people1_bj=0;


	gbl[0].monstre1_x=1000;           //�����粼�ֵĳ�ʼλ��
 	gbl[0].monstre1_y=400;
	
	gbl[1].monstre1_x=800;
	gbl[1].monstre1_y=500;

	gbl[2].monstre1_x=900;
	gbl[2].monstre1_y=400;
	
	gbl[3].monstre1_x=800;
	gbl[3].monstre1_y=400;
	
	gbl[4].monstre1_x=500;
	gbl[4].monstre1_y=450;




	technical='-';



	

}
void show(int time,gebulin gbl[])
{
	
	int a[2][100];
	putimage(0,0,&img_background1);
	
	a[0][0]=people1_y-89+207;
	a[1][0]=0-1;
	for(int i=0;i<=gbls-1;i++)
	{
		a[0][i+1]=gbl[i].monstre1_y+80;
		a[1][i+1]=i;
	}
	for(int i=1;i<=gbls;i++)          // //Ϊ�˸��õػ�����ʾ��˭��y�����˭����ʾ�����ֳ�2.5DЧ��(����ֱ�Ӳ��뷨��������)
	{
		int elem=a[0][i];
		int elem1=a[1][i];
		int j=i-1;
		while(a[0][j]>elem&&j>=0)
		{
			a[0][j+1]=a[0][j];
			a[1][j+1]=a[1][j];
			j--;
		}
		a[0][j+1]=elem;
		a[1][j+1]=elem1;
	}
	
	



	for(int ii=0;ii<=gbls;ii++)
	{
		if(a[1][ii]>-1&&gbl[a[1][ii]].monstre_blood>0)                              //��Ѫ��������ʱ����ʾ����
		{
			static int speed=0;
			if(gbl[a[1][ii]].monstre_bj==0)
			{
				setcolor(BLACKNESS);                                                       //����Ѫ��
				rectangle(gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y-10,gbl[a[1][ii]].monstre1_x+70,gbl[a[1][ii]].monstre1_y-5);
				setcolor(RED);
				for(int i=5;i>=1;i--)
					line(gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y-5-i,gbl[a[1][ii]].monstre1_x+gbl[a[1][ii]].monstre_blood,gbl[a[1][ii]].monstre1_y-5-i);
				TransparentBlt(GetImageHDC(NULL),gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y,70,80,GetImageHDC(&gbl[a[1][ii]].img_monstre1),gbl[a[1][ii]].monstre1_xx,gbl[a[1][ii]].monstre1_yy,70,80,RGB(0,0,0));  //��ʾ����
			}
			else if(gbl[a[1][ii]].monstre_bj==1)
			{
				setcolor(BLACKNESS);                                                       //����Ѫ��
				rectangle(gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y-10,gbl[a[1][ii]].monstre1_x+70,gbl[a[1][ii]].monstre1_y-5);
				setcolor(RED);
				for(int i=5;i>=1;i--)
					line(gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y-5-i,gbl[a[1][ii]].monstre1_x+gbl[a[1][ii]].monstre_blood,gbl[a[1][ii]].monstre1_y-5-i);
				TransparentBlt(GetImageHDC(NULL),gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y,100,80,GetImageHDC(&gbl[a[1][ii]].img_monstre2),gbl[a[1][ii]].monstre2_xx,gbl[a[1][ii]].monstre2_yy,100,80,RGB(0,0,0));  //��ʾ����ͼ��
				if(speed<15)
					speed++;
				else if(speed==15)                              //����15�β���һ������                                                                //���ű�������
				{
					mciSendString(L"close jpmusic",NULL,0,NULL);
					mciSendString(L"open E:\\dnf\\�粼��\\����1.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString(L"play jpmusic",NULL,0,NULL);
					speed=0;
				}
			}
			else if(gbl[a[1][ii]].monstre_bj==2)
			{
				setcolor(BLACKNESS);                                                       //����Ѫ��
				rectangle(gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y-10,gbl[a[1][ii]].monstre1_x+70,gbl[a[1][ii]].monstre1_y-5);
				setcolor(RED);
				for(int i=5;i>=1;i--)
					line(gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y-5-i,gbl[a[1][ii]].monstre1_x+gbl[a[1][ii]].monstre_blood,gbl[a[1][ii]].monstre1_y-5-i);
				TransparentBlt(GetImageHDC(NULL),gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y,100,80,GetImageHDC(&gbl[a[1][ii]].img_monstre2),gbl[a[1][ii]].monstre2_xx,gbl[a[1][ii]].monstre2_yy,100,80,RGB(0,0,0)); //��ʾ����ͼ��
				if(speed<15)
					speed++;
				else if(speed==15)                              //����15�β���һ������                                                                //���ű�������
				{
					mciSendString(L"close jpmusic",NULL,0,NULL);
					mciSendString(L"open E:\\dnf\\�粼��\\����1.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString(L"play jpmusic",NULL,0,NULL);
					speed=0;
				}
			}
		}
		else if(a[1][ii]==-1)
		{
			if(people1_bj==0)           //TransparentBlt(Ŀ���豸��NULLΪĬ�ϵ���ʾ���ڣ�,��ʾ����Ϸ����ľ�������(x,y),��ʾͼƬ�Ĵ�С,��ʾͼƬ��HDC,��ʾͼƬ���������(�������ͼƬ��С��ʾ������),��ʾͼƬ�Ĵ�С,͸���������ɫ��rgb)
				TransparentBlt(GetImageHDC(NULL),people1_x,people1_y,100,118,GetImageHDC(&img_people11),people1_xx,people1_yy,100,118,RGB(0,0,0));
			else if(people1_bj==1)
				TransparentBlt(GetImageHDC(NULL),people1_x-77,people1_y-89,333,207,GetImageHDC(&img_people13),people13_xx,people13_yy,331,207,RGB(0,0,0));
			else if(people1_bj==2)
				TransparentBlt(GetImageHDC(NULL),people1_x-163,people1_y-89,333,207,GetImageHDC(&img_people13),people13_xx,people13_yy,333,207,RGB(0,0,0));  
		}
	}
	Sleep(time);
	
}

void withoutinput(gebulin gbl[])
{
	for(int i=0;i<=gbls-1;i++)
		monstre_gbl(gbl,i);
}


void monstre_gbl(gebulin gbl[],int gbl_n)
{
	static int speed=0;
	if(speed<gbls)
		speed++;
	else if(speed==gbls)
	{
		
		if(technical=='j'||technical=='u')           //���ʹ�û���ն�ͣ��չ��Ļ�
		{
			int bj=0;           //����������Ƿ񱻻���
			gbl[gbl_n].monstre2_xx=gbl[gbl_n].monstre1_xx/70*100;         //���ݹ�������ʱ�ĳ������ж��ܹ���ʱ�ĳ���
			gbl[gbl_n].monstre2_yy=(gbl[gbl_n].monstre2_yy+80)%480;
			if(people1_yy%236+236==236&&(gbl[gbl_n].monstre1_x-(people1_x-77)>100)&&(gbl[gbl_n].monstre1_x-(people1_x-77)<210)&&((people1_y-89)+207<(gbl[gbl_n].monstre1_y+80)+11&&(people1_y-89)+207>(gbl[gbl_n].monstre1_y+80)-11))//�жϹ����Ƿ��ܱ��������(�һ�)
			{
				gbl[gbl_n].monstre_bj=1;
				if(gbl[gbl_n].monstre_blood>=0&&technical=='j')
				{                                                        //���Ϊ��ͨ������Ѫ��һ�μ���7
					gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-7;
					bj=1;
				}
				else if(gbl[gbl_n].monstre_blood>=0&&technical=='u')             //���Ϊ����ն��Ѫ��һ�μ���10
				{
					gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-10;
					bj=1;
				}
				if(gbl[gbl_n].monstre_blood<=0&&bj==1)                            //��Ѫ��С�������ٴα������ǲ�����������
				{
					mciSendString(L"close jpmusic",NULL,0,NULL);
					mciSendString(L"open E:\\dnf\\�粼��\\����2.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString(L"play jpmusic",NULL,0,NULL);
				}
			}
			else if(people1_yy%236+236==354&&((people1_x-163+333)-(gbl[gbl_n].monstre1_x+70)>100)&&((people1_x-163+333)-(gbl[gbl_n].monstre1_x+70)<235)&&((people1_y-89)+207<(gbl[gbl_n].monstre1_y+80)+11&&(people1_y-89)+207>(gbl[gbl_n].monstre1_y+80)-11))//�жϹ����Ƿ񱻻���(���)
			{
				gbl[gbl_n].monstre_bj=2;
				if(technical=='j')                  //���Ϊ��ͨ������Ѫ��һ�μ���7
					gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-7;   
				else if(technical=='u')             //���Ϊ����ն��Ѫ��һ�μ���10
					gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-10;
				if(gbl[gbl_n].monstre_blood<=0&&bj==1)      
				{
					mciSendString(L"close jpmusic",NULL,0,NULL);
					mciSendString(L"open E:\\dnf\\�粼��\\����2.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString(L"play jpmusic",NULL,0,NULL);
				}
			}

		}
		else if(technical=='l')                    //�������Ϊ�߲�����
		{
			int bj=0;            //����������Ƿ񱻻���
			gbl[gbl_n].monstre2_xx=gbl[gbl_n].monstre1_xx/70*100;         //���ݹ�������ʱ�ĳ������ж��ܹ���ʱ�ĳ���
			gbl[gbl_n].monstre2_yy=(gbl[gbl_n].monstre2_yy+80)%480;
			if(gbl[gbl_n].monstre_blood>=0&&people1_yy%236+236==236&&(gbl[gbl_n].monstre1_x-(people1_x-51)>180)&&(gbl[gbl_n].monstre1_x-(people1_x-51)<540)&&((people1_y-114)+232<(gbl[gbl_n].monstre1_y+80)+20&&(people1_y-114)+232>(gbl[gbl_n].monstre1_y+80)-20))//�жϹ����Ƿ��ܱ��������(�һ�)
			{
				gbl[gbl_n].monstre_bj=1;
				gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-28;
				bj=1;
			}
			else if(gbl[gbl_n].monstre_blood>=0&&people1_yy%236+236==354&&((people1_x-400+548)-(gbl[gbl_n].monstre1_x+70)>180)&&((people1_x-400+548)-(gbl[gbl_n].monstre1_x+70)<540)&&((people1_y-114)+232<(gbl[gbl_n].monstre1_y+80)+20&&(people1_y-114)+232>(gbl[gbl_n].monstre1_y+80)-20))//�жϹ����Ƿ񱻻���(���)
			{
				gbl[gbl_n].monstre_bj=2;
				gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-28;
				bj=1;
			}
			if(gbl[gbl_n].monstre_blood<=0&&bj==1)
			{
					mciSendString(L"close jpmusic",NULL,0,NULL);
					mciSendString(L"open E:\\dnf\\�粼��\\����2.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString(L"play jpmusic",NULL,0,NULL);
			}
		}
		else if(technical=='h')
		{
			int bj=0;                                                     //����������Ƿ񱻻���
			gbl[gbl_n].monstre2_xx=gbl[gbl_n].monstre1_xx/70*100;         //���ݹ�������ʱ�ĳ������ж��ܹ���ʱ�ĳ���
			gbl[gbl_n].monstre2_yy=(gbl[gbl_n].monstre2_yy+80)%480;
			
			if(gbl[gbl_n].monstre_blood>=0&&people1_yy%236+236==236&&(gbl[gbl_n].monstre1_x-(people1_x-51)>290)&&(gbl[gbl_n].monstre1_x-(people1_x-51)<490)&&((people1_y-114)+232<(gbl[gbl_n].monstre1_y+80)+20&&(people1_y-114)+232>(gbl[gbl_n].monstre1_y+80)-20))//�жϹ����Ƿ��ܱ��������(�һ�)
			{
				gbl[gbl_n].monstre_bj=1;
				gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-35;
				gbl[gbl_n].monstre1_y=gbl[gbl_n].monstre1_y-10;               //�ø粼�����ƣ�������
				bj=1;
			}
			else if(gbl[gbl_n].monstre_blood>=0&&people1_yy%236+236==354&&((people1_x-400+548)-(gbl[gbl_n].monstre1_x+70)>290)&&((people1_x-400+548)-(gbl[gbl_n].monstre1_x+70)<490)&&((people1_y-114)+232<(gbl[gbl_n].monstre1_y+80)+20&&(people1_y-114)+232>(gbl[gbl_n].monstre1_y+80)-20))//�жϹ����Ƿ񱻻���(���)
			{
				gbl[gbl_n].monstre_bj=2;
				gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-35;
				gbl[gbl_n].monstre1_y=gbl[gbl_n].monstre1_y-10;               //�ø粼�����ƣ�������
				bj=1;
			}
			if(gbl[gbl_n].monstre_blood<=0&&bj==1)
			{
					mciSendString(L"close jpmusic",NULL,0,NULL);
					mciSendString(L"open E:\\dnf\\�粼��\\����2.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString(L"play jpmusic",NULL,0,NULL);
			}
		}
		else if(technical=='i')
		{
			int bj=0;                                                     //����������Ƿ񱻻���
			gbl[gbl_n].monstre2_xx=gbl[gbl_n].monstre1_xx/70*100;         //���ݹ�������ʱ�ĳ������ж��ܹ���ʱ�ĳ���
			gbl[gbl_n].monstre2_yy=(gbl[gbl_n].monstre2_yy+80)%480;
			
			if(gbl[gbl_n].monstre_blood>=0&&people1_yy%236+236==236&&(gbl[gbl_n].monstre1_x-(people1_x-56)>550)&&(gbl[gbl_n].monstre1_x-(people1_x-51)<813)&&((people1_y-114)+232<(gbl[gbl_n].monstre1_y+80)+20&&(people1_y-114)+232>(gbl[gbl_n].monstre1_y+80)-35))//�жϹ����Ƿ��ܱ��������(�һ�)
			{
				gbl[gbl_n].monstre_bj=1;
				gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-70;
				bj=1;
			}
			else if(gbl[gbl_n].monstre_blood>=0&&people1_yy%236+236==354&&((people1_x-619+813)-(gbl[gbl_n].monstre1_x+70)>550)&&((people1_x-619+548)-(gbl[gbl_n].monstre1_x+70)<813)&&((people1_y-114)+232<(gbl[gbl_n].monstre1_y+80)+20&&(people1_y-114)+232>(gbl[gbl_n].monstre1_y+80)-35))//�жϹ����Ƿ񱻻���(���)
			{
				gbl[gbl_n].monstre_bj=2;
				gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-70;
				bj=1;
			}
			if(gbl[gbl_n].monstre_blood<=0&&bj==1)
			{
					mciSendString(L"close jpmusic",NULL,0,NULL);
					mciSendString(L"open E:\\dnf\\�粼��\\����2.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString(L"play jpmusic",NULL,0,NULL);
			}
		}
		else if(technical=='o')
		{
			int bj=0;                                                     //����������Ƿ񱻻���
			gbl[gbl_n].monstre2_xx=gbl[gbl_n].monstre1_xx/70*100;         //���ݹ�������ʱ�ĳ������ж��ܹ���ʱ�ĳ���
			gbl[gbl_n].monstre2_yy=(gbl[gbl_n].monstre2_yy+80)%480;
			
			if(gbl[gbl_n].monstre_blood>=0&&people1_yy%236+236==236&&(gbl[gbl_n].monstre1_x-(people1_x-56)>230)&&(gbl[gbl_n].monstre1_x-(people1_x-51)<530)&&((people1_y-182)+300<(gbl[gbl_n].monstre1_y+80)+20&&(people1_y-182)+300>(gbl[gbl_n].monstre1_y+80)-40))//�жϹ����Ƿ��ܱ��������(�һ�)
			{
				gbl[gbl_n].monstre_bj=1;
				gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-70;
				bj=1;
			}
			else if(gbl[gbl_n].monstre_blood>=0&&people1_yy%236+236==354&&((people1_x-399+548)-(gbl[gbl_n].monstre1_x+70)>230)&&((people1_x-399+548)-(gbl[gbl_n].monstre1_x+70)<530)&&((people1_y-182)+300<(gbl[gbl_n].monstre1_y+80)+20&&(people1_y-182)+300>(gbl[gbl_n].monstre1_y+80)-40))//�жϹ����Ƿ񱻻���(���)
			{
				gbl[gbl_n].monstre_bj=2;
				gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-70;
				bj=1;
			}
			if(gbl[gbl_n].monstre_blood<=0&&bj==1)
			{
					mciSendString(L"close jpmusic",NULL,0,NULL);
					mciSendString(L"open E:\\dnf\\�粼��\\����2.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString(L"play jpmusic",NULL,0,NULL);
			}
		}



		else
			gbl[gbl_n].monstre_bj=0;

		if(gbl[gbl_n].monstre_bj==0)
		{
			if(gbl[gbl_n].monstre1_x>0&&people1_x<gbl[gbl_n].monstre1_x)             //��������ĳ��������¹���ĳ���,���ҿ��ƹ�������Ϸ�������ƶ�
			{
				gbl[gbl_n].monstre1_xx=0;
				gbl[gbl_n].monstre1_x=gbl[gbl_n].monstre1_x-5;
			}

			else if(people1_x>gbl[gbl_n].monstre1_x&&gbl[gbl_n].monstre1_x<=width-75)
			{
				gbl[gbl_n].monstre1_xx=70;
				gbl[gbl_n].monstre1_x=gbl[gbl_n].monstre1_x+5;
			}
		}
		gbl[gbl_n].monstre1_yy=(gbl[gbl_n].monstre1_yy+80)%480;   //�ù�������ͼƬѭ������
		speed=0;
	}
}



void withinput(gebulin gbl[])
{
	char n;
	people1_bj=0;
	technical='-';
	if(kbhit())
	{
		n=getch();
		technical=n;
		if(n=='a')
		{
			people1_yy=354;
			people1_xx=(people1_xx+100)%1000;
			people1_x=people1_x-15;
		}
		else if(n=='d')
		{
			people1_yy=236;
			people1_xx=(people1_xx+100)%1000;
			people1_x=people1_x+15;

		}
		else if(n=='w')
		{
			people1_yy=people1_yy%236+236;
			people1_xx=(people1_xx+100)%1000;
			people1_y=people1_y-5;
		}
		else if(n=='s')
		{
			people1_yy=people1_yy%236+236;
			people1_xx=(people1_xx+100)%1000;
			people1_y=people1_y+5;
		}
		else if(n==' ')
		{
			for(int i=0;i<=15;i++)
			{
	            putimage(200,200,800,326,&img_people12,0,i*326);
				Sleep(100);
			}
		}
		
		else if(n=='j')
		{
			if(people1_yy%236+236==236)                  //���ݾ�ֹͼƬ��ѡ������ж������泯��һ�棬���ж�����
			{
				people13_xx=333;
				people13_yy=(people13_yy+207)%7245;
				people1_bj=1;
			}
			else if(people1_yy%236+236==354)            //���ж�����
			{
				people13_xx=0;
				people13_yy=(people13_yy+207)%7245;
				people1_bj=2;
			}

		}
		else if(n=='k')
		{
			people1_bj=0-1;
			if(people1_yy%236+236==354)
				for(int i=0;i<6;i++)
				{
					char hh;
					if(kbhit())
					{
						hh=getch();
						if(hh=='w')
							people1_y=people1_y-20;
						else if(hh=='d')
							people1_x=people1_x+10;
						else if(hh=='a')
							people1_x=people1_x-10;
					}
					show(0,gbl);
					TransparentBlt(GetImageHDC(NULL),people1_x-163,people1_y-89,333,207,GetImageHDC(&img_people17),0,i*207,333,207,RGB(0,0,0));
					withoutinput(gbl);
					Sleep(200);
				}
			else if(people1_yy%236+236==236)
				for(int i=0;i<6;i++)
				{
					char hh;
					if(kbhit())
					{
						hh=getch();
						if(hh=='w')
							people1_y=people1_y-20;
						else if(hh=='d')
							people1_x=people1_x+10;
						else if(hh=='a')
							people1_x=people1_x-10;
					}
					show(0,gbl);
				    TransparentBlt(GetImageHDC(NULL),people1_x-77,people1_y-89,333,207,GetImageHDC(&img_people17),333,i*207,333,207,RGB(0,0,0));
					withoutinput(gbl);
					Sleep(200);
				}
			people1_bj=0;
		}
			
		else if(n=='u')
		{
			people1_bj=0-1;
			if(people1_yy%236+236==236)
				for(int i=0;i<10;i++)
				{
					show(0,gbl);
					TransparentBlt(GetImageHDC(NULL),people1_x-163,people1_y-89,333,207,GetImageHDC(&img_people14),0,i*207,333,207,RGB(0,0,0));
					withoutinput(gbl);
					Sleep(100);
				}
			else if(people1_yy%236+236==354)
				for(int i=0;i<10;i++)
				{
					show(0,gbl);
				    TransparentBlt(GetImageHDC(NULL),people1_x-77,people1_y-89,333,207,GetImageHDC(&img_people14),333,i*207,333,207,RGB(0,0,0));
					withoutinput(gbl);
					Sleep(100);
				}
			people1_bj=0;
		}
		
		else if(n=='l')
		{
			people1_bj=0-1;
			if(people1_yy%236+236==236)
				for(int i=0;i<6;i++)
				{
					show(0,gbl);
					TransparentBlt(GetImageHDC(NULL),people1_x-56,people1_y-114,548,232,GetImageHDC(&img_people15),548,i*232,548,232,RGB(0,0,0));
					withoutinput(gbl);
					Sleep(100);
				}
			else if(people1_yy%236+236==354)
				for(int i=0;i<6;i++)
				{
					show(0,gbl);
				    TransparentBlt(GetImageHDC(NULL),people1_x-400,people1_y-114,548,232,GetImageHDC(&img_people15),0,i*232,548,232,RGB(0,0,0));
					withoutinput(gbl);
					Sleep(100);
				}
			people1_bj=0;
		}
		else if(n=='h')
		{
			people1_bj=0-1;
			if(people1_yy%236+236==236)
				for(int i=0;i<6;i++)
				{
					show(0,gbl);
					TransparentBlt(GetImageHDC(NULL),people1_x-56,people1_y-114,548,232,GetImageHDC(&img_people16),548,i*232,548,232,RGB(0,0,0));
					withoutinput(gbl);
					Sleep(100);
				}
			else if(people1_yy%236+236==354)
				for(int i=0;i<6;i++)
				{
					show(0,gbl);
				    TransparentBlt(GetImageHDC(NULL),people1_x-400,people1_y-114,548,232,GetImageHDC(&img_people16),0,i*232,548,232,RGB(0,0,0));
					withoutinput(gbl);
					Sleep(100);
				}
			people1_bj=0;
		}
		else if(n=='i')
		{
			people1_bj=0-1;
			if(people1_yy%236+236==236)
				for(int i=0;i<7;i++)
				{
					show(0,gbl);
					TransparentBlt(GetImageHDC(NULL),people1_x-56,people1_y-210,813,328,GetImageHDC(&img_people18),813,i*328,813,328,RGB(0,0,0));
					withoutinput(gbl);
					Sleep(100);
				}
			else if(people1_yy%236+236==354)
				for(int i=0;i<7;i++)
				{
					show(0,gbl);
				    TransparentBlt(GetImageHDC(NULL),people1_x-619,people1_y-210,813,328,GetImageHDC(&img_people18),0,i*328,813,328,RGB(0,0,0));
					withoutinput(gbl);
					Sleep(100);
				}
			people1_bj=0;
		}
		else if(n=='o')
		{
			people1_bj=0-1;
			if(people1_yy%236+236==236)
				for(int i=0;i<6;i++)
				{
					show(0,gbl);
					TransparentBlt(GetImageHDC(NULL),people1_x-56,people1_y-182,542,300,GetImageHDC(&img_people19),542,i*300,542,300,RGB(0,0,0));
					withoutinput(gbl);
					Sleep(100);
				}
			else if(people1_yy%236+236==354)
				for(int i=0;i<6;i++)
				{
					show(0,gbl);
				    TransparentBlt(GetImageHDC(NULL),people1_x-399,people1_y-182,542,300,GetImageHDC(&img_people19),0,i*300,542,300,RGB(0,0,0));
					withoutinput(gbl);
					Sleep(100);
				}
			people1_bj=0;
		}
			
	}
	else
	{
		int k=(people1_yy/118)-2;      //���ƶ��겻�ƶ�ʱ������ֳ���ֹ״̬
		if(k>=0)                       //�ж�����ֹ�����Ҿ�ֹ
		{
			people1_yy=k*118;
			people1_xx=0;
		}
		else                           //����Ѿ���ֹ��ѭ�����ž�ֹͼƬ
			people1_xx=(people1_xx+100)%1000;
	}
	





	if(people1_x<0)             //������������Ϸ�����ڣ�������Ϸ����
		people1_x=0;
	else if(people1_x>=width-75)
		people1_x=width-75;
	if(people1_y<330)
		people1_y=330;
	else if(people1_y>=hight-115)
		people1_y=hight-115;
}







