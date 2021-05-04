#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>
#include <string.h>
#include "Globals.h"
#include"DynamicEffect .h"
#include"MES-Leader.h"
#include"MES-WarehouseKeeper.h"
#include"MES-PLSupervisionEngineer.h"
#include"MES-ProductSalesman.h"
#include"MES-ProcessDesigner.h"
#define _CRT_SECURE_NO_DEPRECATE��
#define _CRT_SECURE_NO_WARNINGS��
#pragma warning(disable:4996)��


MComsSeqList allMComslist;   //����̬˳���洢����ԭ�Ϲ�Ӧ��ҵ��Ϣ
PComsSeqList allPComslist;   //����̬˳���洢���в�Ʒ�ɹ���ҵ��Ϣ
MWaresSeqList allMWareslist; //����̬˳���洢���вִ�ԭ�Ϲ�����Ϣ
PSalesSeqList allPSaleslist; //����̬˳���洢���вɹ�����������Ϣ
DProcessSeqList  allDProcesslist;//����̬˳���洢���еĹ���������Ϣ

//ͨ�ú���1���õ���ǰ������
void getTimeNow(char d[]);
//ͨ�ú���2����ʼ����̬˳���sizeΪ��ʼ������
void intListInit(IntSeqList* s, int size);
//ͨ�ú���3�����һ����������̬˳�����
int addInt(IntSeqList* s, int data);
//ͨ�ú���4��ͨ�õ��˳���ǰ�������ĺ���,��ͬ������ͨ������type����
void exitMES(int type);
//ͨ�ú���5��ͨ�õı������ģ�壬���κεط�������ʹ��,x��y�ֱ��ʾ��ʾ�������꣬errorΪ������Ϣ
void errorTemplate(int x, char error[40]);

//ͨ�ú���6��ͨ�õ�ROOT�û�����ģ�壬x��y�ֱ��ʾ��ʾ�������꣬welcomΪ���صĻ�ӭ��Ϣ
void rootWelcome(int x, char welcome[40], char tip[40], int type);

//ͨ�ú���1���õ���ǰ������
void getTimeNow(char d[]) {
	time_t tnow;
	time(&tnow);
	struct tm* sttm;
	sttm = localtime(&tnow);
	sprintf(d, "%d-%d-%d", sttm->tm_year + 1900, sttm->tm_mon + 1, sttm->tm_mday);
}

//ͨ�ú���2����ʼ����̬˳���sizeΪ��ʼ������
void intListInit(IntSeqList* s, int size) {
	s->list = (int*)malloc(size * sizeof(int));
	s->length = 0;
	s->size = size;
}

//ͨ�ú���3�����һ����������̬˳�����
int addInt(IntSeqList* s, int data) {
	if (s->length >= s->size) {
		int* t = s->list;
		s->list = (int*)malloc(2 * s->size * sizeof(int));
		if (s->list == NULL)
			return -1;
		s->size = 2 * s->size;
		for (int i = 0; i < s->length; i++)
			s->list[i] = t[i];
		free(t);
	}
	s->list[s->length] = data;
	s->length++;
	return 0;
}

//ͨ�ú���4��ͨ�õ��˳���ǰ�������ĺ���,��ͬ������ͨ������type����
void exitMES(int type) {
	int check;
	system("cls");		//1.	
	checkFrameShow();
	Gotoxy(35 + 13, 13);
	printf("��ȷ��Ҫ�˳�MESϵͳ��");
	Gotoxy(35 + 13, 14);
	printf("ȷ������ 1,�������� 0��");
	Gotoxy(35 + 13+ 11, 17);
	scanf("%d", &check);
	Gotoxy(35 + 13 + 11+3, 17);
	charRotation();
	if (check == 1) {
		system("cls");
		LoadExitMES(33, 15);
		system("cls");
		earthEffect();
		exit(0);
	}
	//�����˳�0��1����������
	else if (check!=0&&check!=1) {
		system("cls");
		exitMES(type);
	}
	else {
		//��Ϊ���صĽ�����岻һ�£�������Ҫ����ͬ���趨
		//0�Ƿ���root�������
		if (type == 0) {
			system("cls");
			Sleep(100);
			system("cls");
			rootLeaderInterface();
		}
		//1�Ƿ�����ҵ�����߽������
		else if (type == 1) {
			system("cls");
			Sleep(100);
			system("cls");
			adminLeaderInterface();
		}
		//2�Ƿ��زִ������߽������
		else if (type == 2) {
			system("cls");
			Sleep(100);
			system("cls");
			wareInterface();
		}
		//3�Ƿ��ع����������ʦ
		else if (type == 3) {
			system("cls");
			Sleep(100);
			system("cls");
			DProcessInterface();
			return 0;
		}
		//4�Ƿ��������ල����ʦ
		else if (type == 4) {	
			system("cls");
			Sleep(100);
			system("cls");
			SuperPLInterface();
			return 0;
		}
		//5�Ƿ��ز�Ʒ����Ա
		else{
			system("cls");
			Sleep(100);
			system("cls");
			proSalesInterface();
			return 0;
		}
	}
	while (1);
	//earthEffect();

}

//ͨ�ú���5��ͨ�õı������ģ�壬���κεط�������ʹ��,x��y�ֱ��ʾ��ʾ�������꣬errorΪ������Ϣ
void errorTemplate(int x,char error[40]) {
	//error���������12����
	system("cls");	
	checkFrameShow();
	Gotoxy(x ,14);
	printf("%s",error);
	Gotoxy(117/2,16);
	charRotation();
	Sleep(2000);
	system("cls");
}

//ͨ�ú���6��ͨ�õ�ROOT�û�����ģ�壬x��y�ֱ��ʾ��ʾ�������꣬welcomΪ���صĻ�ӭ��Ϣ
void rootWelcome(int x, char welcome[40],char tip[40],int type) {
	system("cls");
	checkFrameShow();
	Gotoxy(x, 14);
	printf("%s", welcome);
	Gotoxy(41, 14+2);
	printf("%s", tip);
	LoadRoot(33, 20, type);
	Sleep(3000);
}

//ͨ�ú���7:������еĳ�ʼ������
void initAll() {
	//��һ������ʼ��ԭ�Ϲ�Ӧ��ҵ����
	MComsSeqListInit(&allMComslist, 100);
	//�ڶ����������ݿ��ж�ȡ���ݵ�ԭ�Ϲ�Ӧ��ҵ����
	allMComsInfoReadFromFile(&allMComslist, "�����Ĺ�Ӧ��ҵ��Ϣ���ݿ�.txt");
	//����������ʼ����Ʒ�ɹ���ҵ����
	PComsSeqListInit(&allPComslist, 100);
	//���Ĳ��������ݿ��ж�ȡ���ݵ���Ʒ�ɹ���ҵ����
	allPComsInfoReadFromFile(&allPComslist, "�����Ĳɹ���ҵ��Ϣ���ݿ�.txt");
	//���岽����ʼ���ִ�ԭ�Ϲ�������
	MWaresSeqListInit(&allMWareslist, 100);
	//�������������ݿ��ж�ȡ���ݵ��ִ�ԭ�Ϲ�������
	allMWaresInfoReadFromFile(&allMWareslist, "�ִ�������Ϣ���ݿ�.txt");
	//���߲�����ʼ���������̹�������
	DProcessSeqListInit(&allDProcesslist, 100);
	//�ڰ˲��������ݿ��ж�ȡ���ݵ��������̹�������
	allDProcessInfoReadFromFile(&allDProcesslist, "������������ģ����Ϣ��Ϣ���ݿ�.txt");
	//�ھŲ�����ɹ������ߵĳ�ʼ��״̬
	ProductionLineInit();
	//��ʮ������ɹ��������ĳ�ʼ��״̬
	ProductionLineInit();
	//�ھŲ�����ʼ���ɹ�������������
	PSalesSeqListInit(&allPSaleslist, 100);
	//��ʮ���������ݿ��ж�ȡ���ݵ��ɹ�������������
	allPSalesInfoReadFromFile(&allPSaleslist, "�ɹ�������Ϣ���ݿ�.txt");
}