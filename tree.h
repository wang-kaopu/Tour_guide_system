
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include "tool.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define UNVISITED 0
#define VISITED 1

typedef int Status;
typedef int VexType;

// 树

// 孩子兄弟表示法
// CSTNode: 树结点
// CSTree: 树
// CSForest: 森林
// firstChild: 第一个孩子
// nextSibling: 第一个右兄弟
typedef struct CSTNode {
	VexType data;
	struct CSTNode* firstChild, * nextSibling;
}CSTNode, * CSTree, * CSForest;

// 为T插入孩子，位置是最后一个
Status InsertChild(CSTree& T, CSTree c) {
	// 0. 空树不能插入
	if (NULL == T) {
		return ERROR;
	}
	// 1. 插入在第1个，需要修改T->firstChild，单独处理
	if (NULL == T->firstChild) {
		c->nextSibling = T->firstChild;
		T->firstChild = c;
	}
	// 2. i > 1，需要注意修改两个结点的指针域：第i - 1个的nextSibling、被插入的c的nextSibling
	else {
		CSTree p = T->firstChild;
		// p走到最后一个
		while (p->nextSibling) {
			p = p->nextSibling;
		}
		p->nextSibling = c;
	}
	return OK;
}