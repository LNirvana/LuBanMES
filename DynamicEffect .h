/*��ͷ�ļ��������ǹ��ڶ�̬��һЩ�������溯����ʹ�ã�ͬʱ����һЩ���õĿ��ʹ��*/

/*ͬʱ�ڱ�ͷ�ļ���Ҳ������һЩ���õľ�̬��ܽṹ��                            */
#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>


typedef struct { double x, y; } Vec;

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
//��Ч����7���˳�MESϵͳ���ؽ�����
void LoadRoot(int x, int y, int type);
//��Ч����8���ַ���ת������Ч
void charRotation();
//��Ч����9���߿���ʾ����
void frameShow();

//³��MES�������ǻۿ���
void smartFactoryShow();

//��Ч����9�����ƽ�����˳��ĵ�����ת��Ч
void calc(double i, double j, double rot, Vec* v);
void earthEffect();

