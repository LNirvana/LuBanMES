#pragma once
#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>
#include <math.h>
#include"DynamicEffect .h"
#define LEN 50

/*����̬Ч����ʾ����*/
#define PI 3.1415926
#define SX 8
#define SY 16
#define DX PI / SX
#define DY PI * 2 / SY
#define X(a, b) (cx + v[a][b].x * r), (cy + v[a][b].y * r)

//��Ч����1�����ع��
void HideCursor();
//��Ч����2����갴����x,yֵ�ƶ�
void Gotoxy(int x, int y);
//��Ч����3�����ƽ�����ר�ñ߿�
void DrawBox(int x, int y);
//��Ч����4�����ؽ������ɹ�����
void LoadInSuccess(int x, int y);
//��Ч����5�����ؽ�����ʧ�ܺ���
void LoadInFail(int x, int y);
//��Ч����6���˳�MESϵͳ���ؽ�����
void LoadExitMES(int x, int y);
//��Ч����7���ַ���ת������Ч
void charRotation();
//��Ч����8���߿���ʾ����
void frameShow();
//��Ч����9�����ƽ�����˳��ĵ�����ת��Ч
void calc(double i, double j, double rot, Vec* v);
void earthEffect();


//���ع��
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };//��ߵ�0�����겻�ɼ�
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//����ƶ�
void Gotoxy(int x, int y)
{
	HANDLE hout; //����������hout
	COORD coord; //����ṹ��coord
	coord.X = x;
	coord.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);//��ñ�׼�������Ļ�����
	SetConsoleCursorPosition(hout, coord);//�ƶ����
}

//���߿�
void DrawBox(int x, int y)
{
	Gotoxy(x, y);
	printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
	putchar('\n');
	Gotoxy(x, y + 1);
	printf("�U                                                  �U");
	putchar('\n');
	Gotoxy(x, y + 2);
	printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
}

//��½�ɹ�������
void LoadInSuccess(int x, int y)
{
	int len;
	HideCursor();

	DrawBox(x, y);
	for (len = x; len <= LEN * 2 / 2 + x - 2; len++) {
		Gotoxy(len + 1, y + 1);
		printf("��");
		Gotoxy(x + 20, y + 4);
		printf("���ڼ���%d%%", 2 * len - 62);
		Sleep(500);
	}
	//printf("  ");
	//Gotoxy(x + 54, y + 1);
	//charRotation();
	Gotoxy(x + 10, y + 4);
	printf("���سɹ�����ӭ����³��MESϵͳ");
}

//��½ʧ�ܽ�����
void LoadInFail(int x, int y)
{
	int len;
	HideCursor();
	DrawBox(x, y);
	for (len = x; len <= (LEN * 2 / 2 + x - 2) / 2; len++) {
		Gotoxy(len + 1, y + 1);
		printf("��");
		Gotoxy(x + 20, y + 4);
		printf("���ڼ���%d%%", 2 * len - 62);
		Sleep(500);
	}
	Sleep(5000);
	Gotoxy(x + 10, y + 4);
	printf("����ʧ�ܣ��������������������   ");
	Sleep(5);
	//Gotoxy(x + 40, y + 4);
	charRotation();

}

//�����˳�����
void LoadExitMES(int x, int y)
{
	int len;
	HideCursor();

	DrawBox(x, y);
	for (len = x; len <= LEN * 2 / 2 + x - 2; len++) {
		Gotoxy(len + 1, y + 1);
		printf("��");
		Gotoxy(x + 14, y + 4);
		printf("�����˳�³��MESϵͳ  ");
		printf("%d%%", 2 * len - 62);
		Sleep(500);
	}
	//printf("  ");
	//Gotoxy(x + 54, y + 1);
	//charRotation();
	Gotoxy(x + 10, y + 4);
	printf("���سɹ�����ӭ����³��MESϵͳ");
}

//���س����û�ROOT���涯��
void LoadRoot(int x, int y,int type) {
	int len;
	HideCursor();
	DrawBox(x, y);
	for (len = x; len <= LEN * 2 / 2 + x - 2; len++) {
		Gotoxy(len + 1, y + 1);
		printf("��");
		Gotoxy(x + 13, y + 4);
		//1.ִ �� �� �� �� �� Ա Ȩ �� 
		if (type==1) printf("���ڼ��زִ�Root����ģ��%d%%", 2 * len - 62);
		//2.ִ �� �� Ʒ �� �� ʦ Ȩ ��
		else if (type == 2)printf("���ڼ��ز�ƷRoot���ģ��%d%%", 2 * len - 62);
		//3.ִ �� �����������ʦ Ȩ ��
		else if (type == 3)printf("���ڼ��ع���Root����ģ��%d%%", 2 * len - 62);
		//4.ִ �� ���߼ල����ʦ Ȩ ��
		else if (type == 4)printf("���ڼ��ز���Root�ලģ��%d%%", 2 * len - 62);
		//5.ִ �� �� Ʒ �� �� Ա Ȩ ��
		else printf("���ڼ��ز�ƷRoot����ģ��%d%%", 2 * len - 62);
		Sleep(500);
	}
	//printf("  ");
	//Gotoxy(x + 54, y + 1);
	//charRotation();
	Gotoxy(x + 8, y + 4);
	printf("���سɹ�����ӭ����³��Root-MESϵͳ");
}

//��̬���ط��ź����������ڲ�����time�����޸ļ���ʱ��
void charRotation()
{

	char a[] = { '-','\\','|','/' };          //������Ҫע����Ƿ�б���ַ�����Ҫ����һ����б���ַ�����Ҫ�������'\\'������'\'
	int i = 0;								  //��������i�����±�
	int time = 4;								  //ʱ������ʦ
	while (time--)                            //��while������������ʱ��ѭ��ִ��while���
	{
		for (i = 0; i < 4; ++i)
		{
			printf("%c", a[i]);				  //����ַ�����a[]�еĵ�i���ַ����ַ����鹲���ĸ��ַ���a[0]~a[3]�ĸ���
			Sleep(100);                       //����ַ�a[i]֮��ͣ��100ms��ע�������ڵ����ֵ�λΪ���룩
			printf("\b");                     //���"\b"Ϊ�˸����˼�����Ƽ�����Backspace�����ã�
		}

	}
}

//������
void frameShow() {
	printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��                                                                                                                    ��\n");
	printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
}

//ר�����ڸ���ˢ�º�Ľ�����
void checkFrameShow() {
	frameShow();
	Gotoxy(35, 10);
	printf("������������������������������������������������������������������������������������������������");
	Gotoxy(35, 11);
	printf("��                                              ��");
	Gotoxy(35, 12);
	printf("��                                              ��");
	Gotoxy(35, 13);
	printf("��                                              ��");
	Gotoxy(35, 14);
	printf("��                                              ��");
	Gotoxy(35, 15);
	printf("��                                              ��");
	Gotoxy(35, 16);
	printf("��                                              ��");
	Gotoxy(35, 17);
	printf("��                                              ��");
	Gotoxy(35, 18);
	printf("��                                              ��");
	Gotoxy(35, 19);
	printf("��                                              ��");
	Gotoxy(35, 20);
	printf("��                                              ��");
	Gotoxy(35, 21);
	printf("������������������������������������������������������������������������������������������������");
	Sleep(100);
}

void smartFactoryShow() {
	system("cls");
	frameShow();
	Gotoxy(57 + 11, 0);
	printf("��");
	for (int i = 0; i < 29; i++) {
		Gotoxy(57+11, 1+i);
		printf("��");
	}
	Gotoxy(57 + 11, 30);
	printf("��");
	Gotoxy(23, 4);
	printf("³�� MES ���ǻ۹�������");
	for (int i = 0; i < 4; i++) {
		Gotoxy(9,7+i*3);
		printf("����������������������������������������������������");
		Gotoxy(9+23, 7 + i * 3+1);
		printf("���� %d",i+1);
	}
	//���ƻ��� 1
	for (int i = 0; i < 5;i++) {
		Gotoxy(13,21+i);
		printf("����������");
	}
	Gotoxy(14+1, 26);
	printf("���� 1");
	//���ƻ��� 2
	for (int i = 0; i < 5; i++) {
		Gotoxy(13+5+13 , 21 + i);
		printf("����������");
	}
	Gotoxy(14+5+14, 26);
	printf("���� 2");
	//���ƻ��� 3
	for (int i = 0; i < 5; i++) {
		Gotoxy(13+5+13+5+13 , 21 + i);
		printf("����������");
	}
	Gotoxy(14+5+14+5+13, 26);
	printf("���� 3");
}

//��������ʱ�ĵ���Ч��
void calc(double i, double j, double rot, Vec* v) {
	double x = sin(i) * cos(j), y = sin(i) * sin(j), z = cos(i),
		s = sin(rot), c = cos(rot), c1 = 1 - c, u = 1 / sqrt(3.0f), u2 = u * u;
	v->x = x * (c + u2 * c1) + y * (u2 * c1 - u * s) + z * (u2 * c1 + u * s);
	v->y = x * (u2 * c1 + u * s) + y * (c + u2 * c1) + z * (u2 * c1 - u * s);
}
void earthEffect() {
	HWND hwnd = GetConsoleWindow(); HDC hdc1 = GetDC(hwnd);
	double rot = 0;
	int time = 500;
	while (time--) {
		RECT rect; GetClientRect(hwnd, &rect); int w = rect.right, h = rect.bottom, cx = w / 2, cy = h / 2, r = h * 0.375;
		HDC hdc2 = CreateCompatibleDC(hdc1); HBITMAP bmp = CreateCompatibleBitmap(hdc1, w, h); SelectObject(hdc2, bmp);
		SelectObject(hdc2, GetStockObject(WHITE_PEN));
		Vec v[SX + 1][SY + 1];
		for (int i = 0; i <= SX; ++i) for (int j = 0; j <= SY; ++j) calc(i * DX, j * DY, rot, &v[i][j]);
		for (int i = 0; i < SX; ++i) for (int j = 0; j < SY; ++j) {
			MoveToEx(hdc2, X(i, j), NULL); LineTo(hdc2, X(i + 1, j));
			MoveToEx(hdc2, X(i, j), NULL); LineTo(hdc2, X(i, j + 1));
		}
		BitBlt(hdc1, 0, 0, w, h, hdc2, 0, 0, SRCCOPY); DeleteObject(bmp); DeleteDC(hdc2);
		rot += 0.01; Sleep(5);
	}
	Sleep(20);
}
