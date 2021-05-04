#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>

typedef int Elemtype;

//ԭ����������Ϣ
typedef  struct  MWare {
	char MWare_id[10];				//ԭ������ִ�������
	char MWare_name[50];			//ԭ������ִ��Ǽ�����
	char MWare_location[50];		//���ԭ�ϲ��أ���׷�ݣ�
	char MWare_company[60];			//ԭ�Ϲ�Ӧ��ҵ���ƵǼ�
	float MWare_num;				//ԭ�������������
	char in_time[20];				//ԭ������ִ��Ǽ�ʱ��
}MWareInfo;

//���ö�̬����˳�����Ϊ���ݽṹ��������еĲִ����ԭ�Ϲ�����Ϣ   
typedef struct {
	MWareInfo*  list;
	int length;		//��̬����˳���ĳ���
	int size;		//��̬����˳���ĳ���2
}MWaresSeqList;

/* ����������ṹ */
typedef struct BTNode {
	Elemtype data;
	struct BTNode *lchild, *rchild;
}BTree;

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
//��Ϲ��ܽ���5�����ܺ���--������ϵͳ������ɾ�����ĺ����Ϣ�������ݿ���
int allMWaresInfoSaveToFile(MWaresSeqList mwsl, char* filename);
//��Ϲ��ܽ���5�����ܺ���--�����ͱ���ִ���Ϣ���ļ���
int allSaveWare();
//����ӿں���������Աר���ڲ�ѯ�ִ����ԭ����Ϣ����
void queryMWareAdmin();