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

// ��¼����
// key: �ü�¼�Ĺؼ���
// typedef struct {
// 	KeyType key;
// }RcdType;

// ����С��������Kruscal�㷨
typedef struct {
    int v, w;
    int key;
} KruscalRcdType;

typedef KruscalRcdType RcdType;

// ������
// rcd: ��¼����
// n: ��ǰ�ѵ�Ԫ�ظ���
// size: ������
// tag: ��С���ѱ�־��0��ʾС���ѣ�1��ʾ�󶥶�
// prior: �Ѷ����Ⱥ��������ڹؼ������ȼ��Ƚ�
typedef struct {
	RcdType* rcd;
	int n;
	int size;
	int tag;
	int (*prior)(KeyType x, KeyType y);
}Heap;

/// <summary>
/// ��ʼ����
/// </summary>
/// <param name="H">Ŀ���</param>
/// <param name="size">������</param>
/// <param name="tag">��С���ѱ�־</param>
/// <param name="prior">���Ⱥ���</param>
/// <returns></returns>
Status InitHeap(Heap& H, int size, int tag, int(*prior)(KeyType x, KeyType y));

/// <summary>
/// ���ݴ���ļ�¼���鴴����
/// </summary>
/// <param name="H">Ŀ���</param>
/// <param name="E">��¼����</param>
/// <param name="n">��¼����Ĵ�С</param>
/// <param name="size">������</param>
/// <param name="tag">��С���ѱ�־</param>
/// <param name="prior">���Ⱥ���</param>
void MakeHeap(Heap& H, RcdType* E, int n, int size, int tag, int(*prior)(KeyType x, KeyType y));

/// <summary>
/// �ݻٶ�
/// </summary>
/// <param name="H"></param>
/// <returns></returns>
Status DestroyHeap(Heap& H);

/// <summary>
/// ��H��posλ�õ�Ԫ������ɸѡ
/// </summary>
/// <param name="H"></param>
/// <param name="pos"></param>
void ShiftDown(Heap& H, int pos);

/// <summary>
/// ��Ԫ��e�����
/// </summary>
/// <param name="H"></param>
/// <param name="e"></param>
/// <returns></returns>
Status InsertHeap(Heap& H, RcdType e);

/// <summary>
/// ɾ���Ѷ���㣬����e����
/// </summary>
/// <param name="H"></param>
/// <param name="e"></param>
/// <returns></returns>
Status RemoveFirstHeap(Heap& H, RcdType& e);

/// <summary>
/// ɾ��H��posλ�õĽ�㣬����e����
/// </summary>
/// <param name="H"></param>
/// <param name="pos"></param>
/// <param name="e"></param>
/// <returns></returns>
Status RemoveHeap(Heap& H, int pos, RcdType& e);

/// <summary>
/// ������
/// </summary>
/// <param name="rcd"></param>
/// <param name="length"></param>
/// <param name="size"></param>
/// <param name="tag"></param>
/// <param name="prior"></param>
void HeapSort(RcdType* rcd, int length, int size, int tag, int (*prior)(KeyType x, KeyType y));

/// <summary>
/// �󶥶����Ⱥ���
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
int greaterPrior(int x, int y);

/// <summary>
/// С�������Ⱥ���
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
		SwapHeapElem(H, p, p / 2); //����shiftDown����Ϊp���ֵܺ�p�ĸ���������һ������shiftDown�����ж����֮���پ����Ƿ񽻻�
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

// �󶥶����Ⱥ���
int greaterPrior(int x, int y) {
	return x >= y;
}

// С�������Ⱥ���
int lessPrior(int x, int y) {
	return x <= y;
}