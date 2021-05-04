#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include"Globals.h"
#include<string.h>
#include"MES-ProcessDesigner.h"
//#include"GenericData.h"

#define _CRT_SECURE_NO_DEPRECATE��
#define _CRT_SECURE_NO_WARNINGS��
#pragma warning(disable:4996)��

//����ֱ�ӽ�������������ʾ�������������ʱ��ʹ��
struct coordinate coord[15] = { {9,9},{31,9},{53,9},{75,9} ,{97,9},{97,15},{75,15},{53,15},{31,15},{9,15} ,{9,21},{31,21},{53,21},{75,21} ,{97,21} };

extern DProcessSeqList  allDProcesslist;//����̬˳���洢���еĹ���������Ϣ

/*----------------------����������Ϣ�������ݽṹ�ӿ�----------------------*/
//���ݽṹ����1��DProcess����-��ʼ������� dpsl��size��ʾ��ʼ������
void DProcessSeqListInit(DProcessSeqList* dpsl, int size);

//���ݽṹ����2�������е������ʼ��������ʹ��֮ǰҪ��ʼ����ͬʱ����ͷβָ�븳��ֵ
void PMLinkedListInit(PMLinkedList* list);

//���ݽṹ����3��DProcess���ݲ���--���ݿ���Ϣ��ʼ��
int allDProcessInfoReadFromFile(DProcessSeqList* dpsl, char* filename);

/*----------------------����ӿڼ���----------------------*/
//����1������������Ϣ�������
void DProcessInterface();

/*----------------------����������Ϣ�������ݲ����ӿ�----------------------*/
//���ݽṹ���ܺ���1����ȫ�µ������������ģ�飬���������ģ�飬Ҳ�����������̵�ģ��ֵ��PModuleΪ��Ҫ���ӽ�ȥ������
//�������ڳ�ʼ��
void addNewPModuleListTill(PMLinkedList* list, char* PModule);

//���ݽṹ���ܺ���2,��ȫ�µ�������б���ģ�飬�Ҳ�����idֵ���������Ǵ����õ�����ͼ�ĸ���ģ������idΪlist�ڱ��е�λ�� 
void ScanNewPModuleList(DProcessInfo newProcess);

//���ݽṹ���ܺ���3,��ѯ����ͼ��ָ����һ�����ڳ���
struct PModuleNode* FindPModuleNode(DProcessSeqList dpsl, int id, char* tarModule);

//���ݽṹ���ܺ���4������ͼ����ղ��������Խ���������ͼ��ģ���ÿ�
void FreePModuleList(DProcessSeqList* dpsl, int id);

//���ݽṹ���ܺ���5����ָ����ģ��λ�ò���ģ�飬����ʵ������ͼ�ı༭�����������
void AddPModuleListRand(DProcessSeqList* dpsl, int id, char* tarModule, char* addModule);

//���ݽṹ���ܺ���6����ָ����ģ��λ�ñ༭�����ݣ�����ʵ������ͼ�ı༭������ĸģ�
void modiPModuleListRand(DProcessSeqList* dpsl, int id, char* oldModule, char* newModule);

//���ݽṹ���ܺ���7��ɾ��ģ�����֮ɾ��ָ��ģ��
void DeletePModuleListRand(DProcessSeqList* dpsl, int id, char* deleModule);

/*----------------------����������Ϣ�����ͼ�����ӿ�----------------------*/
//��ͼ������ר�����ڻ�������ͼ������numֵΪ�����ģ������
void processFrame(int num);

//���ƺ�����ר�����ڻ�����Ʊ߿�
void DProcessFrame();

/*----------------------�������ӿڼ���----------------------*/
//���ܽ���1���������������ӽ���
void addDProcess();

//���ܽ���2����ѯ�������̵Ľ���
void checkDProcess();

//���ܽ���3����������ɾ������
void deleteDProcess();

//���ܽ���4���޸Ĺ���������Ϣ
void modifiDProcess();

//���ܽ���5���༭��������ģ�����
void  modifiDProcessModule();

//���ܽ���6�����湤��������Ϣ����
void saveDProcess();

//��Ϲ��ܽ���1�����ܺ���--��������������ȫ�µ�һ��newDProcess
int addNewDProcess(DProcessSeqList* dpsl, DProcessInfo newDProcess);

//��Ϲ��ܽ���123�����ܺ���--�ڹ������̵ǼǱ��и��ݵǼ����̱�Ž��в��ң�û�иñ����ռ�ÿ���򷵻�-1������з���ֵ���ǸõǼǱ���ѱ�ռ�ã������㷨�ö��ֲ��ҷ���
int searchDProcess(DProcessSeqList dpsl, char* DPsn);

//��Ϲ��ܽ���123�����ܺ���--��ȿ��������Ĺ�������ͼֽ��Ϣ,����num�����������õ�ģ����
void DProcessCopy(DProcessInfo* to, DProcessInfo from, int num);

//��Ϲ��ܽ���2�����ܺ���--�ڹ������̹������ɾ����index��Ԫ�أ�ɾ���㷨Ϊ�Ѻ��������Ԫ�ظ���ǰ�棬����0��ʾɾ���ɹ�
int delDProcess(DProcessSeqList* dpsl, int index);

//��Ϲ��ܽ���3�����ܺ������ڹ������̹����dpsl���޸ĵ�index���������ε���Ϣ��type��ʾҪ�޸ĵ����ͣ�ȡֵ1���������̵ǼǱ�ţ���2���������̵Ǽ����ƣ���3������������ʽ��ע����4����������ģ��������,5���������̵Ǽ�ʱ�䣩����info��ʾ�µ���Ϣֵ���޸ĳɹ�����0�����򷵻�1
int modifyDProcess(DProcessSeqList* dpsl, int index, int type, char* info);

//��Ϲ��ܽ���5�����ܺ���--������ϵͳ������ɾ�����ĺ����Ϣ�������ݿ���
int allDProcessInfoSaveToFile(DProcessSeqList dpsl, char* filename);

//��Ϲ��ܽ���5�����ܺ���--�����ͱ���ִ���Ϣ���ļ���
int allSaveDProcess();

//����ӿں���������Աר���ڲ�ѯ�ִ����ԭ����Ϣ����
void checkDProcessAdmin();


/*----------------------����������Ϣ�������ݽṹ�ӿ�----------------------*/
//���ݽṹ����1��DProcess����-��ʼ������� dpsl��size��ʾ��ʼ������
void DProcessSeqListInit(DProcessSeqList* dpsl, int size) {
	dpsl->list = (DProcessInfo*)malloc(size * sizeof(DProcessInfo));
	dpsl->size = size;
	dpsl->length = 0;
}

//���ݽṹ����2�������е������ʼ��������ʹ��֮ǰҪ��ʼ����ͬʱ����ͷβָ�븳��ֵ
void PMLinkedListInit(PMLinkedList* list) {
	list->head = (PModuleNode*)malloc(sizeof(PModuleNode));
	list->rear = (PModuleNode*)malloc(sizeof(PModuleNode));
	list->head->next = list->rear;
	strcpy(list->head->PModule, "�������̿�ʼ");
	strcpy(list->rear->PModule, "�������̽���");
	list->rear->next = NULL;
	list->count = 0;
}

//���ݽṹ����3��DProcess���ݲ���--���ݿ���Ϣ��ʼ��
int allDProcessInfoReadFromFile(DProcessSeqList* dpsl, char* filename) {
	FILE *fp;
	char strline[80];						   //ÿ������ȡ���ַ���
	if ((fp = fopen(filename, "r")) == NULL) { //�ж��ļ��Ƿ���ڼ��ɶ�
		errorTemplate(48, "���� MES���ݿ���Ϣ����");
		return -1;
	}
	DProcessInfo newDProcess;
	PMLinkedListInit(&newDProcess.processList);//ǧ��Ҫ�����˳�ʼ����������������˺ö����
	while (!feof(fp)) {
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newDProcess.DProcess_id, strline);
		else {
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newDProcess.DProcess_name, strline);
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0)
			strcpy(newDProcess.DProcess_method, strline);
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			newDProcess.DProcess_num = atof(strline);
		}
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		if (fscanf(fp, "%s", strline) > 0) {
			strcpy(newDProcess.in_time, strline);
		}
		else {
			errorTemplate(48, "���� MES���ݿ���Ϣ����");
			fclose(fp);
			return -1;
		}
		for (int i = 0; i < newDProcess.DProcess_num+2; i++) {
			if (fscanf(fp, "%s", strline) > 0) {
				if(!(strcmp(strline, "�������̿�ʼ") == 0 || strcmp(strline, "�������̽���") == 0))
				addNewPModuleListTill(&newDProcess.processList, &strline);
			}
			else {
				fclose(fp);
				return -1;
			}
		}
		addNewDProcess(dpsl, newDProcess);
	}
	fclose(fp);//�ر��ļ�
	return 0;
}

/*----------------------����ӿڼ���----------------------*/
//����1������������Ϣ�������
void DProcessInterface() {	//��Ʒͼֽ�������
	int choice;
	system("cls");
	frameShow();
	Gotoxy(44 + 6, 7);
	printf("����������Ϣ����");
	Gotoxy(44 + 2, 10);		//��̬�ƶ���꣬ͬʱ��ҳ�������꣨48��10����Ϊ��׼�ƶ�����Ĺ��
	printf("1.�� �� �� �� �� �� �� ��");
	Gotoxy(44 + 2, 12);
	printf("2.�� �� �� �� �� �� �� Ϣ");
	Gotoxy(44 + 2, 14);
	printf("3.�� �� �� �� �� �� �� Ϣ");
	Gotoxy(44 + 2, 16);
	printf("4.�� �� �� �� ģ �� �� Ϣ");
	Gotoxy(44 + 2, 18);
	printf("5.ɾ �� �� �� �� �� �� Ϣ");
	Gotoxy(44 + 2, 20);
	printf("6.�� �� �� �� �� �� �� Ϣ");
	Gotoxy(44 + 2, 22);
	printf("7.�� �� �� �� �� �� �� ��");
	Gotoxy(44 + 2, 24);
	printf("����������Ҫ�����ı��룺");
	Gotoxy(44 + 23 + 3, 24);
	scanf("%d", &choice);
	Gotoxy(44 + 23 + 3+2, 24);
	charRotation();
	switch (choice) {
	case 1: {
		DProcessFrame();
		addDProcess();
	}
	case 2: {
		checkDProcess();
	}
	case 3: {
		modifiDProcess();
	}
	case 4: {
		modifiDProcessModule();
	}
	case 5: {
		deleteDProcess();
	}
	case 6: {
		saveDProcess();
	}
	case 7: {
		errorTemplate(47.5, "�����˳��������������壡");
		exitMES(3);
	}
	default: {
		errorTemplate(47.5, "�������������������룡");
		DProcessInterface();
	}
	}
}


/*----------------------����������Ϣ�������ݲ����ӿ�----------------------*/
//���ݽṹ���ܺ���1����ȫ�µ������������ģ�飬���������ģ�飬Ҳ�����������̵�ģ��ֵ��PModuleΪ��Ҫ���ӽ�ȥ������
//�������ڳ�ʼ��
void addNewPModuleListTill(PMLinkedList* list,char* PModule)
{
	//����һ���ڵ�
	PModuleNode* temp = (PModuleNode*)malloc(sizeof(PModuleNode)); //�˴�ע��ǿ������ת��
	//�ڵ����ݽ��и�ֵ
	strcpy(temp->PModule, PModule);
	//����ָ����һ��
	temp->next = NULL;
	//���ӷ��������1.һ���ڵ㶼û��2.�Ѿ��нڵ��ˣ���ӵ�β����
	//��һ�־���ͷ�ڵ㶼�ǿյģ��Ǿ���ͷ�ڵ㱾���Ϊtemp��һ��ֵstrcpy(list->head->PModule,"�������̿�ʼ");
	if ( list->head->next == list->rear){
		list->head->next = temp;
		temp->next = list->rear;
		//	end=temp;
	}
	//�ڶ��֣���Ϊǰ���Ѿ��� temp��ָ����ָ����NULL����������ֻҪ����rear
	else{
		//�ȴ���һ���ڵ㣬�����β�ڵ��ǰһ��ֵ
		PModuleNode* before_rear = (PModuleNode*)malloc(sizeof(PModuleNode)); //�˴�ע��ǿ������ת��
		PModuleNode* p = (PModuleNode*)malloc(sizeof(PModuleNode)); //�˴�ע��ǿ������ת��
		p = list->head;
		while (!(strcmp(p->PModule, "�������̽���") == 0)) {
			before_rear =p;
			p = p->next;
		}
		//newProcess->processList.rear->next = temp;
		before_rear->next = temp;
		temp->next= list->rear;
		//newProcess->processList.rear = temp;
	}
	//β���Ӧ��ʼ��ָ�����һ������ʱΪtemp
}

//���ݽṹ���ܺ���2,��ȫ�µ�������б���ģ�飬�Ҳ�����idֵ���������Ǵ����õ�����ͼ�ĸ���ģ������idΪlist�ڱ��е�λ�� 
void ScanNewPModuleList(DProcessInfo newProcess)
{
	PModuleNode *temp = newProcess.processList.head;		//����һ����ʱ������ָ��ͷ
	//��tempֵָ��յ�ʱ�����ֹͣ��˵������ͼ�Ѿ��������
	//��һ���������˵��������ǿյ�����
	if (newProcess.processList.head->next==newProcess.processList.rear){
		errorTemplate(48, "�ù�������û��ģ����Ϣ��");
		//�����ﷵ�ز�ѯ����
	}
	else {
		int i = 0;
		while (temp != NULL)
		{
			Gotoxy(coord[i].x, coord[i].y);
			//��ӡPModuleģ�����ַ�����
			printf("%s  ", temp->PModule);
			temp = temp->next;		//tempָ����һ���ĵ�ַ ��ʵ���ԼӲ���
			i = i++;
		}
	}
}

//���ݽṹ���ܺ���3,��ѯ����ͼ��ָ����һ�����ڳ���
struct PModuleNode* FindPModuleNode(DProcessSeqList dpsl, int id,char* tarModule)
{
	PModuleNode *temp = dpsl.list[id].processList.head;
	//���п����Ǹýڵ�������ڲ������κε�ģ����Ϣ
	if (NULL == dpsl.list[id].processList.head) {
		errorTemplate(48, "�ù�������û��ģ����Ϣ��");
		return NULL;
	}
	else {
		while (temp != NULL) {
			//ר��ʹ��strcmp����������ģ���ƥ�䣬���ҳ�������ͼ��ʹ���˴�ģ���
			if (strcmp(temp->PModule, tarModule) == 0) {
				//����鵽ָ�����ڣ��ͷ���tempֵ����
				return temp;
			}
			//��Ȼ�����¼�����
			temp = temp->next;
		}
		//û�ҵ��Ļ�����ʱ�ýڵ�н�ֵΪ��ֵ
		errorTemplate(46, "��������û������������ģ����Ϣ��");
		//���ؿ�ֵʱ������Ҫ������
		return NULL;
	}
}

//���ݽṹ���ܺ���4������ͼ����ղ��������Խ���������ͼ��ģ���ÿ�
void FreePModuleList(DProcessSeqList* dpsl, int id)
{
	PModuleNode *temp = dpsl->list[id].processList.head;		//����һ����ʱ������ָ��ͷ
	//���п����Ǹýڵ�������ڲ������κε�ģ����Ϣ
	if (NULL == dpsl->list[id].processList.head) {
		errorTemplate(48, "�ù�������û��ģ����Ϣ��");
		DProcessInterface();
	}
	else{
		while (temp != NULL){
			PModuleNode* pt = temp;
			temp = temp->next;		    //tempָ����һ���ĵ�ַ ��ʵ�������ģ�鲻���ƶ�����
			free(pt);					//�ͷŵ�ǰ
		}
		//ͷβ��ն�Ҫ��պã�������ȫɾ���ɾ�
		dpsl->list[id].processList.head = NULL;
		dpsl->list[id].processList.rear = NULL;
		errorTemplate(46, "�����ɣ���������û��ģ����Ϣ��");
	}
}

//���ݽṹ���ܺ���5����ָ����ģ��λ�ò���ģ�飬����ʵ������ͼ�ı༭�����������
void AddPModuleListRand(DProcessSeqList* dpsl, int id,char* tarModule, char* addModule)
{
	//˵����ʱ�ýڵ�Ϊ��
	if ( dpsl->list[id].processList.head->next==dpsl->list[id].processList.rear){
		errorTemplate(48, "�ù�������û��ģ����Ϣ��");
		modifiDProcessModule();
	}
	else {
		PModuleNode* pt = FindPModuleNode(allDProcesslist,id,tarModule);
		//������ص�ptֵΪ�գ���֤��û�д�ƥ������̻��ڣ�˵�������id�Ǵ���
		if (NULL == pt) modifiDProcessModule();
		else{
			//�д˽ڵ�
			//������ʱ�ڵ㣬�����ڴ�
			PModuleNode* temp = (PModuleNode *)malloc(sizeof(PModuleNode));
			//�ڵ��Ա���и�ֵ,������Ҫ�����ģ�����ӽ�����ʱ�ڵ���
			strcpy(temp->PModule, addModule);
			temp->next = NULL;
			//��Ҫ������Ҫ���ӵ�ģ�����ӵ��������������� 
			//���ӵ����Ҳ��Ϊ���֣�����Ϊͷβ�ڵ�̶�������ֻ�ÿ���һ��ͨ����� 
			// �������� ���Ƚ�Ҫ����Ľڵ�ָ��ָ��ԭ���ҵ��ڵ����һ����
			temp->next = pt->next;
			//����ǰ��
			pt->next = temp;
		}
		
	}
	
}

//���ݽṹ���ܺ���6����ָ����ģ��λ�ñ༭�����ݣ�����ʵ������ͼ�ı༭������ĸģ�
void modiPModuleListRand(DProcessSeqList* dpsl, int id, char* oldModule, char* newModule) {
	//˵����ʱ�ýڵ�Ϊ��
	if (dpsl->list[id].processList.head->next == dpsl->list[id].processList.rear) {
		errorTemplate(48, "�ù�������û��ģ����Ϣ��");
		modifiDProcessModule();
	}
	else {
		PModuleNode* pt = FindPModuleNode(allDProcesslist, id, oldModule);
		//������ص�ptֵΪ�գ���֤��û�д�ƥ������̻��ڣ�˵�������id�Ǵ���
		if (NULL == pt) modifiDProcessModule();
		else {
			memset(pt->PModule, 0, sizeof(pt->PModule));	//����������ٸ�ֵ
			strcpy(pt->PModule, newModule);
		}
	}
}

//���ݽṹ���ܺ���7��ɾ��ģ�����֮ɾ��ָ��ģ��
void DeletePModuleListRand(DProcessSeqList* dpsl, int id,char* deleModule)
{
	//������ .�ж��Ƿ�Ϊ��
	if (dpsl->list[id].processList.head->next == dpsl->list[id].processList.rear) {
		errorTemplate(48, "�ù�������û��ģ����Ϣ��");
		modifiDProcessModule();
	}
	//����Ϊ�յĻ�����ȥѰ�������Ҫɾ������ģ��
	PModuleNode* temp = FindPModuleNode(allDProcesslist, id, deleModule);
	if (NULL == temp) modifiDProcessModule();
	//�ҵ���Ҫɾ���Ĺ�������ͼģ��ʱ,����ͼ�ж���ڵ�������
	else{
		//ɾ���м�ĳ���ڵ㣬��Ҫɾ��tempǰһ��������
		PModuleNode* pt = dpsl->list[id].processList.head;
		while (pt->next != temp) {
			pt = pt->next;
		}
		//�ҵ����˸�ģ���Ժ󣬾�ֱ����ǰһ��ֱ�����Ӻ�һ��
		//Ȼ���ͷŵ���Ҫɾ����ģ�鼴���Զ�
		pt->next = temp->next;
		free(temp);
		}
	}

/*----------------------����������Ϣ�����ͼ�����ӿ�----------------------*/
//��ͼ������ר�����ڻ�������ͼ������numֵΪ�����ģ������
void processFrame(int num) {
	if (num <= 5) {
		for (int i = 0; i < num - 1; i++) {
			Gotoxy(7 + i * 22, 8);
			printf("��������������������������������");
			Gotoxy(7 + i * 22, 9);
			printf("��              ��");
			Gotoxy(7 + i * 22, 10);
			printf("��������������������������������");
			Gotoxy(23 + 22 * i, 9);
			printf("����������>");
		}
		Gotoxy(7 + (num - 1) * 22, 8);
		printf("��������������������������������");
		Gotoxy(7 + (num - 1) * 22, 9);
		printf("��              ��");
		Gotoxy(7 + (num - 1) * 22, 10);
		printf("��������������������������������");
	}
	else {
		Gotoxy(103, 10);
		printf("��");
		for (int i = 0; i < 4; i++) {
			Gotoxy(103, 11 + i);
			printf("��");
		}
		Gotoxy(103, 14);
		printf("��");
		//�ոպ�6��ģ��
		if (num == 6) {
			Gotoxy(7 + (5 - 1) * 22, 14);
			printf("��������������������������������");
			Gotoxy(7 + (5 - 1) * 22, 15);
			printf("��              ��");
			Gotoxy(7 + (5 - 1) * 22, 16);
			printf("��������������������������������");
		}
		//����6��ģ�飬��С�ڵ���10��ģ��ʱ
		else if (num >= 6 && num <= 10) {
			for (int i = 0; i < 5 - 1; i++) {
				Gotoxy(7 + i * 22, 8);
				printf("��������������������������������");
				Gotoxy(7 + i * 22, 9);
				printf("��              ��");
				Gotoxy(7 + i * 22, 10);
				printf("��������������������������������");
				Gotoxy(23 + 22 * i, 9);
				printf("����������>");
			}
			Gotoxy(7 + (5 - 1) * 22, 8);
			printf("��������������������������������");
			Gotoxy(7 + (5 - 1) * 22, 9);
			printf("��              ��");
			Gotoxy(7 + (5 - 1) * 22, 10);
			printf("��������������������������������");

			Gotoxy(7 + (5 - 1) * 22, 14);
			printf("��������������������������������");
			Gotoxy(7 + (5 - 1) * 22, 15);
			printf("��              ��");
			Gotoxy(7 + (5 - 1) * 22, 16);
			printf("��������������������������������");
			for (int i = 0; i < num - 6; i++) {
				Gotoxy(95 - 6 - (6 + 16)*i, 15);
				printf("<����������");
				Gotoxy(95 - 6 - 16 - (6 + 16)*i, 14);
				printf("��������������������������������");
				Gotoxy(95 - 6 - 16 - (6 + 16)*i, 15);
				printf("��              ��");
				Gotoxy(95 - 6 - 16 - (6 + 16)*i, 16);
				printf("��������������������������������");
			}
		}
		//����10��ģ��
		else {
			for (int i = 0; i < 5 - 1; i++) {
				Gotoxy(7 + i * 22, 8);
				printf("��������������������������������");
				Gotoxy(7 + i * 22, 9);
				printf("��              ��");
				Gotoxy(7 + i * 22, 10);
				printf("��������������������������������");
				Gotoxy(23 + 22 * i, 9);
				printf("����������>");
			}
			Gotoxy(7 + (5 - 1) * 22, 8);
			printf("��������������������������������");
			Gotoxy(7 + (5 - 1) * 22, 9);
			printf("��              ��");
			Gotoxy(7 + (5 - 1) * 22, 10);
			printf("��������������������������������");


			Gotoxy(7 + (5 - 1) * 22, 14);
			printf("��������������������������������");
			Gotoxy(7 + (5 - 1) * 22, 15);
			printf("��              ��");
			Gotoxy(7 + (5 - 1) * 22, 16);
			printf("��������������������������������");
			for (int i = 0; i < 4; i++) {
				Gotoxy(95 - 6 - (6 + 16)*i, 15);
				printf("<����������");
				Gotoxy(95 - 6 - 16 - (6 + 16)*i, 14);
				printf("��������������������������������");
				Gotoxy(95 - 6 - 16 - (6 + 16)*i, 15);
				printf("��              ��");
				Gotoxy(95 - 6 - 16 - (6 + 16)*i, 16);
				printf("��������������������������������");
			}
			Gotoxy(7 + 8, 16);
			printf("��");
			for (int i = 0; i < 4; i++) {
				Gotoxy(7 + 8, 17 + i);
				printf("��");
			}
			Gotoxy(7 + 8, 20);
			printf("��");
			//����ģ��������11��ʱ
			if (num == 11) {
				Gotoxy(7, 20);
				printf("��������������������������������");
				Gotoxy(7, 21);
				printf("��              ��");
				Gotoxy(7, 22);
				printf("��������������������������������");
			}
			//����ģ��������11��ʱ,��С��15ʱ
			else {

				Gotoxy(7, 20);
				printf("��������������������������������");
				Gotoxy(7, 21);
				printf("��              ��");
				Gotoxy(7, 22);
				printf("��������������������������������");
				for (int i = 0; i < num - 11; i++) {
					Gotoxy(23 + 22 * i, 21);
					printf("����������>");
					Gotoxy(7 + (i + 1) * 22, 20);
					printf("��������������������������������");
					Gotoxy(7 + (i + 1) * 22, 21);
					printf("��              ��");
					Gotoxy(7 + (i + 1) * 22, 22);
					printf("��������������������������������");

				}
			}
		}

	}
}

//���ƺ�����ר�����ڻ�����Ʊ߿�
void DProcessFrame() {
	system("cls");
	frameShow();
	Gotoxy(57 + 11, 0);
	printf("��");
	for (int i = 0; i < 29; i++) {
		Gotoxy(57 + 11, 1 + i);
		printf("��");
	}
	Gotoxy(57 + 11, 30);
	printf("��");
	Gotoxy(23, 4);
}

/*----------------------�������ӿڼ���----------------------*/
//���ܽ���1���������������ӽ���
void addDProcess() {
	char temp[80];//��Ϊ�۸�Ľ���ֵ
	char module[30];
	DProcessInfo newDProcess;
	PMLinkedListInit(&newDProcess.processList);
	Gotoxy(22+5, 7);
	printf("�������̹滮������");
	Gotoxy(84, 7);
	printf("��������ģ��������");
	Gotoxy(22, 11);
	printf("1.�������̵ǼǱ�ţ�");
	Gotoxy(22 + 20 + 4, 11);
	scanf("%s", newDProcess.DProcess_id);
	Gotoxy(22 + 20 + 4+17, 11);
	charRotation();
	Gotoxy(22, 13);
	printf("2.�������̵Ǽ����ƣ�");
	Gotoxy(22 + 20 + 4, 13);
	scanf("%s", newDProcess.DProcess_name);
	Gotoxy(22 + 20 + 4 + 17, 13);
	charRotation();
	Gotoxy(22, 15);
	printf("3.����������ʽ��ע��");
	Gotoxy(22 + 20 + 4, 15);
	scanf("%s", newDProcess.DProcess_method);
	Gotoxy(22 + 20 + 4 + 17, 15);
	charRotation();
	Gotoxy(22, 17);
	printf("4.��������ģ��������");
	Gotoxy(22 + 20 + 4, 17);
	scanf("%s", temp);
	Gotoxy(22 + 20 + 4 + 17, 17);
	charRotation();
	newDProcess.DProcess_num = atof(temp);
	getTimeNow(newDProcess.in_time);
	//Gotoxy(80, 11);
	//printf("1.����ģ��1��  ");
	//scanf("%s", test);
	for (int i = 0; i < newDProcess.DProcess_num; i++) {
		Gotoxy(80, 11+i);
		printf("%d.����ģ��%d��  ",i+1,i+1);
		scanf("%s", module);
		Gotoxy(80+18+12+1, 11 + i);
		charRotation();
		addNewPModuleListTill(&newDProcess.processList, &module);
		memset(module, 0, sizeof(module));	//����������ٸ�ֵ
	}
	Gotoxy(75, 11+ newDProcess.DProcess_num+3);
	printf("ȷ�Ϸ�����湤���������? y/n ��  ");
	int r1;
	scanf("%s", temp);
	Gotoxy(117-4, 11 + newDProcess.DProcess_num + 3);
	charRotation();
	if (temp[0] == 'y') {
		r1 = addNewDProcess(&allDProcesslist, newDProcess);
		if (r1 == -1) {
			errorTemplate(44, "�������ʧ�ܣ������ģ����Ϣ��");
			DProcessInterface();
		}
		else {
			errorTemplate(44, "������̳ɹ����ɹ���ӹ�����Ϣ��");
			DProcessInterface();
		}
	}
	//����no�������
	else if (temp[0] == 'n') {
		errorTemplate(44, "���ڷ��ع�����壬��ȷ�Ϻ����룡");
		charRotation();
		Sleep(5000);
		DProcessInterface();
	}
	//�������ȥy��n�������ַ��Ļ�
	else {
		errorTemplate(44, "��������������ȷ��Ҫ������룡");
		addDProcess();
	}
}

//���ܽ���2����ѯ�������̵Ľ���
void checkDProcess() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(48, 6);
	printf("�ѷ����������̲鿴���");
	Gotoxy(41, 14);
	printf("����������Ҫ��ѯ�Ĺ������̱�ţ�  ");
	scanf("%s", temp);
	Gotoxy(44 + 34, 14);
	charRotation();
	errorTemplate(47, "���ڲ�ѯ��ص�������Ϣ��");
	int r1 = searchDProcess(allDProcesslist, temp);
	//��������ֲ���ʧ�ܵ����
	if (r1 < 0) {
		errorTemplate(46, "��ѯʧ�ܣ�û�����������Ϣ��");
		errorTemplate(47, "�����˳���ѯ��壬���Եȣ�");
		DProcessInterface();
	}
	else {
		system("cls");
		frameShow();
		Gotoxy(48, 2);
		printf("�ѷ����������̲鿴���");
		Gotoxy(8, 4);
		printf("1.���̵ǼǱ�ţ� %s", allDProcesslist.list[r1].DProcess_id);
		Gotoxy(36, 4);
		printf("2.�������ƣ� %s", allDProcesslist.list[r1].DProcess_name);
		Gotoxy(8, 6);
		printf("3.������ʽ�� %s", allDProcesslist.list[r1].DProcess_method);
		Gotoxy(36, 6);
		printf("4.ģ�������� %d", allDProcesslist.list[r1].DProcess_num);
		Gotoxy(60, 6);
		printf("5.����ʱ�䣺 %s", allDProcesslist.list[r1].in_time);
		processFrame(allDProcesslist.list[r1].DProcess_num+2);
		ScanNewPModuleList(allDProcesslist.list[r1]);
		Gotoxy(39, 24);
		printf("�鿴���������������ֵ���ع�����壺 ");
		scanf("%s", temp);
		if (temp[0] == 'y') {
			errorTemplate(48, "���ڷ��ع���������壡");
			DProcessInterface();
		}
		else {
			errorTemplate(48, "���ڷ��ع���������壡");
			DProcessInterface();
		}	
	}
}

//���ܽ���3����������ɾ������
void deleteDProcess() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(44 + 3, 8);
	printf("����������Ϣɾ�����");
	Gotoxy(43, 11);
	printf("����������Ҫɾ�������̱�ţ�");
	scanf("%s", temp);
	Gotoxy(43 + 32, 11);
	charRotation();
	int r1 = searchDProcess(allDProcesslist, temp);
	//��������ֲ���ʧ�ܵ����
	if (r1 < 0) {
		Gotoxy(44, 13);
		printf("��ѯ����ʧ�ܣ�ȷ�Ϻ�����  ");
		charRotation();
		DProcessInterface();
	}
	else {
		Gotoxy(43, 13);
		printf("����ȷ����Ҫɾ����������Ϣ��");
		Gotoxy(44, 15);
		printf("1.�������̵ǼǱ�ţ� %s", allDProcesslist.list[r1].DProcess_id);
		Gotoxy(44, 17);
		printf("2.�������̵Ǽ����ƣ� %s", allDProcesslist.list[r1].DProcess_name);
		Gotoxy(44, 19);
		printf("3.����������ʽ��ע�� %s", allDProcesslist.list[r1].DProcess_method);
		Gotoxy(44, 21);
		printf("4.��������ģ�������� %d", allDProcesslist.list[r1].DProcess_num);
		Gotoxy(44, 23);
		printf("5.�������̵Ǽ�ʱ�䣺 %s", allDProcesslist.list[r1].in_time);
		Gotoxy(44 - 2, 28);
		printf("ȷ�Ͻ�ɾ���ù��������� y/n:  ");
		scanf("%s", temp);
		Gotoxy(44 - 2 + 33, 28);
		charRotation();
		Gotoxy(44 - 2, 29);
		if (temp[0] == 'y') {
			int r3 = delDProcess(&allDProcesslist, r1);
			FreePModuleList(&allDProcesslist, r1);
			if (r3 == -1) {
				errorTemplate(47, "ɾ��ʧ�ܣ��޷�������Ϣ��");
				Sleep(5000);
				DProcessInterface();
			}
			else {
				errorTemplate(47, "ɾ���ɹ���ϵͳ������Ϣ��");
				Sleep(1000);
				DProcessInterface();
			}
		}
		//����no�������
		else if (temp[0] == 'n') {
			printf("���ڷ��ع�����壬��ȷ�Ϻ����룡 ");
			charRotation();
			Sleep(3000);
			DProcessInterface();
		}
		//�������ȥy��n�������ַ��Ļ�
		else {
			printf("��������������ȷ��Ҫ������룡 ");
			charRotation();
			Sleep(3000);
			deleteDProcess();
		}
	}
}

//���ܽ���4���޸Ĺ���������Ϣ
void modifiDProcess() {
	system("cls");
	frameShow();
	Gotoxy(44 + 3, 5);
	printf("����������Ϣ�޸����");
	char temp[30];
	Gotoxy(43, 8);
	printf("����������Ҫ�޸ĵ����̱�ţ�");
	scanf("%s", temp);
	Gotoxy(43 + 32, 8);
	charRotation();
	int r1 = searchDProcess(allDProcesslist, temp);
	int r2 = 0, r3 = 0;
	//��������ֲ���ʧ�ܵ����
	if (r1 < 0) {
		Gotoxy(44, 10);
		printf("��ѯ����ʧ�ܣ�ȷ�Ϻ�����  ");
		charRotation();
		DProcessInterface();
	}
	else {
		Gotoxy(43, 10);
		printf("����ȷ����Ҫ�޸ĵ�������Ϣ��");
		Gotoxy(44, 12);
		printf("1.�������̵ǼǱ�ţ� %s", allDProcesslist.list[r1].DProcess_id);
		Gotoxy(44, 14);
		printf("2.�������̵Ǽ����ƣ� %s", allDProcesslist.list[r1].DProcess_name);
		Gotoxy(44, 16);
		printf("3.����������ʽ��ע�� %s", allDProcesslist.list[r1].DProcess_method);
		Gotoxy(44, 18);
		//printf("4.��������ģ�������� %d", allDProcesslist.list[r1].DProcess_num);
		//Gotoxy(44, 20);			��������ģ�������������׵ı༭
		//printf("4.�������̵Ǽ�ʱ�䣺 %.s", allDProcesslist.list[r1].in_time);
		while (1) {
			Gotoxy(44 - 2, 24);
			printf("ѡ��Ҫ�޸ĵ����ݱ�ţ� ");
			char temp[30];
			scanf("%s", temp);
			Gotoxy(44 - 2+24+16, 24);
			charRotation();
			r2 = atoi(temp);
			//����ı���ڷ�Χ֮�ڵģ�1~6��
			if (r2 >= 1 && r2 <= 5) {
				char newContent[50];
				Gotoxy(44 - 2, 26);
				printf("���޸Ĳ��ֵ�������Ϊ�� ");
				scanf("%s", newContent);
				Gotoxy(44 - 2 + 24 + 16, 26);
				charRotation();
				r3 = modifyDProcess(&allDProcesslist, r1, r2, newContent);
				if (r3 == -1) {
					Gotoxy(44 - 2, 28);
					printf("�޸�������Ϣʧ�ܣ�  ");
					charRotation();
					Sleep(3000);
					DProcessInterface();
				}
				else {
					Gotoxy(44 - 2, 28);
					printf("ѡ���޸�������Ϣ�ɹ��� ");
					charRotation();
					Sleep(3000);
					DProcessInterface();
				}
				break;
			}
			//����ı�Ų��ڷ�Χ�ڵ�
			else {
				Gotoxy(44 - 2, 26);
				printf("�������ѡ���Ŵ��� ");
				charRotation();
				Sleep(5000);
				DProcessInterface();
			}
		}
	}

}

//���ܽ���5���༭��������ģ�����
void  modifiDProcessModule() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(48, 6);
	printf("�ѷ����������̱༭���");
	Gotoxy(41, 14);
	printf("����������Ҫ�༭�Ĺ������̱�ţ�  ");
	scanf("%s", temp);
	Gotoxy(44 + 34, 14);
	charRotation();
	errorTemplate(47, "���ڲ�ѯ��ص�������Ϣ��");
	int r1 = searchDProcess(allDProcesslist, temp);
	//��������ֲ���ʧ�ܵ����
	if (r1 < 0) {
		errorTemplate(46, "��ѯʧ�ܣ�û�����������Ϣ��");
		errorTemplate(47, "�����˳��༭��壬���Եȣ�");
		DProcessInterface();
	}
	else {
		system("cls");
		frameShow();
		Gotoxy(48, 2);
		printf("�ѷ����������̱༭���");
		Gotoxy(8, 4);
		printf("1.���̵ǼǱ�ţ� %s", allDProcesslist.list[r1].DProcess_id);
		Gotoxy(36, 4);
		printf("2.�������ƣ� %s", allDProcesslist.list[r1].DProcess_name);
		Gotoxy(8, 6);
		printf("3.������ʽ�� %s", allDProcesslist.list[r1].DProcess_method);
		Gotoxy(36, 6);
		printf("4.ģ�������� %d", allDProcesslist.list[r1].DProcess_num);
		Gotoxy(60, 6);
		printf("5.����ʱ�䣺 %s", allDProcesslist.list[r1].in_time);
		processFrame(allDProcesslist.list[r1].DProcess_num + 2);
		ScanNewPModuleList(allDProcesslist.list[r1]);
		//�����￪ʼ�����趨
		int choice;
		Gotoxy(9 + 30+2, 24);
		printf("(��ʾ��1.Ϊ���ӣ�2Ϊ�޸ģ�3Ϊɾ��)");
		Gotoxy(9, 24);
		printf("������༭�������̷�ʽ��  ");
		scanf("%d", &choice);
		Gotoxy(9+28, 24);
		charRotation();
		//����˵�༭�������̷�ʽ 1������
		if (choice == 1) {
			char addContent[50];
			char before_addContent[50];
			Gotoxy(9, 26);
			printf("��������Ҫ����ģ�����ݣ� ");
			scanf("%s", addContent);
			Gotoxy(9 +41, 26);
			charRotation();
			Gotoxy(10, 29);
			printf("��ʾ����������ģ��λ�õ�ǰһ������ģ������");
			Gotoxy(9, 28);
			printf("����������ģ����õ�λ�ã�");
			scanf("%s", before_addContent);
			Gotoxy(9+41, 29);
			charRotation();
			/*-------------------------���ݽṹ����---------------------------*/
			AddPModuleListRand(&allDProcesslist, r1, &before_addContent, &addContent);
			allDProcesslist.list[r1].DProcess_num = allDProcesslist.list[r1].DProcess_num + 1;
			Gotoxy(73, 27);
			printf("���ڱ༭�ڲ���������ģ�飬���Ժ�...  ");
			charRotation();
			Sleep(2000);
			errorTemplate(46, "��������ȫ�µĹ�������ģ��ͼ��");
			frameShow();
			Gotoxy(48, 2);
			printf("�ѷ����������̲鿴���");
			Gotoxy(8, 4);
			printf("1.���̵ǼǱ�ţ� %s", allDProcesslist.list[r1].DProcess_id);
			Gotoxy(36, 4);
			printf("2.�������ƣ� %s", allDProcesslist.list[r1].DProcess_name);
			Gotoxy(8, 6);
			printf("3.������ʽ�� %s", allDProcesslist.list[r1].DProcess_method);
			Gotoxy(36, 6);
			printf("4.ģ�������� %d", allDProcesslist.list[r1].DProcess_num);
			Gotoxy(60, 6);
			printf("5.����ʱ�䣺 %s", allDProcesslist.list[r1].in_time);
			processFrame(allDProcesslist.list[r1].DProcess_num + 2);
			ScanNewPModuleList(allDProcesslist.list[r1]);
			Gotoxy(39, 24);
			printf("�鿴���������������ֵ���ع�����壺 ");
			scanf("%s", temp);
			if (temp[0] == 'y') {
				errorTemplate(48, "���ڷ��ع���������壡");
				DProcessInterface();
			}
			else {
				errorTemplate(48, "���ڷ��ع���������壡");
				DProcessInterface();
			}
		}
		//����˵�༭�������̷�ʽ 2���޸�
		else if (choice == 2) {
			char newContent[50];
			char oldContent[50];
			Gotoxy(9, 26);
			printf("��������Ҫ�滻��ģ�����ݣ� ");
			scanf("%s", oldContent);
			Gotoxy(9, 28);
			printf("�������滻��ģ���µ����ݣ� ");
			scanf("%s", newContent);
			/*-------------------------���ݽṹ����---------------------------*/
			modiPModuleListRand(&allDProcesslist, r1, &oldContent, &newContent);
			Gotoxy(73, 27);
			printf("���ڱ༭�ڲ���������ģ�飬���Ժ�...");
			charRotation();
			Sleep(2000);
			errorTemplate(46, "��������ȫ�µĹ�������ģ��ͼ��");
			system("cls");
			frameShow();
			Gotoxy(48, 2);
			printf("�ѷ����������̲鿴���");
			Gotoxy(8, 4);
			printf("1.���̵ǼǱ�ţ� %s", allDProcesslist.list[r1].DProcess_id);
			Gotoxy(36, 4);
			printf("2.�������ƣ� %s", allDProcesslist.list[r1].DProcess_name);
			Gotoxy(8, 6);
			printf("3.������ʽ�� %s", allDProcesslist.list[r1].DProcess_method);
			Gotoxy(36, 6);
			printf("4.ģ�������� %d", allDProcesslist.list[r1].DProcess_num);
			Gotoxy(60, 6);
			printf("5.����ʱ�䣺 %s", allDProcesslist.list[r1].in_time);
			processFrame(allDProcesslist.list[r1].DProcess_num + 2);
			ScanNewPModuleList(allDProcesslist.list[r1]);
			Gotoxy(39, 24);
			printf("�鿴���������������ֵ���ع�����壺 ");
			scanf("%s", temp);
			if (temp[0] == 'y') {
				errorTemplate(48, "���ڷ��ع���������壡");
				DProcessInterface();
			}
			else {
				errorTemplate(48, "���ڷ��ع���������壡");
				DProcessInterface();
			}
		}
		//����˵�༭�������̷�ʽ 3��ɾ��
		else if (choice == 3) {
			char deleContent[50];
			Gotoxy(9, 26);
			printf("��������Ҫɾ����ģ�����ݣ� ");
			scanf("%s", deleContent);
			/*-------------------------���ݽṹ����---------------------------*/
			DeletePModuleListRand(&allDProcesslist, r1, &deleContent);
			allDProcesslist.list[r1].DProcess_num = allDProcesslist.list[r1].DProcess_num - 1;
			Gotoxy(73, 27);
			printf("���ڱ༭�ڲ���������ģ�飬���Ժ�...");
			charRotation();
			Sleep(2000);
			errorTemplate(46, "��������ȫ�µĹ�������ģ��ͼ��");
			system("cls");
			frameShow();
			Gotoxy(48, 2);
			printf("�ѷ����������̲鿴���");
			Gotoxy(8, 4);
			printf("1.���̵ǼǱ�ţ� %s", allDProcesslist.list[r1].DProcess_id);
			Gotoxy(36, 4);
			printf("2.�������ƣ� %s", allDProcesslist.list[r1].DProcess_name);
			Gotoxy(8, 6);
			printf("3.������ʽ�� %s", allDProcesslist.list[r1].DProcess_method);
			Gotoxy(36, 6);
			printf("4.ģ�������� %d", allDProcesslist.list[r1].DProcess_num);
			Gotoxy(60, 6);
			printf("5.����ʱ�䣺 %s", allDProcesslist.list[r1].in_time);
			processFrame(allDProcesslist.list[r1].DProcess_num + 2);
			ScanNewPModuleList(allDProcesslist.list[r1]);
			Gotoxy(39, 24);
			printf("�鿴���������������ֵ���ع�����壺 ");
			scanf("%s", temp);
			if (temp[0] == 'y') {
				errorTemplate(48, "���ڷ��ع���������壡");
				DProcessInterface();
			}
			else {
				errorTemplate(48, "���ڷ��ع���������壡");
				DProcessInterface();
			}
		}
		//����������̷�ʽ�� ����Ĳ���1��3��Χ��
		else {
			errorTemplate(46, "��������û��������̲�����");
			modifiDProcessModule();
		}
	}

}

//���ܽ���6�����湤��������Ϣ����
void saveDProcess() {
	int r1 = allSaveDProcess();
	if (r1 == -1) {
		errorTemplate(48, "���浱ǰ��������Ϣʧ�ܣ�");
		DProcessInterface();
	}
	else {
		errorTemplate(48, "���ڱ������е�������Ϣ��");
		errorTemplate(48, "�������е�������Ϣ�ɹ���");
		DProcessInterface();
	}
}

//��Ϲ��ܽ���1�����ܺ���--��������������ȫ�µ�һ��newDProcess
int addNewDProcess(DProcessSeqList* dpsl,DProcessInfo newDProcess) {

	//�����ڲִ���������Ϣ�в����Ƿ��д˵Ǽǵ����̣�����У����� - 1����ʾ���Ǽ�ʧ��
	int r = searchDProcess(*dpsl, newDProcess.DProcess_id);
	if (r >= 0) {
		errorTemplate(48, "�������̵ǼǱ���Ѵ��ڣ�");
		DProcessInterface();
	}
	//��������ռ䲻����������ռ�
	if (dpsl->length >= dpsl->size) {
		DProcessInfo* t = dpsl->list;
		dpsl->list = (DProcessInfo*)malloc(2 * dpsl->size * sizeof(DProcessInfo));
		if (dpsl->list == NULL) {
			errorTemplate(48, "������Ч���ڴ����ʧ�ܣ�");
			DProcessInterface();
		}
		dpsl->size = 2 * dpsl->size;
		for (int i = 0; i < dpsl->length; i++)
			DProcessCopy(&(dpsl->list[i]),t[i],newDProcess.DProcess_num);//�����num��ȫ������newDProcess��num�滻
		free(t);
	}
	//	��ԭ�����ǼǱ�Ų��뵽���ʵ�λ�ã���֤��ԭ�Ϲ�Ӧ��ҵ�������
	int i = 0;
	for (i = dpsl->length - 1; i >= 0; i--) {
		r = strcmp(dpsl->list[i].DProcess_id, newDProcess.DProcess_id);
		if (r > 0)
			DProcessCopy(&(dpsl->list[i + 1]), dpsl->list[i], newDProcess.DProcess_num);
		else
			break;

	}
	DProcessCopy(&(dpsl->list[i + 1]), newDProcess, newDProcess.DProcess_num);
	dpsl->length++;
	//��ӳɹ�����0
	return 0;
}

//��Ϲ��ܽ���123�����ܺ���--�ڹ������̵ǼǱ��и��ݵǼ����̱�Ž��в��ң�û�иñ����ռ�ÿ���򷵻�-1������з���ֵ���ǸõǼǱ���ѱ�ռ�ã������㷨�ö��ֲ��ҷ���
int searchDProcess(DProcessSeqList dpsl, char* DPsn) {	
	int low = 0;
	int high = dpsl.length - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;		//���ֲ��ҷ�
		if (strcmp(dpsl.list[mid].DProcess_id, DPsn) == 0)
			return mid;
		else
			if (strcmp(dpsl.list[mid].DProcess_id, DPsn) < 0)
				low = mid + 1;
			else
				high = mid - 1;
	}
	return -1;
}

//��Ϲ��ܽ���123�����ܺ���--��ȿ��������Ĺ�������ͼֽ��Ϣ,����num�����������õ�ģ����
void DProcessCopy(DProcessInfo* to, DProcessInfo from,int num) {
	PMLinkedListInit(&to->processList);		//ǧ�������ǳ�ʼ��
	strcpy(to->DProcess_id, from.DProcess_id);
	strcpy(to->DProcess_name, from.DProcess_name);
	strcpy(to->DProcess_method, from.DProcess_method);
	PModuleNode *temp = from.processList.head->next;
	for (int i = 0; i < num; i++) {
		addNewPModuleListTill(&to->processList, temp->PModule);
		temp = temp->next;
	}
	to->DProcess_num = from.DProcess_num;
	strcpy(to->in_time, from.in_time);
}

//��Ϲ��ܽ���2�����ܺ���--�ڹ������̹������ɾ����index��Ԫ�أ�ɾ���㷨Ϊ�Ѻ��������Ԫ�ظ���ǰ�棬����0��ʾɾ���ɹ�
int delDProcess(DProcessSeqList* dpsl, int index) {
	if (dpsl->length <= 0) {
		errorTemplate(48, "�����������ݿ���ϢΪ�գ�");
		DProcessInterface();
		return -1;
	}
	if (index < 0 || index >= dpsl->length) {
		errorTemplate(47, "��Ҫɾ�������̳���ִ�з�Χ��");
		DProcessInterface();
		return -1;
	}

	for (int i = index + 1; i < dpsl->length; i++) {
		DProcessCopy(&(dpsl->list[i - 1]), dpsl->list[i], dpsl->list[i].DProcess_num);
	}
	dpsl->length--;
	return 0;
}

//��Ϲ��ܽ���3�����ܺ������ڹ������̹����dpsl���޸ĵ�index���������ε���Ϣ��type��ʾҪ�޸ĵ����ͣ�ȡֵ1���������̵ǼǱ�ţ���2���������̵Ǽ����ƣ���3������������ʽ��ע����4����������ģ��������,5���������̵Ǽ�ʱ�䣩����info��ʾ�µ���Ϣֵ���޸ĳɹ�����0�����򷵻�1
int modifyDProcess(DProcessSeqList* dpsl, int index, int type, char* info) {
	if (index < 0 && index >= dpsl->length) {
		errorTemplate(47, "��Ҫɾ�������̳���ִ�з�Χ��");
		DProcessInterface();
	}
	switch (type) {
		case 1: strcpy(dpsl->list[index].DProcess_id, info); break;
		case 2: strcpy(dpsl->list[index].DProcess_name, info); break;
		case 3: strcpy(dpsl->list[index].DProcess_method, info); break;
		//case 4: dpsl->list[index].DProcess_num = atof(info); break;
		case 4: strcpy(dpsl->list[index].in_time, info); break;
		default: {
			errorTemplate(48, "�޸ĵ�������Ϣ�������");
			DProcessInterface();
		}
	}
	return 0;
}

//��Ϲ��ܽ���5�����ܺ���--������ϵͳ������ɾ�����ĺ����Ϣ�������ݿ���
int allDProcessInfoSaveToFile(DProcessSeqList dpsl, char* filename) {
	FILE *fp;
	char strline[80];
	if ((fp = fopen(filename, "w")) == NULL) {
		errorTemplate(47, "�������̵�������ݿⲻ���ڣ�");
		DProcessInterface();
	}

	for (int i = 0; i < dpsl.length; i++) {
		fputs(dpsl.list[i].DProcess_id, fp);
		fputc('\n', fp);
		fputs(dpsl.list[i].DProcess_name, fp);
		fputc('\n', fp);
		fputs(dpsl.list[i].DProcess_method, fp);
		fputc('\n', fp);
		sprintf(strline, "%d", dpsl.list[i].DProcess_num);
		fputs(strline, fp);
		fputc('\n', fp);
		fputs(dpsl.list[i].in_time, fp);
		fputc('\n', fp);
		/*-------------------------------------------*/
		PModuleNode *temp = dpsl.list[i].processList.head;	//����һ����ʱ������ָ��ͷ
	//���п����Ǹýڵ�������ڲ������κε�ģ����Ϣ
		while (temp != NULL) {
			PModuleNode* pt = temp;
			temp = temp->next;		    //tempָ����һ���ĵ�ַ ��ʵ�������ģ�鲻���ƶ�����
			fputs(pt->PModule, fp);
			fputc('\n', fp);
		}
	}
	fclose(fp);
	return 0;
}

//��Ϲ��ܽ���5�����ܺ���--�����ͱ���ִ���Ϣ���ļ���
int allSaveDProcess() {
	int r1 = allDProcessInfoSaveToFile(allDProcesslist, "������������ģ����Ϣ��Ϣ���ݿ�.txt");  //�������еĹ���������Ϣ���ļ���
	if (r1 == -1) {
		errorTemplate(48, "���浱ǰ��������Ϣʧ�ܣ�");
		DProcessInterface();
	}
	return 0;
}

//����ӿں���������Աר���ڲ�ѯ�ִ����ԭ����Ϣ����
void checkDProcessAdmin() {
	system("cls");
	frameShow();
	char temp[30];
	Gotoxy(48, 6);
	printf("�ѷ����������̲鿴���");
	Gotoxy(41, 14);
	printf("����������Ҫ��ѯ�Ĺ������̱�ţ�  ");
	scanf("%s", temp);
	Gotoxy(44 + 34, 14);
	charRotation();
	errorTemplate(47, "���ڲ�ѯ��ص�������Ϣ��");
	int r1 = searchDProcess(allDProcesslist, temp);
	//��������ֲ���ʧ�ܵ����
	if (r1 < 0) {
		errorTemplate(46, "��ѯʧ�ܣ�û�����������Ϣ��");
		errorTemplate(49, "���ڷ��ع���Ա����壡");
		adminLeaderInterface();
	}
	else {
		system("cls");
		frameShow();
		Gotoxy(48, 2);
		printf("�ѷ����������̲鿴���");
		Gotoxy(8, 4);
		printf("1.���̵ǼǱ�ţ� %s", allDProcesslist.list[r1].DProcess_id);
		Gotoxy(36, 4);
		printf("2.�������ƣ� %s", allDProcesslist.list[r1].DProcess_name);
		Gotoxy(8, 6);
		printf("3.������ʽ�� %s", allDProcesslist.list[r1].DProcess_method);
		Gotoxy(36, 6);
		printf("4.ģ�������� %d", allDProcesslist.list[r1].DProcess_num);
		Gotoxy(60, 6);
		printf("5.����ʱ�䣺 %s", allDProcesslist.list[r1].in_time);
		processFrame(allDProcesslist.list[r1].DProcess_num + 2);
		ScanNewPModuleList(allDProcesslist.list[r1]);
		Gotoxy(39, 24);
		printf("�鿴���������������ֵ���ع�����壺 ");
		scanf("%s", temp);
		if (temp[0] == 'y') {
			errorTemplate(49, "���ڷ��ع���Ա����壡");
			adminLeaderInterface();
		}
		else {
			errorTemplate(49, "���ڷ��ع���Ա����壡");
			adminLeaderInterface();
		}
	}
}