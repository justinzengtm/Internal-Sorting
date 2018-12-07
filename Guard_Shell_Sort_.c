#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20
typedef int ElemType;

//�������еĴ洢�ṹ
typedef struct SqlList *PtrlSqlList;
struct SqlList {
	ElemType arr[MaxSize+1];
	int length;
};

//��������
void Insert_Array(PtrlSqlList P, int K); //���в���Ԫ��
void PrintList(PtrlSqlList P, int count); //�������
int GetLength(PtrlSqlList P); //������еĳ���
void Shell_Sort(PtrlSqlList P, int lenght); //ϣ������

int main(int argc, char const* argv[]) 
{
	int data=0;
 
	PtrlSqlList P;
	P=(PtrlSqlList)malloc(sizeof(struct SqlList));
	P->arr[0]=0; /*�����0λ����Ϊ�ڱ�*/
	P->arr[1]=-1;
	
	printf("\n�봴������:");
	while (data!=-1) {
		scanf("%d", &data); 
		Insert_Array(P, data);
	}
	
	printf("\nԭ����Ϊ:");
	PrintList(P, 0);
	//������еĳ���
	P->length=GetLength(P);
	printf("\n\n���г���Ϊ:%d\n", P->length);
	//ϣ������
	Shell_Sort(P, P->length);
	printf("ϣ�������:");
	PrintList(P, 0);
	
	return 0;
}

//���в���Ԫ��
void Insert_Array(PtrlSqlList P, int K) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		i++;
	}
	P->arr[i]=K;
	P->arr[i+1]=-1;
	
	return;
}

//�������
void PrintList(PtrlSqlList P, int count) 
{
	int i=1;
	int j; 
	if (count!=0) {
		printf("��%d������:", count);
		while (P->arr[i]!=-1) {
		printf("%d  ", P->arr[i]);
		i++;
		}
	} else {
		while (P->arr[i]!=-1) {
		printf("%d  ", P->arr[i]);
		i++;
	}
	}
}

//������г���
int GetLength(PtrlSqlList P) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		i++;
	}
	
	return (i-1);
}


//ϣ������ӿ� 
void Shell_Sort(PtrlSqlList P, int length) 
{
	int increases, j, k, ListLength, Si;
	int count=0;
	//Sedgewick��������
	//int Increment[]={929, 505, 209, 109, 41, 19, 5, 1, 0,}; 
	int Increment[]={5, 3, 1,};
	ListLength=GetLength(P);
	
	//���������Ҫ����������
	for (Si=0; Increment[Si]>=ListLength; Si++);
	
	printf("\n��Ҫ�õ�����������Ϊ:");
	for (j=Si; Increment[j]>=1; j++) {
		printf("%d ", Increment[j]);
	}
	
	printf("\n\nϣ���������:\n");
	for (increases=Increment[Si]; increases>=1; increases=Increment[++Si]) {
		//��������
		for (j=increases; j<=ListLength; j++) {
			//�����һ����С��ǰһ�������������
			if (P->arr[j]<P->arr[j-increases]) {
				P->arr[0]=P->arr[j]; //�ѽ�С������ֵ���ڱ��ݴ�
				for (k=j-increases; k>0 && P->arr[0]<P->arr[k]; k-=increases) {
					//���P->arr[0]<P->arr[k],���ڱ���Ԫ�ر�ĳһ��������Ԫ��С�Ļ�
					P->arr[k+increases]=P->arr[k]; //��¼����,�ҳ�����λ��
				} 
				P->arr[k+increases]=P->arr[0];
			}
		}
		count++;
		PrintList(P, count);
		printf("\n\n");
	}
}
