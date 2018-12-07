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
void Shell_Sort(PtrlSqlList P, int N); //ϣ������ӿ�
void PrintList(PtrlSqlList P, int count); //�������
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
	
	printf("\n\nԭ����Ϊ:");
	PrintList(P, 0);
	//������г���
	P->length=GetListLength(P);
	printf("\n\n���г���Ϊ = %d\n", P->length);
	//ϣ������
	Shell_Sort(P, P->length);
	//�������
	printf("\nϣ�����������:");
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

//ϣ������ӿ�
void Shell_Sort(PtrlSqlList P, int N) 
{
	int increases, j, Tmp, k, Si;
	int count=0; //��������ļ���
	//Sedgewick��������
	//int Increment[]={929, 505, 209, 109, 41, 19, 5, 1, 0,}; 
	int Increment[]={5, 3, 1,}; 
	//��ô������еĳ���,��������ʹ���������еĳ���
	int ListLength=GetListLength(P);
	
	//�����ó���Ҫ�������еĳ���
	for (Si=0; Increment[Si]>=ListLength; Si++);
	//��ɺ�õ��ľ���ֻ��Ҫ�õ�Increment[Si]��֮ǰ��Ԫ��
	
	printf("\n��Ҫ�õ�����������Ϊ:");
	for (j=Si; Increment[j]>=1; j++) {
		printf("%d ", Increment[j]);
	}
	printf("\n\nϣ�������������:\n");
	//ѡ������,������������1ʱ,����һ������
	for (increases=Increment[Si]; increases>=1; increases=Increment[++Si]) {
		//ֱ�Ӳ�������
		for (k=increases; k<=ListLength; k++) {
			Tmp=P->arr[k]; //������������ó�Ԫ��
			for (j=k; j>=increases && P->arr[j-increases]>Tmp; j-=increases) {
				P->arr[j]=P->arr[j-increases]; //����Ųһλ
			}
			P->arr[j]=Tmp; //����ҵ���Tmp�����������Ų��,������ȷ��λ�þͲ���
		}
		count++;
		PrintList(P, count); //��Ϊ������к���,�˴�ÿ�����һ������������ 
		printf("\n");
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
