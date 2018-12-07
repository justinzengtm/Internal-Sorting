#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
//#define BucketVolume 11
#define ElemType int

/*
 *时间：2018/12/5
 *算法：桶排序
 *实现：justinzeng
 */
 
//待排序列的存储结构
typedef struct SqlList *PtrlSqlList;
struct SqlList {
	ElemType arr[MaxSize+1]; //待排序列
	int length; //待排序列的长度 
};

//桶的存储结构
typedef struct Bucket *ListBucket;
struct Bucket {
	PtrlSqlList P[MaxSize+2];
}; 

//函数声明
PtrlSqlList InitialList(); //序列初始化
ListBucket InitialListBucket(); //桶的初始化 
void Insert_Array(PtrlSqlList P, ElemType K); //序列插入元素 
void Insert_Bucket(ListBucket B, ElemType K); //桶插入元素
void PrintList(PtrlSqlList P, int count); //输出序列
void PrintBucket(ListBucket B); //输出整个桶里的所有链表 
int GetListLength(PtrlSqlList P); //计算序列长度
void Bucket_Sort(PtrlSqlList P, int N); //桶排序
 
int main(int argc, char const *argv[]) 
{
	ElemType data=0;
	
	//创建一个待排序列
	PtrlSqlList P=InitialList();
	printf("请创建待排序列:");
	while (data!=-1) {
		scanf("%d", &data);
		if (data!=-1) {
			Insert_Array(P, data);
		}
	}
	
	//输出待排序列看看
	printf("\n待排序列为:");
	PrintList(P, 0); 
	//获得序列长度 
	P->length=GetListLength(P);
	printf("\n待排序列长度为: %d\n\n", P->length);
	
	//桶排序
	Bucket_Sort(P, P->length);
	
	return 0;
}

//序列初始化
PtrlSqlList InitialList()
{
	PtrlSqlList P=(PtrlSqlList)malloc(sizeof(struct SqlList));
	P->arr[0]=-1;	
	P->length=0; //初始化序列长度为0,不算哨兵
	
	return P; 
} 

 //桶的初始化
ListBucket InitialListBucket()
{
	int i=0;
	ListBucket Bucket=(ListBucket)malloc(sizeof(struct Bucket));
	
	//桶中每一个链表初始化 
	for (i=0; i<=MaxSize+2; i++) {
		Bucket->P[i]=InitialList();
	} 

	return Bucket;
}

//序列插入元素
void Insert_Array(PtrlSqlList P, ElemType K)
{
	int i=0;
	
	while (P->arr[i]!=-1) {
		i++;
	}
	P->arr[i]=K;
	P->arr[i+1]=-1;
} 

//桶插入元素
void Insert_Bucket(ListBucket B,ElemType K) 
{
	Insert_Array(B->P[K], K);
	
	return; 
}

//输出序列
void PrintList(PtrlSqlList P, int count)
{
	int i=0;
	
	if (count!=0) {
		printf("第%d次排序:", count);
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

//输出整个桶里的所有链表
void PrintBucket(ListBucket B)
{
	int i=0; 
	
	printf("输出桶:"); 
	for (i=0; i<MaxSize+2; i++) {
		PrintList(B->P[i], 0);
	}
	
	return;
} 

//计算序列的长度
int GetListLength(PtrlSqlList P) 
{
	int length=0;
	
	while (P->arr[length]!=-1) {
		length++;
	}
	
	return length;
} 

//桶排序
void Bucket_Sort(PtrlSqlList P, int N) 
{
	int i;
	//初始化一个桶 
	ListBucket B=InitialListBucket();
	
	//待排序列放入桶中 
	for (i=0; i<N; i++) {
		Insert_Array(B->P[P->arr[i]], P->arr[i]);
	}
	
	//输出整个桶里的所有链表
	PrintBucket(B);
	
	return;
} 
