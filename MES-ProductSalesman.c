#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>
#include"Globals.h"
#include"MES-ProductSalesman.h"

#define _CRT_SECURE_NO_DEPRECATE��
#define _CRT_SECURE_NO_WARNINGS��
#pragma warning(disable:4996)��

extern PSalesSeqList allPSaleslist;


/*----------------------�ɹ�������Ϣ�������ݽṹ�ӿ�----------------------*/
//���ݽṹ����1��PSale����-��ʼ������� pssl��size��ʾ��ʼ������
void PSalesSeqListInit(PSalesSeqList* pssl, int size);

//���ݽṹ����2��PSale����--���ݿ���Ϣ��ʼ��
int allPSalesInfoReadFromFile(PSalesSeqList* pssl, char* filename);

/*----------------------����ӿڼ���----------------------*/
//����1���ɹ�������Ϣ�������
void proSalesInterface();

/*----------------------�������ӿڼ���----------------------*/
//���ܽ���1��������Ʒ�����������
void addProduct();

//���ܽ���2��ɾ���ɹ������������
void deleteProduct();

//���ܽ���3���޸Ĳɹ�������Ϣ����
void modifiPSale();

//���ܽ���4����ѯ�ɹ�������Ϣ����
void queryPSale();

//���ܽ���5�������ɹ������������
void deliveryPSale();

//���ܽ���6������ɹ�������Ϣ����
void savePSale();

//��Ϲ��ܽ���1�����ܺ���--���Ӳɹ������Ǽ���Ϣ
int addNewPSale(PSalesSeqList* pssl, PSaleInfo newPSale);

//��Ϲ��ܽ���123�����ܺ���--�ڲɹ������ǼǱ��Լ�����и��ݲɹ�������Ž��в��ң�û�иñ����ռ�ö����򷵻�-1������з���ֵ���ǸõǼǱ���ѱ�ռ�ã������㷨�ö��ֲ��ҷ���
int searchPSale(PSalesSeqList pssl, char* PSsn);

//��Ϲ��ܽ���123�����ܺ���--��ȿ������������Ǽ���Ϣ
void PSaleCopy(PSaleInfo* to, PSaleInfo from);

//��Ϲ��ܽ���2�����ܺ���--�ڶ����������ɾ����index��Ԫ�أ�ɾ���㷨Ϊ�Ѻ��������Ԫ�ظ���ǰ�棬����0��ʾɾ���ɹ�
int delPSale(PSalesSeqList* pssl, int index);

//��Ϲ��ܽ���3�����ܺ������ڶ��������pssl���޸ĵ�index���������ε���Ϣ��type��ʾҪ�޸ĵ����ͣ�ȡֵ1�������ǼǱ�ţ���2�����������Ʒ���ƣ���3����Ӧ��ƷĿ�ĵأ���4���ɹ���Ʒ��ҵ�Ǽ����ƣ�����info��ʾ�µ���Ϣֵ���޸ĳɹ�����0�����򷵻�1
int modifyPSale(PSalesSeqList* pssl, int index, int type, char* info);

//��Ϲ��ܽ���4�����ܺ���--���ݶ�����������Ϣ��tpyeȡֵ1�������Ǽ����ƣ���2����Ӧ��Ʒ����Ŀ�ĵأ���3���ɹ���Ʒ��ҵ���ƣ�����ѯ��ؼ�¼�Ĳɹ�������Ϣ��
//               ���û���ҵ����򷵻� - 1������У���ѯ�����һ��IntSeqList�б��أ��б�װ���Ƕ����ڶ���˳����е����
int searchPSaleByOthers(PSalesSeqList pssl, char* info, int type, IntSeqList* psindex);

//��Ϲ��ܽ���5�����ܺ���--������ϵͳ������ɾ�����ĺ����Ϣ�������ݿ���
int allPSalesInfoSaveToFile(PSalesSeqList pssl, char* filename);

//��Ϲ��ܽ���5�����ܺ���--�����ͱ���ɹ�������Ϣ���ļ���
int allSaveSale();



/*----------------------�ɹ�������Ϣ�������ݽṹ�ӿ�----------------------*/
//���ݽṹ����1��PSale����-��ʼ������� pssl��size��ʾ��ʼ������
void PSalesSeqListInit(PSalesSeqList* pssl, int size) {
	pssl->list = (PSaleInfo*)malloc(size * sizeof(PSaleInfo));
	pssl->size = size;
	pssl->length = 0;
}

//���ݽṹ����2��PSale����--���ݿ���Ϣ��ʼ��
int allPSalesInfoReadFromFile(PSalesSeqList* pssl, char* filename) {
	FILE *fp;
	char strline[80];             //ÿ������ȡ���ַ���
	if ((fp = fopen(filename, "r")) == NULL) { //�ж��ļ��Ƿ���ڼ��ɶ�
		errorTemplate(48, "���� MES���ݿ���Ϣ����");
		return -1;
	}
	PSaleInfo newPSale;
	while (!feof(fp)) {
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newPSale.PSale_id, strline);
		else {
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newPSale.PSale_name, strline);
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newPSale.PSale_destination, strline);
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newPSale.PSale_company, strline);
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			newPSale.PSale_num = atof(strline);
		}
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			strcpy(newPSale.in_time, strline);
		}
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		addNewPSale(pssl, newPSale);
	}
	fclose(fp);//�ر��ļ�
	return 0;
}


/*----------------------����ӿڼ���----------------------*/
//����1���ɹ�������Ϣ�������
void proSalesInterface() {	
	int choice;
	system("cls");
	frameShow();
	Gotoxy(44 + 5, 7);
	printf("�ɹ�������Ϣ�������");
	Gotoxy(44 + 3, 10);		//��̬�ƶ���꣬ͬʱ��ҳ�������꣨48��10����Ϊ��׼�ƶ�����Ĺ��
	printf("1.�� �� �� �� �� �� �� Ϣ");
	Gotoxy(44 + 3, 12);
	printf("2.ɾ �� �� �� �� �� �� Ϣ");
	Gotoxy(44 + 3, 14);
	printf("3.�� �� �� �� �� Ϣ �� ��");
	Gotoxy(44 + 3, 16);
	printf("4.�� �� �� �� �� Ϣ �� ѯ");
	Gotoxy(44 + 3, 18);
	printf("5.�� �� �� �� �� �� �� �� ");
	Gotoxy(44 + 3, 20);
	printf("6.�� �� �� �� �� �� �� Ϣ ");
	Gotoxy(44 + 3, 22);
	printf("7.�� �� �� �� �� �� �� ��");
	Gotoxy(44 + 3, 26);
	printf("����������Ҫ�����ı��룺");
	Gotoxy(44 + 23 + 3, 26);
	scanf("%d", &choice);
	switch (choice) {
		case 1: {
			addProduct();
		}
	
		case 2: {
			deleteProduct();
		}
		case 3: {
			modifiPSale();
		}
		case 4: {
			queryPSale();
		}
		case 5: {
			deliveryPSale();
		}
		case 6: {
			savePSale();
		}
		case 7: {
			errorTemplate(47.5, "�����˳��ִ���������壡");
			exitMES(6);
		}
		default: {
			errorTemplate(47.5, "�������������������룡");
			proSalesInterface();
		}
	}
}

/*----------------------�������ӿڼ���----------------------*/
//���ܽ���1��������Ʒ�����������
void addProduct() {
	system("cls");
	frameShow();
	char temp[80];//��Ϊ�۸�Ľ���ֵ
	PSaleInfo newPSale;
	Gotoxy(44 + 5, 9);
	printf("��Ӳɹ�������Ϣ���");
	Gotoxy(44, 12);
	printf("1.�ɹ����������ţ�");
	Gotoxy(44 + 20 + 4, 12);
	scanf("%s", newPSale.PSale_id);
	Gotoxy(44, 14);
	printf("2.�ɹ�������Ʒ���ƣ�");
	Gotoxy(44 + 20 + 4, 14);
	scanf("%s", newPSale.PSale_name);
	Gotoxy(44, 16);
	printf("3.����������Ŀ�ĵأ�");
	Gotoxy(44 + 20 + 4, 16);
	scanf("%s", newPSale.PSale_destination);
	Gotoxy(44, 18);
	printf("4.�ɹ�������ҵ�Ǽǣ�");
	Gotoxy(44 + 20 + 4, 18);
	scanf("%s", newPSale.PSale_company);
	Gotoxy(44, 20);
	printf("5.�����ɹ���Ʒ������");
	Gotoxy(44 + 20 + 4, 20);
	scanf("%s", temp);
	newPSale.PSale_num = atof(temp);
	getTimeNow(newPSale.in_time);
	Gotoxy(44 - 3, 24);
	printf("ȷ�Ͻ������ζ����ǽ�ϵͳ? y/n ��  ");
	int r1;
	scanf("%s", temp);
	Gotoxy(44 - 3, 26);
	if (temp[0] == 'y') {
		r1 = addNewPSale(&allPSaleslist, newPSale);
		if (r1 == -1) {
			printf("�ǼǶ���ʧ�ܣ�����õǼ���Ϣ��  ");
			charRotation();
			proSalesInterface();
		}
		else {
			printf("�ɹ��Ǽǳɹ����ɹ���Ӷ�����Ϣ��  ");
			charRotation();
			proSalesInterface();
		}
	}
	//����no�������
	else if (temp[0] == 'n') {
		printf("���ڷ��زɹ���壬��ȷ�Ϻ����룡 ");
		charRotation();
		Sleep(5000);
		proSalesInterface();
	}
	//�������ȥy��n�������ַ��Ļ�
	else {
		printf("��������������ȷ��Ҫ������룡 ");
		charRotation();
		Sleep(5000);
		addProduct();
	}
}

//���ܽ���2��ɾ���ɹ������������
void deleteProduct() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(44 + 3, 8);
	printf("ɾ���ɹ������������");
	Gotoxy(43, 11);
	printf("����������Ҫɾ���Ķ�����ţ�");
	scanf("%s", temp);
	Gotoxy(43 + 32, 11);
	charRotation();
	int r1 = searchPSale(allPSaleslist, temp);
	//��������ֲ���ʧ�ܵ����
	if (r1 < 0) {
		Gotoxy(44, 13);
		printf("��ѯ����ʧ�ܣ�ȷ�Ϻ�����  ");
		charRotation();
		deleteProduct();
	}
	else {
		Gotoxy(43, 13);
		printf("����ȷ����Ҫɾ���Ķ�����Ϣ��");
		Gotoxy(44, 15);
		printf("1.�ɹ����������ţ� %s", allPSaleslist.list[r1].PSale_id);
		Gotoxy(44, 17);
		printf("2.�ɹ�������Ʒ���ƣ� %s", allPSaleslist.list[r1].PSale_name);
		Gotoxy(44, 19);
		printf("3.����������Ŀ�ĵأ� %s", allPSaleslist.list[r1].PSale_destination);
		Gotoxy(44, 21);
		printf("4.�ɹ�������ҵ�Ǽǣ� %s", allPSaleslist.list[r1].PSale_company);
		Gotoxy(44, 23);
		printf("5.�����ɹ���Ʒ������ %.2f", allPSaleslist.list[r1].PSale_num);
		Gotoxy(44, 25);
		printf("6.�ɹ������Ǽ�ʱ�䣺 %s", allPSaleslist.list[r1].in_time);
		Gotoxy(44 - 2, 28);
		printf("ȷ��Ҫɾ�������ζ����� y/n:  ");
		scanf("%s", temp);
		Gotoxy(44 - 2 + 33, 28);
		charRotation();
		Gotoxy(44 - 2, 29);
		if (temp[0] == 'y') {
			int r3 = delPSale(&allPSaleslist, r1);
			if (r3 == -1) {
				printf("ɾ��ʧ�ܣ��޷�����ö�����Ϣ��");
				Sleep(5000);
			}
			else {
				printf("ɾ���ɹ���ϵͳ�����޸ö�����Ϣ��");
				Sleep(1000);
				proSalesInterface();
			}
		}
		//����no�������
		else if (temp[0] == 'n') {
			printf("���ڷ��زɹ���壬��ȷ�Ϻ����룡 ");
			charRotation();
			Sleep(3000);
			proSalesInterface();
		}
		//�������ȥy��n�������ַ��Ļ�
		else {
			printf("��������������ȷ��Ҫ������룡 ");
			charRotation();
			Sleep(3000);
			deleteProduct();
		}
	}
}

//���ܽ���3���޸Ĳɹ�������Ϣ����
void modifiPSale() {
	system("cls");
	frameShow();
	Gotoxy(44 + 3, 5);
	printf("�ɹ�������Ϣ�޸����");
	char temp[30];
	Gotoxy(43, 8);
	printf("����������Ҫ�޸ĵĶ�����ţ�");
	scanf("%s", temp);
	Gotoxy(43 + 32, 8);
	charRotation();
	int r1 = searchPSale(allPSaleslist, temp);
	int r2 = 0, r3 = 0;
	//��������ֲ���ʧ�ܵ����
	if (r1 < 0) {
		Gotoxy(44, 10);
		printf("��ѯ����ʧ�ܣ�ȷ�Ϻ�����  ");
		charRotation();
		proSalesInterface();
	}
	else {
		Gotoxy(43, 10);
		printf("����ȷ����Ҫ�޸ĵĶ�����Ϣ��");
		Gotoxy(44, 12);
		printf("1.�ɹ����������ţ� %s", allPSaleslist.list[r1].PSale_id);
		Gotoxy(44, 14);
		printf("2.�ɹ�������Ʒ���ƣ� %s", allPSaleslist.list[r1].PSale_name);
		Gotoxy(44, 16);
		printf("3.����������Ŀ�ĵأ� %s", allPSaleslist.list[r1].PSale_destination);
		Gotoxy(44, 18);
		printf("4.�ɹ�������ҵ�Ǽǣ� %s", allPSaleslist.list[r1].PSale_company);
		Gotoxy(44, 20);
		printf("5.�����ɹ���Ʒ������ %.2f", allPSaleslist.list[r1].PSale_num);
		Gotoxy(44, 22);
		printf("6.�ɹ������Ǽ�ʱ�䣺 %s", allPSaleslist.list[r1].in_time);
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
				r3 = modifyPSale(&allPSaleslist, r1, r2, newContent);
				if (r3 == -1) {
					Gotoxy(44 - 2, 28);
					printf("�޸Ķ�����Ϣʧ�ܣ�  ");
					charRotation();
					Sleep(5000);
					proSalesInterface();
				}
				else {
					Gotoxy(44 - 2, 28);
					printf("ѡ���޸Ķ�����Ϣ�ɹ��� ");
					charRotation();
					Sleep(3000);
					proSalesInterface();
				}
				break;
			}
			//����ı�Ų��ڷ�Χ�ڵ�
			else {
				Gotoxy(44 - 2, 26);
				printf("�������ѡ���Ŵ��� ");
				charRotation();
				Sleep(5000);
				proSalesInterface();
			}
		}
	}

}

//���ܽ���4����ѯ�ɹ�������Ϣ����
void queryPSale() {
	system("cls");
	frameShow();
	Gotoxy(22 + 2, 8);
	printf("�ɹ�������Ϣ��ѯ���");
	Gotoxy(22, 10);
	printf("����ȷ�ϲ�ѯ������Ϣ�ķ�ʽ��");
	int choice, r2;
	while (1) {
		Gotoxy(22, 12);
		printf("1.�ɹ�����������");
		Gotoxy(22, 14);
		printf("2.�ɹ�������Ʒ����");
		Gotoxy(22, 16);
		printf("3.����������Ŀ�ĵ�");
		Gotoxy(22, 18);
		printf("4.�ɹ������Ǽ���ҵ");
		Gotoxy(22, 20);
		printf("5.��ʾ���ж�����Ϣ");
		Gotoxy(22, 22);
		printf("6.���زɹ��������");
		Gotoxy(22, 25);
		printf("�������ѯ��ʽ�ı�ţ� ");
		char temp[80];
		scanf("%s", temp);
		Gotoxy(22 + 23 + 2, 25);//����
		charRotation();
		choice = atoi(temp);
		switch (choice) {
			//����Ĳ�ѯ��ʽΪ1ʱ����ʱ��ѯ��ʽΪ�������
		case 1: {
			char content[50];
			Gotoxy(22, 27);
			printf("��������Ҫ��ѯ�����ݣ� ");
			scanf("%s", content);
			Gotoxy(22 + 20 + 5, 27);
			charRotation();
			r2 = searchPSale(allPSaleslist, content);
			if (r2 < 0) {
				Gotoxy(22 + 20 + 10, 27);
				printf("��ѯ����ʧ�ܣ�ȷ�Ϻ�����  ");
				charRotation();
				queryPSale();
			}
			else {
				Gotoxy(58 + 22 - 16, 10);
				printf("1.�ɹ����������ţ� %s", allPSaleslist.list[r2].PSale_id);
				Gotoxy(58 + 22 - 16, 12);
				printf("2.�ɹ�������Ʒ���ƣ� %s", allPSaleslist.list[r2].PSale_name);
				Gotoxy(58 + 22 - 16, 14);
				printf("3.����������Ŀ�ĵأ� %s", allPSaleslist.list[r2].PSale_destination);
				Gotoxy(58 + 22 - 16, 16);
				printf("4.�ɹ������Ǽ���ҵ�� %s", allPSaleslist.list[r2].PSale_company);
				Gotoxy(58 + 22 - 16, 18);
				printf("5.�����ɹ���Ʒ������ %.2f", allPSaleslist.list[r2].PSale_num);
				Gotoxy(58 + 22 - 16, 20);
				printf("6.�ɹ������Ǽ�ʱ�䣺 %s", allPSaleslist.list[r2].in_time);
				Gotoxy(58 + 22 - 16, 24);
				printf("�鿴�����������y������һ�㣺 ");
				scanf("%s", temp);
				if (temp[0] == 'y') {
					Gotoxy(58 + 22 + 16 * 2 + 2 - 16 + 1, 24);
					charRotation();
					Sleep(1000);
					queryPSale();
				}
				else {
					Gotoxy(58 + 22 + 16 * 2 + 2 - 16 + 1, 24);
					printf("��������Ϊ����������� ");
					charRotation();
					Sleep(1000);
					proSalesInterface();
				}
			}
			break;
		}
		//����Ĳ�ѯ��ʽΪ2ʱ����ʱ��ѯ��ʽΪ���������Ʒ����
		case 2: {
			char content[50];
			Gotoxy(22, 27);
			printf("��������Ҫ��ѯ�����ݣ� ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 8, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchPSaleByOthers(allPSaleslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "û�����������Ķ�����Ϣ��");
				queryPSale();
			}
			//����ɹ��ҵ��ж�Ӧ��ֵ
			else {
				system("cls");
				frameShow();
				//����һ��
				Gotoxy(6, 4);
				printf("�������     �ɹ���Ʒ      ����Ŀ�ĵ�              �ɹ���Ʒ��ҵ         �ɹ���Ʒ����       �ǼǶ���ʱ��");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8, 8 + i);
					printf(" %s        %s           %s       %s    %.2f          %s", allPSaleslist.list[result.list[i]].PSale_id, allPSaleslist.list[result.list[i]].PSale_name, allPSaleslist.list[result.list[i]].PSale_destination, allPSaleslist.list[result.list[i]].PSale_company, allPSaleslist.list[result.list[i]].PSale_num, allPSaleslist.list[result.list[i]].in_time);
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
					queryPSale();
				}
				//������������
				else {
					Gotoxy(58 + 22, 28);
					printf("��������Ϊ����������� ");
					charRotation();
					Sleep(1000);
					proSalesInterface();
				}
			}
			errorTemplate(48, "û�����������Ķ�����Ϣ��");
			proSalesInterface();
			break;
		}
		//����Ĳ�ѯ��ʽΪ3ʱ����ʱ��ѯ��ʽΪ��Ʒ����Ŀ�ĵ�
		case 3: {
			char content[50];
			Gotoxy(22, 27);
			printf("��������Ҫ��ѯ�����ݣ� ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 28 - 15, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchPSaleByOthers(allPSaleslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "û�����������Ķ�����Ϣ��");
				queryPSale();
			}
			//����ɹ��ҵ��ж�Ӧ��ֵ
			else {
				system("cls");
				frameShow();
				//����һ��
				Gotoxy(6, 4);
				printf("�������     �ɹ���Ʒ      ����Ŀ�ĵ�              �ɹ���Ʒ��ҵ         �ɹ���Ʒ����       �ǼǶ���ʱ��");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8, 8 + i);
					printf(" %s        %s           %s       %s    %.2f          %s", allPSaleslist.list[result.list[i]].PSale_id, allPSaleslist.list[result.list[i]].PSale_name, allPSaleslist.list[result.list[i]].PSale_destination, allPSaleslist.list[result.list[i]].PSale_company, allPSaleslist.list[result.list[i]].PSale_num, allPSaleslist.list[result.list[i]].in_time);
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
					queryPSale();
				}
				//������������
				else {
					Gotoxy(58 + 22, 28);
					printf("��������Ϊ����������� ");
					charRotation();
					Sleep(1000);
					proSalesInterface();
				}
			}
			errorTemplate(48, "û�����������Ķ�����Ϣ��");
			proSalesInterface();
			break;
		}
		//����Ĳ�ѯ��ʽΪ4ʱ����ʱ��ѯ��ʽΪ�ɹ���������ҵ����
		case 4: {
			char content[50];
			Gotoxy(22, 27);
			printf("��������Ҫ��ѯ�����ݣ� ");
			scanf("%s", content);
			Gotoxy(22 + 23 + 29, 27);
			charRotation();
			IntSeqList result;
			intListInit(&result, 5);
			searchPSaleByOthers(allPSaleslist, content, choice, &result);
			if (result.length == 0) {
				errorTemplate(48, "û�����������Ķ�����Ϣ��");
				queryPSale();
			}
			//����ɹ��ҵ��ж�Ӧ��ֵ
			else {
				system("cls");
				frameShow();
				//����һ��
				Gotoxy(6, 4);
				printf("�������     �ɹ���Ʒ      ����Ŀ�ĵ�              �ɹ���Ʒ��ҵ         �ɹ���Ʒ����       �ǼǶ���ʱ��");
				for (int i = 0; i < result.length; i++) {
					Gotoxy(8, 8 + i);
					printf(" %s        %s           %s       %s    %.2f          %s", allPSaleslist.list[result.list[i]].PSale_id, allPSaleslist.list[result.list[i]].PSale_name, allPSaleslist.list[result.list[i]].PSale_destination, allPSaleslist.list[result.list[i]].PSale_company, allPSaleslist.list[result.list[i]].PSale_num, allPSaleslist.list[result.list[i]].in_time);
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
					queryPSale();
				}
				//������������
				else {
					Gotoxy(58 + 22, 28);
					printf("��������Ϊ����������� ");
					charRotation();
					Sleep(1000);
					proSalesInterface();
				}
			}
			errorTemplate(48, "û�����������Ķ�����Ϣ��");
			proSalesInterface();
			break;
		}
		//����Ĳ�ѯ��ʽΪ4ʱ����ʱ��ѯ��ʽΪ��ʾ���ж���
		case 5: {
			if (allPSaleslist.length == 0) {
				errorTemplate(48, "�ɹ�������Ϣ���ݿ�Ϊ�գ�");
				queryPSale();
			}
			system("cls");
			frameShow();
			//����һ��
			Gotoxy(6, 4);
			printf("�������     �ɹ���Ʒ      ����Ŀ�ĵ�              �ɹ���Ʒ��ҵ         �ɹ���Ʒ����       �ǼǶ���ʱ��");
			for (int i = 0; i < allPSaleslist.length; i++) {
				Gotoxy(8, 8 + i);
				printf(" %s        %s           %s       %s    %.2f          %s", allPSaleslist.list[i].PSale_id, allPSaleslist.list[i].PSale_name, allPSaleslist.list[i].PSale_destination, allPSaleslist.list[i].PSale_company, allPSaleslist.list[i].PSale_num, allPSaleslist.list[i].in_time);
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
				queryPSale();
			}
			//������������
			else {
				Gotoxy(58 + 22, 28);
				printf("��������Ϊ����������� ");
				charRotation();
				Sleep(1000);
				proSalesInterface();
			}
		}
		//����Ĳ�ѯ��ʽΪ6ʱ����ʱ�˳���ѯ�������
		case 6: {
			errorTemplate(49, "���ڷ��زɹ�������壡");
			proSalesInterface();
		}
		default: {
			errorTemplate(48, "����Ĳ�ѯ��ʽ�������");
			queryPSale();
		}
		}
	}
}

//���ܽ���5�������ɹ������������
void deliveryPSale() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(44 + 3, 8);
	printf("�˶Խ����ɹ��������");
	Gotoxy(43, 11);
	printf("����������Ҫ�����Ķ�����ţ�");
	scanf("%s", temp);
	Gotoxy(43 + 32, 11);
	charRotation();
	int r1 = searchPSale(allPSaleslist, temp);
	//��������ֲ���ʧ�ܵ����
	if (r1 < 0) {
		Gotoxy(44, 13);
		printf("��ѯ����ʧ�ܣ�ȷ�Ϻ�����  ");
		charRotation();
		deliveryPSale();
	}
	else {
		Gotoxy(43, 13);
		printf("�����˶���Ҫ�����Ķ�����Ϣ��");
		Gotoxy(44, 15);
		printf("1.�ɹ����������ţ� %s", allPSaleslist.list[r1].PSale_id);
		Gotoxy(44, 17);
		printf("2.�ɹ�������Ʒ���ƣ� %s", allPSaleslist.list[r1].PSale_name);
		Gotoxy(44, 19);
		printf("3.����������Ŀ�ĵأ� %s", allPSaleslist.list[r1].PSale_destination);
		Gotoxy(44, 21);
		printf("4.�ɹ�������ҵ�Ǽǣ� %s", allPSaleslist.list[r1].PSale_company);
		Gotoxy(44, 23);
		printf("5.�����ɹ���Ʒ������ %.2f", allPSaleslist.list[r1].PSale_num);
		Gotoxy(44, 25);
		printf("6.�ɹ������Ǽ�ʱ�䣺 %s", allPSaleslist.list[r1].in_time);
		Gotoxy(44 - 2, 28);
		printf("ȷ��Ҫ���������ζ����� y/n:  ");
		scanf("%s", temp);
		Gotoxy(44 - 2 + 33, 28);
		charRotation();
		Gotoxy(44 - 2, 29);
		if (temp[0] == 'y') {
			int r3 = delPSale(&allPSaleslist, r1);
			if (r3 == -1) {
				errorTemplate(48, "�˶Ե�ǰ�Ķ�����Ϣʧ�ܣ�");
				deliveryPSale();
				Sleep(5000);
			}
			else {
				errorTemplate(48, "�˶Գɹ���������ɶ�������");
				Sleep(1000);
				errorTemplate(48, "�����ɹ���ϵͳ���޶�����Ϣ");
				proSalesInterface();
			}
		}
		//����no�������
		else if (temp[0] == 'n') {
			printf("���ڷ��زɹ���壬��ȷ�Ϻ����룡 ");
			charRotation();
			Sleep(3000);
			proSalesInterface();
		}
		//�������ȥy��n�������ַ��Ļ�
		else {
			printf("��������������ȷ��Ҫ������룡 ");
			charRotation();
			Sleep(3000);
			deliveryPSale();
		}
	}
}

//���ܽ���6������ɹ�������Ϣ����
void savePSale() {
	int r1 = allSaveSale();
	if (r1 == -1) {
		errorTemplate(48, "���浱ǰ�Ķ�����Ϣʧ�ܣ�");
		proSalesInterface();
	}
	else {
		errorTemplate(48, "���ڱ������еĶ�����Ϣ��");
		errorTemplate(48, "�������еĶ�����Ϣ�ɹ���");
		proSalesInterface();
	}
}

//��Ϲ��ܽ���1�����ܺ���--���Ӳɹ������Ǽ���Ϣ
int addNewPSale(PSalesSeqList* pssl, PSaleInfo newPSale) {

	//�����ڲɹ�������Ϣ���в����Ƿ��д˲ɹ�������Ϣ������У����� - 1����ʾ�����Ǽ�ʧ��
	int r = searchPSale(*pssl, newPSale.PSale_id);
	if (r >= 0) {
		errorTemplate(48, "�ɹ������ǼǱ���Ѵ��ڣ�");
		proSalesInterface();
	}
	//��������ռ䲻����������ռ�
	if (pssl->length >= pssl->size) {
		PSaleInfo* t = pssl->list;
		pssl->list = (PSaleInfo*)malloc(2 * pssl->size * sizeof(PSaleInfo));
		if (pssl->list == NULL) {
			errorTemplate(48, "������Ч���ڴ����ʧ�ܣ�");
			proSalesInterface();
		}
		pssl->size = 2 * pssl->size;
		for (int i = 0; i < pssl->length; i++)
			PSaleCopy(&(pssl->list[i]), t[i]);
		free(t);
	}
	//	�ϲɹ������ǼǱ�Ų��뵽���ʵ�λ�ã���֤�ݲɹ������������
	int i = 0;
	for (i = pssl->length - 1; i >= 0; i--) {
		r = strcmp(pssl->list[i].PSale_id, newPSale.PSale_id);
		if (r > 0)
			PSaleCopy(&(pssl->list[i + 1]), pssl->list[i]);
		else
			break;

	}
	PSaleCopy(&(pssl->list[i + 1]), newPSale);
	pssl->length++;
	//��ӳɹ�����0
	return 0;
}

//��Ϲ��ܽ���123�����ܺ���--�ڲɹ������ǼǱ��Լ�����и��ݲɹ�������Ž��в��ң�û�иñ����ռ�ö����򷵻�-1������з���ֵ���ǸõǼǱ���ѱ�ռ�ã������㷨�ö��ֲ��ҷ���
int searchPSale(PSalesSeqList pssl, char* PSsn) {		//����������������һ����pssl��һ����PSsn
	int low = 0;
	int high = pssl.length - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;		//���ֲ��ҷ�
		if (strcmp(pssl.list[mid].PSale_id, PSsn) == 0)
			return mid;
		else
			if (strcmp(pssl.list[mid].PSale_id, PSsn) < 0)
				low = mid + 1;
			else
				high = mid - 1;
	}
	return -1;
}

//��Ϲ��ܽ���123�����ܺ���--��ȿ������������Ǽ���Ϣ
void PSaleCopy(PSaleInfo* to, PSaleInfo from) {
	strcpy(to->PSale_id, from.PSale_id);
	strcpy(to->PSale_name, from.PSale_name);
	strcpy(to->PSale_destination, from.PSale_destination);
	strcpy(to->PSale_company, from.PSale_company);
	to->PSale_num = from.PSale_num;
	strcpy(to->in_time, from.in_time);
}

//��Ϲ��ܽ���2�����ܺ���--�ڶ����������ɾ����index��Ԫ�أ�ɾ���㷨Ϊ�Ѻ��������Ԫ�ظ���ǰ�棬����0��ʾɾ���ɹ�
int delPSale(PSalesSeqList* pssl, int index) {
	if (pssl->length <= 0) {
		errorTemplate(48, "�ɹ��������ݿ���ϢΪ�գ�");
		proSalesInterface();
		return -1;
	}
	if (index < 0 || index >= pssl->length) {
		errorTemplate(47, "��Ҫɾ���Ķ�������ִ�з�Χ��");
		proSalesInterface();
		return -1;
	}

	for (int i = index + 1; i < pssl->length; i++) {
		PSaleCopy(&(pssl->list[i - 1]), pssl->list[i]);
	}
	pssl->length--;
	return 0;
}

//��Ϲ��ܽ���3�����ܺ������ڶ��������pssl���޸ĵ�index���������ε���Ϣ��type��ʾҪ�޸ĵ����ͣ�ȡֵ1�������ǼǱ�ţ���2�����������Ʒ���ƣ���3����Ӧ��ƷĿ�ĵأ���4���ɹ���Ʒ��ҵ�Ǽ����ƣ�����info��ʾ�µ���Ϣֵ���޸ĳɹ�����0�����򷵻�1
int modifyPSale(PSalesSeqList* pssl, int index, int type, char* info) {
	if (index < 0 && index >= pssl->length) {
		errorTemplate(47, "��Ҫ�޸ĵĶ�������ִ�з�Χ��");
		proSalesInterface();
	}
	switch (type) {
		case 1: strcpy(pssl->list[index].PSale_id, info); break;
		case 2: strcpy(pssl->list[index].PSale_name, info); break;
		case 3: strcpy(pssl->list[index].PSale_destination, info); break;
		case 4: strcpy(pssl->list[index].PSale_company, info); break;
		case 5: pssl->list[index].PSale_num = atof(info); break;
		case 6: strcpy(pssl->list[index].in_time, info); break;
		default: {
			errorTemplate(48, "�޸ĵĶ�����Ϣ�������");
			proSalesInterface();
		}
	}
	return 0;
}

//��Ϲ��ܽ���4�����ܺ���--���ݶ�����������Ϣ��tpyeȡֵ1�������Ǽ����ƣ���2����Ӧ��Ʒ����Ŀ�ĵأ���3���ɹ���Ʒ��ҵ���ƣ�����ѯ��ؼ�¼�Ĳɹ�������Ϣ��
//               ���û���ҵ����򷵻� - 1������У���ѯ�����һ��IntSeqList�б��أ��б�װ���Ƕ����ڶ���˳����е����
int searchPSaleByOthers(PSalesSeqList pssl, char* info, int type, IntSeqList* psindex) {
	for (int i = 0; i < pssl.length; i++) {
		switch (type - 1) {
			//�������ѡ��Ϊ2ʱ��typeֵ��ӦΪ1����ִ�а��ն��������Ʒ���Ʋ�ѯ���ַ���
		case 1: if (strcmp(pssl.list[i].PSale_name, info) == 0)
			addInt(psindex, i);
			break;
			//�������ѡ��Ϊ3ʱ��typeֵ��ӦΪ2����ִ�а��ն�������Ŀ�ĵصĲ�ѯ���ַ���
		case 2: if (strcmp(pssl.list[i].PSale_destination, info) == 0)
			addInt(psindex, i);
			break;
			//�������ѡ��Ϊ4ʱ��typeֵ��ӦΪ3����ִ�а��ղɹ�������ҵ���ƵĲ�ѯ�ַ���
		case 3: if (strcmp(pssl.list[i].PSale_company, info) == 0)
			addInt(psindex, i);
			break;
		default: {
			errorTemplate(47.5, "��ѯ������Ϣ��ʽ�������");
			proSalesInterface();
		}
		}
	}
	return 0;
}

//��Ϲ��ܽ���5�����ܺ���--������ϵͳ������ɾ�����ĺ����Ϣ�������ݿ���
int allPSalesInfoSaveToFile(PSalesSeqList pssl, char* filename) {
	FILE *fp;
	char strline[80];
	if ((fp = fopen(filename, "w")) == NULL) {
		errorTemplate(48, "�ɹ����������ݿⲻ���ڣ�");
		proSalesInterface();
	}

	for (int i = 0; i < pssl.length; i++) {
		fputs(pssl.list[i].PSale_id, fp);
		fputc('\n', fp);
		fputs(pssl.list[i].PSale_name, fp);
		fputc('\n', fp);
		fputs(pssl.list[i].PSale_destination, fp);
		fputc('\n', fp);
		fputs(pssl.list[i].PSale_company, fp);
		fputc('\n', fp);
		sprintf(strline, "%.2f", pssl.list[i].PSale_num);
		fputs(strline, fp);
		fputc('\n', fp);
		fputs(pssl.list[i].in_time, fp);
		fputc('\n', fp);
	}
	fclose(fp);
	return 0;
}

//��Ϲ��ܽ���5�����ܺ���--�����ͱ���ɹ�������Ϣ���ļ���
int allSaveSale() {
	int r1 = allPSalesInfoSaveToFile(allPSaleslist, "�ɹ�������Ϣ���ݿ�.txt");  //�������еĲɹ�������Ϣ���ļ���
	if (r1 == -1) {
		errorTemplate(48, "���浱ǰ�Ķ�����Ϣʧ�ܣ�");
		proSalesInterface();
	}
	return 0;
}