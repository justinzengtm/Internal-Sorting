#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20
#define ElemType int

/*待排序列的存储结构*/
typedef struct SqList *PtrlSqList;
struct SqList {
	ElemType arr[MaxSize+1];
	int length;
};

/*函数声明*/
void Swap(int i, int Min, PtrlSqList P); /*交换元素位置*/ 
PtrlSqList CreatList(); /*初始化序列*/
void Selection_Sort(PtrlSqList P, int N); /*选择排序*/
void Insert_Array(PtrlSqList P, int K); /*序列插入元素*/
void PrintList(PtrlSqList P); /*输出序列*/
int GetLength(PtrlSqList P); /*获得序列长度*/

int main(int argc, char const* argv[])
{
	PtrlSqList P=CreatList();
	int data=0;
	
	printf("请创建序列:");
	while (data!=-1) {
		scanf("%d", &data);
		Insert_Array(P, data);
	}
	
	/*输出原序列*/
	printf("\n原序列为:");
	PrintList(P);
	
	/*获得序列长度*/
	P->length=GetLength(P);
	printf("\n序列长度为:%d\n", P->length);
	
	/*选择排序*/
	Selection_Sort(P, P->length);
	
	printf("\n选择排序后序列:");
	PrintList(P);
	
}

/*交换元素位置*/
void Swap(int i, int Min, PtrlSqList P) 
{
	int Tmp=P->arr[i];
	P->arr[i]=P->arr[Min];
	P->arr[Min]=Tmp;	
} 

/*初始化序列*/
PtrlSqList CreatList()
{
	PtrlSqList P;
	P=(PtrlSqList)malloc(sizeof(struct SqList));
	P->arr[0]=0; /*哨兵*/
	P->arr[1]=-1; 
	
	return P;
} 

/*选择排序*/
void Selection_Sort(PtrlSqList P, int N) 
{
	int i, j, Min;
	
	printf("\n选择排序过程:\n");
	for (i=1; i<N; i++) {
		/*一开始整个序列看作待排序列,所以从待排序列中拿出逐个拿出元素赋值给Min*/ 
		Min=i;
		/*i+1之后看作是待排序列,i+1前是已排好序列*/
		for (j=i+1; j<=N; j++) {
			/*如果某一位置的元素小于Min位置的元素*/
			if (P->arr[j]<P->arr[Min]) {
				/*就交换,Min存更小元素的位置*/
				Min=j;
			}
		}
		/*最后交换最小元素P->arr[Min]和待排序列中的首元素的位置即P->arr[i]*/
		if (i==Min) {
			continue;
		} else {
			Swap(i, Min, P); 
			PrintList(P);
			printf("\n");
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
