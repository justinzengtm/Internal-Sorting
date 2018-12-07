#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20
typedef int ElemType;

//待排记录的存储结构
typedef struct SqlList *PtrlSqlList;
struct SqlList{
	ElemType arr[MaxSize+1]; //r[0]做为哨兵
	int length; //顺序表的长度 
}; //顺序表类型

//函数声明
void Insert_Array(PtrlSqlList P, int K); //序列插入元素
void Shell_Sort(PtrlSqlList P, int N); //希尔排序接口
void PrintList(PtrlSqlList P, int count); //输出序列
int GetListLength(PtrlSqlList P); //计算序列的长度

int main(int argc, char const* argv[]) 
{
	int data=0;
	
	PtrlSqlList P;
	P=(PtrlSqlList)malloc(sizeof(struct SqlList));
	P->arr[1]=-1;
	P->arr[0]=0;
	
	printf("\n请创建序列:");
	while (data!=-1) {
		scanf("%d", &data);
		Insert_Array(P, data);
	} 
	
	printf("\n\n原序列为:");
	PrintList(P, 0);
	//获得序列长度
	P->length=GetListLength(P);
	printf("\n\n序列长度为 = %d\n", P->length);
	//希尔排序
	Shell_Sort(P, P->length);
	//输出序列
	printf("\n希尔插入排序后:");
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

//希尔排序接口
void Shell_Sort(PtrlSqlList P, int N) 
{
	int increases, j, Tmp, k, Si;
	int count=0; //排序次数的计数
	//Sedgewick增量序列
	//int Increment[]={929, 505, 209, 109, 41, 19, 5, 1, 0,}; 
	int Increment[]={5, 3, 1,}; 
	//获得待排序列的长度,用来决定使用增量序列的长度
	int ListLength=GetListLength(P);
	
	//遍历得出需要增量序列的长度
	for (Si=0; Increment[Si]>=ListLength; Si++);
	//完成后得到的就是只需要用到Increment[Si]和之前的元素
	
	printf("\n需要用到的增量序列为:");
	for (j=Si; Increment[j]>=1; j++) {
		printf("%d ", Increment[j]);
	}
	printf("\n\n希尔插入排序过程:\n");
	//选择增量,当增量不等与1时,到下一个增量
	for (increases=Increment[Si]; increases>=1; increases=Increment[++Si]) {
		//直接插入排序
		for (k=increases; k<=ListLength; k++) {
			Tmp=P->arr[k]; //从序列中逐个拿出元素
			for (j=k; j>=increases && P->arr[j-increases]>Tmp; j-=increases) {
				P->arr[j]=P->arr[j-increases]; //往后挪一位
			}
			P->arr[j]=Tmp; //最后找到比Tmp大的数都往后挪了,留下正确的位置就插入
		}
		count++;
		PrintList(P, count); //此为输出序列函数,此处每次输出一次排序后的序列 
		printf("\n");
		printf("\n");
	}
} 

//计算序列的长度
int GetListLength(PtrlSqlList P) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		i++;
	}

	return (i-1);
}
