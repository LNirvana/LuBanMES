#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>


//˳��������ṹ�壬�������
typedef struct {
	int* list;
	int size;
	int length;
}IntSeqList;

typedef  struct  time   //��ʾ����
{
	int year;			//��
	int month;			//��
	int day;			//��
} Date;

//�õ���ǰ�Ĺ���ʱ��
void getTimeNow(char d[]);

//�����ʼ������
void intListInit(IntSeqList* s, int size);

//���һ����������̬˳�����
int addInt(IntSeqList* s, int data);

//ͨ�ý��湦�ܺ���1--�˳�MESϵͳ
void  exitMES();

//ͨ�õı������ģ�壬���κεط�������ʹ��,x��y�ֱ��ʾ��ʾ�������꣬errorΪ������Ϣ
void errorTemplate(int x, char error[40]);

//ͨ�ú���6��ͨ�õ�ROOT�û�����ģ�壬x��y�ֱ��ʾ��ʾ�������꣬welcomΪ���صĻ�ӭ��Ϣ
void rootWelcome(int x, char welcome[40], char tip[40], int type);

//ͨ�ú���7:������еĳ�ʼ������
void initAll();