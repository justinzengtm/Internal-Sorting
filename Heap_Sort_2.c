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
	int NowSize; /*当前堆里的元素个数*/
	int MaxContent; /*堆的最大容量*/
};

/*函数声明*/
PtrlSqList CreatList(); /*序列的创建*/
int GetListLength(PtrlSqList P); /*计算序列的长度*/
void Swap(ElemType *a, ElemType *b); /*交换元素*/
void PrintList(PtrlSqList P, int count); /*输出序列*/
void Insert_Array(PtrlSqList P, int K); /*序列插入元素*/
bool IsFull(PtrlSqList H); /*判断最大堆是否已满*/
bool IsEmpty(PtrlSqList H); /*判断最大堆是否为空*/
void Insert(PtrlSqList P, ElemType X); /*最大堆的插入*/
ElemType Delete(PtrlSqList P); /*最大堆的删除(即弹出一个元素)*/

/*主函数*/
int main(int agrc, char const* argv[]) 
{
	bool IsFull, IsEmpty;
	int i, j;
	ElemType InsertData, DeleteItem, data=0;
	
	/*创建一个堆序列,把待排序列一个一个插入到堆中并调整成最大堆*/ 
	PtrlSqList H=CreatList(); 
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
	printf("\n待排序列长度=%d\n", P->length); 
	
	/*把待排序列元素一个个插入到堆中同时做调整*/
	/*for循环中i<=P->length+1是为了把-1结束标志也存进去*/
	for (i=1; i<=P->length+1; i++) {
		Insert(H, P->arr[i]);
		P->arr[i]=0;
		j=i;
	} 
	P->arr[j]=-1; /*结束符*/
	
	printf("\n最大堆H：");
	PrintList(H, 0);
	/*获取最大堆的长度*/
	H->length=GetListLength(H);
	printf("\n最大堆H的长度=%d\n", H->length); 

	printf("\n回归过程:\n");
	j=P->length;
	for (i=1; i<=P->length; i++) {
		P->arr[j]=Delete(H);
		PrintList(P, 0);
		printf("\n");
		j--;
	}
	
	printf("\n堆排序后序列：");
	PrintList(P, 0);
	return 0;
} 

/*序列的创建*/
PtrlSqList CreatList() 
{
	PtrlSqList P=(PtrlSqList)malloc(sizeof(struct SqList));
	P->arr[0]=MaxData; /*哨兵*/
	P->arr[1]=-1;
	P->NowSize=0; /*NowSize记录当前堆大小,也就是最后一个元素的位置下标*/
	P->MaxContent=MaxData; /*记录堆的最大容量*/
	
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

/*判断最大堆是否已满*/
bool IsFull(PtrlSqList P) 
{
	return (P->MaxContent==P->NowSize);
} 

/*判断最大堆是否为空*/
bool IsEmpty(PtrlSqList P)
{
	return (P->NowSize==0);
}

/*最大堆的插入*/
void Insert(PtrlSqList H, ElemType X)
{
	int i;
	/*插入前先判断堆满不满*/
	if (IsFull(H)) {
		printf("最大堆已满,无法插入.");
		return;
	}
	/*没有满就插入*/
	i=++H->NowSize; /*因为NowSize记录的是当前堆中最后一个元素的下标,所以在它后面做插入*/
	 
	/*调整插入的位置,如果i位置的父结点比插入的值小,就把父结点移动下来*/
	/*i/2是i的父结点,2i是左子树,2i+1是右子树*/
	for (; H->arr[i/2]<X; i/=2) {
		H->arr[i]=H->arr[i/2]; /*把父结点往下移*/
	} 
	/*i的父结点不比要插入的X小了,那么就插入X到i*/
	H->arr[i]=X;
}

/*最大堆的删除(即弹出一个元素)*/ 
ElemType Delete(PtrlSqList H) 
{
	int Head, Max; /*Head是要插入的位置, Max是Head的子结点的下标位置*/
	ElemType DeleteItem, Tag;
	
	/*弹出一个元素前,先判断堆为不为空*/
	if (IsEmpty(H)) {
		printf("最大堆为空.");
		return;
	}
	/*不为空就弹出元素*/
	DeleteItem=H->arr[1]; /*先把要弹出的结点保存起来,最后返回出去*/
	Tag=H->arr[H->NowSize--]; /*保存弹出一个元素后,堆中最后一个元素(最小元素)的下标*/
	
	/*下面的操作是把弹出一个元素后的堆调整回最大堆*/
	/*Head*2是判断该结点是否有左子树,Head*2是左子树,Head*2+1是右子树*/
	/*Head即要插入的位置从1开始,即从第一个顶点(根节点)开始判断*/
	for (Head=1; Head*2<=H->NowSize; Head=Max) {
		/*如果有左子树,就判断左子树和右子树谁更大*/
		/*Head*2<=NowSize判断当前要插入的位置是否有左子树,如果左子树==NowSize,则没右子树*/
		Max=Head*2; /*一开始先让Max的值是左子树的位置下标,即指向左子树*/
		/*如果左子树结点小于右子树结点*/
		if ((H->arr[Max]<H->arr[Max+1]) && (Max!=H->NowSize)) {
			/*Max!=H->NowSize,证明有右子树*/
			/*就把Max指向更大的右子树的位置*/ 
			Max++;
		}
		/*一轮循环找到当前要插入的位置的左右子树的更大的那个位置Max后*/ 
		/*比较我当前要插入的元素Tag是否比左右子树大,是就直接插入*/ 
		if (Tag>=H->arr[Max]) {
			break;
		} else {
			/*否则就把更大的那个值提上来,调成最大堆的规律*/
			/*而我Tag要插入的位置下移,下移操作是for循环的最后Head=Max*/
			/*Head=Max即把Head的子树位置给了自己,让自己下移了*/
			H->arr[Head]=H->arr[Max]; 
		} 
	}
	/*for循环做完后,即找到正确的插入位置,就插入Tag元素*/
	H->arr[Head]=Tag;
	
	return DeleteItem;
}
