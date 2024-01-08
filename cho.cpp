#include "ui.h"
#include <conio.h>
#include <windows.h>
#define getrand(a,b) (rand()%b+a)//隨機取得機率
//----------------------------------------------------------------
//                            宣告預設值
//----------------------------------------------------------------
int plx=10,ply=8;		//玩家初始坐標 
int Profession;			//職業
int maxhp;				//max HP
int ruby = 2000;		//預設錢幣數量
int arms[10];			//武器背包
int fangbag[10];		//玩家防具背包
int nowwu=-1;			//玩家預設武器狀態
int boci = 1;			//怪物刷新次數
int mis;				//mission
int check;				//check in which map
int ability = 1;		//技能點數
int Attributes = 1;		//屬性點數
int check_f;			//避免判斷升級的地方重復加取用於技能
int check_s;			//避免判斷升級的地方重復加取用於屬性
string title[9] = {"","鐵牌","銅牌","銀牌","金牌","白金","鑽石","超凡","神話"}; //等級系統
char m;					//跳轉指令的變數(change string)
char up;				//屬性點數內的指令變數
char l;					//技能點數內的指令變數
string np;				//用於npc商店				
int kill_a;				//任務用的殺死骷
int kill_b;				//任務用的殺死殭
int kill_c;				//任務用的殺死蜘
//----------------------------------------------------------------
//                             定義函式
//----------------------------------------------------------------
void room1();			//村莊中心
void room2();			//任務中心
void fig();				//打怪房間
void start(int);		//怪物初始化
void fight(int);		//選擇是否打怪
void openbag();			//open bag
void frun();			//for run
void map();				//世界地圖
void we();				//weapon
void fa();				//防具
void ffight(int n);		//打怪函式
void at();				//atibility points
void st();				//still points
void mi();				//任務完成頁面
int hp();				//hp
int unhurt(int m);		//免傷率
int eva();				//閃避率
int crit();				//爆擊率
int damage();			//傷害
int sp();				//體力
//----------------------------------------------------------------
//                            預設怪物數值
//----------------------------------------------------------------
string monpic[4]={"","骷","殭","蛛"}; 
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
	{}, //{" xxxx ", /*種類*/, /*掉落*/,/*寶石*/,/*傷害*/,/*免傷*/,/*暴擊*/,/*閃避*/,/*x*/ ,/*y*/ ,/*alive*/,/*生命*/},
	{
		{}, 
		{"竹箭骷弓", 1, 5,30,10,10,10,10, 5, 5,1,200},
		{"竹甲殭尸", 2, 0,25, 5,10,10,10, 5,10,1,180},
		{"竹甲蜘蛛", 3, 0,30, 5,10,10,10,9, 5,1,160}, 
	},
	{
		{},
		{"石箭骷弓", 1, 5,45,25,15,15,15,10, 9,2,220},
		{"石甲殭尸", 2, 1,35,20,25,10,10, 5, 5,2,210},
		{"石甲蜘蛛", 3, 0,40,25,15,10,15,15, 9,2,200}, 
	},
	{
		{}, 
		{"鐵箭骷弓", 1/*種類*/, 6/*掉落*/,55/*寶石*/,40/*傷害*/,10/*免傷*/,15/*暴擊*/,15/*閃避*/, 7, 5,2,210/*生命*/},
		{"鐵甲殭尸", 2/*種類*/, 5/*掉落*/,50/*寶石*/,30/*傷害*/,15/*免傷*/,10/*暴擊*/,15/*閃避*/, 3, 3,2,230/*生命*/},
		{"鐵甲蜘蛛", 3/*種類*/, 0/*掉落*/,50/*寶石*/,25/*傷害*/,20/*免傷*/,20/*暴擊*/,9/*閃避*/,9,12,2,230/*生命*/},
	},
	{
		{}, 
		{"鋼甲骷弓", 1/*種類*/, 0/*掉落*/,50/*寶石*/,45/*傷害*/,20/*免傷*/,10/*暴擊*/,20/*閃避*/, 7, 3,2,255/*生命*/},
		{"鋼甲殭尸", 2/*種類*/, 3/*掉落*/,55/*寶石*/,45/*傷害*/,35/*免傷*/,15/*暴擊*/,15/*閃避*/, 3, 5,2,245/*生命*/},
		{"鋼甲蜘蛛", 3/*種類*/, 0/*掉落*/,55/*寶石*/,50/*傷害*/,20/*免傷*/,15/*暴擊*/,15/*閃避*/,9,9,2,250/*生命*/},
	},	
	{
		{}, 
		{"金甲骷弓", 1/*種類*/, 4/*掉落*/,50/*寶石*/,50/*傷害*/,40/*免傷*/,10/*暴擊*/,10/*閃避*/, 7, 3,2,255/*生命*/},
		{"金甲殭尸", 2/*種類*/, 0/*掉落*/,55/*寶石*/,45/*傷害*/,25/*免傷*/,15/*暴擊*/,20/*閃避*/, 3, 5,2,250/*生命*/},
		{"金甲蜘蛛", 3/*種類*/, 7/*掉落*/,50/*寶石*/,50/*傷害*/,20/*免傷*/,15/*暴擊*/,15/*閃避*/,9, 8,2,250/*生命*/},
	},
	{
		{}, 
		{"鑽甲骷弓", 1/*種類*/, 3/*掉落*/,55/*寶石*/,50/*傷害*/,40/*免傷*/,15/*暴擊*/,10/*閃避*/, 7, 3,2,265/*生命*/},
		{"鑽甲殭尸", 2/*種類*/, 0/*掉落*/,45/*寶石*/,45/*傷害*/,25/*免傷*/,15/*暴擊*/,25/*閃避*/, 3, 5,2,265/*生命*/},
		{"鑽甲蜘蛛", 3/*種類*/, 7/*掉落*/,50/*寶石*/,65/*傷害*/,20/*免傷*/,15/*暴擊*/,10/*閃避*/,9,10,2,265/*生命*/},
	},
	{
		{}, 
		{"無敵骷弓", 1/*種類*/, 6/*掉落*/,66/*寶石*/,35/*傷害*/,10/*免傷*/,15/*暴擊*/,10/*閃避*/, 7, 5,2,250/*生命*/},
		{"無敵殭尸", 2/*種類*/, 1/*掉落*/,66/*寶石*/,25/*傷害*/,15/*免傷*/,10/*暴擊*/,10/*閃避*/, 3, 3,2,250/*生命*/},
		{"無敵蜘蛛", 3/*種類*/, 0/*掉落*/,66/*寶石*/,25/*?害*/,10/*免傷*/,20/*暴擊*/,10/*閃避*/,11,10,2,250/*生命*/},	
	}	
}; 

//----------------------------------------------------------------
//                             預設職業資料
//----------------------------------------------------------------
struct Prof{
	string name;	//名稱
	int HP; 		//生命值
	int SP;			//體力
	int damage;		//傷害值
    int EVA;		//免傷率
	int CR;			//暴擊率
	int ER;			//閃避率
	string icon;
}   Profess[5]= {
	{},
	{"弓箭",400,225,130,16,20,15,"弓"},
	{"戰士",600,210,120,22,30,10,"戰"},
	{"劍士",500, 175,115,30,25, 5,"劍"},
	{"刺客",1600,1550,2000,20,40,25,"刺"},
};
//----------------------------------------------------------------
//                             技能
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
	{"精準強化","百步穿楊","霸王箭","終極之弓",1,1,1,1,10,20,30,40},
	{"粉碎","激勵","反射之盾","終極之釜",1,1,1,1,10,20,30,40},
	{"魔天一擊","劍氣縱橫","雷鳴之劍","無雙劍舞",1,1,1,1,10,20,30,40},
	{"幻化術","雙飛斬","精準暗器","極速暗殺",1,1,1,1,10,20,30,40},
};
//----------------------------------------------------------------
//                             預設武器
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
	{"石箭",25, 70,0,1},
	{"鐵箭",35,130,0,1},
	{"鑽箭",55,220,0,1},
	
	{"石刀",25, 70,0,2},
	{"鐵刀",35,130,0,2},
	{"鑽刀",55,220,0,2},
	
	{"木劍",25, 70,0,3},
	{"石劍",35,130,0,3},
	{"鑽劍",55,220,0,3},
	
	{"石匕",25, 65,0,1},
	{"鐵匕",35,125,0,1},
	{"鑽匕",55,230,0,1},
};
//----------------------------------------------------------------
//                          預設防具
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
	{"木盾",11,10, 6,80,0,1,1},
	
	{"鐵褲", 7,11, 5,90,0,2,1},
	{"鑽褲",12,16, 6,175,0,2,2},
	
	{"鐵甲",11, 5,12,120,0,3,1},
	{"鑽甲",16, 6,17,200,0,3,2},	
};
//----------------------------------------------------------------
//                             現在裝備的防具
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
	printf("請選擇你任務：");
	set.go(2,2);
	printf("     殺死3隻骷");
	set.go(2,3);
	printf("     殺死3隻殭屍");
	set.go(2,4);
	printf("     殺死3隻蜘蛛");
    set.go(2,5);
	printf("     放棄任務");
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
//                             世界地圖
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
			set.go(16,0);set.color(12);cout<<"*";//野外
			set.go(10,15);
			set.color();
		}
		
	cout<<"請輸入指令: ";
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
//                            選擇職業
//-----------------------------------------------------------------------------------
void cho()
{
	ui set;
	system("cls");//清空畫面
	set.go(0,0);
	cout<<("請選擇你的職業：");
	set.go(2,1);
	cout<<("職業  生命值  體力值  傷害值 免傷率%%  爆擊率%%   閃避率%%   圖標");	
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
//                      執行遊戲內容的主程式
//----------------------------------------------------------------
void gaming(){
	ui set;
	system("cls");
	set.printmap();
	string icon = Profess[Profession].icon;
	int plx = 1,ply = 8;
	int key = 0;

	set.go(25,0);cout<<"職業: "<<Profess[Profession].name;
	set.go(25,1);cout<<"生命值: "<<Profess[Profession].HP;
	set.go(25,2);cout<<"體力值: "<<Profess[Profession].SP;
	set.go(25,4);cout<<"傷害值: "<<Profess[Profession].damage;
    set.go(26,5);cout<<"免傷率："<<Profess[Profession].EVA;
	set.go(25,6);cout<<"爆擊率: "<<Profess[Profession].CR;
	set.go(25,7);cout<<"閃避率: "<<Profess[Profession].ER;
	set.go(25,9);cout<<"紅寶石: "<<ruby;

    while(1){
        ui set;
		room1();
		room2();	
    }
   
}


//----------------------------------------------------------------
//                             武器商店
//----------------------------------------------------------------
void weshop()
{
    ui set;
	system("cls");
	system("color 0F");
	set.go(9,0);printf("武器商店"); 
	set.go(2,2);
	printf("名稱  傷害值  買價  ");	
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
					set.go(2,7);printf("你已經擁有此物品                                 ");
				}
			}
			else
			{
				set.go(2,7);printf("寶石不足                                            ");
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
//                             防具商店
//----------------------------------------------------------------
void fangshop()
{
    ui set;
	system("cls");
	system("color 0F");
	set.go(7,0);printf("防具商店"); 
	set.go(2,2);
	printf("名稱  防骷  防僵  防蛛  買價  ");
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
					set.go(2,9);printf("你已經擁有此物品                                 ");
				}
			}
			else
			{
				set.go(2,9);printf("寶石不足                                            ");
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
	set.go(25,0);cout<<"職業："<<Profess[Profession].name;
	set.go(25,1);cout<<"生命值："<<hp()<<"/"<<maxhp<<"   ";
	set.go(25,2);cout<<"體力值："<<sp()<<"   ";
	set.go(25,4);cout<<"傷害值："<<damage()<<"%  ";
    set.go(25,5);cout<<"免傷率："<<unhurt(1)<<"%/"<<unhurt(2)<<"%/"<<unhurt(3)<<"%";
	set.go(25,6);cout<<"暴擊率："<<crit()<<"%   ";
	set.go(25,7);cout<<"閃避率："<<eva()<<"%   ";
	set.go(25,8);
		if(boci==1){
			cout<<"具有技能: "<<skill[Profession].name1<<endl;
		}else if(boci==2){
			cout<<"具有技能: "<<skill[Profession].name1<<" "<<skill[Profession].name2<<endl;
		}else if(boci==3){
			cout<<"具有技能: "<<skill[Profession].name1<<" "<<skill[Profession].name2<<" "<<skill[Profession].name3<<endl;
		} else if(boci==4){
			cout<<"具有技能: "<<skill[Profession].name1<<" "<<skill[Profession].name2<<" "<<skill[Profession].name3<<" "<<skill[Profession].name4<<endl;
		}
	set.go(25,10);cout<<"稱號： "<<title[boci]<<Profess[Profession].name<<"  ";
	set.go(25,11);//{"","鐵牌","銅牌","銀牌","金牌","白金","鑽石","超凡","神話"};
 					if(title[boci]=="銅牌"&&check_f==1){
						ability = ability+1;
						check_f -= 1;
					}
					else if(title[boci]=="銀牌"&&check_f==1){
						ability = ability+1;
						check_f -= 1;
					}
					else if(title[boci]=="金牌"&&check_f==1){
						ability = ability+1;
						check_f -= 1;
					}
					else if(title[boci]=="白金"&&check_f==1){
						ability = ability+1;
						check_f -= 1;
					}
					else if(title[boci]=="鑽石"&&check_f==1){
						ability = ability+1;
						check_f -= 1;
					}
					else if(title[boci]=="超凡"&&check_f==1){
						ability = ability+1;
						check_f -= 1;
					}
					else if(title[boci]=="神話"&&check_f==1){
						ability = ability+1;
						check_f -= 1;
					}
		cout<<"技能點數: "<<ability<<"點";
	set.go(25,12);//{"","鐵牌","銅牌","銀牌","金牌","白金","鑽石","超凡","神話"};
 					if(title[boci]=="銅牌"&&check_s==1){
						Attributes = Attributes+1;
						check_s -= 1;
					}
					else if(title[boci]=="銀牌"&&check_s==1){
						Attributes = Attributes+1;
						check_s -= 1;
					}
					else if(title[boci]=="金牌"&&check_s==1){
						Attributes = Attributes+1;
						check_s -= 1;
					}
					else if(title[boci]=="白金"&&check_s==1){
						Attributes = Attributes+1;
						check_s -= 1;
					}
					else if(title[boci]=="鑽石"&&check_s==1){
						Attributes = Attributes+1;
						check_s -= 1;
					}
					else if(title[boci]=="超凡"&&check_s==1){
						Attributes = Attributes+1;
						check_s -= 1;
					}
					else if(title[boci]=="神話"&&check_s==1){
						Attributes = Attributes+1;
						check_s -= 1;
					}
		cout<<"屬性點數: "<<Attributes<<"點";
	set.go(25,13);cout<<"寶石: "<<ruby<<"   ";
	set.go(25,14);
		if(mis==0||mis==5)
			cout<<" no mission";
		else if(mis==2)
			cout<<"殺死三隻骷"<<kill_a;
		else if(mis==3)
			cout<<"殺死三隻殭屍"<<kill_b;
        else if(mis==4)
			cout<<"殺死三隻蜘蛛"<<kill_c;
        
}
//----------------------------------------------------------------
//                        村莊中心==room1
//----------------------------------------------------------------
void room1(){
    ui set;
	int key=0;
	string icon=Profess[Profession].icon;
	
	system("color 0F");
	system("cls");
	set.printmap();
	
	set.go(23,10);printf("門");
	set.go(plx,ply);set.color(240);cout<<icon; 
	set.go(10,11);set.color(15);cout<<"防";
	set.go(10,3);set.color(15);cout<<"武";
	set.go(10,-1);
	
	printright();
	check=1;
	set.go(8,-1);printf("村莊中心");
	while(plx!=24||ply!=10)									//整?房? 
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
                cout<<"請輸入跳轉指令: ";
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
			set.color(15);printf("門");	
			set.go(10,11);set.color(15);cout<<"防";
			set.go(10,3);set.color(15);cout<<"武";
			
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
//                            野外==room2
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
		
	set.go( 0,10);printf("門");
	set.go( 8,-1);printf("任務中心");
	set.go( 5,11);set.color(15);cout<<"npc";
	set.go( 5,3);set.color(15);cout<<"野外";
	set.go(plx,ply);set.color(240);cout<<icon; 
	
		
	while(plx!=-1||ply!=10)								//打怪房? 
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
			set.color(15);printf("門");	
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
                cout<<"請輸入跳轉指令: ";
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
//                             打怪選擇
//----------------------------------------------------------------
void fight(int n)
{
    ui set;
	system("color 0F");
	system("cls");
	
	set.go(4,2);printf("戰鬥");
	set.go(4,4);printf("逃跑（消耗10體力值）");
	set.go(2,2);printf(">>");
	set.go(4,7);printf("對手：");cout<<mon[boci][n].name;
	set.go(4,9);printf("生命值：");cout<<mon[boci][n].hp;
	set.go(4,10);printf("傷害值：");cout<<mon[boci][n].damage;
	set.go(4,11);printf("免傷率：");cout<<mon[boci][n].unhurt;
	set.go(4,12);printf("暴擊率：");cout<<mon[boci][n].crit;
	set.go(4,13);printf("閃避率：");cout<<mon[boci][n].eva;
	
	set.go(4,14);printf("掉落寶石:");cout<<mon[boci][n].ruby;
	 
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
//                            打怪函示
//----------------------------------------------------------------
void ffight(int n)
{
    ui set;
	system("cls");system("color 0F");
	set.go(3,1);cout<<Profess[Profession].name;	
	set.go(12,1);cout<<mon[boci][n].name;
	
	set.go(2,3);cout<<"生命值："<<hp();	
	set.go(11,3);cout<<"生命值："<<mon[boci][n].hp;
	set.go(2,4);cout<<"體力值："<<sp();
	set.go(2,5);cout<<"傷害值："<<damage();
	set.go(11,5);cout<<"傷害值："<<mon[boci][n].damage;	
	set.go(2,6);cout<<"免傷率："<<unhurt(mon[boci][n].type)<<"%";
	set.go(11,6);cout<<"免傷率："<<mon[boci][n].unhurt<<"%";
	set.go(2,7);cout<<"暴擊率："<<crit()<<"%";
	set.go(11,7);cout<<"暴擊率："<<mon[boci][n].crit<<"%";
	set.go(2,8);cout<<"閃避率："<<eva()<<"%";
	set.go(11,8);cout<<"閃避率："<<mon[boci][n].eva<<"%";
	
	set.go(4,10);printf("輕輕攻擊（傷害值25，消耗2體力值）");
	set.go(4,11);printf("普通攻擊（傷害值80，消耗8體力值）");
	set.go(4,12);printf("大力攻擊（傷害值160，消耗20體力值）");
	set.go(4,13);printf("退出");
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
				set.go(1,2);printf(" 暴擊 ");  Sleep(500);
			}
			mon[boci][n].hp-=b;
		}
		else{
			set.go(13,2);printf(" 閃避 ");  Sleep(500);
		} 
		Profess[Profession].SP-=2; 

		if(sp()<=0)
		{
			system("cls");
			system("color 0F");
			set.go(6,6);printf("你累死了");
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
				set.go(1,2);printf(" 暴擊 ");  Sleep(500);
			}
			mon[boci][n].hp-=b;
		}
		else
		{
			set.go(13,2);printf(" 閃避 ");  Sleep(500);
		} 
		Profess[Profession].SP-=8; 
		if(sp()<=0)
		{
			system("cls");
			system("color 0F");
			set.go(6,6);printf("你累死了。");
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
				set.go(1,2);printf(" 暴擊 "); Sleep(500);
			}
			mon[boci][n].hp-=b;
		}
		else
		{
			set.go(13,2);printf(" 閃避 ");  Sleep(500);
		} 
		Profess[Profession].SP-=20;
		if(sp()<=0)
		{
			system("cls");
			system("color 0F");
			set.go(6,6);printf("你累死了。");
			room1();
		} 

	}
	
	if(getrand(1,100)>eva())
	{
		float c=mon[boci][n].damage*(100-unhurt(mon[boci][n].type))/100;
		if(getrand(1,100)<mon[boci][n].crit)
		{
			c*=1.5;
			set.go(10,2);printf(" 暴擊 "); Sleep(500);
		}
		Profess[Profession].HP-=c;
	}
	else
	{
		set.go(4,2);printf(" 閃避 ");  Sleep(500);
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
		set.go(6,6);printf("怪物被打死了！獲得%d個寶石！",mon[boci][n].ruby);
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
		set.go(6,6);printf("你犧牲了。");
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
		set.go(6,6);printf(" 你累死了 ");
		Profess[Profession].SP = 200;
		room1();
	} 
}
//----------------------------------------------------------------
//                             打怪房間
//----------------------------------------------------------------
void fig(){
	check  = 5;
	ui set;
	int key=0;
	string icon=Profess[Profession].icon;
	
	system("color 0F");
	system("cls");
	set.printmap();
	
	set.go( 0,10);printf("門");
	set.go( 8,-1);printf("野外");
	set.go(plx,ply);set.color(240);cout<<icon; 
	
		
	while(plx!=-1||ply!=10)								//打怪房間 
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
			set.color(15);printf("門");	
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
                cout<<"請輸入跳轉指令: ";
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
//                             武器房間
//----------------------------------------------------------------
void we(){
	ui set;
	int key=0;
	string icon=Profess[Profession].icon;
	
	check = 2;
	system("color 0F");
	system("cls");
	set.printmap();
	
	set.go( 0,10);printf("門");
	set.go( 8,-1);printf("武器");
    set.go(10,10);printf("武器商店");
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
			set.color(15);printf("門");	
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
                cout<<"請輸入跳轉指令: ";
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
//                             防具商店
//----------------------------------------------------------------
void fa(){
	ui set;
	int key=0;
	string icon=Profess[Profession].icon;
	check = 3;
	system("color 0F");
	system("cls");
	set.printmap();
	
	set.go( 0,10);printf("門");
	set.go( 8,-1);printf("防具");
    set.go(10,10);printf("防具商店");
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
			set.color(15);printf("門");	
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
                cout<<"請輸入跳轉指令: ";
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
	printf("背包");
	set.go(2,1);
	set.color(15);
	printf("物品名稱  物品數值  物品狀態"); 
	for(int i=1;i<=arms[0]+fangbag[0];i++)
	{
		if(i<=arms[0])
		{
			set.go( 2,i+1);cout<<ARMM[arms[i]].name;
			set.go( 7,i+1);cout<<ARMM[arms[i]].damage<<"%";
			set.go(12,i+1);if(nowwu==i)printf("已裝備");else printf("未裝備");
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
					printf("已裝備");
				}
				else
				{
					printf("未裝備");
				}
			}
			if(fangju[fangbag[i-arms[0]]].type==2)
			{
				if(nowfang.ku==i)
				{
					printf("已裝備");
				}
				else
				{
					printf("未裝備");
				}					
			}
			if(fangju[fangbag[i-arms[0]]].type==3)
			{
				if(nowfang.jia==i)
				{
					printf("已裝備");
				}
				else
				{
					printf("未裝備");
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
						printf("未裝備");
					}
					nowwu=a;
					set.go(12,nowwu+1);
					printf("已裝備");					
				}
				else
				{
					set.go(12,nowwu+1);printf("未裝備");nowwu=-1;
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
							printf("未裝備");
						}
						nowfang.dun=a;
						set.go(12,nowfang.dun+1);
						printf("已裝備");
					}
					else
					{
						set.go(12,nowfang.dun+1);printf("未裝備");nowfang.dun=-1;
					}
				}
				else if(fangju[fangbag[a-arms[0]]].type==2)
				{
					if(nowfang.ku!=a)
					{
						if(nowfang.ku!=-1)
						{
							set.go(12,nowfang.ku+1);
							printf("未裝備");
						}
						nowfang.ku=a;
						set.go(12,nowfang.ku+1);
						printf("已裝備");
					}
					else
					{
						set.go(12,nowfang.ku+1);printf("未裝備");nowfang.ku=-1;
					}					
				}
				else if(fangju[fangbag[a-arms[0]]].type==3)
				{
					if(nowfang.jia!=a)
					{
						if(nowfang.jia!=-1)
						{
							set.go(12,nowfang.jia+1);
							printf("未裝備");
						}
						nowfang.jia=a;
						set.go(12,nowfang.jia+1);
						printf("已裝備");
					}
					else
					{
						set.go(12,nowfang.jia+1);printf("未裝備");nowfang.jia=-1;
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
//                             屬性點數
//----------------------------------------------------------------
void  at(){
	ui set;
	system("cls");
	system("color 0F");
	set.go(2,6);
	while(1){
		set.go(15,5);cout<<"你擁有的點數 "<<Attributes;
		set.go(15,6);cout<<"HP: "<<Profess[Profession].HP;
		set.go(15,7);cout<<"SP: " <<Profess[Profession].SP;
		set.go(15,8);cout<<"damage: "<<Profess[Profession].damage;
		set.go(2,5);cout<<"請輸入你想提升的數值: ";
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
			set.go(2,7);cout<<"你的屬性點數不足         ";
		}
	}
	maxhp = Profess[Profession].HP;
}
//----------------------------------------------------------------
//                             技能點數
//----------------------------------------------------------------
void st(){
	ui set;
	int point_ch = 0;
	system("cls");
	system("color 0F");
	while(1){

		set.go(2,2);cout<<"你擁有的技能";
		set.go(3,3);
				if(boci==1){
					cout<<skill[Profession].name1<<" "<<skill[Profession].rank1<<"等 "<<"傷害"<<skill[Profession].damage1;
					point_ch++;
				}else if(boci==2){
					cout<<skill[Profession].name1<<" "<<skill[Profession].rank1<<"等 "<<"傷害"<<skill[Profession].damage1;
					set.go(3,4);cout<<skill[Profession].name2<<" "<<skill[Profession].rank2<<"等 "<<"傷害"<<skill[Profession].damage2;
					point_ch++;
				}else if(boci==3){
					cout<<skill[Profession].name1<<" "<<skill[Profession].rank1<<"等 "<<"傷害"<<skill[Profession].damage1;
					set.go(3,4);cout<<skill[Profession].name2<<" "<<skill[Profession].rank2<<"等 "<<"傷害"<<skill[Profession].damage2;
					set.go(3,5);cout<<skill[Profession].name3<<" "<<skill[Profession].rank3<<"等 "<<"傷害"<<skill[Profession].damage3;
					point_ch++;
				} else if(boci==4){
					cout<<skill[Profession].name1<<" "<<skill[Profession].rank1<<"等 "<<"傷害"<<skill[Profession].damage1;
					set.go(3,4);cout<<skill[Profession].name2<<" "<<skill[Profession].rank2<<"等 "<<"傷害"<<skill[Profession].damage2;
					set.go(3,5);cout<<skill[Profession].name3<<" "<<skill[Profession].rank3<<"等 "<<"傷害"<<skill[Profession].damage3;
					set.go(3,6);cout<<skill[Profession].name4<<" "<<skill[Profession].rank4<<"等 "<<"傷害"<<skill[Profession].damage4;
					point_ch++;
				}
		set.go(23,2);cout<<"請輸入升級的技能";
		set.go(25,2);cout<<"你擁有的技能點數 "<<ability;
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
//                             任務結算頁面
//----------------------------------------------------------------
void mi(){
	ui set;
	system("cls");
		while(1){
			set.go(2,10);cout<<"你擁有 "<<ruby<<"個寶石";
			set.go(2,5);cout<<"請輸入完成任務指令";
			set.go(2,6);
			cin>>np;
			cout<<"                ";
			if(np=="aflash"&&kill_a==0){
				ruby = ruby+1000;
				cout<<"任務完成發放1000寶石獎勵";
				cout<<"                        ";
			}
			if(np=="bflash"&&kill_b==0){
				ruby = ruby+1000;
				cout<<"任務完成發放1000寶石獎勵";
				cout<<"                        ";
			}
			if(np=="cflash"&&kill_c==0){
				ruby = ruby+1000;
				cout<<"任務完成發放1000寶石獎勵";
				cout<<"                        ";
			}
			if(np!="aflash"&&np!="bflash"&&np!="cflash"){
				cout<<"輸入錯誤或未完成任務 ";
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

