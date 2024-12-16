#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef int Status;
typedef int KeyType;

// 记录类型
// key: 该记录的关键字
// typedef struct {
// 	KeyType key;
// }RcdType;

// 求最小生成树：Kruscal算法
typedef struct {
    int v, w;
    int key;
} KruscalRcdType;

typedef KruscalRcdType RcdType;

// 堆类型
// rcd: 记录数组
// n: 当前堆的元素个数
// size: 堆容量
// tag: 大小顶堆标志，0表示小顶堆，1表示大顶堆
// prior: 堆顶优先函数，用于关键字优先级比较
typedef struct {
	RcdType* rcd;
	int n;
	int size;
	int tag;
	int (*prior)(KeyType x, KeyType y);
}Heap;

/// <summary>
/// 初始化堆
/// </summary>
/// <param name="H">目标堆</param>
/// <param name="size">堆容量</param>
/// <param name="tag">大小顶堆标志</param>
/// <param name="prior">优先函数</param>
/// <returns></returns>
Status InitHeap(Heap& H, int size, int tag, int(*prior)(KeyType x, KeyType y));

/// <summary>
/// 根据传入的记录数组创建堆
/// </summary>
/// <param name="H">目标堆</param>
/// <param name="E">记录数组</param>
/// <param name="n">记录数组的大小</param>
/// <param name="size">堆容量</param>
/// <param name="tag">大小顶堆标志</param>
/// <param name="prior">优先函数</param>
void MakeHeap(Heap& H, RcdType* E, int n, int size, int tag, int(*prior)(KeyType x, KeyType y));

/// <summary>
/// 摧毁堆
/// </summary>
/// <param name="H"></param>
/// <returns></returns>
Status DestroyHeap(Heap& H);

/// <summary>
/// 将H中pos位置的元素向下筛选
/// </summary>
/// <param name="H"></param>
/// <param name="pos"></param>
void ShiftDown(Heap& H, int pos);

/// <summary>
/// 将元素e插入堆
/// </summary>
/// <param name="H"></param>
/// <param name="e"></param>
/// <returns></returns>
Status InsertHeap(Heap& H, RcdType e);

/// <summary>
/// 删除堆顶结点，并用e返回
/// </summary>
/// <param name="H"></param>
/// <param name="e"></param>
/// <returns></returns>
Status RemoveFirstHeap(Heap& H, RcdType& e);

/// <summary>
/// 删除H中pos位置的结点，并用e返回
/// </summary>
/// <param name="H"></param>
/// <param name="pos"></param>
/// <param name="e"></param>
/// <returns></returns>
Status RemoveHeap(Heap& H, int pos, RcdType& e);

/// <summary>
/// 堆排序
/// </summary>
/// <param name="rcd"></param>
/// <param name="length"></param>
/// <param name="size"></param>
/// <param name="tag"></param>
/// <param name="prior"></param>
void HeapSort(RcdType* rcd, int length, int size, int tag, int (*prior)(KeyType x, KeyType y));

/// <summary>
/// 大顶堆优先函数
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
int greaterPrior(int x, int y);

/// <summary>
/// 小顶堆优先函数
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
int lessPrior(int x, int y);

Status InitHeap(Heap& H, int size, int tag, int(*prior)(KeyType x, KeyType y)) {
	Heap* p = (Heap*)malloc(sizeof(Heap));
	if (NULL == p) {
		return ERROR;
	}
	H = *p;
	H.size = size;
	H.n = 0;
	H.tag = tag;
	H.prior = prior;
	return OK;
}
void MakeHeap(Heap& H, RcdType* E, int n, int size, int tag, int(*prior)(KeyType x, KeyType y)) {
	H.rcd = E;
	H.n = n;
	H.size = size;
	H.tag = tag;
	H.prior = prior;
	for (int p = H.n / 2;p >= 1;--p) {
		ShiftDown(H, p);
	}
	//for (int i = 0; i < 40;++i) {
	//	printf("%d ", H.rcd[i + 1]);
	//}
	//printf("\n");
}
Status DestroyHeap(Heap& H) {
	free(&H);
	return OK;
}
Status SwapHeapElem(Heap& H, int i, int j) {
	if (i <= 0 || i > H.n || j <= 0 || j > H.n) {
		return ERROR;
	}
	RcdType tmp = H.rcd[i];
	H.rcd[i] = H.rcd[j];
	H.rcd[j] = tmp;
	return OK;
}
void ShiftDown(Heap& H, int pos) {
	while (pos <= H.n / 2) {
		int rchild = pos * 2 + 1, p = pos * 2;
		if (rchild <= H.n && H.prior(H.rcd[rchild].key, H.rcd[p].key)) {
			p = rchild;
		}
		if (H.prior(H.rcd[pos].key, H.rcd[p].key)) {
			return;
		}
		SwapHeapElem(H, pos, p);
		pos = p;
	}
}
Status InsertHeap(Heap& H, RcdType e) {
	if (H.n > H.size - 1) {
		return ERROR;
	}
	H.rcd[++H.n] = e;
	for (int p = H.n;p / 2 >= 1 && H.prior(H.rcd[p].key, H.rcd[p / 2].key);p /= 2) {
		SwapHeapElem(H, p, p / 2); //不用shiftDown是因为p的兄弟和p的父亲这两个一定有序，shiftDown还会判断这对之后再决定是否交换
	}
	return OK;
}
Status RemoveFirstHeap(Heap& H, RcdType& e) {
	if (0 >= H.n) {
		return ERROR;
	}
	e = H.rcd[1];
	SwapHeapElem(H, 1, H.n);
	H.n--;
	if (H.n > 1) {
		ShiftDown(H, 1);
	}
	return OK;
}
Status RemoveHeap(Heap& H, int pos, RcdType& e) {
	if (0 == H.n) {
		return ERROR;
	}
	e = H.rcd[pos];
	SwapHeapElem(H, pos, H.n);
	H.n--;
	if (H.n > 1) {
		ShiftDown(H, pos);
	}
	return OK;
}

void HeapSort(RcdType* rcd, int length, int size, int tag, int (*prior)(KeyType x, KeyType y)) {
	Heap H;
	RcdType r;
	MakeHeap(H, rcd, length, size, tag, prior);
	while (H.n >= 1) {
		RemoveFirstHeap(H, r);
	}
}

// 大顶堆优先函数
int greaterPrior(int x, int y) {
	return x >= y;
}

// 小顶堆优先函数
int lessPrior(int x, int y) {
	return x <= y;
}