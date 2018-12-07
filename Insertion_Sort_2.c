#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20
typedef int ElemType;

//�������еĴ洢�ṹ
typedef struct SqList *PtrlSqList;
struct SqList {
	ElemType arr[MaxSize+1];
	int length;
};

//��������
void Insert_Array(PtrlSqList P, int K); //���в���Ԫ��
void PrintList(PtrlSqList P); //�������
int GetLength(PtrlSqList P); //������еĳ���
void Insert_Sort(PtrlSqList P, int lenght); //ֱ�Ӳ�������

int main(int argc, char const* argv[]) 
{
	int data=0;
	PtrlSqList P;
	P=(PtrlSqList)malloc(sizeof(struct SqList));
	P->arr[0]=0; //�����0λ����Ϊ�ڱ�
	P->arr[1]=-1;
	
	printf("\n�봴������:");
	while (data!=-1) {
		scanf("%d", &data); 
		Insert_Array(P, data);
	}
	
	printf("\nԭ����Ϊ:");
	PrintList(P);
	//������еĳ���
	P->length=GetLength(P);
	printf("\n���г���Ϊ:%d\n", P->length);
	//ֱ�Ӳ�������
	Insert_Sort(P, P->length);
	printf("\nֱ�Ӳ��������:");
	PrintList(P);
	
	return 0;
}

//���в���Ԫ��
void Insert_Array(PtrlSqList P, int K) 
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
void PrintList(PtrlSqList P) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		printf("%d  ", P->arr[i]);
		i++;
	}
	
	return;
}

//������г���
int GetLength(PtrlSqList P) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		i++;
	}
	
	return (i-1);
}

//ֱ�Ӳ�������
void Insert_Sort(PtrlSqList P, int length) 
{
	int i, j;
	
	printf("\nֱ�Ӳ����������:\n");
	for (i=2; i<=length; i++) {
		//�����һ����С��ǰһ���� 
		if (P->arr[i]<P->arr[i-1]) {
			P->arr[0]=P->arr[i]; //�Ȱѽ�С������ֵ���ڱ�
			P->arr[i]=P->arr[i-1]; //�ϴ��������һλ
			for (j=i-2; P->arr[0]<P->arr[j]; j--) {
				//��i-2��ʼ,������ڱ������,�ͺ���һλ,�ڳ�λ��
				P->arr[j+1]=P->arr[j];
			} 
			//��forѭ�������,���ڱ����ֵ��������һλ,�ڳ�����ȷ��λ�ø��ڱ�����
			P->arr[j+1]=P->arr[0]; 
			PrintList(P);
			printf("\n");
		}
	}
}
