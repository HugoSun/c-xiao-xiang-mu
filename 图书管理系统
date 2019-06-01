//图书管理系统

#include <iostream>
#include <stdio.h>
#include <string>
#include <iomanip>
using namespace std;
struct book
{
	char name[20];
	char writer[20];
	char press[20];
	char day[20];
	char ISBN[20];
	char num[20];
	book *next;
};
char entry();

void Book_Manage(book *head);
void make_book(book *head);
void look_book(book *head);
void see_book(book *head);
void del_book(book *head);
void keep_book(book *head);
void initi(book *head);

struct users
{
	char names[20];
	char pass[20];
	users *next;
};
void initi1(users *head1);
void User_Manage(users *head1);
void make_user(users *head1);
void look_user(users *head1);
void see_user(users *head1);
void del_user(users *head1);
void keep_user(users *head1);


void user(book *head);
void Adtor(book *head,users *head1);

int main()
{
	char n;
	book *head;
	head=new book;
	head->next=NULL;
	initi(head);

	users *head1;
	head1=new users;
	head1->next=NULL;
	initi1(head1);
	cout<<"           #************************************#"<<endl;
	cout<<"           *                                    *"<<endl;
	cout<<"           *        欢迎进入图书馆管理系统      *"<<endl;
	cout<<"           *                                    *"<<endl;
	cout<<"           #************************************#"<<endl;
	while(1)
	{
	    n=entry();
		if(n!='0')
			break;
	}
	if(n=='1')
		user(head); 
	else if(n=='2')
		Adtor(head,head1);
	return 0;
}

char entry()
{
	char name1[20],password1[20],name2[20],password2[20];
	char ans='a';
	int len,x1=0,x2=0,bj1=0,bj2=0;
	cout<<endl<<"请输入用户名:";
	cin>>name1;
	cout<<endl<<"请输入用户密码:";
	cin>>password1;
	FILE *fp1,*fp2;
	fp1=fopen("E:\\tsgsjk\\user.txt","r");
	if(fp1==NULL)
		cout<<"文件打开失败!"<<endl;    
	else
	{                                     //feof()能检查文件是否结束,结束返回非0值,没结束返回0
		while(ans!=EOF)                   //没有用feof的原因是因为文件结尾有一行空字符,其并不是文件结尾只有把这个空字符读取之后才会到文件结尾
		{                                //        所以用getc()函数与ungetc()函数结合来判断当前读取位置的下一个位置是否为文件结束(功能与c++中的peek函数一样)           
			                                     
			                              //fgets(string,n,文件指针)从文件的一行数据中读n-1个字符存到字符串string中(注意如果n足够大其会连换行符一起读入)
			fgets(name2,10,fp1);          //会将fp1文件中的一行加上换行符都存入字符数组name2中
			len=strlen(name2);            //strlen计算字符数组的长度,在把换行符换成字符数组结束标志'\0'            
			name2[len-1]='\0';            
			x1++;                         
			if(!strcmp(name1,name2))      //注意字符数组比较是否相等时不能直接用数组名(其数组名相当于是首元素的地址，两个字符数组在计算机中的存储在不同的内存块中，所以肯定地址不同)
			{                             //用strcmp()可以比较两个字符数组是否相等,注意相等返回0，不相等返回1
				bj1=1;
				break;
			}

			ans=getc(fp1);                 //先从文件缓冲区中获得下一个字符
			ungetc(ans,fp1);               //在将这个字符送回文件缓冲区,相当于文件指针位置没变

		}
		fclose(fp1);
	}
	fp2=fopen("E:\\tsgsjk\\password.txt","r");
	if(fp2==NULL)
		cout<<"文件打开失败!"<<endl;
	else
	{
		ans='c';
	    while(ans!=EOF)
	    {
		    fgets(password2,14,fp2);
		    len=strlen(password2);
		    password2[len-1]='\0';
		    x2++;
		    if(x2==x1&&!strcmp(password1,password2))
		    {
			    bj2=1;
			    break;
		    }

			ans=getc(fp1);
			ungetc(ans,fp1);

	    }
	    fclose(fp2);
	    if(bj1==1&&bj2==1)
		{
			cout<<"    ****************"<<endl;
		    cout<<"    *   登录成功!  *"<<endl;
			cout<<"    ****************"<<endl;
			return password1[0];
		}
	    else
		{
			cout<<"**************************"<<endl;
			cout<<"*  用户名或密码输入错误! *"<<endl;
			cout<<"**************************"<<endl;
			return '0';
		}
	}
}




void user(book *head)
{
	int n;
	while(1)
	{
		cout<<endl<<"****************用户界面******************"<<endl;
		cout<<"1.浏览图书"<<endl;
		cout<<"2.查询图书"<<endl;
		cout<<"0.退出登录"<<endl;
		cout<<"请输入你想要选择的功能:";
		while(1)
		{
			cin>>n;
			if(n<0||n>2)
				cout<<endl<<"输入错误请重新输入:";
			else
				break;
		}
		if(n==1)
			look_book(head);
		else if(n==2)
			see_book(head);
		else if(n==0)
			break;
	}
	cout<<endl<<"        *************************"<<endl;
	cout<<"        *  已退出图书管理系统!  *"<<endl;
	cout<<"        *************************"<<endl;
}



void Adtor(book *head,users *head1)
{
	int n;
	while(1)
	{
		cout<<endl<<"***************管理员界面*****************"<<endl;
	    cout<<"1.图书管理"<<endl;
	    cout<<"2.用户管理"<<endl;
	    cout<<"0.退出系统"<<endl;
		cout<<"请选择你的功能:";
		while(1)
		{
			cin>>n;
			if(n<0||n>2)
				cout<<endl<<"功能选择错误,请重新选择:";
			else
			{
				cout<<"       ********************"<<endl;
				cout<<"       *   功能选择正确!  *"<<endl;
				cout<<"       ********************"<<endl;
				break;
			}
		}
		if(n==1)
			Book_Manage(head);
		else if(n==2)
			User_Manage(head1);
		else if(n==0)
			break;
	}
}
void Book_Manage(book *head)
{
	int n;
	while(1)
	{
		cout<<endl<<"****************图书管理******************"<<endl;
		cout<<"1.新增图书"<<endl;
		cout<<"2.浏览图书"<<endl;
		cout<<"3.查询图书"<<endl;
		cout<<"4.删除图书"<<endl;
		cout<<"5.保存图书信息"<<endl;
		cout<<"0.退出图书管理"<<endl;
		cout<<"请选择你的功能:";
		while(1)
		{
			cin>>n;
			if(n<0||n>5)
				cout<<endl<<"功能选择错误,请重新选择:";
			else
			{
				cout<<"       ********************"<<endl;
				cout<<"       *   功能选择正确!  *"<<endl;
				cout<<"       ********************"<<endl;
				break;
			}
		}
		if(n==1)
			make_book(head);
		else if(n==2)
			look_book(head);
		else if(n==3)
			see_book(head);
		else if(n==4)
			del_book(head);
		else if(n==5)
			keep_book(head);
		else if(n==0)
		{
			cout<<endl<<"退出图书管理!"<<endl;
			break;
		}
	}
}

void initi(book *head)
{
	FILE *fp;
	char ans='c';
	book *p1=head->next;
	fp=fopen("E:\\tsgsjk\\books.txt","r");
	while(ans!=EOF)
	{
		head->next=new book;
		head->next->next=p1;
		p1=head->next;
		fgets(head->next->name,20,fp);
		head->next->name[strlen(head->next->name)-1]='\0';
		fgets(head->next->writer,20,fp);
		head->next->writer[strlen(head->next->writer)-1]='\0';
		fgets(head->next->press,20,fp);
		head->next->press[strlen(head->next->press)-1]='\0';
		fgets(head->next->day,20,fp);
		head->next->day[strlen(head->next->day)-1]='\0';
		fgets(head->next->ISBN,20,fp);
		head->next->ISBN[strlen(head->next->ISBN)-1]='\0';
		fgets(head->next->num,20,fp);
		head->next->num[strlen(head->next->num)-1]='\0';

		ans=getc(fp);
		ungetc(ans,fp);
	
	}
	fclose(fp);
}


void make_book(book *head)
{
	book *p1;
	string i;
	while(1)
	{
	    p1=head->next;
	    head->next=new book;
	    head->next->next=p1;
		cout<<endl;
		cout<<"请输入图书的名称:";
		cin>>head->next->name;
		cout<<"请输入图书的作者:";
		cin>>head->next->writer;
		cout<<"请输入图书的出版社:";
		cin>>head->next->press;
		cout<<"请输入图书的出版日期:";
		cin>>head->next->day;
		cout<<"请输入图书的ISBN:";
		cin>>head->next->ISBN;
		cout<<"请输入图书的页数:";
		cin>>head->next->num;
		cout<<endl<<"继续增加请按<Y>,增加完成请按其他键:";
		cin>>i;
		if(i!="Y")
		{
			cout<<"        ******************"<<endl;
			cout<<"        *   增加完成!    *"<<endl;
			cout<<"        ******************"<<endl;
			break;
		}
	}
}
void look_book(book *head)
{
	head=head->next;
	cout<<"$*************************************************************$"<<endl;
	cout<<"*            书名              |              作者            *"<<endl;
	cout<<"***************************************************************"<<endl;
	while(head!=NULL)
	{
		cout<<"*"<<setw(23)<<head->name<<"       "<<"|"<<setw(18)<<head->writer<<"            "<<"*"<<endl;
		cout<<"***************************************************************"<<endl;
		head=head->next;
	}
}
void see_book(book *head)
{
	string ibsn,i;
	book *p1=head;
	while(1)
	{
		int bj=0;
		cout<<"请输入需要查询图书的IBSN:";
		cin>>ibsn;
		head=p1->next;
		while(head!=NULL)
		{
			if(head->ISBN==ibsn)
			{
				cout<<"书名:"<<head->name<<endl<<"作者:"<<head->writer<<endl;
				cout<<"出版社:"<<head->press<<endl<<"出版日期:"<<head->day<<endl;
				cout<<"ISBN:"<<head->ISBN<<endl<<"图书的页数:"<<head->num<<endl;
				bj=1;
				break;
			}
			head=head->next;
		}
		if(bj==0)
			cout<<"图书不存在!"<<endl;
		cout<<"继续查询请按<Y>,查询完成请按其他键:";
		cin>>i;
		if(i!="Y")
		{
			cout<<"查询完成!"<<endl;
			break;
		}
	}
}
void del_book(book *head)
{
	string isbn,i;
	int bj=0;
	book *p1,*p2;
	p2=head;
	while(1)
	{
		p1=p2;
		head=p2->next;
		cout<<endl<<"请输入你所要删除的书的ISBN:";
		cin>>isbn;
		while(head!=NULL)
		{
			if(head->ISBN==isbn)
			{
				p1->next=head->next;
				delete head;
				bj=1;
				break;
			}
			p1=head;
			head=head->next;
		}
		if(bj==1)
		{
			cout<<"          *******************"<<endl;
			cout<<"          *     删除成功!   *"<<endl;
			cout<<"          *******************"<<endl;
		}
		else if(bj==0)
		{
			cout<<"         **********************"<<endl;
			cout<<"         *     未找到此书!    *"<<endl;
			cout<<"         **********************"<<endl;
		}
		cout<<"继续删除请按<Y>,删除完成请按其他键:";
		cin>>i;
		if(i!="Y")
		{
			cout<<"          *******************"<<endl;
			cout<<"          *     删除完成!   *"<<endl;
			cout<<"          *******************"<<endl;
			break;
		}
	}
	
}


void keep_book(book *head)
{
	FILE *fp;
	fp=fopen("E:\\tsgsjk\\books.txt","w");
	head=head->next;
	while(head!=NULL)
	{
		fputs(head->name,fp);
		fputs("\n",fp);
		fputs(head->writer,fp);
		fputs("\n",fp);
		fputs(head->press,fp);
		fputs("\n",fp);
		fputs(head->day,fp);
		fputs("\n",fp);
		fputs(head->ISBN,fp);
		fputs("\n",fp);
		fputs(head->num,fp);
		fputs("\n",fp);
		head=head->next;
	}
	fclose(fp);
	cout<<endl<<endl;
	cout<<"        *******************"<<endl;
	cout<<"        *     保存成功!   *"<<endl;
	cout<<"        *******************"<<endl;
}




void initi1(users *head1)
{
	FILE *fp1,*fp2;
	char ans='c';
	users *p1=head1->next;
	fp1=fopen("E:\\tsgsjk\\user.txt","r");
	fp2=fopen("E:\\tsgsjk\\password.txt","r");
	while(ans!=EOF)
	{
		head1->next=new users;
		head1->next->next=p1;
		p1=head1->next;

		fgets(head1->next->names,20,fp1);
		head1->next->names[strlen(head1->next->names)-1]='\0';
		fgets(head1->next->pass,20,fp2);
		head1->next->pass[strlen(head1->next->pass)-1]='\0';

		ans=getc(fp1);
		ungetc(ans,fp1);
	}
	fclose(fp1);
	fclose(fp2);
}

void User_Manage(users *head1)
{
	int n;
	while(1)
	{
		cout<<endl<<"****************成员管理******************"<<endl;
		cout<<"1.新增成员"<<endl;
		cout<<"2.浏览成员"<<endl;
		cout<<"3.查询成员"<<endl;
		cout<<"4.删除成员"<<endl;
		cout<<"5.保存成员信息"<<endl;
		cout<<"0.退出成员管理"<<endl;
		cout<<"请选择你的功能:";
		while(1)
		{
			cin>>n;
			if(n<0||n>5)
				cout<<endl<<"功能选择错误,请重新选择:";
			else
			{
				cout<<"       ********************"<<endl;
				cout<<"       *   功能选择正确!  *"<<endl;
				cout<<"       ********************"<<endl;
				break;
			}
		}
		if(n==1)
			make_user(head1);
		else if(n==2)
			look_user(head1);
		else if(n==3)
			see_user(head1);
		else if(n==4)
			del_user(head1);
		else if(n==5)
			keep_user(head1);
		else if(n==0)
		{
			cout<<endl<<"退出成员管理!"<<endl;
			break;
		}
	}
}
void make_user(users *head1)
{
	users *p1;
	string i;
	while(1)
	{
	    p1=head1->next;
	    head1->next=new users;
	    head1->next->next=p1;
		cout<<endl;
		cout<<"请输入成员的姓名:";
		cin>>head1->next->names;
		cout<<"请输入成员的密码:";
		cin>>head1->next->pass;
		cout<<endl<<"继续增加请按<Y>,增加完成请按其他键:";
		cin>>i;
		if(i!="Y")
		{
			cout<<"          *******************"<<endl;
	        cout<<"          *     增加完成!   *"<<endl;
	        cout<<"          *******************"<<endl;
			break;
		}
	}
}
void look_user(users *head1)
{
	head1=head1->next;
	cout<<"$*************************************************************$"<<endl;
	cout<<"*            姓名              |              密码            *"<<endl;
	cout<<"***************************************************************"<<endl;
	while(head1!=NULL)
	{
		cout<<"*"<<setw(18)<<head1->names<<"            "<<"|"<<setw(13)<<head1->pass<<"                 "<<"*"<<endl;
		cout<<"***************************************************************"<<endl;
		head1=head1->next;
	}
}


void see_user(users *head1)
{
	string names,i;
	users *p1=head1;
	while(1)
	{
		int bj=0;
		cout<<endl<<"请输入需要查询成员的姓名:";
		cin>>names;
		head1=p1->next;
		while(head1!=NULL)
		{
			cout<<"ok"<<endl;
			if(head1->names==names)
			{
				cout<<"ob"<<endl;
				cout<<"姓名:"<<head1->names<<endl<<"密码:"<<head1->pass<<endl;
				bj=1;
				break;
			}
			head1=head1->next;
		}
		if(bj==0)
		{
			cout<<"         **********************"<<endl;
			cout<<"         *     未找到此人!    *"<<endl;
			cout<<"         **********************"<<endl;
		}
		cout<<"继续查询请按<Y>,查询完成请按其他键:";
		cin>>i;
		if(i!="Y")
		{
			cout<<"          *******************"<<endl;
	        cout<<"          *     查询完成!   *"<<endl;
			cout<<"          *******************"<<endl;
			break;
		}
	}
}

void del_user(users *head1)
{
	string names,i;
	int bj=0;
	users *p1,*p2;
	p2=head1;
	while(1)
	{
		p1=p2;
		head1=p2->next;
		cout<<endl<<"请输入你所要删除的成员的姓名:";
		cin>>names;
		while(head1!=NULL)
		{
			if(head1->names==names)
			{
				p1->next=head1->next;
				delete head1;
				bj=1;
				break;
			}
			p1=head1;
			head1=head1->next;
		}
		if(bj==1)
		{
			cout<<"          *******************"<<endl;
	        cout<<"          *     删除成功!   *"<<endl;
			cout<<"          *******************"<<endl;
		}
		else if(bj==0)
		{
			cout<<"         **********************"<<endl;
			cout<<"         *     未找到此人!    *"<<endl;
			cout<<"         **********************"<<endl;
		}
		cout<<endl<<"继续删除请按<Y>,删除完成请按其他键:";
		cin>>i;
		if(i!="Y")
		{
			cout<<"          *******************"<<endl;
	        cout<<"          *     删除完成!   *"<<endl;
			cout<<"          *******************"<<endl;
			break;
		}
	}
}


void keep_user(users *head1)
{
	FILE *fp1,*fp2;
	fp1=fopen("E:\\tsgsjk\\user.txt","w");
	fp2=fopen("E:\\tsgsjk\\password.txt","w");
	head1=head1->next;
	while(head1!=NULL)
	{
		fputs(head1->names,fp1);
		fputs("\n",fp1);
		fputs(head1->pass,fp2);
		fputs("\n",fp2);
		head1=head1->next;
	}
	fclose(fp1);
	fclose(fp2);
	cout<<"          *******************"<<endl;
	cout<<"          *     保存成功!   *"<<endl;
	cout<<"          *******************"<<endl;
}
