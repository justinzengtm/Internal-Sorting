#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20
typedef int ElemType;

/*待排记录的存储结构*/
typedef struct SqList *PtrlSqList;
struct SqList{
	ElemType arr[MaxSize+1]; /*r[0]做为哨兵*/
	int length; /*顺序表的长度*/ 
}; /*顺序表类型*/

/*函数声明*/
void Insert_Array(PtrlSqList P, int K); /*序列插入元素*/
int GetListLength(PtrlSqList P); /*计算序列的长度*/
void PrintList(PtrlSqList P); /*输出序列*/
void Swap(PtrlSqList P, int i); /*元素i和i+1位置互换*/
void Bubble_Sort(PtrlSqList P, int N); /*改良冒泡排序*/

int main(int argc, char const* argv[]) 
{
	int data;
	PtrlSqList P;
	P=(PtrlSqList)malloc(sizeof(struct SqList));
	P->arr[1]=-1;
	P->arr[0]=0;
	
	printf("请创建序列:");
	do {
		scanf("%d", &data);
		Insert_Array(P, data);
	} while (data!=-1);
	
	P->length=GetListLength(P);
	//P.r[]={34, 8, 64, 51, 32, 31};
	Bubble_Sort(P, P->length);
	
	printf("\n冒泡排序后:");
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
}

/*计算序列的长度*/
int GetListLength(PtrlSqList P) 
{
	int count=0;
	int i=1;
	
	while (P->arr[i]!=-1) {
		count++;
		i++;
	}

	return count;
}

/*输出序列*/
void PrintList(PtrlSqList P) 
{
	int i=1; 
	while (P->arr[i]!=-1) {
		printf("%d\t", P->arr[i]);
		i++;
	}
} 

/*元素i和i+1位置互换*/
void Swap(PtrlSqList P, int j) 
{
	ElemType Temp;
	Temp=P->arr[j];
	P->arr[j]=P->arr[j+1];
	P->arr[j+1]=Temp; 
}

/*改良冒泡排序*/
void Bubble_Sort (PtrlSqList P, int N)  
{
	/*P是待排序列,N是要排序的个数*/
	int i,j,flag;
	flag=0; /*flag标记是否有执行Swap函数*/
	
	for (i=N; i>0; i--) {
		flag=0; /*每做完一轮排序,flag重置为0*/
		for (j=1; j<i; j++) {
			if (P->arr[j]>P->arr[j+1]) {
				Swap(P, j);
				flag=1;
			}
		}
		/*如果做完一轮排序,全程无交换,证明排序已完成*/
		if (flag==0) {
			break; /*就跳出剩下的循环*/
		}
	}
}
