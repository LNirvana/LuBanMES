#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>
#include"MES-WarehouseKeeper.h"
#include"Globals.h"
#include"MES-Leader.h"

#define _CRT_SECURE_NO_DEPRECATE��
#define _CRT_SECURE_NO_WARNINGS��
#pragma warning(disable:4996)��

extern MWaresSeqList allMWareslist;

/*----------------------�ִ�ԭ����Ϣ�������ݽṹ�ӿ�----------------------*/
//���ݽṹ����1��MWare����-��ʼ������� mwsl��size��ʾ��ʼ������
void MWaresSeqListInit(MWaresSeqList* mwsl, int size);
//���ݽṹ����2��MWare����--���ݿ���Ϣ��ʼ��
int allMWaresInfoReadFromFile(MWaresSeqList* mwsl, char* filename);

/*----------------------����ӿڼ���----------------------*/
//����1���ִ������Ϣ�������
void wareInterface();

/*----------------------�������ӿڼ���----------------------*/
//���ܽ���1������ԭ�����������
void addMaterial();
//���ܽ���2���ִ�ԭ�ϳ���������
void deleteMaterial();
//���ܽ���3���޸Ĳִ����ԭ�Ͻ���
void modifiMWare();
//���ܽ���4����ѯ�ִ����ԭ����Ϣ����
void queryMWare();
//���ܽ���5������ִ�������Ϣ����
void saveMWare();

/*----------------------���ܺ����ӿڼ���----------------------*/
//��Ϲ��ܽ���1�����ܺ���--����ԭ�������Ǽ���Ϣ
int addNewMWare(MWaresSeqList* mwsl, MWareInfo newMWare);
//��Ϲ��ܽ���123�����ܺ���--��ԭ�����ǼǱ��Լ�����и��ݵǼ�ԭ�ϱ�Ž��в��ң�û�иñ����ռ�ÿ���򷵻�-1������з���ֵ���ǸõǼǱ���ѱ�ռ�ã������㷨�ö��ֲ��ҷ���
int searchMWare(MWaresSeqList mwsl, char* MWsn);
//��Ϲ��ܽ���123�����ܺ���--��ȿ����������ԭ�ϵǼ���Ϣ
void MWareCopy(MWareInfo* to, MWareInfo from);
//��Ϲ��ܽ���2�����ܺ���--��ԭ�ϲִ��������ɾ����index��Ԫ�أ�ɾ���㷨Ϊ�Ѻ��������Ԫ�ظ���ǰ�棬����0��ʾɾ���ɹ�
int delMWare(MWaresSeqList* mwsl, int index);
//��Ϲ��ܽ���3�����ܺ������ڲִ������mwsl���޸ĵ�index��ԭ�����ε���Ϣ��type��ʾҪ�޸ĵ����ͣ�ȡֵ1��ԭ�ϵǼǱ�ţ���2��ԭ�ϵǼ����ƣ���3����Ӧԭ�����ڵأ���4����Ӧԭ����ҵ���ƣ�����info��ʾ�µ���Ϣֵ���޸ĳɹ�����0�����򷵻�1
int modifyMWare(MWaresSeqList* mwsl, int index, int type, char* info);
//��Ϲ��ܽ���4�����ܺ���--���ݲִ�ԭ�ϵ�������Ϣ��tpyeȡֵ1��ԭ�ϵǼ����ƣ���2����Ӧԭ�����ڵأ���3����Ӧԭ����ҵ���ƣ�����ѯ��ؼ�¼�Ĳִ������Ϣ��
//               ���û���ҵ����򷵻� - 1������У���ѯ�����һ��IntSeqList�б��أ��б�װ����ԭ���ڲִ�˳����е����
int searchMWareByOthers(MWaresSeqList mwsl, char* info, int type, IntSeqList* mwindex);
//��Ϲ��ܽ���5�����ܺ���--������ϵͳ������ɾ�����ĺ����Ϣ�������ݿ���
int allMWaresInfoSaveToFile(MWaresSeqList mwsl, char* filename);
//��Ϲ��ܽ���5�����ܺ���--�����ͱ���ִ���Ϣ���ļ���
int allSaveWare();

//����ӿں���������Աר���ڲ�ѯ�ִ����ԭ����Ϣ����
void queryMWareAdmin();


/*----------------------�ִ�ԭ����Ϣ�������ݽṹ�ӿ�----------------------*/
//���ݽṹ����1��MWare����-��ʼ������� mwsl��size��ʾ��ʼ������
void MWaresSeqListInit(MWaresSeqList* mwsl, int size) {
	mwsl->list = (MWareInfo*)malloc(size * sizeof(MWareInfo));
	mwsl->size = size;
	mwsl->length = 0;
}

//���ݽṹ����2��MWare����--���ݿ���Ϣ��ʼ��
int allMWaresInfoReadFromFile(MWaresSeqList* mwsl, char* filename) {
	FILE *fp;
	char strline[80];             //ÿ������ȡ���ַ���
	if ((fp = fopen(filename, "r")) == NULL) { //�ж��ļ��Ƿ���ڼ��ɶ�
		errorTemplate(48, "���� MES���ݿ���Ϣ����");
		return -1;
	}
	MWareInfo newMWare;
	while (!feof(fp)) {
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newMWare.MWare_id, strline);
		else {
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newMWare.MWare_name, strline);
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newMWare.MWare_location, strline);
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newMWare.MWare_company, strline);
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			newMWare.MWare_num = atof(strline);
		}
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			strcpy(newMWare.in_time, strline);
		}
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		addNewMWare(mwsl, newMWare);
	}
	fclose(fp);//�ر��ļ�
	return 0;
}

/*----------------------����ӿڼ���----------------------*/
//����1���ִ������Ϣ�������
void wareInterface() {	//�洢���ϵ���ҵ��Ϣ�������
	int choice;
	system("cls");
	frameShow();
	Gotoxy(44 + 5,7);
	printf("�ִ������Ϣ�������");
	Gotoxy(44 + 3, 10);		
	printf("1.�� �� ԭ �� �� �� �� Ϣ");
	Gotoxy(44 + 3, 12);
	printf("2.�� �� ԭ �� �� �� �� Ϣ");
	Gotoxy(44 + 3, 14);
	printf("3.�� �� ԭ �� �� Ϣ �� ��");
	Gotoxy(44 + 3, 16);
	printf("4.�� �� ԭ �� �� Ϣ �� ѯ");
	Gotoxy(44 + 3, 18);
	printf("5.�� �� �� �� ԭ �� �� Ϣ");
	Gotoxy(44 + 3, 20);
	printf("6.�� �� �� �� ԭ �� �� ��");
	Gotoxy(44 + 3, 24);
	printf("����������Ҫ�����ı��룺 ");
	scanf("%d", &choice);
	Gotoxy(44 + 3 +12*2 + 3, 24);
	charRotation();
	switch (choice) {
		case 1: {
			addMaterial();
		}
		case 2: {
			deleteMaterial();
		}
		case 3: {
			modifiMWare();
		}
		case 4: {
			queryMWare();
		}
		case 5: {
			saveMWare();
		}
		case 6: {
			errorTemplate(47.5, "�����˳��ִ���������壡");
			exitMES(2);
		}
		default: {
			errorTemplate(47.5, "�������������������룡");
			wareInterface();
		}
	}
}

/*----------------------�������ӿڼ���----------------------*/
//���ܽ���1������ԭ�����������
void addMaterial() {
	system("cls");
	frameShow();
	char temp[80];//��Ϊ�۸�Ľ���ֵ
	MWareInfo newMWare;
	Gotoxy(44 + 5, 9);
	printf("�ִ�����ԭ��������");
	Gotoxy(44, 12);
	printf("1.ԭ���������ţ�");
	Gotoxy(44 + 20 + 4, 12);
	scanf("%s", newMWare.MWare_id);
	Gotoxy(44, 14);
	printf("2.ԭ�����Ǽ����ƣ�");
	Gotoxy(44 + 20 + 4, 14);
	scanf("%s", newMWare.MWare_name);
	Gotoxy(44, 16);
	printf("3.���ԭ�ϲ��ر�ע��");
	Gotoxy(44 + 20 + 4, 16);
	scanf("%s", newMWare.MWare_location);
	Gotoxy(44, 18);
	printf("4.ԭ�Ϲ�Ӧ��ҵ�Ǽǣ�");
	Gotoxy(44 + 20 + 4, 18);
	scanf("%s", newMWare.MWare_company);
	Gotoxy(44, 20);
	printf("5.����ԭ�����������");
	Gotoxy(44 + 20 + 4, 20);
	scanf("%s", temp);
	newMWare.MWare_num = atof(temp);
	getTimeNow(newMWare.in_time);
	Gotoxy(44 - 3, 24);
	printf("ȷ�Ͻ�������ԭ�ϵǼ����? y/n ��  ");
	int r1;
	scanf("%s", temp);
	Gotoxy(44 - 3, 26);
	if (temp[0] == 'y') {
		r1 = addNewMWare(&allMWareslist, newMWare);
		if (r1 == -1) {
			printf("���ԭ��ʧ�ܣ�����õǼ���Ϣ��  ");
			charRotation();
			wareInterface();
		}
		else {
			printf("���Ǽǳɹ����ɹ����ԭ����Ϣ��  ");
			charRotation();
			wareInterface();
		}
	}
	//����no�������
	else if (temp[0] == 'n') {
		printf("���ڷ��زִ���壬��ȷ�Ϻ����룡 ");
		charRotation();
		Sleep(5000);
		wareInterface();
	}
	//�������ȥy��n�������ַ��Ļ�
	else {
		printf("��������������ȷ��Ҫ������룡 ");
		charRotation();
		Sleep(5000);
		addMaterial();
	}
}

//���ܽ���2���ִ�ԭ�ϳ���������
void deleteMaterial() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(44 + 3, 8);
	printf("�ִ�����ԭ�ϳ������");
	Gotoxy(43, 11);
	printf("����������Ҫ�����ԭ�ϱ�ţ�");
	scanf("%s", temp);
	Gotoxy(43 + 32, 11);
	charRotation();
	int r1 = searchMWare(allMWareslist, temp);
	//��������ֲ���ʧ�ܵ����
	if (r1 < 0) {
		Gotoxy(44, 13);
		printf("��ѯԭ��ʧ�ܣ�ȷ�Ϻ�����  ");
		charRotation();
		deleteMaterial();
	}
	else {
		Gotoxy(43, 13);
		printf("����ȷ����Ҫ�����ԭ����Ϣ��");
		Gotoxy(44, 15);
		printf("1.ԭ���������ţ� %s", allMWareslist.list[r1].MWare_id);
		Gotoxy(44, 17);
		printf("2.ԭ�����Ǽ����ƣ� %s", allMWareslist.list[r1].MWare_name);
		Gotoxy(44, 19);
		printf("3.���ԭ�ϲ��ر�ע�� %s", allMWareslist.list[r1].MWare_location);
		Gotoxy(44, 21);
		printf("4.ԭ�Ϲ�Ӧ��ҵ�Ǽǣ� %s", allMWareslist.list[r1].MWare_company);
		Gotoxy(44, 23);
		printf("5.����ԭ����������� %.2f", allMWareslist.list[r1].MWare_num);
		Gotoxy(44, 25);
		printf("6.ԭ�����Ǽ�ʱ�䣺 %s", allMWareslist.list[r1].in_time);
		Gotoxy(44 - 2, 28);
		printf("ȷ�Ͻ�������ԭ�ϳ����� y/n:  ");
		scanf("%s", temp);
		Gotoxy(44 - 2 + 33, 28);
		charRotation();
		Gotoxy(44 - 2, 29);
		if (temp[0] == 'y') {
			int r3 = delMWare(&allMWareslist, r1);
			if (r3 == -1) {
				printf("����ʧ�ܣ��޷������������Ϣ��");
				Sleep(5000);
				wareInterface();
			}
			else {
				printf("����ɹ�����������޸�������Ϣ��");
				Sleep(1000);
				wareInterface();
			}
		}
		//����no�������
		else if (temp[0] == 'n') {
			printf("���ڷ��زִ���壬��ȷ�Ϻ����룡 ");
			charRotation();
			Sleep(3000);
			wareInterface();
		}
		//�������ȥy��n�������ַ��Ļ�
		else {
			printf("��������������ȷ��Ҫ������룡 ");
			charRotation();
			Sleep(3000);
			deleteMaterial();
		}
	}
}

//���ܽ���3���޸Ĳִ����ԭ�Ͻ���
void modifiMWare() {
	system("cls");
	frameShow();
	Gotoxy(44 + 3, 5);
	printf("�ִ�����ԭ���޸����");
	char temp[30];
	Gotoxy(43, 8);
	printf("����������Ҫ�޸ĵ�ԭ�ϱ�ţ�");
	scanf("%s", temp);
	Gotoxy(43 + 32, 8);
	charRotation();
	int r1 = searchMWare(allMWareslist, temp);
	int r2 = 0, r3 = 0;
	//��������ֲ���ʧ�ܵ����
	if (r1 < 0) {
		Gotoxy(44, 10);
		printf("��ѯԭ��ʧ�ܣ�ȷ�Ϻ�����  ");
		charRotation();
		wareInterface();
	}
	else {
		Gotoxy(43, 10);
		printf("����ȷ����Ҫ�޸ĵ�ԭ����Ϣ��");
		Gotoxy(44, 12);
		printf("1.ԭ���������ţ� %s", allMWareslist.list[r1].MWare_id);
		Gotoxy(44, 14);
		printf("2.ԭ�����Ǽ����ƣ� %s", allMWareslist.list[r1].MWare_name);
		Gotoxy(44, 16);
		printf("3.���ԭ�ϲ��ر�ע�� %s", allMWareslist.list[r1].MWare_location);
		Gotoxy(44, 18);
		printf("4.ԭ�Ϲ�Ӧ��ҵ�Ǽǣ� %s", allMWareslist.list[r1].MWare_company);
		Gotoxy(44, 20);
		printf("5.����ԭ����������� %.2f", allMWareslist.list[r1].MWare_num);
		Gotoxy(44, 22);
		printf("6.ԭ�����Ǽ�ʱ�䣺 %s", allMWareslist.list[r1].in_time);
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
				r3 = modifyMWare(&allMWareslist, r1, r2, newContent);
				if (r3 == -1) {
					Gotoxy(44 - 2, 28);
					printf("�޸�ԭ����Ϣʧ�ܣ�  ");
					charRotation();
					Sleep(5000);
					wareInterface();
				}
				else {
					Gotoxy(44 - 2, 28);
					printf("ѡ���޸�ԭ����Ϣ�ɹ��� ");
					charRotation();
					Sleep(3000);
					wareInterface();
				}
				break;
			}
			//����ı�Ų��ڷ�Χ�ڵ�
			else {
				Gotoxy(44 - 2, 26);
				printf("�������ѡ���Ŵ��� ");
				charRotation();
				Sleep(5000);
				wareInterface();
			}
		}
	}

}

//���ܽ���4����ѯ�ִ����ԭ����Ϣ����
void queryMWare() {
	system("cls");
	frameShow();
	Gotoxy(22 + 2, 8);
	printf("�ִ�����ԭ�ϲ�ѯ���");
	Gotoxy(22, 10);
	printf("����ȷ�ϲ�ѯԭ����Ϣ�ķ�ʽ��");
	int choice, r2;
	while (1) {
		Gotoxy(22, 12);
		printf("1.ԭ����������");
		Gotoxy(22, 14);
		printf("2.ԭ�����Ǽ�����");
		Gotoxy(22, 16);
		printf("3.���ԭ�ϲ��ر�ע");
		Gotoxy(22, 18);
		printf("4.ԭ�Ϲ�Ӧ��ҵ�Ǽ�");
		Gotoxy(22, 20);
		printf("5.��ʾ���вִ�ԭ��");
		Gotoxy(22, 22);
		printf("6.���زִ��������");
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
			r2 = searchMWare(allMWareslist, content);
			if (r2 < 0) {
				Gotoxy(22 + 20 + 10, 27);
				printf("��ѯ����ʧ�ܣ�ȷ�Ϻ�����  ");
				charRotation();
				queryMWare();
			}
			else {
				Gotoxy(58 + 22 - 16, 10);
				printf("1.ԭ���������ţ� %s", allMWareslist.list[r2].MWare_id);
				Gotoxy(58 + 22 - 16, 12);
				printf("2.ԭ�����Ǽ����ƣ� %s", allMWareslist.list[r2].MWare_name);
				Gotoxy(58 + 22 - 16, 14);
				printf("3.���ԭ�ϲ��ر�ע�� %s", allMWareslist.list[r2].MWare_location);
				Gotoxy(58 + 22 - 16, 16);
				printf("4.ԭ�Ϲ�Ӧ��ҵ�Ǽǣ� %s", allMWareslist.list[r2].MWare_company);
				Gotoxy(58 + 22 - 16, 18);
				printf("5.����ԭ����������� %.2f", allMWareslist.list[r2].MWare_num);
				Gotoxy(58 + 22 - 16, 20);
				printf("6.ԭ�����Ǽ�ʱ�䣺 %s", allMWareslist.list[r2].in_time);
				Gotoxy(58 + 22 - 16, 24);
				printf("�鿴�����������y������һ�㣺 ");
				scanf("%s", temp);
				if (temp[0] == 'y') {
					Gotoxy(58 + 22 + 16 * 2 + 2 - 16 + 1, 24);
					charRotation();
					Sleep(1000);
					queryMWare();
				}
				else {
					Gotoxy(58 + 22 + 16 * 2 + 2 - 16 + 1, 24);
					printf("��������Ϊ����������� ");
					charRotation();
					Sleep(1000);
					wareInterface();
				}
			}
			break;
		}
		//����Ĳ�ѯ��ʽΪ2ʱ����ʱ��ѯ��ʽΪԭ������
		case 2: {
			char content[50];
			Gotoxy(22, 27);
			printf("��������Ҫ��ѯ�����ݣ� ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 8, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchMWareByOthers(allMWareslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "û�����������Ĳִ���Ϣ��");
				queryMWare();
			}
			//����ɹ��ҵ��ж�Ӧ��ֵ
			else {
				system("cls");
				frameShow();
				//����һ��
				Gotoxy(6, 4);
				printf("ԭ�ϱ��     ԭ������      ԭ����Դ��              ��Ӧԭ����ҵ         �ִ�ԭ������       ԭ�����ʱ��");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8 , 8 + i);
					printf(" %s        %s           %s       %s    %.2f          %s", allMWareslist.list[result.list[i]].MWare_id, allMWareslist.list[result.list[i]].MWare_name, allMWareslist.list[result.list[i]].MWare_location, allMWareslist.list[result.list[i]].MWare_company, allMWareslist.list[result.list[i]].MWare_num, allMWareslist.list[result.list[i]].in_time);
				}
				//�����˳��Ľӿ�
				char yes[3];
				Gotoxy(43, 28);
				printf("�鿴�����������y������һ�㣺 ");
				scanf("%s", yes);
				if (yes[0] == 'y') {
					Gotoxy(43 + 16 * 2 + 2, 28);
					charRotation();
					Sleep(1000);
					queryMWare();
				}
				//������������
				else {
					Gotoxy(58 + 22, 28);
					printf("��������Ϊ����������� ");
					charRotation();
					Sleep(1000);
					wareInterface();
				}
			}
			errorTemplate(48, "û�����������Ĳִ���Ϣ��");
			wareInterface();
			break;
		}
				//����Ĳ�ѯ��ʽΪ3ʱ����ʱ��ѯ��ʽΪԭ�ϵ���Դ��
		case 3: {
			char content[50];
			Gotoxy(22, 27);
			printf("��������Ҫ��ѯ�����ݣ� ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 28 - 15, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchMWareByOthers(allMWareslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "û�����������Ĳִ���Ϣ��");
				queryMWare();
			}
			//����ɹ��ҵ��ж�Ӧ��ֵ
			else {
				system("cls");
				frameShow();
				//����һ��
				Gotoxy(6, 4);
				printf("ԭ�ϱ��     ԭ������      ԭ����Դ��              ��Ӧԭ����ҵ         �ִ�ԭ������       ԭ�����ʱ��");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8 , 8 + i );
					printf(" %s        %s           %s       %s    %.2f          %s", allMWareslist.list[result.list[i]].MWare_id, allMWareslist.list[result.list[i]].MWare_name, allMWareslist.list[result.list[i]].MWare_location, allMWareslist.list[result.list[i]].MWare_company, allMWareslist.list[result.list[i]].MWare_num, allMWareslist.list[result.list[i]].in_time);
				}
				//�����˳��Ľӿ�
				char yes[3];
				Gotoxy(43, 28);
				printf("�鿴�����������y������һ�㣺 ");
				scanf("%s", yes);
				if (yes[0] == 'y') {
					Gotoxy(43 + 16 * 2 + 2, 28);
					charRotation();
					Sleep(1000);
					queryMWare();
				}
				//������������
				else {
					Gotoxy(58 + 22, 28);
					printf("��������Ϊ����������� ");
					charRotation();
					Sleep(1000);
					wareInterface();
				}
			}
			errorTemplate(48, "û�����������Ŀ����Ϣ��");
			wareInterface();
			break;
		}
		//����Ĳ�ѯ��ʽΪ4ʱ����ʱ��ѯ��ʽΪ�ṩԭ�ϵ���ҵ����
		case 4: {
			char content[50];
			Gotoxy(22, 27);
			printf("��������Ҫ��ѯ�����ݣ� ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 29, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchMWareByOthers(allMWareslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "û�����������Ĳִ���Ϣ��");
				queryMWare();
			}
			//����ɹ��ҵ��ж�Ӧ��ֵ
			else {
				system("cls");
				frameShow();
				//����һ��
				Gotoxy(6, 4);
				printf("ԭ�ϱ��     ԭ������      ԭ����Դ��              ��Ӧԭ����ҵ         �ִ�ԭ������       ԭ�����ʱ��");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8, 8 + i );
					printf(" %s        %s           %s       %s    %.2f          %s", allMWareslist.list[result.list[i]].MWare_id, allMWareslist.list[result.list[i]].MWare_name, allMWareslist.list[result.list[i]].MWare_location, allMWareslist.list[result.list[i]].MWare_company, allMWareslist.list[result.list[i]].MWare_num, allMWareslist.list[result.list[i]].in_time);
				}
				//�����˳��Ľӿ�
				char yes[3];
				Gotoxy(43, 28);
				printf("�鿴�����������y������һ�㣺 ");
				scanf("%s", yes);
				if (yes[0] == 'y') {
					Gotoxy(43 + 16 * 2 + 2, 28);
					charRotation();
					Sleep(1000);
					queryMWare();
				}
				//������������
				else {
					Gotoxy(58 + 22, 28);
					printf("��������Ϊ����������� ");
					charRotation();
					Sleep(1000);
					wareInterface();
				}
			}
			errorTemplate(48, "û�����������Ĳִ���Ϣ��");
			wareInterface();
			break;
		}
		//����Ĳ�ѯ��ʽΪ4ʱ����ʱ��ѯ��ʽΪ��ʾ������ҵ
		case 5: {
			if (allMWareslist.length == 0) {
				errorTemplate(48, "�ִ�������Ϣ���ݿ�Ϊ�գ�");
				queryMWare();
			}
			system("cls");
			frameShow();
			//����һ��
			Gotoxy(6, 4);
			printf("ԭ�ϱ��     ԭ������      ԭ����Դ��              ��Ӧԭ����ҵ         �ִ�ԭ������       ԭ�����ʱ��");
			for (int i = 0; i < allMWareslist.length; i++) {
				Gotoxy(8, 8 + i );
				printf(" %s        %s           %s       %s    %.2f          %s", allMWareslist.list[i].MWare_id, allMWareslist.list[i].MWare_name, allMWareslist.list[i].MWare_location, allMWareslist.list[i].MWare_company, allMWareslist.list[i].MWare_num, allMWareslist.list[i].in_time);
			}
			//�����˳��Ľӿ�
			char yes[3];
			Gotoxy(43, 28);
			printf("�鿴�����������y������һ�㣺 ");
			scanf("%s", yes);
			if (yes[0] == 'y') {
				Gotoxy(43 + 16 * 2 + 2, 28);
				charRotation();
				Sleep(1000);
				queryMWare();
			}
			//������������
			else {
				Gotoxy(58 + 22, 28);
				printf("��������Ϊ����������� ");
				charRotation();
				Sleep(1000);
				wareInterface();
			}
		}
		//����Ĳ�ѯ��ʽΪ6ʱ����ʱ�˳���ѯ��ҵ���
		case 6: {
			errorTemplate(49, "���ڷ��زִ�������壡");
			wareInterface();
		}
		default: {
			errorTemplate(48, "����Ĳ�ѯ��ʽ�������");
			queryMWare();
		}
		}
	}
}

//���ܽ���5�����湩Ӧ��ҵ��Ϣ����
void saveMWare() {
	int r1 = allSaveWare();
	if (r1 == -1) {
		errorTemplate(48, "���浱ǰ�Ĳִ���Ϣʧ�ܣ�");
		wareInterface();
	}
	else {
		errorTemplate(48, "���ڱ������еĲִ���Ϣ��");
		errorTemplate(48, "�������еĲִ���Ϣ�ɹ���");
		wareInterface();
	}
}

//��Ϲ��ܽ���1�����ܺ���--����ԭ�������Ǽ���Ϣ
int addNewMWare(MWaresSeqList* mwsl, MWareInfo newMWare) {

	//�����ڲִ���������Ϣ�в����Ƿ��д�ԭ�ϵĿ�棬����У����� - 1����ʾ���Ǽ�ʧ��
	int r = searchMWare(*mwsl, newMWare.MWare_id);
	if (r >= 0) {
		errorTemplate(48, "ԭ�����ǼǱ���Ѵ��ڣ�");
		wareInterface();
	}
	//��������ռ䲻����������ռ�
	if (mwsl->length >= mwsl->size) {
		MWareInfo* t = mwsl->list;
		mwsl->list = (MWareInfo*)malloc(2 * mwsl->size * sizeof(MWareInfo));
		if (mwsl->list == NULL) {
			errorTemplate(48, "������Ч���ڴ����ʧ�ܣ�");
			wareInterface();
		}
		mwsl->size = 2 * mwsl->size;
		for (int i = 0; i < mwsl->length; i++)
			MWareCopy(&(mwsl->list[i]), t[i]);
		free(t);
	}
	//	��ԭ�����ǼǱ�Ų��뵽���ʵ�λ�ã���֤��ԭ�Ϲ�Ӧ��ҵ�������
	int i = 0;
	for (i = mwsl->length - 1; i >= 0; i--) {
		r = strcmp(mwsl->list[i].MWare_id, newMWare.MWare_id);
		if (r > 0)
			MWareCopy(&(mwsl->list[i + 1]), mwsl->list[i]);
		else
			break;

	}
	MWareCopy(&(mwsl->list[i + 1]), newMWare);
	mwsl->length++;
	//��ӳɹ�����0
	return 0;
}

//��Ϲ��ܽ���123�����ܺ���--��ԭ�����ǼǱ��Լ�����и��ݵǼ�ԭ�ϱ�Ž��в��ң�û�иñ����ռ�ÿ���򷵻�-1������з���ֵ���ǸõǼǱ���ѱ�ռ�ã������㷨�ö��ֲ��ҷ���
int searchMWare(MWaresSeqList mwsl, char* MWsn) {		//����������������һ����mcsl��һ����MWsn
	int low = 0;
	int high = mwsl.length - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;		//���ֲ��ҷ�
		if (strcmp(mwsl.list[mid].MWare_id, MWsn) == 0)
			return mid;
		else
			if (strcmp(mwsl.list[mid].MWare_id, MWsn) < 0)
				low = mid + 1;
			else
				high = mid - 1;
	}
	return -1;
}

//��Ϲ��ܽ���123�����ܺ���--��ȿ����������ԭ�ϵǼ���Ϣ
void MWareCopy(MWareInfo* to, MWareInfo from) {
	strcpy(to->MWare_id, from.MWare_id);
	strcpy(to->MWare_name, from.MWare_name);
	strcpy(to->MWare_location, from.MWare_location);
	strcpy(to->MWare_company, from.MWare_company);
	to->MWare_num = from.MWare_num;
	strcpy(to->in_time, from.in_time);
}

//��Ϲ��ܽ���2�����ܺ���--��ԭ�ϲִ��������ɾ����index��Ԫ�أ�ɾ���㷨Ϊ�Ѻ��������Ԫ�ظ���ǰ�棬����0��ʾɾ���ɹ�
int delMWare(MWaresSeqList* mwsl, int index) {
	if (mwsl->length <= 0) {
		errorTemplate(48, "�ִ��������ݿ���ϢΪ�գ�");
		wareInterface();
		return -1;
	}
	if (index < 0 || index >= mwsl->length) {
		errorTemplate(47, "��Ҫ�����ԭ�ϳ���ִ�з�Χ��");
		wareInterface();
		return -1;
	}

	for (int i = index + 1; i < mwsl->length; i++) {
		MWareCopy(&(mwsl->list[i - 1]), mwsl->list[i]);
	}
	mwsl->length--;
	return 0;
}

//��Ϲ��ܽ���3�����ܺ������ڲִ������mwsl���޸ĵ�index��ԭ�����ε���Ϣ��type��ʾҪ�޸ĵ����ͣ�ȡֵ1��ԭ�ϵǼǱ�ţ���2��ԭ�ϵǼ����ƣ���3����Ӧԭ�����ڵأ���4����Ӧԭ����ҵ���ƣ�����info��ʾ�µ���Ϣֵ���޸ĳɹ�����0�����򷵻�1
int modifyMWare(MWaresSeqList* mwsl, int index, int type, char* info) {
	if (index < 0 && index >= mwsl->length) {
		errorTemplate(47, "��Ҫ�����ԭ�ϳ���ִ�з�Χ��");
		wareInterface();
	}
	switch (type) {
		case 1: strcpy(mwsl->list[index].MWare_id, info); break;
		case 2: strcpy(mwsl->list[index].MWare_name, info); break;
		case 3: strcpy(mwsl->list[index].MWare_location, info); break;
		case 4: strcpy(mwsl->list[index].MWare_company, info); break;
		case 5: mwsl->list[index].MWare_num = atof(info); break;
		case 6: strcpy(mwsl->list[index].in_time, info); break;
		default: {
			errorTemplate(48, "�޸ĵ�ԭ����Ϣ�������");
			wareInterface();
		}
	}
	return 0;
}

//��Ϲ��ܽ���4�����ܺ���--���ݲִ�ԭ�ϵ�������Ϣ��tpyeȡֵ1��ԭ�ϵǼ����ƣ���2����Ӧԭ�����ڵأ���3����Ӧԭ����ҵ���ƣ�����ѯ��ؼ�¼�Ĳִ������Ϣ��
//               ���û���ҵ����򷵻� - 1������У���ѯ�����һ��IntSeqList�б��أ��б�װ����ԭ���ڲִ�˳����е����
int searchMWareByOthers(MWaresSeqList mwsl, char* info, int type, IntSeqList* mwindex) {
	for (int i = 0; i < mwsl.length; i++) {
		switch (type - 1) {
			//�������ѡ��Ϊ2ʱ��typeֵ��ӦΪ1����ִ�а���ԭ�ϵǼ����Ʋ�ѯ���ַ���
			case 1: if (strcmp(mwsl.list[i].MWare_name, info) == 0)
				addInt(mwindex, i);
				break;
			//�������ѡ��Ϊ3ʱ��typeֵ��ӦΪ2����ִ�а��չ�Ӧԭ�����ڵصĲ�ѯ���ַ���
			case 2: if (strcmp(mwsl.list[i].MWare_location, info) == 0)
				addInt(mwindex, i);
				break;
			//�������ѡ��Ϊ4ʱ��typeֵ��ӦΪ3����ִ�а��չ�Ӧԭ����ҵ���ƵĲ�ѯ�ַ���
			case 3: if (strcmp(mwsl.list[i].MWare_company, info) == 0)
				addInt(mwindex, i);
				break;
			default: {
				errorTemplate(47.5, "��ѯ�����Ϣ��ʽ�������");
				wareInterface();
			}
		}
	}
	return 0;
}

//��Ϲ��ܽ���5�����ܺ���--������ϵͳ������ɾ�����ĺ����Ϣ�������ݿ���
int allMWaresInfoSaveToFile(MWaresSeqList mwsl, char* filename) {
	FILE *fp;
	char strline[80];
	if ((fp = fopen(filename, "w")) == NULL) {
		errorTemplate(48, "�ִ���������ݿⲻ���ڣ�");
		wareInterface();
	}

	for (int i = 0; i < mwsl.length; i++) {
		fputs(mwsl.list[i].MWare_id, fp);
		fputc('\n', fp);
		fputs(mwsl.list[i].MWare_name, fp);
		fputc('\n', fp);
		fputs(mwsl.list[i].MWare_location, fp);
		fputc('\n', fp);
		fputs(mwsl.list[i].MWare_company, fp);
		fputc('\n', fp);
		sprintf(strline, "%.2f", mwsl.list[i].MWare_num);
		fputs(strline, fp);
		fputc('\n', fp);
		fputs(mwsl.list[i].in_time, fp);
		fputc('\n', fp);
	}
	fclose(fp);
	return 0;
}

//��Ϲ��ܽ���5�����ܺ���--�����ͱ���ִ���Ϣ���ļ���
int allSaveWare() {
	int r1 = allMWaresInfoSaveToFile(allMWareslist, "�ִ�������Ϣ���ݿ�.txt");  //�������еĲִ���Ϣ���ļ���
	if (r1 == -1) {
		errorTemplate(48, "���浱ǰ�Ĳִ���Ϣʧ�ܣ�");
		wareInterface();
	}
	return 0;
}

//����ӿں���������Աר���ڲ�ѯ�ִ����ԭ����Ϣ����
void queryMWareAdmin() {
	system("cls");
	frameShow();
	Gotoxy(22 + 2, 8);
	printf("�ִ�����ԭ�ϲ�ѯ���");
	Gotoxy(22, 10);
	printf("����ȷ�ϲ�ѯԭ����Ϣ�ķ�ʽ��");
	int choice, r2;
	while (1) {
		Gotoxy(22, 12);
		printf("1.ԭ����������");
		Gotoxy(22, 14);
		printf("2.ԭ�����Ǽ�����");
		Gotoxy(22, 16);
		printf("3.���ԭ�ϲ��ر�ע");
		Gotoxy(22, 18);
		printf("4.ԭ�Ϲ�Ӧ��ҵ�Ǽ�");
		Gotoxy(22, 20);
		printf("5.��ʾ���вִ�ԭ��");
		Gotoxy(22, 22);
		printf("6.���ع���Ա�����");
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
			r2 = searchMWare(allMWareslist, content);
			if (r2 < 0) {
				Gotoxy(22 + 20 + 10, 27);
				printf("��ѯ����ʧ�ܣ�ȷ�Ϻ�����  ");
				charRotation();
				queryMWare();
			}
			else {
				Gotoxy(58 + 22 - 16, 10);
				printf("1.ԭ���������ţ� %s", allMWareslist.list[r2].MWare_id);
				Gotoxy(58 + 22 - 16, 12);
				printf("2.ԭ�����Ǽ����ƣ� %s", allMWareslist.list[r2].MWare_name);
				Gotoxy(58 + 22 - 16, 14);
				printf("3.���ԭ�ϲ��ر�ע�� %s", allMWareslist.list[r2].MWare_location);
				Gotoxy(58 + 22 - 16, 16);
				printf("4.ԭ�Ϲ�Ӧ��ҵ�Ǽǣ� %s", allMWareslist.list[r2].MWare_company);
				Gotoxy(58 + 22 - 16, 18);
				printf("5.����ԭ����������� %.2f", allMWareslist.list[r2].MWare_num);
				Gotoxy(58 + 22 - 16, 20);
				printf("6.ԭ�����Ǽ�ʱ�䣺 %s", allMWareslist.list[r2].in_time);
				Gotoxy(58 + 22 - 16, 24);
				printf("�鿴�����������y������һ�㣺 ");
				scanf("%s", temp);
				if (temp[0] == 'y') {
					Gotoxy(58 + 22 + 16 * 2 + 2 - 16 + 1, 24);
					charRotation();
					Sleep(1000);
					queryMWare();
				}
				else {
					Gotoxy(58 + 22 + 16 * 2 + 2 - 16 + 1, 24);
					printf("��������Ϊ����������� ");
					charRotation();
					Sleep(1000);
					adminLeaderInterface();
				}
			}
			break;
		}
				//����Ĳ�ѯ��ʽΪ2ʱ����ʱ��ѯ��ʽΪԭ������
		case 2: {
			char content[50];
			Gotoxy(22, 27);
			printf("��������Ҫ��ѯ�����ݣ� ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 8, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchMWareByOthers(allMWareslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "û�����������Ĳִ���Ϣ��");
				queryMWare();
			}
			//����ɹ��ҵ��ж�Ӧ��ֵ
			else {
				system("cls");
				frameShow();
				//����һ��
				Gotoxy(6, 4);
				printf("ԭ�ϱ��     ԭ������      ԭ����Դ��              ��Ӧԭ����ҵ         �ִ�ԭ������       ԭ�����ʱ��");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8, 8 + i);
					printf(" %s        %s           %s       %s    %.2f          %s", allMWareslist.list[result.list[i]].MWare_id, allMWareslist.list[result.list[i]].MWare_name, allMWareslist.list[result.list[i]].MWare_location, allMWareslist.list[result.list[i]].MWare_company, allMWareslist.list[result.list[i]].MWare_num, allMWareslist.list[result.list[i]].in_time);
				}
				//�����˳��Ľӿ�
				char yes[3];
				Gotoxy(43, 28);
				printf("�鿴�����������y������һ�㣺 ");
				scanf("%s", yes);
				if (yes[0] == 'y') {
					Gotoxy(43 + 16 * 2 + 2, 28);
					charRotation();
					Sleep(1000);
					queryMWare();
				}
				//������������
				else {
					Gotoxy(58 + 22, 28);
					printf("��������Ϊ����������� ");
					charRotation();
					Sleep(1000);
					adminLeaderInterface();
				}
			}
			errorTemplate(48, "û�����������Ĳִ���Ϣ��");
			adminLeaderInterface();
			break;
		}
				//����Ĳ�ѯ��ʽΪ3ʱ����ʱ��ѯ��ʽΪԭ�ϵ���Դ��
		case 3: {
			char content[50];
			Gotoxy(22, 27);
			printf("��������Ҫ��ѯ�����ݣ� ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 28 - 15, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchMWareByOthers(allMWareslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "û�����������Ĳִ���Ϣ��");
				queryMWare();
			}
			//����ɹ��ҵ��ж�Ӧ��ֵ
			else {
				system("cls");
				frameShow();
				//����һ��
				Gotoxy(6, 4);
				printf("ԭ�ϱ��     ԭ������      ԭ����Դ��              ��Ӧԭ����ҵ         �ִ�ԭ������       ԭ�����ʱ��");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8, 8 + i);
					printf(" %s        %s           %s       %s    %.2f          %s", allMWareslist.list[result.list[i]].MWare_id, allMWareslist.list[result.list[i]].MWare_name, allMWareslist.list[result.list[i]].MWare_location, allMWareslist.list[result.list[i]].MWare_company, allMWareslist.list[result.list[i]].MWare_num, allMWareslist.list[result.list[i]].in_time);
				}
				//�����˳��Ľӿ�
				char yes[3];
				Gotoxy(43, 28);
				printf("�鿴�����������y������һ�㣺 ");
				scanf("%s", yes);
				if (yes[0] == 'y') {
					Gotoxy(43 + 16 * 2 + 2, 28);
					charRotation();
					Sleep(1000);
					queryMWare();
				}
				//������������
				else {
					Gotoxy(58 + 22, 28);
					printf("��������Ϊ����������� ");
					charRotation();
					Sleep(1000);
					adminLeaderInterface();
				}
			}
			errorTemplate(48, "û�����������Ŀ����Ϣ��");
			adminLeaderInterface();
			break;
		}
				//����Ĳ�ѯ��ʽΪ4ʱ����ʱ��ѯ��ʽΪ�ṩԭ�ϵ���ҵ����
		case 4: {
			char content[50];
			Gotoxy(22, 27);
			printf("��������Ҫ��ѯ�����ݣ� ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 29, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchMWareByOthers(allMWareslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "û�����������Ĳִ���Ϣ��");
				queryMWare();
			}
			//����ɹ��ҵ��ж�Ӧ��ֵ
			else {
				system("cls");
				frameShow();
				//����һ��
				Gotoxy(6, 4);
				printf("ԭ�ϱ��     ԭ������      ԭ����Դ��              ��Ӧԭ����ҵ         �ִ�ԭ������       ԭ�����ʱ��");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8, 8 + i);
					printf(" %s        %s           %s       %s    %.2f          %s", allMWareslist.list[result.list[i]].MWare_id, allMWareslist.list[result.list[i]].MWare_name, allMWareslist.list[result.list[i]].MWare_location, allMWareslist.list[result.list[i]].MWare_company, allMWareslist.list[result.list[i]].MWare_num, allMWareslist.list[result.list[i]].in_time);
				}
				//�����˳��Ľӿ�
				char yes[3];
				Gotoxy(43, 28);
				printf("�鿴�����������y������һ�㣺 ");
				scanf("%s", yes);
				if (yes[0] == 'y') {
					Gotoxy(43 + 16 * 2 + 2, 28);
					charRotation();
					Sleep(1000);
					queryMWare();
				}
				//������������
				else {
					Gotoxy(58 + 22, 28);
					printf("��������Ϊ����������� ");
					charRotation();
					Sleep(1000);
					adminLeaderInterface();
				}
			}
			errorTemplate(48, "û�����������Ĳִ���Ϣ��");
			adminLeaderInterface();
			break;
		}
				//����Ĳ�ѯ��ʽΪ4ʱ����ʱ��ѯ��ʽΪ��ʾ������ҵ
		case 5: {
			if (allMWareslist.length == 0) {
				errorTemplate(48, "�ִ�������Ϣ���ݿ�Ϊ�գ�");
				queryMWare();
			}
			system("cls");
			frameShow();
			//����һ��
			Gotoxy(6, 4);
			printf("ԭ�ϱ��     ԭ������      ԭ����Դ��              ��Ӧԭ����ҵ         �ִ�ԭ������       ԭ�����ʱ��");
			for (int i = 0; i < allMWareslist.length; i++) {
				Gotoxy(8, 8 + i);
				printf(" %s        %s           %s       %s    %.2f          %s", allMWareslist.list[i].MWare_id, allMWareslist.list[i].MWare_name, allMWareslist.list[i].MWare_location, allMWareslist.list[i].MWare_company, allMWareslist.list[i].MWare_num, allMWareslist.list[i].in_time);
			}
			//�����˳��Ľӿ�
			char yes[3];
			Gotoxy(43, 28);
			printf("�鿴�����������y������һ�㣺 ");
			scanf("%s", yes);
			if (yes[0] == 'y') {
				Gotoxy(43 + 16 * 2 + 2, 28);
				charRotation();
				Sleep(1000);
				queryMWare();
			}
			//������������
			else {
				Gotoxy(58 + 22, 28);
				printf("��������Ϊ����������� ");
				charRotation();
				Sleep(1000);
				adminLeaderInterface();
			}
		}
				//����Ĳ�ѯ��ʽΪ6ʱ����ʱ�˳���ѯ��ҵ���
		case 6: {
			errorTemplate(49, "���ڷ��ع���Ա����壡");
			adminLeaderInterface();
		}
		default: {
			errorTemplate(48, "����Ĳ�ѯ��ʽ�������");
			queryMWare();
		}
		}
	}
}