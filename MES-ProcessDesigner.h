#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>

/*-----------------------------------------------------------*/

//���ݽṹ����1-����ÿ���ṹ��ڵ�
typedef struct node{
	char PModule[30];		//������,���ڴ������ģ��ֵ
	struct node* next;	//ָ����(ָ��ڵ��ָ�룩
}PModuleNode;

//������ṹ��
typedef struct {
	PModuleNode* head;
	PModuleNode* rear;
	int count;
}PMLinkedList;

//����������Ʒ���������Ϣ
typedef  struct  DProcess {
	char DProcess_id[10];			//����������ƹ�����
	char DProcess_name[50];			//�������̵Ǽ����ƣ��磺���-�������̣�
	char DProcess_method[50];		//�������������豸�����ߡ������ӹ����Ʋ�ͬ��
	int DProcess_num;				//������������������ģ�鹤����
	char in_time[20];				//�����������̵Ǽ�ʱ��
	PMLinkedList processList;
}DProcessInfo;

//���ö�̬����˳�����Ϊ���ݽṹ��������еĹ���������ƹ�����Ϣ   
typedef struct {
	DProcessInfo*  list;
	int length;		//��̬����˳���ĳ���
	int size;		//��̬����˳���ĳ���2
}DProcessSeqList;

struct coordinate {	//ר��������¼�������������ֵ
	int x;			//Gotoxy�Ĳ���x
	int y;			//Gotoxy�Ĳ���x
};

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