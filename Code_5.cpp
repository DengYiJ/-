#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>
#include<Windows.h>
#include<time.h>
#pragma comment(lib, "Winmm.lib")
#define  WIDTH 1250 // ������
#define  HEIGHT 760 // ����߶�
#define vy 5//�����ƶ��ٶ�
#define x1 120//���Ƽ���
#define img_x 195//��������x����
#define img_y 590//����y����
#define img_top 525//ȷ��ȡ��y����
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

int img_h = 590;//ͼƬy����
IMAGE im_bk;//����ͼ
IMAGE im_right1, im_cancel, im_right0, im_cance0, im_end;//ȷ����ȡ��������ͼƬ
IMAGE  im_arm[2], im_defendhorse[2], im_attackhorse[2],im_defend[2];//װ����ͼƬ
IMAGE �������ҷ�, ������з�,�����ҷ�,���õз�,צ�Ʒɵ�з�,צ�Ʒɵ��ҷ�;//װ����װ����
IMAGE ��ʯ���ҷ�,��ʯ���з�,���빭�ҷ�,���빭�з�,���G���ҷ�,���G���з�;
IMAGE �ƶѻغ���;
IMAGE ��¼����;
IMAGE im_loading;//���ر���
IMAGE im_renwu[2];//����ͼ
IMAGE im_bagua[2];//������
IMAGE im_playerblood[5],im_npcblood[5];
MOUSEMSG m,m0,m1,m2,m3,m4,m5;//�����Ϣ
int ischoose = 0, paistate = 1;//��δ��ѡ��
int a[73];//�����
int usenum = 0;//��ʹ��������
int playerpai[6] = {-1,-1,-1,-1,-1,-1},npcpai[6] = {-1,-1,-1,-1,-1,-1};//���浱ǰ����
int playershoupai = 0, npcshoupai = 0;//��ǰ����
int defendnum[2]={0,0},attackhorse[2]={0,0},defendhorse[2]={0,0};//װ������������
int qingnum[2]={0,0},qilingnum[2]={0,0},guannum[2]={0,0};//װ����������
int shannum = 0;//ÿ�غϴ����
int huihe = 0;//��һغ�
int defendlocation[2] = {625,178};//װ��������y����
int armlocation[2]={580,160};//װ��������y����
int dhorselocation[2]={720,212};//װ����������y����
int ahorselocation[2]={675,195};//װ����������y����
int elocation[2]={2,547};//װ����װ��λ��x����
int shalimitation = 1;//��ɱ������������
int npcshan = 0;//��Ҵ��ɱʱnpc�������
int end1 = 0, end = 0;//
int chupainum = 0;//npc����
int jiunum = 0;//����ľƵ�����
int shanghai = 1;//ɱ�˺���ֵ
int npclife = 4, playerlife = 4;//npc���������ֵ
int baguanum1 = 0, baguanum2 = 0,shengxiao1 = 0, shengxiao2 = 0;//�������Ƿ���Ч
int huihenum=1;//�غ���
int wanjian=0;//�Ƿ�������뷢
int wuxienum=0;//�Ƿ�����и�ɻ�

struct pai//�����Ƶ���š�ͼ��
{
	int type;
	int num;
	IMAGE im;
};

struct location//�Ƶ�λ��
{
	int x;//x����
	int y;//y����
};

pai paidui[73];
location pail[7];

void xipai()//ϴ�ƺ���
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

void startuppicture()//���Ƹ���ͼ��
{
	int i;
	for(i = 0;i<73;i++)
		paidui[i].num = i + 1;
	for(i = 0;i<20;i++)
		loadimage(&paidui[i].im, _T("ɱ.jpg"));
	for(i = 20;i<35;i++)
		loadimage(&paidui[i].im, _T("��.jpg"));
	for(i = 35;i<43;i++)
		loadimage(&paidui[i].im, _T("��.jpg"));
	for(i = 43;i<45;i++)
		loadimage(&paidui[i].im, _T("������.png"));
	for(i = 45;i<49;i++)
		loadimage(&paidui[i].im, _T("˳��ǣ��.png"));
	for(i = 49;i<53;i++)
		loadimage(&paidui[i].im, _T("���Ӳ���.png"));
	for(i = 53;i<56;i++)
		loadimage(&paidui[i].im, _T("����.png"));
	for(i = 56;i<60;i++)
		loadimage(&paidui[i].im, _T("��и�ɻ�.png"));
	for(i = 60;i<64;i++)
		loadimage(&paidui[i].im, _T("��.jpg"));
	loadimage(&paidui[64].im, _T("צ�Ʒɵ�.png"));
	loadimage(&paidui[65].im, _T("����.png"));
	loadimage(&paidui[66].im, _T("���빭.png"));
	loadimage(&paidui[67].im, _T("���G��.png"));
	loadimage(&paidui[68].im, _T("��ʯ��.png"));
	for(i=69;i<71;i++)
		loadimage(&paidui[i].im, _T("��������.jpg"));
	for(i = 71;i<73;i++)
		loadimage(&paidui[i].im, _T("����뷢.jpg"));
	loadimage(&�������ҷ�,_T("�������ҷ�.PNG"));
	loadimage(&������з�,_T("������з�.PNG"));
	loadimage(&���õз�,_T("���õз�.PNG"));
	loadimage(&�����ҷ�,_T("�����ҷ�.PNG"));
	loadimage(&צ�Ʒɵ��ҷ�,_T("צ�Ʒɵ��ҷ�.PNG"));
	loadimage(&צ�Ʒɵ�з�,_T("צ�Ʒɵ�з�.PNG"));
	loadimage(&��ʯ���з�,_T("��ʯ���з�.PNG"));
	loadimage(&��ʯ���ҷ�,_T("��ʯ���ҷ�.PNG"));
	loadimage(&���G���з�,_T("���G���з�.PNG"));
	loadimage(&���G���ҷ�,_T("���G���ҷ�.PNG"));
	loadimage(&���빭�з�,_T("���빭�з�.PNG"));
	loadimage(&���빭�ҷ�,_T("���빭�ҷ�.PNG"));
	loadimage(&im_playerblood[0],_T("4Ѫ0.png"));
	loadimage(&im_playerblood[1],_T("4Ѫ1.png"));
	loadimage(&im_playerblood[2],_T("4Ѫ2.png"));
	loadimage(&im_playerblood[3],_T("4Ѫ3.png"));
	loadimage(&im_playerblood[4],_T("4Ѫ4.png"));
	loadimage(&im_npcblood[4],_T("�з�4Ѫ4.png"));
	loadimage(&im_npcblood[3],_T("�з�4Ѫ3.png"));
	loadimage(&im_npcblood[2],_T("�з�4Ѫ2.png"));
	loadimage(&im_npcblood[1],_T("�з�4Ѫ1.png"));
	loadimage(&im_npcblood[0],_T("�з�4Ѫ0.png"));
	loadimage(&im_right1, _T("ȷ��1.png"));
	loadimage(&im_cancel, _T("ȡ��1.png"));
	loadimage(&im_right0, _T("ȷ��0.png"));
	loadimage(&im_cance0, _T("ȡ��0.png"));
	loadimage(&�ƶѻغ���,_T("�ƶѻغ���.png"));
	loadimage(&im_bk, _T("����.png"));
	loadimage(&im_end, _T("����.png"));
	loadimage(&im_bagua[0], _T("�ж��ɹ�.png"));
	loadimage(&im_bagua[1], _T("�ж�ʧ��.png"));
	loadimage(&im_renwu[0], _T("�ŷ�.png"));
	loadimage(&im_renwu[1], _T("�з��ŷ�.png"));
	loadimage(&��¼����, _T("��¼����.png"));
	loadimage(&im_loading,_T("����ͼƬ.png"));
}

void startupdenglu()//������Ϸ����
{
	initgraph(WIDTH,HEIGHT);
	putimage(0,0,&��¼����);
	while(1)
	{
		m0 = GetMouseMsg();//��ȡ�����Ϣ
		if(m0.uMsg==WM_LBUTTONDOWN)//���������
		{
			if(m0.x>=510&&m0.x<=682&&m0.y>=492&&m0.y<=538)
				break;
		}
	}
}

void loading()//���ؽ���
{	
	clock_t start, now; // ���ڼ�ʱ�ı���
	start = clock(); // ��¼��ǰ����ʱ��
	float maxTime = 2; // ����ʱ��
	float remainTime = maxTime; // ʣ��ʱ��
	BeginBatchDraw();//��ʼ��������
	while (remainTime>=0)// ѭ��
	{
		now = clock(); // ��õ�ǰʱ��
		// �������һ�������˶�����
		double duration =( double(now - start) / CLOCKS_PER_SEC); 
		remainTime = maxTime - duration; // ����ʣ��ʱ��
		cleardevice(); // ����
		putimage(0,0,&im_loading);//���ü���ͼƬ
		setbkmode(TRANSPARENT);
		setlinecolor(HSVtoRGB(60,1,1)); // ���ý���������ɫ
		setfillcolor(HSVtoRGB(60,1,1));
		fillrectangle(0,749,duration*1250/maxTime,750); // ���ƽ�����
		FlushBatchDraw();//��������һ��
		Sleep(20); // ��ͣ20����
	}
	EndBatchDraw();//������������
}

void startup()//��ʼ��Ϸ����
{
	putimage(0, 0, &im_bk);	// ��ʾ����ͼƬ	
	putimage(775, img_top, &im_end);
	putimage(1095,35,&�ƶѻغ���);
	putimage(1058,540,&im_renwu[0]);
	putimage(550,49,&im_renwu[1]);
	outround();
	int i;
	for(i = 0;i<6;i++)
		pail[i].x = img_x + i * x1;//������λ��x����
	pail[6].x = 565;//���м�x����
	pail[0].y = 560;//��΢����y����
	pail[1].y = 270;//���м�y����
	xipai();//���ϴ��
	for(i = 0;i < 8; i++)
	{
		if(i%2==0)
		{
			playershoupai++;//���������+1
			playerpai[i/2] = a[usenum];//�����������
			putimage(img_x+x1*(i/2),img_y,&paidui[playerpai[i/2]].im);//��ͼ
		}
		else 
		{
			npcshoupai++;
			npcpai[i/2] = a[usenum];//����npc����
		}
		usenum++;//��ʹ������+1
	}
	for(i=4;i<6;i++)//����ȳ��֣���������
	{
		playershoupai++;
		playerpai[i] = a[usenum];
		putimage(img_x+x1*i,img_y,&paidui[playerpai[i]].im);
		usenum++;
	}
	outpaiduinum();
	outpainum();
	mciSendString(_T("open ��������.mp3 alias bkmusic"), NULL, 0, NULL);//�򿪱�������.
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//ѭ������
}

void playmusiconce(TCHAR fileName[80])//��Ч���ź���
{
	TCHAR cmdString1[50];
	_stprintf(cmdString1, _T("open %s alias tmpmusic"), fileName); // ���������ַ���
	mciSendString(_T("close tmpmusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
	mciSendString(cmdString1, NULL, 0, NULL); // ������
	mciSendString(_T("play tmpmusic"), NULL, 0, NULL); // ������һ��
}

void judgemusic(int i)//�ж���Ч����
{
	if(i>=0&&i<20)
		playmusiconce(_T("ɱ��.wav"));
	else if(i>=20&&i<35)
		playmusiconce(_T("����.mp3"));
	else if(i>=35&&i<43)
		playmusiconce(_T("ʹ����.mp3"));
	else if(i>=43&&i<45)
		playmusiconce(_T("������.mp3"));
	else if(i>=45&&i<49)
		playmusiconce(_T("˳��ǣ��.mp3"));
	else if(i>=49&&i<53)
		playmusiconce(_T("���Ӳ�����.mp3"));
	else if(i>=53&&i<56)
		playmusiconce(_T("����.mp3"));
	else if(i>=56&&i<60)
		playmusiconce(_T("��и�ɻ�.mp3"));
	else if(i>=60&&i<64)
		playmusiconce(_T("����.mp3"));
	else if(i>=64&&i<66)
		playmusiconce(_T("ʹ��������.mp3"));
	else if(i==67)
		playmusiconce(_T("���G��.mp3"));
	else if(i>=69&&i<71)
		playmusiconce(_T("��������.mp3"));
	else if(i>=71&&i<73)
		playmusiconce(_T("����뷢.mp3"));
}

void placeequipment()//���ñ����������������װ��������װ����
{
	int i;
	putimage(0, 0, &im_bk);
	putimage(775, img_top, &im_end);
	putimage(1095,35,&�ƶѻغ���);
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

void placeshoupai()//��������ͼ��
{
	int i;
	for(i=0;i<6;i++)
		if(playerpai[i]!=-1)
			putimage(pail[i].x,img_y,&paidui[playerpai[i]].im);
}

void Playerbagua()//������Ч��
{
	int j = rand()%2;
	shengxiao1 = 0;
	putimage(400, img_top, &im_right1);
	putimage(600, img_top, &im_cancel);
	outbagua();
	FlushBatchDraw();
	while(1)
	{
		m3 = GetMouseMsg();//��ȡ�����Ϣ
		if(m3.uMsg==WM_LBUTTONDOWN)//���������
		{
			if(m3.x>=400&&m3.x<=524&&m3.y>=img_top&&m3.y<=img_top+39)//���ȷ��
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
			if(m3.x>=600&&m3.x<=724&&m3.y>=img_top&&m3.y<=img_top+43)//���ȡ��
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

void judgeequipment(int i)//�ж��Ƿ�Ϊװ����
{
	if(i>=43&&i<45)
	{
		if(huihe==0)
		{
			im_defend[0] = �������ҷ�;
			putimage(elocation[0], defendlocation[0], &im_defend[0]);
			if(defendnum[0]==0)
			{
				defendnum[0]++;
				baguanum1++;
			}
		}
		else
		{
			im_defend[1] = ������з�;
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
			im_defendhorse[0] = �����ҷ�;
			putimage(elocation[0], dhorselocation[0], &im_defendhorse[0]);
			defendhorse[0]++;
		}
		else
		{
			im_defendhorse[1] = ���õз�;
			putimage(elocation[1], dhorselocation[1], &im_defendhorse[1]);
			defendhorse[1]++;
		}
	}
	else if(i==64)
	{
		if(huihe==0)
		{
			im_attackhorse[0] = צ�Ʒɵ��ҷ�;
			putimage(elocation[0], ahorselocation[0], &im_attackhorse[0]);
			attackhorse[0]++;
		}
		else
		{
			im_attackhorse[1] = צ�Ʒɵ�з�;
			putimage(elocation[1], ahorselocation[1], &im_attackhorse[1]);
			attackhorse[1]++;
		}
	}
	else if(i==67)
	{
		if(huihe==0)
		{
			qingnum[0]++;
			im_arm[0] = ���G���ҷ�;
			putimage(elocation[0], armlocation[0], &im_arm[0]);
			guannum[0]=0;
			qilingnum[0]=0;
		}
		else 
		{
			qingnum[1]++;
			im_arm[1] = ���G���з�;
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
			im_arm[0] = ��ʯ���ҷ�;
			putimage(elocation[0], armlocation[0], &im_arm[0]);
			qingnum[0]=0;
			qilingnum[0]=0;
		}
		else 
		{
			guannum[1]++;
			im_arm[1] = ��ʯ���з�;
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
			im_arm[0] = ���빭�ҷ�;
			putimage(elocation[0], armlocation[0], &im_arm[0]);
			guannum[0]=0;
			qingnum[0]=0;
		}
		else 
		{
			qilingnum[1]++;
			im_arm[1] = ���빭�з�;
			putimage(elocation[1], armlocation[1], &im_arm[1]);
			guannum[1]=0;
			qingnum[1]=0;
		}
	}
}

void adjustpai(int card1[])//�����������
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

void clearpai()//����Ѵ����
{
	cleardevice();//����
	placeequipment();
	//���û�ɫȷ��ȡ��
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
	int k = 0;//��һ��˻��Ƿ��ɱ
	int ns = 0;//�˻�����ɱ������
	int ps = 0;//�������ɱ������
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
						playmusiconce(_T("ɱ��.wav"));
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
							playmusiconce(_T("ɱ��.wav"));
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
						playmusiconce(_T("ɱ��.wav"));
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
							putimage(pail[j].x, img_y, &paidui[playerpai[j]].im);//δ����Ʋ���
						else 
							putimage(pail[j].x, pail[0].y, &paidui[playerpai[j]].im);//��������ƶ�
					}
				}
				outwuxie();
				FlushBatchDraw();
				while(1)
				{
					m5 = GetMouseMsg();//��ȡ�����
					if(m5.uMsg==WM_LBUTTONDOWN)//���������
					{
						if(m5.x>=400&&m5.x<=524&&m5.y>=img_top&&m5.y<=img_top+39)//���ȷ��
						{
							wuxienum=1;
							cleardevice();
							placeequipment();
							putimage(pail[6].x, pail[1].y, &paidui[playerpai[i]].im);//����������
							judgemusic(playerpai[i]);//������Ч
							playerpai[i]=-1;//������ʧ
							playershoupai--;//�����������һ
							adjustpai(playerpai);
							placeshoupai();
							FlushBatchDraw();
							Sleep(1500);
							clearpai();
							FlushBatchDraw();
							break;
						}
						else if(m2.x>=600&&m2.x<=724&&m2.y>=img_top&&m2.y<=img_top+43&&wanjian==0)//���ȡ��
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
				playmusiconce(_T("ɱ��.wav"));
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

void playerpaieffect(int i)//��Ҵ���Ƶ�Ч��
{
	if((i>=0&&i<20)||(i>=71&&i<73))//ɱ������뷢
	{
		if(i>=71&&i<73)//������뷢
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
	else if(i>=35&&i<43)//��
	{
		if(huihe==0&&playerlife<4)
		{
			playerlife++;
			clearpai();
		}
		else if(huihe==1&&npclife<4)
			npclife++;
	}
	else if(i>=45&&i<49)//˳��ǣ��
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
	else if(i>=49&&i<53)//���Ӳ���
	{
		wuxie();
		if(npcshoupai>0&&wuxienum==0)
		{
			Sleep(500);
			putimage(pail[6].x, pail[1].y, &paidui[npcpai[0]].im);//�����Է���һ����
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
	else if(i>=69&&i<71)//��������
		nanman();
	else if(i>=53&&i<56)//����
	{
		wuxie();
		if(wuxie==0)
			juedou();
		wuxienum=0;
	}
	else if(i>=60&&i<64)//��
		if(shanghai=1)
			shanghai++;//ɱ�˺�����
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
			m3 = GetMouseMsg();//��ȡ�����Ϣ
			if(m3.uMsg==WM_LBUTTONDOWN)//���������
			{
				if(m3.x>=400&&m3.x<=524&&m3.y>=img_top&&m3.y<=img_top+39)//���ȷ��
				{
					playmusiconce(_T("��ʯ��.mp3"));
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
				else if(m3.x>=600&&m3.x<=724&&m3.y>=img_top&&m3.y<=img_top+43)//���ȡ��
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
			m4 = GetMouseMsg();//��ȡ�����Ϣ
			putimage(400, img_top, &im_right1);
			putimage(600, img_top, &im_cancel);
			outqiling();
			FlushBatchDraw();
			if(m4.uMsg==WM_LBUTTONDOWN)//���������
			{
				if(m4.x>=400&&m4.x<=524&&m4.y>=img_top&&m4.y<=img_top+39)//���ȷ��
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
				else if(m4.x>=600&&m4.x<=724&&m4.y>=img_top&&m4.y<=img_top+43)//���ȡ��
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
				putimage(pail[6].x, pail[1].y, &paidui[playerpai[i]].im);//����������
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
		setbkmode(TRANSPARENT); // ��������͸��
		if(huihe==0)
			_stprintf(s, _T("��Ϸ���������ʤ��"));
		else _stprintf(s, _T("��Ϸ�������˻�ʤ��"));
		settextcolor(BLACK); // �趨������ɫ
		settextstyle(60, 0, _T("����"));//  �趨���ִ�С����ʽ
		outtextxy(360, 350, s); //  �����������
		end1 = 1;
	}
}

void outbagua()//����Ƿ�ʹ�ð�����
{
	TCHAR s1[] = _T("�Ƿ�ʹ�ð�����");
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(30,0,_T("Times"));
	outtextxy(550, 500, s1);
}

void outwuxie()
{
	TCHAR s1[] = _T("�Ƿ�ʹ����и�ɻ�");
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(30,0,_T("Times"));
	outtextxy(520, 490, s1);
}

void outchusha()//����Ƿ���ɱ
{
	TCHAR s1[] = _T("����һ��ɱ");
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(30,0,_T("Times"));
	outtextxy(550, 490, s1);
}

void outPlayerDiscardWriting(int i)//�����������
{
	TCHAR s1[100],s2[100];
	setbkmode(TRANSPARENT); // ��������͸��
	_stprintf(s2, _T("���ƽ׶�"));
	_stprintf(s1, _T("����Ҫ����%d����"), i);	
	settextcolor(WHITE); // �趨������ɫ
	settextstyle(20, 0, _T("����"));//  �趨���ִ�С����ʽ
	outtextxy(580,470,s2);
	outtextxy(550, 500, s1); //  �����������
}

void outNpcDiscardWritng()
{
	TCHAR s1[100];
	setbkmode(TRANSPARENT); // ��������͸��
	_stprintf(s1, _T("�Է����ƽ׶�"));	
	settextcolor(WHITE); // �趨������ɫ
	settextstyle(20, 0, _T("����"));//  �趨���ִ�С����ʽ
	outtextxy(550, 500, s1); //  �����������
}

void outpainum()//������Ѫ�����˻���������Ѫ��
{
	int i;
	TCHAR s[20]; // �����ַ�������
	setbkmode(TRANSPARENT);
	_stprintf(s, _T("%d"), npcshoupai); // ��Npaiת��Ϊ�ַ���
	settextstyle(35, 0, _T("Times")); // �������ִ�С������
	settextcolor(WHITE);  // ����������ɫΪ��ɫ
	outtextxy(550, 120, s); // ����˻�������
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

void outchushan()//����Ƿ�����
{
	TCHAR s1[] = _T("������һ����");
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
		_stprintf(s, _T("�Ƿ񷢶����빭��Ч(�����Է���һ����)"));
	else _stprintf(s, _T("�з��������빭��Ч(�����ҷ���һ����)"));
	settextcolor(WHITE);  // ����������ɫΪ��ɫ
	settextstyle(20, 0, _T("����"));//  �趨���ִ�С����ʽ
	outtextxy(430, 490, s);
}

void outguanshifu()
{
	TCHAR s[100];
	setbkmode(TRANSPARENT);
	if(huihe==0)
		_stprintf(s, _T("�Ƿ񷢶���ʯ����Ч(�����������ǿ�ƿ�Ѫ)"));
	else _stprintf(s, _T("�Է�������ʯ����Ч(�����������ǿ�ƿ�Ѫ)"));
	settextcolor(WHITE);  // ����������ɫΪ��ɫ
	settextstyle(20, 0, _T("����"));//  �趨���ִ�С����ʽ
	outtextxy(410, 490, s);
}

void outround()//�����ǰ�غ�Ϊ�ķ��غ�
{
	TCHAR s[20];
	setbkmode(TRANSPARENT);
	if(huihe==0)
		_stprintf(s, _T("��Ļغ�"));
	else _stprintf(s, _T("�Է��غ�"));
	settextcolor(WHITE);  // ����������ɫΪ��ɫ
	settextstyle(40, 0, _T("����"));//  �趨���ִ�С����ʽ
	outtextxy(1050, 350, s); // ����˻�������
}

void outpaiduinum()
{
	TCHAR s1[20],s2[20];
	setbkmode(TRANSPARENT);
	_stprintf(s1, _T("%d"),huihenum);
	_stprintf(s2, _T("%d"),73-usenum);
	settextcolor(WHITE);  // ����������ɫΪ��ɫ
	settextstyle(20, 0, _T("����"));//  �趨���ִ�С����ʽ
	outtextxy(1187, 39, s1); // ����˻�������
	outtextxy(1215, 62, s2); // ����˻�������
}

int n1;
void discard()//����
{
	BeginBatchDraw();//��ʼ��������
	if(huihe==0)
	{
		if(playershoupai>playerlife)
		{
			int k1 = playershoupai-playerlife;
			outPlayerDiscardWriting(k1);
			FlushBatchDraw();//��������һ��
			int i;
			while(1)
			{
				m1 = GetMouseMsg();//��ȡ�����Ϣ
				if(m1.uMsg==WM_LBUTTONDOWN)//���������
				{
					if(ischoose==1&&m1.x>=400&&m1.x<=524&&m1.y>=img_top&&m1.y<=img_top+39)//���ȷ��
						paistate = 0;
					if(paistate==1&&!(m1.x>=600&&m1.x<=724&&m1.y>=img_top&&m1.y<=img_top+43))
						n1 = (m1.x - 195)/x1;//������λ�����
					if(ischoose==0&&m1.x>=195+x1*n1&&m1.x<=311+x1*n1&&m1.y>=590&&m1.y<=753)//����������ѡ��
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
									putimage(pail[i].x, img_y, &paidui[playerpai[i]].im);//δ����Ʋ���
								else 
									putimage(pail[i].x, pail[0].y, &paidui[playerpai[i]].im);//��������ƶ�
							}
						}
						outPlayerDiscardWriting(k1);
						FlushBatchDraw();//��������һ��
						ischoose = 1;
					}
					else if((ischoose==1&&m1.x>=195+x1*n1&&m1.x<=311+x1*n1&&m1.y>=560&&m1.y<=723)||
						(ischoose==1&&ischoose==1&&m1.x>=600&&m1.x<=724&&m1.y>=525&&m1.y<=568))//�ٴε���ƻ��ȡ�������½�
 					{
						clearpai();
						outPlayerDiscardWriting(k1);
						FlushBatchDraw();//��������һ��
						ischoose = 0;
					}
					else if(ischoose==1&&m1.x>=400&&m1.x<=524&&m1.y>=img_top&&m1.y<=img_top+39)//�Ʊ����
					{
						cleardevice();
						k1--;
						placeequipment();
						if(k1>0)
							outPlayerDiscardWriting(k1);
						putimage(pail[6].x, pail[1].y, &paidui[playerpai[n1]].im);//����������
						playerpai[n1]=-1;//������ʧ
						playershoupai--;//�����������һ
						putimage(400, img_top, &im_right0);
						putimage(600, img_top, &im_cance0);
						adjustpai(playerpai);
						placeshoupai();
						FlushBatchDraw();//��������һ��;
						Sleep(1500);
						clearpai();
						if(k1>0)
							outPlayerDiscardWriting(k1);
						FlushBatchDraw();//��������һ��
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
		huihe=1;//npc�غ�
		cleardevice();
		placeequipment();
		placeshoupai();
		nextHuihe(npcpai);
	}
	else//npc����
	{
		if(npcshoupai>npclife)
		{
			int k2=npcshoupai-npclife;
			while(k2>0)
			{
				int p=rand()%npcshoupai;
				putimage(pail[6].x, pail[1].y, &paidui[npcpai[p]].im);//����������
				outNpcDiscardWritng();
				npcshoupai--;
				npcpai[p]=-1;
				adjustpai(npcpai);
				FlushBatchDraw();//��������һ��
				Sleep(1500);
				clearpai();
				k2--;
				if(k2>0)//�������һ������������ֻ���
					outNpcDiscardWritng();
				FlushBatchDraw();//��������һ��
				Sleep(500);
			}
		}
	}
	EndBatchDraw();//������������
}

void npcchupai(int i)
{
	putimage(pail[6].x, pail[1].y, &paidui[npcpai[i]].im);//����������
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
				putimage(pail[i].x, img_y, &paidui[playerpai[i]].im);//δ����Ʋ���
			else 
				putimage(pail[i].x, pail[0].y, &paidui[playerpai[i]].im);//��������ƶ�
		}
	}
	outchusha();
	FlushBatchDraw();
	while(1)
	{
		m2 = GetMouseMsg();//��ȡ�����Ϣ
		if(m2.uMsg==WM_LBUTTONDOWN)//���������
		{
			if(m2.x>=400&&m2.x<=524&&m2.y>=img_top&&m2.y<=img_top+39)//���ȷ��
			{
				cleardevice();
				placeequipment();
				putimage(pail[6].x, pail[1].y, &paidui[playerpai[j]].im);//����������
				judgemusic(playerpai[j]);//������Ч
				playerpai[j]=-1;//������ʧ
				playershoupai--;//�����������һ
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
			else if(m2.x>=600&&m2.x<=724&&m2.y>=img_top&&m2.y<=img_top+43)//���ȡ��
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
				putimage(pail[i].x, img_y, &paidui[playerpai[i]].im);//δ����Ʋ���
			else 
				putimage(pail[i].x, pail[0].y, &paidui[playerpai[i]].im);//��������ƶ�
		}
	}
	outchushan();
	FlushBatchDraw();
	while(1)
	{
		m2 = GetMouseMsg();//��ȡ�����Ϣ
		if(m2.uMsg==WM_LBUTTONDOWN)//���������
		{
			if(m2.x>=400&&m2.x<=524&&m2.y>=img_top&&m2.y<=img_top+39)//���ȷ��
			{
				cleardevice();
				placeequipment();
				putimage(pail[6].x, pail[1].y, &paidui[playerpai[j]].im);//����������
				judgemusic(playerpai[j]);//������Ч
				playerpai[j]=-1;//������ʧ
				playershoupai--;//�����������һ
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
			else if(m2.x>=600&&m2.x<=724&&m2.y>=img_top&&m2.y<=img_top+43&&wanjian==0)//���ȡ��
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

void npcshow()//npc����
{
	int i,j, k=0;
	chupainum = 0;//δ����
	BeginBatchDraw();
	if(npcshan==0)
		Sleep(1500);
	else Sleep(500);
	clearpai();
	FlushBatchDraw();
	if(npcshan==0)
	{
		while(chupainum==0)//δ����
		{
			shanghai = 1;
			for(i=0;i<6;i++)
				if(npclife<4)
					if(npcpai[i]>=35&&npcpai[i]<43)//��
					{
						npclife++;
						npcchupai(i);
						Sleep(1000);
					}
			for(i = 0;i<6;i++)
				if(npcpai[i]>=45&&npcpai[i]<49)//�Ƿ���˳��ǣ��
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
				if(npcpai[i]>=49&&npcpai[i]<53)//�Ƿ��й��Ӳ���
				{
					npcchupai(i);
					wuxie();
					if(wuxienum==0)
					{
						Sleep(500);
						putimage(pail[6].x, pail[1].y, &paidui[playerpai[0]].im);//����������
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
				if(npcpai[i]>=53&&npcpai[i]<56)//�Ƿ��о���
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
				if(npcpai[i]>=69&&npcpai[i]<71)//�Ƿ�����������
				{
					npcchupai(i);
					nanman();
					Sleep(1000);
				}
			for(i = 0;i<6;i++)
				if(npcpai[i]>=43&&npcpai[i]<45)//�ж��Ƿ��а�����
				{
					npcchupai(i);
					Sleep(1000);
					break;
				}
			for(i = 0;i<6;i++)
				if(npcpai[i]>=64&&npcpai[i]<66)//�Ƿ���������
				{
					npcchupai(i);
					Sleep(1000);
					break;
				}
			for(i = 0;i<6;i++)
				if(npcpai[i]==66)//�Ƿ������빭
				{
					npcchupai(i);
					Sleep(1000);
					break;
				}
			for(i = 0;i<6;i++)
				if(npcpai[i]==67)//�Ƿ������G��
				{
					npcchupai(i);
					Sleep(1000);
					break;
				}
			for(i = 0;i<6;i++)
				if(npcpai[i]==68)//�Ƿ��й�ʯ��
				{
					npcchupai(i);
					Sleep(1000);
					break;
				}
			for(i = 0;i<6;i++)
				if(npcpai[i]>=60&&npcpai[i]<64)//�Ƿ��о�
				{
					jiunum++;
					npcchupai(i);
					Sleep(1000);
					break;
				}
			for(i = 0;i<6;i++)
			{
				if((npcpai[i]>=0&&npcpai[i]<20)||(npcpai[i]>=71&&npcpai[i]<73))//�ж��Ƿ���ɱ������뷢
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
						if(playerpai[j]>=20&&playerpai[j]<35)//�������
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
			if(npcpai[i]>=20&&npcpai[i]<35&&wuxienum==0)//�Ƿ����������
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

void playershow(int xi)//ͼƬ����
{
	int i, k = playerpai[xi];
	cleardevice();//��������
	BeginBatchDraw();//��ʼ��������
	placeequipment();
	if(ischoose==0&&shannum==0)//ѡ���Ʋ�Ϊ��
	{
		//���ú�ɫȷ��ȡ��
		putimage(400, img_top, &im_right1);
		putimage(600, img_top, &im_cancel);
	}
	else if(ischoose==0&&shannum==1)//ѡ����Ϊ��
	{
		//���û�ɫȷ������ɫȡ��
		putimage(400, img_top, &im_right0);
		putimage(600, img_top, &im_cancel);
	}
	else//�ٴε��ѡ����
	{
		//���û�ɫȷ��ȡ��
		putimage(400, img_top, &im_right0);
		putimage(600, img_top, &im_cance0);
	}
	if(ischoose == 0&&paistate == 1)//�������y��������
		img_h-=vy;
	else if(ischoose == 1&&paistate == 1)//�������y�������
		img_h+=vy;
	if(paistate==1)//����ѡ�е��ƣ��������
	{
		for(i = 0;i<6;i++)
		{
			if(playerpai[i]!=-1)
			{
				if(i!=xi)
					putimage(pail[i].x, img_y, &paidui[playerpai[i]].im);//δ����Ʋ���
				else 
					putimage(pail[i].x, img_h, &paidui[playerpai[i]].im);//��������ƶ�
			}
		}
		FlushBatchDraw();//��������һ��
	}
	else
	{
		putimage(pail[6].x, pail[1].y, &paidui[playerpai[xi]].im);//����������
		judgemusic(playerpai[xi]);//������Ч
		judgeequipment(playerpai[xi]);//�жϴ�����Ƿ�Ϊװ����
		playerpai[xi]=-1;//������ʧ
		playershoupai--;//�����������һ
		adjustpai(playerpai);
		placeshoupai();
		FlushBatchDraw();//��������һ��
		Sleep(1500);
		clearpai();//����������
		FlushBatchDraw();//��������һ��
		playerpaieffect(k);
		EndBatchDraw();//������������
	}
	Sleep(3);
}

int n = 0;
void nextHuihe(int card2[])//���������������
{
	int i, j;
	for(i=0;i<6;i++)
	{
		if(card2[i]==-1)
		{
			if(huihe==0)//�������������
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
			else//��npc������
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
				if(ischoose==1)//�������ʱ�������Ʊ�ѡ�����ƻ�ԭ��λ��
				{
					while(img_h<590)
						playershow(n);
				}
				break;
			}
		}
	}
}

int playerfenxi()//�������Ϣ���з����������Ƶ��ƶ�
{
	if(m.x>=775&&m.x<=873&&m.y>=img_top&&m.y<=img_top+44)//�������
	{
		end = 1;
		return 0;
	}
	if(ischoose==1&&m.x>=400&&m.x<=524&&m.y>=img_top&&m.y<=img_top+39)//���ȷ��
		paistate = 0;
	if(paistate==1&&!(m.x>=600&&m.x<=724&&m.y>=img_top&&m.y<=img_top+43))//�������
		n = (m.x - 195)/x1;//����������λ�����
	if((playerpai[n]>=20&&playerpai[n]<35)//�����Ϊ��
		||(playerpai[n]>=56&&playerpai[n]<60)//�����Ϊ��и�ɻ�
		||(playerpai[n]>=35&&playerpai[n]<43&&playerlife==4))//��Ѫʱ�����
		shannum++;
	if(paistate==0&&shannum==1)//�������ѡ���ҵ��ȷ��
		paistate = 1;
	if(ischoose==0&&m.x>=195+x1*n&&m.x<=311+x1*n&&m.y>=590&&m.y<=753)//����������ѡ��
	{
		while(img_h>=560)
			playershow(n);
		if(shannum==1)
			shannum--;
		return 1;//����1
	}
	if((ischoose==1&&m.x>=195+x1*n&&m.x<=311+x1*n&&m.y>=560&&m.y<=723)||
		(ischoose==1&&m.x>=600&&m.x<=724&&m.y>=img_top&&m.y<=img_top+43))//�ٴε���ƻ��ȡ�������½�
	{
		while(img_h<590)
			playershow(n);
		if(shannum==1)
			shannum--;
		return 0;//����0
	}
	if(ischoose==1&&m.x>=400&&m.x<=524&&m.y>=img_top&&m.y<=img_top+39&&shannum==0)//�Ʊ����
	{
		img_h = 590;
		playershow(n);
		paistate = 1;
		if(shannum==1)
			shannum--;
		return 0;//����0
	}
	if(shannum==1)
		shannum--;
	return 0;//����0
}

void update()//���������
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
						m = GetMouseMsg();//��ȡ�����Ϣ
						if(huihe==0)//��һغ�
							if(m.uMsg==WM_LBUTTONDOWN)//���������
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
	srand(time(0));//�������
	startuppicture();
	startupdenglu();
	loading();
	startup();
	update();
	_getch();
}