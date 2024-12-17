#pragma once

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1

#include <stdlib.h>

/// Elemtype: 元素类型
typedef int Elemtype;

/// Status: 状态
typedef int Status;

/// LQNode: 链队列结点
/// QueuePtr: 链队列头尾结点指针
typedef struct LQNode {
	Elemtype data;
	struct LQNode* next;
}LQNode, *QueuePtr;

/// LQueue: 链队列
typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LQueue;

// 初始化队列
void InitQueue_LQ(LQueue& Q) {
	LQNode* node = (LQNode*)malloc(sizeof(LQNode));
	if (NULL == node) {
		return;
	}
	node->next = NULL;
	Q.front = Q.rear = node;
}

// 摧毁队列
void DestroyQueue_LQ(LQueue& Q) {
	LQNode* node;
	while (Q.front != NULL) {
		node = Q.front;
		Q.front = node -> next;
		free(node);
	}
}

// 队列判空
Status QueueEmpty_LQ(LQueue Q){
	return Q.front == Q.rear;
}

// 求队列长度
int QueueLength_LQ(LQueue Q) {
	int length = 0;
	for (LQNode* it = Q.front;it->next != NULL;it = it->next) {
		length++;
	}
	return length;
}

// 元素入队
Status EnQueue_LQ(LQueue& Q, Elemtype e) {
	LQNode* node = (LQNode*)malloc(sizeof(LQNode));
	if (NULL == node) {
		return OVERFLOW;
	}
	Q.rear->data = e;
	node->next = NULL;
	Q.rear->next = node;
	Q.rear = node;
	return OK;
}

// 复制队列Q到T
void CopyQueue_LQ(LQueue& T, LQueue Q) {
	LQNode* p = Q.front;
	InitQueue_LQ(T);
	while (p->next) {
		EnQueue_LQ(T, p->data);
		p = p->next;
	}
}

// // 打印队列
// void PrintQueue_LQ(LQueue Q) {
// 	QueuePtr p = Q.front;
// 	if (p->next) {
// 		printf("%d", p->data);
// 	}
// 	p = p->next;
// 	while (p->next) {
// 		printf("->%d", p->data);
// 		p = p->next;
// 	}
// }

// // 删除元素
// Status DeQueue_LQ(LQueue& Q, Elemtype& e) {
// 	if (Q.front == Q.rear) {
// 		return ERROR;
// 	}
// 	e = Q.front->data;
// 	LQNode* node = Q.front;
// 	Q.front = node->next;
// 	free(node);
// 	return OK;
// }
