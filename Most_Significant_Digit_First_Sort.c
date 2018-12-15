/*
 *�������� - ��λ����
 *date:2018/12/15
 *author:justinzeng
 */
 
#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100 //���е���󳤶�
#define MaxDigit 4 //�ؼ����������λ
#define Radix 10 //������10
typedef int ElemType;

//�������еĴ洢�ṹ
typedef struct SqlList *PtrlSqlList;
struct SqlList {
	ElemType arr[MaxSize+1]; //��������������ʽ
	int length; //�������еĳ��� 
}; 

//ͰԪ�صĽ��Ĵ洢�ṹ
typedef struct BucketNode *PtrlBucketNode; //Ͱ���������ʽ�洢
struct BucketNode {
	int key; //�������
	PtrlBucketNode Next; //ָ����һ������ָ�� 
}; 

//Ͱ���ϵĽṹ
struct BucketHeadNode {
	PtrlBucketNode Head; //ָ��Ͱ�����ͷ���
	PtrlBucketNode Tail; //ָ��Ͱ�����β��� 
}; 
//һ����Radix���������,���Է�Radix��Ͱ 
typedef struct BucketHeadNode Bucket[Radix];  

//��������
PtrlSqlList InitialList(); //���г�ʼ��
PtrlBucketNode InitialBucket(); //��ʼ��һ��Ͱ
void CreatList(PtrlSqlList P); //�������� 
int GetListLength(PtrlSqlList P); //������г���
void Insert_Array(PtrlSqlList P, ElemType K); //���в���Ԫ��
void Conncet(ElemType data, PtrlBucketNode Ptrl); //Ͱ���ӽ��
void PrintList(PtrlSqlList P, int count); //�������
void PrintBucketList(PtrlBucketNode PBL); //���Ͱ 
int GetDigit(int K, int Down); //���λ����
void Most_Significant_Digit_Sort(PtrlSqlList P, int L, int R, int N); //MSD��λ���Ȼ�������

int main(int argc, char const *argv[]) 
{
	//����һ����������
	PtrlSqlList P=InitialList();
	CreatList(P); //������������
	printf("\n��������Ϊ:"); 
	PrintList(P, 0); //�����������
	//������г���
	P->length=GetListLength(P);
	printf("\n�������г���Ϊ:%d\n", P->length);
	
	//MSD��λ���Ȼ�������
	Most_Significant_Digit_Sort(P, 0, P->length, MaxDigit); 
	
	printf("\n��λ���Ȼ������������:");
	PrintList(P, 0);
	
	return 0;
	 
}

//���г�ʼ��
PtrlSqlList InitialList()
{
	PtrlSqlList P=(PtrlSqlList)malloc(sizeof(struct SqlList));
	P->arr[0]=-1;
	P->length=0;
	
	return P;
}

//��ʼ��һ��Ͱ 
PtrlBucketNode InitialBucket()
{
	PtrlBucketNode Bucket;
	Bucket=(PtrlBucketNode)malloc(sizeof(struct BucketNode));
	Bucket->Next=NULL;
	
	return Bucket;
}

//��������
void CreatList(PtrlSqlList P)
{
	ElemType data=0;
	
	printf("�봴����������:");
	while (data!=-1) {
		scanf("%d", &data);
		if (data!=-1) {
			Insert_Array(P, data);
		}
	}
	
	return;
}

//���в���Ԫ�� 
void Insert_Array(PtrlSqlList P, ElemType K) 
{
	int i=0;
	
	while(P->arr[i]!=-1) {
		i++;
	}
	P->arr[i]=K;
	P->arr[i+1]=-1;
	
	return;
} 

//Ͱ���ӽ��
void BucketConnect(PtrlBucketNode Ptrl, ElemType K) 
{
	PtrlBucketNode Ptrl1,Ptrl2; //Ptrl1�����������λ��,Ptrl2�������ӽ�� 
	Ptrl1=Ptrl;  
	//Ptrl2�洢Ҫ���ӽ����Ľ�� 
	Ptrl2=InitialBucket();
	Ptrl2->key=K;
	Ptrl2->Next=NULL;
	
	if (Ptrl1) {
		//whileѭ��һֱ�ҵ������ĩβ���
		while (Ptrl1->Next) {
			Ptrl1=Ptrl1->Next;
		}
		//�ҵ���,���� 
		Ptrl1->Next=Ptrl2;
	} else {
		//�������ֻ�г�ʼ����һ�����Ļ�
		Ptrl1=Ptrl2;
	}	
	
	return;
}

//������г��� 
int GetListLength(PtrlSqlList P) 
{
	int length=0;
	
	while (P->arr[length]!=-1) {
		length++;
	}
	
	return length;
} 

//������� 
void PrintList(PtrlSqlList P, int count) 
{
	int i=0;
	
	if (count!=0) {
		printf("��%d������:", count);
		//�������
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

//���Ͱ 
void PrintBucketList(PtrlBucketNode PBL) 
{
	int i=0;
	PtrlBucketNode P=PBL;
	
	while (P) {
		printf("%d ", P->key);
		P=P->Next;
	}
	
	return;
}

//���λ����
int GetDigit(int K, int Down) 
{
	int tmp, i;
	
	for (i=1; i<=Down; i++) {
		tmp = K%Radix; //�õ���ǰK�����λ
		K /= Radix; //ȥ����ǰK�����λ 
	} 
	
	return tmp;
} 

//MSD��λ���Ȼ�������
void Most_Significant_Digit_Sort(PtrlSqlList P, int L, int R, int N) 
{
	//�ݹ麯����P->arr[L]��P->arr[R]�ĵ�Nλ����������
	int Di, i, j;
	
	Bucket B; //����һ��Ͱ����
	PtrlBucketNode tmp, p, List=NULL; //������ʱͰ
	
	//���λ������0��,����ֹ�ݹ� 
	if (N==0) {
		return;
	} 
	
	//�ȳ�ʼ��ÿһ��ͰΪһ�������� 
	for (i=0; i<Radix; i++) {
		B[i].Head=B[i].Tail=NULL;
	}
	
	//�Ѵ������д���List������
	tmp=InitialBucket(); //��ʼ��һ��ͰԪ�ؽ��
	for (i=L; i<R; i++) {
		BucketConnect(tmp, P->arr[i]);
	} 
	List=tmp->Next; //!!!!

	//Ȼ��ʼ�������
	p=List; 
	//ÿһ�������Ҫ���յ�List��,������p������
	while(p) {
		Di=GetDigit(p->key, N); //��õ�ǰԪ�ص�λ����
		//printf("λ��=%d\n", Di);
		//Ȼ���������ִ�List��ɾ��
		tmp=p; //Ȼ���tmp���뵽��Ӧ��Ͱ�� 
		p=p->Next;
		tmp->Next=NULL; //��tmpŪ�ɵ���һ����� 
		//����λ���ְ����Ԫ�ز��뵽��Ӧ��Ͱ��
		//��������ж����ͰB[Di]Ϊ��
		if (B[Di].Head==NULL) {
			B[Di].Head=B[Di].Tail=tmp;
		} else {
			B[Di].Tail->Next=tmp;
			B[Di].Tail=tmp;
		}	 
	}
				
	i=j=L; //��i��j��¼��ǰҪ���������P�����Ҷ˵���±�
	printf("\ni=%d j=%d N=%d\n", i, j, N);
	//�ռ�ÿһ��Ͱ,Ҳ�����ռ�Radix������Ͱ,Di������ 
	for (Di=0; Di<Radix; Di++) {
		if (B[Di].Head) {
			p=B[Di].Head;
			while (p) {
				tmp=p;
				p=p->Next;
				P->arr[j]=tmp->key;
				j++; //j���ջص�R,Ҳ���ǵ�ǰ�������еĳ��� 
				free(tmp);
			}
			printf("�ռ�Ͱ:");
			PrintList(P, 0);
			printf("\n");
			//�ݹ�Ը�Ͱ��Ԫ�ؽ�������,λ����1
			Most_Significant_Digit_Sort(P, i, j, N-1);
			i=j; 
		} 
	}
	
	return; 
}
