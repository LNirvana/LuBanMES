#include<stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<process.h>
#include<string.h>
#include"MES-PLSupervisionEngineer.h"
#include"Globals.h"

#define _CRT_SECURE_NO_DEPRECATE��
#define _CRT_SECURE_NO_WARNINGS��
#pragma warning(disable:4996)��

struct ProductionLine P1 = { 1 ,"���� 1","�ȴ���","��",0 };
struct ProductionLine P2 = { 2 ,"���� 2","�ȴ���","��",0 };
struct ProductionLine P3 = { 3 ,"���� 3","�ȴ���","��",0 };
struct ProductionLine P4 = { 4 ,"���� 4","�ȴ���","��",0 };

struct ProductionTool T1 = { 1 ,"���� 1","�ȴ���","��",0 };
struct ProductionTool T2 = { 2 ,"���� 2","�ȴ���","��",0 };
struct ProductionTool T3 = { 3 ,"���� 3","�ȴ���","��",0 };

//1.�ǻ۹������߳�ʼ������
void ProductionLineInit();

//2.�ǻ۹���������ʼ������
void ProductionToolInit();

//�������
void SuperPLInterface();

//1.�������߹�������
void arrangePLine(int type);

//2.�������߹����鿴
void checkPLine(int type);

//3.�������߹���ȡ��
void cancelPLine(int type);

//4.�������߼���ά��
void fixPLine(int type);

//5.����������������
void arrangePTool(int type);

//6.�������������鿴
void checkPTool(int type);

//7.������������ȡ��
void cancelPTool(int type);

//8.������������ά��
void fixPTool(int type);

//9.����ӿں���--����Ա�������߹����鿴
void checkPLineAdmin();

//10.����ӿں���--����Ա�������������鿴
void checkPToolAdmin();


//1.�ǻ۹������߳�ʼ������
void ProductionLineInit() {
	struct ProductionLine P1 = { 1 ,"���� 1","�ȴ���","��",0 };
	struct ProductionLine P2 = { 2 ,"���� 2","�ȴ���","��",0 };
	struct ProductionLine P3 = { 3 ,"���� 3","�ȴ���","��",0 };
	struct ProductionLine P4 = { 4 ,"���� 4","�ȴ���","��",0 };
}

//2.�ǻ۹���������ʼ������
void ProductionToolInit() {
	struct ProductionTool T1 = { 1 ,"���� 1","�ȴ���","��",0 };
	struct ProductionTool T2 = { 2 ,"���� 2","�ȴ���","��",0 };
	struct ProductionTool T3 = { 3 ,"���� 3","�ȴ���","��",0 };
}

//�������
void SuperPLInterface() {
	int choice;
	smartFactoryShow();
	Gotoxy(68+13+2, 4);
	printf("���߼ල����ʦ�������");
	Gotoxy(68 + 13, 7);
	printf("1.�� �� �� �� �� �� �� ��");
	Gotoxy(68 + 13, 9);
	printf("2.�� �� �� �� �� �� �� ��");
	Gotoxy(68 + 13, 11);
	printf("3.�� �� �� �� �� �� ȡ ��");
	Gotoxy(68 + 13, 13);
	printf("4.�� �� �� �� �� �� ά ��");
	Gotoxy(68 + 13, 15);
	printf("5.�� �� �� �� �� �� �� ��");
	Gotoxy(68 + 13, 17);
	printf("6.�� �� �� �� �� �� �� ��");
	Gotoxy(68 + 13, 19);
	printf("7.�� �� �� �� �� �� ȡ ��");
	Gotoxy(68 + 13, 21);
	printf("8.�� �� �� �� �� �� ά ��");
	Gotoxy(68 + 13, 23);
	printf("9.�� �� ³��  ��MES �� ��");
	Gotoxy(68 + 13, 25);
	printf("����������Ҫ�����ı��룺");
	scanf("%d", &choice);
	Gotoxy(68 + 13 + 26, 25);
	charRotation();
	switch (choice) {
		//1.�� �� �� �� �� �� �� ��
		case 1: {
			int type;
			int  PLineID;
			smartFactoryShow();
			Gotoxy(68 + 13 - 5 + 7, 7);
			printf("�ǻ�ϵͳ���߹�������");
			Gotoxy(68+13 - 5,10);
			printf("��������Ҫ���Ź����Ĳ��ߣ�    ");
			scanf("%d", &PLineID);
			Gotoxy(68 + 13 +29+4, 10);
			charRotation();
			arrangePLine(PLineID);
		}
		//2.�� �� �� �� �� �� �� ��
		case 2: {
			int type;
			int  PLineID;
			smartFactoryShow();
			Gotoxy(68 + 13 - 5 + 7, 7);
			printf("�ǻ�ϵͳ���߹����鿴");
			Gotoxy(68 + 13 - 5, 10);
			printf("��������Ҫ�鿴�����Ĳ��ߣ�     ");
			scanf("%d", &PLineID);
			Gotoxy(68 + 13 + 29 + 4, 10);
			charRotation();
			checkPLine(PLineID);
		}
		//3.�� �� �� �� �� �� ȡ ��
		case 3: {
			int type;
			int  PLineID;
			smartFactoryShow();
			Gotoxy(68 + 13 - 5 + 7, 7);
			printf("�ǻ�ϵͳ���߹���ȡ��");
			Gotoxy(68 + 13 - 5, 10);
			printf("��������Ҫȡ�������Ĳ��ߣ�    ");
			scanf("%d", &PLineID);
			Gotoxy(68 + 13 + 29 + 4, 10);
			charRotation();
			cancelPLine(PLineID);
		}
		//4.�� �� �� �� �� �� ά ��
		case 4: {
			int type;
			int  PLineID;
			smartFactoryShow();
			Gotoxy(68 + 13 - 5 + 7, 7);
			printf("�ǻ�ϵͳ���߼���ά��");
			Gotoxy(68 + 13 - 5, 10);
			printf("��������Ҫά�������Ĳ��ߣ�    ");
			scanf("%d", &PLineID);
			Gotoxy(68 + 13 + 29 + 4, 10);
			charRotation();
			fixPLine(PLineID);
		}
		//5.�� �� �� �� �� �� �� ��
		case 5: {
			int type;
			int  PToolID;
			smartFactoryShow();
			Gotoxy(68 + 13 - 5 + 7, 7);
			printf("�ǻ�ϵͳ������������");
			Gotoxy(68 + 13 - 5, 10);
			printf("��������Ҫ���Ź����Ļ�����    ");
			scanf("%d", &PToolID);
			Gotoxy(68 + 13 + 29 + 4, 10);
			charRotation();
			arrangePTool(PToolID);
		}
		//6.�� �� �� �� �� �� �� ��
		case 6: {
			int type;
			int  PToolID;
			smartFactoryShow();
			Gotoxy(68 + 13 - 5 + 7, 7);
			printf("�ǻ�ϵͳ���������鿴");
			Gotoxy(68 + 13 - 5, 10);
			printf("��������Ҫ�鿴�����Ļ�����     ");
			scanf("%d", &PToolID);
			Gotoxy(68 + 13 + 29 + 4, 10);
			charRotation();
			checkPTool(PToolID);
		}
		//7.�� �� �� �� �� �� ȡ ��
		case 7: {
			int type;
			int  PToolID;
			smartFactoryShow();
			Gotoxy(68 + 13 - 5 + 7, 7);
			printf("�ǻ�ϵͳ��������ȡ��");
			Gotoxy(68 + 13 - 5, 10);
			printf("��������Ҫȡ�������Ļ�����    ");
			scanf("%d", &PToolID);
			Gotoxy(68 + 13 + 29 + 4, 10);
			charRotation();
			cancelPTool(PToolID);
		}
		//8.�� �� �� �� �� �� ά ��
		case 8: {
			int type;
			int  PToolID;
			smartFactoryShow();
			Gotoxy(68 + 13 - 5 + 7, 7);
			printf("�ǻ�ϵͳ��������ά��");
			Gotoxy(68 + 13 - 5, 10);
			printf("��������Ҫά�������Ļ�����    ");
			scanf("%d", &PToolID);
			Gotoxy(68 + 13 + 29 + 4, 10);
			charRotation();
			fixPTool(PToolID);
		}
		//9.�� �� ³�� ��MES �� ��
		case 9: {
			errorTemplate(47, "�����˳�³����MES�ǻ���壡");
			exitMES(4);
		}
		//����������������
		default: {
			errorTemplate(47.5, "�������������������룡");
			SuperPLInterface();
		}	
	}
}

//1.�������߹�������
void arrangePLine(int type) {
	//����1��������
	if (type == 1) {
		if (strcmp(P1.Line_condition, "��ά��") == 0) {
			errorTemplate(47, "���� 1��ά���У�����ʧ�ܣ�");
			SuperPLInterface();
		}
		else if (strcmp(P1.Line_condition, "������") == 0) {
			errorTemplate(47, "���� 1���ڹ���������ʧ�ܣ�");
			SuperPLInterface();
		}
		else {
			int newTime = 0;
			char newProduct[30];
			memset(P1.Line_Product, 0, sizeof(P1.Line_Product));	//����������ٸ�ֵ
			Gotoxy(68 + 13 - 5, 12);
			printf("����������Ҫ�ӹ��Ĳ�Ʒ�� ");
			scanf("%s", newProduct);
			strcpy(P1.Line_Product, newProduct);		//��������������¿�����ȥ
			Gotoxy(68 + 13 + 29 + 4, 12);
			charRotation();
			Gotoxy(68 + 13 - 5, 14);
			printf("����������߼ӹ��Ĺ�ʱ��      ");
			scanf("%d", &newTime);
			P1.Line_Worktime = newTime;		//��������������¿�����ȥ
			Gotoxy(68 + 13 + 29 + 4, 14);
			charRotation();
			memset(P1.Line_condition, 0, sizeof(P1.Line_condition));	//����������ٸ�ֵ
			strcpy(P1.Line_condition, "������");
			errorTemplate(47.5, "�ǻ�ϵͳ��ʼ���Ų��߹�����");
			SuperPLInterface();
		}
	}
	//����2��������
	else if (type == 2) {
		if (strcmp(P2.Line_condition, "��ά��") == 0) {
			errorTemplate(47, "���� 2��ά���У�����ʧ�ܣ�");
			SuperPLInterface();
		}
		else if (strcmp(P2.Line_condition, "������") == 0) {
			errorTemplate(47, "���� 2���ڹ���������ʧ�ܣ�");
			SuperPLInterface();
		}
		else {
			int newTime = 0;
			char newProduct[30];
			memset(P2.Line_Product, 0, sizeof(P2.Line_Product));	//����������ٸ�ֵ
			Gotoxy(68 + 13 - 5, 12);
			printf("����������Ҫ�ӹ��Ĳ�Ʒ�� ");
			scanf("%s", newProduct);
			strcpy(P2.Line_Product, newProduct);		//��������������¿�����ȥ
			Gotoxy(68 + 13 + 29 + 4, 12);
			charRotation();
			Gotoxy(68 + 13 - 5, 14);
			printf("����������߼ӹ��Ĺ�ʱ��      ");
			scanf("%d", &newTime);
			P1.Line_Worktime = newTime;		//��������������¿�����ȥ
			Gotoxy(68 + 13 + 29 + 4, 14);
			charRotation();
			memset(P2.Line_condition, 0, sizeof(P2.Line_condition));	//����������ٸ�ֵ
			strcpy(P2.Line_condition, "������");
			errorTemplate(47.5, "�ǻ�ϵͳ��ʼ���Ų��߹�����");
			SuperPLInterface();
		}
	}
	//����3��������
	else if (type==3) {
		if (strcmp(P3.Line_condition, "��ά��") == 0) {
			errorTemplate(47, "���� 3��ά���У�����ʧ�ܣ�");
			SuperPLInterface();
		}
		else if (strcmp(P3.Line_condition, "������") == 0) {
			errorTemplate(47, "���� 3���ڹ���������ʧ�ܣ�");
			SuperPLInterface();
		}
		else {
			int newTime = 0;
			char newProduct[30];
			memset(P3.Line_Product, 0, sizeof(P3.Line_Product));	//����������ٸ�ֵ
			Gotoxy(68 + 13 - 5, 12);
			printf("����������Ҫ�ӹ��Ĳ�Ʒ�� ");
			scanf("%s", newProduct);
			strcpy(P3.Line_Product, newProduct);		//��������������¿�����ȥ
			Gotoxy(68 + 13 + 29 + 4, 12);
			charRotation();
			Gotoxy(68 + 13 - 5, 14);
			printf("����������߼ӹ��Ĺ�ʱ��      ");
			scanf("%d", &newTime);
			P1.Line_Worktime = newTime;		//��������������¿�����ȥ
			Gotoxy(68 + 13 + 29 + 4, 14);
			charRotation();
			memset(P3.Line_condition, 0, sizeof(P3.Line_condition));	//����������ٸ�ֵ
			strcpy(P3.Line_condition, "������");
			errorTemplate(47.5, "�ǻ�ϵͳ��ʼ���Ų��߹�����");
			SuperPLInterface();
		}
		
	}
	//����4��������
	else if (type == 4) {
		if(strcmp(P4.Line_condition, "��ά��") == 0) {
			errorTemplate(47, "���� 4��ά���У�����ʧ�ܣ�");
			SuperPLInterface();
		}
		else if (strcmp(P4.Line_condition, "������") == 0) {
			errorTemplate(47, "���� 4���ڹ���������ʧ�ܣ�");
			SuperPLInterface();
		}
		else {
			int newTime = 0;
			char newProduct[30];
			memset(P4.Line_Product, 0, sizeof(P4.Line_Product));	//����������ٸ�ֵ
			Gotoxy(68 + 13 - 5, 12);
			printf("����������Ҫ�ӹ��Ĳ�Ʒ�� ");
			scanf("%s", newProduct);
			strcpy(P4.Line_Product, newProduct);		//��������������¿�����ȥ
			Gotoxy(68 + 13 + 29 + 4, 12);
			charRotation();
			Gotoxy(68 + 13 - 5, 14);
			printf("����������߼ӹ��Ĺ�ʱ��      ");
			scanf("%d", &newTime);
			P1.Line_Worktime = newTime;		//��������������¿�����ȥ
			Gotoxy(68 + 13 + 29 + 4, 14);
			charRotation();
			memset(P4.Line_condition, 0, sizeof(P4.Line_condition));	//����������ٸ�ֵ
			strcpy(P4.Line_condition, "������");
			errorTemplate(47.5, "�ǻ�ϵͳ��ʼ���Ų��߹�����");
			SuperPLInterface();
		}
	}
	//������Ĳ��߱���������ʱ��
	else{
		errorTemplate(48.5, "�ǻ�ϵͳ�����޴˲��ߣ�");
		SuperPLInterface();
	}
}

//2.�������߹����鿴
void checkPLine(int type) {
	//�鿴����1����״��
	if (type == 1) {
		Gotoxy(68 + 13 - 5, 12);
		printf("����1 ���ڼӹ��Ĳ�Ʒ��   ");
		if (strcmp(P1.Line_Product, "��")==0){
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", P1.Line_Product);
		}
		else  printf("%s", P1.Line_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("����1 �ӹ���Ʒ�Ĺ�ʱ��         ");
		printf("%d", P1.Line_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("����1 Ŀǰ�Ĺ���״̬��       ");
		printf("%s", P1.Line_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("�鿴�����������������壺     ");
		scanf("%s", yes);
		//��������ֵ�����,ִ����ͬ��Ч��
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32+2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
		//��������ֵ�����,ִ����ͬ��Ч��
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
	}
	//�鿴����2����״��
	else if (type == 2) {
		Gotoxy(68 + 13 - 5, 12);
		printf("����2 ���ڼӹ��Ĳ�Ʒ��   ");
		if (strcmp(P2.Line_Product, "��") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", P2.Line_Product);
		}
		else  printf("%s", P2.Line_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("����2 �ӹ���Ʒ�Ĺ�ʱ��         ");
		printf("%d", P2.Line_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("����2 Ŀǰ�Ĺ���״̬��       ");
		printf("%s", P2.Line_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("�鿴�����������������壺     ");
		scanf("%s", yes);
		//��������ֵ�����,ִ����ͬ��Ч��
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
		//��������ֵ�����,ִ����ͬ��Ч��
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
	}
	//�鿴����3����״��
	else if (type == 3) {
		Gotoxy(68 + 13 - 5, 12);
		printf("����3 ���ڼӹ��Ĳ�Ʒ��   ");
		if (strcmp(P3.Line_Product, "��") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", P3.Line_Product);
		}
		else  printf("%s", P3.Line_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("����3 �ӹ���Ʒ�Ĺ�ʱ��         ");
		printf("%d", P3.Line_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("����3 Ŀǰ�Ĺ���״̬��       ");
		printf("%s", P3.Line_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("�鿴�����������������壺     ");
		scanf("%s", yes);
		//��������ֵ�����,ִ����ͬ��Ч��
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
		//��������ֵ�����,ִ����ͬ��Ч��
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
	}
	//�鿴����4����״��
	else if (type = 4) {
		Gotoxy(68 + 13 - 5, 12);
		printf("����4 ���ڼӹ��Ĳ�Ʒ��   ");
		if (strcmp(P4.Line_Product, "��") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", P4.Line_Product);
		}
		else  printf("%s", P4.Line_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("����4 �ӹ���Ʒ�Ĺ�ʱ��         ");
		printf("%d", P4.Line_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("����4 Ŀǰ�Ĺ���״̬��       ");
		printf("%s", P4.Line_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("�鿴�����������������壺     ");
		scanf("%s", yes);
		//��������ֵ�����,ִ����ͬ��Ч��
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
		//��������ֵ�����,ִ����ͬ��Ч��
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
}
	//��������߱�Ŵ����ʱ��
	else {
		errorTemplate(48.5, "�ǻ�ϵͳ�����޴˲��ߣ�");
		SuperPLInterface();
	}
}

//3.�������߹���ȡ��
void cancelPLine(int type) {
	if (type == 1) {
		if (strcmp(P1.Line_condition, "��ά��") == 0) {
			errorTemplate(47, "���� 1��ά���У�ȡ��ʧ�ܣ�");
			SuperPLInterface();
		}
		else if (strcmp(P1.Line_condition, "�ȴ���") == 0) {
			errorTemplate(47.5, "���� 1�ȴ��У�ȡ��ʧ�ܣ�");
			SuperPLInterface();
		}
		else {
			int condition;
			//��Ϊȡ�����ߵĹ������ߺ����׽�����ά����״̬
			//�����������ֵ���Բ��ߵ�״̬��Ҫ����ģ�⣬���ﷶΧ��1~100��
			condition = rand() % 100 + 1;
			if (condition <= 100 && condition >= 40) strcpy(P1.Line_condition, "��ά��");
			else strcpy(P1.Line_condition, "�ȴ���");
			strcpy(P1.Line_Product, "��");
			P1.Line_Worktime = 0;
			errorTemplate(48, "�ǻ�ϵͳȡ�����߹����У�");
			if (strcmp(P1.Line_condition, "��ά��") == 0) {
				errorTemplate(48, "��ʾ�� ����1��ά���У���");
				SuperPLInterface();
			}
			SuperPLInterface();
		}
	}
	//ȡ������ 2�Ĺ���
	else if( type== 2) {
		if (strcmp(P2.Line_condition, "��ά��") == 0) {
			errorTemplate(47, "���� 2��ά���У�ȡ��ʧ�ܣ�");
			SuperPLInterface();
		}
		else if (strcmp(P2.Line_condition, "�ȴ���") == 0) {
			errorTemplate(47.5, "���� 2�ȴ��У�ȡ��ʧ�ܣ�");
			SuperPLInterface();
		}
		else {
			int condition;
			//��Ϊȡ�����ߵĹ������ߺ����׽�����ά����״̬
			//�����������ֵ���Բ��ߵ�״̬��Ҫ����ģ�⣬���ﷶΧ��1~100��
			condition = rand() % 100 + 1;
			if (condition <= 100 && condition >= 40) strcpy(P2.Line_condition, "��ά��");
			else strcpy(P2.Line_condition, "�ȴ���");
			strcpy(P2.Line_Product, "��");
			P2.Line_Worktime = 0;
			errorTemplate(48, "�ǻ�ϵͳȡ�����߹����У�");
			if (strcmp(P2.Line_condition, "��ά��") == 0) {
				errorTemplate(48, "��ʾ�� ����2��ά���У���");
				SuperPLInterface();
			}
			SuperPLInterface();
		}
	}
	//ȡ������ 3�Ĺ���
	else if (type == 3) {
		if (strcmp(P3.Line_condition, "��ά��") == 0) {
			errorTemplate(47, "���� 3��ά���У�ȡ��ʧ�ܣ�");
			SuperPLInterface();
		}
		else if (strcmp(P3.Line_condition, "�ȴ���") == 0) {
			errorTemplate(47.5, "���� 3�ȴ��У�ȡ��ʧ�ܣ�");
			SuperPLInterface();
		}
		else{
			int condition;
			//��Ϊȡ�����ߵĹ������ߺ����׽�����ά����״̬
			//�����������ֵ���Բ��ߵ�״̬��Ҫ����ģ�⣬���ﷶΧ��1~100��
			condition = rand() % 100 + 1;
			if (condition <= 100 && condition >= 40) strcpy(P3.Line_condition, "��ά��");
			else strcpy(P3.Line_condition, "�ȴ���");
			strcpy(P3.Line_Product, "��");
			P3.Line_Worktime = 0;
			errorTemplate(48, "�ǻ�ϵͳȡ�����߹����У�");
			if (strcmp(P3.Line_condition, "��ά��") == 0) {
				errorTemplate(48, "��ʾ�� ����3��ά���У���");
				SuperPLInterface();
			}
			SuperPLInterface();
		}
	}
	//ȡ������ 4�Ĺ���
	else if (type ==  4) {
		if (strcmp(P4.Line_condition, "��ά��") == 0) {
			errorTemplate(47, "���� 4��ά���У�ȡ��ʧ�ܣ�");
			SuperPLInterface();
		}
		else if (strcmp(P4.Line_condition, "�ȴ���") == 0) {
			errorTemplate(47.5, "���� 4�ȴ��У�ȡ��ʧ�ܣ�");
			SuperPLInterface();
		}
		else {
			int condition;
			//��Ϊȡ�����ߵĹ������ߺ����׽�����ά����״̬
			//�����������ֵ���Բ��ߵ�״̬��Ҫ����ģ�⣬���ﷶΧ��1~100��
			condition = rand() % 100 + 1;
			if (condition <= 100 && condition >= 40) strcpy(P4.Line_condition, "��ά��");
			else strcpy(P4.Line_condition, "�ȴ���");
			strcpy(P4.Line_Product, "��");
			P4.Line_Worktime = 0;
			errorTemplate(48, "�ǻ�ϵͳȡ�����߹����У�");
			if (strcmp(P4.Line_condition, "��ά��") == 0) {
				errorTemplate(48, "��ʾ�� ����4��ά���У���");
				SuperPLInterface();
			}
			SuperPLInterface();
		}
	}
	//������ı�Ŵ����ʱ��
	else {
		errorTemplate(48.5, "�ǻ�ϵͳ�����޴˲��ߣ�");
		SuperPLInterface();
	}
}

//4.�������߼���ά��
void fixPLine(int type) {
	//����1��Ҫ�ṩ����ά��
	if (type == 1) {
		//����1�����ڴ�ά��״̬ʱ
		if (strcmp(P1.Line_condition, "��ά��") == 0) {
			strcpy(P1.Line_condition, "�ȴ���");
			errorTemplate(49, "����ʦ����ά�������У�");
			errorTemplate(49, "   ���� 1ά���ɹ���   ");
			SuperPLInterface();
		}
		//�������
		else {
			errorTemplate(46, "�ǻ�ϵͳ��⵽��������ά����");
			SuperPLInterface();
		}
	}
	//����2��Ҫ�ṩ����ά��
	else if (type == 2) {
		if (strcmp(P2.Line_condition, "��ά��") == 0) {
			strcpy(P2.Line_condition, "�ȴ���");
			errorTemplate(49, "����ʦ����ά�������У�");
			errorTemplate(49, "   ���� 2ά���ɹ���   ");
			SuperPLInterface();
		}
		//�������
		else {
			errorTemplate(46, "�ǻ�ϵͳ��⵽��������ά����");
			SuperPLInterface();
		}
	}
	//����3��Ҫ�ṩ����ά��
	else if (type == 3) {
		if (strcmp(P3.Line_condition, "��ά��") == 0) {
			strcpy(P3.Line_condition, "�ȴ���");
			errorTemplate(49, "����ʦ����ά�������У�");
			errorTemplate(49, "   ���� 3ά���ɹ���   ");
			SuperPLInterface();
		}
		//�������
		else {
			errorTemplate(46, "�ǻ�ϵͳ��⵽��������ά����");
			SuperPLInterface();
		}
	}
	//����3��Ҫ�ṩ����ά��
	else if (type == 4) {
		if (strcmp(P4.Line_condition, "��ά��") == 0) {
			strcpy(P4.Line_condition, "�ȴ���");
			errorTemplate(49, "����ʦ����ά�������У�");
			errorTemplate(49, "   ���� 4ά���ɹ���   ");
			SuperPLInterface();
		}
		//�������
		else {
			errorTemplate(46, "�ǻ�ϵͳ��⵽��������ά����");
			SuperPLInterface();
		}
	}
	//������߱�Ŵ���ʱ
	else {
		errorTemplate(48.5, "�ǻ�ϵͳ�����޴˲��ߣ�");
		SuperPLInterface();
	}
}

//5.����������������
void arrangePTool(int type) {
	//���� 1��������
	if (type == 1) {
		if (strcmp(T1.Tool_condition, "��ά��") == 0) {
			errorTemplate(47, "���� 1��ά���У�����ʧ�ܣ�");
			SuperPLInterface();
		}
		else if (strcmp(T1.Tool_condition, "������") == 0) {
			errorTemplate(47, "���� 1���ڹ���������ʧ�ܣ�");
			SuperPLInterface();
		}
		else {
			int newTime = 0;
			char newProduct[30];
			memset(T1.Tool_Product, 0, sizeof(T1.Tool_Product));	//����������ٸ�ֵ
			Gotoxy(68 + 13 - 5, 12);
			printf("����������Ҫ�ӹ��Ĳ�Ʒ�� ");
			scanf("%s", newProduct);
			strcpy(T1.Tool_Product, newProduct);		//��������������¿�����ȥ
			Gotoxy(68 + 13 + 29 + 4, 12);
			charRotation();
			Gotoxy(68 + 13 - 5, 14);
			printf("������������ӹ��Ĺ�ʱ��      ");
			scanf("%d", &newTime);
			T1.Tool_Worktime = newTime;		//��������������¿�����ȥ
			Gotoxy(68 + 13 + 29 + 4, 14);
			charRotation();
			memset(T1.Tool_condition, 0, sizeof(T1.Tool_condition));	//����������ٸ�ֵ
			strcpy(T1.Tool_condition, "������");
			errorTemplate(47.5, "�ǻ�ϵͳ��ʼ���Ż���������");
			SuperPLInterface();
		}
	}
	//����2��������
	else if (type == 2) {
		if (strcmp(T2.Tool_condition, "��ά��") == 0) {
			errorTemplate(47, "���� 2��ά���У�����ʧ�ܣ�");
			SuperPLInterface();
		}
		else if (strcmp(T2.Tool_condition, "������") == 0) {
			errorTemplate(47, "���� 2���ڹ���������ʧ�ܣ�");
			SuperPLInterface();
		}
		else {
			int newTime = 0;
			char newProduct[30];
			memset(T2.Tool_Product, 0, sizeof(T2.Tool_Product));	//����������ٸ�ֵ
			Gotoxy(68 + 13 - 5, 12);
			printf("����������Ҫ�ӹ��Ĳ�Ʒ�� ");
			scanf("%s", newProduct);
			strcpy(T2.Tool_Product, newProduct);		//��������������¿�����ȥ
			Gotoxy(68 + 13 + 29 + 4, 12);
			charRotation();
			Gotoxy(68 + 13 - 5, 14);
			printf("������������ӹ��Ĺ�ʱ��      ");
			scanf("%d", &newTime);
			T2.Tool_Worktime = newTime;		//��������������¿�����ȥ
			Gotoxy(68 + 13 + 29 + 4, 14);
			charRotation();
			memset(T2.Tool_condition, 0, sizeof(T2.Tool_condition));	//����������ٸ�ֵ
			strcpy(T2.Tool_condition, "������");
			errorTemplate(47.5, "�ǻ�ϵͳ��ʼ���Ż���������");
			SuperPLInterface();
		}
	}
	//����3��������
	else if (type == 3) {
		if (strcmp(T3.Tool_condition, "��ά��") == 0) {
			errorTemplate(47, "���� 3��ά���У�����ʧ�ܣ�");
			SuperPLInterface();
		}
		else if (strcmp(T3.Tool_condition, "������") == 0) {
			errorTemplate(47, "���� 3���ڹ���������ʧ�ܣ�");
			SuperPLInterface();
		}
		else {
			int newTime = 0;
			char newProduct[30];
			memset(T3.Tool_Product, 0, sizeof(T3.Tool_Product));	//����������ٸ�ֵ
			Gotoxy(68 + 13 - 5, 12);
			printf("����������Ҫ�ӹ��Ĳ�Ʒ�� ");
			scanf("%s", newProduct);
			strcpy(T3.Tool_Product, newProduct);		//��������������¿�����ȥ
			Gotoxy(68 + 13 + 29 + 4, 12);
			charRotation();
			Gotoxy(68 + 13 - 5, 14);
			printf("������������ӹ��Ĺ�ʱ��      ");
			scanf("%d", &newTime);
			T3.Tool_Worktime = newTime;		//��������������¿�����ȥ
			Gotoxy(68 + 13 + 29 + 4, 14);
			charRotation();
			memset(T3.Tool_condition, 0, sizeof(T3.Tool_condition));	//����������ٸ�ֵ
			strcpy(T3.Tool_condition, "������");
			errorTemplate(47.5, "�ǻ�ϵͳ��ʼ���Ż���������");
			SuperPLInterface();
		}
	}
	//������Ĳ��߱���������ʱ��
	else {
		errorTemplate(48.5, "�ǻ�ϵͳ�����޴˻�����");
		SuperPLInterface();
	}
}

//6.�������������鿴
void checkPTool(int type) {
	//�鿴����1����״��
	if (type == 1) {
		Gotoxy(68 + 13 - 5, 12);
		printf("����1 ���ڼӹ��Ĳ�Ʒ��   ");
		if (strcmp(T1.Tool_Product, "��") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", T1.Tool_Product);
		}
		else  printf("%s", T1.Tool_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("����1 �ӹ���Ʒ�Ĺ�ʱ��         ");
		printf("%d", T1.Tool_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("����1 Ŀǰ�Ĺ���״̬��       ");
		printf("%s", T1.Tool_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("�鿴�����������������壺     ");
		scanf("%s", yes);
		//��������ֵ�����,ִ����ͬ��Ч��
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
		//��������ֵ�����,ִ����ͬ��Ч��
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
	}
	//�鿴���� 2����״��
	else if (type == 2) {
		Gotoxy(68 + 13 - 5, 12);
		printf("���� 2���ڼӹ��Ĳ�Ʒ��   ");
		if (strcmp(T2.Tool_Product, "��") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", T2.Tool_Product);
		}
		else  printf("%s", T2.Tool_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("���� 2�ӹ���Ʒ�Ĺ�ʱ��         ");
		printf("%d", T2.Tool_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("���� 2Ŀǰ�Ĺ���״̬��       ");
		printf("%s", T2.Tool_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("�鿴�����������������壺     ");
		scanf("%s", yes);
		//��������ֵ�����,ִ����ͬ��Ч��
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
		//��������ֵ�����,ִ����ͬ��Ч��
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
	}
	//�鿴���� 3����״��
	else if (type == 3) {
		Gotoxy(68 + 13 - 5, 12);
		printf("���� 3���ڼӹ��Ĳ�Ʒ��   ");
		if (strcmp(T3.Tool_Product, "��") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", T3.Tool_Product);
		}
		else  printf("%s", T3.Tool_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("���� 3�ӹ���Ʒ�Ĺ�ʱ��         ");
		printf("%d", T3.Tool_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("���� 3Ŀǰ�Ĺ���״̬��       ");
		printf("%s", T3.Tool_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("�鿴�����������������壺     ");
		scanf("%s", yes);
		//��������ֵ�����,ִ����ͬ��Ч��
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
		//��������ֵ�����,ִ����ͬ��Ч��
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			SuperPLInterface();
		}
	}

	//��������߱�Ŵ����ʱ��
	else {
		errorTemplate(48.5, "�ǻ�ϵͳ�����޴˻�����");
		SuperPLInterface();
	}
}

//7.������������ȡ��
void cancelPTool(int type) {
	if (type == 1) {
		if (strcmp(T1.Tool_condition, "��ά��") == 0) {
			errorTemplate(47, "���� 1��ά���У�ȡ��ʧ�ܣ�");
			SuperPLInterface();
		}
		else if (strcmp(T1.Tool_condition, "�ȴ���") == 0) {
			errorTemplate(47.5, "���� 1�ȴ��У�ȡ��ʧ�ܣ�");
			SuperPLInterface();
		}
		else {
			int condition;
			//��Ϊȡ�������Ĺ������������׽�����ά����״̬
			//�����������ֵ���Ի�����״̬��Ҫ����ģ�⣬���ﷶΧ��1~100��
			condition = rand() % 100 + 1;
			if (condition <= 100 && condition >= 40) strcpy(T1.Tool_condition, "��ά��");
			else strcpy(T1.Tool_condition, "�ȴ���");
			strcpy(T1.Tool_Product, "��");
			T1.Tool_Worktime = 0;
			errorTemplate(48, "�ǻ�ϵͳȡ�����������У�");
			if (strcmp(T1.Tool_condition, "��ά��") == 0) {
				errorTemplate(48, "��ʾ�� ����1��ά���У���");
				SuperPLInterface();
			}
			SuperPLInterface();
		}
	}
	//ȡ������ 2�Ĺ���
	else if (type == 2) {
		if (strcmp(T2.Tool_condition, "��ά��") == 0) {
			errorTemplate(47, "���� 2��ά���У�ȡ��ʧ�ܣ�");
			SuperPLInterface();
		}
		else if (strcmp(T2.Tool_condition, "�ȴ���") == 0) {
			errorTemplate(47.5, "���� 2�ȴ��У�ȡ��ʧ�ܣ�");
			SuperPLInterface();
		}
		else {
			int condition;
			//��Ϊȡ�������Ĺ������������׽�����ά����״̬
			//�����������ֵ���Ի�����״̬��Ҫ����ģ�⣬���ﷶΧ��1~100��
			condition = rand() % 100 + 1;
			if (condition <= 100 && condition >= 40) strcpy(T2.Tool_condition, "��ά��");
			else strcpy(T2.Tool_condition, "�ȴ���");
			strcpy(T2.Tool_Product, "��");
			T2.Tool_Worktime = 0;
			errorTemplate(48, "�ǻ�ϵͳȡ�����������У�");
			if (strcmp(T2.Tool_condition, "��ά��") == 0) {
				errorTemplate(48, "��ʾ�� ����2��ά���У���");
				SuperPLInterface();
			}
			SuperPLInterface();
		}
	}
	//ȡ������ 3�Ĺ���
	else if (type == 3) {
		if (strcmp(T3.Tool_condition, "��ά��") == 0) {
			errorTemplate(47, "���� 3��ά���У�ȡ��ʧ�ܣ�");
			SuperPLInterface();
		}
		else if (strcmp(T3.Tool_condition, "�ȴ���") == 0) {
			errorTemplate(47.5, "���� 3�ȴ��У�ȡ��ʧ�ܣ�");
			SuperPLInterface();
		}
		else {
			int condition;
			//��Ϊȡ�������Ĺ������������׽�����ά����״̬
		//�����������ֵ���Ի�����״̬��Ҫ����ģ�⣬���ﷶΧ��1~100��
			condition = rand() % 100 + 1;
			if (condition <= 100 && condition >= 40) strcpy(T3.Tool_condition, "��ά��");
			else strcpy(T3.Tool_condition, "�ȴ���");
			strcpy(T3.Tool_Product, "��");
			T3.Tool_Worktime = 0;
			errorTemplate(48, "�ǻ�ϵͳȡ�����������У�");
			if (strcmp(T3.Tool_condition, "��ά��") == 0) {
				errorTemplate(48, "��ʾ�� ����3��ά���У���");
				SuperPLInterface();
			}
			SuperPLInterface();
		}
	}
	//������ı�Ŵ����ʱ��
	else {
		errorTemplate(48.5, "�ǻ�ϵͳ�����޴˻�����");
		SuperPLInterface();
	}
}

//8.������������ά��
void fixPTool(int type) {
	//���� 1��Ҫ�ṩ����ά��
	if (type == 1) {
		//���� 1�����ڴ�ά��״̬ʱ
		if (strcmp(T1.Tool_condition, "��ά��") == 0) {
			strcpy(T1.Tool_condition, "�ȴ���");
			errorTemplate(49, "����ʦ����ά�������У�");
			errorTemplate(49, "   ���� 1ά���ɹ���   ");
			SuperPLInterface();
		}
		//�������
		else {
			errorTemplate(46, "�ǻ�ϵͳ��⵽��������ά����");
			SuperPLInterface();
		}
	}
	//���� 2��Ҫ�ṩ����ά��
	else if (type == 2) {
		if (strcmp(T2.Tool_condition, "��ά��") == 0) {
			strcpy(T2.Tool_condition, "�ȴ���");
			errorTemplate(49, "����ʦ����ά�������У�");
			errorTemplate(49, "   ���� 2ά���ɹ���   ");
			SuperPLInterface();
		}
		//�������
		else {
			errorTemplate(46, "�ǻ�ϵͳ��⵽��������ά����");
			SuperPLInterface();
		}
	}
	//����3��Ҫ�ṩ����ά��
	else if (type == 3) {
		if (strcmp(T3.Tool_condition, "��ά��") == 0) {
			strcpy(T3.Tool_condition, "�ȴ���");
			errorTemplate(49, "����ʦ����ά�������У�");
			errorTemplate(49, "   ���� 3ά���ɹ���   ");
			SuperPLInterface();
		}
		//�������
		else {
			errorTemplate(46, "�ǻ�ϵͳ��⵽��������ά����");
			SuperPLInterface();
		}
	}	
	//������߱�Ŵ���ʱ
	else {
		errorTemplate(48.5, "�ǻ�ϵͳ�����޴˻�����");
		SuperPLInterface();
	}
}

//9.����ӿں���--����Ա�������߹����鿴
void checkPLineAdmin(){
	int  PLineID;
	smartFactoryShow();
	Gotoxy(68 + 13 - 5 + 7, 7);
	printf("�ǻ�ϵͳ���߹����鿴");
	Gotoxy(68 + 13 - 5, 10);
	printf("��������Ҫ�鿴�����Ĳ��ߣ�     ");
	scanf("%d", &PLineID);
	Gotoxy(68 + 13 + 29 + 4, 10);
	charRotation();
	//�鿴����1����״��
	if (PLineID == 1) {
		Gotoxy(68 + 13 - 5, 12);
		printf("����1 ���ڼӹ��Ĳ�Ʒ��   ");
		if (strcmp(P1.Line_Product, "��") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", P1.Line_Product);
		}
		else  printf("%s", P1.Line_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("����1 �ӹ���Ʒ�Ĺ�ʱ��         ");
		printf("%d", P1.Line_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("����1 Ŀǰ�Ĺ���״̬��       ");
		printf("%s", P1.Line_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("�鿴�����������������壺     ");
		scanf("%s", yes);
		//��������ֵ�����,ִ����ͬ��Ч��
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
		//��������ֵ�����,ִ����ͬ��Ч��
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
	}
	//�鿴����2����״��
	else if (PLineID == 2) {
		Gotoxy(68 + 13 - 5, 12);
		printf("����2 ���ڼӹ��Ĳ�Ʒ��   ");
		if (strcmp(P2.Line_Product, "��") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", P2.Line_Product);
		}
		else  printf("%s", P2.Line_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("����2 �ӹ���Ʒ�Ĺ�ʱ��         ");
		printf("%d", P2.Line_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("����2 Ŀǰ�Ĺ���״̬��       ");
		printf("%s", P2.Line_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("�鿴�����������������壺     ");
		scanf("%s", yes);
		//��������ֵ�����,ִ����ͬ��Ч��
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
		//��������ֵ�����,ִ����ͬ��Ч��
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
	}
	//�鿴����3����״��
	else if (PLineID == 3) {
		Gotoxy(68 + 13 - 5, 12);
		printf("����3 ���ڼӹ��Ĳ�Ʒ��   ");
		if (strcmp(P3.Line_Product, "��") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", P3.Line_Product);
		}
		else  printf("%s", P3.Line_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("����3 �ӹ���Ʒ�Ĺ�ʱ��         ");
		printf("%d", P3.Line_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("����3 Ŀǰ�Ĺ���״̬��       ");
		printf("%s", P3.Line_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("�鿴�����������������壺     ");
		scanf("%s", yes);
		//��������ֵ�����,ִ����ͬ��Ч��
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
		//��������ֵ�����,ִ����ͬ��Ч��
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
	}
	//�鿴����4����״��
	else if (PLineID = 4) {
		Gotoxy(68 + 13 - 5, 12);
		printf("����4 ���ڼӹ��Ĳ�Ʒ��   ");
		if (strcmp(P4.Line_Product, "��") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", P4.Line_Product);
		}
		else  printf("%s", P4.Line_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("����4 �ӹ���Ʒ�Ĺ�ʱ��         ");
		printf("%d", P4.Line_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("����4 Ŀǰ�Ĺ���״̬��       ");
		printf("%s", P4.Line_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("�鿴�����������������壺     ");
		scanf("%s", yes);
		//��������ֵ�����,ִ����ͬ��Ч��
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
		//��������ֵ�����,ִ����ͬ��Ч��
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
	}
	//��������߱�Ŵ����ʱ��
	else {
		errorTemplate(48.5, "�ǻ�ϵͳ�����޴˲��ߣ�");
		adminLeaderInterface();
	}
}

//10.����ӿں���--����Ա�������������鿴
void checkPToolAdmin() {
	int  PToolID;
	smartFactoryShow();
	Gotoxy(68 + 13 - 5 + 7, 7);
	printf("�ǻ�ϵͳ���������鿴");
	Gotoxy(68 + 13 - 5, 10);
	printf("��������Ҫ�鿴�����Ļ�����     ");
	scanf("%d", &PToolID);
	Gotoxy(68 + 13 + 29 + 4, 10);
	charRotation();
	//�鿴����1����״��
	if (PToolID == 1) {
		Gotoxy(68 + 13 - 5, 12);
		printf("����1 ���ڼӹ��Ĳ�Ʒ��   ");
		if (strcmp(T1.Tool_Product, "��") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", T1.Tool_Product);
		}
		else  printf("%s", T1.Tool_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("����1 �ӹ���Ʒ�Ĺ�ʱ��         ");
		printf("%d", T1.Tool_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("����1 Ŀǰ�Ĺ���״̬��       ");
		printf("%s", T1.Tool_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("�鿴�����������������壺     ");
		scanf("%s", yes);
		//��������ֵ�����,ִ����ͬ��Ч��
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
		//��������ֵ�����,ִ����ͬ��Ч��
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
	}
	//�鿴���� 2����״��
	else if (PToolID == 2) {
		Gotoxy(68 + 13 - 5, 12);
		printf("���� 2���ڼӹ��Ĳ�Ʒ��   ");
		if (strcmp(T2.Tool_Product, "��") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", T2.Tool_Product);
		}
		else  printf("%s", T2.Tool_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("���� 2�ӹ���Ʒ�Ĺ�ʱ��         ");
		printf("%d", T2.Tool_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("���� 2Ŀǰ�Ĺ���״̬��       ");
		printf("%s", T2.Tool_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("�鿴�����������������壺     ");
		scanf("%s", yes);
		//��������ֵ�����,ִ����ͬ��Ч��
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
		//��������ֵ�����,ִ����ͬ��Ч��
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
	}
	//�鿴���� 3����״��
	else if (PToolID == 3) {
		Gotoxy(68 + 13 - 5, 12);
		printf("���� 3���ڼӹ��Ĳ�Ʒ��   ");
		if (strcmp(T3.Tool_Product, "��") == 0) {
			Gotoxy(68 + 13 - 5 + 26 + 5, 12);
			printf("%s", T3.Tool_Product);
		}
		else  printf("%s", T3.Tool_Product);
		Gotoxy(68 + 13 - 5, 14);
		printf("���� 3�ӹ���Ʒ�Ĺ�ʱ��         ");
		printf("%d", T3.Tool_Worktime);
		Gotoxy(68 + 13 - 5, 16);
		printf("���� 3Ŀǰ�Ĺ���״̬��       ");
		printf("%s", T3.Tool_condition);
		char yes[3];
		Gotoxy(68 + 13 - 5, 18);
		printf("�鿴�����������������壺     ");
		scanf("%s", yes);
		//��������ֵ�����,ִ����ͬ��Ч��
		if (yes[0] == 'y') {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
		//��������ֵ�����,ִ����ͬ��Ч��
		else {
			Gotoxy(68 + 13 - 5 + 32 + 2, 18);
			charRotation();
			Sleep(1000);
			adminLeaderInterface();
		}
	}
	//��������߱�Ŵ����ʱ��
	else {
		errorTemplate(48.5, "�ǻ�ϵͳ�����޴˻�����");
		adminLeaderInterface();
	}
}
