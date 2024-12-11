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
typedef struct {
	KeyType key;
}RcdType;

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