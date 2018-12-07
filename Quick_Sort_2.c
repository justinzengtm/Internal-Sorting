#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20
typedef int ElemType;

//�������еĴ洢�ṹ
typedef struct SqlList *PtrlSqlList;
struct SqlList {
	ElemType arr[MaxSize+1]; //��������
	int length; //�������еĳ��� 
}; 

//��������
PtrlSqlList InitialList(); //���г�ʼ��
void Insert_Array(PtrlSqlList P, ElemType K); //���в���Ԫ��
void PrintList(PtrlSqlList P, int count); //�������
int GetListLength(PtrlSqlList P); //�������г���
void Swap(ElemType Left, ElemType Right, PtrlSqlList P); //������Ԫ��λ�� 
ElemType Median3(PtrlSqlList P, int Left, int Right); //ѡ������ 
void QuickSort(PtrlSqlList P, int N); //��������ӿ� 
void Quick_Sort(PtrlSqlList P, int Low, int High); //��������
void Insertion_Sort(PtrlSqlList P, int Left, int N); //��������
void PrintList2(PtrlSqlList P, int Left, int Right); //�������2
 
int main(int argc, char const* argv[]) 
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
	
	//�������� 
	printf("����������̣�\n");
	QuickSort(P, P->length);
	printf("\n�������������:");
	PrintList(P, 0);
	
	return 0; 
}

//���г�ʼ��
PtrlSqlList InitialList()
{
	PtrlSqlList P=(PtrlSqlList)malloc(sizeof(struct SqlList));
	P->arr[0]=MaxSize; //�ڱ� 
	P->arr[1]=-1;	
	P->length=0; //��ʼ�����г���Ϊ0,�����ڱ�
	
	return P; 
} 

//���в���Ԫ��
void Insert_Array(PtrlSqlList P, ElemType K)
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
	int j=0;
	
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
	
	return length-1;
} 

//������Ԫ��λ��
void Swap(ElemType Left, ElemType Right, PtrlSqlList P) 
{
	int Tmp=P->arr[Right];
	P->arr[Right]=P->arr[Left];
	P->arr[Left]=Tmp;
} 

//ѡ������ 
ElemType Median3(PtrlSqlList P, int Left, int Right) 
{
	int i=0;
	
	//ȡ���еĵ�һλ,�м�λ�����һλ��,ȡ��λ��. 
	int Center=(Left+Right)/2;
	if (P->arr[Left]>P->arr[Center]) {
		Swap(Left, Center, P);
	}
	if (P->arr[Left]>P->arr[Right]) {
		Swap(Left, Right, P);
	}
	if (P->arr[Center]>P->arr[Right]) {
		Swap(Center, Right, P);
	}
	
	//printf("\n�������������: %d %d %d", P->arr[Left], P->arr[Center], P->arr[Right]);
	//��ʱӦ�� P->arr[Left] < P->arr[Center] < P->arr[Right] 
	
	/*������Ԫ�ػ���Right-1��λ��,��Ϊ��ʱRightλ�õ�Ԫ��һ������
	 *Centerλ�õ�����,Leftλ�õ�Ԫ��һ��С������,���Խ������Ĳ���
	 *ֻ��Ҫ��Left+1��Right-2��һ����������������
	 */  
	Swap(Left, Center, P);
	
	return P->arr[Left]; //�����᷵�س�ȥ 
}

void QuickSort(PtrlSqlList P, int N) 
{
	Quick_Sort(P, 1, N);
	
	return;
}
//�������� 
void Quick_Sort(PtrlSqlList P, int Left, int Right)
{
	int Low, High;
	int cutoff=2; //��ֵ 
	Low=Left;
	High=Right-1; 
	
	//���о����Ƿ��ж������������Ԫ��������ֵ,�Ͳ��ü򵥲������� 
	//if (cutoff<=Right-Left) {
		if (Left<Right) {
		ElemType pivotkey=Median3(P, Left, Right); //��ȡ���� 
		P->arr[0]=pivotkey; //���ᱣ�浽�ڱ�λ��. 
		printf("\nLow=%d High=%d\n", Low, High);
		printf("����pivotkey=%d\n", pivotkey);
		//�ȴ�High��ʼ����ɨ�� 
		while (Low<High) {
			while (Low<High && P->arr[High]>pivotkey) {
				High--;
			}
			//�ҵ���һ��P->arr[High] < pivotkey��,����Low��Highλ�õ�Ԫ��
			P->arr[Low]=P->arr[High]; 
			
			//Ȼ���Low��ʼ����ɨ��
			while (Low<High && P->arr[Low]<pivotkey) {
				Low++;
			} 
			//�ҵ���һ��P->arr[Low] > pivotkey��,����Low��Highλ�õ�Ԫ��
			P->arr[High]=P->arr[Low];
		}	
		//Low��High��λ֮��,Low���������λ��,��Ϊ����������,�����ỻ����ȷ��λ��
		printf("Left=%d Right=%d ����λ��=%d\n", Left, Right, Low);
		if (Right-Left>0) {
			Swap(Low, 0, P);
		}
		
		//���ÿһ���������
		PrintList(P, 0);
		printf("\n");
		
		//��ʼ�ݹ�����������
		Quick_Sort(P, Left, Low-1); //�ݹ������ 
		Quick_Sort(P, Low+1, Right); //�ݹ����ұ� 
		
		return; 
		}
//	} else {
//		if (Right!=Left) {
//			printf("\n��������������������ֵ,���ò�������....\n");
//			//������е�������С����ֵ,�Ͳ��ü򵥵Ĳ�������
//			Insertion_Sort(P, Left, Right-Left+1);
//		}
//	}
}

/*ֱ�Ӳ�������*/
void Insertion_Sort(PtrlSqlList P, int Left, int N) 
{
	int i, j, Tmp, flag;
	for (i=Left+1; i<=N; i++) {
		Tmp=P->arr[i]; /*������������ó�Ԫ��*/
		printf("Tmp=%d\n", Tmp);
		for (j=i; j>Left && P->arr[j-1]>Tmp; j--) {
			P->arr[j]=P->arr[j-1]; /*����Ųһλ*/
		}
		P->arr[j]=Tmp; /*����ҵ���Tmp�����������Ų��,������ȷ��λ�þͲ���*/
		PrintList2(P, Left, Left+N+1); /*��Ϊ������к���,�˴�ÿ�����һ������������*/ 
		printf("\n");
	}
} 

//�������2
void PrintList2(PtrlSqlList P, int Left, int Right)
{
	int i=0;
	
	for (i=Left; i<=Right; i++) {
		printf("%d ", P->arr[i]);
	}
	
	return;
}
