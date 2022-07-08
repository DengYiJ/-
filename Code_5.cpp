#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>
#include<Windows.h>
#include<time.h>
#pragma comment(lib, "Winmm.lib")
#define  WIDTH 1250 // 画面宽度
#define  HEIGHT 760 // 画面高度
#define vy 5//手牌移动速度
#define x1 120//手牌间间隔
#define img_x 195//首张手牌x坐标
#define img_y 590//手牌y坐标
#define img_top 525//确定取消y坐标
void nextHuihe(int card2[]);
int playermove();
void update();
void outpainum();
void npcshow();
void outround();
void outguanshifu();
void clearpai();
void outpaiduinum();
void outqiling();
void judgelife();
void npcchupai(int i);
void outchusha();
void outwuxie();
void playerchusha(int i);
void outbagua();

int img_h = 590;//图片y坐标
IMAGE im_bk;//背景图
IMAGE im_right1, im_cancel, im_right0, im_cance0, im_end;//确定、取消、结束图片
IMAGE  im_arm[2], im_defendhorse[2], im_attackhorse[2],im_defend[2];//装备区图片
IMAGE 八卦阵我方, 八卦阵敌方,赤兔我方,赤兔敌方,爪黄飞电敌方,爪黄飞电我方;//装备区装备牌
IMAGE 贯石斧我方,贯石斧敌方,麒麟弓我方,麒麟弓敌方,青釭剑我方,青釭剑敌方;
IMAGE 牌堆回合数;
IMAGE 登录背景;
IMAGE im_loading;//加载背景
IMAGE im_renwu[2];//人物图
IMAGE im_bagua[2];//八卦阵
IMAGE im_playerblood[5],im_npcblood[5];
MOUSEMSG m,m0,m1,m2,m3,m4,m5;//鼠标消息
int ischoose = 0, paistate = 1;//牌未被选中
int a[73];//牌序号
int usenum = 0;//已使用手牌数
int playerpai[6] = {-1,-1,-1,-1,-1,-1},npcpai[6] = {-1,-1,-1,-1,-1,-1};//储存当前手牌
int playershoupai = 0, npcshoupai = 0;//当前牌数
int defendnum[2]={0,0},attackhorse[2]={0,0},defendhorse[2]={0,0};//装备区非武器牌
int qingnum[2]={0,0},qilingnum[2]={0,0},guannum[2]={0,0};//装备区武器牌
int shannum = 0;//每回合打出闪
int huihe = 0;//玩家回合
int defendlocation[2] = {625,178};//装备区防具y坐标
int armlocation[2]={580,160};//装备区武器y坐标
int dhorselocation[2]={720,212};//装备区防御马y坐标
int ahorselocation[2]={675,195};//装备区进攻马y坐标
int elocation[2]={2,547};//装备区装备位置x坐标
int shalimitation = 1;//出杀的数量有限制
int npcshan = 0;//玩家打出杀时npc所需出闪
int end1 = 0, end = 0;//
int chupainum = 0;//npc出牌
int jiunum = 0;//打出的酒的数量
int shanghai = 1;//杀伤害数值
int npclife = 4, playerlife = 4;//npc和玩家生命值
int baguanum1 = 0, baguanum2 = 0,shengxiao1 = 0, shengxiao2 = 0;//八卦阵及是否生效
int huihenum=1;//回合数
int wanjian=0;//是否打出万箭齐发
int wuxienum=0;//是否打出无懈可击

struct pai//定义牌的序号、图像
{
	int type;
	int num;
	IMAGE im;
};

struct location//牌的位置
{
	int x;//x坐标
	int y;//y坐标
};

pai paidui[73];
location pail[7];

void xipai()//洗牌函数
{
	int i, j, k, t;
	for(i = 0;i<73;i++)
		a[i] = i;
	for(k = 0;k<100;k++)
	{
		i = rand()%73;
		j = rand()%73;
		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
}

void startuppicture()//给牌赋予图像
{
	int i;
	for(i = 0;i<73;i++)
		paidui[i].num = i + 1;
	for(i = 0;i<20;i++)
		loadimage(&paidui[i].im, _T("杀.jpg"));
	for(i = 20;i<35;i++)
		loadimage(&paidui[i].im, _T("闪.jpg"));
	for(i = 35;i<43;i++)
		loadimage(&paidui[i].im, _T("桃.jpg"));
	for(i = 43;i<45;i++)
		loadimage(&paidui[i].im, _T("八卦阵.png"));
	for(i = 45;i<49;i++)
		loadimage(&paidui[i].im, _T("顺手牵羊.png"));
	for(i = 49;i<53;i++)
		loadimage(&paidui[i].im, _T("过河拆桥.png"));
	for(i = 53;i<56;i++)
		loadimage(&paidui[i].im, _T("决斗.png"));
	for(i = 56;i<60;i++)
		loadimage(&paidui[i].im, _T("无懈可击.png"));
	for(i = 60;i<64;i++)
		loadimage(&paidui[i].im, _T("酒.jpg"));
	loadimage(&paidui[64].im, _T("爪黄飞电.png"));
	loadimage(&paidui[65].im, _T("赤兔.png"));
	loadimage(&paidui[66].im, _T("麒麟弓.png"));
	loadimage(&paidui[67].im, _T("青釭剑.png"));
	loadimage(&paidui[68].im, _T("贯石斧.png"));
	for(i=69;i<71;i++)
		loadimage(&paidui[i].im, _T("南蛮入侵.jpg"));
	for(i = 71;i<73;i++)
		loadimage(&paidui[i].im, _T("万箭齐发.jpg"));
	loadimage(&八卦阵我方,_T("八卦阵我方.PNG"));
	loadimage(&八卦阵敌方,_T("八卦阵敌方.PNG"));
	loadimage(&赤兔敌方,_T("赤兔敌方.PNG"));
	loadimage(&赤兔我方,_T("赤兔我方.PNG"));
	loadimage(&爪黄飞电我方,_T("爪黄飞电我方.PNG"));
	loadimage(&爪黄飞电敌方,_T("爪黄飞电敌方.PNG"));
	loadimage(&贯石斧敌方,_T("贯石斧敌方.PNG"));
	loadimage(&贯石斧我方,_T("贯石斧我方.PNG"));
	loadimage(&青釭剑敌方,_T("青釭剑敌方.PNG"));
	loadimage(&青釭剑我方,_T("青釭剑我方.PNG"));
	loadimage(&麒麟弓敌方,_T("麒麟弓敌方.PNG"));
	loadimage(&麒麟弓我方,_T("麒麟弓我方.PNG"));
	loadimage(&im_playerblood[0],_T("4血0.png"));
	loadimage(&im_playerblood[1],_T("4血1.png"));
	loadimage(&im_playerblood[2],_T("4血2.png"));
	loadimage(&im_playerblood[3],_T("4血3.png"));
	loadimage(&im_playerblood[4],_T("4血4.png"));
	loadimage(&im_npcblood[4],_T("敌方4血4.png"));
	loadimage(&im_npcblood[3],_T("敌方4血3.png"));
	loadimage(&im_npcblood[2],_T("敌方4血2.png"));
	loadimage(&im_npcblood[1],_T("敌方4血1.png"));
	loadimage(&im_npcblood[0],_T("敌方4血0.png"));
	loadimage(&im_right1, _T("确定1.png"));
	loadimage(&im_cancel, _T("取消1.png"));
	loadimage(&im_right0, _T("确定0.png"));
	loadimage(&im_cance0, _T("取消0.png"));
	loadimage(&牌堆回合数,_T("牌堆回合数.png"));
	loadimage(&im_bk, _T("背景.png"));
	loadimage(&im_end, _T("结束.png"));
	loadimage(&im_bagua[0], _T("判定成功.png"));
	loadimage(&im_bagua[1], _T("判定失败.png"));
	loadimage(&im_renwu[0], _T("张飞.png"));
	loadimage(&im_renwu[1], _T("敌方张飞.png"));
	loadimage(&登录背景, _T("登录背景.png"));
	loadimage(&im_loading,_T("加载图片.png"));
}

void startupdenglu()//进入游戏界面
{
	initgraph(WIDTH,HEIGHT);
	putimage(0,0,&登录背景);
	while(1)
	{
		m0 = GetMouseMsg();//获取鼠标信息
		if(m0.uMsg==WM_LBUTTONDOWN)//点击鼠标左键
		{
			if(m0.x>=510&&m0.x<=682&&m0.y>=492&&m0.y<=538)
				break;
		}
	}
}

void loading()//加载界面
{	
	clock_t start, now; // 用于计时的变量
	start = clock(); // 记录当前运行时刻
	float maxTime = 2; // 加载时间
	float remainTime = maxTime; // 剩余时间
	BeginBatchDraw();//开始批量绘制
	while (remainTime>=0)// 循环
	{
		now = clock(); // 获得当前时刻
		// 计算程序一共运行了多少秒
		double duration =( double(now - start) / CLOCKS_PER_SEC); 
		remainTime = maxTime - duration; // 计算剩余时间
		cleardevice(); // 清屏
		putimage(0,0,&im_loading);//放置加载图片
		setbkmode(TRANSPARENT);
		setlinecolor(HSVtoRGB(60,1,1)); // 设置进度条的颜色
		setfillcolor(HSVtoRGB(60,1,1));
		fillrectangle(0,749,duration*1250/maxTime,750); // 绘制进度条
		FlushBatchDraw();//批量绘制一次
		Sleep(20); // 暂停20毫秒
	}
	EndBatchDraw();//结束批量绘制
}

void startup()//开始游戏界面
{
	putimage(0, 0, &im_bk);	// 显示背景图片	
	putimage(775, img_top, &im_end);
	putimage(1095,35,&牌堆回合数);
	putimage(1058,540,&im_renwu[0]);
	putimage(550,49,&im_renwu[1]);
	outround();
	int i;
	for(i = 0;i<6;i++)
		pail[i].x = img_x + i * x1;//牌区各位置x坐标
	pail[6].x = 565;//正中间x坐标
	pail[0].y = 560;//牌微上移y坐标
	pail[1].y = 270;//正中间y坐标
	xipai();//随机洗牌
	for(i = 0;i < 8; i++)
	{
		if(i%2==0)
		{
			playershoupai++;//玩家手牌数+1
			playerpai[i/2] = a[usenum];//赋给玩家手牌
			putimage(img_x+x1*(i/2),img_y,&paidui[playerpai[i/2]].im);//赋图
		}
		else 
		{
			npcshoupai++;
			npcpai[i/2] = a[usenum];//赋给npc手牌
		}
		usenum++;//已使用牌数+1
	}
	for(i=4;i<6;i++)//玩家先出手，赋两张牌
	{
		playershoupai++;
		playerpai[i] = a[usenum];
		putimage(img_x+x1*i,img_y,&paidui[playerpai[i]].im);
		usenum++;
	}
	outpaiduinum();
	outpainum();
	mciSendString(_T("open 背景音乐.mp3 alias bkmusic"), NULL, 0, NULL);//打开背景音乐.
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//循环播放
}

void playmusiconce(TCHAR fileName[80])//音效播放函数
{
	TCHAR cmdString1[50];
	_stprintf(cmdString1, _T("open %s alias tmpmusic"), fileName); // 生成命令字符串
	mciSendString(_T("close tmpmusic"), NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString(cmdString1, NULL, 0, NULL); // 打开音乐
	mciSendString(_T("play tmpmusic"), NULL, 0, NULL); // 仅播放一次
}

void judgemusic(int i)//判断音效种类
{
	if(i>=0&&i<20)
		playmusiconce(_T("杀男.wav"));
	else if(i>=20&&i<35)
		playmusiconce(_T("闪男.mp3"));
	else if(i>=35&&i<43)
		playmusiconce(_T("使用桃.mp3"));
	else if(i>=43&&i<45)
		playmusiconce(_T("八卦阵.mp3"));
	else if(i>=45&&i<49)
		playmusiconce(_T("顺手牵羊.mp3"));
	else if(i>=49&&i<53)
		playmusiconce(_T("过河拆桥男.mp3"));
	else if(i>=53&&i<56)
		playmusiconce(_T("决斗.mp3"));
	else if(i>=56&&i<60)
		playmusiconce(_T("无懈可击.mp3"));
	else if(i>=60&&i<64)
		playmusiconce(_T("酒男.mp3"));
	else if(i>=64&&i<66)
		playmusiconce(_T("使用坐骑牌.mp3"));
	else if(i==67)
		playmusiconce(_T("青釭剑.mp3"));
	else if(i>=69&&i<71)
		playmusiconce(_T("南蛮入侵.mp3"));
	else if(i>=71&&i<73)
		playmusiconce(_T("万箭齐发.mp3"));
}

void placeequipment()//放置背景，结束，人物，在装备区放置装备牌
{
	int i;
	putimage(0, 0, &im_bk);
	putimage(775, img_top, &im_end);
	putimage(1095,35,&牌堆回合数);
	putimage(1058,540,&im_renwu[0]);
	putimage(550,49,&im_renwu[1]);
	outpainum();
	outround();
	outpaiduinum();
	for(i=0;i<2;i++)
	{
		if(defendnum[i]==1)
			putimage(elocation[i], defendlocation[i], &im_defend[i]);
		if(qingnum[i]==1||guannum[i]==1||qilingnum[i]==1)
			putimage(elocation[i], armlocation[i], &im_arm[i]);
		if(defendhorse[i]==1)
			putimage(elocation[i], dhorselocation[i], &im_defendhorse[i]);
		if(attackhorse[i]==1)
			putimage(elocation[i], ahorselocation[i], &im_attackhorse[i]);
	}
}

void placeshoupai()//放置手牌图像
{
	int i;
	for(i=0;i<6;i++)
		if(playerpai[i]!=-1)
			putimage(pail[i].x,img_y,&paidui[playerpai[i]].im);
}

void Playerbagua()//八卦阵效果
{
	int j = rand()%2;
	shengxiao1 = 0;
	putimage(400, img_top, &im_right1);
	putimage(600, img_top, &im_cancel);
	outbagua();
	FlushBatchDraw();
	while(1)
	{
		m3 = GetMouseMsg();//获取鼠标信息
		if(m3.uMsg==WM_LBUTTONDOWN)//点击鼠标左键
		{
			if(m3.x>=400&&m3.x<=524&&m3.y>=img_top&&m3.y<=img_top+39)//点击确定
			{
				if(j == 0)
				{
					putimage(625,300,&im_bagua[0]);
					Sleep(500);
					FlushBatchDraw();
					shengxiao1++;
				}
				else
				{
					putimage(625,300,&im_bagua[1]);
					Sleep(500);
					FlushBatchDraw();
				}
				Sleep(1500);
				clearpai();
				FlushBatchDraw();
				break;
			}
			if(m3.x>=600&&m3.x<=724&&m3.y>=img_top&&m3.y<=img_top+43)//点击取消
			{
				shengxiao1--;
				break;
			}
		}
	}
	Sleep(500);
}

void Npcbagua()
{
	int j = rand()%2;
	shengxiao2 = 0;
	if(j==0)
	{
		putimage(425,200,&im_bagua[0]);
		Sleep(500);
		FlushBatchDraw();
		shengxiao2++;
	}
	else
	{
		putimage(425,200,&im_bagua[1]);
		Sleep(500);
		FlushBatchDraw();
	}
	Sleep(1500);
	clearpai();
}

void judgeequipment(int i)//判断是否为装备牌
{
	if(i>=43&&i<45)
	{
		if(huihe==0)
		{
			im_defend[0] = 八卦阵我方;
			putimage(elocation[0], defendlocation[0], &im_defend[0]);
			if(defendnum[0]==0)
			{
				defendnum[0]++;
				baguanum1++;
			}
		}
		else
		{
			im_defend[1] = 八卦阵敌方;
			putimage(elocation[1], defendlocation[1], &im_defend[1]);
			if(defendnum[1]==0)
			{
				defendnum[1]++;
				baguanum2++;
			}
		}
	}
	else if(i==65)
	{
		if(huihe==0)
		{
			im_defendhorse[0] = 赤兔我方;
			putimage(elocation[0], dhorselocation[0], &im_defendhorse[0]);
			defendhorse[0]++;
		}
		else
		{
			im_defendhorse[1] = 赤兔敌方;
			putimage(elocation[1], dhorselocation[1], &im_defendhorse[1]);
			defendhorse[1]++;
		}
	}
	else if(i==64)
	{
		if(huihe==0)
		{
			im_attackhorse[0] = 爪黄飞电我方;
			putimage(elocation[0], ahorselocation[0], &im_attackhorse[0]);
			attackhorse[0]++;
		}
		else
		{
			im_attackhorse[1] = 爪黄飞电敌方;
			putimage(elocation[1], ahorselocation[1], &im_attackhorse[1]);
			attackhorse[1]++;
		}
	}
	else if(i==67)
	{
		if(huihe==0)
		{
			qingnum[0]++;
			im_arm[0] = 青釭剑我方;
			putimage(elocation[0], armlocation[0], &im_arm[0]);
			guannum[0]=0;
			qilingnum[0]=0;
		}
		else 
		{
			qingnum[1]++;
			im_arm[1] = 青釭剑敌方;
			putimage(elocation[1], armlocation[1], &im_arm[1]);
			guannum[1]=0;
			qilingnum[1]=0;
		}
	}
	else if(i==68)
	{
		if(huihe==0)
		{
			guannum[0]++;
			im_arm[0] = 贯石斧我方;
			putimage(elocation[0], armlocation[0], &im_arm[0]);
			qingnum[0]=0;
			qilingnum[0]=0;
		}
		else 
		{
			guannum[1]++;
			im_arm[1] = 贯石斧敌方;
			qingnum[1]=0;
			putimage(elocation[1], armlocation[1], &im_arm[1]);
			qilingnum[1]=0;
		}
	}
	else if(i==66)
	{
		if(huihe==0)
		{
			qilingnum[0]++;
			im_arm[0] = 麒麟弓我方;
			putimage(elocation[0], armlocation[0], &im_arm[0]);
			guannum[0]=0;
			qingnum[0]=0;
		}
		else 
		{
			qilingnum[1]++;
			im_arm[1] = 麒麟弓敌方;
			putimage(elocation[1], armlocation[1], &im_arm[1]);
			guannum[1]=0;
			qingnum[1]=0;
		}
	}
}

void adjustpai(int card1[])//调整手牌序号
{
	int i, j, t;
	for(i=0;i<6;i++)
	{
		if(card1[i]== -1)
		{
			for(j=i+1;j<6;j++)
			{
				if(card1[j]!=-1)
				{
					t=card1[i];
					card1[i]=card1[j];
					card1[j]=t;
					break;
				}
			}
		}
	}
}

void clearpai()//清除已打出牌
{
	cleardevice();//清屏
	placeequipment();
	//放置灰色确定取消
	if(huihe==0)
	{
		putimage(400, img_top, &im_right0);
		putimage(600, img_top, &im_cance0);
	}
	placeshoupai();
}

void juedou()
{
	int i = 0;
	int k = 0;//玩家或人机是否出杀
	int ns = 0;//人机牌中杀的数量
	int ps = 0;//玩家牌中杀的数量
	for(i=0;i<6;i++)
	{
		if(npcpai[i]>=0&&npcpai[i]<20)
		{
			ns++;
		}
		if(playerpai[i]>=0&&playerpai[i]<20)
		{
			ps++;
		}
	}
	if(huihe==0)
	{
		if(ns==0)
		{
			npclife--;
			clearpai();
		}
		else if(ns>0)
		{
			while(ns>=0||ps>=0)
			{
				for(i=0;i<6;i++)
				{
					if(npcpai[i]>=0&&npcpai[i]<20)
					{
						putimage(pail[6].x, pail[1].y, &paidui[npcpai[i]].im);
						playmusiconce(_T("杀男.wav"));
						npcpai[i]=-1;
						FlushBatchDraw();
						Sleep(1000);
						npcshoupai--;
						ns--;
						break;
					}
				}
				for(i=0;i<6;i++)
				{
					if(playerpai[i]>=0&&playerpai[i]<20)
					{
						k++;
						playerchusha(i);
						ps--;
						break;
					}
				}
				if(ns>=0&&ps==0&&k==0)
				{
					playerlife--;
					clearpai();
					break;
				}
				if(ns==0&&ps==0&&k!=0)
				{
					npclife--;
					clearpai();
					break;
				}
				if(ns==0&&ps>0)
				{
					npclife--;
					clearpai();
					break;
				}
				if(ns>0&&ps==0&&k!=0)
				{
					for(i=0;i<6;i++)
					{
						if(npcpai[i]>=0&&npcpai[i]<20)
						{
							putimage(pail[6].x, pail[1].y, &paidui[npcpai[i]].im);
							playmusiconce(_T("杀男.wav"));
							npcpai[i]=-1;
							FlushBatchDraw();
							Sleep(1000);
							npcshoupai--;
							playerlife--;
							break;
						}
					}
				}
			}
			clearpai();
		}
	}
	if(huihe==1)
	{
		if(ps==0)
		{
			playerlife--;
			clearpai();
		}
		else if(ps>0)
		{
			while(ns>=0||ps>=0)
			{
				for(i=0;i<6;i++)
				{
					if(playerpai[i]>=0&&playerpai[i]<20)
					{
						playerchusha(i);
						ps--;
						break;
					}
				}
				for(i=0;i<6;i++)
				{
					if(npcpai[i]>=0&&npcpai[i]<20)
					{
						k++;
						putimage(pail[6].x, pail[1].y, &paidui[npcpai[i]].im);
						playmusiconce(_T("杀男.wav"));
						npcpai[i]=-1;
						FlushBatchDraw();
						Sleep(1000);
						npcshoupai--;
						ns--;
						break;
					}
				}
				if(ps>=0&&ns==0&&k==0)
				{
					npclife--;
					clearpai();
					break;
				}
				if(ps==0&&ns==0&&k!=0)
				{
					playerlife--;
					clearpai();
					break;
				}
				if(ps==0&&ns>0)
				{
					playerlife--;
					clearpai();
					break;
				}
				if(ps>0&&ns==0&&k!=0)
				{
					for(i=0;i<6;i++)
					{
						if(playerpai[i]>=0&&playerpai[i]<20)
						{
							playerchusha(i);
							npclife--;
							break;
						}
					}
				}
			}
			clearpai();
		}
	}
}

void wuxie()
{
	int i;
	if(huihe==0)
	{
		for(i=0;i<6;i++)
		{
			if(npcpai[i]>=56&&npcpai[i]<60)
			{
				wuxienum++;
				npcchupai(i);
				break;
			}
		}
	}
	else 
	{
		int j;
		for(i=0;i<6;i++)
		{
			if(playerpai[i]>=56&&playerpai[i]<60)
			{
				cleardevice();
				placeequipment();
				putimage(400, img_top, &im_right1);
				putimage(600, img_top, &im_cancel);
				for(j = 0;j<6;j++)
				{
					if(playerpai[j]!=-1)
					{
						if(j!=i)
							putimage(pail[j].x, img_y, &paidui[playerpai[j]].im);//未点击牌不动
						else 
							putimage(pail[j].x, pail[0].y, &paidui[playerpai[j]].im);//所点击牌移动
					}
				}
				outwuxie();
				FlushBatchDraw();
				while(1)
				{
					m5 = GetMouseMsg();//获取鼠标信
					if(m5.uMsg==WM_LBUTTONDOWN)//点击鼠标左键
					{
						if(m5.x>=400&&m5.x<=524&&m5.y>=img_top&&m5.y<=img_top+39)//点击确定
						{
							wuxienum=1;
							cleardevice();
							placeequipment();
							putimage(pail[6].x, pail[1].y, &paidui[playerpai[i]].im);//打出所点击牌
							judgemusic(playerpai[i]);//播放音效
							playerpai[i]=-1;//该牌消失
							playershoupai--;//玩家手牌数减一
							adjustpai(playerpai);
							placeshoupai();
							FlushBatchDraw();
							Sleep(1500);
							clearpai();
							FlushBatchDraw();
							break;
						}
						else if(m2.x>=600&&m2.x<=724&&m2.y>=img_top&&m2.y<=img_top+43&&wanjian==0)//点击取消
						{
							clearpai();
							FlushBatchDraw();
							break;
						}
						judgelife();
					}
				}
				Sleep(500);
				break;
			}
		}
	}
}

void nanman()
{
	int i = 0;
	int N = 0;
	int P = 0;
	if(huihe==0)
	{
		for(i=0;i<6;i++)
		{
			if(npcpai[i]>=0&&npcpai[i]<20)
			{
				N++;
				putimage(pail[6].x, pail[1].y, &paidui[npcpai[i]].im);
				playmusiconce(_T("杀男.wav"));
				npcpai[i]=-1;
				FlushBatchDraw();
				Sleep(1000);
				npcshoupai--;
				break;
			}
		}
		if(N==0)
		{
			npclife--;
		}
		clearpai();
	}
	if(huihe==1)
	{
		for(i=0;i<6;i++)
		{
			if(playerpai[i]>=0&&playerpai[i]<20)
			{
				P++;
				playerchusha(i);
				break;
			}
		}
		if(P==0)
		{
			playerlife--;
		}
		clearpai();
	}
}

void playerpaieffect(int i)//玩家打出牌的效果
{
	if((i>=0&&i<20)||(i>=71&&i<73))//杀或万箭齐发
	{
		if(i>=71&&i<73)//若万箭齐发
		{
			wuxie();
			wanjian=1;
		}
		npcshan++;
		npcshow();
		npcshan=0;
		wanjian=0;
		if(shanghai>1)
			shanghai=1;
		wuxienum=0;
	}
	else if(i>=35&&i<43)//桃
	{
		if(huihe==0&&playerlife<4)
		{
			playerlife++;
			clearpai();
		}
		else if(huihe==1&&npclife<4)
			npclife++;
	}
	else if(i>=45&&i<49)//顺手牵羊
	{
		wuxie();
		if(npcshoupai>0&&wuxienum==0)
		{
			playerpai[5]=npcpai[0];
			npcpai[0]=-1;
			playershoupai++;
			npcshoupai--;
			adjustpai(playerpai);
			adjustpai(npcpai);
			clearpai();
		}
		wuxienum=0;
	}
	else if(i>=49&&i<53)//过河拆桥
	{
		wuxie();
		if(npcshoupai>0&&wuxienum==0)
		{
			Sleep(500);
			putimage(pail[6].x, pail[1].y, &paidui[npcpai[0]].im);//弃掉对方第一张牌
			FlushBatchDraw();
			npcpai[0]=-1;
			npcshoupai--;
			adjustpai(npcpai);
			Sleep(1500);
			clearpai();
			Sleep(500);
		}
		wuxienum=0;
	}
	else if(i>=69&&i<71)//南蛮入侵
		nanman();
	else if(i>=53&&i<56)//决斗
	{
		wuxie();
		if(wuxie==0)
			juedou();
		wuxienum=0;
	}
	else if(i>=60&&i<64)//酒
		if(shanghai=1)
			shanghai++;//杀伤害增加
}

void guanshi()
{
	int k,t1=0,t2=0;
	if(huihe==0)
	{
		while(1)
		{
			int i=rand()%playershoupai,j=rand()%playershoupai;
			while(i==j)
				j=rand()%playershoupai;
			putimage(400, img_top, &im_right1);
			putimage(600, img_top, &im_cancel);
			outguanshifu();
			FlushBatchDraw();
			m3 = GetMouseMsg();//获取鼠标信息
			if(m3.uMsg==WM_LBUTTONDOWN)//点击鼠标左键
			{
				if(m3.x>=400&&m3.x<=524&&m3.y>=img_top&&m3.y<=img_top+39)//点击确定
				{
					playmusiconce(_T("贯石斧.mp3"));
					npclife-=shanghai;
					cleardevice();
					placeequipment();
					for(k=0;k<6;k++)
						if(playerpai[k]!=-1)
						{
							if(k==i||k==j)
							{
								putimage(505+120*t1,pail[1].y,&paidui[playerpai[k]].im);
								t1++;
							}
							else 
							{
								putimage(pail[t2].x,img_y,&paidui[playerpai[k]].im);
								t2++;
							}
						}
					playerpai[i]=-1;
					playerpai[j]=-1;
					adjustpai(playerpai);
					playershoupai-=2;
					FlushBatchDraw();
					Sleep(1500);
					clearpai();
					FlushBatchDraw();
					break;
				}
				else if(m3.x>=600&&m3.x<=724&&m3.y>=img_top&&m3.y<=img_top+43)//点击取消
				{
					clearpai();
					FlushBatchDraw();
					break;
				}
			}
		}
	}
	else 
	{
		outguanshifu();
		int i=rand()%npcshoupai,j=rand()%npcshoupai;
		while(i==j)
			j=rand()%npcshoupai;
		for(k=0;k<6;k++)
			if(npcpai[k]!=-1)
			{
				if(k==i||k==j)
				{
					putimage(505+120*t1,pail[1].y,&paidui[playerpai[k]].im);
					t1++;
				}
			}
		playerlife-=shanghai;
		npcpai[i]=-1;
		npcpai[j]=-1;
		npcshoupai-=2;
		adjustpai(npcpai);
		FlushBatchDraw();
		Sleep(1500);
		clearpai();
		FlushBatchDraw();
	}
}

void qiling()
{
	if(huihe==0)
	{
		while(1)
		{
			m4 = GetMouseMsg();//获取鼠标信息
			putimage(400, img_top, &im_right1);
			putimage(600, img_top, &im_cancel);
			outqiling();
			FlushBatchDraw();
			if(m4.uMsg==WM_LBUTTONDOWN)//点击鼠标左键
			{
				if(m4.x>=400&&m4.x<=524&&m4.y>=img_top&&m4.y<=img_top+39)//点击确定
				{
					int horsenum=0;
					if(attackhorse[1]==1)
					{
						attackhorse[1]=0;
						horsenum++;
					}
					if(defendhorse[1]==1&&horsenum==0)
						defendhorse[1]=0;
					clearpai();
					FlushBatchDraw();
					break;
				}
				else if(m4.x>=600&&m4.x<=724&&m4.y>=img_top&&m4.y<=img_top+43)//点击取消
				{
					clearpai();
					FlushBatchDraw();
					break;
				}
			}
		}
	}
	else
	{
		outqiling();
		FlushBatchDraw();
		Sleep(1000);
		int horsenum=0;
		if(attackhorse[0]==1)
		{
			attackhorse[0]=0;
			horsenum++;
		}
		if(defendhorse[0]==1&&horsenum==0)
			defendhorse[0]=0;
		FlushBatchDraw();
		Sleep(1000);
	}
}

void judgelife()
{
	int i;
	if(npclife==0)
		for(i=0;i<6;i++)
			if(npcpai[i]>=35&&npcpai[i]<43)
			{
				npclife++;
				npcchupai(i);
				break;
			}
	if(playerlife==0)
		for(i=0;i<6;i++)
			if(playerpai[i]>=35&&playerpai[i]<43)
			{
				putimage(pail[6].x, pail[1].y, &paidui[playerpai[i]].im);//打出所点击牌
				playerlife++;
				playerpai[i]=-1;
				playershoupai--;
				adjustpai(playerpai);
				FlushBatchDraw();
				Sleep(1500);
				clearpai();
				FlushBatchDraw();
				break;
			}
	if(npclife<=0||playerlife<=0)
	{
		TCHAR s[20];
		setbkmode(TRANSPARENT); // 文字字体透明
		if(huihe==0)
			_stprintf(s, _T("游戏结束，玩家胜利"));
		else _stprintf(s, _T("游戏结束，人机胜利"));
		settextcolor(BLACK); // 设定文字颜色
		settextstyle(60, 0, _T("黑体"));//  设定文字大小、样式
		outtextxy(360, 350, s); //  输出文字内容
		end1 = 1;
	}
}

void outbagua()//输出是否使用八卦阵
{
	TCHAR s1[] = _T("是否使用八卦阵");
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(30,0,_T("Times"));
	outtextxy(550, 500, s1);
}

void outwuxie()
{
	TCHAR s1[] = _T("是否使用无懈可击");
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(30,0,_T("Times"));
	outtextxy(520, 490, s1);
}

void outchusha()//输出是否打出杀
{
	TCHAR s1[] = _T("请打出一张杀");
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(30,0,_T("Times"));
	outtextxy(550, 490, s1);
}

void outPlayerDiscardWriting(int i)//玩家弃牌文字
{
	TCHAR s1[100],s2[100];
	setbkmode(TRANSPARENT); // 文字字体透明
	_stprintf(s2, _T("弃牌阶段"));
	_stprintf(s1, _T("你需要丢弃%d张牌"), i);	
	settextcolor(WHITE); // 设定文字颜色
	settextstyle(20, 0, _T("黑体"));//  设定文字大小、样式
	outtextxy(580,470,s2);
	outtextxy(550, 500, s1); //  输出文字内容
}

void outNpcDiscardWritng()
{
	TCHAR s1[100];
	setbkmode(TRANSPARENT); // 文字字体透明
	_stprintf(s1, _T("对方弃牌阶段"));	
	settextcolor(WHITE); // 设定文字颜色
	settextstyle(20, 0, _T("黑体"));//  设定文字大小、样式
	outtextxy(550, 500, s1); //  输出文字内容
}

void outpainum()//输出玩家血量和人机手牌数和血量
{
	int i;
	TCHAR s[20]; // 定义字符串数组
	setbkmode(TRANSPARENT);
	_stprintf(s, _T("%d"), npcshoupai); // 将Npai转换为字符串
	settextstyle(35, 0, _T("Times")); // 设置文字大小、字体
	settextcolor(WHITE);  // 设置字体颜色为白色
	outtextxy(550, 120, s); // 输出人机手牌数
	for(i=0;i<5;i++)
	{
		if(playerlife<0||npclife<0)
		{
			putimage(1210,620,&im_playerblood[0]);
			putimage(683,137,&im_npcblood[0]);
		}
		else
		{
			if(i==playerlife)
				putimage(1210,620,&im_playerblood[i]);
			if(i==npclife)
				putimage(683,137,&im_npcblood[i]);
		}
	}
}

void outchushan()//输出是否打出闪
{
	TCHAR s1[] = _T("请你打出一张闪");
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(30,0,_T("Times"));
	outtextxy(550, 490, s1);
}

void outqiling()
{
	TCHAR s[100];
	setbkmode(TRANSPARENT);
	if(huihe==0)
		_stprintf(s, _T("是否发动麒麟弓特效(弃掉对方第一张马)"));
	else _stprintf(s, _T("敌方发动麒麟弓特效(弃掉我方第一张马)"));
	settextcolor(WHITE);  // 设置字体颜色为白色
	settextstyle(20, 0, _T("黑体"));//  设定文字大小、样式
	outtextxy(430, 490, s);
}

void outguanshifu()
{
	TCHAR s[100];
	setbkmode(TRANSPARENT);
	if(huihe==0)
		_stprintf(s, _T("是否发动贯石斧特效(随机弃两张牌强制扣血)"));
	else _stprintf(s, _T("对方发动贯石斧特效(随机弃两张牌强制扣血)"));
	settextcolor(WHITE);  // 设置字体颜色为白色
	settextstyle(20, 0, _T("黑体"));//  设定文字大小、样式
	outtextxy(410, 490, s);
}

void outround()//输出当前回合为哪方回合
{
	TCHAR s[20];
	setbkmode(TRANSPARENT);
	if(huihe==0)
		_stprintf(s, _T("你的回合"));
	else _stprintf(s, _T("对方回合"));
	settextcolor(WHITE);  // 设置字体颜色为白色
	settextstyle(40, 0, _T("黑体"));//  设定文字大小、样式
	outtextxy(1050, 350, s); // 输出人机手牌数
}

void outpaiduinum()
{
	TCHAR s1[20],s2[20];
	setbkmode(TRANSPARENT);
	_stprintf(s1, _T("%d"),huihenum);
	_stprintf(s2, _T("%d"),73-usenum);
	settextcolor(WHITE);  // 设置字体颜色为白色
	settextstyle(20, 0, _T("黑体"));//  设定文字大小、样式
	outtextxy(1187, 39, s1); // 输出人机手牌数
	outtextxy(1215, 62, s2); // 输出人机手牌数
}

int n1;
void discard()//弃牌
{
	BeginBatchDraw();//开始批量绘制
	if(huihe==0)
	{
		if(playershoupai>playerlife)
		{
			int k1 = playershoupai-playerlife;
			outPlayerDiscardWriting(k1);
			FlushBatchDraw();//批量绘制一次
			int i;
			while(1)
			{
				m1 = GetMouseMsg();//获取鼠标信息
				if(m1.uMsg==WM_LBUTTONDOWN)//点击鼠标左键
				{
					if(ischoose==1&&m1.x>=400&&m1.x<=524&&m1.y>=img_top&&m1.y<=img_top+39)//点击确定
						paistate = 0;
					if(paistate==1&&!(m1.x>=600&&m1.x<=724&&m1.y>=img_top&&m1.y<=img_top+43))
						n1 = (m1.x - 195)/x1;//牌所在位置序号
					if(ischoose==0&&m1.x>=195+x1*n1&&m1.x<=311+x1*n1&&m1.y>=590&&m1.y<=753)//牌上升，被选中
					{
						cleardevice();
						placeequipment();
						putimage(400, img_top, &im_right1);
						putimage(600, img_top, &im_cancel);
						for(i = 0;i<6;i++)
						{
							if(playerpai[i]!=-1)
							{
								if(i!=n1)
									putimage(pail[i].x, img_y, &paidui[playerpai[i]].im);//未点击牌不动
								else 
									putimage(pail[i].x, pail[0].y, &paidui[playerpai[i]].im);//所点击牌移动
							}
						}
						outPlayerDiscardWriting(k1);
						FlushBatchDraw();//批量绘制一次
						ischoose = 1;
					}
					else if((ischoose==1&&m1.x>=195+x1*n1&&m1.x<=311+x1*n1&&m1.y>=560&&m1.y<=723)||
						(ischoose==1&&ischoose==1&&m1.x>=600&&m1.x<=724&&m1.y>=525&&m1.y<=568))//再次点该牌或点取消，牌下降
 					{
						clearpai();
						outPlayerDiscardWriting(k1);
						FlushBatchDraw();//批量绘制一次
						ischoose = 0;
					}
					else if(ischoose==1&&m1.x>=400&&m1.x<=524&&m1.y>=img_top&&m1.y<=img_top+39)//牌被打出
					{
						cleardevice();
						k1--;
						placeequipment();
						if(k1>0)
							outPlayerDiscardWriting(k1);
						putimage(pail[6].x, pail[1].y, &paidui[playerpai[n1]].im);//打出所点击牌
						playerpai[n1]=-1;//该牌消失
						playershoupai--;//玩家手牌数减一
						putimage(400, img_top, &im_right0);
						putimage(600, img_top, &im_cance0);
						adjustpai(playerpai);
						placeshoupai();
						FlushBatchDraw();//批量绘制一次;
						Sleep(1500);
						clearpai();
						if(k1>0)
							outPlayerDiscardWriting(k1);
						FlushBatchDraw();//批量绘制一次
						ischoose = 0;
					}
					paistate = 1;
				}
				if(k1==0)
				{
					end = 0;
					break;
				}
			}
		}
		else end = 0;
		huihe=1;//npc回合
		cleardevice();
		placeequipment();
		placeshoupai();
		nextHuihe(npcpai);
	}
	else//npc弃牌
	{
		if(npcshoupai>npclife)
		{
			int k2=npcshoupai-npclife;
			while(k2>0)
			{
				int p=rand()%npcshoupai;
				putimage(pail[6].x, pail[1].y, &paidui[npcpai[p]].im);//打出所点击牌
				outNpcDiscardWritng();
				npcshoupai--;
				npcpai[p]=-1;
				adjustpai(npcpai);
				FlushBatchDraw();//批量绘制一次
				Sleep(1500);
				clearpai();
				k2--;
				if(k2>0)//避免最后一张牌弃完后文字还在
					outNpcDiscardWritng();
				FlushBatchDraw();//批量绘制一次
				Sleep(500);
			}
		}
	}
	EndBatchDraw();//结束批量绘制
}

void npcchupai(int i)
{
	putimage(pail[6].x, pail[1].y, &paidui[npcpai[i]].im);//打出所点击牌
	judgemusic(npcpai[i]);
	judgeequipment(npcpai[i]);
	chupainum=1;
	npcshoupai--;
	npcpai[i]=-1;
	adjustpai(npcpai);
	FlushBatchDraw();
	Sleep(1500);
	clearpai();
	FlushBatchDraw();
}

void playerchusha(int j)
{
	int i;
	cleardevice();
	placeequipment();
	putimage(400, img_top, &im_right1);
	putimage(600, img_top, &im_cancel);
	for(i = 0;i<6;i++)
	{
		if(playerpai[i]!=-1)
		{
			if(i!=j)
				putimage(pail[i].x, img_y, &paidui[playerpai[i]].im);//未点击牌不动
			else 
				putimage(pail[i].x, pail[0].y, &paidui[playerpai[i]].im);//所点击牌移动
		}
	}
	outchusha();
	FlushBatchDraw();
	while(1)
	{
		m2 = GetMouseMsg();//获取鼠标信息
		if(m2.uMsg==WM_LBUTTONDOWN)//点击鼠标左键
		{
			if(m2.x>=400&&m2.x<=524&&m2.y>=img_top&&m2.y<=img_top+39)//点击确定
			{
				cleardevice();
				placeequipment();
				putimage(pail[6].x, pail[1].y, &paidui[playerpai[j]].im);//打出所点击牌
				judgemusic(playerpai[j]);//播放音效
				playerpai[j]=-1;//该牌消失
				playershoupai--;//玩家手牌数减一
				adjustpai(playerpai);
				placeshoupai();
				FlushBatchDraw();
				Sleep(1500);
				clearpai();
				FlushBatchDraw();
				if(guannum[1]==1&&npcshoupai>=2)
					guanshi();
				break;
			}
			else if(m2.x>=600&&m2.x<=724&&m2.y>=img_top&&m2.y<=img_top+43)//点击取消
			{
				playerlife-=shanghai;
				int horsenum=0;
				if(attackhorse[0]==1)
				{
					attackhorse[0]=0;
					horsenum++;
				}
				if(defendhorse[0]==1&&horsenum==0)
					defendhorse[0]=0;
				clearpai();
				FlushBatchDraw();
				break;
			}
			judgelife();
		}
	}
	Sleep(500);
}

void playerchushan(int j)
{
	int i;
	cleardevice();
	placeequipment();
	putimage(400, img_top, &im_right1);
	putimage(600, img_top, &im_cancel);
	for(i = 0;i<6;i++)
	{
		if(playerpai[i]!=-1)
		{
			if(i!=j)
				putimage(pail[i].x, img_y, &paidui[playerpai[i]].im);//未点击牌不动
			else 
				putimage(pail[i].x, pail[0].y, &paidui[playerpai[i]].im);//所点击牌移动
		}
	}
	outchushan();
	FlushBatchDraw();
	while(1)
	{
		m2 = GetMouseMsg();//获取鼠标信息
		if(m2.uMsg==WM_LBUTTONDOWN)//点击鼠标左键
		{
			if(m2.x>=400&&m2.x<=524&&m2.y>=img_top&&m2.y<=img_top+39)//点击确定
			{
				cleardevice();
				placeequipment();
				putimage(pail[6].x, pail[1].y, &paidui[playerpai[j]].im);//打出所点击牌
				judgemusic(playerpai[j]);//播放音效
				playerpai[j]=-1;//该牌消失
				playershoupai--;//玩家手牌数减一
				adjustpai(playerpai);
				placeshoupai();
				FlushBatchDraw();
				Sleep(1500);
				clearpai();
				FlushBatchDraw();
				if(guannum[1]==1&&npcshoupai>=2&&wanjian==0)
					guanshi();
				break;
			}
			else if(m2.x>=600&&m2.x<=724&&m2.y>=img_top&&m2.y<=img_top+43&&wanjian==0)//点击取消
			{
				playerlife-=shanghai;
				clearpai();
				FlushBatchDraw();
				break;
			}
			judgelife();
		}
	}
	Sleep(500);
}

void npcshow()//npc出牌
{
	int i,j, k=0;
	chupainum = 0;//未出牌
	BeginBatchDraw();
	if(npcshan==0)
		Sleep(1500);
	else Sleep(500);
	clearpai();
	FlushBatchDraw();
	if(npcshan==0)
	{
		while(chupainum==0)//未出牌
		{
			shanghai = 1;
			for(i=0;i<6;i++)
				if(npclife<4)
					if(npcpai[i]>=35&&npcpai[i]<43)//桃
					{
						npclife++;
						npcchupai(i);
						Sleep(1000);
					}
			for(i = 0;i<6;i++)
				if(npcpai[i]>=45&&npcpai[i]<49)//是否有顺手牵羊
				{
					npcchupai(i);
					wuxie();
					if(wuxienum==0)
					{
						Sleep(500);
						npcpai[5]=playerpai[0];
						playerpai[0]=-1;
						playershoupai--;
						npcshoupai++;
						adjustpai(playerpai);
						adjustpai(npcpai);
						clearpai();
						Sleep(1500);
					}
					wuxienum=0;
				}
			for(i = 0;i<6;i++)
				if(npcpai[i]>=49&&npcpai[i]<53)//是否有过河拆桥
				{
					npcchupai(i);
					wuxie();
					if(wuxienum==0)
					{
						Sleep(500);
						putimage(pail[6].x, pail[1].y, &paidui[playerpai[0]].im);//打出所点击牌
						FlushBatchDraw();
						playerpai[0]=-1;
						playershoupai--;
						adjustpai(playerpai);
						Sleep(1500);
						clearpai();
						Sleep(1500);
					}
					wuxienum=0;
				}
			for(i = 0;i<6;i++)
				if(npcpai[i]>=53&&npcpai[i]<56)//是否有决斗
				{
					wuxie();
					if(wuxienum==0)
					{
						npcchupai(i);
						juedou();
						Sleep(1000);
					}
					wuxienum=0;
				}
			for(i=0;i<6;i++)
				if(npcpai[i]>=69&&npcpai[i]<71)//是否有南蛮入侵
				{
					npcchupai(i);
					nanman();
					Sleep(1000);
				}
			for(i = 0;i<6;i++)
				if(npcpai[i]>=43&&npcpai[i]<45)//判断是否有八卦阵
				{
					npcchupai(i);
					Sleep(1000);
					break;
				}
			for(i = 0;i<6;i++)
				if(npcpai[i]>=64&&npcpai[i]<66)//是否有坐骑牌
				{
					npcchupai(i);
					Sleep(1000);
					break;
				}
			for(i = 0;i<6;i++)
				if(npcpai[i]==66)//是否有麒麟弓
				{
					npcchupai(i);
					Sleep(1000);
					break;
				}
			for(i = 0;i<6;i++)
				if(npcpai[i]==67)//是否有青釭剑
				{
					npcchupai(i);
					Sleep(1000);
					break;
				}
			for(i = 0;i<6;i++)
				if(npcpai[i]==68)//是否有贯石斧
				{
					npcchupai(i);
					Sleep(1000);
					break;
				}
			for(i = 0;i<6;i++)
				if(npcpai[i]>=60&&npcpai[i]<64)//是否有酒
				{
					jiunum++;
					npcchupai(i);
					Sleep(1000);
					break;
				}
			for(i = 0;i<6;i++)
			{
				if((npcpai[i]>=0&&npcpai[i]<20)||(npcpai[i]>=71&&npcpai[i]<73))//判断是否有杀和万箭齐发
				{
					if(npcpai[i]>=71&&npcpai[i]<73)
						wanjian=1;
					npcchupai(i);
					Sleep(500);
					if(jiunum==1&&wanjian==0)
					{
						shanghai++;
						jiunum=0;
					}
					for(j=0;j<6;j++)
					{
						if(playerpai[j]>=20&&playerpai[j]<35)//玩家有闪
						{
							playerchushan(j);
							break;
						}
					}
					if(j==6&&baguanum1==1&&qingnum[1]==0)
					{
						Playerbagua();
						Sleep(1000);
					}
					if(j==6&&shengxiao1!=1)
					{
						playerlife-=shanghai;
						clearpai();
						FlushBatchDraw();
						if(qilingnum[1]==1&&(attackhorse[0]==1||defendhorse[0]==1)&&wanjian==0)
							qiling();
					}
					clearpai();
					judgelife();
					wanjian=0;
					if(playerlife<=0)
						break;
					FlushBatchDraw();
				}
				shanghai=1;
			}
			chupainum=1;
			shanghai=1;
		}
		if(playerlife>0)
		{
			jiunum=0;
			discard();
			huihe = 0;
			huihenum++;
			clearpai();
			FlushBatchDraw();
			nextHuihe(playerpai);
			Sleep(1000);
		}
	}
	else
	{
		for(i = 0;i<6;i++)
		{
			if(npcpai[i]>=20&&npcpai[i]<35&&wuxienum==0)//是否有闪并打出
			{
				npcchupai(i);
				if(guannum[0]==1&&playershoupai>=2&&wanjian==0)
					guanshi();
				break;
			}
			k++;
		}
		if(k==6)
		{
			if(baguanum2==1&&qingnum[0]==0&&wuxienum==0)
			{
				Npcbagua();
				Sleep(500);
			}
			if(shengxiao2!=1&&wuxienum==0)
			{
				npclife-=shanghai;
				clearpai();
				FlushBatchDraw();
				if(qilingnum[0]==1&&(attackhorse[1]==1||defendhorse[1]==1)&&wanjian==0)
					qiling();
			}
		}
		judgelife();
		shanghai = 1;
	}
	EndBatchDraw();
}

void playershow(int xi)//图片处理
{
	int i, k = playerpai[xi];
	cleardevice();//清屏函数
	BeginBatchDraw();//开始批量绘制
	placeequipment();
	if(ischoose==0&&shannum==0)//选中牌不为闪
	{
		//放置红色确定取消
		putimage(400, img_top, &im_right1);
		putimage(600, img_top, &im_cancel);
	}
	else if(ischoose==0&&shannum==1)//选中牌为闪
	{
		//放置灰色确定，红色取消
		putimage(400, img_top, &im_right0);
		putimage(600, img_top, &im_cancel);
	}
	else//再次点击选中牌
	{
		//放置灰色确定取消
		putimage(400, img_top, &im_right0);
		putimage(600, img_top, &im_cance0);
	}
	if(ischoose == 0&&paistate == 1)//所点击牌y坐标增加
		img_h-=vy;
	else if(ischoose == 1&&paistate == 1)//所点击牌y坐标减少
		img_h+=vy;
	if(paistate==1)//放置选中的牌，但不打出
	{
		for(i = 0;i<6;i++)
		{
			if(playerpai[i]!=-1)
			{
				if(i!=xi)
					putimage(pail[i].x, img_y, &paidui[playerpai[i]].im);//未点击牌不动
				else 
					putimage(pail[i].x, img_h, &paidui[playerpai[i]].im);//所点击牌移动
			}
		}
		FlushBatchDraw();//批量绘制一次
	}
	else
	{
		putimage(pail[6].x, pail[1].y, &paidui[playerpai[xi]].im);//打出所点击牌
		judgemusic(playerpai[xi]);//播放音效
		judgeequipment(playerpai[xi]);//判断打出牌是否为装备牌
		playerpai[xi]=-1;//该牌消失
		playershoupai--;//玩家手牌数减一
		adjustpai(playerpai);
		placeshoupai();
		FlushBatchDraw();//批量绘制一次
		Sleep(1500);
		clearpai();//清除打出的牌
		FlushBatchDraw();//批量绘制一次
		playerpaieffect(k);
		EndBatchDraw();//结束批量绘制
	}
	Sleep(3);
}

int n = 0;
void nextHuihe(int card2[])//结束赋玩家两张牌
{
	int i, j;
	for(i=0;i<6;i++)
	{
		if(card2[i]==-1)
		{
			if(huihe==0)//赋给玩家两张牌
			{
				for(j=i;j<i+2;j++)
				{
					playershoupai++;
					card2[j] = a[usenum];
					usenum++;
					if(usenum>72)
					{
						xipai();
						usenum=0;
					}
					putimage(img_x+x1*j,img_y,&paidui[card2[j]].im);
				}
				EndBatchDraw();
				break;
			}
			else//赋npc两张牌
			{
				for(j=i;j<i+2;j++)
				{
					npcshoupai++;
					card2[j] = a[usenum];
					usenum++;
					if(usenum>72)
					{
						xipai();
						usenum=0;
					}
				}
				if(ischoose==1)//点击结束时若有手牌被选中手牌回原来位置
				{
					while(img_h<590)
						playershow(n);
				}
				break;
			}
		}
	}
}

int playerfenxi()//对鼠标信息进行分析并进行牌的移动
{
	if(m.x>=775&&m.x<=873&&m.y>=img_top&&m.y<=img_top+44)//点击结束
	{
		end = 1;
		return 0;
	}
	if(ischoose==1&&m.x>=400&&m.x<=524&&m.y>=img_top&&m.y<=img_top+39)//点击确定
		paistate = 0;
	if(paistate==1&&!(m.x>=600&&m.x<=724&&m.y>=img_top&&m.y<=img_top+43))//点击牌区
		n = (m.x - 195)/x1;//赋予牌所在位置序号
	if((playerpai[n]>=20&&playerpai[n]<35)//点击牌为闪
		||(playerpai[n]>=56&&playerpai[n]<60)//点击牌为无懈可击
		||(playerpai[n]>=35&&playerpai[n]<43&&playerlife==4))//满血时点击桃
		shannum++;
	if(paistate==0&&shannum==1)//如果闪被选中且点击确定
		paistate = 1;
	if(ischoose==0&&m.x>=195+x1*n&&m.x<=311+x1*n&&m.y>=590&&m.y<=753)//牌上升，被选中
	{
		while(img_h>=560)
			playershow(n);
		if(shannum==1)
			shannum--;
		return 1;//返回1
	}
	if((ischoose==1&&m.x>=195+x1*n&&m.x<=311+x1*n&&m.y>=560&&m.y<=723)||
		(ischoose==1&&m.x>=600&&m.x<=724&&m.y>=img_top&&m.y<=img_top+43))//再次点该牌或点取消，牌下降
	{
		while(img_h<590)
			playershow(n);
		if(shannum==1)
			shannum--;
		return 0;//返回0
	}
	if(ischoose==1&&m.x>=400&&m.x<=524&&m.y>=img_top&&m.y<=img_top+39&&shannum==0)//牌被打出
	{
		img_h = 590;
		playershow(n);
		paistate = 1;
		if(shannum==1)
			shannum--;
		return 0;//返回0
	}
	if(shannum==1)
		shannum--;
	return 0;//返回0
}

void update()//鼠标点击更新
{
	while(1)
	{
		if(end1==0)
		{
			while(huihe==0)
			{
				if(end==0)
				{
					if(end1==0)
					{
						m = GetMouseMsg();//获取鼠标信息
						if(huihe==0)//玩家回合
							if(m.uMsg==WM_LBUTTONDOWN)//点击鼠标左键
								ischoose = playerfenxi();
					}
					else break;
				}
				else discard();
			}
			if(end1==0)
				npcshow();
		}
		else break;
	}
}

int main()
{
	srand(time(0));//随机种子
	startuppicture();
	startupdenglu();
	loading();
	startup();
	update();
	_getch();
}