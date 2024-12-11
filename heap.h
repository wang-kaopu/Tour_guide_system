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
typedef struct {
	KeyType key;
}RcdType;

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