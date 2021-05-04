#include<stdio.h>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include <time.h>

//�ɹ�����������Ϣ
typedef  struct  PSale {
	char PSale_id[10];				//�ɹ���Ʒ�����ǼǱ��
	char PSale_name[50];			//�ɹ���Ʒ�Ǽ�����
	char PSale_destination[50];		//�ɹ�����������Ŀ�ĵ�
	char PSale_company[60];			//�ɹ�����������ҵ����
	float PSale_num;				//�ɹ���Ʒ������������
	char in_time[20];				//�ɹ����������Ǽ�ʱ��
}PSaleInfo;

//���ö�̬����˳�����Ϊ���ݽṹ��������еĲɹ�����������Ϣ   
typedef struct {
	PSaleInfo*  list;
	int length;		//��̬����˳���ĳ���
	int size;		//��̬����˳���ĳ���2
}PSalesSeqList;

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

//��Ϲ��ܽ���5�����ܺ���--������ϵͳ������ɾ�����ĺ����Ϣ�������ݿ���
int allPSalesInfoSaveToFile(PSalesSeqList pssl, char* filename);

//��Ϲ��ܽ���5�����ܺ���--�����ͱ���ɹ�������Ϣ���ļ���
int allSaveSale();