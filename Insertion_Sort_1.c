#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20
typedef int ElemType;

//���ż�¼�Ĵ洢�ṹ
typedef struct SqlList *PtrlSqlList;
struct SqlList{
	ElemType arr[MaxSize+1]; //r[0]��Ϊ�ڱ�
	int length; //˳���ĳ���
}; //˳�������

//��������
void Insert_Array(PtrlSqlList P, int K); //���в���Ԫ��
void Insertion_Sort(PtrlSqlList P, int N); //��������
void PrintList(PtrlSqlList P); //�������
int GetListLength(PtrlSqlList P); //�������еĳ���

int main(int argc, char const* argv[]) 
{
	int data=0;
	PtrlSqlList P;
	P=(PtrlSqlList)malloc(sizeof(struct SqlList));
	P->arr[1]=-1;
	P->arr[0]=0;
	
	printf("\n�봴������:");
	while (data!=-1) {
		scanf("%d", &data);
		Insert_Array(P, data);
	} 
	
	printf("\nԭ����Ϊ:");
	PrintList(P);
	//������г���
	P->length=GetListLength(P);
	printf("\n���г���Ϊ = %d\n", P->length);
	//��������
	Insertion_Sort(P, P->length);
	//�������
	printf("\nֱ�Ӳ��������:");
	PrintList(P); 
	
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
}

//�������
void PrintList(PtrlSqlList P) 
{
	int i=1; 
	while (P->arr[i]!=-1) {
		printf("%d\t", P->arr[i]);
		i++;
	}
} 

//ֱ�Ӳ�������
void Insertion_Sort(PtrlSqlList P, int N) 
{
	int i, j, Tmp, flag;
	printf("\nֱ�Ӳ����������:\n");
	for (i=2; i<=N; i++) {
		Tmp=P->arr[i]; /*������������ó�Ԫ��*/
		printf("Tmp=%d\n", Tmp);
		for (j=i; j>1 && P->arr[j-1]>Tmp; j--) {
			P->arr[j]=P->arr[j-1]; /*����Ųһλ*/
		}
		P->arr[j]=Tmp; //����ҵ���Tmp�����������Ų��,������ȷ��λ�þͲ���
		PrintList(P); //��Ϊ������к���,�˴�ÿ�����һ������������
		printf("\n");
	}
} 

//�������еĳ���
int GetListLength(PtrlSqlList P) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		i++;
	}

	return (i-1);
}
