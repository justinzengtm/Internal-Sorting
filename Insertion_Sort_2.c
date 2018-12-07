#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20
typedef int ElemType;

//待排序列的存储结构
typedef struct SqList *PtrlSqList;
struct SqList {
	ElemType arr[MaxSize+1];
	int length;
};

//函数声明
void Insert_Array(PtrlSqList P, int K); //序列插入元素
void PrintList(PtrlSqList P); //输出序列
int GetLength(PtrlSqList P); //获得序列的长度
void Insert_Sort(PtrlSqList P, int lenght); //直接插入排序

int main(int argc, char const* argv[]) 
{
	int data=0;
	PtrlSqList P;
	P=(PtrlSqList)malloc(sizeof(struct SqList));
	P->arr[0]=0; //数组第0位设置为哨兵
	P->arr[1]=-1;
	
	printf("\n请创建序列:");
	while (data!=-1) {
		scanf("%d", &data); 
		Insert_Array(P, data);
	}
	
	printf("\n原序列为:");
	PrintList(P);
	//获得序列的长度
	P->length=GetLength(P);
	printf("\n序列长度为:%d\n", P->length);
	//直接插入排序
	Insert_Sort(P, P->length);
	printf("\n直接插入排序后:");
	PrintList(P);
	
	return 0;
}

//序列插入元素
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

//输出序列
void PrintList(PtrlSqList P) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		printf("%d  ", P->arr[i]);
		i++;
	}
	
	return;
}

//获得序列长度
int GetLength(PtrlSqList P) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		i++;
	}
	
	return (i-1);
}

//直接插入排序
void Insert_Sort(PtrlSqList P, int length) 
{
	int i, j;
	
	printf("\n直接插入排序过程:\n");
	for (i=2; i<=length; i++) {
		//如果后一个数小于前一个数 
		if (P->arr[i]<P->arr[i-1]) {
			P->arr[0]=P->arr[i]; //先把较小的数赋值给哨兵
			P->arr[i]=P->arr[i-1]; //较大的数后移一位
			for (j=i-2; P->arr[0]<P->arr[j]; j--) {
				//从i-2开始,如果比哨兵大的数,就后移一位,腾出位置
				P->arr[j+1]=P->arr[j];
			} 
			//内for循环做完后,比哨兵大的值都后移了一位,腾出了正确的位置给哨兵插入
			P->arr[j+1]=P->arr[0]; 
			PrintList(P);
			printf("\n");
		}
	}
}
