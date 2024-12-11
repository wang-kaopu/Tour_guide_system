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
/// 初始化并查集
/// </summary>
/// <param name="S"></param>
/// <param name="n"></param>
/// <returns></returns>
Status InitMFSet(MFSet& S, int n);

/// <summary>
/// 摧毁并查集
/// </summary>
/// <param name="S"></param>
/// <returns></returns>
Status DestroyMFSet(MFSet& S);

/// <summary>
/// 查找元素i
/// </summary>
/// <param name="S"></param>
/// <param name="i"></param>
/// <returns></returns>
int FindMFSet(MFSet& S, int i);

/// <summary>
/// 判断元素i和j是否在同一个集合
/// </summary>
/// <param name="S"></param>
/// <param name="i"></param>
/// <param name="j"></param>
/// <returns></returns>
Status DiffMFSet(MFSet& S, int i, int j);

/// <summary>
/// 把i元素所在集合合并到j元素所在集合
/// </summary>
/// <param name="S"></param>
/// <param name="i"></param>
/// <param name="j"></param>
/// <returns></returns>
Status UnionMFSet(MFSet& S, int i, int j);

/// <summary>
/// 按加权合并规则合并i和j所在集合 
/// </summary>
/// <param name="S"></param>
/// <param name="i"></param>
/// <param name="j"></param>
/// <returns></returns>
Status UnionMFSet_WUR(MFSet& S, int i, int j);

/// <summary>
/// 查找元素i所在的集合（路径压缩法）
/// </summary>
/// <param name="S"></param>
/// <param name="i"></param>
/// <returns></returns>
int FindMFSet_PC(MFSet& S, int i);

/// <summary>
/// 判断a和b是否有关系，查找过程中调用路径压缩法
/// </summary>
/// <param name="S"></param>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
Status HasRelationship(MFSet& S, int a, int b);

/// <summary>
/// 打印并查集
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
	// 加权合并法
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
	// 路径压缩法
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
