#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
//#define BucketVolume 11
#define ElemType int

/*
 *ʱ�䣺2018/12/5
 *�㷨��Ͱ����
 *ʵ�֣�justinzeng
 */
 
//�������еĴ洢�ṹ
typedef struct SqlList *PtrlSqlList;
struct SqlList {
	ElemType arr[MaxSize+1]; //��������
	int length; //�������еĳ��� 
};

//Ͱ�Ĵ洢�ṹ
typedef struct Bucket *ListBucket;
struct Bucket {
	PtrlSqlList P[MaxSize+2];
}; 

//��������
PtrlSqlList InitialList(); //���г�ʼ��
ListBucket InitialListBucket(); //Ͱ�ĳ�ʼ�� 
void Insert_Array(PtrlSqlList P, ElemType K); //���в���Ԫ�� 
void Insert_Bucket(ListBucket B, ElemType K); //Ͱ����Ԫ��
void PrintList(PtrlSqlList P, int count); //�������
void PrintBucket(ListBucket B); //�������Ͱ����������� 
int GetListLength(PtrlSqlList P); //�������г���
void Bucket_Sort(PtrlSqlList P, int N); //Ͱ����
 
int main(int argc, char const *argv[]) 
{
	ElemType data=0;
	
	//����һ����������
	PtrlSqlList P=InitialList();
	printf("�봴����������:");
	while (data!=-1) {
		scanf("%d", &data);
		if (data!=-1) {
			Insert_Array(P, data);
		}
	}
	
	//����������п���
	printf("\n��������Ϊ:");
	PrintList(P, 0); 
	//������г��� 
	P->length=GetListLength(P);
	printf("\n�������г���Ϊ: %d\n\n", P->length);
	
	//Ͱ����
	Bucket_Sort(P, P->length);
	
	return 0;
}

//���г�ʼ��
PtrlSqlList InitialList()
{
	PtrlSqlList P=(PtrlSqlList)malloc(sizeof(struct SqlList));
	P->arr[0]=-1;	
	P->length=0; //��ʼ�����г���Ϊ0,�����ڱ�
	
	return P; 
} 

 //Ͱ�ĳ�ʼ��
ListBucket InitialListBucket()
{
	int i=0;
	ListBucket Bucket=(ListBucket)malloc(sizeof(struct Bucket));
	
	//Ͱ��ÿһ�������ʼ�� 
	for (i=0; i<=MaxSize+2; i++) {
		Bucket->P[i]=InitialList();
	} 

	return Bucket;
}

//���в���Ԫ��
void Insert_Array(PtrlSqlList P, ElemType K)
{
	int i=0;
	
	while (P->arr[i]!=-1) {
		i++;
	}
	P->arr[i]=K;
	P->arr[i+1]=-1;
} 

//Ͱ����Ԫ��
void Insert_Bucket(ListBucket B,ElemType K) 
{
	Insert_Array(B->P[K], K);
	
	return; 
}

//�������
void PrintList(PtrlSqlList P, int count)
{
	int i=0;
	
	if (count!=0) {
		printf("��%d������:", count);
		while (P->arr[i]!=-1) {
			printf("%d ", P->arr[i]);
			i++;
		}
	} else {
		while (P->arr[i]!=-1) {
			printf("%d ", P->arr[i]);
			i++;
		}
	}
	
	return;
} 

//�������Ͱ�����������
void PrintBucket(ListBucket B)
{
	int i=0; 
	
	printf("���Ͱ:"); 
	for (i=0; i<MaxSize+2; i++) {
		PrintList(B->P[i], 0);
	}
	
	return;
} 

//�������еĳ���
int GetListLength(PtrlSqlList P) 
{
	int length=0;
	
	while (P->arr[length]!=-1) {
		length++;
	}
	
	return length;
} 

//Ͱ����
void Bucket_Sort(PtrlSqlList P, int N) 
{
	int i;
	//��ʼ��һ��Ͱ 
	ListBucket B=InitialListBucket();
	
	//�������з���Ͱ�� 
	for (i=0; i<N; i++) {
		Insert_Array(B->P[P->arr[i]], P->arr[i]);
	}
	
	//�������Ͱ�����������
	PrintBucket(B);
	
	return;
} 
