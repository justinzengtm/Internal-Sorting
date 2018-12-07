#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ElemType int
#define MaxSize 100
#define MaxData 1000 

/*�������еĴ洢�ṹ*/
typedef struct SqList *PtrlSqList;
struct SqList{
	ElemType arr[MaxSize+1]; /*arr[0]��Ϊ�ڱ�*/
	int length; /*���еĳ���*/
	int NowSize; /*��ǰ�����Ԫ�ظ���*/
	int MaxContent; /*�ѵ��������*/
};

/*��������*/
PtrlSqList CreatList(); /*���еĴ���*/
int GetListLength(PtrlSqList P); /*�������еĳ���*/
void Swap(ElemType *a, ElemType *b); /*����Ԫ��*/
void PrintList(PtrlSqList P, int count); /*�������*/
void Insert_Array(PtrlSqList P, int K); /*���в���Ԫ��*/
bool IsFull(PtrlSqList H); /*�ж������Ƿ�����*/
bool IsEmpty(PtrlSqList H); /*�ж������Ƿ�Ϊ��*/
void Insert(PtrlSqList P, ElemType X); /*���ѵĲ���*/
ElemType Delete(PtrlSqList P); /*���ѵ�ɾ��(������һ��Ԫ��)*/

/*������*/
int main(int agrc, char const* argv[]) 
{
	bool IsFull, IsEmpty;
	int i, j;
	ElemType InsertData, DeleteItem, data=0;
	
	/*����һ��������,�Ѵ�������һ��һ�����뵽���в�����������*/ 
	PtrlSqList H=CreatList(); 
	/*����һ����������*/
	PtrlSqList P=CreatList();
	printf("�봴����������:");
	while (data!=-1) {
		scanf("%d", &data);
		if (data!=-1) {
			Insert_Array(P, data);
		}
	} 
	/*��ô������г���*/
	P->length=GetListLength(P);
	/*�����������*/
	printf("\n��������Ϊ:");
	PrintList(P, 0); 
	printf("\n�������г���=%d\n", P->length); 
	
	/*�Ѵ�������Ԫ��һ�������뵽����ͬʱ������*/
	/*forѭ����i<=P->length+1��Ϊ�˰�-1������־Ҳ���ȥ*/
	for (i=1; i<=P->length+1; i++) {
		Insert(H, P->arr[i]);
		P->arr[i]=0;
		j=i;
	} 
	P->arr[j]=-1; /*������*/
	
	printf("\n����H��");
	PrintList(H, 0);
	/*��ȡ���ѵĳ���*/
	H->length=GetListLength(H);
	printf("\n����H�ĳ���=%d\n", H->length); 

	printf("\n�ع����:\n");
	j=P->length;
	for (i=1; i<=P->length; i++) {
		P->arr[j]=Delete(H);
		PrintList(P, 0);
		printf("\n");
		j--;
	}
	
	printf("\n����������У�");
	PrintList(P, 0);
	return 0;
} 

/*���еĴ���*/
PtrlSqList CreatList() 
{
	PtrlSqList P=(PtrlSqList)malloc(sizeof(struct SqList));
	P->arr[0]=MaxData; /*�ڱ�*/
	P->arr[1]=-1;
	P->NowSize=0; /*NowSize��¼��ǰ�Ѵ�С,Ҳ�������һ��Ԫ�ص�λ���±�*/
	P->MaxContent=MaxData; /*��¼�ѵ��������*/
	
	return P; 
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

/*����Ԫ��*/
void Swap(ElemType *a, ElemType *b) 
{
	ElemType t=*a;
	*a=*b;
	*b=t;
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

/*���в���Ԫ��*/
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

/*�ж������Ƿ�����*/
bool IsFull(PtrlSqList P) 
{
	return (P->MaxContent==P->NowSize);
} 

/*�ж������Ƿ�Ϊ��*/
bool IsEmpty(PtrlSqList P)
{
	return (P->NowSize==0);
}

/*���ѵĲ���*/
void Insert(PtrlSqList H, ElemType X)
{
	int i;
	/*����ǰ���ж϶�������*/
	if (IsFull(H)) {
		printf("��������,�޷�����.");
		return;
	}
	/*û�����Ͳ���*/
	i=++H->NowSize; /*��ΪNowSize��¼���ǵ�ǰ�������һ��Ԫ�ص��±�,������������������*/
	 
	/*���������λ��,���iλ�õĸ����Ȳ����ֵС,�ͰѸ�����ƶ�����*/
	/*i/2��i�ĸ����,2i��������,2i+1��������*/
	for (; H->arr[i/2]<X; i/=2) {
		H->arr[i]=H->arr[i/2]; /*�Ѹ����������*/
	} 
	/*i�ĸ���㲻��Ҫ�����XС��,��ô�Ͳ���X��i*/
	H->arr[i]=X;
}

/*���ѵ�ɾ��(������һ��Ԫ��)*/ 
ElemType Delete(PtrlSqList H) 
{
	int Head, Max; /*Head��Ҫ�����λ��, Max��Head���ӽ����±�λ��*/
	ElemType DeleteItem, Tag;
	
	/*����һ��Ԫ��ǰ,���ж϶�Ϊ��Ϊ��*/
	if (IsEmpty(H)) {
		printf("����Ϊ��.");
		return;
	}
	/*��Ϊ�վ͵���Ԫ��*/
	DeleteItem=H->arr[1]; /*�Ȱ�Ҫ�����Ľ�㱣������,��󷵻س�ȥ*/
	Tag=H->arr[H->NowSize--]; /*���浯��һ��Ԫ�غ�,�������һ��Ԫ��(��СԪ��)���±�*/
	
	/*����Ĳ����ǰѵ���һ��Ԫ�غ�Ķѵ���������*/
	/*Head*2���жϸý���Ƿ���������,Head*2��������,Head*2+1��������*/
	/*Head��Ҫ�����λ�ô�1��ʼ,���ӵ�һ������(���ڵ�)��ʼ�ж�*/
	for (Head=1; Head*2<=H->NowSize; Head=Max) {
		/*�����������,���ж���������������˭����*/
		/*Head*2<=NowSize�жϵ�ǰҪ�����λ���Ƿ���������,���������==NowSize,��û������*/
		Max=Head*2; /*һ��ʼ����Max��ֵ����������λ���±�,��ָ��������*/
		/*������������С�����������*/
		if ((H->arr[Max]<H->arr[Max+1]) && (Max!=H->NowSize)) {
			/*Max!=H->NowSize,֤����������*/
			/*�Ͱ�Maxָ��������������λ��*/ 
			Max++;
		}
		/*һ��ѭ���ҵ���ǰҪ�����λ�õ����������ĸ�����Ǹ�λ��Max��*/ 
		/*�Ƚ��ҵ�ǰҪ�����Ԫ��Tag�Ƿ������������,�Ǿ�ֱ�Ӳ���*/ 
		if (Tag>=H->arr[Max]) {
			break;
		} else {
			/*����ͰѸ�����Ǹ�ֵ������,�������ѵĹ���*/
			/*����TagҪ�����λ������,���Ʋ�����forѭ�������Head=Max*/
			/*Head=Max����Head������λ�ø����Լ�,���Լ�������*/
			H->arr[Head]=H->arr[Max]; 
		} 
	}
	/*forѭ�������,���ҵ���ȷ�Ĳ���λ��,�Ͳ���TagԪ��*/
	H->arr[Head]=Tag;
	
	return DeleteItem;
}
