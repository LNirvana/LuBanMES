#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>
#include "string.h"
#include"Globals.h"
#include"MES-Leader.h"      //�����쵼��
#include"DynamicEffect .h"  //���ض�̬Ч��
#include"MainInterface.h"	
#include"MES-WarehouseKeeper.h"
#include"MES-ProcessDesigner.h"
#include"MES-PLSupervisionEngineer.h"

#define _CRT_SECURE_NO_DEPRECATE��
#define _CRT_SECURE_NO_WARNINGS��
#pragma warning(disable:4996)��

int resultID = 1;			//ȫ�ֱ���resultID��Ϊ����ID���ķ���ֵ
char password[6] = "root";	//���������ʼ��ֵΪroot
char employeeID[4] = "00";	//���˱�ų�ʼ��ֵΪ00

//���溯��1����½���溯��
int interFacemainWrong();
//���ܺ���1��ר�����ڻ�ԭ�ֳ����������������
int interFacemainWrong();
//���ܺ���1�������Ϣ��֤����
int sys_loginID(char* employeeID);

//���溯��1����½���溯��
void interFacemain() {
	int x = 0;
	char c = '0';
	system("cls");
	frameShow();
	Gotoxy(48, 10);		//��̬�ƶ���꣬ͬʱ��ҳ�������꣨48��10����Ϊ��׼�ƶ�����Ĺ��
	printf("³��MES��������ִ��ϵͳ\n");
	Gotoxy(48 - 9, 12);		//��̬�ƶ����
	printf("Ա����ţ�");
	Gotoxy(45 + 14, 12);		//��̬�ƶ����
	for (int i = 0; i < 5; i++) {
		scanf("%c", &employeeID[i]);
		if (employeeID[i] == '\n') {
			break;
		}
	}
	resultID = sys_loginID(employeeID);	//���������֤ID
	Gotoxy(48 + 26, 12);
	charRotation();			
	Gotoxy(48 - 9, 14);					
	printf("Ա����λ��");
	/*---1.��ҵ�쵼����֤�ӿ�---*/
	if (resultID==0||resultID==1){
		Gotoxy(45 + 14, 14);			
		printf("��ҵ�쵼��");
		Gotoxy(48 + 26, 14);
		charRotation();					//������ִ����֤�����Ϣ
		Gotoxy(48 - 9, 16);				
		printf("Ա�����룺\n");
		Gotoxy(45 + 14, 16);		//��̬�ƶ����
		while (x < 4 && c != 13)   //13�ǻس�����ASCII��
		{
			c = getch();
			password[x++] = c;
			if (c != 13)
				putchar('*');
		}
		password[x] = '\0';
		Gotoxy(48 + 26, 16);
		charRotation();
		if (strcmp("root\0", password) == 0) {	//root�û�������
			Gotoxy(48 + 26, 16);
			charRotation();			//������ִ����֤�����Ϣ
			//*�����˷�ʱ����
			LoadInSuccess(48 - 15, 20);
			Sleep(1000);
			//*/
			system("cls");			//�����Ļ������һ����
			rootLeaderInterface();
		}
		else if (strcmp("0000\0", password) == 0) {	//������������
			Gotoxy(48 + 26, 16);
			charRotation();			//������ִ����֤�����Ϣ
			///*�����˷�ʱ����
			LoadInSuccess(48 - 15, 20);
			Sleep(1000);
			//*/
			system("cls");			//�����Ļ������һ����
			adminLeaderInterface();
		}
		else {
			Gotoxy(48 - 20, 18);
			LoadInFail(48 - 15, 20);
			system("cls");			//�����Ļ������һ����
			interFacemainWrong();
		}
	}
	/*---2.�ִ�����Ա��֤�ӿ�---*/
	else if (resultID == 2) {
		Gotoxy(45 + 14, 14);		//��̬�ƶ����
		printf("�ִ�����Ա");
		Gotoxy(48 + 26, 14);
		charRotation();			//������ִ����֤�����Ϣ
		Gotoxy(48 - 9, 16);		//��̬�ƶ����
		printf("Ա�����룺\n");
		Gotoxy(45 + 14, 16);		//��̬�ƶ����
	    while (x < 4 && c != 13)   //13�ǻس�����ASCII��
		{
			c = getch();
			password[x++] = c;
			if (c != 13)
				putchar('*');
		}
		password[x] = '\0';
		Gotoxy(48 + 26, 16);
		charRotation();
		if (strcmp("0001\0", password) == 0) {
			Gotoxy(48 + 26, 16);
			charRotation();			//������ִ����֤�����Ϣ
			/*�����˷�ʱ����
			LoadInSuccess(48 - 15, 20);
			Sleep(1000);
			//*/
			system("cls");			//�����Ļ������һ����
			wareInterface();
		}
		else {
			Gotoxy(48 - 20, 18);
			LoadInFail(48 - 15, 20);
			system("cls");			//�����Ļ������һ����
			interFacemainWrong();
		}
	}
	/*---3.�������ʦ��֤�ӿ�---*/
	else if (resultID == 3) {
		Gotoxy(45 + 14, 14);		//��̬�ƶ����
		printf("�����������ʦ");
		Gotoxy(48 + 26, 14);
		charRotation();			//������ִ����֤�����Ϣ
		Gotoxy(48 - 9, 16);		//��̬�ƶ����
		printf("Ա�����룺\n");
		Gotoxy(45 + 14, 16);		//��̬�ƶ����
		while (x < 4 && c != 13)   //13�ǻس�����ASCII��
		{
			c = getch();
			password[x++] = c;
			if (c != 13)
				putchar('*');
		}
		password[x] = '\0';
		Gotoxy(48 + 26, 16);
		charRotation();
		if (strcmp("0002\0", password) == 0) {
			Gotoxy(48 + 26, 16);
			charRotation();			//������ִ����֤�����Ϣ
			/*�����˷�ʱ����
			LoadInSuccess(48 - 15, 20);
			Sleep(1000);
			//*/
			system("cls");			//�����Ļ������һ����
			DProcessInterface();
		}
		else {
			Gotoxy(48 - 20, 18);
			LoadInFail(48 - 15, 20);
			system("cls");			//�����Ļ������һ����
			interFacemainWrong();
		}
	}
	/*---4.���߼ල����ʦ��֤�ӿ�---*/
	else if (resultID == 4) {
		Gotoxy(45 + 14, 14);		//��̬�ƶ����
		printf("���߼ල����ʦ");
		Gotoxy(48 + 26, 14);
		charRotation();			//������ִ����֤�����Ϣ
		Gotoxy(48 - 9, 16);		//��̬�ƶ����
		printf("Ա�����룺\n");
		Gotoxy(45 + 14, 16);		//��̬�ƶ����
		while (x < 4 && c != 13)   //13�ǻس�����ASCII��
		{
			c = getch();
			password[x++] = c;
			if (c != 13)
				putchar('*');
		}
		password[x] = '\0';
		Gotoxy(48 + 26, 16);
		charRotation();
	    if (strcmp("0003\0", password) == 0) {
			Gotoxy(48 + 26, 16);
			charRotation();			//������ִ����֤�����Ϣ
			/*�����˷�ʱ����
			LoadInSuccess(48 - 15, 20);
			Sleep(1000);
			//*/
			system("cls");			//�����Ļ������һ����
			SuperPLInterface();
		}
		else {
			Gotoxy(48 - 20, 18);
			LoadInFail(48 - 15, 20);
			system("cls");			//�����Ļ������һ����
			interFacemainWrong();
		}
	}
	/*---5.��Ʒ����Ա��֤�ӿ�---*/
	else if (resultID == 5) {
		Gotoxy(45 + 14, 14);		//��̬�ƶ����
		printf("��Ʒ����Ա");
		Gotoxy(48 + 26, 14);
		charRotation();			//������ִ����֤�����Ϣ
		Gotoxy(48 - 9, 16);		//��̬�ƶ����
		printf("Ա�����룺\n");
		Gotoxy(45 + 14, 16);		//��̬�ƶ����
		while (x < 4 && c != 13)   //13�ǻس�����ASCII��
		{
			c = getch();
			password[x++] = c;
			if (c != 13)
				putchar('*');
		}
		password[x] = '\0';
		Gotoxy(48 + 26, 16);
		charRotation();
		if (strcmp("0004\0", password) == 0) {
			Gotoxy(48 + 26, 16);
			charRotation();			//������ִ����֤�����Ϣ
			/*�����˷�ʱ����
			LoadInSuccess(48 - 15, 20);
			Sleep(1000);
			//*/
			system("cls");			//�����Ļ������һ����
			proSalesInterface();
		}
		//�����������������
		else {
			Gotoxy(48 - 20, 18);
			LoadInFail(48 - 15, 20);
			system("cls");			//�����Ļ������һ����
			interFacemainWrong();	//�����������
		}
	}
	/*---6.����ı�Ŵ���ӿ�---*/
	else{
		Gotoxy(45 + 14, 14);
		printf("�ޱ�Ŷ�Ӧ��λ");
		Gotoxy(48 + 26, 14);
		charRotation();
		Gotoxy(48 - 9-3, 19);
		printf("�������Ա�����������������������������  ");
		charRotation();
		memset(employeeID, 0, sizeof(employeeID));	//����������Ҫ���¶�employee���鸳��ֵ
		Sleep(3000);
		interFacemain();
	}
}

//���ܺ���1��ר�����ڻ�ԭ�ֳ����������������
int interFacemainWrong() {
	int x = 0;
	char c = '0';
	while (1) {
		frameShow();
		Gotoxy(48, 10);		//��̬�ƶ���꣬ͬʱ��ҳ�������꣨48��10����Ϊ��׼�ƶ�����Ĺ��
		printf("³��MES��������ִ��ϵͳ\n");
		Gotoxy(48 - 9, 12);		//��̬�ƶ����
		printf("Ա����ţ�");
		Gotoxy(45 + 14, 12);		//��̬�ƶ����
		printf("%s",employeeID);
		Gotoxy(48 + 26, 12);
		printf("/");			//������ִ����֤�����Ϣ
		Gotoxy(48 - 9, 14);		//��̬�ƶ����
		printf("Ա����λ��");
		Gotoxy(45 + 14, 14);		//��̬�ƶ����
		//1.��ԭ��ҵ����Ա�ĵ�½�ֳ�
		if (resultID == 0 || resultID == 1) {
			printf("��ҵ�쵼��");
			Gotoxy(48 + 26, 14);
			printf("/");
			Gotoxy(48 - 9, 16);		//��̬�ƶ����
			printf("Ա�����룺\n");
			Gotoxy(45 + 14, 16);		//��̬�ƶ����
			while (x < 4 && c != 13)   //13�ǻس�����ASCII��
			{
				c = getch();
				password[x++] = c;
				if (c != 13)
					putchar('*');
			}
			password[x] = '\0';
			Gotoxy(48 + 26, 16);
			charRotation();
			if (strcmp("root\0", password) == 0) {
				Gotoxy(48 + 26, 16);
				charRotation();			//������ִ����֤�����Ϣ
				///*�����˷�ʱ����
				LoadInSuccess(48 - 15, 20);
				Sleep(1000);
				//*/
				system("cls");			//�����Ļ������һ����
				rootLeaderInterface();
			}
			else if (strcmp("0000\0", password) == 0) {
				Gotoxy(48 + 26, 16);
				charRotation();			//������ִ����֤�����Ϣ
				///*�����˷�ʱ����
				LoadInSuccess(48 - 15, 20);
				Sleep(1000);
				//*/
				system("cls");			//�����Ļ������һ����
				adminLeaderInterface();
			}
			else {
				Gotoxy(48 - 20, 18);
				LoadInFail(48 - 15, 20);
				system("cls");			//�����Ļ������һ����
				interFacemainWrong();	//��������������������»ص�����ͷ
			}
		}
		//2.��ԭ�ִ�����Ա�ĵ�½�ֳ�
		else if (resultID == 2) {
			printf("�ִ�����Ա");
			Gotoxy(48 + 26, 14);
			printf("/");
			Gotoxy(48 - 9, 16);		//��̬�ƶ����
			printf("Ա�����룺\n");
			Gotoxy(45 + 14, 16);		//��̬�ƶ����
			while (x < 4 && c != 13)   //13�ǻس�����ASCII��
			{
				c = getch();
				password[x++] = c;
				if (c != 13)
					putchar('*');
			}
			password[x] = '\0';
			Gotoxy(48 + 26, 16);
			charRotation();
			if (strcmp("0001\0", password) == 0) {
				Gotoxy(48 + 26, 16);
				charRotation();			//������ִ����֤�����Ϣ
				/*�����˷�ʱ����
				LoadInSuccess(48 - 15, 20);
				Sleep(1000);
				//*/
				system("cls");			//�����Ļ������һ����
				wareInterface();
			}
			else {
				Gotoxy(48 - 20, 18);
				LoadInFail(48 - 15, 20);
				system("cls");			//�����Ļ������һ����
				interFacemainWrong();	//��������������������»ص�����ͷ
			}
		}
		//3.��ԭ�����������ʦ�ĵ�½�ֳ�
		else if (resultID == 3) {
			printf("�����������ʦ");
			Gotoxy(48 + 26, 14);
			printf("/");
			Gotoxy(48 - 9, 16);		//��̬�ƶ����
			printf("Ա�����룺\n");
			Gotoxy(45 + 14, 16);		//��̬�ƶ����
			while (x < 4 && c != 13)   //13�ǻس�����ASCII��
			{
				c = getch();
				password[x++] = c;
				if (c != 13)
					putchar('*');
			}
			password[x] = '\0';
			Gotoxy(48 + 26, 16);
			charRotation();
			if (strcmp("0002\0", password) == 0) {
				Gotoxy(48 + 26, 16);
				charRotation();			//������ִ����֤�����Ϣ
				/*�����˷�ʱ����
				LoadInSuccess(48 - 15, 20);
				Sleep(1000);
				//*/
				system("cls");			//�����Ļ������һ����
			    DProcessInterface();
			}
			else {
				Gotoxy(48 - 20, 18);
				LoadInFail(48 - 15, 20);
				system("cls");			//�����Ļ������һ����
				interFacemainWrong();	//��������������������»ص�����ͷ
			}
		}
		//5.��ԭ���߼ල����ʦ�ĵ�½�ֳ�
		else if (resultID == 4) {
			printf("���߼ල����ʦ");
			Gotoxy(48 + 26, 14);
			printf("/");
			Gotoxy(48 - 9, 16);		//��̬�ƶ����
			printf("Ա�����룺\n");
			Gotoxy(45 + 14, 16);		//��̬�ƶ����
			while (x < 4 && c != 13)   //13�ǻس�����ASCII��
			{
				c = getch();
				password[x++] = c;
				if (c != 13)
					putchar('*');
			}
			password[x] = '\0';
			Gotoxy(48 + 26, 16);
			charRotation();
			if (strcmp("0003\0", password) == 0) {
				Gotoxy(48 + 26, 16);
				charRotation();			//������ִ����֤�����Ϣ
				/*�����˷�ʱ����
				LoadInSuccess(48 - 15, 20);
				Sleep(1000);
				//*/
				system("cls");			//�����Ļ������һ����
				SuperPLInterface();
			}
			else {
				Gotoxy(48 - 20, 18);
				LoadInFail(48 - 15, 20);
				system("cls");			//�����Ļ������һ����
				interFacemainWrong();	//��������������������»ص�����ͷ
			}
		}
		//6��ԭ��Ʒ����Ա�ĵ�½�ֳ�
		else if (resultID == 5) {
			printf("��Ʒ����Ա");
			Gotoxy(48 + 26, 14);
			printf("/");
			Gotoxy(48 - 9, 16);		//��̬�ƶ����
			printf("Ա�����룺\n");
			Gotoxy(45 + 14, 16);		//��̬�ƶ����
			while (x < 4 && c != 13)   //13�ǻس�����ASCII��
			{
				c = getch();
				password[x++] = c;
				if (c != 13)
					putchar('*');
			}
			password[x] = '\0';
			Gotoxy(48 + 26, 16);
			charRotation();
			if (strcmp("0004\0", password) == 0) {
				Gotoxy(48 + 26, 16);
				charRotation();			//������ִ����֤�����Ϣ
				/*�����˷�ʱ����
				LoadInSuccess(48 - 15, 20);
				Sleep(1000);
				//*/
				system("cls");			//�����Ļ������һ����
				proSalesInterface();
			}
			else {
				Gotoxy(48 - 20, 18);
				LoadInFail(48 - 15, 20);
				system("cls");			//�����Ļ������һ����
				interFacemainWrong();	//��������������������»ص�����ͷ
			}
		}
	}
}

//���ܺ���1�������Ϣ��֤����
int sys_loginID(char* employeeID) {		//�û������֤
	//rootȨ�������֤
	if (strcmp( "root\n",employeeID)==0) {
		return 0;
	}
	//��ҵ����Ա�����֤
	if (strcmp("00\n", employeeID) == 0) {
		return 1;
	}
	//�ִ�����Ա�����֤
	else if (strcmp("01\n", employeeID) == 0 || strcmp(employeeID, "02\n") == 0 || strcmp("03\n", employeeID) == 0 || strcmp("04\n", employeeID) == 0 || strcmp("05\n", employeeID) == 0){
		return 2;
	}
	//�������������ʦ�����֤
	else if (strcmp("06\n",employeeID ) == 0 || strcmp(employeeID, "07\n") == 0 || strcmp("08\n",employeeID ) == 0 || strcmp("09\n", employeeID) == 0 || strcmp("10\n",employeeID) == 0) {
		return 3;
	}
	//���߼ල����ʦ�����֤	
	else if (strcmp("11\n", employeeID) == 0 || strcmp(employeeID, "12\n") == 0 || strcmp("13\n", employeeID) == 0 || strcmp("14\n", employeeID) == 0 || strcmp("15\n", employeeID) == 0) {
		return 4;
	}
	//��Ʒ����Ա�����֤
	else if (strcmp("16\n", employeeID) == 0 || strcmp(employeeID, "17\n") == 0 || strcmp("18\n", employeeID) == 0 || strcmp("19\n", employeeID) == 0 || strcmp("20\n", employeeID) == 0) {
		return 5;
	}
	else return 7;
}