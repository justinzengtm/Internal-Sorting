#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20
typedef int ElemType;

/*���ż�¼�Ĵ洢�ṹ*/
typedef struct SqList *PtrlSqList;
struct SqList{
	ElemType arr[MaxSize+1]; /*r[0]��Ϊ�ڱ�*/
	int length; /*˳���ĳ���*/ 
}; /*˳�������*/

/*��������*/
PtrlSqList CreatList(); /*���еĳ�ʼ��*/
void Insert_Array(PtrlSqList P, int K); /*���в���Ԫ��*/
void PrintList(PtrlSqList P, int count); /*�������*/
int GetListLength(PtrlSqList P); /*�������еĳ���*/
void Merge_Sort(PtrlSqList P, int length); /*�鲢����ӿں���*/
void CircleMsort(PtrlSqList P, PtrlSqList M, int L, int RightEnd); /*ѭ���鲢����*/
void Merge(PtrlSqList P, PtrlSqList M, int L, int R, int RightEnd); /*�鲢����*/

int main(int argc, char const* argv[])
{
	ElemType data;
	
	/*����һ����������*/
	PtrlSqList P=CreatList();
	printf("�봴����������:");
	while (data!=-1) {
		scanf("%d", &data);
		if (data!=-1) {
			Insert_Array(P, data);
		}
	}  
	/*��ô������еĳ���*/
	P->length=GetListLength(P);
	printf("�������г���Ϊ��%d\n\n", P->length);
	/*���һ�´�������*/
	printf("��������Ϊ:");
	PrintList(P, 0);
	
	printf("\n\nѭ���鲢�������:\n");
	Merge_Sort(P, P->length);
	
	printf("\n�鲢���������:");
	PrintList(P, 0);
	
	return 0;
}
 
 /*���еĳ�ʼ��*/
PtrlSqList CreatList() 
{
	PtrlSqList P=(PtrlSqList)malloc(sizeof(struct SqList));
	P->arr[0]=MaxSize; 
	P->arr[1]=-1;
	P->length=0; 
	
	return P; 
}

/*���в���Ԫ��*/
void Insert_Array(PtrlSqList P, int K)
{
	int i=1;
	while (P->arr[i]!=-1) {
		i++;
	}
	P->arr[i]=K;
	P->arr[i+1]=-1;
}

/*�������*/
void PrintList(PtrlSqList P, int count) 
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

/*�������еĳ���*/
int GetListLength(PtrlSqList P) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		i++;
	}

	return (i-1);
}

/*�鲢����ӿں���*/
void Merge_Sort(PtrlSqList P, int length) 
{
	int i=0;
	int ListLength=1; /*��ʼ���������г���Ϊ1,Ҳ����˵ÿһ��Ԫ�ض������������*/
	/*����һ������ռ�����������*/
	PtrlSqList M=CreatList();
	for (i=0; i<=MaxSize; i++) {
		M->arr[i]=-1;
	}

	if (M->length!=MaxSize) {
		/*��ʼѭ���鲢����*/
		/*����ȥ�Ĳ���:��������P,�����������M,�ʼ���λ��1,����λ��length*/
		while (ListLength<length) {
			CircleMsort(P, M, length, ListLength);
			ListLength*=2;
			CircleMsort(M, P, length, ListLength);
			ListLength*=2;
		} 
		/*��������ͷŵ���ʱ����ռ�M*/
		free(M); 
	} else {
		/*����鲢����û����,M��û�ռ���*/ 
		printf("�ռ䲻��");
	}
}

/*ѭ���鲢����*/
void CircleMsort(PtrlSqList P, PtrlSqList M, int N, int length) 
{
	/*����N�������������еĳ���,length�ǵ�ǰ�������еĳ���*/
	int i, j;
	
	for (i=1; i<=N-2*length; i+=2*length) {
		Merge(P, M, i, i+length, i+2*length-1); //!!
		/*i+length<N��ʾ���ʣ����������*/
		if (i+length<N) {
			Merge(P, M, i, i+length, N);
		} else {
			/*Ҳ����ֻʣ��һ����������,�������������в��ȳ�*/
			//������ѭ��������Ǹ����ȳ����н���ȥ. 
			for (j=i; j<N; j++) {
				M->arr[j]=P->arr[j];
			}
		}
	}
}

/*�鲢����*/
void Merge(PtrlSqList P, PtrlSqList M, int L, int R, int RightEnd) 
{
	/*L��������е���ʼλ��,R���ұ����е���ʼλ��,RightEnd���ұ����е��յ�λ��.*/
	/*L��R��ָ���������е�ָ��*/
	int LeftEnd, ElementNum, Tmp, i;
	
	LeftEnd=R-1; /*�����е��յ�λ�����ұ�������ʼλ��-1*/ 
	Tmp=L; /*Tmp��¼��һ�����е���ʼλ��,������1,������������ʱ����ռ���������.*/
	ElementNum=RightEnd-L+1; /*!!!!*/
	printf("ElementNum=%d L=%d LeftEnd=%d R=%d RightEnd=%d\t", ElementNum, L, LeftEnd, R, RightEnd);
		
	/*���������û�����һ��Ԫ�� && �ұ�����Ҳû�����һ��Ԫ��ʱ,�����鲢����*/ 
	while (L<=LeftEnd && R<=RightEnd) {
		/*���������еĵ�һ��Ԫ�ؿ�ʼ�������Ƚ�*/
		if (P->arr[L]<=P->arr[R]) {
			M->arr[Tmp++]=P->arr[L++]; 
		} else {
			M->arr[Tmp++]=P->arr[R++];
		} 
	}
	
	/*������һ��Ԫ�ز������,����һ�����е�ʣ��Ԫ��ȫ�����뵽����ռ���*/
	while (L<=LeftEnd) {
		M->arr[Tmp++]=P->arr[L++];
	} 
	while (R<=RightEnd) {
		M->arr[Tmp++]=P->arr[R++];
	}
	/*�Ѷ���ռ����ź�������и��ƻ��û���������*/
	for (i=0; i<ElementNum && RightEnd>0; i++, RightEnd--) {
		P->arr[RightEnd]=M->arr[RightEnd];
	}  
	PrintList(P, 0);
	printf("\n\n"); //������
}
