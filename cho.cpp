#include "ui.h"
#include <conio.h>
#include <windows.h>
#define getrand(a,b) (rand()%b+a)//�H�����o���v
//----------------------------------------------------------------
//                            �ŧi�w�]��
//----------------------------------------------------------------
int plx=10,ply=8;		//���a��l���� 
int Profession;			//¾�~
int maxhp;				//max HP
int ruby = 2000;		//�w�]�����ƶq
int arms[10];			//�Z���I�]
int fangbag[10];		//���a����I�]
int nowwu=-1;			//���a�w�]�Z�����A
int boci = 1;			//�Ǫ���s����
int mis;				//mission
int check;				//check in which map
int ability = 1;		//�ޯ��I��
int Attributes = 1;		//�ݩ��I��
int check_f;			//�קK�P�_�ɯŪ��a�譫�_�[���Ω�ޯ�
int check_s;			//�קK�P�_�ɯŪ��a�譫�_�[���Ω��ݩ�
string title[9] = {"","�K�P","�ɵP","�ȵP","���P","�ժ�","�p��","�W�Z","����"}; //���Ũt��
char m;					//������O���ܼ�(change string)
char up;				//�ݩ��I�Ƥ������O�ܼ�
char l;					//�ޯ��I�Ƥ������O�ܼ�
string np;				//�Ω�npc�ө�				
int kill_a;				//���ȥΪ������u
int kill_b;				//���ȥΪ������L
int kill_c;				//���ȥΪ������j
//----------------------------------------------------------------
//                             �w�q�禡
//----------------------------------------------------------------
void room1();			//��������
void room2();			//���Ȥ���
void fig();				//���ǩж�
void start(int);		//�Ǫ���l��
void fight(int);		//��ܬO�_����
void openbag();			//open bag
void frun();			//for run
void map();				//�@�ɦa��
void we();				//weapon
void fa();				//����
void ffight(int n);		//���Ǩ禡
void at();				//atibility points
void st();				//still points
void mi();				//���ȧ�������
int hp();				//hp
int unhurt(int m);		//�K�˲v
int eva();				//�{�ײv
int crit();				//�z���v
int damage();			//�ˮ`
int sp();				//��O
//----------------------------------------------------------------
//                            �w�]�Ǫ��ƭ�
//----------------------------------------------------------------
string monpic[4]={"","�u","�L","��"}; 
struct smonster
{
	string name;
	int type;
	int drop;
	int ruby;
	int damage;
	int unhurt;
	int crit;
	int eva;
	int x;
	int y;
	int alive;
	int hp;
}mon[8][4]=
{
	{}, //{" xxxx ", /*����*/, /*����*/,/*�_��*/,/*�ˮ`*/,/*�K��*/,/*����*/,/*�{��*/,/*x*/ ,/*y*/ ,/*alive*/,/*�ͩR*/},
	{
		{}, 
		{"�˽b�u�}", 1, 5,30,10,10,10,10, 5, 5,1,200},
		{"�˥��L�r", 2, 0,25, 5,10,10,10, 5,10,1,180},
		{"�˥һj��", 3, 0,30, 5,10,10,10,9, 5,1,160}, 
	},
	{
		{},
		{"�۽b�u�}", 1, 5,45,25,15,15,15,10, 9,2,220},
		{"�ۥ��L�r", 2, 1,35,20,25,10,10, 5, 5,2,210},
		{"�ۥһj��", 3, 0,40,25,15,10,15,15, 9,2,200}, 
	},
	{
		{}, 
		{"�K�b�u�}", 1/*����*/, 6/*����*/,55/*�_��*/,40/*�ˮ`*/,10/*�K��*/,15/*����*/,15/*�{��*/, 7, 5,2,210/*�ͩR*/},
		{"�K���L�r", 2/*����*/, 5/*����*/,50/*�_��*/,30/*�ˮ`*/,15/*�K��*/,10/*����*/,15/*�{��*/, 3, 3,2,230/*�ͩR*/},
		{"�K�һj��", 3/*����*/, 0/*����*/,50/*�_��*/,25/*�ˮ`*/,20/*�K��*/,20/*����*/,9/*�{��*/,9,12,2,230/*�ͩR*/},
	},
	{
		{}, 
		{"���Ҿu�}", 1/*����*/, 0/*����*/,50/*�_��*/,45/*�ˮ`*/,20/*�K��*/,10/*����*/,20/*�{��*/, 7, 3,2,255/*�ͩR*/},
		{"�����L�r", 2/*����*/, 3/*����*/,55/*�_��*/,45/*�ˮ`*/,35/*�K��*/,15/*����*/,15/*�{��*/, 3, 5,2,245/*�ͩR*/},
		{"���һj��", 3/*����*/, 0/*����*/,55/*�_��*/,50/*�ˮ`*/,20/*�K��*/,15/*����*/,15/*�{��*/,9,9,2,250/*�ͩR*/},
	},	
	{
		{}, 
		{"���Ҿu�}", 1/*����*/, 4/*����*/,50/*�_��*/,50/*�ˮ`*/,40/*�K��*/,10/*����*/,10/*�{��*/, 7, 3,2,255/*�ͩR*/},
		{"�����L�r", 2/*����*/, 0/*����*/,55/*�_��*/,45/*�ˮ`*/,25/*�K��*/,15/*����*/,20/*�{��*/, 3, 5,2,250/*�ͩR*/},
		{"���һj��", 3/*����*/, 7/*����*/,50/*�_��*/,50/*�ˮ`*/,20/*�K��*/,15/*����*/,15/*�{��*/,9, 8,2,250/*�ͩR*/},
	},
	{
		{}, 
		{"�p�Ҿu�}", 1/*����*/, 3/*����*/,55/*�_��*/,50/*�ˮ`*/,40/*�K��*/,15/*����*/,10/*�{��*/, 7, 3,2,265/*�ͩR*/},
		{"�p���L�r", 2/*����*/, 0/*����*/,45/*�_��*/,45/*�ˮ`*/,25/*�K��*/,15/*����*/,25/*�{��*/, 3, 5,2,265/*�ͩR*/},
		{"�p�һj��", 3/*����*/, 7/*����*/,50/*�_��*/,65/*�ˮ`*/,20/*�K��*/,15/*����*/,10/*�{��*/,9,10,2,265/*�ͩR*/},
	},
	{
		{}, 
		{"�L�ľu�}", 1/*����*/, 6/*����*/,66/*�_��*/,35/*�ˮ`*/,10/*�K��*/,15/*����*/,10/*�{��*/, 7, 5,2,250/*�ͩR*/},
		{"�L���L�r", 2/*����*/, 1/*����*/,66/*�_��*/,25/*�ˮ`*/,15/*�K��*/,10/*����*/,10/*�{��*/, 3, 3,2,250/*�ͩR*/},
		{"�L�Ļj��", 3/*����*/, 0/*����*/,66/*�_��*/,25/*?�`*/,10/*�K��*/,20/*����*/,10/*�{��*/,11,10,2,250/*�ͩR*/},	
	}	
}; 

//----------------------------------------------------------------
//                             �w�]¾�~���
//----------------------------------------------------------------
struct Prof{
	string name;	//�W��
	int HP; 		//�ͩR��
	int SP;			//��O
	int damage;		//�ˮ`��
    int EVA;		//�K�˲v
	int CR;			//�����v
	int ER;			//�{�ײv
	string icon;
}   Profess[5]= {
	{},
	{"�}�b",400,225,130,16,20,15,"�}"},
	{"�Ԥh",600,210,120,22,30,10,"��"},
	{"�C�h",500, 175,115,30,25, 5,"�C"},
	{"���",1600,1550,2000,20,40,25,"��"},
};
//----------------------------------------------------------------
//                             �ޯ�
//----------------------------------------------------------------
struct SKILL{
	string name1;
	string name2;
	string name3;
	string name4;
	int rank1;
	int rank2;
	int rank3;
	int rank4;
	int damage1;
	int damage2;
	int damage3;
	int damage4;
}skill[5]  = {
	{},
	{"��Ǳj��","�ʨB�﷨","�Q���b","�׷����}",1,1,1,1,10,20,30,40},
	{"���H","�E�y","�Ϯg����","�׷����y",1,1,1,1,10,20,30,40},
	{"�]�Ѥ@��","�C���a��","�p�蠟�C","�L���C�R",1,1,1,1,10,20,30,40},
	{"�ۤƳN","������","��Ƿt��","���t�t��",1,1,1,1,10,20,30,40},
};
//----------------------------------------------------------------
//                             �w�]�Z��
//----------------------------------------------------------------
struct ARM
{
	string name;
	int damage;
	int much; 
	int have;
	int zhiye;
}   ARMM[13] = {
	{}, 
	{"�۽b",25, 70,0,1},
	{"�K�b",35,130,0,1},
	{"�p�b",55,220,0,1},
	
	{"�ۤM",25, 70,0,2},
	{"�K�M",35,130,0,2},
	{"�p�M",55,220,0,2},
	
	{"��C",25, 70,0,3},
	{"�ۼC",35,130,0,3},
	{"�p�C",55,220,0,3},
	
	{"�ۤP",25, 65,0,1},
	{"�K�P",35,125,0,1},
	{"�p�P",55,230,0,1},
};
//----------------------------------------------------------------
//                          �w�]����
//----------------------------------------------------------------
struct sfangju
{
	string name;
	int fangku;
	int fangzhu;
	int fangjiang;
	int much;
	int have;
	int type;
	int check;
}fangju[6]=
{
	{}, 
	{"���",11,10, 6,80,0,1,1},
	
	{"�K��", 7,11, 5,90,0,2,1},
	{"�p��",12,16, 6,175,0,2,2},
	
	{"�K��",11, 5,12,120,0,3,1},
	{"�p��",16, 6,17,200,0,3,2},	
};
//----------------------------------------------------------------
//                             �{�b�˳ƪ�����
//----------------------------------------------------------------
struct snowfang
{
	int dun;
	int ku;
	int jia;
}nowfang={-1,-1,-1};
//----------------------------------------------------------------
//                             npc page
//----------------------------------------------------------------
void npc(){
    
	ui set;
	system("cls");
	system("color 0F");
    set.go(2,1);
	printf("�п�ܧA���ȡG");
	set.go(2,2);
	printf("     ����3���u");
	set.go(2,3);
	printf("     ����3���L��");
	set.go(2,4);
	printf("     ����3���j��");
    set.go(2,5);
	printf("     ������");
	int key = 0;
	int massione = 0;
    while(key!=13)
	{
		if(kbhit())
		{
			key=getch();
			if(key=='w'||key=='W')
			{
				set.go(0,1+massione);
				printf("  ");
				massione++;
			}
			if(key=='s'||key=='S')
			{
				set.go(0,1+massione);
				printf("  ");
				massione++;
			}
             if(key==27){
			     return;
		     }
			if(massione>4)massione-=4;
			if(massione<1)massione+=4;
			set.go(0,1+massione);
			mis = massione;
			mis++;
			printf(">>");

			if(mis==2)
				kill_a = 3;
			if(mis==3)
				kill_b = 3;
			if(mis==4)
				kill_c = 3;
        
		}
	}
}
//------------------------------------------------------------------------------------------
//                             �@�ɦa��
//------------------------------------------------------------------------------------------
void map(){
	ui set;
    system("cls");
	system("color 0F");
    cout<<"--------------------------------------------------------------------|"<<endl;
    cout<<"|                    -----------     ----------                     |"<<endl;
    cout<<"|                    |   we    |     |  out   |                     |"<<endl;
    cout<<"|                    |         |     |        |                     |"<<endl;
    cout<<"|                    -----------     ----------                     |"<<endl;
    cout<<"|                      |   |          |  |                          |"<<endl;
    cout<<"|                    ----------      ----------                     |"<<endl;
    cout<<"|                    |  room1 | -----| room2  |                     |"<<endl;
    cout<<"|                    |        | -----|        |                     |"<<endl;
    cout<<"|                    ----------      ----------                     |"<<endl;
    cout<<"|                      |   |                                        |"<<endl;
    cout<<"|                    ---------                                      |"<<endl;
    cout<<"|                    |   fa  |                                      |"<<endl;
    cout<<"|                    |       |                                      |"<<endl;
    cout<<"|                    ---------                                      |"<<endl;   
    cout<<"--------------------------------------------------------------------|"<<endl;
		if(check==1){
			set.go(8,5);set.color();cout<<"*";//room1
			set.go(10,15);
		}else if(check==2){
			set.go(8,0);set.color(12);cout<<"*";//we
			set.go(10,15);
			set.color();
		}else if (check==3){
			set.go(8,10);set.color(12);cout<<"*";//fa
			set.go(10,15);
			set.color();
		}else if(check==4){
			set.go(16,5);set.color(12);cout<<"*";//room2
			set.go(10,15);
			set.color();
		}else if(check==5){
			set.go(16,0);set.color(12);cout<<"*";//���~
			set.go(10,15);
			set.color();
		}
		
	cout<<"�п�J���O: ";
	cin>>m;
	if(m=='3'&&check==1){
		 system("cls");
		 room1();
	}else if(m =='3'&&check==2){
		system("cls");
		we();
	}else if(m =='3'&&check==3){
		system("cls");
		fa();
	}else if(m=='3'&&check==4){
		system("cls");
		room2();
	}else if(m=='3'&&check==5){
		system("cls");
		fig();
	}
}
//-----------------------------------------------------------------------------------
//                            ���¾�~
//-----------------------------------------------------------------------------------
void cho()
{
	ui set;
	system("cls");//�M�ŵe��
	set.go(0,0);
	cout<<("�п�ܧA��¾�~�G");
	set.go(2,1);
	cout<<("¾�~  �ͩR��  ��O��  �ˮ`�� �K�˲v%%  �z���v%%   �{�ײv%%   �ϼ�");	
	for(int i=1;i<=4;i++)
	{
		set.go(2,1+i);
		cout<<Profess[i].name;
		set.go(5,1+i);
		cout<<Profess[i].HP;
		set.go(9,1+i);
		cout<<Profess[i].SP;
		set.go(13,1+i);
		cout<<Profess[i].damage;
		set.go(17,1+i);
		cout<<Profess[i].EVA;
        set.go(22,1+i);
		cout<<Profess[i].CR;
		set.go(27,1+i);
		cout<<Profess[i].ER;
		set.go(32,1+i);
		cout<<Profess[i].icon;
	}
	Profession=1;
	set.go(0,2);
	cout<<(">>");
	int key=0;
	while(key!=13)
	{
		if(kbhit())
		{
			key=getch();
			if(key=='w'||key=='W')
			{
				set.go(0,1+Profession);
				printf("  ");
				Profession--;
			}
			if(key=='s'||key=='S')
			{
				set.go(0,1+Profession);
				printf("  ");
				Profession++;
			}
			if(Profession>4)Profession-=4;
			if(Profession<1)Profession+=4;
			set.go(0,1+Profession);
			cout<<(">>");
		}
	}
	maxhp = Profess[Profession].HP;
}
//----------------------------------------------------------------
//                      ����C�����e���D�{��
//----------------------------------------------------------------
void gaming(){
	ui set;
	system("cls");
	set.printmap();
	string icon = Profess[Profession].icon;
	int plx = 1,ply = 8;
	int key = 0;

	set.go(25,0);cout<<"¾�~: "<<Profess[Profession].name;
	set.go(25,1);cout<<"�ͩR��: "<<Profess[Profession].HP;
	set.go(25,2);cout<<"��O��: "<<Profess[Profession].SP;
	set.go(25,4);cout<<"�ˮ`��: "<<Profess[Profession].damage;
    set.go(26,5);cout<<"�K�˲v�G"<<Profess[Profession].EVA;
	set.go(25,6);cout<<"�z���v: "<<Profess[Profession].CR;
	set.go(25,7);cout<<"�{�ײv: "<<Profess[Profession].ER;
	set.go(25,9);cout<<"���_��: "<<ruby;

    while(1){
        ui set;
		room1();
		room2();	
    }
   
}


//----------------------------------------------------------------
//                             �Z���ө�
//----------------------------------------------------------------
void weshop()
{
    ui set;
	system("cls");
	system("color 0F");
	set.go(9,0);printf("�Z���ө�"); 
	set.go(2,2);
	printf("�W��  �ˮ`��  �R��  ");	
	for(int i=1;i<=3;i++)
	{
		set.go(2,2+i);cout<<ARMM[(Profession-1)*3+i].name;
		set.go(5,2+i);cout<<ARMM[(Profession-1)*3+i].damage;
		set.go(9,2+i);cout<<ARMM[(Profession-1)*3+i].much;
	}
	
	int key=0;int a=1;
	while(key!=27)
	{
		set.color(15);
		set.go(0,2+a);printf(">>");
		key=getch();
		if(key==13)
		{
			if(ruby>=ARMM[(Profession-1)*3+a].much){
				if(ARMM[a].have==0){
					ruby-=ARMM[(Profession-1)*3+a].much;
					ARMM[a].have=1;
					arms[++arms[0]]=(Profession-1)*3+a;
					set.go(2,7);printf("successfully purchased  remaining %d ruby ",ruby);
				}
				else
				{
					set.go(2,7);printf("�A�w�g�֦������~                                 ");
				}
			}
			else
			{
				set.go(2,7);printf("�_�ۤ���                                            ");
			}
		}
		else if(key=='W'||key=='w')
		{
			set.go(0,2+a);printf("  "); 
			a--;
			if(a<1)a+=3;
		}
		else if(key=='S'||key=='s')
		{
			set.go(0,2+a);printf("  "); 
			a++;
			if(a>3)a-=3;
		}
		else if(key==27)
		{
			return;
		}
		else
		{
			weshop();
			return;
		}
	}
}
//----------------------------------------------------------------
//                             ����ө�
//----------------------------------------------------------------
void fangshop()
{
    ui set;
	system("cls");
	system("color 0F");
	set.go(7,0);printf("����ө�"); 
	set.go(2,2);
	printf("�W��  ���u  ����  ����  �R��  ");
	for(int i=1;i<=5;i++)
	{
		set.go(2,2+i);cout<<fangju[i].name;
		set.go(5,2+i);cout<<fangju[i].fangku;
		set.go(8,2+i);cout<<fangju[i].fangjiang;
		set.go(11,2+i);cout<<fangju[i].fangzhu;
		set.go(14,2+i);cout<<fangju[i].much;
	}
	
	int key=0;
	int a=1;
	while(key!=27)
	{
		set.color(15);
		set.go(0,2+a);printf(">>");
		key=getch();
		if(key==13)
		{
			if(ruby>=fangju[a].much)
			{
				if(fangju[a].have==0)
				{
					ruby-=fangju[a].much;
					fangju[a].have=1;
					fangbag[++fangbag[0]]=a;
					set.go(2,9);printf("successfully purchased  remaining %d ruby ",ruby);
				}
				else 
				{
					set.go(2,9);printf("�A�w�g�֦������~                                 ");
				}
			}
			else
			{
				set.go(2,9);printf("�_�ۤ���                                            ");
			}
		}
		else if(key=='W'||key=='w')
		{
			set.go(0,2+a);printf("  "); 
			a--;
			if(a<1)a+=5;
		}
		else if(key=='S'||key=='s')
		{
			set.go(0,2+a);printf("  "); 
			a++;
			if(a>5)a-=5;
		}
		else if(key==27)
		{
			return;
		}
		else
		{
			fangshop();
			return;
		}
	}
}
//----------------------------------------------------------------
//                            printright
//----------------------------------------------------------------

void printright()
{

    ui set;
	set.go(25,0);cout<<"¾�~�G"<<Profess[Profession].name;
	set.go(25,1);cout<<"�ͩR�ȡG"<<hp()<<"/"<<maxhp<<"   ";
	set.go(25,2);cout<<"��O�ȡG"<<sp()<<"   ";
	set.go(25,4);cout<<"�ˮ`�ȡG"<<damage()<<"%  ";
    set.go(25,5);cout<<"�K�˲v�G"<<unhurt(1)<<"%/"<<unhurt(2)<<"%/"<<unhurt(3)<<"%";
	set.go(25,6);cout<<"�����v�G"<<crit()<<"%   ";
	set.go(25,7);cout<<"�{�ײv�G"<<eva()<<"%   ";
	set.go(25,8);
		if(boci==1){
			cout<<"�㦳�ޯ�: "<<skill[Profession].name1<<endl;
		}else if(boci==2){
			cout<<"�㦳�ޯ�: "<<skill[Profession].name1<<" "<<skill[Profession].name2<<endl;
		}else if(boci==3){
			cout<<"�㦳�ޯ�: "<<skill[Profession].name1<<" "<<skill[Profession].name2<<" "<<skill[Profession].name3<<endl;
		} else if(boci==4){
			cout<<"�㦳�ޯ�: "<<skill[Profession].name1<<" "<<skill[Profession].name2<<" "<<skill[Profession].name3<<" "<<skill[Profession].name4<<endl;
		}
	set.go(25,10);cout<<"�ٸ��G "<<title[boci]<<Profess[Profession].name<<"  ";
	set.go(25,11);//{"","�K�P","�ɵP","�ȵP","���P","�ժ�","�p��","�W�Z","����"};
 					if(title[boci]=="�ɵP"&&check_f==1){
						ability = ability+1;
						check_f -= 1;
					}
					else if(title[boci]=="�ȵP"&&check_f==1){
						ability = ability+1;
						check_f -= 1;
					}
					else if(title[boci]=="���P"&&check_f==1){
						ability = ability+1;
						check_f -= 1;
					}
					else if(title[boci]=="�ժ�"&&check_f==1){
						ability = ability+1;
						check_f -= 1;
					}
					else if(title[boci]=="�p��"&&check_f==1){
						ability = ability+1;
						check_f -= 1;
					}
					else if(title[boci]=="�W�Z"&&check_f==1){
						ability = ability+1;
						check_f -= 1;
					}
					else if(title[boci]=="����"&&check_f==1){
						ability = ability+1;
						check_f -= 1;
					}
		cout<<"�ޯ��I��: "<<ability<<"�I";
	set.go(25,12);//{"","�K�P","�ɵP","�ȵP","���P","�ժ�","�p��","�W�Z","����"};
 					if(title[boci]=="�ɵP"&&check_s==1){
						Attributes = Attributes+1;
						check_s -= 1;
					}
					else if(title[boci]=="�ȵP"&&check_s==1){
						Attributes = Attributes+1;
						check_s -= 1;
					}
					else if(title[boci]=="���P"&&check_s==1){
						Attributes = Attributes+1;
						check_s -= 1;
					}
					else if(title[boci]=="�ժ�"&&check_s==1){
						Attributes = Attributes+1;
						check_s -= 1;
					}
					else if(title[boci]=="�p��"&&check_s==1){
						Attributes = Attributes+1;
						check_s -= 1;
					}
					else if(title[boci]=="�W�Z"&&check_s==1){
						Attributes = Attributes+1;
						check_s -= 1;
					}
					else if(title[boci]=="����"&&check_s==1){
						Attributes = Attributes+1;
						check_s -= 1;
					}
		cout<<"�ݩ��I��: "<<Attributes<<"�I";
	set.go(25,13);cout<<"�_��: "<<ruby<<"   ";
	set.go(25,14);
		if(mis==0||mis==5)
			cout<<" no mission";
		else if(mis==2)
			cout<<"�����T���u"<<kill_a;
		else if(mis==3)
			cout<<"�����T���L��"<<kill_b;
        else if(mis==4)
			cout<<"�����T���j��"<<kill_c;
        
}
//----------------------------------------------------------------
//                        ��������==room1
//----------------------------------------------------------------
void room1(){
    ui set;
	int key=0;
	string icon=Profess[Profession].icon;
	
	system("color 0F");
	system("cls");
	set.printmap();
	
	set.go(23,10);printf("��");
	set.go(plx,ply);set.color(240);cout<<icon; 
	set.go(10,11);set.color(15);cout<<"��";
	set.go(10,3);set.color(15);cout<<"�Z";
	set.go(10,-1);
	
	printright();
	check=1;
	set.go(8,-1);printf("��������");
	while(plx!=24||ply!=10)									//��?��? 
	{
		if(kbhit)
		{
			key=getch();
			if((key=='W'||key=='w')&&!set.goout(plx,ply-1))
			{
				set.go(plx,ply);
                set.color(15);printf("  ");
				ply--;
			}
			if((key=='S'||key=='s')&&!set.goout(plx,ply+1))
			{
				set.go(plx,ply);
                set.color(15);printf("  ");
				ply++;
			}
			if((key=='A'||key=='a')&&!set.goout(plx-1,ply))
			{
				set.go(plx,ply);
                set.color(15);printf("  ");
				plx--;
			}	
			if((key=='D'||key=='d'))
			{
				if(!set.goout(plx+1,ply)||ply==10)
				{
					set.go(plx,ply);
                    set.color(15);printf("  ");
					plx++;
				}
			}
			if(key==9)
			{
				openbag();
				room1();
				return;
			}
			if(key==112){
				at();
				room1();
				return;
			}
			if(key==111){
				st();
				room1();
				return;
			}

            if(key==46){
                set.go(2,15);
                cout<<"�п�J������O: ";
                cin>>m;
                if(m =='f'){
                    fa();
                    //room1();
                    return;
                }else if(m=='w'){
                    we();
                   // room1();
                    return;
                } else if(m =='n'){
                    npc();
                    //room1();
					return;
                } else if(m =='g'){
                    fig();
                    //room1();
					return;
                }else if(m=='1'){
                    room1();
					return;
                }else if(m=='2'){
                    room2();
					return;
                }else if(m=='4'){
					map();
					return;
				}
            }



			set.go(23,10);
			set.color(15);printf("��");	
			set.go(10,11);set.color(15);cout<<"��";
			set.go(10,3);set.color(15);cout<<"�Z";
			
			if(plx!=24||ply!=10)
			{
				set.go(plx,ply);set.color(240);cout<<icon;
			}
				
			if(plx==10&&ply==11)
			{
				fa();
				ply--;
				room1();
				return;
			}
			if(plx==10&&ply==3)
			{
				we();
				ply++;
				room1();
				return;
			}
		}
		Sleep(125);
	}
    plx = 1,ply = 10;
}
//----------------------------------------------------------------
//                            ���~==room2
//----------------------------------------------------------------
void room2()
{
    ui set;
	int key=0;
	string icon=Profess[Profession].icon;
	check  = 4;
	system("color 0F");
	system("cls");
	set.printmap();
	
	printright();
		
	set.go( 0,10);printf("��");
	set.go( 8,-1);printf("���Ȥ���");
	set.go( 5,11);set.color(15);cout<<"npc";
	set.go( 5,3);set.color(15);cout<<"���~";
	set.go(plx,ply);set.color(240);cout<<icon; 
	
		
	while(plx!=-1||ply!=10)								//���ǩ�? 
	{
		if(kbhit)
		{
            key=getch();
			if((key=='W'||key=='w')&&!set.goout(plx,ply-1))
			{
				set.go(plx,ply);
                set.color(15);printf("  ");
				ply--;
			}
			if((key=='S'||key=='s')&&!set.goout(plx,ply+1))
			{
				set.go(plx,ply);
                set.color(15);printf("  ");
				ply++;
			}
			if((key=='D'||key=='d')&&!set.goout(plx+1,ply))
			{
				set.go(plx,ply);
                set.color(15);printf("  ");
				plx++;
			}	
			if((key=='A'||key=='a'))
			{
				if(!set.goout(plx-1,ply)||ply==10&&plx>=0)
				{
					set.go(plx,ply);
                set.color(15);printf("  ");
					plx--;
				}
			}
			set.go(0,10);
			set.color(15);printf("��");	
            set.go(5,11);set.color(15);cout<<"npc";
			if(key==9)
			{
				openbag();
				room2();
				return;
			}
			if(plx== 5&&ply==11){
				npc();
				ply--;
				room2();
				return;
			}
			
            if(plx== 5&&ply==3){
				fig();
				ply--;
				room2();
				return;
			}

			if(key==47){
				mi();
				ply--;
				room2();
				return;
			}
            
			if(key==46){
                set.go(2,15);
                cout<<"�п�J������O: ";
                cin>>m;
                if(m =='f'){
                    fa();
                    //room1();
                    return;
                }else if(m=='w'){
                    we();
                    //room1();
                    return;
                } else if(m =='n'){
                    npc();
                    //room1();
					 return;
                } else if(m =='g'){
                    fig();
                    //room1();
					 return;
                }else if(m=='1'){
                    room1();
					 return;
                }else if(m=='2'){
                    room2();
					 return;
                }else if(m=='4'){
					map();
					 return;
				}

            }
			
			if(plx!=-1||ply!=10)
			{
				set.go(plx,ply);set.color(240);cout<<icon;
			}
		}
		Sleep(125);
	}
    plx = 22,ply = 10;
}




void start(int n){
	ui set;
	if(mon[boci][n].alive!=1)
	{
		return;
	}
	if(plx==mon[boci][n].x&&ply==mon[boci][n].y)
	{
		fight(n);
		return;
	}
	set.color(15);
	set.go(mon[boci][n].x,mon[boci][n].y);
	cout<<monpic[mon[boci][n].type];
}
//----------------------------------------------------------------
//                             ���ǿ��
//----------------------------------------------------------------
void fight(int n)
{
    ui set;
	system("color 0F");
	system("cls");
	
	set.go(4,2);printf("�԰�");
	set.go(4,4);printf("�k�]�]����10��O�ȡ^");
	set.go(2,2);printf(">>");
	set.go(4,7);printf("���G");cout<<mon[boci][n].name;
	set.go(4,9);printf("�ͩR�ȡG");cout<<mon[boci][n].hp;
	set.go(4,10);printf("�ˮ`�ȡG");cout<<mon[boci][n].damage;
	set.go(4,11);printf("�K�˲v�G");cout<<mon[boci][n].unhurt;
	set.go(4,12);printf("�����v�G");cout<<mon[boci][n].crit;
	set.go(4,13);printf("�{�ײv�G");cout<<mon[boci][n].eva;
	
	set.go(4,14);printf("�����_��:");cout<<mon[boci][n].ruby;
	 
	int key=0;
	int a=1;
	while(key!=13)
	{
		key=getch();
		if(key=='w'||key=='W'||key=='s'||key=='S')
		{
			set.go(2,a*2);printf("  ");
			a=3-a;
			set.go(2,a*2);printf(">>");
		}
	}
	if(a==1)
	{
		ffight(n);
	}
	else if(a==2)
	{
		frun();
	}
	fig(); 
}
//----------------------------------------------------------------
//                            ���Ǩ��
//----------------------------------------------------------------
void ffight(int n)
{
    ui set;
	system("cls");system("color 0F");
	set.go(3,1);cout<<Profess[Profession].name;	
	set.go(12,1);cout<<mon[boci][n].name;
	
	set.go(2,3);cout<<"�ͩR�ȡG"<<hp();	
	set.go(11,3);cout<<"�ͩR�ȡG"<<mon[boci][n].hp;
	set.go(2,4);cout<<"��O�ȡG"<<sp();
	set.go(2,5);cout<<"�ˮ`�ȡG"<<damage();
	set.go(11,5);cout<<"�ˮ`�ȡG"<<mon[boci][n].damage;	
	set.go(2,6);cout<<"�K�˲v�G"<<unhurt(mon[boci][n].type)<<"%";
	set.go(11,6);cout<<"�K�˲v�G"<<mon[boci][n].unhurt<<"%";
	set.go(2,7);cout<<"�����v�G"<<crit()<<"%";
	set.go(11,7);cout<<"�����v�G"<<mon[boci][n].crit<<"%";
	set.go(2,8);cout<<"�{�ײv�G"<<eva()<<"%";
	set.go(11,8);cout<<"�{�ײv�G"<<mon[boci][n].eva<<"%";
	
	set.go(4,10);printf("���������]�ˮ`��25�A����2��O�ȡ^");
	set.go(4,11);printf("���q�����]�ˮ`��80�A����8��O�ȡ^");
	set.go(4,12);printf("�j�O�����]�ˮ`��160�A����20��O�ȡ^");
	set.go(4,13);printf("�h�X");
	int a=1;
	int key=0;
	set.go(2,9+a);printf(">>");

	while(key!=13){
			key=getch();
			set.go(2,9+a);printf("  ");
			if(key=='w'||key=='W')
			{
				a--;
				if(a<1)a+=4;
			}
			else if(key=='s'||key=='S')
			{
				a++;
				if(a>4)a-=4;
			}
			set.go(2,9+a);printf(">>");
	} 
	if(a==4){
		fight(n);return;
	}
	if(a==1){
		if(getrand(1,100)>mon[boci][n].eva)
		{
			float b=(damage()+25)*(100-mon[boci][n].unhurt)/100;
			if(getrand(1,100)<crit())
			{
				b*=1.5;
				set.go(1,2);printf(" ���� ");  Sleep(500);
			}
			mon[boci][n].hp-=b;
		}
		else{
			set.go(13,2);printf(" �{�� ");  Sleep(500);
		} 
		Profess[Profession].SP-=2; 

		if(sp()<=0)
		{
			system("cls");
			system("color 0F");
			set.go(6,6);printf("�A�֦��F");
			room1();	
		}
	}
	if(a==2)
	{
		if(getrand(1,100)>mon[boci][n].eva)
		{
			float b=(damage()+80)*(100-mon[boci][n].unhurt)/100;
			if(getrand(1,100)<crit())
			{
				b*=1.5;
				set.go(1,2);printf(" ���� ");  Sleep(500);
			}
			mon[boci][n].hp-=b;
		}
		else
		{
			set.go(13,2);printf(" �{�� ");  Sleep(500);
		} 
		Profess[Profession].SP-=8; 
		if(sp()<=0)
		{
			system("cls");
			system("color 0F");
			set.go(6,6);printf("�A�֦��F�C");
			room1();
		}
	}
	if(a==3)
	{
		if(getrand(1,100)>mon[boci][n].eva)
		{
			float b=(damage()+160)*(100-mon[boci][n].unhurt)/100;
			if(getrand(1,100)<crit())
			{
				b*=1.5;
				set.go(1,2);printf(" ���� "); Sleep(500);
			}
			mon[boci][n].hp-=b;
		}
		else
		{
			set.go(13,2);printf(" �{�� ");  Sleep(500);
		} 
		Profess[Profession].SP-=20;
		if(sp()<=0)
		{
			system("cls");
			system("color 0F");
			set.go(6,6);printf("�A�֦��F�C");
			room1();
		} 

	}
	
	if(getrand(1,100)>eva())
	{
		float c=mon[boci][n].damage*(100-unhurt(mon[boci][n].type))/100;
		if(getrand(1,100)<mon[boci][n].crit)
		{
			c*=1.5;
			set.go(10,2);printf(" ���� "); Sleep(500);
		}
		Profess[Profession].HP-=c;
	}
	else
	{
		set.go(4,2);printf(" �{�� ");  Sleep(500);
	} 
	if(mon[boci][n].hp>0&&hp()>0&&sp()>0) 
	{
		ffight(n);
		return; 
	}

	if(mon[boci][n].type==1){
		kill_a -=1; 
	}
	if(mon[boci][n].type==2){
		kill_b -=1; 
	}
	if(mon[boci][n].type==3){
		kill_c -=1; 
	}


	if(mon[boci][n].hp<=0)
	{
		mon[boci][n].alive=0;
		system("cls");
		system("color 0F");
		set.go(6,6);printf("�Ǫ��Q�����F�I��o%d���_�ۡI",mon[boci][n].ruby);
		ruby+=mon[boci][n].ruby; 

		Sleep(1000);
		if(n==3&&boci!=8){ 
			boci++;
			check_f++;
			check_s++;
		}
		if(mon[boci][1].alive+mon[boci][2].alive+mon[boci][3].alive==6)
		{
			mon[boci][1].alive=1;
			mon[boci][2].alive=1;
			mon[boci][3].alive=1;
		}

	}
	if(hp()<=0)
	{
		system("cls");
		system("color 0F");
		set.go(6,6);printf("�A�묹�F�C");
		Profess[Profession].HP = 200;
		room1();
	} 
} 
void frun()
{
    ui set;
	Profess[Profession].SP-=10;
	plx--;
	if(sp()<=0)
	{
		system("cls");
		system("color 0F");
		set.go(6,6);printf(" �A�֦��F ");
		Profess[Profession].SP = 200;
		room1();
	} 
}
//----------------------------------------------------------------
//                             ���ǩж�
//----------------------------------------------------------------
void fig(){
	check  = 5;
	ui set;
	int key=0;
	string icon=Profess[Profession].icon;
	
	system("color 0F");
	system("cls");
	set.printmap();
	
	set.go( 0,10);printf("��");
	set.go( 8,-1);printf("���~");
	set.go(plx,ply);set.color(240);cout<<icon; 
	
		
	while(plx!=-1||ply!=10)								//���ǩж� 
	{
		for(int i=1;i<=3;i++) start(i);
		if(kbhit)
		{
			 key=getch();
			if((key=='W'||key=='w')&&!set.goout(plx,ply-1))
			{
				set.go(plx,ply);
                set.color(15);printf("  ");
				ply--;
			}
			if((key=='S'||key=='s')&&!set.goout(plx,ply+1))
			{
				set.go(plx,ply);
                set.color(15);printf("  ");
				ply++;
			}
			if((key=='D'||key=='d')&&!set.goout(plx+1,ply))
			{
				set.go(plx,ply);
                set.color(15);printf("  ");
				plx++;
			}	
			if((key=='A'||key=='a'))
			{
				if(!set.goout(plx-1,ply)||ply==10&&plx>=0)
				{
					set.go(plx,ply);
                set.color(15);printf("  ");
					plx--;
				}
			}
			set.go(0,10);
			set.color(15);printf("��");	
			if(key==9)
			{
				openbag();
				fig();
				return;
			}
			if(plx!=-1||ply!=10)
			{
				set.go(plx,ply);set.color(240);cout<<icon;
			}
             if(key==46){
                set.go(2,15);
                cout<<"�п�J������O: ";
                cin>>m;
                if(m =='f'){
                    fa();
                    //room1();
                    return;
                }else if(m=='w'){
                    we();
                    //room1();
                    return;
                } else if(m =='n'){
                    npc();
                    //room1();
					return;
                } else if(m =='g'){
                    fig();
                    //room1();
					return;
                }else if(m=='1'){
                    room1();
					return;
                }else if(m=='2'){
                    room2();
					return;
                }else if(m=='4'){
					map();
					return;
				}

            }
		}
		
		Sleep(125);
	}
    plx = 5,ply = 5;
}
//----------------------------------------------------------------
//                             �Z���ж�
//----------------------------------------------------------------
void we(){
	ui set;
	int key=0;
	string icon=Profess[Profession].icon;
	
	check = 2;
	system("color 0F");
	system("cls");
	set.printmap();
	
	set.go( 0,10);printf("��");
	set.go( 8,-1);printf("�Z��");
    set.go(10,10);printf("�Z���ө�");
	set.go(plx,ply);set.color(240);cout<<icon; 
	
		
	while(plx!=-1||ply!=10)								//we
	{
		if(kbhit)
		{
            key=getch();
			if((key=='W'||key=='w')&&!set.goout(plx,ply-1))
			{
				set.go(plx,ply);
                set.color(15);printf("  ");
				ply--;
			}
			if((key=='S'||key=='s')&&!set.goout(plx,ply+1))
			{
				set.go(plx,ply);
                set.color(15);printf("  ");
				ply++;
			}
			if((key=='D'||key=='d')&&!set.goout(plx+1,ply))
			{
				set.go(plx,ply);
                set.color(15);printf("  ");
				plx++;
			}	
			if((key=='A'||key=='a'))
			{
				if(!set.goout(plx-1,ply)||ply==10&&plx>=0)
				{
					set.go(plx,ply);
                set.color(15);printf("  ");
					plx--;
				}
			}
			set.go(0,10);
			set.color(15);printf("��");	
			if(key==9)
			{
				openbag();
				fig();
				return;
			}
			if(plx!=-1||ply!=10)
			{
				set.go(plx,ply);set.color(240);cout<<icon;
			}
            if(plx==10&&ply==10){
                weshop();
                we();
                return;
            }
             if(key==46){
                set.go(2,15);
                cout<<"�п�J������O: ";
                cin>>m;
                if(m =='f'){
                    fa();
                    //room1();
                    return;
                }else if(m=='w'){
                    we();
                    //room1();
                    return;
                } else if(m =='n'){
                    npc();
                    //room1();
					 return;
                } else if(m =='g'){
                    fig();
                    //room1();
					 return;
                }else if(m=='1'){
                    room1();
					 return;
                }else if(m=='2'){
                    room2();
					 return;
                }else if(m=='4'){
					map();
					 return;
				}

            }
		}
		
		Sleep(125);
	}
    plx = 5,ply = 5;
}

//----------------------------------------------------------------
//                             ����ө�
//----------------------------------------------------------------
void fa(){
	ui set;
	int key=0;
	string icon=Profess[Profession].icon;
	check = 3;
	system("color 0F");
	system("cls");
	set.printmap();
	
	set.go( 0,10);printf("��");
	set.go( 8,-1);printf("����");
    set.go(10,10);printf("����ө�");
	set.go(plx,ply);set.color(240);cout<<icon; 
	
		
	while(plx!=-1||ply!=10)								//we
	{
		if(kbhit)
		{
            key=getch();
			if((key=='W'||key=='w')&&!set.goout(plx,ply-1))
			{
				set.go(plx,ply);
                set.color(15);printf("  ");
				ply--;
			}
			if((key=='S'||key=='s')&&!set.goout(plx,ply+1))
			{
				set.go(plx,ply);
                set.color(15);printf("  ");
				ply++;
			}
			if((key=='D'||key=='d')&&!set.goout(plx+1,ply))
			{
				set.go(plx,ply);
                set.color(15);printf("  ");
				plx++;
			}	
			if((key=='A'||key=='a'))
			{
				if(!set.goout(plx-1,ply)||ply==10&&plx>=0)
				{
					set.go(plx,ply);
                set.color(15);printf("  ");
					plx--;
				}
			}
			set.go(0,10);
			set.color(15);printf("��");	
			if(key==9)
			{
				openbag();
				fig();
				return;
			}
			if(plx!=-1||ply!=10)
			{
				set.go(plx,ply);set.color(240);cout<<icon;
			}
            if(plx==10&&ply==10){
                fangshop();
                fa();
                return;
            }
             if(key==46){
                set.go(2,15);
                cout<<"�п�J������O: ";
                cin>>m;
                if(m =='f'){
                    fa();
                    //room1();
                    return;
                }else if(m=='w'){
                    we();
                    //room1();
                    return;
                } else if(m =='n'){
                    npc();
                    //room1();
					return;
                } else if(m =='g'){
                    fig();
                    //room1();
					return;
                }else if(m=='1'){
                    room1();
					return;
                }else if(m=='2'){
                    room2();
					return;
                }else if(m=='4'){
					map();
					return;
				}

            }
		}
		
		Sleep(125);
	}
    plx = 5,ply = 5;
}
//----------------------------------------------------------------
//                        openbag
//----------------------------------------------------------------
void openbag()
{
    ui set;
	system("color 0F");
	system("cls");
	
	set.go(8,-1);
	printf("�I�]");
	set.go(2,1);
	set.color(15);
	printf("���~�W��  ���~�ƭ�  ���~���A"); 
	for(int i=1;i<=arms[0]+fangbag[0];i++)
	{
		if(i<=arms[0])
		{
			set.go( 2,i+1);cout<<ARMM[arms[i]].name;
			set.go( 7,i+1);cout<<ARMM[arms[i]].damage<<"%";
			set.go(12,i+1);if(nowwu==i)printf("�w�˳�");else printf("���˳�");
		}
		else if(i<=arms[0]+fangbag[0])
		{
			set.go( 2,i+1);cout<<fangju[fangbag[i-arms[0]]].name;
			set.go( 7,i+1);cout<<fangju[fangbag[i-arms[0]]].fangku<<"%"<<fangju[fangbag[i-arms[0]]].fangjiang<<"%"<<fangju[fangbag[i-arms[0]]].fangzhu<<"%";
			set.go(12,i+1);
			if(fangju[fangbag[i-arms[0]]].type==1)
			{
				if(nowfang.dun==i)
				{
					printf("�w�˳�");
				}
				else
				{
					printf("���˳�");
				}
			}
			if(fangju[fangbag[i-arms[0]]].type==2)
			{
				if(nowfang.ku==i)
				{
					printf("�w�˳�");
				}
				else
				{
					printf("���˳�");
				}					
			}
			if(fangju[fangbag[i-arms[0]]].type==3)
			{
				if(nowfang.jia==i)
				{
					printf("�w�˳�");
				}
				else
				{
					printf("���˳�");
				}					
			}				
		}
	}
	printright();
	int a=1;
	set.go(0,a+1);printf(">>");
	int key=0;
	while(key!=27)
	{
		key=getch();
		if((key=='W'||key=='w')&&arms[0]+fangbag[0]>0)
		{
			set.go(0,a+1);printf("  ");
			a--;
			if(a<1)
			{
				a+=arms[0]+fangbag[0];
			}
		}
		else if((key=='S'||key=='s')&&arms[0]+fangbag[0]>0)
		{
			set.go(0,a+1);printf("  ");
			a++;
			if(a>arms[0]+fangbag[0])
			{
				a-=arms[0]+fangbag[0];
			}			
		}
		else if(key==13&&arms[0]+fangbag[0]>0)
		{
			if(a<=arms[0])
			{
				if(nowwu!=a)
				{
					if(nowwu!=-1)
					{
						set.go(12,nowwu+1);
						printf("���˳�");
					}
					nowwu=a;
					set.go(12,nowwu+1);
					printf("�w�˳�");					
				}
				else
				{
					set.go(12,nowwu+1);printf("���˳�");nowwu=-1;
				}
			}
			else if(a<=arms[0]+fangbag[0])
			{
				if(fangju[fangbag[a-arms[0]]].type==1)
				{
					if(nowfang.dun!=a)
					{
						if(nowfang.dun!=-1)
						{
							set.go(12,nowfang.dun+1);
							printf("���˳�");
						}
						nowfang.dun=a;
						set.go(12,nowfang.dun+1);
						printf("�w�˳�");
					}
					else
					{
						set.go(12,nowfang.dun+1);printf("���˳�");nowfang.dun=-1;
					}
				}
				else if(fangju[fangbag[a-arms[0]]].type==2)
				{
					if(nowfang.ku!=a)
					{
						if(nowfang.ku!=-1)
						{
							set.go(12,nowfang.ku+1);
							printf("���˳�");
						}
						nowfang.ku=a;
						set.go(12,nowfang.ku+1);
						printf("�w�˳�");
					}
					else
					{
						set.go(12,nowfang.ku+1);printf("���˳�");nowfang.ku=-1;
					}					
				}
				else if(fangju[fangbag[a-arms[0]]].type==3)
				{
					if(nowfang.jia!=a)
					{
						if(nowfang.jia!=-1)
						{
							set.go(12,nowfang.jia+1);
							printf("���˳�");
						}
						nowfang.jia=a;
						set.go(12,nowfang.jia+1);
						printf("�w�˳�");
					}
					else
					{
						set.go(12,nowfang.jia+1);printf("���˳�");nowfang.jia=-1;
					}			
				}
				
			}
		}
		else if(key==27)
		{
			return;
		}
		else if(key==8&&arms[0]+fangbag[0]>0)
		{
			openbag();
			return;
		}
		set.go(0,a+1);printf(">>");
		
		printright();
	}
}
//----------------------------------------------------------------
//                             �ݩ��I��
//----------------------------------------------------------------
void  at(){
	ui set;
	system("cls");
	system("color 0F");
	set.go(2,6);
	while(1){
		set.go(15,5);cout<<"�A�֦����I�� "<<Attributes;
		set.go(15,6);cout<<"HP: "<<Profess[Profession].HP;
		set.go(15,7);cout<<"SP: " <<Profess[Profession].SP;
		set.go(15,8);cout<<"damage: "<<Profess[Profession].damage;
		set.go(2,5);cout<<"�п�J�A�Q���ɪ��ƭ�: ";
		set.go(2,6);cin>>up;
		if(up=='r')
			break;
		if(up == 'h'&&Attributes>0){
			Profess[Profession].HP *=2;
			Attributes = Attributes - 1;
			set.go(2,7);cout<<"successfully updated";
		}
		else if(up == 's'&&Attributes>0){
			Profess[Profession].SP *=2;
			Attributes = Attributes - 1;
			set.go(2,7);cout<<"successfully updated";
		}
		else if(up == 'd'&& Attributes>0){
			Profess[Profession].damage *=2;
			Attributes = Attributes - 1;
			set.go(2,7);cout<<"successfully updated";
		}else if(Attributes==0){
			set.go(2,7);cout<<"�A���ݩ��I�Ƥ���         ";
		}
	}
	maxhp = Profess[Profession].HP;
}
//----------------------------------------------------------------
//                             �ޯ��I��
//----------------------------------------------------------------
void st(){
	ui set;
	int point_ch = 0;
	system("cls");
	system("color 0F");
	while(1){

		set.go(2,2);cout<<"�A�֦����ޯ�";
		set.go(3,3);
				if(boci==1){
					cout<<skill[Profession].name1<<" "<<skill[Profession].rank1<<"�� "<<"�ˮ`"<<skill[Profession].damage1;
					point_ch++;
				}else if(boci==2){
					cout<<skill[Profession].name1<<" "<<skill[Profession].rank1<<"�� "<<"�ˮ`"<<skill[Profession].damage1;
					set.go(3,4);cout<<skill[Profession].name2<<" "<<skill[Profession].rank2<<"�� "<<"�ˮ`"<<skill[Profession].damage2;
					point_ch++;
				}else if(boci==3){
					cout<<skill[Profession].name1<<" "<<skill[Profession].rank1<<"�� "<<"�ˮ`"<<skill[Profession].damage1;
					set.go(3,4);cout<<skill[Profession].name2<<" "<<skill[Profession].rank2<<"�� "<<"�ˮ`"<<skill[Profession].damage2;
					set.go(3,5);cout<<skill[Profession].name3<<" "<<skill[Profession].rank3<<"�� "<<"�ˮ`"<<skill[Profession].damage3;
					point_ch++;
				} else if(boci==4){
					cout<<skill[Profession].name1<<" "<<skill[Profession].rank1<<"�� "<<"�ˮ`"<<skill[Profession].damage1;
					set.go(3,4);cout<<skill[Profession].name2<<" "<<skill[Profession].rank2<<"�� "<<"�ˮ`"<<skill[Profession].damage2;
					set.go(3,5);cout<<skill[Profession].name3<<" "<<skill[Profession].rank3<<"�� "<<"�ˮ`"<<skill[Profession].damage3;
					set.go(3,6);cout<<skill[Profession].name4<<" "<<skill[Profession].rank4<<"�� "<<"�ˮ`"<<skill[Profession].damage4;
					point_ch++;
				}
		set.go(23,2);cout<<"�п�J�ɯŪ��ޯ�";
		set.go(25,2);cout<<"�A�֦����ޯ��I�� "<<ability;
		set.go(23,3);cin>>l;cout<<"  ";

		if(l=='r')
			break;
		set.go(23,4);
		if(point_ch>0){
			if(l == '1' && ability > 0&&boci>=1){
				skill[Profession].rank1 += 1;
				skill[Profession].damage1 *= 2;
				ability = ability - 1;
				cout<<"upgrade successfully";
			}else if(l == '1' && ability == 0)
				cout<<"Not enough points";

			if(l == '2'&& ability > 0&&boci>=2){
				skill[Profession].rank2 += 1;
				skill[Profession].damage2 *= 2;
				ability = ability - 1;
				cout<<"upgrade successfully";
			}else if(l == '2' && ability == 0)
				cout<<"Not enough points";
			
			if(l == '3'&& ability > 0&&boci>=3){
				skill[Profession].rank3 += 1;
				skill[Profession].damage3 *= 2;
				ability = ability - 1;
				cout<<"upgrade successfully";
			}else  if(l == '3' && ability == 0)
				cout<<"Not enough points";
			
			if(l == '4'&& ability > 0&&boci>=4){
				skill[Profession].rank4 += 1;
				skill[Profession].damage4 *= 2;
				ability = ability - 1;
				cout<<"upgrade successfully";
			}else if(l == '4' && ability == 0)
				cout<<"Not enough points";
		}else 
			cout<<"you dont have skill";
	}
}
//----------------------------------------------------------------
//                             ���ȵ��⭶��
//----------------------------------------------------------------
void mi(){
	ui set;
	system("cls");
		while(1){
			set.go(2,10);cout<<"�A�֦� "<<ruby<<"���_��";
			set.go(2,5);cout<<"�п�J�������ȫ��O";
			set.go(2,6);
			cin>>np;
			cout<<"                ";
			if(np=="aflash"&&kill_a==0){
				ruby = ruby+1000;
				cout<<"���ȧ����o��1000�_�ۼ��y";
				cout<<"                        ";
			}
			if(np=="bflash"&&kill_b==0){
				ruby = ruby+1000;
				cout<<"���ȧ����o��1000�_�ۼ��y";
				cout<<"                        ";
			}
			if(np=="cflash"&&kill_c==0){
				ruby = ruby+1000;
				cout<<"���ȧ����o��1000�_�ۼ��y";
				cout<<"                        ";
			}
			if(np!="aflash"&&np!="bflash"&&np!="cflash"){
				cout<<"��J���~�Υ��������� ";
				cout<<"                        ";
			}
			if(np=="out")
				break;

		}
}

int hp(){
	int k=Profess[Profession].HP;
	return k;
}

int sp(){
	int k=Profess[Profession].SP;
	return k;
}

int damage(){
	int k=Profess[Profession].damage;
	k+=ARMM[arms[nowwu]].damage;
	return k;
}

int unhurt(int m){
	int k=Profess[Profession].EVA;
	if(m==2)
	{
		if(nowfang.dun!=-1){
			k += fangju[fangbag[nowfang.dun-arms[0]]].fangjiang;
		}
		if(nowfang.jia!=-1){
			k += fangju[fangbag[nowfang.jia-arms[0]]].fangjiang;
		}
		if(nowfang.ku!=-1){
			k += fangju[fangbag[nowfang.ku-arms[0]]].fangjiang;
		}
	}
	if(m==1)
	{
		if(nowfang.dun!=-1)
		{
			k += fangju[fangbag[nowfang.dun-arms[0]]].fangku;
		}
		if(nowfang.jia!=-1)
		{
			k += fangju[fangbag[nowfang.jia-arms[0]]].fangku;
		}
		if(nowfang.ku!=-1)
		{
			k += fangju[fangbag[nowfang.ku-arms[0]]].fangku;
		}		
	}
	if(m==3)
	{
		if(nowfang.dun!=-1)
		{
			k += fangju[fangbag[nowfang.dun-arms[0]]].fangzhu;
		}
		if(nowfang.jia!=-1)
		{
			k += fangju[fangbag[nowfang.jia-arms[0]]].fangzhu;
		}
		if(nowfang.ku!=-1)
		{
			k += fangju[fangbag[nowfang.ku-arms[0]]].fangzhu;
		}
	}
	return k;
}

int crit(){
	int k = Profess[Profession].CR;
	return k;
}

int eva(){
	int k = Profess[Profession].ER;
	return k;
}

