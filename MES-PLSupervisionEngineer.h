#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>

//��Ϊ�������ߺͻ�����Ϊ���ӣ�һ�㲻������ɾ�Ĳ飬��³��MES��
//��ֱ��ʹ�ýṹ��������Ϊԭʼ״̬��ʹ�ã��������������ߣ���̨����

typedef struct ProductionLine {		//�������߽ṹ
	int  Line_id;					//�������߱��
	char Line_name[20];				//������������
	char Line_condition[30];		//�������߹���״̬
	char Line_Product[30];			//�������߼ӹ���Ʒ����
	int  Line_Worktime;				//�������߼ӹ�ʱ��
};

typedef struct ProductionTool {		//���������ṹ
	int  Tool_id;					//�����������
	char Tool_name[20];				//������������
	char Tool_condition[30];		//������������״̬
	char Tool_Product[30];			//���������ӹ���Ʒ����
	int  Tool_Worktime;				//���������ӹ�ʱ��
};

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