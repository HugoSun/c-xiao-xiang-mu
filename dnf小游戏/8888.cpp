#include <graphics.h>
#include <Windows.h>
#include <iostream>
#include <conio.h>
#pragma comment(lib, "MSIMG32.LIB")   //能调用TransparentBlt函数进行透明图片的导入
#pragma comment(lib,"Winmm.lib")      //能播放音乐


int hight,width;                //游戏页面的大小
MOUSEMSG mousemsg;               //设置鼠标交互

IMAGE img_background1;           //场景1图片
IMAGE img_initi;                 //初始图片
IMAGE img_begin;                 //开始图片
IMAGE img_mousemsg;              //鼠标图片


IMAGE img_people11;              //定义人物1图片对象(移动与静止状态)
IMAGE img_people12;              //觉醒状态
IMAGE img_people13;              //普通攻击状态
IMAGE img_people14;              //回旋斩
IMAGE img_people15;              //七彩漩涡
IMAGE img_people16;              //突刺
IMAGE img_people17;              //跳跃
IMAGE img_people18;              //过山斩
IMAGE img_people19;              //血色凝结



int people1_x,people1_y;          //人物1在游戏画面上显示的绝对坐标
int people1_xx,people1_yy;        //人物1显示自身图片的相对坐标
int people13_xx,people13_yy;        //普通攻击的相对坐标
int gbls;                           //哥布林的数目

struct gebulin                          //哥布林
{
    IMAGE img_monstre1;             //哥布林怪物(行走状态)
	IMAGE img_monstre2;             //哥布林受伤状态
	int monstre1_x,monstre1_y;       //哥布林怪物在游戏上显示的绝对坐标
	int monstre1_xx,monstre1_yy;     //哥布林怪物显示自身图片的相对坐标;
	int monstre2_xx,monstre2_yy;   //哥布林怪物受伤时显示的相对坐标
	int monstre_blood;               //哥布林怪物的血量
	int monstre_bj;              //哥布林怪物1标记变量（用来标记怪物更新的状态，0静止和走动,1左普工,2右普攻）
};


int people1_bj;                  //人物1标记变量1（用来标记是人物更新什么状态，0静止和走动，1左普攻，2右普攻）

char technical;                //存放上次所按得技能        

void initi(gebulin gbl[]);
void show(int time,gebulin gbl[]);           //显示函数,time参数的意思为画面提留时间
void withoutinput(gebulin gbl[]);            //与输入无关的更新
void withinput(gebulin gbl[]);              //与输入有关的更新


void monstre_gbl(gebulin gbl[],int gbl_n);           //哥布林类型的怪物的状态更新



int main()
{	

	gebulin  gbl[100];        //定义100个哥布林                
	initi(gbl);
	initgraph(width,hight);        //设置游戏画面大小

	mciSendString(L"open E:\\dnf\\系统\\开始.mp3 alias bkmusic",NULL,0,NULL);
	mciSendString(L"play bkmusic repeat",NULL,0,NULL);
	putimage(0,0,&img_initi);
	Sleep(5000);
	
	while(1)
	{
		
		mousemsg=GetMouseMsg();        //获取鼠标信息,并改变鼠标的图案
	    putimage(0,0,&img_begin);
		TransparentBlt(GetImageHDC(NULL),mousemsg.x-7,mousemsg.y-7,30,30,GetImageHDC(&img_mousemsg),0,0,30,30,RGB(0,0,0));
		if(mousemsg.x>460&&mousemsg.x<660&&mousemsg.y>310&&mousemsg.y<380&&mousemsg.uMsg==WM_LBUTTONDOWN)
		{
			mciSendString(L"close bkmusic",NULL,0,NULL);   //关闭开始音乐
			mciSendString(L"open E:\\dnf\\系统\\龙人之塔.mp3 alias bkmusic",NULL,0,NULL);   //打开龙人之塔背景音乐
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
	loadimage(&img_background1,_T("E:\\dnf\\系统\\场景1.jpg")); //将背景1图片与其关联
	loadimage(&img_initi,_T("E:\\dnf\\系统\\初始.png")); //初始图片
	loadimage(&img_begin,_T("E:\\dnf\\系统\\开始界面.png"));//开始图片
	loadimage(&img_mousemsg,_T("E:\\dnf\\系统\\鼠标.png"));//鼠标图片

	loadimage(&img_people11,_T("E:\\dnf\\女鬼剑\\静止走动.png")); //将图片与image对象关联,
	loadimage(&img_people12,_T("E:\\dnf\\女鬼剑\\觉醒.jpg")); //将觉醒图片与其关联
	loadimage(&img_people13,_T("E:\\dnf\\女鬼剑\\普攻.png")); //将普通攻击与其关联
	loadimage(&img_people14,_T("E:\\dnf\\女鬼剑\\回旋斩.png")); //回旋斩
	loadimage(&img_people15,_T("E:\\dnf\\女鬼剑\\七彩旋涡.png"));//七彩漩涡
	loadimage(&img_people16,_T("E:\\dnf\\女鬼剑\\突刺.png"));   //突刺
	loadimage(&img_people17,_T("E:\\dnf\\女鬼剑\\跳跃.png"));   //跳跃
	loadimage(&img_people18,_T("E:\\dnf\\女鬼剑\\过山斩.png")); //过山斩
	loadimage(&img_people19,_T("E:\\dnf\\女鬼剑\\血色凝结.png"));//血色凝结

	gbls=5;
	for(int i=0;i<=gbls-1;i++)
	{
		loadimage(&gbl[i].img_monstre1,_T("E:\\dnf\\哥布林\\行走.png"));   //怪物行走
		loadimage(&gbl[i].img_monstre2,_T("E:\\dnf\\哥布林\\受伤.png"));   //怪物受伤
		
		gbl[i].monstre1_xx=0;
		gbl[i].monstre1_yy=0;
		gbl[i].monstre2_yy=0;
		gbl[i].monstre2_xx=0;
		gbl[i].monstre_blood=70;          //哥布林怪物血量初始值为70像素;
		gbl[i].monstre_bj=0;

	}
	

	people1_x=0;
	people1_y=400;
	people1_xx=0;
	people1_yy=0;

	people13_xx=0;
	people13_yy=0;
	people1_bj=0;


	gbl[0].monstre1_x=1000;           //各个哥布林的初始位置
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
	for(int i=1;i<=gbls;i++)          // //为了更好地画面显示，谁的y坐标大谁先显示，呈现出2.5D效果(利用直接插入法进行排序)
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
		if(a[1][ii]>-1&&gbl[a[1][ii]].monstre_blood>0)                              //当血量大于零时才显示怪物
		{
			static int speed=0;
			if(gbl[a[1][ii]].monstre_bj==0)
			{
				setcolor(BLACKNESS);                                                       //绘制血量
				rectangle(gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y-10,gbl[a[1][ii]].monstre1_x+70,gbl[a[1][ii]].monstre1_y-5);
				setcolor(RED);
				for(int i=5;i>=1;i--)
					line(gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y-5-i,gbl[a[1][ii]].monstre1_x+gbl[a[1][ii]].monstre_blood,gbl[a[1][ii]].monstre1_y-5-i);
				TransparentBlt(GetImageHDC(NULL),gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y,70,80,GetImageHDC(&gbl[a[1][ii]].img_monstre1),gbl[a[1][ii]].monstre1_xx,gbl[a[1][ii]].monstre1_yy,70,80,RGB(0,0,0));  //显示怪物
			}
			else if(gbl[a[1][ii]].monstre_bj==1)
			{
				setcolor(BLACKNESS);                                                       //绘制血量
				rectangle(gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y-10,gbl[a[1][ii]].monstre1_x+70,gbl[a[1][ii]].monstre1_y-5);
				setcolor(RED);
				for(int i=5;i>=1;i--)
					line(gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y-5-i,gbl[a[1][ii]].monstre1_x+gbl[a[1][ii]].monstre_blood,gbl[a[1][ii]].monstre1_y-5-i);
				TransparentBlt(GetImageHDC(NULL),gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y,100,80,GetImageHDC(&gbl[a[1][ii]].img_monstre2),gbl[a[1][ii]].monstre2_xx,gbl[a[1][ii]].monstre2_yy,100,80,RGB(0,0,0));  //显示被击图像
				if(speed<15)
					speed++;
				else if(speed==15)                              //更新15次播放一次声音                                                                //播放被击声音
				{
					mciSendString(L"close jpmusic",NULL,0,NULL);
					mciSendString(L"open E:\\dnf\\哥布林\\被击1.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString(L"play jpmusic",NULL,0,NULL);
					speed=0;
				}
			}
			else if(gbl[a[1][ii]].monstre_bj==2)
			{
				setcolor(BLACKNESS);                                                       //绘制血量
				rectangle(gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y-10,gbl[a[1][ii]].monstre1_x+70,gbl[a[1][ii]].monstre1_y-5);
				setcolor(RED);
				for(int i=5;i>=1;i--)
					line(gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y-5-i,gbl[a[1][ii]].monstre1_x+gbl[a[1][ii]].monstre_blood,gbl[a[1][ii]].monstre1_y-5-i);
				TransparentBlt(GetImageHDC(NULL),gbl[a[1][ii]].monstre1_x,gbl[a[1][ii]].monstre1_y,100,80,GetImageHDC(&gbl[a[1][ii]].img_monstre2),gbl[a[1][ii]].monstre2_xx,gbl[a[1][ii]].monstre2_yy,100,80,RGB(0,0,0)); //显示被击图像
				if(speed<15)
					speed++;
				else if(speed==15)                              //更新15次播放一次声音                                                                //播放被击声音
				{
					mciSendString(L"close jpmusic",NULL,0,NULL);
					mciSendString(L"open E:\\dnf\\哥布林\\被击1.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString(L"play jpmusic",NULL,0,NULL);
					speed=0;
				}
			}
		}
		else if(a[1][ii]==-1)
		{
			if(people1_bj==0)           //TransparentBlt(目标设备（NULL为默认的显示窗口）,显示到游戏界面的绝对坐标(x,y),显示图片的大小,显示图片的HDC,显示图片的相对坐标(如果超出图片大小显示不出来),显示图片的大小,透明区域的颜色的rgb)
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
		
		if(technical=='j'||technical=='u')           //如果使用回旋斩和，普攻的话
		{
			int bj=0;           //用来标记其是否被击中
			gbl[gbl_n].monstre2_xx=gbl[gbl_n].monstre1_xx/70*100;         //根据怪物行走时的朝向来判断受攻击时的朝向
			gbl[gbl_n].monstre2_yy=(gbl[gbl_n].monstre2_yy+80)%480;
			if(people1_yy%236+236==236&&(gbl[gbl_n].monstre1_x-(people1_x-77)>100)&&(gbl[gbl_n].monstre1_x-(people1_x-77)<210)&&((people1_y-89)+207<(gbl[gbl_n].monstre1_y+80)+11&&(people1_y-89)+207>(gbl[gbl_n].monstre1_y+80)-11))//判断怪物是否能被人物击中(右击)
			{
				gbl[gbl_n].monstre_bj=1;
				if(gbl[gbl_n].monstre_blood>=0&&technical=='j')
				{                                                        //如果为普通攻击则血量一次减少7
					gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-7;
					bj=1;
				}
				else if(gbl[gbl_n].monstre_blood>=0&&technical=='u')             //如果为回旋斩则血量一次减少10
				{
					gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-10;
					bj=1;
				}
				if(gbl[gbl_n].monstre_blood<=0&&bj==1)                            //当血量小于零且再次被击中是播放死亡声音
				{
					mciSendString(L"close jpmusic",NULL,0,NULL);
					mciSendString(L"open E:\\dnf\\哥布林\\被击2.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString(L"play jpmusic",NULL,0,NULL);
				}
			}
			else if(people1_yy%236+236==354&&((people1_x-163+333)-(gbl[gbl_n].monstre1_x+70)>100)&&((people1_x-163+333)-(gbl[gbl_n].monstre1_x+70)<235)&&((people1_y-89)+207<(gbl[gbl_n].monstre1_y+80)+11&&(people1_y-89)+207>(gbl[gbl_n].monstre1_y+80)-11))//判断怪物是否被击中(左击)
			{
				gbl[gbl_n].monstre_bj=2;
				if(technical=='j')                  //如果为普通攻击则血量一次减少7
					gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-7;   
				else if(technical=='u')             //如果为回旋斩则血量一次减少10
					gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-10;
				if(gbl[gbl_n].monstre_blood<=0&&bj==1)      
				{
					mciSendString(L"close jpmusic",NULL,0,NULL);
					mciSendString(L"open E:\\dnf\\哥布林\\被击2.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString(L"play jpmusic",NULL,0,NULL);
				}
			}

		}
		else if(technical=='l')                    //如果技能为七彩漩涡
		{
			int bj=0;            //用来标记其是否被击中
			gbl[gbl_n].monstre2_xx=gbl[gbl_n].monstre1_xx/70*100;         //根据怪物行走时的朝向来判断受攻击时的朝向
			gbl[gbl_n].monstre2_yy=(gbl[gbl_n].monstre2_yy+80)%480;
			if(gbl[gbl_n].monstre_blood>=0&&people1_yy%236+236==236&&(gbl[gbl_n].monstre1_x-(people1_x-51)>180)&&(gbl[gbl_n].monstre1_x-(people1_x-51)<540)&&((people1_y-114)+232<(gbl[gbl_n].monstre1_y+80)+20&&(people1_y-114)+232>(gbl[gbl_n].monstre1_y+80)-20))//判断怪物是否能被人物击中(右击)
			{
				gbl[gbl_n].monstre_bj=1;
				gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-28;
				bj=1;
			}
			else if(gbl[gbl_n].monstre_blood>=0&&people1_yy%236+236==354&&((people1_x-400+548)-(gbl[gbl_n].monstre1_x+70)>180)&&((people1_x-400+548)-(gbl[gbl_n].monstre1_x+70)<540)&&((people1_y-114)+232<(gbl[gbl_n].monstre1_y+80)+20&&(people1_y-114)+232>(gbl[gbl_n].monstre1_y+80)-20))//判断怪物是否被击中(左击)
			{
				gbl[gbl_n].monstre_bj=2;
				gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-28;
				bj=1;
			}
			if(gbl[gbl_n].monstre_blood<=0&&bj==1)
			{
					mciSendString(L"close jpmusic",NULL,0,NULL);
					mciSendString(L"open E:\\dnf\\哥布林\\被击2.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString(L"play jpmusic",NULL,0,NULL);
			}
		}
		else if(technical=='h')
		{
			int bj=0;                                                     //用来标记其是否被击中
			gbl[gbl_n].monstre2_xx=gbl[gbl_n].monstre1_xx/70*100;         //根据怪物行走时的朝向来判断受攻击时的朝向
			gbl[gbl_n].monstre2_yy=(gbl[gbl_n].monstre2_yy+80)%480;
			
			if(gbl[gbl_n].monstre_blood>=0&&people1_yy%236+236==236&&(gbl[gbl_n].monstre1_x-(people1_x-51)>290)&&(gbl[gbl_n].monstre1_x-(people1_x-51)<490)&&((people1_y-114)+232<(gbl[gbl_n].monstre1_y+80)+20&&(people1_y-114)+232>(gbl[gbl_n].monstre1_y+80)-20))//判断怪物是否能被人物击中(右击)
			{
				gbl[gbl_n].monstre_bj=1;
				gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-35;
				gbl[gbl_n].monstre1_y=gbl[gbl_n].monstre1_y-10;               //让哥布林上移（悬浮）
				bj=1;
			}
			else if(gbl[gbl_n].monstre_blood>=0&&people1_yy%236+236==354&&((people1_x-400+548)-(gbl[gbl_n].monstre1_x+70)>290)&&((people1_x-400+548)-(gbl[gbl_n].monstre1_x+70)<490)&&((people1_y-114)+232<(gbl[gbl_n].monstre1_y+80)+20&&(people1_y-114)+232>(gbl[gbl_n].monstre1_y+80)-20))//判断怪物是否被击中(左击)
			{
				gbl[gbl_n].monstre_bj=2;
				gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-35;
				gbl[gbl_n].monstre1_y=gbl[gbl_n].monstre1_y-10;               //让哥布林上移（悬浮）
				bj=1;
			}
			if(gbl[gbl_n].monstre_blood<=0&&bj==1)
			{
					mciSendString(L"close jpmusic",NULL,0,NULL);
					mciSendString(L"open E:\\dnf\\哥布林\\被击2.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString(L"play jpmusic",NULL,0,NULL);
			}
		}
		else if(technical=='i')
		{
			int bj=0;                                                     //用来标记其是否被击中
			gbl[gbl_n].monstre2_xx=gbl[gbl_n].monstre1_xx/70*100;         //根据怪物行走时的朝向来判断受攻击时的朝向
			gbl[gbl_n].monstre2_yy=(gbl[gbl_n].monstre2_yy+80)%480;
			
			if(gbl[gbl_n].monstre_blood>=0&&people1_yy%236+236==236&&(gbl[gbl_n].monstre1_x-(people1_x-56)>550)&&(gbl[gbl_n].monstre1_x-(people1_x-51)<813)&&((people1_y-114)+232<(gbl[gbl_n].monstre1_y+80)+20&&(people1_y-114)+232>(gbl[gbl_n].monstre1_y+80)-35))//判断怪物是否能被人物击中(右击)
			{
				gbl[gbl_n].monstre_bj=1;
				gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-70;
				bj=1;
			}
			else if(gbl[gbl_n].monstre_blood>=0&&people1_yy%236+236==354&&((people1_x-619+813)-(gbl[gbl_n].monstre1_x+70)>550)&&((people1_x-619+548)-(gbl[gbl_n].monstre1_x+70)<813)&&((people1_y-114)+232<(gbl[gbl_n].monstre1_y+80)+20&&(people1_y-114)+232>(gbl[gbl_n].monstre1_y+80)-35))//判断怪物是否被击中(左击)
			{
				gbl[gbl_n].monstre_bj=2;
				gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-70;
				bj=1;
			}
			if(gbl[gbl_n].monstre_blood<=0&&bj==1)
			{
					mciSendString(L"close jpmusic",NULL,0,NULL);
					mciSendString(L"open E:\\dnf\\哥布林\\被击2.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString(L"play jpmusic",NULL,0,NULL);
			}
		}
		else if(technical=='o')
		{
			int bj=0;                                                     //用来标记其是否被击中
			gbl[gbl_n].monstre2_xx=gbl[gbl_n].monstre1_xx/70*100;         //根据怪物行走时的朝向来判断受攻击时的朝向
			gbl[gbl_n].monstre2_yy=(gbl[gbl_n].monstre2_yy+80)%480;
			
			if(gbl[gbl_n].monstre_blood>=0&&people1_yy%236+236==236&&(gbl[gbl_n].monstre1_x-(people1_x-56)>230)&&(gbl[gbl_n].monstre1_x-(people1_x-51)<530)&&((people1_y-182)+300<(gbl[gbl_n].monstre1_y+80)+20&&(people1_y-182)+300>(gbl[gbl_n].monstre1_y+80)-40))//判断怪物是否能被人物击中(右击)
			{
				gbl[gbl_n].monstre_bj=1;
				gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-70;
				bj=1;
			}
			else if(gbl[gbl_n].monstre_blood>=0&&people1_yy%236+236==354&&((people1_x-399+548)-(gbl[gbl_n].monstre1_x+70)>230)&&((people1_x-399+548)-(gbl[gbl_n].monstre1_x+70)<530)&&((people1_y-182)+300<(gbl[gbl_n].monstre1_y+80)+20&&(people1_y-182)+300>(gbl[gbl_n].monstre1_y+80)-40))//判断怪物是否被击中(左击)
			{
				gbl[gbl_n].monstre_bj=2;
				gbl[gbl_n].monstre_blood=gbl[gbl_n].monstre_blood-70;
				bj=1;
			}
			if(gbl[gbl_n].monstre_blood<=0&&bj==1)
			{
					mciSendString(L"close jpmusic",NULL,0,NULL);
					mciSendString(L"open E:\\dnf\\哥布林\\被击2.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString(L"play jpmusic",NULL,0,NULL);
			}
		}



		else
			gbl[gbl_n].monstre_bj=0;

		if(gbl[gbl_n].monstre_bj==0)
		{
			if(gbl[gbl_n].monstre1_x>0&&people1_x<gbl[gbl_n].monstre1_x)             //根据人物的朝向来更新怪物的朝向,而且控制怪物在游戏界面内移动
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
		gbl[gbl_n].monstre1_yy=(gbl[gbl_n].monstre1_yy+80)%480;   //让怪物行走图片循环播放
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
			if(people1_yy%236+236==236)                  //根据静止图片的选择可以判断其是面朝哪一面，此判断向右
			{
				people13_xx=333;
				people13_yy=(people13_yy+207)%7245;
				people1_bj=1;
			}
			else if(people1_yy%236+236==354)            //此判断向左
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
		int k=(people1_yy/118)-2;      //当移动完不移动时让其呈现出静止状态
		if(k>=0)                       //判断是左静止还是右静止
		{
			people1_yy=k*118;
			people1_xx=0;
		}
		else                           //如果已经静止则循环播放静止图片
			people1_xx=(people1_xx+100)%1000;
	}
	





	if(people1_x<0)             //控制人物在游戏界面内，不出游戏界面
		people1_x=0;
	else if(people1_x>=width-75)
		people1_x=width-75;
	if(people1_y<330)
		people1_y=330;
	else if(people1_y>=hight-115)
		people1_y=hight-115;
}







