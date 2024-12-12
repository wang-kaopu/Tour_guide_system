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

void InitQueue_LQ(LQueue& Q) {
	LQNode* node = (LQNode*)malloc(sizeof(LQNode));
	if (NULL == node) {
		return;
	}
	node->next = NULL;
	Q.front = Q.rear = node;
}

void DestroyQueue_LQ(LQueue& Q) {
	LQNode* node;
	while (Q.front != NULL) {
		node = Q.front;
		Q.front = node -> next;
		free(node);
	}
}

Status QueueEmpty_LQ(LQueue Q){
	return Q.front == Q.rear;
}

int QueueLength_LQ(LQueue Q) {
	int length = 0;
	for (LQNode* it = Q.front;it->next != NULL;it = it->next) {
		length++;
	}
	return length;
}

Status GetHead_LQ(LQueue Q, Elemtype& e) {
	if (Q.front == Q.rear) {
		return FALSE;
	}
	e = Q.front->data;
	return OK;
}

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

Status DeQueue_LQ(LQueue& Q, Elemtype& e) {
	if (Q.front == Q.rear) {
		return ERROR;
	}
	e = Q.front->data;
	LQNode* node = Q.front;
	Q.front = node->next;
	free(node);
	return OK;
}

void CopyQueue_LQ(LQueue& T, LQueue Q) {
	// LQNode* node = (LQNode*)malloc(sizeof(LQNode));
	// if (NULL == node) {
	// 	return;
	// }
	// node->next = NULL;
	// T.front = T.rear = node;
	LQNode* p = Q.front;
	InitQueue_LQ(T);
	while (p->next) {
		EnQueue_LQ(T, p->data);
		p = p->next;
	}
}

void PrintQueue_LQ(LQueue Q) {
	QueuePtr p = Q.front;
	if (p->next) {
		printf("%d", p->data);
	}
	p = p->next;
	while (p->next) {
		printf("->%d", p->data);
		p = p->next;
	}
}