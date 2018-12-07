/*�������� - ��λ����
 *time:2018/12/6
 *tutor:justinzeng
 */

#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define MaxDigit 3 //�ؼ���������λ 
#define Radix 10 //����Ϊ10
#define ElemType int

//�������еĴ洢�ṹ
typedef struct SqlList *PtrlSqlList;
struct SqlList {
	ElemType arr[MaxSize+1]; //��������
	int length; //�������еĳ��� 
};

//ͰԪ�صĽ��Ĵ洢��� 
typedef struct BucketNode *PtrlBucketNode; //Ͱ���������ʽ�洢 
struct BucketNode {
	int key;
	PtrlBucketNode Next;
}; 

//Ͱ��ͷ���
struct BucketHeadNode {
	PtrlBucketNode Head; //ָ��Ͱ����ͷ��ͷ���
	PtrlBucketNode Tail; //ָ��Ͱ����β��Ϊ��� 
}; 
typedef struct BucketHeadNode Bucket[Radix]; //���Ͱ������

//��������
PtrlSqlList InitialList(); //���г�ʼ��
PtrlBucketNode InitialBucket(); //��ʼ��һ��Ͱ 
void Insert_Array(PtrlSqlList P, ElemType K); //���в���Ԫ��
void PrintList(PtrlSqlList P, int count); //�����������
int GetDigit(int K, int Down); //���λ����  
void Least_Significant_Digit_Sort(PtrlSqlList P, int N); //LSD��λ���Ȼ�������
void PrintBucketList(PtrlBucketNode PBL); //���Ͱ��Ԫ��

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
	
	//LSD��λ���Ȼ�������
	Least_Significant_Digit_Sort(P, P->length);
	
	printf("\n�������������:");
	PrintList(P, 0); 
	return 0; 
}
//��ʼ��һ��Ͱ
PtrlBucketNode InitialBucket()
{
	PtrlBucketNode Bucket;
	Bucket=(PtrlBucketNode)malloc(sizeof(struct BucketNode));
	
	return Bucket;
}

//���г�ʼ��
PtrlSqlList InitialList()
{
	PtrlSqlList P=(PtrlSqlList)malloc(sizeof(struct SqlList)); 
	P->arr[0]=-1;	
	P->length=0; //��ʼ�����г���Ϊ0,�����ڱ�
	
	return P; 
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

//���Ͱ��Ԫ��
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
int GetDigit(int K, int Digit) 
{
	//��λһ��ʼΪDown=1,��λΪD<=MaxDigit.
	int i, digit;
	
	for (i=1; i<=Digit; i++) {
		digit=K%Radix;
		K/=Radix;
	} 
	
	return digit;
} 

//LSD��λ���Ȼ������� 
void Least_Significant_Digit_Sort(PtrlSqlList P, int N)
{
	//�������� - ��λ����
	int D, Di, i;
	Bucket B; //����һ��Ͱ������,Ҳ����һ��Ͱ
	PtrlBucketNode tmp, p, List=NULL; //����������Ͱ,�ҳ�ʼ��ΪNULL
	
	//��ʼ��ÿ��ͰΪһ�������� 
	//���������Radixλ,������ҪRadix��Ͱ 
	for (i=0; i<Radix; i++) {
		B[i].Head=B[i].Tail=NULL; //Ͱ��ͷβָ�����ʼ��ΪNULL 
	} 
	
	//!!!!������������������ʼ����List�� 
	for (i=0; i<N; i++) {
		tmp=InitialBucket(); //��ʼ��һ��Ͱ
		//�������Ĳ����ǰѴ�����������洢��ListͰ�� 
		tmp->key=P->arr[i];
		tmp->Next=List;
		List=tmp;
	} 
	
	//Ȼ��ʼ�������
	for (D=1; D<=MaxDigit; D++) {
		//�����ݵ�ÿһλ���д���,�������������������λ
		p=List; 
		while (p) {
			//Dһ��ʼ��1��ʼ,Ҳ����һ��ʼֻ����λ 
			//��õ�ǰԪ�صĵ�ǰλ���� 
			Di=GetDigit(p->key, D); 
			tmp=p;
			p=p->Next; 
			//tmp������p,get��p�����ݵ���λ��,�����ListͰ���Ƴ� 
			tmp->Next=NULL;
			//�����λ��,���뵽B[Di]Ͱ��
			//��������ж����ͰB[Di]������Ϊ��
			if (B[Di].Head==NULL) {
				B[Di].Head=B[Di].Tail=tmp;
			} else {
				B[Di].Tail->Next=tmp;
				B[Di].Tail=tmp;
			}
		}
		
		printf("��%d�δ�λ���Ȼ�������\n", D);
		for (i=0; i<Radix-1; i++) {
			printf("B[%d]��", i);
			PrintBucketList(B[i].Head);
			printf("\n");
		}	
		
		//����һ��Ͱ�����,�ռ�Ͱ����B�е�Ԫ��
		List=NULL; //List��ΪͰ����ͷ 
		//0-9ʮ�����,��������ListͰ��,����Di��Radix-1Ҳ����9��ʼ 
		for (Di=Radix-1; Di>=0; Di--) {
			if (B[Di].Head) {
				//����Ͱ����List��ͷ
				B[Di].Tail->Next=List; //��ʱ��List==NULL 
				List=B[Di].Head; 
				//���ͰB[Di]
				B[Di].Head=B[Di].Tail=NULL; 
			} 
		}
		printf("�ռ�Ͱ��");
		PrintBucketList(List);
		printf("\n\n");
	} 	
	
	//�������������,��List�Ż��û��������в��ͷŵ�List
	for (i=0; i<N; i++) {
		tmp=List;
		List=List->Next;
		P->arr[i]=tmp->key;
		free(tmp);
	}  
}
