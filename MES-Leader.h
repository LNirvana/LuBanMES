#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>

//ԭ�Ϲ�Ӧ��ҵ��Ϣ
typedef  struct  MCom {
	char MCom_id[10];				//ԭ�Ϲ�Ӧ��ҵ���
	char MCom_name[50];			//ԭ�Ϲ�Ӧ��ҵ����
	char MCom_location[20];			//ԭ�Ϲ�Ӧ��ҵ���ڵ�
	char MCom_material[20];				//ԭ�Ϲ�Ӧ��ҵ�ṩ��Ʒ
	float MCom_price;				//ԭ�Ϲ�Ӧ��ҵ��Ӧ�۸�
	char in_time[20];				//ǩԼ��ҵʱ��
}MComInfo;

//ԭ�Ϲ�Ӧ��ҵ��Ϣ
typedef  struct  PCom {
	char PCom_id[10];				//��Ʒ�ɹ���ҵ���
	char PCom_name[50];			//��Ʒ�ɹ���ҵ����
	char PCom_location[20];			//��Ʒ�ɹ���ҵ���ڵ�
	char PCom_material[20];				//��Ʒ�ɹ���ҵ�ṩ��Ʒ
	float PCom_price;				//��Ʒ�ɹ���ҵ��Ӧ�۸�
	char in_time[20];				//ǩԼ��Ʒ�ɹ���ҵʱ��
}PComInfo;

//���ö�̬����˳�����Ϊ���ݽṹ��������е�ԭ�Ϲ�Ӧ��ҵ��Ϣ   
typedef struct {
	MComInfo*  list;
	int length;		//��̬����˳���ĳ���
	int size;		//��̬����˳���ĳ���2
}MComsSeqList;

//���ö�̬����˳�����Ϊ���ݽṹ��������еĲ�Ʒ�ɹ���ҵ��Ϣ   
typedef struct {
	PComInfo*  list;
	int length;		//��̬����˳���ĳ���
	int size;		//��̬����˳���ĳ���2
}PComsSeqList;

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
//��Ϲ��ܽ���123�����ܺ���--�ڲ�Ʒ�ɹ���ҵ���и���ǩԼ��ҵ��Ž��в��ң�û�д���ҵ�򷵻�-1������з���ֵ���Ǹò�Ʒ�ɹ���ҵ�ı�ţ������㷨�ö��ֲ��ҷ���
int searchPCom(PComsSeqList pcsl, char* PCsn);
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

//��Ϲ��ܽ���5�����ܺ���--������ϵͳ������ɾ�����ĺ����Ϣ�������ݿ���
int allMComsInfoSaveToFile(MComsSeqList mcsl, char* filename);
//��Ϲ��ܽ���5�����ܺ���--������ϵͳ������ɾ�����ĺ����Ϣ�������ݿ���
int allPComsInfoSaveToFile(PComsSeqList pcsl, char* filename);
//��ͨ�ã���Ϲ��ܽ���5�����ܺ���--�����ͱ��������Ϣ���ļ���
int allSave(int type);