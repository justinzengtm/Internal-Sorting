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
PtrlSqList CreatList(); /*序列的初始化*/
void Insert_Array(PtrlSqList P, int K); /*序列插入元素*/
void PrintList(PtrlSqList P, int count); /*输出序列*/
int GetListLength(PtrlSqList P); /*计算序列的长度*/
void Merge_Sort(PtrlSqList P, int length); /*归并排序*/
void Msort(PtrlSqList P, PtrlSqList M, int L, int RightEnd); /*递归归并排序*/
void Merge(PtrlSqList P, PtrlSqList M, int L, int R, int RightEnd); /*归并操作*/

int main(int argc, char const* argv[])
{
	ElemType data;
	
	/*创建一个待排序列*/
	PtrlSqList P=CreatList();
	printf("请创建待排序列:");
	while (data!=-1) {
		scanf("%d", &data);
		if (data!=-1) {
			Insert_Array(P, data);
		}
	}  
	/*获得待排序列的长度*/
	P->length=GetListLength(P);
	printf("待排序列长度为：%d\n\n", P->length);
	/*输出一下待排序列*/
	printf("待排序列为:");
	PrintList(P, 0);
	
	printf("\n\n归并排序递归过程:\n");
	Merge_Sort(P, P->length);
	
	printf("\n归并排序后序列:");
	PrintList(P, 0);
	
	return 0;
}
 
 /*序列的初始化*/
PtrlSqList CreatList() 
{
	PtrlSqList P=(PtrlSqList)malloc(sizeof(struct SqList));
	P->arr[0]=MaxSize; 
	P->arr[1]=-1;
	P->length=0; 
	
	return P; 
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

/*计算序列的长度*/
int GetListLength(PtrlSqList P) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		i++;
	}

	return (i-1);
}

/*归并排序*/
void Merge_Sort(PtrlSqList P, int length) 
{
	int i=0;
	/*创建一个额外空间存放有序序列*/
	PtrlSqList M=CreatList();
	for (i=0; i<=MaxSize; i++) {
		M->arr[i]=-1;
	}

	if (M->length!=MaxSize) {
		/*开始递归归并排序*/
		/*传进去的参数:待排序列P,存放有序序列M,最开始左边位置1,结束位置length*/
		Msort(P, M, 1, length); /*递归归并排序*/ 
		/*排序完后释放掉临时额外空间M*/
		free(M); 
	} else {
		/*如果归并排序没做完,M就没空间了*/ 
		printf("空间不足");
	}
}

/*递归归并排序*/
void Msort(PtrlSqList P, PtrlSqList M, int L, int RightEnd) 
{
	int Mid; /*取中间值,当作把序列平分的边界*/
	
	/*如果左边序列开头位置小于右边序列结束位置,即整体序列中还有元素*/
	if (L<RightEnd) {
		/*把待排序列序列平分*/
		Mid=(L+RightEnd)/2;
		/*然后递归归并左右两边*/
		Msort(P, M, L, Mid); /*左边序列*/
		Msort(P, M, Mid+1, RightEnd); /*右边序列*/ 
		/*递归中的归并操作,即合并两段有序序列*/
		Merge(P, M, L, Mid+1, RightEnd);
	}
}

/*归并操作*/
void Merge(PtrlSqList P, PtrlSqList M, int L, int R, int RightEnd) 
{
	/*L是左边序列的起始位置,R是右边序列的起始位置,RightEnd是右边序列的终点位置.*/
	/*L和R是指向两个序列的指针*/
	int LeftEnd, ElementNum, Tmp, i;
	
	LeftEnd=R-1; /*左序列的终点位置是右边序列起始位置-1*/ 
	Tmp=L; /*Tmp记录第一次序列的左开始位置,即等于1,下面用来给临时额外空间做插入用.*/
	ElementNum=RightEnd-L+1; /*!!!!*/
	printf("ElementNum=%d L=%d LeftEnd=%d R=%d RightEnd=%d\t", ElementNum, L, LeftEnd, R, RightEnd);
		
	/*当左边序列没到最后一个元素 && 右边序列也没到最后一个元素时,继续归并操作*/ 
	while (L<=LeftEnd && R<=RightEnd) {
		/*从左右序列的第一个元素开始亮两两比较*/
		if (P->arr[L]<=P->arr[R]) {
			M->arr[Tmp++]=P->arr[L++]; 
		} else {
			M->arr[Tmp++]=P->arr[R++];
		} 
	}
	
	/*当其中一个元素插入完后,把另一个序列的剩余元素全部插入到额外空间中*/
	while (L<=LeftEnd) {
		M->arr[Tmp++]=P->arr[L++];
	} 
	while (R<=RightEnd) {
		M->arr[Tmp++]=P->arr[R++];
	}
	/*把额外空间中排好序的序列复制回用户的序列中*/
	for (i=0; i<ElementNum && RightEnd>0; i++, RightEnd--) {
		P->arr[RightEnd]=M->arr[RightEnd];
	}  
	PrintList(P, 0);
	printf("\n\n"); //美观用
}
