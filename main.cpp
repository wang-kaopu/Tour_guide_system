#include "main.h"

int main() {
    // UDN G;
    // VexType vexs[5] = {1, 2, 3, 4, 5};
    // VexNode* vexNodes = (VexNode*)malloc(sizeof(VexNode) * 5);
    // for (int i = 0; i < 5; ++i) {
    //     char* tmp = (char*)malloc(sizeof(char) * 2);
    //     vexNodes[i] = {vexs[i], concatenateStrings("name_", itoa(i, tmp, 10)), NULL, NULL};
    // }
    // ArcInfo arcs[5] = {{vexNodes[0], vexNodes[1], 1},
    //     {vexNodes[1], vexNodes[2], 2}, 
    //     {vexNodes[0], vexNodes[2], 3}, 
    //     {vexNodes[2], vexNodes[3], 4}, 
    //     {vexNodes[2], vexNodes[5], 5}};
    // CreateUDG(G, vexs, 5, arcs, 5);
    // int arr[5] = {1, 2, 3, 4, 5};
    
    // int* arr = (int*)malloc(sizeof(int) * 5);
    // for (int i = 1; i <= 5; ++i) {
    //     arr[i - 1] = i;
    // }
    // arr = (int*)deleteFromArray(arr, 5, 3, sizeof(int));
    // for (int i = 0; i < 4; ++i) {
    //     printf("%d ", arr[i]);
    // }

    int n = 5, e = 7;
    VexType* vexs = (VexType*)malloc(sizeof(char) * 5);
    UDN G;
    for (int i = 0;i < 5; ++i) {
        vexs[i] = i + 1;
    }
    ArcInfo arcs[] = { {2,3,3}, {2,5,8}, {2,1,16}, {4,3,2}, {4,1,10}, {5,1,2}, {3,5,7} };
    CreateUDN(G, vexs, NULL, n, arcs, e);
    
    // InitUDN(G, vexs, n);
    // SetArc(G, 2, 3, 3);
    // SetArc(G, 2, 5, 8);
    // SetArc(G, 2, 1, 16);
    // SetArc(G, 4, 3, 2);
    // SetArc(G, 4, 1, 10);
    // SetArc(G, 5, 1, 2);
    // SetArc(G, 3, 5, 7);
    
    // char* name = (char*)"夏日";
    // char* vexInfo = (char*)"天鹅";
    // AddVex(G, name, vexInfo);

    VexNode* nodes = G.vexs;
    for (int i = 0; i < G.n; ++i) {
        printf("%d:", nodes[i].id - 1);
        for (AdjVexNode* p = nodes[i].firstArc; p; p = p->next) {
            printf("%d(%d) ", p->adjvex, p->weight);
        }
        printf("\n");
    }
    printf("\n");

    // CSTree ret = SearchPathBFS(G, 1, 1);
    // PrintCSTree(ret);
    // printf("\n");

    // TopSq TS;
    // InitTopSq(TS, G.n);
    // int result = ToplogicalSort(G, TS);
    // printf("%d\n", result);
    // for (int i = 0; i < TS.n; ++i) {
    //     printf("%d->", TS.sq[i]);
    // }
    // printf("\n");

    // DistInfo* Dist = (DistInfo*)malloc(sizeof(DistInfo) * G.n);
    // Dijkstra(G, 1, Dist);
    // for (int i = 0;i < G.n; ++i) {
    //     printf("lowcost: %d; prev: %d\n", Dist[i].lowcost, Dist[i].prev);    
    // }
    // OutputPath(G, Dist, 3);
    // printf("\n");
    
    // OutputVexs(G);
    // OutputAllArcs(G);
    
    // DFS(G);

    // UDN_to_DN(G);

    // nodes = G.vexs;
    // for (int i = 0; i < G.n; ++i) {
    //     printf("%d:", nodes[i].id - 1);
    //     for (AdjVexNode* p = nodes[i].firstArc; p; p = p->next) {
    //         printf("%d(%d) ", p->adjvex, p->weight);
    //     }
    //     printf("\n");
    // }

    // ToplogicalSort(G);

    int locs[] = {0, 1, 4};
    PathPlanning(G, locs, 3);
    return 0;
}