#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20
typedef int ElemType;

/*待排序列的存储结构*/
typedef struct SqList *PtrlSqList;
struct SqList {
	ElemType arr[MaxSize+1];
	int length;
};

/*函数声明*/
void Insert_Array(PtrlSqList P, int K); /*序列插入元素*/
void PrintList(PtrlSqList P); /*输出序列*/
int GetLength(PtrlSqList P); /*获得序列的长度*/
void Binary_Sort(PtrlSqList P, int length); /*折半插入排序*/ 

int main(int argc, char const* argv[]) 
{
	int data=0;
	PtrlSqList P;
	P=(PtrlSqList)malloc(sizeof(struct SqList));
	P->arr[0]=0; /*数组第0位设置为哨兵*/
	P->arr[1]=-1;
	
	printf("\n请创建序列:");
	while (data!=-1) {
		scanf("%d", &data); 
		Insert_Array(P, data);
	}
	
	printf("\n原序列为:");
	PrintList(P);
	/*获得序列的长度*/
	P->length=GetLength(P);
	printf("\n序列长度为:%d\n", P->length);
	printf("\n二分插入排序过程:"); 
	/*直接插入排序*/
	Binary_Sort(P, P->length);
	printf("\n二分插入排序后:");
	PrintList(P);
	
	return 0;
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

/*输出序列*/
void PrintList(PtrlSqList P) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		printf("%d  ", P->arr[i]);
		i++;
	}
	
	return;
}

/*获得序列长度*/
int GetLength(PtrlSqList P) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		i++;
	}
	
	return (i-1);
}

/*二分插入排序2*/
void Binary_Sort(PtrlSqList P, int length) 
{
	int front, rear;
	int i, j, Tmp, m;
	
	for (i=2; i<=length; i++) {
		P->arr[0]=P->arr[i];
		front=1;
		rear=i-1; /*因为要从已排好序列中做插入排序,所以rear=i-1开始*/ 
		/*二分查找找出已排好序列中元素*/
		while (front<=rear) {
			m=(front+rear)/2;
			if (P->arr[m]>P->arr[0]) {
				/*证明插入点在前半部分*/
				rear=m-1;
			} else {
				/*否则插入点在后半部分*/ 
				front=m+1;
			}
		}
		printf("\nfront=%d, rear=%d, m=%d\n", front, rear, m);
		/*找到插入*/
		/*front插入位置的起点,i是已排好序列的终点*/ 
		/*把已排好序列中插入位置fonrt及之后的元素往后挪*/
		for (j=i; j>0 && j>=front; j--) {
			P->arr[j]=P->arr[j-1]; /*往后挪一位*/
		}
		P->arr[front]=P->arr[0];
		PrintList(P);
		printf("\n");	
	}
}
