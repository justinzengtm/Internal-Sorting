#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20
typedef int ElemType;

//待排序列的存储结构
typedef struct SqlList *PtrlSqlList;
struct SqlList {
	ElemType arr[MaxSize+1];
	int length;
};

//函数声明
void Insert_Array(PtrlSqlList P, int K); //序列插入元素
void PrintList(PtrlSqlList P, int count); //输出序列
int GetLength(PtrlSqlList P); //获得序列的长度
void Shell_Sort(PtrlSqlList P, int lenght); //希尔排序

int main(int argc, char const* argv[]) 
{
	int data=0;
 
	PtrlSqlList P;
	P=(PtrlSqlList)malloc(sizeof(struct SqlList));
	P->arr[0]=0; /*数组第0位设置为哨兵*/
	P->arr[1]=-1;
	
	printf("\n请创建序列:");
	while (data!=-1) {
		scanf("%d", &data); 
		Insert_Array(P, data);
	}
	
	printf("\n原序列为:");
	PrintList(P, 0);
	//获得序列的长度
	P->length=GetLength(P);
	printf("\n\n序列长度为:%d\n", P->length);
	//希尔排序
	Shell_Sort(P, P->length);
	printf("希尔排序后:");
	PrintList(P, 0);
	
	return 0;
}

//序列插入元素
void Insert_Array(PtrlSqlList P, int K) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		i++;
	}
	P->arr[i]=K;
	P->arr[i+1]=-1;
	
	return;
}

//输出序列
void PrintList(PtrlSqlList P, int count) 
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

//获得序列长度
int GetLength(PtrlSqlList P) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		i++;
	}
	
	return (i-1);
}


//希尔排序接口 
void Shell_Sort(PtrlSqlList P, int length) 
{
	int increases, j, k, ListLength, Si;
	int count=0;
	//Sedgewick增量序列
	//int Increment[]={929, 505, 209, 109, 41, 19, 5, 1, 0,}; 
	int Increment[]={5, 3, 1,};
	ListLength=GetLength(P);
	
	//遍历获得需要的增量序列
	for (Si=0; Increment[Si]>=ListLength; Si++);
	
	printf("\n需要用到的增量序列为:");
	for (j=Si; Increment[j]>=1; j++) {
		printf("%d ", Increment[j]);
	}
	
	printf("\n\n希尔排序过程:\n");
	for (increases=Increment[Si]; increases>=1; increases=Increment[++Si]) {
		//插入排序
		for (j=increases; j<=ListLength; j++) {
			//如果后一个数小于前一个间隔增量的数
			if (P->arr[j]<P->arr[j-increases]) {
				P->arr[0]=P->arr[j]; //把较小的数赋值给哨兵暂存
				for (k=j-increases; k>0 && P->arr[0]<P->arr[k]; k-=increases) {
					//如果P->arr[0]<P->arr[k],即哨兵处元素比某一增量处的元素小的话
					P->arr[k+increases]=P->arr[k]; //记录后移,找出插入位置
				} 
				P->arr[k+increases]=P->arr[0];
			}
		}
		count++;
		PrintList(P, count);
		printf("\n\n");
	}
}
