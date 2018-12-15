/*
 *基数排序 - 主位优先
 *date:2018/12/15
 *author:justinzeng
 */
 
#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100 //序列的最大长度
#define MaxDigit 4 //关键字最多有四位
#define Radix 10 //基数是10
typedef int ElemType;

//待排序列的存储结构
typedef struct SqlList *PtrlSqlList;
struct SqlList {
	ElemType arr[MaxSize+1]; //待排序列数组形式
	int length; //待排序列的长度 
}; 

//桶元素的结点的存储结构
typedef struct BucketNode *PtrlBucketNode; //桶以链表的形式存储
struct BucketNode {
	int key; //结点数据
	PtrlBucketNode Next; //指向下一个结点的指针 
}; 

//桶集合的结构
struct BucketHeadNode {
	PtrlBucketNode Head; //指向桶链表的头结点
	PtrlBucketNode Tail; //指向桶链表的尾结点 
}; 
//一共有Radix基数个情况,所以分Radix个桶 
typedef struct BucketHeadNode Bucket[Radix];  

//函数声明
PtrlSqlList InitialList(); //序列初始化
PtrlBucketNode InitialBucket(); //初始化一个桶
void CreatList(PtrlSqlList P); //创建序列 
int GetListLength(PtrlSqlList P); //获得序列长度
void Insert_Array(PtrlSqlList P, ElemType K); //序列插入元素
void Conncet(ElemType data, PtrlBucketNode Ptrl); //桶链接结点
void PrintList(PtrlSqlList P, int count); //输出序列
void PrintBucketList(PtrlBucketNode PBL); //输出桶 
int GetDigit(int K, int Down); //获得位数字
void Most_Significant_Digit_Sort(PtrlSqlList P, int L, int R, int N); //MSD主位优先基数排序

int main(int argc, char const *argv[]) 
{
	//创建一个待排序列
	PtrlSqlList P=InitialList();
	CreatList(P); //创建待排序列
	printf("\n待排序列为:"); 
	PrintList(P, 0); //输出待排序列
	//获得序列长度
	P->length=GetListLength(P);
	printf("\n待排序列长度为:%d\n", P->length);
	
	//MSD主位优先基数排序
	Most_Significant_Digit_Sort(P, 0, P->length, MaxDigit); 
	
	printf("\n主位优先基数排序后序列:");
	PrintList(P, 0);
	
	return 0;
	 
}

//序列初始化
PtrlSqlList InitialList()
{
	PtrlSqlList P=(PtrlSqlList)malloc(sizeof(struct SqlList));
	P->arr[0]=-1;
	P->length=0;
	
	return P;
}

//初始化一个桶 
PtrlBucketNode InitialBucket()
{
	PtrlBucketNode Bucket;
	Bucket=(PtrlBucketNode)malloc(sizeof(struct BucketNode));
	Bucket->Next=NULL;
	
	return Bucket;
}

//创建序列
void CreatList(PtrlSqlList P)
{
	ElemType data=0;
	
	printf("请创建待排序列:");
	while (data!=-1) {
		scanf("%d", &data);
		if (data!=-1) {
			Insert_Array(P, data);
		}
	}
	
	return;
}

//序列插入元素 
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

//桶链接结点
void BucketConnect(PtrlBucketNode Ptrl, ElemType K) 
{
	PtrlBucketNode Ptrl1,Ptrl2; //Ptrl1负责查找连接位置,Ptrl2负责链接结点 
	Ptrl1=Ptrl;  
	//Ptrl2存储要链接进来的结点 
	Ptrl2=InitialBucket();
	Ptrl2->key=K;
	Ptrl2->Next=NULL;
	
	if (Ptrl1) {
		//while循环一直找到链表的末尾结点
		while (Ptrl1->Next) {
			Ptrl1=Ptrl1->Next;
		}
		//找到后,链接 
		Ptrl1->Next=Ptrl2;
	} else {
		//如果链表只有初始的那一个结点的话
		Ptrl1=Ptrl2;
	}	
	
	return;
}

//获得序列长度 
int GetListLength(PtrlSqlList P) 
{
	int length=0;
	
	while (P->arr[length]!=-1) {
		length++;
	}
	
	return length;
} 

//输出序列 
void PrintList(PtrlSqlList P, int count) 
{
	int i=0;
	
	if (count!=0) {
		printf("第%d次排序:", count);
		//输出序列
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

//输出桶 
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

//获得位数字
int GetDigit(int K, int Down) 
{
	int tmp, i;
	
	for (i=1; i<=Down; i++) {
		tmp = K%Radix; //得到当前K的最低位
		K /= Radix; //去掉当前K的最低位 
	} 
	
	return tmp;
} 

//MSD主位优先基数排序
void Most_Significant_Digit_Sort(PtrlSqlList P, int L, int R, int N) 
{
	//递归函数对P->arr[L]到P->arr[R]的第N位数进行排序
	int Di, i, j;
	
	Bucket B; //创建一个桶数组
	PtrlBucketNode tmp, p, List=NULL; //三个临时桶
	
	//如果位数等于0了,就终止递归 
	if (N==0) {
		return;
	} 
	
	//先初始化每一个桶为一个空链表 
	for (i=0; i<Radix; i++) {
		B[i].Head=B[i].Tail=NULL;
	}
	
	//把待排序列存入List链表中
	tmp=InitialBucket(); //初始化一个桶元素结点
	for (i=L; i<R; i++) {
		BucketConnect(tmp, P->arr[i]);
	} 
	List=tmp->Next; //!!!!

	//然后开始排序过程
	p=List; 
	//每一次排序后要回收到List中,所以用p来操作
	while(p) {
		Di=GetDigit(p->key, N); //获得当前元素的位数字
		//printf("位数=%d\n", Di);
		//然后把这个数字从List中删除
		tmp=p; //然后把tmp插入到相应的桶中 
		p=p->Next;
		tmp->Next=NULL; //把tmp弄成单独一个结点 
		//根据位数字把这个元素插入到相应的桶中
		//特殊情况判断如果桶B[Di]为空
		if (B[Di].Head==NULL) {
			B[Di].Head=B[Di].Tail=tmp;
		} else {
			B[Di].Tail->Next=tmp;
			B[Di].Tail=tmp;
		}	 
	}
				
	i=j=L; //用i和j记录当前要处理的序列P的左右端点的下标
	printf("\ni=%d j=%d N=%d\n", i, j, N);
	//收集每一个桶,也就是收集Radix基数个桶,Di计数用 
	for (Di=0; Di<Radix; Di++) {
		if (B[Di].Head) {
			p=B[Di].Head;
			while (p) {
				tmp=p;
				p=p->Next;
				P->arr[j]=tmp->key;
				j++; //j最终回到R,也就是当前待排序列的长度 
				free(tmp);
			}
			printf("收集桶:");
			PrintList(P, 0);
			printf("\n");
			//递归对该桶的元素进行排序,位数减1
			Most_Significant_Digit_Sort(P, i, j, N-1);
			i=j; 
		} 
	}
	
	return; 
}
