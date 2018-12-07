#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20
#define ElemType int

//待排序列的存储结构
typedef struct SqlList *PtrlSqlList;
struct SqlList {
	ElemType arr[MaxSize+1]; //待排序列
	int length; //待排序列的长度 
}; 

//函数声明
PtrlSqlList InitialList(); //序列初始化
void Insert_Array(PtrlSqlList P, ElemType K); //序列插入元素
void PrintList(PtrlSqlList P, int count); //输出序列
int GetListLength(PtrlSqlList P); //计算序列长度
void Swap(ElemType Left, ElemType Right, PtrlSqlList P); //交换两元素位置 
ElemType Median3(PtrlSqlList P, int Left, int Right); //选择枢轴 
void QuickSort(PtrlSqlList P, int N); //快速排序接口 
void Quick_Sort(PtrlSqlList P, int Low, int High); //快速排序
void Insertion_Sort(PtrlSqlList P, int Left, int N); //插入排序
void PrintList2(PtrlSqlList P, int Left, int Right); //输出序列2 

int main(int argc, char const* argv[]) 
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
	
	//快速排序 
	printf("快速排序过程：\n");
	QuickSort(P, P->length);
	printf("\n快速排序后序列:");
	PrintList(P, 0);
	
	return 0; 
}

//序列初始化
PtrlSqlList InitialList()
{
	PtrlSqlList P=(PtrlSqlList)malloc(sizeof(struct SqlList));
	P->arr[0]=MaxSize; //哨兵 
	P->arr[1]=-1;	
	P->length=0; //初始化序列长度为0,不算哨兵
	
	return P; 
} 

//序列插入元素
void Insert_Array(PtrlSqlList P, ElemType K)
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
	int j=0;
	
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
} 

//输出序列2
void PrintList2(PtrlSqlList P, int Left, int Right)
{
	int i=0;
	
	for (i=Left; i<=Right; i++) {
		printf("%d ", P->arr[i]);
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
	
	return length-1;
} 

//交换两元素位置
void Swap(ElemType Left, ElemType Right, PtrlSqlList P) 
{
	int Tmp=P->arr[Right];
	P->arr[Right]=P->arr[Left];
	P->arr[Left]=Tmp;
} 

//选择枢轴 
ElemType Median3(PtrlSqlList P, int Left, int Right) 
{
	int i=0;
	
	//取序列的第一位,中间位和最后一位数,取中位数. 
	int Center=(Left+Right)/2;
	if (P->arr[Left]>P->arr[Center]) {
		Swap(Left, Center, P);
	}
	if (P->arr[Left]>P->arr[Right]) {
		Swap(Left, Right, P);
	}
	if (P->arr[Center]>P->arr[Right]) {
		Swap(Center, Right, P);
	}
	
	//printf("\n枢轴序列排序后: %d %d %d", P->arr[Left], P->arr[Center], P->arr[Right]);
	//此时应该 P->arr[Left] < P->arr[Center] < P->arr[Right] 
	
	/*将枢轴元素换到Right-1的位置,因为此时Right位置的元素一定大于
	 *Center位置的枢轴,Left位置的元素一定小于枢轴,所以接下来的操作
	 *只需要对Left+1到Right-2这一段序列做操作即可
	 */ 
	Swap(Center, Right-1, P); 
	 
	return P->arr[Right-1]; //把枢轴返回出去 
}

//快速排序接口
void QuickSort(PtrlSqlList P, int N)
{
	Quick_Sort(P, 1, N);
	
	return;
} 

//快速排序
void Quick_Sort(PtrlSqlList P, int Left, int Right)
{
	int Low, High;
	int cutoff=3; //阈值 
	Low=Left;
	High=Right-1;
	
	//自行决定是否判断如果待排序列元素少于阈值,就采用简单插入排序法
//	if (cutoff<=Right-Left) {
		if (Left<Right) {
			//获得枢轴,完成后枢轴在Right-1位置
			ElemType pivotkey=Median3(P, Left, Right);
			printf("\nLow=%d High=%d\n", Low, High);
			printf("枢轴pivotkey=%d\n", pivotkey);
			while(1) {
				PrintList(P, 0);
				printf("\n");
			//从Low开始向右遍历,直到找到第一个比枢轴大的元素,就停止 
			while (P->arr[++Low]<pivotkey);
			//同理从High开始向左遍历,直到找到第一个比枢轴小的元素,就停止 
			while (P->arr[--High]>pivotkey);
			
			if (Low<High) {
				//交换两个位置的元素,完成一趟快排 
				Swap(Low, High, P);
			} else {
					break; //如果Low和High错位了,就停止 
				}
			}
			printf("Left=%d Right=%d 枢轴位置=%d\n", Left, Right, Low);
			//Low和High错位之后,Low就是枢轴的位置,因为是升序排序,把枢轴换到正确的位置
			if (Right-Left>1) {
				Swap(Low, Right-1, P);
			}
			
			//输出每一趟排序过程
			PrintList(P, 0);
			printf("\n\n");
			
			//开始递归解决左右序列
			Quick_Sort(P, Left, Low-1); //递归解决左边 
			Quick_Sort(P, Low+1, Right); //递归解决右边 
			 
			return;
		}  	
//	} else {
//		if (Right!=Left) {
//			printf("\n待排序列数据量少于阈值,调用插入排序....\n");
//			//如果排列的数据量小于阈值,就采用简单的插入排序法
//			Insertion_Sort(P, Left, Right-Left+1);
//		}	
//	} 
}

/*直接插入排序*/
void Insertion_Sort(PtrlSqlList P, int Left, int N) 
{
	int i, j, Tmp, flag;
	for (i=Left+1; i<=N; i++) {
		Tmp=P->arr[i]; /*从序列中逐个拿出元素*/
		printf("Tmp=%d\n", Tmp);
		for (j=i; j>Left && P->arr[j-1]>Tmp; j--) {
			P->arr[j]=P->arr[j-1]; /*往后挪一位*/
		}
		P->arr[j]=Tmp; /*最后找到比Tmp大的数都往后挪了,留下正确的位置就插入*/
		PrintList2(P, Left, Left+N+1); /*此为输出序列函数,此处每次输出一次排序后的序列*/ 
		printf("\n");
	}
} 
