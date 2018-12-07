#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ElemType int
#define MaxSize 100
#define MaxData 1000 

/*待排序列的存储结构*/
typedef struct SqList *PtrlSqList;
struct SqList{
	ElemType arr[MaxSize+1]; /*arr[0]做为哨兵*/
	int length; /*序列的长度*/
};

/*函数声明*/
PtrlSqList CreatList(); /*序列的创建*/
int GetListLength(PtrlSqList P); /*计算序列的长度*/
void Swap(ElemType *a, ElemType *b); /*交换元素*/
void PrintList(PtrlSqList P, int count); /*输出序列*/
void Insert_Array(PtrlSqList P, int K); /*序列插入元素*/
void AdjustMaxHeap(PtrlSqList P, ElemType i, int length); /*调整堆的有序性,调整为最大堆*/
void Heap_Sort(PtrlSqList P, int N); /*堆排序*/

/*主函数*/
int main(int agrc, char const* argv[]) 
{
	bool IsFull, IsEmpty;
	int i;
	ElemType InsertData, DeleteItem, data=0;
	
	/*创建一个待排序列*/
	PtrlSqList P=CreatList();
	printf("请创建待排序列:");
	while (data!=-1) {
		scanf("%d", &data);
		if (data!=-1) {
			Insert_Array(P, data);
		}
	} 
	
	/*获得待排序列长度*/
	P->length=GetListLength(P);
	
	/*输出待排序列*/
	printf("\n待排序列为:");
	PrintList(P, 0); 
	printf("\nP->lenght=%d\n", P->length); 

	/*堆排序*/ 
	printf("\n堆排序过程:\n");
	Heap_Sort(P, P->length);
	printf("\n堆排序后序列:");
	PrintList(P, 0);
	return 0;
} 

/*序列的创建*/
PtrlSqList CreatList() 
{
	PtrlSqList P=(PtrlSqList)malloc(sizeof(struct SqList));
	P->arr[0]=0; /*哨兵*/
	P->arr[1]=-1;
	
	return P; 
}

/*计算序列的长度*/
int GetListLength(PtrlSqList P) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		i++;
	}

	return (i-1);
}

/*交换元素*/
void Swap(ElemType *a, ElemType *b) 
{
	ElemType t=*a;
	*a=*b;
	*b=t;
} 

/*输出序列*/
void PrintList(PtrlSqList P, int count) 
{
	int i=1;
	int j; 
	if (count!=0) {
		printf("第%d次排序:", count);
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

/*序列插入元素*/
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

/*调整堆的有序性,调整为最大堆*/
void AdjustMaxHeap(PtrlSqList P, ElemType i, int length) 
{
	int Head, Max; /*作用和最大堆删除函数中一样*/
	ElemType Tmp; /*临时保存那个要调整位置的元素*/
	
	Tmp=P->arr[i]; /*把要调整位置的元素赋给一个临时变量*/
	for (Head=i; Head*2<=length; Head=Max) {
		Max=Head*2;
		if (Max!=length && P->arr[Max]<P->arr[Max+1]) {
			Max++;
		}
		if (Tmp>P->arr[Max]) {
			break;
		} else {
			P->arr[Head]=P->arr[Max];
		}
	} 
	P->arr[Head]=Tmp;
}

/*堆排序*/
void Heap_Sort(PtrlSqList P, int N) 
{
	int i=0; 
	/*从最后一个结点的父结点开始往上调整*/
	for (i=N/2; i>0; i--) {
		/*把待排序列中的元素调整成最大堆*/
		AdjustMaxHeap(P, i, N);
	}
	/*调整成最大堆后的序列*/
	printf("调整成最大堆后的序列为:");
	PrintList(P, 0); 
	
	printf("\n\n"); /*为了美观的换行*/
	/*开始堆排序*/
	for (i=N; i>0; i--) {
		//printf("此时i=%d\n", i);
		Swap(&P->arr[1], &P->arr[i]);
		/*一趟堆排序后,把待排序列继续调整回最大堆,做下一趟堆排序*/
		AdjustMaxHeap(P, 1, i-1);
		PrintList(P, (N-i+1));
		printf("\n");
	}
}
