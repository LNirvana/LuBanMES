#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>

#include"Globals.h"
#include"DynamicEffect .h"
#include"MES-Leader.h"
#include"MainInterface.h"
#include"MES-PLSupervisionEngineer.h"
#include"MES-ProductSalesman.h"

#define _CRT_SECURE_NO_DEPRECATE��
#define _CRT_SECURE_NO_WARNINGS��
#pragma warning(disable:4996)��

extern MComsSeqList allMComslist;
extern PComsSeqList allPComslist;
/*----------------------���ݽṹ�ӿڼ���----------------------*/
//���ݽṹ����1��MCom����-��ʼ������� mcsl��size��ʾ��ʼ������
void MComsSeqListInit(MComsSeqList* mcsl, int size);
//���ݽṹ����2��MCom����--���ݿ���Ϣ��ʼ��
int allMComsInfoReadFromFile(MComsSeqList* mcsl, char* filename);

//���ݽṹ����3��PCom����-��ʼ������� pcsl��size��ʾ��ʼ������
void PComsSeqListInit(PComsSeqList* pcsl, int size);

//���ݽṹ����4��PCom����--���ݿ���Ϣ��ʼ��
int allPComsInfoReadFromFile(PComsSeqList* pcsl, char* filename);

/*----------------------�û�����ӿڼ���----------------------*/
//����1��root�����û��ĵ�½����
void rootLeaderInterface();
//����2����ҵ�����ߵĵ�½����
void adminLeaderInterface();
//����3��ԭ�Ϲ�Ӧ��ҵ��Ϣ�������
void materialComInterface();
//����4����Ʒ�ɹ���ҵ��Ϣ�������
void productComInterface();

/*----------------------�������ӿڼ���----------------------*/
//���ܽ���1��ԭ�Ϲ�Ӧ��ҵ��ӽ���
void addMaterialCom();
//���ܽ���2�����ԭ�Ϲ�Ӧ��ҵ������ϵ����
void deleteMaterialCom();
//���ܽ���3���޸���ҵ��Ӧԭ�Ͻ���
void modifiMCom();
//���ܽ���4����ѯ��Ӧ��ҵ��Ϣ����
void queryMCom();
//���ܽ���5�����湩Ӧ��ҵ��Ϣ����
void saveMCom();
//���ܽ���6����Ʒ�ɹ���ҵǩ������
void addProductCom();
//���ܽ���7�������Ʒ�ɹ���ҵ������ϵ����
void deleteProductCom();
//���ܽ���8���޸���ҵ��Ӧԭ�Ͻ���
void modifiPCom();
//���ܽ���9����ѯ�ɹ���ҵ��Ϣ����
void queryPCom();
//���ܽ���10������ɹ���ҵ��Ϣ����
void savePCom();

/*----------------------���ܺ����ӿڼ���----------------------*/
//��Ϲ��ܽ���1�����ܺ���--����ԭ���Ϲ�Ӧ��ҵ
int addNewMCom(MComsSeqList* mcsl, MComInfo newMCom);
//��Ϲ��ܽ���1�����ܺ���--����ԭ���Ϲ�Ӧ��ҵ
int addNewPCom(PComsSeqList* pcsl, PComInfo newPCom);
//��Ϲ��ܽ���123�����ܺ���--��ԭ�Ϲ�Ӧ��ҵ���и���ǩԼ��ҵ��Ž��в��ң�û�д���ҵ�򷵻�-1������з���ֵ���Ǹ�ԭ�Ϲ�Ӧ��ҵ�ı�ţ������㷨�ö��ֲ��ҷ���
int searchMCom(MComsSeqList mcsl, char* MCsn);
//��Ϲ��ܽ���123�����ܺ���--�ڲ�Ʒ�ɹ���ҵ���и���ǩԼ��ҵ��Ž��в��ң�û�д���ҵ�򷵻�-1������з���ֵ���Ǹò�Ʒ�ɹ���ҵ�ı�ţ������㷨�ò�ֵ���ҷ���
int searchMComByInterpolationSearch(MComsSeqList mcsl, char* MCsn);
//��Ϲ��ܽ���123�����ܺ���--�ڲ�Ʒ�ɹ���ҵ���и���ǩԼ��ҵ��Ž��в��ң�û�д���ҵ�򷵻�-1������з���ֵ���Ǹò�Ʒ�ɹ���ҵ�ı�ţ������㷨�ö��ֲ��ҷ���
int searchPCom(PComsSeqList pcsl, char* PCsn);
//��Ϲ��ܽ���123�����ܺ���--�ڲ�Ʒ�ɹ���ҵ���и���ǩԼ��ҵ��Ž��в��ң�û�д���ҵ�򷵻�-1������з���ֵ���Ǹò�Ʒ�ɹ���ҵ�ı�ţ������㷨�ò�ֵ���ҷ���
int searchPComByInterpolationSearch(PComsSeqList pcsl, char* PCsn);
//��Ϲ��ܽ���123�����ܺ���--��ȿ�������ԭ�Ϲ�Ӧ��ҵ
void MComCopy(MComInfo* to, MComInfo from);
//��Ϲ��ܽ���123�����ܺ���--��ȿ���������Ʒ�ɹ���ҵ
void PComCopy(PComInfo* to, PComInfo from);
//��Ϲ��ܽ���2�����ܺ���--��ԭ�Ϲ�Ӧ��ҵ����ɾ����index��Ԫ�أ�ɾ���㷨Ϊ�Ѻ��������Ԫ�ظ���ǰ�棬����0��ʾɾ���ɹ�
int delMCom(MComsSeqList* mcsl, int index);
//��Ϲ��ܽ���2�����ܺ���--��ԭ�Ϲ�Ӧ��ҵ����ɾ����index��Ԫ�أ�ɾ���㷨Ϊ�Ѻ��������Ԫ�ظ���ǰ�棬����0��ʾɾ���ɹ�
int delPCom(PComsSeqList* pcsl, int index);
//��Ϲ��ܽ���3�����ܺ�������ԭ�Ϲ�Ӧ��ҵ��mcsl���޸ĵ�index����ҵ����Ϣ��type��ʾҪ�޸ĵ����ͣ�ȡֵ1����ҵ��ţ���2����ҵ���ƣ���3����ҵ���ڵأ���4����ҵ���ṩ��Ʒ������info��ʾ�µ���Ϣֵ���޸ĳɹ�����0�����򷵻�1
int modifyMCom(MComsSeqList* mcsl, int index, int type, char* info);
//��Ϲ��ܽ���3�����ܺ������ڲ�Ʒ�ɹ���ҵ��mcsl���޸ĵ�index����ҵ����Ϣ��type��ʾҪ�޸ĵ����ͣ�ȡֵ1����ҵ��ţ���2����ҵ���ƣ���3����ҵ���ڵأ���4����ҵ���ṩ��Ʒ������info��ʾ�µ���Ϣֵ���޸ĳɹ�����0�����򷵻�1
int modifyPCom(PComsSeqList* pcsl, int index, int type, char* info);

//��Ϲ��ܽ���4�����ܺ���--�����ṩ��ԭ����ҵ��Ϣ��tpyeȡֵ1����ҵ���ƣ���2����ҵ���ڵأ���3����ҵ�ṩԭ�ϣ�����ѯ��ؼ�¼����ҵ��Ϣ��
//               ���û���ҵ����򷵻� - 1������У���ѯ�����һ��IntSeqList�б��أ��б�װ������ҵ��˳����е����
int searchMComByOthers(MComsSeqList mcsl, char* info, int type, IntSeqList* mcindex);
//��Ϲ��ܽ���4�����ܺ���--���ݲɹ���Ʒ����ҵ��Ϣ��tpyeȡֵ1����ҵ���ƣ���2����ҵ���ڵأ���3����ҵ������Ʒ������ѯ��ؼ�¼����ҵ��Ϣ��
//               ���û���ҵ����򷵻� - 1������У���ѯ�����һ��IntSeqList�б��أ��б�װ������ҵ��˳����е����
int searchPComByOthers(PComsSeqList pcsl, char* info, int type, IntSeqList* pcindex);
//��Ϲ��ܽ���5�����ܺ���--������ϵͳ������ɾ�����ĺ����Ϣ�������ݿ���
int allMComsInfoSaveToFile(MComsSeqList mcsl, char* filename);
//��Ϲ��ܽ���5�����ܺ���--������ϵͳ������ɾ�����ĺ����Ϣ�������ݿ���
int allPComsInfoSaveToFile(PComsSeqList pcsl, char* filename);
//��ͨ�ã���Ϲ��ܽ���5�����ܺ���--�����ͱ��������Ϣ���ļ���
int allSave(int type);

void BubbleSortPrice(MComsSeqList* mcsl);
void MySwap(MComsSeqList* mcsl, int x, int y);

/*----------------------ԭ�Ϲ�Ӧ��ҵ��Ϣ�������ݽṹ�ӿ�----------------------*/
//���ݽṹ����1��MCom����-��ʼ������� mcsl��size��ʾ��ʼ������
void MComsSeqListInit(MComsSeqList* mcsl, int size) {
	mcsl->list = (MComInfo*)malloc(size * sizeof(MComInfo));
	mcsl->size = size;
	mcsl->length = 0;
}

//���ݽṹ����2��MCom����--���ݿ���Ϣ��ʼ��
int allMComsInfoReadFromFile(MComsSeqList* mcsl, char* filename) {
	FILE *fp;
	char strline[80];             //ÿ������ȡ���ַ���
	if ((fp = fopen(filename, "r")) == NULL) { //�ж��ļ��Ƿ���ڼ��ɶ�
		errorTemplate(48, "���� MES���ݿ���Ϣ����");
		return -1;
	}
	MComInfo newMCom;
	while (!feof(fp)) {
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newMCom.MCom_id, strline);
		else {
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newMCom.MCom_name, strline);
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newMCom.MCom_location, strline);
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newMCom.MCom_material, strline);
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			newMCom.MCom_price = atof(strline);
		}
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			strcpy(newMCom.in_time, strline);
		}
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		addNewMCom(mcsl, newMCom);
	}
	fclose(fp);//�ر��ļ�
	return 0;
}

//���ݽṹ����3��PCom����-��ʼ������� pcsl��size��ʾ��ʼ������
void PComsSeqListInit(PComsSeqList* pcsl, int size) {
	pcsl->list = (PComInfo*)malloc(size * sizeof(PComInfo));
	pcsl->size = size;
	pcsl->length = 0;
}

//���ݽṹ����4��PCom����--���ݿ���Ϣ��ʼ��
int allPComsInfoReadFromFile(PComsSeqList* pcsl, char* filename) {
	FILE *fp;
	char strline[80];             //ÿ������ȡ���ַ���
	if ((fp = fopen(filename, "r")) == NULL) { //�ж��ļ��Ƿ���ڼ��ɶ�
		errorTemplate(48, "���� MES���ݿ���Ϣ����");
		return -1;
	}
	PComInfo newPCom;
	while (!feof(fp)) {
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newPCom.PCom_id, strline);
		else {
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newPCom.PCom_name, strline);
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newPCom.PCom_location, strline);
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newPCom.PCom_material, strline);
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			newPCom.PCom_price = atof(strline);
		}
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			strcpy(newPCom.in_time, strline);
		}
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		addNewPCom(pcsl, newPCom);
	}
	fclose(fp);//�ر��ļ�
	return 0;
}

//����1��root�����û��ĵ�½����
void rootLeaderInterface() {
	int choice = 0;
	frameShow();
	Gotoxy(44 + 5, 9.5);
	printf("³��MES�ǻۿ������");
	Gotoxy(44, 12);		//��̬�ƶ���꣬ͬʱ��ҳ�������꣨48��10����Ϊ��׼�ƶ�����Ĺ��
	printf("1.ִ �� �� �� �� �� Ա Ȩ �� ");
	Gotoxy(44, 14);
	printf("2.ִ �� �����������ʦ Ȩ �� ");
	Gotoxy(44, 16);
	printf("3.ִ �� ���߼ල����ʦ Ȩ �� ");
	Gotoxy(44, 18);
	printf("4.ִ �� �� Ʒ �� �� Ա Ȩ �� ");
	Gotoxy(44, 20);
	printf("5.�� �� �� �� �û�ROOT Ȩ �� ");
	Gotoxy(44, 24);
	printf("��������Ҫִ�е�Ȩ�ޱ��룺");//23
	Gotoxy(44 + 23 + 4, 24);
	scanf("%d", &choice);
	switch (choice) {
		case 1: {
			rootWelcome(44+3, "��ӭ����³�೬��Root�û���","��ʾ��������ִ�вִ�����Ա������Ȩ�ޣ�" ,choice);
			wareInterface();
		}
		case 2: {
			rootWelcome(44 + 3, "��ӭ����³�೬��Root�û���", "��ʾ��������ִ���������ʦ������Ȩ�ޣ�", choice);
			DProcessInterface();
		}
		case 3: {
			rootWelcome(44 + 3, "��ӭ����³�೬��Root�û���", "��ʾ��������ִ����������ʦ������Ȩ�ޣ�", choice);
			SuperPLInterface();
		}
		case 4: {
			rootWelcome(44 + 3, "��ӭ����³�೬��Root�û���", "��ʾ��������ִ�в�Ʒ����Ա������Ȩ�ޣ�", choice);
			proSalesInterface();
		}
		case 5: {
			exitMES(0);
		}
		default: {
			errorTemplate(47.5, "�������������������룡");
			rootLeaderInterface();
		}
	}
}

//����2����ҵ�����ߵĵ�½����
void adminLeaderInterface() {			//��ҵ�����ߵĽ�ɫ����MESϵͳ����
	system("cls");
	int choice = 0;
	frameShow();
	Gotoxy(44 + 5, 6.5);
	printf("³��MES�ǻۿ������");
	Gotoxy(44 + 2, 9);		//��̬�ƶ���꣬ͬʱ��ҳ�������꣨48��10����Ϊ��׼�ƶ�����Ĺ��
	printf("1.ԭ �� �� Ӧ �� Ϣ ά �� ");
	Gotoxy(44 + 2, 11);
	printf("2.�� �� �� �� �� Ϣ �� �� ");
	Gotoxy(44 + 2, 13);
	printf("3.�� �� �� �� �� Ϣ �� �� ");
	Gotoxy(44 + 2, 15);
	printf("4.�� �� �� �� �� Ϣ �� �� ");
	Gotoxy(44 + 2, 17);
	printf("5.�� �� �� �� �� Ϣ �� �� ");
	Gotoxy(44 + 2, 19);
	printf("6.�� Ʒ �� �� �� Ϣ ά �� ");
	Gotoxy(44 + 2, 21);
	printf("7.�� �� �� �� �� �� �� �� ");
	Gotoxy(44 + 2, 24);
	printf("����������Ҫ�����ı��룺");
	Gotoxy(44 + 23 + 3, 24);
	scanf("%d", &choice);
	Gotoxy(44 + 2+27, 24);
	charRotation();
	switch (choice){
		case 1: {
			materialComInterface();
		}
		case 2: {
			queryMWareAdmin();
		}	
		case 3: {
			checkDProcessAdmin();
		}
		case 4: {
			//9.����ӿں���--����Ա�������߹����鿴
			checkPLineAdmin();
		}
		case 5: {
			//10.����ӿں���--����Ա�������������鿴
			checkPToolAdmin();
		}
		case 6: {
			productComInterface();
		}
		case 7: {
			exitMES(1);
		}
		default: {
			errorTemplate(47.5, "�������������������룡");
			adminLeaderInterface();
		}
	}
}

//����3��ԭ�Ϲ�Ӧ��ҵ��Ϣ�������
void materialComInterface() {	//ԭ�Ϲ�Ӧ��ҵ��Ϣ�������
	int choice;
	system("cls");
	frameShow();
	Gotoxy(44 + 5, 7.5);
	printf("ԭ�Ϲ�Ӧ��ҵ��Ϣ����");
	Gotoxy(44 + 4, 10);		//��̬�ƶ���꣬ͬʱ��ҳ�������꣨48��10����Ϊ��׼�ƶ�����Ĺ��
	printf("1.ǩ��ԭ�Ϲ�Ӧ��ҵ����");
	Gotoxy(44 + 4, 12);
	printf("2.���ԭ�Ϲ�Ӧ��ҵ����");
	Gotoxy(44 + 4, 14);
	printf("3.ԭ�Ϲ�Ӧ��ҵ��Ϣ�޸�");
	Gotoxy(44 + 4, 16);
	printf("4.ԭ�Ϲ�Ӧ��ҵ��Ϣ��ѯ");
	Gotoxy(44 + 4, 18);
	printf("5.����ԭ�Ϲ�Ӧ��ҵ��Ϣ ");
	Gotoxy(44 + 4, 20);
	printf("6.�˳�ԭ�Ϲ�Ӧ��ҵ����");
	Gotoxy(44 +3, 24);
	printf("����������Ҫ�����ı��룺 ");
	scanf("%d", &choice);
	Gotoxy(44 + 3 +12*2 + 0.5 +2, 24);
	charRotation();
	switch (choice) {
	case 1: {
		addMaterialCom();
	}
	case 2: {
		deleteMaterialCom();
	}
	case 3: {
		modifiMCom();
	}
	case 4: {
		queryMCom();
	}
	case 5: {
		saveMCom();
	}
	case 6: {
		errorTemplate(47.5, "�����˳���Ӧ��ҵ������壡");
		adminLeaderInterface();
	}
	default: {
		errorTemplate(47.5, "�������������������룡");
		materialComInterface();
	}
	}
}

//����4����Ʒ�ɹ���ҵ��Ϣ�������
void productComInterface() {	//��Ʒ�ɹ���ҵ��Ϣ�������
	int choice;
	system("cls");
	frameShow();
	Gotoxy(44 + 5, 7.5);
	printf("��Ʒ�ɹ���ҵ��Ϣ����");
	Gotoxy(44 + 4, 10);		//��̬�ƶ���꣬ͬʱ��ҳ�������꣨48��10����Ϊ��׼�ƶ�����Ĺ��
	printf("1.ǩ����Ʒ�ɹ���ҵ����");
	Gotoxy(44 + 4, 12);
	printf("2.�����Ʒ�ɹ���ҵ����");
	Gotoxy(44 + 4, 14);
	printf("3.ԭ�ϲ�Ʒ�ɹ���Ϣ�޸�");
	Gotoxy(44 + 4, 16);
	printf("4.ԭ�ϲ�Ʒ�ɹ���Ϣ��ѯ");
	Gotoxy(44 + 4, 18);
	printf("5.�����Ʒ�ɹ���ҵ��Ϣ ");
	Gotoxy(44 + 4, 20);
	printf("6.�˳���Ʒ�ɹ���ҵ����");
	Gotoxy(44 + 3, 24);
	printf("����������Ҫ�����ı��룺 ");
	scanf("%d", &choice);
	Gotoxy(44 + 3 + 12 * 2 + 0.5 + 2, 24);
	charRotation();
	switch (choice) {
		case 1: {
			addProductCom();
		}
		case 2: {
			deleteProductCom();
		}
		case 3: {
			modifiPCom();
		}
		case 4: {
			queryPCom();
		}
		case 5: {
			savePCom();
		}
		case 6: {
			errorTemplate(47.5, "�����˳��ɹ���ҵ������壡");
			adminLeaderInterface();
		}
		default: {
			errorTemplate(47.5, "�������������������룡");
			materialComInterface();
		}
	}
}

//����5����ҵԱ����Ϣ������棨�������ƵĽӿڣ��ݲ����ã�
/*�ݲ����õ���ҵԱ����Ϣ�������
void employeeInterface() {		//��ҵԱ����Ϣ�������
	int choice;
	system("cls");
	frameShow();
	Gotoxy(44 + 7, 7.5);
	printf("��ҵԱ����Ϣ����");
	Gotoxy(44 + 5, 10);		//��̬�ƶ���꣬ͬʱ��ҳ�������꣨48��10����Ϊ��׼�ƶ�����Ĺ��
	printf("1.�����ҵԱ����Ϣ");
	Gotoxy(44 + 5, 12);
	printf("2.ɾ����ҵԱ����Ϣ");
	Gotoxy(44 + 5, 14);
	printf("3.��ҵԱ����Ϣ�޸�");
	Gotoxy(44 + 5, 16);
	printf("4.��ҵԱ����Ϣ��ѯ ");
	Gotoxy(44 + 5, 18);
	printf("5.������ҵԱ����Ϣ ");
	Gotoxy(44 + 5, 20);
	printf("6.�˳�Ա����Ϣ����");
	Gotoxy(44 + 5, 24);
	printf("����������Ҫ�����ı��룺");
	Gotoxy(44 + 23 + 1, 24);
	scanf("%d", &choice);
	
}
*/

//���ܽ���1��ԭ�Ϲ�Ӧ��ҵǩ������
void addMaterialCom() {
	system("cls");
	frameShow();
	char temp[80];//��Ϊ�۸�Ľ���ֵ
	MComInfo newMCom;
	Gotoxy(44 + 5, 9.5);
	printf("ԭ�Ϲ�Ӧ��ҵǩԼ���");
	Gotoxy(44, 12);
	printf("1.ԭ�Ϲ�Ӧ��ҵ��ţ�");
	Gotoxy(44+20.5+4, 12);
	scanf("%s", newMCom.MCom_id);
	Gotoxy(44, 14);
	printf("2.ԭ�Ϲ�Ӧ��ҵ���ƣ�");
	Gotoxy(44 + 20.5 + 4, 14);
	scanf("%s", newMCom.MCom_name);
	Gotoxy(44, 16);
	printf("3.��Ӧԭ�ϵ����ڵأ�");
	Gotoxy(44 + 20.5 + 4, 16);
	scanf("%s", newMCom.MCom_location);
	Gotoxy(44, 18);
	printf("4.��Ӧ��ҵ�ṩ��Ʒ��");
	Gotoxy(44 + 20.5 + 4, 18);
	scanf("%s", newMCom.MCom_material);
	Gotoxy(44, 20);
	printf("5.��ҵ��Ӧԭ�ϼ۸�");
	Gotoxy(44 + 20.5 + 4, 20);
	scanf("%s", temp);
	newMCom.MCom_price= atof(temp);
	getTimeNow(newMCom.in_time);
	Gotoxy(44-3, 24);
	printf("ȷ��ǩԼ�ü�ԭ�Ϲ�Ӧ��ҵ? y/n ��  ");
	int r1;
	scanf("%s", temp);
	Gotoxy(44-3, 26);
	if (temp[0] == 'y') {
		r1 = addNewMCom(&allMComslist, newMCom);
		if (r1 == -1) {
			printf("ǩԼ��ҵʧ�ܣ��������ҵ��Ϣ��  ");
			charRotation();
			materialComInterface();
		}
		else {
			printf("ǩԼ��ҵ�ɹ����ɹ������ҵ��Ϣ��  ");
			charRotation();
			materialComInterface();
		}
	}
	//����no�������
	else if (temp[0] == 'n') {
		printf("���ڷ���ǩԼ��壬��ȷ�Ϻ����룡 ");
		charRotation();
		Sleep(5000);
		materialComInterface();
	}
	//�������ȥy��n�������ַ��Ļ�
	else {
		printf("��������������ȷ��Ҫ������룡 ");
		charRotation();
		Sleep(5000);
		addMaterialCom();
	}
}

//���ܽ���2�����ԭ�Ϲ�Ӧ��ҵ������ϵ����
void deleteMaterialCom() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(44 + 3,8);
	printf("ԭ�Ϲ�Ӧ��ҵ��Լ���");
	Gotoxy(43,11);
	printf("����������Ҫ��Լ����ҵ��ţ�");
	scanf("%s", temp);
	Gotoxy(43+31.5, 11);
	charRotation();
	int r1 = searchMCom(allMComslist, temp);
	//��������ֲ���ʧ�ܵ����
	if (r1 < 0) {
		Gotoxy(44, 13);
		printf("��ѯ��ҵʧ�ܣ�ȷ�Ϻ�����  ");
		charRotation();
		deleteMaterialCom();
	}
	else {
		Gotoxy(43, 13);
		printf("����ȷ����Ҫ��Լ����ҵ��Ϣ��");
		Gotoxy(44, 15);
		printf("1.ԭ�Ϲ�Ӧ��ҵ��ţ� %s",allMComslist.list[r1].MCom_id);
		Gotoxy(44, 17);
		printf("2.ԭ�Ϲ�Ӧ��ҵ���ƣ� %s",allMComslist.list[r1].MCom_name);
		Gotoxy(44, 19);
		printf("3.��Ӧ��ҵ�����ڵأ� %s",allMComslist.list[r1].MCom_location);
		Gotoxy(44, 21);
		printf("4.ԭ�Ϲ�Ӧ�ṩ��Ʒ�� %s",allMComslist.list[r1].MCom_material);
		Gotoxy(44, 23);
		printf("5.ԭ�Ϲ�Ӧ��ҵ�۸� %.2f",allMComslist.list[r1].MCom_price);
		Gotoxy(44, 25);
		printf("6.ǩ����ҵ��Լʱ�䣺 %s",allMComslist.list[r1].in_time);
		Gotoxy(44-2, 28);
		printf("ȷ�Ͻ������ҵ������ϵ�� y/n:  ");
		scanf("%s", temp);
		Gotoxy(44 - 2 + 33 , 28);
		charRotation();
		Gotoxy(44 - 2,29);
		if (temp[0] == 'y') {
			int r3 = delMCom(&allMComslist, r1);
			if (r3 == -1){
				printf("��Լʧ�ܣ��������ҵ��Ϣʧ�ܣ�");
				Sleep(5000);
				materialComInterface();
			}
			else {
				printf("��Լ�ɹ����ѳɹ�ɾ������ҵ��Ϣ��");
				Sleep(1000);
				materialComInterface();
			}
				
		}
		//����no�������
		else if (temp[0] == 'n') {
			printf("���ڷ��ع�����壬��ȷ�Ϻ����룡 ");
			charRotation();
			Sleep(5000);
			materialComInterface();
		}
		//�������ȥy��n�������ַ��Ļ�
		else {
			printf("��������������ȷ��Ҫ������룡 ");
			charRotation();
			Sleep(5000);
			deleteMaterialCom();
		}
	}
}

//���ܽ���3���޸���ҵ��Ӧԭ�Ͻ���
void modifiMCom() {
	system("cls");
	frameShow();
	Gotoxy(44 + 3, 5);
	printf("ԭ�Ϲ�Ӧ��ҵ�޸����");
	char temp[30];
	Gotoxy(43, 8);
	printf("����������Ҫ�޸ĵ���ҵ��ţ�");
	scanf("%s", temp);
	Gotoxy(43 + 31.5, 8);
	charRotation();
	int r1 = searchMCom(allMComslist, temp);
	int r2=0, r3 = 0;
	//��������ֲ���ʧ�ܵ����
	if (r1 < 0) {
		Gotoxy(44, 10);
		printf("��ѯ��ҵʧ�ܣ�ȷ�Ϻ�����  ");
		charRotation();
		modifiMCom();
	}
	else {
		Gotoxy(43, 10);
		printf("����ȷ����Ҫ�޸ĵ���ҵ��Ϣ��");
		Gotoxy(44, 12);
		printf("1.ԭ�Ϲ�Ӧ��ҵ��ţ� %s", allMComslist.list[r1].MCom_id);
		Gotoxy(44, 14);
		printf("2.ԭ�Ϲ�Ӧ��ҵ���ƣ� %s", allMComslist.list[r1].MCom_name);
		Gotoxy(44, 16);
		printf("3.ԭ�Ϲ�Ӧ�����ڵأ� %s", allMComslist.list[r1].MCom_location);
		Gotoxy(44, 18);
		printf("4.ԭ�Ϲ�Ӧ�ṩ��Ʒ�� %s", allMComslist.list[r1].MCom_material);
		Gotoxy(44, 20);
		printf("5.ԭ�Ϲ�Ӧ��ҵ�۸� %.2f", allMComslist.list[r1].MCom_price);
		Gotoxy(44, 22);
		printf("6.ǩ����ҵ��Լʱ�䣺 %s", allMComslist.list[r1].in_time);
		while (1) {
			Gotoxy(44 - 2, 24);
			printf("ѡ��Ҫ�޸ĵ����ݱ�ţ� ");
			char temp[30];
			scanf("%s", temp);
			r2 = atoi(temp);
			//����ı���ڷ�Χ֮�ڵģ�1~6��
			if (r2 >= 1 && r2 <= 6) {
				char newContent[50];
				Gotoxy(44 - 2, 26);
				printf("���޸Ĳ��ֵ�������Ϊ�� ");
				scanf("%s", newContent);
				r3 = modifyMCom(&allMComslist, r1, r2, newContent);
				if (r3 == -1) {
					Gotoxy(44 - 2, 28);
					printf("�޸���ҵ��Ϣʧ�ܣ�  ");
					charRotation();
					Sleep(5000);
					materialComInterface();
				}
				else {
					Gotoxy(44 - 2, 28);
					printf("ѡ���޸���ҵ��Ϣ�ɹ��� ");
					charRotation();
					Sleep(3000);
					materialComInterface();
				}
				break;
			}
			//����ı�Ų��ڷ�Χ�ڵ�
			else {
				Gotoxy(44 - 2, 26);
				printf("�������ѡ���Ŵ��� ");
				charRotation();
				Sleep(5000);
				materialComInterface();
			}
		}
	}

}

//���ܽ���4����ѯ��Ӧ��ҵ��Ϣ����
void queryMCom() {
	system("cls");
	frameShow();
	Gotoxy(22+1.5,8);
	printf("ԭ�Ϲ�Ӧ��ҵ��ѯ���");
	Gotoxy(22, 10);
	printf("����ȷ�ϲ�ѯ��ҵ��Ϣ�ķ�ʽ��");
	int choice, r2;
	while (1) {
		Gotoxy(22, 12);
		printf("1.ԭ�Ϲ�Ӧ��ҵ���");
		Gotoxy(22, 14);
		printf("2.ԭ�Ϲ�Ӧ��ҵ����");
		Gotoxy(22, 16);
		printf("3.ԭ�Ϲ�Ӧ�����ڵ�");
		Gotoxy(22, 18);
		printf("4.��ҵ�ṩԭ������");
		Gotoxy(22, 20);
		printf("5.��ʾ���й�Ӧ��ҵ");
		Gotoxy(22, 22);
		printf("6.������ҵ�������");
		Gotoxy(22, 25);
		printf("�������ѯ��ʽ�ı�ţ� ");
		char temp[80];
		scanf("%s", temp);
		Gotoxy(22 + 23 + 2,25);//����
		charRotation();
		choice = atoi(temp);
		switch (choice) {
			//����Ĳ�ѯ��ʽΪ1ʱ����ʱ��ѯ��ʽΪ��ҵ���
			case 1: {
				char content[50];
				Gotoxy(22, 27);
				printf("��������Ҫ��ѯ�����ݣ� ");
				scanf("%s", content);
				Gotoxy(22 + 20 + 5 , 27);
				charRotation();
				r2 = searchMCom(allMComslist, content);
				if (r2 < 0) {
					Gotoxy(22+20+10, 27);
					printf("��ѯ����ʧ�ܣ�ȷ�Ϻ�����  ");
					charRotation();
					queryMCom();
				}
				else {
					Gotoxy(58 + 22-16, 10);
					printf("1.ԭ�Ϲ�Ӧ��ҵ��ţ� %s", allMComslist.list[r2].MCom_id);
					Gotoxy(58 + 22 - 16, 12);
					printf("2.ԭ�Ϲ�Ӧ��ҵ���ƣ� %s", allMComslist.list[r2].MCom_name);
					Gotoxy(58 + 22 - 16, 14);
					printf("3.ԭ�Ϲ�Ӧ�����ڵأ� %s", allMComslist.list[r2].MCom_location);
					Gotoxy(58 + 22 - 16, 16);
					printf("4.ԭ�Ϲ�Ӧ�ṩ��Ʒ�� %s", allMComslist.list[r2].MCom_material);
					Gotoxy(58 + 22 - 16, 18);
					printf("5.ԭ�Ϲ�Ӧ��ҵ�۸� %.2f", allMComslist.list[r2].MCom_price);
					Gotoxy(58 + 22 - 16, 20);
					printf("6.ǩ����ҵ��Լʱ�䣺 %s", allMComslist.list[r2].in_time);
					Gotoxy(58 + 22 - 16, 24);
					printf("�鿴�����������y������һ�㣺 ");
					scanf("%s", temp);
					if (temp[0] == 'y') {
						Gotoxy(58 + 22+16*2+1.5-16+1, 24);
						charRotation();
						Sleep(1000);
						queryMCom();
					}
					else {
						Gotoxy(58 + 22 + 16 * 2 + 1.5 - 16 + 1, 24);
						printf("��������Ϊ����������� ");
						charRotation();
						Sleep(1000);
						materialComInterface();
					}
				}
				break;
			}
			//����Ĳ�ѯ��ʽΪ2ʱ����ʱ��ѯ��ʽΪ��ҵ����
			case 2: {
				char content[50];
				Gotoxy(22, 27);
				printf("��������Ҫ��ѯ�����ݣ� ");
				scanf("%s", content);
				Gotoxy(22 + 23 + 28 , 27);
				charRotation();
				IntSeqList result;
				intListInit(&result, 5);
				searchMComByOthers(allMComslist, content, choice, &result);
				if (result.length == 0) {
					errorTemplate(48,"û��������������ҵ��Ϣ��");
					queryMCom();
				}
				//����ɹ��ҵ��ж�Ӧ��ֵ
				else {
					system("cls");
					frameShow();
					//����һ��
					Gotoxy(6, 4);
					printf("��ҵ���               ��ҵ����             ��ҵ���ڵ�    ��ҵ��Ӧԭ��      ��Ӧԭ�ϼ۸�           ��ҵǩԼʱ��");
					for (int i = 0; i < result.length; i++) {
						Gotoxy(8, 8 + i);
						printf("%s         %s    %s     %s         %.2f           %s", allMComslist.list[result.list[i]].MCom_id, allMComslist.list[result.list[i]].MCom_name, allMComslist.list[result.list[i]].MCom_location, allMComslist.list[result.list[i]].MCom_material, allMComslist.list[result.list[i]].MCom_price, allMComslist.list[result.list[i]].in_time);
					}
					//�����˳��Ľӿ�
					char yes[3];
					Gotoxy((117 - 16 * 2) / 2, 28);
					printf("�鿴�����������y������һ�㣺 ");
					scanf("%s", yes);
					if (yes[0] == 'y') {
						Gotoxy((117 - 16 * 2) / 2 + 16 * 2 + 2, 28);
						charRotation();
						Sleep(1000);
						queryMCom();
					}
					//������������
					else {
						Gotoxy(58 + 22, 28);
						printf("��������Ϊ����������� ");
						charRotation();
						Sleep(1000);
						materialComInterface();
					}
				}
				errorTemplate(48, "û��������������ҵ��Ϣ��");
				materialComInterface();
				break;
			}
			//����Ĳ�ѯ��ʽΪ3ʱ����ʱ��ѯ��ʽΪ��ҵ�ص�
			case 3: {
				char content[50];
				Gotoxy(22, 27);
				printf("��������Ҫ��ѯ�����ݣ� ");
				scanf("%s", content);
				Gotoxy(22 + 23 + 28-15, 27);
				charRotation();
				IntSeqList result;
				intListInit(&result, 5);
				searchMComByOthers(allMComslist, content, choice, &result);
				if (result.length == 0) {
					errorTemplate(48, "û��������������ҵ��Ϣ��");
					queryMCom();
				}
				//����ɹ��ҵ��ж�Ӧ��ֵ
				else {
					system("cls");
					frameShow();
					//����һ��
					Gotoxy(6, 4);
					printf("��ҵ���               ��ҵ����             ��ҵ���ڵ�    ��ҵ��Ӧԭ��      ��Ӧԭ�ϼ۸�       ��ҵǩԼʱ��");
					for (int i = 0; i < result.length; i++) {
						Gotoxy(8 + 0.5, 8 + i * 1.5);
						printf("%s         %s    %s     %s         %.2f           %s", allMComslist.list[result.list[i]].MCom_id, allMComslist.list[result.list[i]].MCom_name, allMComslist.list[result.list[i]].MCom_location, allMComslist.list[result.list[i]].MCom_material, allMComslist.list[result.list[i]].MCom_price, allMComslist.list[result.list[i]].in_time);
					}
					//�����˳��Ľӿ�
					char yes[3];
					Gotoxy((117 - 16 * 2) / 2, 28);
					printf("�鿴�����������y������һ�㣺 ");
					scanf("%s", yes);
					if (yes[0] == 'y') {
						Gotoxy((117 - 16 * 2) / 2 + 16 * 2 + 2, 28);
						charRotation();
						Sleep(1000);
						queryMCom();
					}
					//������������
					else {
						Gotoxy(58 + 22, 28);
						printf("��������Ϊ����������� ");
						charRotation();
						Sleep(1000);
						materialComInterface();
					}
				}
				errorTemplate(48, "û��������������ҵ��Ϣ��");
				materialComInterface();
				break;
			}
			//����Ĳ�ѯ��ʽΪ4ʱ����ʱ��ѯ��ʽΪ��ҵ�ṩԭ��
			case 4: {
				char content[50];
				Gotoxy(22, 27);
				printf("��������Ҫ��ѯ�����ݣ� ");
				scanf("%s", content);
				Gotoxy(22 + 23 + 28 - 15, 27);
				charRotation();
				IntSeqList result;
				intListInit(&result, 5);
				searchMComByOthers(allMComslist, content, choice, &result);
				if (result.length == 0) {
					errorTemplate(48, "û��������������ҵ��Ϣ��");
					queryMCom();
				}
				//����ɹ��ҵ��ж�Ӧ��ֵ
				else {
					system("cls");
					frameShow();
					//����һ��
					Gotoxy(6, 4);
					printf("��ҵ���               ��ҵ����             ��ҵ���ڵ�    ��ҵ��Ӧԭ��      ��Ӧԭ�ϼ۸�       ��ҵǩԼʱ��");
					for (int i = 0; i < result.length; i++) {
						Gotoxy(8 + 0.5, 8 + i * 1.5);
						printf("%s         %s    %s     %s         %.2f           %s", allMComslist.list[result.list[i]].MCom_id, allMComslist.list[result.list[i]].MCom_name, allMComslist.list[result.list[i]].MCom_location, allMComslist.list[result.list[i]].MCom_material, allMComslist.list[result.list[i]].MCom_price, allMComslist.list[result.list[i]].in_time);
					}
					//�����˳��Ľӿ�
					char yes[3];
					Gotoxy((117 - 16 * 2) / 2, 28);
					printf("�鿴�����������y������һ�㣺 ");
					scanf("%s", yes);
					if (yes[0] == 'y') {
						Gotoxy((117 - 16 * 2) / 2 + 16 * 2 + 2, 28);
						charRotation();
						Sleep(1000);
						queryMCom();
					}
					//������������
					else {
						Gotoxy(58 + 22, 28);
						printf("��������Ϊ����������� ");
						charRotation();
						Sleep(1000);
						materialComInterface();
					}
				}
				errorTemplate(48, "û��������������ҵ��Ϣ��");
				materialComInterface();
				break;
			}
			//����Ĳ�ѯ��ʽΪ4ʱ����ʱ��ѯ��ʽΪ��ʾ������ҵ
			case 5:{
				if (allMComslist.length == 0) {
					errorTemplate(48, "������ҵ��Ϣ���ݿ�Ϊ�գ�");
					queryMCom();
				}
				system("cls");
				frameShow();
				//����һ��
				Gotoxy(6, 4);
				printf("��ҵ���               ��ҵ����             ��ҵ���ڵ�    ��ҵ��Ӧԭ��      ��Ӧԭ�ϼ۸�       ��ҵǩԼʱ��");
				for (int i = 0; i < allMComslist.length; i++) {
					Gotoxy(8 + 0.5, 8 + i * 1.5);
					printf("%s         %s    %s     %s         %.2f           %s\n", allMComslist.list[i].MCom_id, allMComslist.list[i].MCom_name, allMComslist.list[i].MCom_location, allMComslist.list[i].MCom_material, allMComslist.list[i].MCom_price, allMComslist.list[i].in_time);
				}
				//�����˳��Ľӿ�
				char yes[3];
				Gotoxy((117 - 16 * 2) / 2, 28);
				printf("�鿴�����������y������һ�㣺 ");
				scanf("%s", yes);
				if (yes[0] == 'y') {
					Gotoxy((117 - 16 * 2) / 2 + 16 * 2 + 2, 28);
					charRotation();
					Sleep(1000);
					queryMCom();
				}
				//������������
				else {
					Gotoxy(58 + 22, 28);
					printf("��������Ϊ����������� ");
					charRotation();
					Sleep(1000);
					materialComInterface();
				}
			}
		    //����Ĳ�ѯ��ʽΪ6ʱ����ʱ�˳���ѯ��ҵ���
			case 6: {
				errorTemplate(48.5, "���ڷ�����ҵ������壡");
				materialComInterface();
			}
			//errorTemplate(48, "û��������������ҵ��Ϣ��");
			//materialComInterface();
			//break;
			//����Ĳ�ѯ��ʽ���ڲ�ѯ��ʽ�ķ�Χ��ʱ��1~6��
			//������Ĳ�ѯ��ʽ���ڷ�Χ�ڵ�ʱ�򣬻�ִ��defult
			default: {
				errorTemplate(48, "����Ĳ�ѯ��ʽ�������");
				queryMCom();
			}
			}
	}
}

//���ܽ���5�����湩Ӧ��ҵ��Ϣ����
void saveMCom() {
	int r1 = allSave(1);
	if (r1 == -1 ) {
		errorTemplate(48, "���浱ǰ����ҵ��Ϣʧ�ܣ�");
		materialComInterface();
	}
	else {
		errorTemplate(48, "���ڱ������е���ҵ��Ϣ��");
		errorTemplate(48, "�������е���ҵ��Ϣ�ɹ���");
		materialComInterface();
	}
}

//���ܽ���6����Ʒ�ɹ���ҵǩ������
void addProductCom() {
	system("cls");
	frameShow();
	char temp[80];//��Ϊ�۸�Ľ���ֵ
	PComInfo newPCom;
	Gotoxy(44 + 5, 9.5);
	printf("��Ʒ�ɹ���ҵǩԼ���");
	Gotoxy(44, 12);
	printf("1.��Ʒ�ɹ���ҵ��ţ�");
	Gotoxy(44 + 20.5 + 4, 12);
	scanf("%s", newPCom.PCom_id);
	Gotoxy(44, 14);
	printf("2.��Ʒ�ɹ���ҵ���ƣ�");
	Gotoxy(44 + 20.5 + 4, 14);
	scanf("%s", newPCom.PCom_name);
	Gotoxy(44, 16);
	printf("3.�ɹ���ҵ�����ڵأ�");
	Gotoxy(44 + 20.5 + 4, 16);
	scanf("%s", newPCom.PCom_location);
	Gotoxy(44, 18);
	printf("4.�ɹ���ҵ������Ʒ��");
	Gotoxy(44 + 20.5 + 4, 18);
	scanf("%s", newPCom.PCom_material);
	Gotoxy(44, 20);
	printf("5.�ɹ���ҵ�����۸�");
	Gotoxy(44 + 20.5 + 4, 20);
	scanf("%s", temp);
	newPCom.PCom_price = atof(temp);
	getTimeNow(newPCom.in_time);
	Gotoxy(44 - 3, 24);
	printf("ȷ��ǩԼ�üҲ�Ʒ�ɹ���ҵ? y/n ��  ");
	int r1;
	scanf("%s", temp);
	Gotoxy(44 - 3, 26);
	if (temp[0] == 'y') {
		r1 = addNewPCom(&allPComslist, newPCom);
		if (r1 == -1) {
			printf("ǩԼ��ҵʧ�ܣ��������ҵ��Ϣ��  ");
			charRotation();
			productComInterface();
		}
		else {
			printf("ǩԼ��ҵ�ɹ����ɹ������ҵ��Ϣ��  ");
			charRotation();
			productComInterface();
		}
	}
	//����no�������
	else if (temp[0] == 'n') {
		printf("���ڷ���ǩԼ��壬��ȷ�Ϻ����룡 ");
		charRotation();
		Sleep(5000);
		productComInterface();
	}
	//�������ȥy��n�������ַ��Ļ�
	else {
		printf("��������������ȷ��Ҫ������룡 ");
		charRotation();
		Sleep(5000);
		addProductCom();
	}
}

//���ܽ���7�������Ʒ�ɹ���ҵ������ϵ����
void deleteProductCom() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(44 + 3, 8);
	printf("��Ʒ�ɹ���ҵ��Լ���");
	Gotoxy(43, 11);
	printf("����������Ҫ��Լ����ҵ��ţ�");
	scanf("%s", temp);
	Gotoxy(43 + 31.5, 11);
	charRotation();
	int r1 = searchPCom(allPComslist, temp);
	//��������ֲ���ʧ�ܵ����
	if (r1 < 0) {
		Gotoxy(44, 13);
		printf("��ѯ��ҵʧ�ܣ�ȷ�Ϻ�����  ");
		charRotation();
		deleteProductCom();
	}
	else {
		Gotoxy(43, 13);
		printf("����ȷ����Ҫ��Լ����ҵ��Ϣ��");
		Gotoxy(44, 15);
		printf("1.��Ʒ�ɹ���ҵ��ţ� %s", allPComslist.list[r1].PCom_id);
		Gotoxy(44, 17);
		printf("2.��Ʒ�ɹ���ҵ���ƣ� %s", allPComslist.list[r1].PCom_name);
		Gotoxy(44, 19);
		printf("3.�ɹ���ҵ�����ڵأ� %s", allPComslist.list[r1].PCom_location);
		Gotoxy(44, 21);
		printf("4.�ɹ���ҵ������Ʒ�� %s", allPComslist.list[r1].PCom_material);
		Gotoxy(44, 23);
		printf("5.�ɹ���ҵ�����۸� %.2f", allPComslist.list[r1].PCom_price);
		Gotoxy(44, 25);
		printf("6.ǩ����ҵ��Լʱ�䣺 %s", allPComslist.list[r1].in_time);
		Gotoxy(44 - 2, 28);
		printf("ȷ�Ͻ������ҵ������ϵ�� y/n:  ");
		scanf("%s", temp);
		Gotoxy(44 - 2 + 33, 28);
		charRotation();
		Gotoxy(44 - 2, 29);
		if (temp[0] == 'y') {
			int r3 = delPCom(&allPComslist, r1);
			if (r3 == -1) {
				printf("��Լʧ�ܣ��������ҵ��Ϣʧ�ܣ�");
				Sleep(5000);
				productComInterface();
			}
			else {
				printf("��Լ�ɹ����ѳɹ�ɾ������ҵ��Ϣ��");
				Sleep(1000);
				productComInterface();
			}
		}
		//����no�������
		else if (temp[0] == 'n') {
			printf("���ڷ��ع�����壬��ȷ�Ϻ����룡 ");
			charRotation();
			Sleep(5000);
			productComInterface();
		}
		//�������ȥy��n�������ַ��Ļ�
		else {
			printf("��������������ȷ��Ҫ������룡 ");
			charRotation();
			Sleep(5000);
			deleteProductCom();
		}
	}
}

//���ܽ���8���޸���ҵ��Ӧԭ�Ͻ���
void modifiPCom() {
	system("cls");
	frameShow();
	Gotoxy(44 + 3, 5);
	printf("��Ʒ�ɹ���ҵ�޸����");
	char temp[30];
	Gotoxy(43, 8);
	printf("����������Ҫ�޸ĵ���ҵ��ţ�");
	scanf("%s", temp);
	Gotoxy(43 + 31.5, 8);
	charRotation();
	int r1 = searchPCom(allPComslist, temp);
	int r2 = 0, r3 = 0;
	//��������ֲ���ʧ�ܵ����
	if (r1 < 0) {
		Gotoxy(44, 10);
		printf("��ѯ��ҵʧ�ܣ�ȷ�Ϻ�����  ");
		charRotation();
		modifiPCom();
	}
	else {
		Gotoxy(43, 10);
		printf("����ȷ����Ҫ�޸ĵ���ҵ��Ϣ��");
		Gotoxy(44, 12);
		printf("1.��Ʒ�ɹ���ҵ��ţ� %s", allPComslist.list[r1].PCom_id);
		Gotoxy(44, 14);
		printf("2.��Ʒ�ɹ���ҵ���ƣ� %s", allPComslist.list[r1].PCom_name);
		Gotoxy(44, 16);
		printf("3.�ɹ���ҵ�����ڵأ� %s", allPComslist.list[r1].PCom_location);
		Gotoxy(44, 18);
		printf("4.�ɹ���ҵ������Ʒ�� %s", allPComslist.list[r1].PCom_material);
		Gotoxy(44, 20);
		printf("5.�ɹ���ҵ�����۸� %.2f", allPComslist.list[r1].PCom_price);
		Gotoxy(44, 22);
		printf("6.ǩ����ҵ��Լʱ�䣺 %s", allPComslist.list[r1].in_time);
		while (1) {
			Gotoxy(44 - 2, 24);
			printf("ѡ��Ҫ�޸ĵ����ݱ�ţ� ");
			char temp[30];
			scanf("%s", temp);
			r2 = atoi(temp);
			//����ı���ڷ�Χ֮�ڵģ�1~6��
			if (r2 >= 1 && r2 <= 6) {
				char newContent[50];
				Gotoxy(44 - 2, 26);
				printf("���޸Ĳ��ֵ�������Ϊ�� ");
				scanf("%s", newContent);
				r3 = modifyPCom(&allPComslist, r1, r2, newContent);
				if (r3 == -1) {
					Gotoxy(44 - 2, 28);
					printf("�޸���ҵ��Ϣʧ�ܣ�  ");
					charRotation();
					Sleep(5000);
					productComInterface();
				}
				else {
					Gotoxy(44 - 2, 28);
					printf("ѡ���޸���ҵ��Ϣ�ɹ��� ");
					charRotation();
					Sleep(3000);
					productComInterface();
				}
				break;
			}
			//����ı�Ų��ڷ�Χ�ڵ�
			else {
				Gotoxy(44 - 2, 26);
				printf("�������ѡ���Ŵ��� ");
				charRotation();
				Sleep(5000);
				productComInterface();
			}
		}
	}
}

//���ܽ���9����ѯ�ɹ���ҵ��Ϣ����
void queryPCom() {
	system("cls");
	frameShow();
	Gotoxy(22 + 1.5, 8);
	printf("��Ʒ�ɹ���ҵ��ѯ���");
	Gotoxy(22, 10);
	printf("����ȷ�ϲ�ѯ��ҵ��Ϣ�ķ�ʽ��");
	int choice, r2;
	while (1) {
		Gotoxy(22, 12);
		printf("1.��Ʒ�ɹ���ҵ���");
		Gotoxy(22, 14);
		printf("2.��Ʒ�ɹ���ҵ����");
		Gotoxy(22, 16);
		printf("3.�ɹ���ҵ�����ڵ�");
		Gotoxy(22, 18);
		printf("4.�ɹ���ҵ������Ʒ");
		Gotoxy(22, 20);
		printf("5.��ʾ���вɹ���ҵ");
		Gotoxy(22, 22);
		printf("6.������ҵ�������");
		Gotoxy(22, 25);
		printf("�������ѯ��ʽ�ı�ţ� ");
		char temp[80];
		scanf("%s", temp);
		Gotoxy(22 + 23 + 2, 25);//����
		charRotation();
		choice = atoi(temp);
		switch (choice) {
			//����Ĳ�ѯ��ʽΪ1ʱ����ʱ��ѯ��ʽΪ��ҵ���
			case 1: {
				char content[50];
				Gotoxy(22, 27);
				printf("��������Ҫ��ѯ�����ݣ� ");
				scanf("%s", content);
				Gotoxy(22 + 20 + 5, 27);
				charRotation();
				r2 = searchPCom(allPComslist, content);
				if (r2 < 0) {
					Gotoxy(22 + 20 + 10, 27);
					printf("��ѯ����ʧ�ܣ�ȷ�Ϻ�����  ");
					charRotation();
					queryPCom();
				}
				else {
					Gotoxy(58 + 22 - 16, 10);
					printf("1.��Ʒ�ɹ���ҵ��ţ� %s", allPComslist.list[r2].PCom_id);
					Gotoxy(58 + 22 - 16, 12);
					printf("2.��Ʒ�ɹ���ҵ���ƣ� %s", allPComslist.list[r2].PCom_name);
					Gotoxy(58 + 22 - 16, 14);
					printf("3.�ɹ���ҵ�����ڵأ� %s", allPComslist.list[r2].PCom_location);
					Gotoxy(58 + 22 - 16, 16);
					printf("4.�ɹ���ҵ������Ʒ�� %s", allPComslist.list[r2].PCom_material);
					Gotoxy(58 + 22 - 16, 18);
					printf("5.�ɹ���Ʒ��ҵ�۸� %.2f", allPComslist.list[r2].PCom_price);
					Gotoxy(58 + 22 - 16, 20);
					printf("6.ǩ����ҵ��Լʱ�䣺 %s", allPComslist.list[r2].in_time);
					Gotoxy(58 + 22 - 16, 24);
					printf("�鿴�����������y������һ�㣺 ");
					scanf("%s", temp);
					if (temp[0] == 'y') {
						Gotoxy(58 + 22 + 16 * 2 + 1.5 - 16 + 1, 24);
						charRotation();
						Sleep(1000);
						queryPCom();
					}
					else {
						Gotoxy(58 + 22 + 16 * 2 + 1.5 - 16 + 1, 24);
						printf("��������Ϊ����������� ");
						charRotation();
						Sleep(1000);
						productComInterface();
					}
				}
				break;
			}
			//����Ĳ�ѯ��ʽΪ2ʱ����ʱ��ѯ��ʽΪ��ҵ����
			case 2: {
				char content[50];
				Gotoxy(22, 27);
				printf("��������Ҫ��ѯ�����ݣ� ");
				scanf("%s", content);
				Gotoxy(22 + 23 + 28, 27);
				charRotation();
				IntSeqList result;
				intListInit(&result, 5);
				searchPComByOthers(allPComslist, content, choice, &result);
				if (result.length == 0) {
					errorTemplate(48, "û��������������ҵ��Ϣ��");
					queryPCom();
				}
				//����ɹ��ҵ��ж�Ӧ��ֵ
				else {
					system("cls");
					frameShow();
					Gotoxy(6, 4);
					printf("��ҵ���               ��ҵ����             ��ҵ���ڵ�    ��ҵ�ɹ���Ʒ      �ɹ���Ʒ�۸�       ��ҵǩԼʱ��");
					for (int i = 0; i < result.length; i++) {
						Gotoxy(8, 8 + i);
						printf("%s         %s    %s     %s         %.2f           %s", allPComslist.list[result.list[i]].PCom_id, allPComslist.list[result.list[i]].PCom_name, allPComslist.list[result.list[i]].PCom_location, allPComslist.list[result.list[i]].PCom_material, allPComslist.list[result.list[i]].PCom_price, allPComslist.list[result.list[i]].in_time);
					}
					//�����˳��Ľӿ�
					char yes[3];
					Gotoxy((117 - 16 * 2) / 2, 28);
					printf("�鿴�����������y������һ�㣺 ");
					scanf("%s", yes);
					if (yes[0] == 'y') {
						Gotoxy((117 - 16 * 2) / 2 + 16 * 2 + 2, 28);
						charRotation();
						Sleep(1000);
						queryPCom();
					}
					//������������
					else {
						Gotoxy(58 + 22, 28);
						printf("��������Ϊ����������� ");
						charRotation();
						Sleep(1000);
						productComInterface();
					}
				}
				errorTemplate(48, "û��������������ҵ��Ϣ��");
				productComInterface();
				break;
			}
			//����Ĳ�ѯ��ʽΪ3ʱ����ʱ��ѯ��ʽΪ��ҵ�ص�
			case 3: {
				char content[50];
				Gotoxy(22, 27);
				printf("��������Ҫ��ѯ�����ݣ� ");
				scanf("%s", content);
				Gotoxy(22 + 23 + 28 - 15, 27);
				charRotation();
				IntSeqList result;
				intListInit(&result, 5);
				searchPComByOthers(allPComslist, content, choice, &result);
				if (result.length == 0) {
					errorTemplate(48, "û��������������ҵ��Ϣ��");
					queryPCom();
				}
				//����ɹ��ҵ��ж�Ӧ��ֵ
				else {
					system("cls");
					frameShow();
					Gotoxy(6, 4);
					printf("��ҵ���               ��ҵ����             ��ҵ���ڵ�    ��ҵ�ɹ���Ʒ      �ɹ���Ʒ�۸�       ��ҵǩԼʱ��");
					for (int i = 0; i < result.length; i++) {
						Gotoxy(8 + 0.5, 8 + i * 1.5);
						printf("%s         %s    %s     %s         %.2f           %s", allPComslist.list[result.list[i]].PCom_id, allPComslist.list[result.list[i]].PCom_name, allPComslist.list[result.list[i]].PCom_location, allPComslist.list[result.list[i]].PCom_material, allPComslist.list[result.list[i]].PCom_price, allPComslist.list[result.list[i]].in_time);
					}
					//�����˳��Ľӿ�
					char yes[3];
					Gotoxy((117 - 16 * 2) / 2, 28);
					printf("�鿴�����������y������һ�㣺 ");
					scanf("%s", yes);
					if (yes[0] == 'y') {
						Gotoxy((117 - 16 * 2) / 2 + 16 * 2 + 2, 28);
						charRotation();
						Sleep(1000);
						queryPCom();
					}
					//������������
					else {
						Gotoxy(58 + 22, 28);
						printf("��������Ϊ����������� ");
						charRotation();
						Sleep(1000);
						productComInterface();
					}
				}
				errorTemplate(48, "û��������������ҵ��Ϣ��");
				productComInterface();
				break;
			}
			//����Ĳ�ѯ��ʽΪ4ʱ����ʱ��ѯ��ʽΪ��ҵ�ṩԭ��
			case 4: {
				char content[50];
				Gotoxy(22, 27);
				printf("��������Ҫ��ѯ�����ݣ� ");
				scanf("%s", content);
				Gotoxy(22 + 23 + 28 - 15, 27);
				charRotation();
				IntSeqList result;
				intListInit(&result, 5);
				searchMComByOthers(allMComslist, content, choice, &result);
				if (result.length == 0) {
					errorTemplate(48, "û��������������ҵ��Ϣ��");
					queryPCom();
				}
				//����ɹ��ҵ��ж�Ӧ��ֵ
				else {
					system("cls");
					frameShow();
					Gotoxy(6, 4);
					printf("��ҵ���               ��ҵ����             ��ҵ���ڵ�    ��ҵ�ɹ���Ʒ      �ɹ���Ʒ�۸�       ��ҵǩԼʱ��");
					for (int i = 0; i < result.length; i++) {
						Gotoxy(8 + 0.5, 8 + i * 1.5);
						printf("%s         %s    %s     %s         %.2f           %s", allPComslist.list[result.list[i]].PCom_id, allPComslist.list[result.list[i]].PCom_name, allPComslist.list[result.list[i]].PCom_location, allPComslist.list[result.list[i]].PCom_material, allPComslist.list[result.list[i]].PCom_price, allPComslist.list[result.list[i]].in_time);
					}
					//�����˳��Ľӿ�
					char yes[3];
					Gotoxy((117 - 16 * 2) / 2, 28);
					printf("�鿴�����������y������һ�㣺 ");
					scanf("%s", yes);
					if (yes[0] == 'y') {
						Gotoxy((117 - 16 * 2) / 2 + 16 * 2 + 2, 28);
						charRotation();
						Sleep(1000);
						queryPCom();
					}
					//������������
					else {
						Gotoxy(58 + 22, 28);
						printf("��������Ϊ����������� ");
						charRotation();
						Sleep(1000);
						productComInterface();
					}
				}
				errorTemplate(48, "û��������������ҵ��Ϣ��");
				productComInterface();
				break;
			}
			//����Ĳ�ѯ��ʽΪ5ʱ����ʱ��ѯ��ʽΪ��ʾ������ҵ
			case 5: {
				if (allPComslist.length == 0) {
					errorTemplate(48, "������ҵ��Ϣ���ݿ�Ϊ�գ�");
					queryPCom();
				}
				system("cls");
				frameShow();
				Gotoxy(6, 4);
				printf("��ҵ���               ��ҵ����             ��ҵ���ڵ�    ��ҵ�ɹ���Ʒ      �ɹ���Ʒ�۸�       ��ҵǩԼʱ��");
				for (int i = 0; i < allPComslist.length; i++) {
					Gotoxy(8 + 0.5, 8 + i * 1.5);
					printf("%s         %s    %s     %s         %.2f           %s", allPComslist.list[i].PCom_id, allPComslist.list[i].PCom_name, allPComslist.list[i].PCom_location, allPComslist.list[i].PCom_material, allPComslist.list[i].PCom_price, allPComslist.list[i].in_time);
				}
				//�����˳��Ľӿ�
				char yes[3];
				Gotoxy((117 - 16 * 2) / 2, 28);
				printf("�鿴�����������y������һ�㣺 ");
				scanf("%s", yes);
				if (yes[0] == 'y') {
					Gotoxy((117 - 16 * 2) / 2 + 16 * 2 + 2, 28);
					charRotation();
					Sleep(1000);
					queryPCom();
				}
				//������������
				else {
					Gotoxy(58 + 22, 28);
					printf("��������Ϊ����������� ");
					charRotation();
					Sleep(1000);
					productComInterface();
				}
			}
			//����Ĳ�ѯ��ʽΪ6ʱ����ʱ�˳���ѯ��ҵ���
			case 6: {
				errorTemplate(48.5, "���ڷ�����ҵ������壡");
				productComInterface();
			}
		    //errorTemplate(48, "û��������������ҵ��Ϣ��");
			//productComInterface();
			//break;
		    //������Ĳ�ѯ��ʽ���ڷ�Χ�ڵ�ʱ�򣬻�ִ��defult
			default: {
				errorTemplate(48, "����Ĳ�ѯ��ʽ�������");
				queryPCom();
			}
		}
	}
}

//���ܽ���10������ɹ���ҵ��Ϣ����
void savePCom() {
	int r1 = allSave(2);
	if (r1 == -1) {
		errorTemplate(48, "���浱ǰ����ҵ��Ϣʧ�ܣ�");
		productComInterface();
	}
	else {
		errorTemplate(48, "���ڱ������е���ҵ��Ϣ��");
		errorTemplate(48, "�������е���ҵ��Ϣ�ɹ���");
		productComInterface();
	}
}

//��Ϲ��ܽ���1�����ܺ���--����ԭ���Ϲ�Ӧ��ҵ
int addNewMCom(MComsSeqList* mcsl, MComInfo newMCom) {

	//������ԭ�Ϲ�Ӧ��ҵ���в����Ƿ��д���ҵ������У����� - 1����ʾǩԼʧ��
	int r = searchMCom(*mcsl, newMCom.MCom_id);
	if (r >= 0) {
		errorTemplate(48, "��ԭ�Ϲ�Ӧ��ҵ��Ŵ��ڣ�");
		materialComInterface();
	}
	//��������ռ䲻����������ռ�
	if (mcsl->length >= mcsl->size) {
		MComInfo* t = mcsl->list;
		mcsl->list = (MComInfo*)malloc(2 * mcsl->size * sizeof(MComInfo));
		if (mcsl->list == NULL) {
			errorTemplate(48, "������Ч���ڴ����ʧ�ܣ�");
			materialComInterface();
		}
		mcsl->size = 2 * mcsl->size;
		for (int i = 0; i < mcsl->length; i++)
			MComCopy(&(mcsl->list[i]), t[i]);
		free(t);
	}
	//	��ԭ�Ϲ�Ӧ������ҵ��Ų��뵽���ʵ�λ�ã���֤��ԭ�Ϲ�Ӧ��ҵ�������
	int i = 0;
	for (i = mcsl->length - 1; i >= 0; i--) {
		r = strcmp(mcsl->list[i].MCom_id, newMCom.MCom_id);
		if (r > 0)
			MComCopy(&(mcsl->list[i + 1]), mcsl->list[i]);
		else
			break;

	}
	MComCopy(&(mcsl->list[i + 1]), newMCom);
	mcsl->length++;
	//��ӳɹ�����0
	return 0;

}

//��Ϲ��ܽ���1�����ܺ���--�����²�Ʒ�ɹ���ҵ
int addNewPCom(PComsSeqList* pcsl, PComInfo newPCom) {

	//�����ڲ�Ʒ�ɹ���ҵ���в����Ƿ��д���ҵ������У����� - 1����ʾǩԼʧ��
	int r = searchPCom(*pcsl, newPCom.PCom_id);
	if (r >= 0) {
		errorTemplate(48, "�˲�Ʒ�ɹ���ҵ��Ŵ��ڣ�");
		productComInterface();
	}
	//��������ռ䲻����������ռ�
	if (pcsl->length >= pcsl->size) {
		PComInfo* t = pcsl->list;
		pcsl->list = (PComInfo*)malloc(2 * pcsl->size * sizeof(PComInfo));
		if (pcsl->list == NULL) {
			errorTemplate(48, "������Ч���ڴ����ʧ�ܣ�");
			productComInterface();
		}
		pcsl->size = 2 * pcsl->size;
		for (int i = 0; i < pcsl->length; i++)
			PComCopy(&(pcsl->list[i]), t[i]);
		free(t);
	}
	//	��ԭ�Ϲ�Ӧ������ҵ��Ų��뵽���ʵ�λ�ã���֤��ԭ�Ϲ�Ӧ��ҵ�������
	int i = 0;
	for (i = pcsl->length - 1; i >= 0; i--) {
		r = strcmp(pcsl->list[i].PCom_id, newPCom.PCom_id);
		if (r > 0)
			PComCopy(&(pcsl->list[i + 1]), pcsl->list[i]);
		else
			break;

	}
	PComCopy(&(pcsl->list[i + 1]), newPCom);
	pcsl->length++;
	//��ӳɹ�����0
	return 0;
}

//��Ϲ��ܽ���123�����ܺ���--��ԭ�Ϲ�Ӧ��ҵ���и���ǩԼ��ҵ��Ž��в��ң�û�д���ҵ�򷵻�-1������з���ֵ���Ǹ�ԭ�Ϲ�Ӧ��ҵ�ı�ţ������㷨�ö��ֲ��ҷ���
int searchMCom(MComsSeqList mcsl, char* MCsn) {		//(���õ��� ���ֲ��ҷ�)
	int low = 0;
	int high = mcsl.length - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;		//���ֲ��ҷ�
		if (strcmp(mcsl.list[mid].MCom_id, MCsn) == 0)
			return mid;
		else
			if (strcmp(mcsl.list[mid].MCom_id, MCsn) < 0)
				low = mid + 1;
			else
				high = mid - 1;
	}
	return -1;
}

//��Ϲ��ܽ���123�����ܺ���--�ڲ�Ʒ�ɹ���ҵ���и���ǩԼ��ҵ��Ž��в��ң�û�д���ҵ�򷵻�-1������з���ֵ���Ǹò�Ʒ�ɹ���ҵ�ı�ţ������㷨�ò�ֵ���ҷ���
int searchMComByInterpolationSearch(MComsSeqList mcsl, char* MCsn) {
	int low, high, mid;
	low = 0;
	high = mcsl.length - 1;
	int key = atoi(MCsn);
	while (low <= high) {
		int MComHigh = atoi(mcsl.list[high].MCom_id);
		int MComLow = atoi(mcsl.list[low].MCom_id);
		mid = low + (high - low)*(key - MComLow) / (MComHigh - MComLow);  //��ֵ���ҷ�
		if (strcmp(mcsl.list[mid].MCom_id, MCsn) == 0) return mid;
		else
			if (strcmp(mcsl.list[mid].MCom_id, MCsn) < 0) low = mid + 1;
			else high = mid - 1;
	}
	return -1;
}

/*
//��Ϲ��ܽ���123�����ܺ���--��ԭ�Ϲ�Ӧ��ҵ���и���ǩԼ��ҵ��Ž��в��ң�û�д���ҵ�򷵻�-1������з���ֵ���Ǹ�ԭ�Ϲ�Ӧ��ҵ�ı��
int searchMComByFibonacciSearch(MComsSeqList mcsl, char* MCsn) {//()
//�޷�ʹ�õ�쳲���������	
}
*/

//��Ϲ��ܽ���123�����ܺ���--�ڲ�Ʒ�ɹ���ҵ���и���ǩԼ��ҵ��Ž��в��ң�û�д���ҵ�򷵻�-1������з���ֵ���Ǹò�Ʒ�ɹ���ҵ�ı�ţ������㷨�ö��ֲ��ҷ���
int searchPCom(PComsSeqList pcsl, char* PCsn) {		
	int low = 0;
	int high = pcsl.length - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;		//���ֲ��ҷ�
		if (strcmp(pcsl.list[mid].PCom_id, PCsn) == 0)
			return mid;
		else
			if (strcmp(pcsl.list[mid].PCom_id, PCsn) < 0)
				low = mid + 1;
			else
				high = mid - 1;
	}
	return -1;
}

//��Ϲ��ܽ���123�����ܺ���--�ڲ�Ʒ�ɹ���ҵ���и���ǩԼ��ҵ��Ž��в��ң�û�д���ҵ�򷵻�-1������з���ֵ���Ǹò�Ʒ�ɹ���ҵ�ı�ţ������㷨�ò�ֵ���ҷ���
int searchPComByInterpolationSearch(PComsSeqList pcsl, char* PCsn) {		
	int low, high, mid;
	low = 0;
	high = pcsl.length - 1;
	int key = atoi(PCsn);
	while (low <= high) {
		int PComHigh = atoi(pcsl.list[high].PCom_id);
		int PComLow = atoi(pcsl.list[low].PCom_id);
		mid = low + (high - low)*(key - PComLow) / (PComHigh - PComLow);  //��ֵ���ҷ�
		if (strcmp(pcsl.list[mid].PCom_id, PCsn) == 0) return mid;
		else
			if (strcmp(pcsl.list[mid].PCom_id, PCsn) < 0) low = mid + 1;
			else high = mid - 1;
	}
	return -1;
}

//��Ϲ��ܽ���123�����ܺ���--��ȿ�������ԭ�Ϲ�Ӧ��ҵ
void MComCopy(MComInfo* to, MComInfo from) {
	strcpy(to->MCom_id, from.MCom_id);
	strcpy(to->MCom_name, from.MCom_name);
	strcpy(to->MCom_location, from.MCom_location);
	strcpy(to->MCom_material, from.MCom_material);
	to->MCom_price = from.MCom_price;
	strcpy(to->in_time, from.in_time);
}

//��Ϲ��ܽ���123�����ܺ���--��ȿ���������Ʒ�ɹ���ҵ
void PComCopy(PComInfo* to, PComInfo from) {
	strcpy(to->PCom_id, from.PCom_id);
	strcpy(to->PCom_name, from.PCom_name);
	strcpy(to->PCom_location, from.PCom_location);
	strcpy(to->PCom_material, from.PCom_material);
	to->PCom_price = from.PCom_price;
	strcpy(to->in_time, from.in_time);
}

//��Ϲ��ܽ���2�����ܺ���--��ԭ�Ϲ�Ӧ��ҵ����ɾ����index��Ԫ�أ�ɾ���㷨Ϊ�Ѻ��������Ԫ�ظ���ǰ�棬����0��ʾɾ���ɹ�
int delMCom(MComsSeqList* mcsl, int index) {
	if (mcsl->length <= 0) {
		errorTemplate(48, "��Ӧ��ҵ���ݿ���ϢΪ�գ�");
		materialComInterface();
		return -1;
	}
	if (index < 0 || index >= mcsl->length) {
		errorTemplate(47, "�������ҵ��Ϣ����ִ�з�Χ��");
		materialComInterface();
		return -1;
	}

	for (int i = index + 1; i < mcsl->length; i++) {
		MComCopy(&(mcsl->list[i - 1]), mcsl->list[i]);
	}
	mcsl->length--;
	return 0;
}

//��Ϲ��ܽ���2�����ܺ���--�ڲ�Ʒ�ɹ���ҵ����ɾ����index��Ԫ�أ�ɾ���㷨Ϊ�Ѻ��������Ԫ�ظ���ǰ�棬����0��ʾɾ���ɹ�
int delPCom(PComsSeqList* pcsl, int index) {
	if (pcsl->length <= 0) {
		errorTemplate(48, "�ɹ���ҵ���ݿ���ϢΪ�գ�");
		productComInterface();
		return -1;
	}
	if (index < 0 || index >= pcsl->length) {
		errorTemplate(47, "�������ҵ��Ϣ����ִ�з�Χ��");
		productComInterface();
		return -1;
	}

	for (int i = index + 1; i < pcsl->length; i++) {
		PComCopy(&(pcsl->list[i - 1]), pcsl->list[i]);
	}
	pcsl->length--;
	return 0;
}

//��Ϲ��ܽ���3�����ܺ�������ԭ�Ϲ�Ӧ��ҵ��mcsl���޸ĵ�index����ҵ����Ϣ��type��ʾҪ�޸ĵ����ͣ�ȡֵ1����ҵ��ţ���2����ҵ���ƣ���3����ҵ���ڵأ���4����ҵ���ṩ��Ʒ������info��ʾ�µ���Ϣֵ���޸ĳɹ�����0�����򷵻�1
int modifyMCom(MComsSeqList* mcsl, int index, int type, char* info) {
	if (index < 0 && index >= mcsl->length) {
		errorTemplate(47, "�������ҵ��Ϣ����ִ�з�Χ��");
		materialComInterface();
	}
	switch (type) {
		case 1: strcpy(mcsl->list[index].MCom_id, info); break;
		case 2: strcpy(mcsl->list[index].MCom_name, info); break;
		case 3: strcpy(mcsl->list[index].MCom_location, info); break;
		case 4: strcpy(mcsl->list[index].MCom_material, info); break;
		case 5: mcsl->list[index].MCom_price = atof(info); break;
		case 6: strcpy(mcsl->list[index].in_time, info); break;
		default: {
			errorTemplate(48, "�޸ĵ���ҵ��Ϣ�������");
			materialComInterface();
		}	
	}
	return 0;
}

//��Ϲ��ܽ���3�����ܺ������ڲ�Ʒ�ɹ���ҵ��mcsl���޸ĵ�index����ҵ����Ϣ��type��ʾҪ�޸ĵ����ͣ�ȡֵ1����ҵ��ţ���2����ҵ���ƣ���3����ҵ���ڵأ���4����ҵ���ṩ��Ʒ������info��ʾ�µ���Ϣֵ���޸ĳɹ�����0�����򷵻�1
int modifyPCom(PComsSeqList* pcsl, int index, int type, char* info) {
	if (index < 0 && index >= pcsl->length) {
		errorTemplate(47, "�������ҵ��Ϣ����ִ�з�Χ��");
		productComInterface();
	}
	switch (type) {
		case 1: strcpy(pcsl->list[index].PCom_id, info); break;
		case 2: strcpy(pcsl->list[index].PCom_name, info); break;
		case 3: strcpy(pcsl->list[index].PCom_location, info); break;
		case 4: strcpy(pcsl->list[index].PCom_material, info); break;
		case 5: pcsl->list[index].PCom_price = atof(info); break;
		case 6: strcpy(pcsl->list[index].in_time, info); break;
		default: {
			errorTemplate(48, "�޸ĵ���ҵ��Ϣ�������");
			productComInterface();
		}
	}
	return 0;
}

//��Ϲ��ܽ���4�����ܺ���--�����ṩԭ�ϵ���ҵ��Ϣ��tpyeȡֵ1����ҵ���ƣ���2����ҵ���ڵأ���3����ҵ�ṩԭ�ϣ�����ѯ��ؼ�¼����ҵ��Ϣ��
//               ���û���ҵ����򷵻� - 1������У���ѯ�����һ��IntSeqList�б��أ��б�װ������ҵ��˳����е����
int searchMComByOthers(MComsSeqList mcsl, char* info, int type, IntSeqList* mcindex) {
	for (int i = 0; i < mcsl.length; i++) {
		switch (type-1) {
			//�������ѡ��Ϊ2ʱ��typeֵ��ӦΪ1����ִ�а���ԭ����ҵ���Ʋ�ѯ���ַ���
			case 1: if (strcmp(mcsl.list[i].MCom_name, info) == 0)
				addInt(mcindex, i);
				break;
			//�������ѡ��Ϊ3ʱ��typeֵ��ӦΪ2����ִ�а���ԭ����ҵ�ص�Ĳ�ѯ���ַ���
			case 2: if (strcmp(mcsl.list[i].MCom_location, info) == 0)
				addInt(mcindex, i);
				break;
			//�������ѡ��Ϊ4ʱ��typeֵ��ӦΪ3����ִ�а���ԭ����ҵ���ṩ��ԭ����Ϣ�Ĳ�ѯ�ַ���
			case 3: if (strcmp(mcsl.list[i].MCom_material, info) == 0)
				addInt(mcindex, i);
				break;
			default: {
				errorTemplate(47.5, "��ѯ��ҵ��Ϣ��ʽ�������");
				materialComInterface();
			}
		}
	}
	return 0;
}

//��Ϲ��ܽ���4�����ܺ���--���ݲɹ���Ʒ����ҵ��Ϣ��tpyeȡֵ1����ҵ���ƣ���2����ҵ���ڵأ���3����ҵ������Ʒ������ѯ��ؼ�¼����ҵ��Ϣ��
//               ���û���ҵ����򷵻� - 1������У���ѯ�����һ��IntSeqList�б��أ��б�װ������ҵ��˳����е����
int searchPComByOthers(PComsSeqList pcsl, char* info, int type, IntSeqList* pcindex) {
	for (int i = 0; i < pcsl.length; i++) {
		switch (type - 1) {
			//�������ѡ��Ϊ2ʱ��typeֵ��ӦΪ1����ִ�а��ղɹ���ҵ���Ʋ�ѯ���ַ���
			case 1: if (strcmp(pcsl.list[i].PCom_name, info) == 0)
				addInt(pcindex, i);
				break;
				//�������ѡ��Ϊ3ʱ��typeֵ��ӦΪ2����ִ�а��ղɹ���ҵ�ص�Ĳ�ѯ���ַ���
			case 2: if (strcmp(pcsl.list[i].PCom_location, info) == 0)
				addInt(pcindex, i);
				break;
				//�������ѡ��Ϊ4ʱ��typeֵ��ӦΪ3����ִ�а��ղɹ���ҵ�������Ĳ�Ʒ��Ϣ�Ĳ�ѯ�ַ���
			case 3: if (strcmp(pcsl.list[i].PCom_material, info) == 0)
				addInt(pcindex, i);
				break;
			default: {
				errorTemplate(47.5, "��ѯ��ҵ��Ϣ��ʽ�������");
				productComInterface();
			}
		}
	}
	return 0;
}

//��Ϲ��ܽ���5�����ܺ���--������ϵͳ������ɾ�����ĺ����Ϣ�������ݿ���
int allMComsInfoSaveToFile(MComsSeqList mcsl, char* filename) {
	FILE *fp;
	char strline[80];						   
	if ((fp = fopen(filename, "w")) == NULL) { 
		errorTemplate(48, "��Ӧ��ҵ�����ݿⲻ���ڣ�");
		materialComInterface();
	}

	for (int i = 0; i < mcsl.length; i++) {
		fputs(mcsl.list[i].MCom_id, fp);
		fputc('\n', fp);
		fputs(mcsl.list[i].MCom_name, fp);
		fputc('\n', fp);
		fputs(mcsl.list[i].MCom_location, fp);
		fputc('\n', fp);
		fputs(mcsl.list[i].MCom_material, fp);
		fputc('\n', fp);
		sprintf(strline, "%.2f", mcsl.list[i].MCom_price);
		fputs(strline, fp);
		fputc('\n', fp);
		fputs(mcsl.list[i].in_time, fp);
		fputc('\n', fp);
	}
	fclose(fp);
	return 0;
}

//��Ϲ��ܽ���5�����ܺ���--������ϵͳ������ɾ�����ĺ����Ϣ�������ݿ���
int allPComsInfoSaveToFile(PComsSeqList pcsl, char* filename) {
	FILE *fp;
	char strline[80];
	if ((fp = fopen(filename, "w")) == NULL) {
		errorTemplate(48, "�ɹ���ҵ�����ݿⲻ���ڣ�");
		productComInterface();
	}
	for (int i = 0; i < pcsl.length; i++) {
		fputs(pcsl.list[i].PCom_id, fp);
		fputc('\n', fp);
		fputs(pcsl.list[i].PCom_name, fp);
		fputc('\n', fp);
		fputs(pcsl.list[i].PCom_location, fp);
		fputc('\n', fp);
		fputs(pcsl.list[i].PCom_material, fp);
		fputc('\n', fp);
		sprintf(strline, "%.2f", pcsl.list[i].PCom_price);
		fputs(strline, fp);
		fputc('\n', fp);
		fputs(pcsl.list[i].in_time, fp);
		fputc('\n', fp);
	}
	fclose(fp);
	return 0;
}

//��ͨ�ã���Ϲ��ܽ���5�����ܺ���--�����ͱ��������Ϣ���ļ���
int allSave(int type) {
	switch (type) {
		//��typeֵȡ1��ʱ��˵����Ҫ�������ҵ��ϢΪ�����Ĺ�Ӧ��ҵ����Ϣ
		case 1: {
			int r1 = allMComsInfoSaveToFile(allMComslist, "�����Ĺ�Ӧ��ҵ��Ϣ���ݿ�.txt");  //�������еĹ�Ӧ��ҵ��Ϣ���ļ���
			if (r1 == -1) {
				errorTemplate(48, "���浱ǰ����ҵ��Ϣʧ�ܣ�");
				materialComInterface();
			}
			return 0;
		}
		//��typeֵȡ2��ʱ��˵����Ҫ�������ҵ��ϢΪ�����Ĳɹ���ҵ����Ϣ
		case 2: {
			int r1 = allPComsInfoSaveToFile(allPComslist, "�����Ĳɹ���ҵ��Ϣ���ݿ�.txt");  //�������еĺ�����ҵ��Ϣ���ļ���
			if (r1 == -1) {
				errorTemplate(48, "���浱ǰ����ҵ��Ϣʧ�ܣ�");
				productComInterface();
			}
			return 0;
		}
		default: {
			errorTemplate(47, "ѡ�����󣬱���ʧ�ܣ�");
			adminLeaderInterface();
		}
	}

}

//δ���Ե�ð�������㷨
void BubbleSortPrice(MComsSeqList *mcsl) {
	int i, j;
	for (i = 1; i < mcsl->length;i++) {
		for (j = mcsl->length - 1; j >= i; j++) {
			if (mcsl->list[j].MCom_price > mcsl->list[j + 1].MCom_price) {
				MySwap(mcsl, j, j + 1);		//��������ֵ
			}
		}
	}
}

void MySwap(MComsSeqList* mcsl, int x, int y) {
	char temp= "";
	temp = mcsl->list[x].MCom_id;
	memset(mcsl->list[x].MCom_id, 0, sizeof(mcsl->list[x].MCom_id));
	strcpy(mcsl->list[x].MCom_id, mcsl->list[y].MCom_id);
	memset(mcsl->list[y].MCom_id, 0, sizeof(mcsl->list[y].MCom_id));
	strcpy(mcsl->list[y].MCom_id, temp);
}