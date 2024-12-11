#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1

typedef int Status;
typedef int KeyType;

typedef struct {
	int* parent;
	int n;
}PForest, MFSet;

/// <summary>
/// ��ʼ�����鼯
/// </summary>
/// <param name="S"></param>
/// <param name="n"></param>
/// <returns></returns>
Status InitMFSet(MFSet& S, int n);

/// <summary>
/// �ݻٲ��鼯
/// </summary>
/// <param name="S"></param>
/// <returns></returns>
Status DestroyMFSet(MFSet& S);

/// <summary>
/// ����Ԫ��i
/// </summary>
/// <param name="S"></param>
/// <param name="i"></param>
/// <returns></returns>
int FindMFSet(MFSet& S, int i);

/// <summary>
/// �ж�Ԫ��i��j�Ƿ���ͬһ������
/// </summary>
/// <param name="S"></param>
/// <param name="i"></param>
/// <param name="j"></param>
/// <returns></returns>
Status DiffMFSet(MFSet& S, int i, int j);

/// <summary>
/// ��iԪ�����ڼ��Ϻϲ���jԪ�����ڼ���
/// </summary>
/// <param name="S"></param>
/// <param name="i"></param>
/// <param name="j"></param>
/// <returns></returns>
Status UnionMFSet(MFSet& S, int i, int j);

/// <summary>
/// ����Ȩ�ϲ�����ϲ�i��j���ڼ��� 
/// </summary>
/// <param name="S"></param>
/// <param name="i"></param>
/// <param name="j"></param>
/// <returns></returns>
Status UnionMFSet_WUR(MFSet& S, int i, int j);

/// <summary>
/// ����Ԫ��i���ڵļ��ϣ�·��ѹ������
/// </summary>
/// <param name="S"></param>
/// <param name="i"></param>
/// <returns></returns>
int FindMFSet_PC(MFSet& S, int i);

/// <summary>
/// �ж�a��b�Ƿ��й�ϵ�����ҹ����е���·��ѹ����
/// </summary>
/// <param name="S"></param>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
Status HasRelationship(MFSet& S, int a, int b);

/// <summary>
/// ��ӡ���鼯
/// </summary>
/// <param name="S"></param>
void PrintSet(MFSet& S);

Status InitMFSet(MFSet& S, int n) {
	S.n = n;
	S.parent = (int*)malloc(sizeof(int) * n);
	if (NULL == S.parent) {
		return OVERFLOW;
	}
	for (int i = 0;i < n;++i) {
		S.parent[i] = -1;
	}
	return OK;
}

Status DestroyMFSet(MFSet& S) {
	S.n = 0;
	if (NULL == S.parent) {
		return OK;
	}
	free(S.parent);
	S.parent = NULL;
	return OK;
}

int FindMFSet(MFSet& S, int i) {
	if (i < 0 || i >= S.n) {
		return -1;
	}
	while (S.parent[i] >= 0) {
		i = S.parent[i];
	}
	return i;
}

Status DiffMFSet(MFSet& S, int i, int j) {
	return FindMFSet(S, i) == FindMFSet(S, j);
}

Status UnionMFSet(MFSet& S, int i, int j) {
	if (i < 0 || i >= S.n || j < 0 || j >= S.n) {
		return FALSE;
	}
	int set_i = FindMFSet(S, i);
	int set_j = FindMFSet(S, j);
	S.parent[set_j] += S.parent[set_i];
	S.parent[set_i] = set_j;
	return TRUE;
}

Status UnionMFSet_WUR(MFSet& S, int i, int j) {
	if (i < 0 || i >= S.n || j < 0 || j >= S.n) {
		return FALSE;
	}
	// ��Ȩ�ϲ���
	int set1 = FindMFSet(S, i);
	int set2 = FindMFSet(S, j);
	if (S.parent[set1] > S.parent[set2]) {
		S.parent[set2] += S.parent[set1];
		S.parent[set1] = set2;
	}
	else {
		S.parent[set1] += S.parent[set2];
		S.parent[set2] = set1;
	}
	return TRUE;
}

int FindMFSet_PC(MFSet& S, int i) {
	if (i < 0 || i >= S.n) {
		return -1;
	}
	// ·��ѹ����
	if (S.parent[i] < 0) {
		return i;
	}
	S.parent[i] = FindMFSet_PC(S, S.parent[i]);
	return S.parent[i];
}

Status HasRelationship(MFSet& S, int a, int b) {
	if (a < 0 || a >= S.n || b < 0 || b >= S.n) {
		return FALSE;
	}
	return FindMFSet_PC(S, a) == FindMFSet_PC(S, b);
}

void PrintSet(MFSet& S) {
	printf("n = %d:\t", S.n);
	for (int i = 0;i < S.n;++i) {
		printf("%d ", S.parent[i]);
	}
	printf("\n");
}
