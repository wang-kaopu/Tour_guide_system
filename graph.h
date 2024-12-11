#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include "tool.h"
#include "tree.h"
#include "queue.h"
#include "heap.h"
#include "union_find_sets.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define UNVISITED 0
#define VISITED 1
// #define INFINITY INT_MAX

typedef int Status;
typedef int VexType;

// VexType: 顶点类型
// id: 顶点id，作为顶点的唯一标识
// name：顶点名称，字符串，可重复
// vexInfo：顶点相关信息，字符串
// firstArc：顶点出度的弧 构成的链表 的头结点
typedef struct VexNode{
    VexType id;
    char* name;
    char* vexInfo;
    struct AdjVexNode* firstArc;
} VexNode; // vertex 顶点

// AdjVexNode：弧
// adjvex：弧的入度顶点 在顶点数组G.vexs中的位置
// next：存放链表的下一个弧结点
// weight：弧的权
typedef struct AdjVexNode
{
    int adjvex;
    struct AdjVexNode* next;
    int weight;
} AdjVexNode;

// ArcInfo: 边（弧）信息
// v_id：出度顶点的id
// w_id：入度顶点的id
// weight：权
typedef struct {
	VexType v_id, w_id; 
    int weight; 
} ArcInfo;

// Undirected Net 无向网
typedef struct {
	VexNode* vexs; // 顶点数组。vertex, 顶点
	int n, e; // n: 顶点数; e: 边数（弧数）
	int* tags; // 标志数组，可用于在图的遍历中标记顶点访问与否
} UDN;

typedef struct {
	VexNode* vexs; // 顶点数组。vertex, 顶点
	int n, e; // n: 顶点数; e: 边数（弧数）
	int* tags; // 标志数组，可用于在图的遍历中标记顶点访问与否
} DN;

// *
// 通过id找到顶点v在顶点数组vexs中的位置，查找成功则返回位置下标，否则返回-1
// G: 图
// v_id：目标顶点id
int LocateVex (UDN& G, VexType v_id) {
    for (int i = 0; i < G.n; ++i) {
        if (G.vexs[i].id == v_id) {
            return i;
        }
    }
    return -1;
}

// *
// 初始化图，只有顶点，没有弧
// G：图
// vexs：顶点数组
// n：顶点个数
Status InitUDN(UDN &G, VexType *vexs, int n) {
    G.n = n;
    G.tags = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        G.tags[i] = 0;
    }
    G.e = 0;
    G.vexs = (VexNode*)malloc(sizeof(VexNode) * n);
    for (int i = 0; i < n; i++) {
        G.vexs[i] = {vexs[i], NULL};
    }
    return OK;
}

// *
// 在图G中添加指定名称和信息的顶点，id被分配成功则返回该顶点id，否则返回-1
// G：图
// name：顶点名称
// vexInfo：顶点信息
int AddVex(UDN &G, char* name, char* vexInfo) {
    VexNode* node = (VexNode*)malloc(sizeof(VexNode));
    if (NULL == node) {
        return -1;
    }
    int id = G.n == 0 ? 1 : G.vexs[G.n - 1].id + 1;
    node->id = id;
    node->name = name;
    node->vexInfo = vexInfo;
    node->firstArc = NULL;

    VexNode* vexNodes = NULL;
    if (G.n == 0) {
        vexNodes = (VexNode*)malloc(sizeof(VexNode) * (G.n + 1));
    }
    else {
        vexNodes = (VexNode*)realloc(G.vexs, sizeof(VexNode) * (G.n + 1));
    }
    if (NULL == vexNodes) {
        return -1;
    }
    G.vexs = vexNodes;
    G.vexs[G.n] = *node;

    G.n++;
    G.tags[G.n - 1] = 0;
    return OK;
}

// *
// 根据给定的顶点数组vexs和弧数组arcs创建无向网G
// G：图
// vexs：顶点数组
// n：顶点个数
// arcs：弧数组
// e：弧数
Status CreateUDN(UDN &G, VexType *vexs, char** name, int n, ArcInfo *arcs, int e) {   
    G.n = n;
    G.tags = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        G.tags[i] = 0;
    }
    G.e = e;
    G.vexs = (VexNode*)malloc(sizeof(VexNode) * n);
    for (int i = 0; i < n; i++) {
        G.vexs[i] = {vexs[i], name == NULL ? NULL : name[i], NULL};
    }
    for (int i = 0; i < e; i++) {
        int v_loc = LocateVex(G, arcs[i].v_id), w_loc = LocateVex(G, arcs[i].w_id);
        if (v_loc < 0 || w_loc < 0) {
            return ERROR;
        }
        AdjVexNode* node = (AdjVexNode*)malloc(sizeof(AdjVexNode));
        node->next = G.vexs[v_loc].firstArc;
        node->adjvex = w_loc;
        node->weight = arcs[i].weight;
        G.vexs[v_loc].firstArc = node;

        node = (AdjVexNode*)malloc(sizeof(AdjVexNode));
        node->next = G.vexs[w_loc].firstArc;
        node->adjvex = v_loc;
        node->weight = arcs[i].weight;
        G.vexs[w_loc].firstArc = node;
    }
    return OK;
}

// *
// 在图G中添加从顶点v到顶点w的弧、从顶点w到顶点v的弧
// G：图
// v_id：出度顶点
// w_id：入度顶点
// weight：权
Status SetArc(UDN &G, VexType v_id, VexType w_id, int weight) 
{  
    int v_loc = LocateVex(G, v_id);
    int w_loc = LocateVex(G, w_id);
    if (v_loc < 0 || w_loc < 0) {
        return ERROR;
    }
    AdjVexNode* node = (AdjVexNode*)malloc(sizeof(AdjVexNode));
    node->next = G.vexs[v_loc].firstArc;
    node->adjvex = w_loc;
    node->weight = weight;
    G.vexs[v_loc].firstArc = node;

    node = (AdjVexNode*)malloc(sizeof(AdjVexNode));
    node->next = G.vexs[w_loc].firstArc;
    node->adjvex = v_loc;
    node->weight = weight;
    G.vexs[w_loc].firstArc = node;

    G.e++;
    return OK;
}


// 修改指定id的顶点名称和顶点信息
// G：图
// id：顶点id
// name：顶点新的名称
// vexInfo：顶点新的信息
Status ModifyVex(UDN &G, VexType id, char* name, char* vexInfo) {
    for (int i = 0; i < G.n; ++i) {
        if (G.vexs[i].id == id) {
            G.vexs[i].name = name;
            G.vexs[i].vexInfo = vexInfo;
            return OK;
        }
    }
    return ERROR;
}

AdjVexNode* SearchArc(UDN& G, VexType v_id, VexType w_id) {
    int v_loc = LocateVex(G, v_id), w_loc = LocateVex(G, w_id);
    for (AdjVexNode* p = G.vexs[v_loc].firstArc; p; p = p->next) {
        if (p->adjvex == w_loc) {
            return p;
        }
    }
    return NULL;
}

Status ModifyArcWeight(UDN &G, ArcInfo& arcInfo) {
    VexType v_id = arcInfo.v_id, w_id = arcInfo.w_id;
    AdjVexNode* arcNode1 = SearchArc(G, v_id, w_id);
    AdjVexNode* arcNode2 = SearchArc(G, w_id, v_id);
    if (NULL == arcNode1 || NULL == arcNode2) {
        return ERROR;
    }
    arcNode1->weight = arcNode2->weight = arcInfo.weight;
    return OK;
}

Status DeleteArc(UDN &G, ArcInfo arc) {
    int v_loc = LocateVex(G, arc.v_id);
    int w_loc = LocateVex(G, arc.w_id);
    if (v_loc < 0 || w_loc < 0) {
        return ERROR;
    }
    for (int i = 0;i < 2; ++i) {
        if (G.vexs[v_loc].firstArc->adjvex == w_loc) {
            AdjVexNode* target = G.vexs[v_loc].firstArc;
            G.vexs[v_loc].firstArc = target->next;
            G.e--;
            free(target);
            target = NULL;
        }
        else {
            for (AdjVexNode* p = G.vexs[v_loc].firstArc; p->next; p = p->next) {
                if (p->next->adjvex == w_loc) {
                    AdjVexNode* target = p->next;
                    p->next = target->next;
                    G.e--;
                    free(target);
                    target = NULL;
                }
            }
        }
        swapInt(v_loc, w_loc);
    }
    return OK;
}

void ClearAdj(UDN& G, int i) {
    VexNode& vex = G.vexs[i];
    AdjVexNode* p = vex.firstArc, *q = (p ? p->next : NULL);
    while (p) {
        free(p);
        p = q;
        if (q) {
            q = q->next;
        }
    }
}

Status DeleteVex(UDN &G, VexType id) {
    int i = LocateVex(G, id);
    if (i == -1) {
        return ERROR;
    }
    ClearAdj(G, i);
    G.vexs = (VexNode*)deleteFromArray(G.vexs, G.n, i, sizeof(VexNode));
    G.n--;
    return OK;
}

// 搜索顶点
// VexNode* SearchVex(UDN G, VexType id) {
//     for (int i = 0; i < G.n; ++i) {
//         if (G.vexs[i].id == id) {
//             return &(G.vexs[i]);
//         }
//     }
//     return NULL;
// }

// 迪杰斯特拉算法：寻找最短路径
// 求图G中从i顶点到其他所有顶点的最短路径，并由Dist返回

// DistInfo：距离信息，用于实现Dijkstra算法时，创建辅助数组
typedef struct {
    int prev; // prev: i顶点到本顶点的最短路径上，本顶点的前驱
    int lowcost; // lowcost: i顶点到本顶点的最短路径的距离
    int single_dist; // single_dist: 前驱顶点到本顶点的距离
} DistInfo;

// Dijkstra算法实现
// G：图
// i：起始顶点在顶点数组vexs中的下标
// Dist：辅助数组，记录距离信息
void Dijkstra(UDN G, int i, DistInfo* Dist) {
    // DistInfo* Dist = *DistPtr;
    VexNode nodeI = G.vexs[i];
    // 1. 初始化Dist数组和G.tag数组
    for (int j = 0; j < G.n; ++j) {
        Dist[j] = {-1, INT_MAX, INT_MAX};
        G.tags[j] = 0;
    }
    Dist[i].lowcost = 0;
    int prev = i;
    // 2. 由前驱顶点出发，寻找下一次的前驱，并尝试更新Dist数组
    // 每次循环后更新前驱，直到所有顶点都作为前驱一次，循环结束
    while (prev >= 0) {
        // 标记本次更新Dist数组时的前驱prev
        G.tags[prev] = 1;
        // 更新Dist数组
        for (AdjVexNode* p = G.vexs[prev].firstArc; p; p = p->next) {
            int adj = p->adjvex;
            if (G.tags[adj] == 0 && Dist[adj].lowcost > Dist[prev].lowcost + p->weight) {
                Dist[adj].lowcost = Dist[prev].lowcost + p->weight;
                Dist[adj].prev = prev;
                Dist[adj].single_dist = p->weight;
            }
        }
        // 寻找下一次的前驱（prev出度的、lowcost最小的入度顶点）
        int next_prev = -1;
        for (int j = 0; j < G.n; ++j) {
            if (G.tags[j] == 0 && (next_prev == -1 || Dist[j].lowcost < Dist[next_prev].lowcost)) {
                next_prev = j;
            }
        }
        prev = next_prev;
    }
}

// 根据Dist数组打印终点为指定某一顶点的路径信息，其中，该顶点在顶点数组的下标为k
// G：图
// Dist：路径信息数组
// k：终点顶点在顶点数组中的下标
void OutputPath(UDN G, DistInfo* Dist, int k) {
    if (k < 0) {
        return;
    }
    OutputPath(G, Dist, Dist[k].prev);
    if (Dist[k].prev != -1) {
        printf("---(%d)--->%d", Dist[k].single_dist, G.vexs[k].id);
    }
    else {
        printf("%d", G.vexs[k].id);
    }
}

void OutputVexs(UDN G) {
    VexNode* vexs = G.vexs;
    printf("---\t---\t---\t\n");
    printf("ID\t名称\t信息\t\n");
    for (int i = 0 ;i < G.n; ++i) {
        VexNode node = vexs[i];
        printf("%d\t", node.id);
        if (node.name != NULL) {
            printf("%s\t", node.name);
        }
        else {
            printf("(暂无)\t");
        }
        if (node.vexInfo != NULL) {
            printf("%s\t\n", node.vexInfo);
        }
        else {
            printf("(暂无)\t\n");
        }
    }
    printf("---\t---\t---\t\n");
}

void OutputAllArcs(UDN G) {
    VexNode* nodes = G.vexs;
    printf("起点ID---\t---(权重)---\t---终点ID\t\n");
    for (int i = 0; i < G.n; ++i) {
        AdjVexNode* p = nodes[i].firstArc;
        while (p) {
            printf("%d---\t---(%d)---\t---%d\t\n", nodes[i].id, p->weight, p->adjvex);
            p = p->next;
        }
    }
}

void DFSprint(UDN& G, int i) {
    if (i < 0 || i >= G.n) {
        return;
    }
    printf("%d\t", G.vexs[i].id);
    if (G.vexs[i].name == NULL) {
        printf("（空）\t");
    }
    else {
        printf("%s\t", G.vexs[i].name);
    }
    if (G.vexs[i].vexInfo == NULL) {
        printf("（空）\t\n");
    }
    else {
        printf("%s\t\n", G.vexs[i].vexInfo);
    }
    G.tags[i] = 1;
    if (NULL != G.vexs[i].firstArc && G.tags[G.vexs[i].firstArc->adjvex] == 0) {
        DFSprint(G, G.vexs[i].firstArc->adjvex);
    }
}

// 深度优先遍历
void DFS(UDN& G) {
    memset(G.tags, sizeof(int) * G.n, 0);
    for (int i = 0;i < G.n; ++i) {
        if (G.tags[i] == 0) {
            DFSprint(G, i);
        }
    }
}

Status PrintSearchPathDFS(UDN G, int prev, int target) {
    if (target == prev) {
        return OK;
    }
    for (AdjVexNode* p = G.vexs[prev].firstArc; p; p = p->next){
        if (G.tags[p->adjvex] == 0) {
            if (PrintSearchPathDFS(G, p->adjvex, target)) {
                printf("%d->", p->adjvex);
                G.tags[p->adjvex] = 1;
            }
        }
    }
}

CSTree SearchPathBFS(UDN G, int bg, int end) {
    CSTree root = (CSTree)malloc(sizeof(CSTree));
    if (NULL == root) {
        return NULL;
    }
    root->data = bg;
    root->firstChild = root->nextSibling = NULL;
    G.tags[bg] = 1;
    if (root->data == end) {
        return root;
    }
    if (NULL == G.vexs[bg].firstArc) {
        return NULL;
    }
    int* ori_tags = (int*)malloc(sizeof(int) * G.n);
    for (AdjVexNode* p = G.vexs[bg].firstArc; p; p = p->next) {
        CSTree child;
        memmove(ori_tags, G.tags, sizeof(int) * G.n);
        if (G.tags[p->adjvex] == 0 && NULL != (child = SearchPathBFS(G, p->adjvex, end))) {
            InsertChild(root, child);
        }
        memmove(G.tags, ori_tags, sizeof(int) * G.n);
    }
    free(ori_tags);
    if (NULL == root->firstChild) {
        return NULL;
    }
    return root;
}

typedef struct {
    int* sq;
    int n;
} TopSq;

// 初始化拓扑排序辅助类型TopSq
void InitTopSq(TopSq& TS, int n) {
    TS.sq = (int*)malloc(sizeof(int) * n);
    TS.n = 0;
}

// 无向图 -> 有向图
void UDN_to_DN (UDN& G) {
    for (int i = 0; i < G.n; ++i) {
        for (AdjVexNode* p = G.vexs[i].firstArc; p; p = p->next) {
            int j = p->adjvex;
            AdjVexNode* q = G.vexs[j].firstArc;
            AdjVexNode* tmp = NULL;
            if (q->adjvex == i) {
                tmp = q;
                G.vexs[j].firstArc = q->next;
            }
            else {
                for (; q && q->next; q = q->next) {
                    if (q->next->adjvex == i) {
                        tmp = q->next;
                        q->next = q->next->next;
                    }
                }
            }
            free(tmp);
        }
    }
}

// 求最小生成树：Kruscal算法
typedef struct {
    int v, w;
    int key;
} KruscalRcdType;

// 构造G的最小生成树T
// Status Kruscal(UDN G, UDN& T) {
//     // 初始化T
//     T.n = G.n;
//     T.e = 0;
//     T.vexs = (VexNode*)malloc(sizeof(VexNode) * T.n);
//     memmove(T.vexs, G.vexs, sizeof(VexNode) * T.n);
//     for (int i = 0; i < T.n; ++i) {
//         T.vexs[i].firstArc  = NULL;
//     }
//     // 

// }

// 拓扑排序
Status ToplogicalSort(UDN G, TopSq& TS) {
    // 将有向图转化为无向图
    UDN_to_DN(G);
    // 辅助数组indegree，记录顶点入度
    int* indegree = (int*)malloc(sizeof(int) * G.n);
    memset(indegree, 0, sizeof(int) * G.n);
    // 辅助队列Q
    LQueue Q;
    InitQueue_LQ(Q);
    // 初始化辅助结构TopSq拓扑序列
    InitTopSq(TS, G.n);
    // 计算所有顶点的入度，存入indegree
    for (int i = 0; i < G.n; ++i) {
        for (AdjVexNode* p = G.vexs[i].firstArc; p; p = p->next) {
            ++indegree[p->adjvex];
        }
    }
    // 搜寻所有入度为0的顶点，入队
    for (int i = 0; i < G.n; ++i) {
        if (0 == indegree[i]) {
            EnQueue_LQ(Q, i);
        }
    }
    // 反复出队、加入拓扑序列、删除所有其出度的弧、搜寻、入队……
    int i = -1, count = 0;
    while (OK == DeQueue_LQ(Q, i)) {
        TS.sq[TS.n++] = i;
        ++count;
        for (AdjVexNode* p = G.vexs[i].firstArc; p; p = p->next) {
            if (0 == --indegree[p->adjvex]) {
                EnQueue_LQ(Q, p->adjvex);
            }
        }
    }
    // 释放辅助数组indegree空间
    free(indegree);
    // 判断是否成功生成拓扑序列
    if (count < G.n) {
        return ERROR;
    }
    return OK;
}

// 根据给定的顶点位置数组locs和顶点个数n，生成子图
// 根据子图生成最小生成树
// 子图->最小生成树（kruscal）
void PathPlanning(UDN G, int* locs, int n) {
    VexNode* nodes = (VexNode*)malloc(sizeof(VexNode) * n);
    if (NULL == nodes)  return;
    int k = 0;
    for (int i = 0; i < n; ++i) {
        nodes[k++] = G.vexs[locs[i]];
    }
    int e = 0;
    for (int i = 0; i < n; ++i) {
        for(AdjVexNode* p = nodes->firstArc; p; p = p->next) {
            ++e;
        }
    }
    int* tags = (int*)malloc(sizeof(int) * n);
    memset(tags, 0, sizeof(int) * n);
    UDN subG = {nodes, n, e, tags};

    nodes = subG.vexs;
    for (int i = 0; i < subG.n; ++i) {
        printf("%d:", nodes[i].id - 1);
        for (AdjVexNode* p = nodes[i].firstArc; p; p = p->next) {
            printf("%d(%d) ", p->adjvex, p->weight);
        }
        printf("\n");
    }
    printf("\n");

    // TopSq TS;
    // InitTopSq(TS, subG.n);
    // int result = ToplogicalSort(subG, TS);
    // printf("%d\n", result);
    // for (int i = 0; i < TS.n; ++i) {
    //     printf("%d->", TS.sq[i]);
    // }
    // printf("\n");
}