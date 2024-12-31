#include "main.h"

// 身份选择
int IdentityChoose() {
    int identity = 0;
    while (identity != 1 && identity != 2) {    
        printf("请选择身份: \n");
        printf("1. 游客 \n");
        printf("2. 管理员 \n");
        scanf("%d", &identity);
        ClearBuffer();
        if (identity != 1 && identity != 2) {
            printf("输入有误，请重新输入: \n");
        }
        else {
           return identity;
        }
    }
}

// 游客菜单
int TouristMenu() {
    int choice = -1;
    while (!(choice <= 6 && choice >= 0)) {
        printf("现在是游客操作页面，请选择操作: \n");
        printf("1. 查看全部景点及其介绍 \n");
        printf("2. 查看全部景点及景点间的路径 \n");
        printf("3. 查找景点 \n");
        printf("4. 查找两个景点之间的最短路径 \n");
        printf("5. 规划一条经过多个景点的路径 \n");
        printf("6. 查找两个景点之间的所有路径 \n");
        printf("0. 退出 \n");
        
        scanf("%d", &choice);
        ClearBuffer();
        if (!(choice <= 6 && choice >= 0)) {
            printf("输入有误，请重新输入: \n");
        }
        else {
           return choice;
        }
    }
}

// 打印所有景点及其邻接路径
void PrintAllDestinationAndPath(UDN G) {
    VexNode* nodes = G.vexs;
    printf("|(ID).(景点名)|:\t邻接景点1 (ID).(名称)((该路径长度))\t\t……\n");
    for (int i = 0; i < G.n; ++i) {
        printf("--------------------------------------------------------------------------------------------------\n");
        printf("|%d.%s|:\t", nodes[i].id, nodes[i].name);
        for (AdjVexNode* p = nodes[i].firstArc; p; p = p->next) {
            printf("%d.%s(%d) ", G.vexs[p->adjvex].id, G.vexs[p->adjvex].name, p->weight);
        }
        printf("\n");
    }
    printf("--------------------------------------------------------------------------------------------------\n");
}

// 管理员菜单
int ManagerMenu() {
    int choice = -1;
    while (!(choice <= 13 && choice >= 0)) {
        printf("现在是管理员操作页面，请选择操作: \n");
        printf("1. 查看全部景点及其介绍 \n");
        printf("2. 查看全部景点及景点间的路径 \n");
        printf("3. 查找景点 \n");
        printf("4. 查找两个景点之间的最短路径 \n");
        printf("5. 规划一条经过多个景点的路径 \n");
        printf("6. 查找两个景点之间的所有路径 \n");
        printf("7. 随机生成景点之间的路径，并覆盖原有的路径信息 \n");
        printf("8. 增加景点 \n");
        printf("9. 删除景点 \n");
        printf("10. 修改景点信息 \n");
        printf("11. 增加景点之间的路径 \n");
        printf("12. 删除景点之间的路径 \n");
        printf("13. 修改景点之间的路径长度 \n");
        printf("0. 退出 \n");
        scanf("%d", &choice);
        ClearBuffer();
        if (!(choice <= 13 && choice >= 0)) {
            printf("输入有误，请重新输入: \n");
        }
        else {
           return choice;
        }
    }
}

// 初始化图，生成默认信息
// 随机生成路径
void InitTouristGuideSystem(UDN& G) {
    VexType vexs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    char* name1 = (char*)malloc(sizeof("日月贝"));
    memcpy(name1, "日月贝", sizeof("日月贝"));
    char* name2 = (char*)malloc(sizeof("爱情邮局"));
    memcpy(name2, "爱情邮局", sizeof("爱情邮局"));
    char* name3 = (char*)malloc(sizeof("情侣北路"));
    memcpy(name3, "情侣北路", sizeof("情侣北路"));
    char* name4 = (char*)malloc(sizeof("半岛驿站公园"));
    memcpy(name4, "半岛驿站公园", sizeof("半岛驿站公园"));
    char* name5 = (char*)malloc(sizeof("珠海中山公园"));
    memcpy(name5, "珠海中山公园", sizeof("珠海中山公园"));
    char* name6 = (char*)malloc(sizeof("港珠澳大桥码头"));
    memcpy(name6, "港珠澳大桥码头", sizeof("港珠澳大桥码头"));
    char* name7 = (char*)malloc(sizeof("望夫石"));
    memcpy(name7, "望夫石", sizeof("望夫石"));
    char* name8 = (char*)malloc(sizeof("高山庙"));
    memcpy(name8, "高山庙", sizeof("高山庙"));
    char* name9 = (char*)malloc(sizeof("唐家湾"));
    memcpy(name9, "唐家湾", sizeof("唐家湾"));
    char* name10 = (char*)malloc(sizeof("城市阳台"));
    memcpy(name10, "城市阳台", sizeof("城市阳台"));
    char* name11 = (char*)malloc(sizeof("香炉洞"));
    memcpy(name11, "香炉洞", sizeof("香炉洞"));
    char* name12 = (char*)malloc(sizeof("珠海渔女"));
    memcpy(name12, "珠海渔女", sizeof("珠海渔女"));
    
    char* names[] = { name1, name2, name3, name4, name5, name6, name7, name8, name9, name10, name11, name12 };
    ArcInfo arcs[25] = {};
    for (int i = 0; i < 25; ++i) {
        int v_id = rand() % 12 + 1;
        int w_id = v_id;
        while (w_id == v_id) {
            w_id = rand() % 12 + 1;
        }
        int weight = rand() % 15 + 1;
        arcs[i] = {v_id, w_id, weight};
    }
    char info[12][150] = {
        "珠海大剧院，位于野狸岛", //1
        "充满浪漫气息的特殊邮局", //2
        "美丽的海滨风光和丰富的旅游资源", //3
        "以自行车驿站为主题的户外休闲乐园", //4
        "充满历史气息和现代活力相结合的公园", //5
        "大湾区三地互通、客货兼重的陆路口岸之一", //6
        "融入动人传说故事的自然景观", //7
        "金台寺，珠海地区最古老的寺院", //8
        "珠海市溯源地，保留众多名人故居", //9
        "山海相拥、陆岛相望的公共服务中心节点", //10
        "以形态各异的钟乳石而闻名", //11
        "巨型石刻雕像，雕塑家潘鹤的杰作" //12
    };
    CreateUDN(G, vexs, names, 12, arcs, 25);
    for (int i = 0; i < 12; ++i) {
        if (NULL == G.vexs[i].vexInfo) {
            G.vexs[i].vexInfo = (char*)malloc(sizeof(char) * 150);
        }
        memset(G.vexs[i].vexInfo, '\0', 150);
        memcpy(G.vexs[i].vexInfo, info[i], 150);    
    }
    for (int i = 0; i < 12; ++i) {
        free(names[i]);
        names[i] = NULL;
    }
}

// 查找景点
void SearchDestination(UDN G) {
    int loc = -1;
    printf("现在是查找景点页面，请输入景点ID查找: \n");
    int id = -1;
    scanf("%d", &id);
    ClearBuffer();
    loc = LocateVex(G, id);
    if (loc > -1) {
        printf("查找成功：\n");
        printf("----------------------------------------\n");
        printf("(ID)\t(景点名):(景点信息)\n");
        PrintSingleVex(G, loc);
        printf("----------------------------------------\n");
    } else {
        printf("抱歉，找不到该景点 \n");
    }
}

// 查找最短路径
void SearchShortestPath(UDN G) {
    int bg, ed, bg_loc, ed_loc;
    printf("现在是查找最短路径的界面\n");
    do {
        printf("请输入起点ID: \n");
        scanf("%d", &bg);
        ClearBuffer();
        bg_loc = LocateVex(G, bg);
        printf("请输入终点ID: \n");
        scanf("%d", &ed);
        ClearBuffer();
        ed_loc = LocateVex(G, ed);
        if (!(bg_loc >= 0 && bg_loc < G.n && ed_loc >= 0 && ed_loc < G.n)) {
            printf("输入有误，请检查输入ID是否正确后重试：\n");
            OutputVexs(G);
        }
    } while (!(bg_loc >= 0 && bg_loc < G.n && ed_loc >= 0 && ed_loc < G.n));
    DistInfo* Dist = (DistInfo*)malloc(sizeof(DistInfo) * G.n);
    Dijkstra(G, bg_loc, Dist);
    if (Dist[ed_loc].lowcost == INT_MAX) {
        printf("抱歉，暂无目标路径\n");
    } else {
        printf("查找成功，路径如下：\n");
        OutputPath(G, Dist, ed_loc);
        printf("\n");
        printf("该路径的长度为：%d \n", Dist[ed_loc].lowcost);
        printf("\n");
    }
}

// 打印LQueue队列形式的路径
void PrintQueueFormPath(UDN G, LQueue Q) {
    QueuePtr p = Q.front;
    if (Q.front == Q.rear) {
        printf("抱歉，暂无目标路径 \n");
        return;
    }
	if (p->next) {
		printf("%d.%s", G.vexs[p->data].id, G.vexs[p->data].name);
	}
	p = p->next;
	while (p->next) {
		printf("->%d.%s", G.vexs[p->data].id, G.vexs[p->data].name);
		p = p->next;
	}
    printf("\n");
}

// 规划一条经过多个景点的路径
void PlanPath(UDN G) {
    printf("现在是规划路径的界面 \n");
    printf("请输入若干个景点的ID，其中第1个为起点，最后一个为终点 \n");
    int* ids = (int*)malloc(sizeof(int) * G.n);
    memset(ids, 0, sizeof(int) * G.n);
    int count = 0;
    int id = 0;
    do {
        printf("请输入需要经过的第%d个景点的ID： \n", count + 1);
        printf("(如输入完毕，请输入0并回车) \n");
        scanf("%d", &id);
        if (id == 0) {
            printf("输入完毕，开始规划 \n");
            break;
        }
        int loc = LocateVex(G, id);
        if (loc == -1) {
            printf("抱歉，找不到该ID，本次输入无效 \n");
            continue;
        }
        ids[count++] = id;
    } while (1);
    if (count < 2) {
        printf("抱歉，输入数量过少，无法规划路径，将自动退出 \n");
        return;
    }
    int* locs = (int*)malloc(sizeof(int) * count);
    for (int i = 0; i < count; ++i) {
        locs[i] = LocateVex(G, ids[i]);
    }
    LQueue Q;
    InitQueue_LQ(Q);
    if (PathPlanning(G, locs, count, Q)) {
        printf("规划成功，以下是目标路径：\n");
        PrintQueueFormPath(G, Q);
    }
    else {
        printf("抱歉，暂无目标路径\n");
    }
}

// 打印CSTree树形式的多条路径
void PrintTreeFormPaths(UDN G, CSTree tree, LQueue& Q) {
    if (NULL == tree) {
        printf("抱歉，暂无目标路径 \n");
        return;
    }
    // 当前顶点入队
    EnQueue_LQ(Q, tree->data);
    if (NULL == tree->firstChild) {
        PrintQueueFormPath(G, Q);
        return;
    }
    // 遍历孩子
    LQueue T;
    // 第一个孩子
    // 复制当前路径到T
    if (tree->firstChild) {
        CopyQueue_LQ(T, Q);
        PrintTreeFormPaths(G, tree->firstChild, T);
        // 第二、第三……个孩子
        for (CSTree p = tree->firstChild->nextSibling; p; p = p->nextSibling) {
        // 复制当前路径到T，并记录当前长度
            CopyQueue_LQ(T, Q);
            PrintTreeFormPaths(G, p, T);
        }
    }
    DestroyQueue_LQ(T);
}

// 搜索两点间的所有路径
void SearchAllPaths(UDN G) {
    printf("现在是搜索两个景点之间的所有路径的界面 \n");
    int bg, ed, bg_loc, ed_loc;
    do {
        printf("请输入起点ID: \n");
        scanf("%d", &bg);
        ClearBuffer();
        bg_loc = LocateVex(G, bg);
        printf("请输入终点ID: \n");
        scanf("%d", &ed);
        ClearBuffer();
        ed_loc = LocateVex(G, ed);
        if (!(bg_loc >= 0 && bg_loc < G.n && ed_loc >= 0 && ed_loc < G.n)) {
            printf("输入有误，请检查输入ID是否正确后重试：\n");
            OutputVexs(G);
        }
    } while (!(bg_loc >= 0 && bg_loc < G.n && ed_loc >= 0 && ed_loc < G.n));
    CSTree tree = SearchPathBFS(G, bg_loc, ed_loc);
    LQueue Q;
    InitQueue_LQ(Q);
    PrintTreeFormPaths(G, tree, Q);
}

// 随机生成路径
void GenerateRandomPaths(UDN& G) {
    printf("现在是随机生成路径界面 \n");
    int choice = -1;
    while (!(choice == 1 || choice == 0)) {
        printf("若确认需要随机生成景点之间的路径，并覆盖原有的路径信息 \n");
        printf("请输入1，否则输入0 \n");
        scanf("%d", &choice);
        ClearBuffer();
        if (!(choice == 1 || choice == 0)) {
            printf("输入有误，请重新输入");
        }
    }
    if (choice == 0) {
        printf("即将退出随机生成路径界面 \n");
        return;
    } else {
        printf("正在随机生成路径... \n");
        // 清除原有路径
        for (int i = 0; i < G.n; ++i) {
            ClearAdj(G, i);
        }
        // 随机生成新路径
        for (int i = 0; i < 20; ++i) {
            int v_loc = rand() % G.n;
            int w_loc = v_loc;
            while (w_loc == v_loc) {
                w_loc = rand() % G.n + 1;
            }
            int v_id = G.vexs[v_loc].id;
            int w_id = G.vexs[w_loc].id;
            int weight = rand() % 12 + 1;
            SetArc(G, v_id, w_id, weight);
        }
    }
}

// 添加景点
void AddDestination(UDN& G) {
    printf("现在是添加景点界面 \n");
    printf("请输入景点名称，少于50个字符: \n");
    char name[50] = {};
    scanf("%[^\n]", &name);
    ClearBuffer();
    printf("请输入景点介绍，少于150个字符: \n");
    char info[50] = {};
    scanf("%[^\n]", &info);
    ClearBuffer();
    printf("输入完成，即将添加的景点 \n");
    int choice = -1;
    while(!(choice == 1 || choice == 0)) {
        printf("景点名称为: %s\n", name);
        printf("景点介绍为: %s\n", info);
        printf("若确认无误，请输入1，否则输入0 \n");
        scanf("%d", &choice);
        ClearBuffer();
        if (!(choice == 1 || choice == 0)) {
            printf("输入有误，请重新选择 \n");
        }
    }
    if (choice == 0) {
        printf("输入已被丢弃，即将退出添加景点界面 \n");
        return;
    }
    printf("正在添加景点... \n");
    AddVex(G, name, info);
    printf("添加完成，即将退出添加景点界面 \n");
}

// 删除景点
void DeleteDestination(UDN& G) {
    printf("现在是删除景点界面 \n");
    printf("请输入景点ID: \n");
    int id = -1, loc = -1;
    scanf("%d", &id);
    ClearBuffer();
    loc = LocateVex(G, id);
    if (loc == -1) {
        printf("抱歉，该ID无效，将自动退出删除景点界面... \n");
        return;
    }
    printf("即将删除的景点是: \n");
    PrintSingleVex(G, loc);
    int choice = 0;
    printf("确认删除请输入1，否则放弃删除 \n");
    scanf("%d", &choice);
    ClearBuffer();
    if (choice == 1) {
        printf("正在删除... \n");
        DeleteVex(G, id);
        printf("删除成功 \n");
    } else {
        printf("放弃删除，正在退出... \n");
    }
}

// 修改景点介绍
void ModifyDestinationInfo(UDN& G) {
    printf("现在是修改景点介绍界面 \n");
    printf("请输入景点ID: \n");
    int id = -1, loc = -1;
    scanf("%d", &id);
    ClearBuffer();
    loc = LocateVex(G, id);
    if (loc == -1) {
        printf("抱歉，该ID无效，将自动退出修改景点介绍界面... \n");
        return;
    }
    char name[50] = {};
    printf("请输入新的景点名，少于50字符：");
    scanf("%[^\n]", &name);
    ClearBuffer();
    char info[150] = {};
    printf("请输入新的景点介绍，少于150字符： \n");
    scanf("%[^\n]", &info);
    ClearBuffer();
    printf("即将修改的景点是: \n");
    PrintSingleVex(G, loc);
    
    printf("新的景点名称是: \n");
    printf("%s\n", name);
    printf("新的景点介绍是: \n");
    printf("%s\n", info);

    int choice = 0;
    printf("确认修改请输入1，否则放弃修改 \n");
    scanf("%d", &choice);
    ClearBuffer();
    if (choice == 1) {
        printf("正在修改... \n");
        ModifyVex(G, id, name, info);
        printf("修改成功 \n");
    } else {
        printf("放弃修改，正在退出... \n");
    }
}

// 添加路径
void AddPathById(UDN& G) {
    printf("现在是添加景点间路径界面 \n");
    printf("请输入第一个景点ID: \n");
    int v_id = -1;
    scanf("%d", &v_id);
    ClearBuffer();
    printf("请输入第二个景点ID: \n");
    int w_id = -1;
    scanf("%d", &w_id);
    ClearBuffer();
    int weight = -1;
    while (weight <= 0) {
        printf("请输入路径长度: \n");
        scanf("%d", &weight);
        ClearBuffer();
        if (weight <= 0) {
            printf("抱歉，请重新输入大于0的路径长度 \n");
        }
    }
    if (ERROR == SetArc(G, v_id, w_id, weight)) {
        printf("抱歉，ID无效，将自动退出添加景点间路径界面... \n");
    } else {
        printf("添加成功 \n");
    }
}

// 删除路径
void DeletePathById(UDN& G){
    printf("现在是删除景点间路径界面 \n");
    printf("请输入第一个景点ID: \n");
    int v_id = -1;
    scanf("%d", &v_id);
    ClearBuffer();
    printf("请输入第二个景点ID: \n");
    int w_id = -1;
    scanf("%d", &w_id);
    ClearBuffer();
    printf("请输入路径长度: \n");
    int weight = -1;
    scanf("%d", &weight);
    ClearBuffer();

    int v_loc = LocateVex(G, v_id);
    int w_loc = LocateVex(G, w_id);
    if (v_loc == -1 || w_loc == -1) {
        printf("存在无效ID，即将自动退出删除路径界面... \n");
        return;
    }

    printf("即将删除[%d.%s]和[%d.%s]间的长度为[%d]的路径，请确认 \n", v_id, G.vexs[v_loc].name, w_id, G.vexs[w_loc].name, weight);
    printf("若确认无误，请输入1，否则放弃删除操作 \n");
    int choice = -1;
    scanf("%d", &choice);
    ClearBuffer();
    if (choice == 1) {
        printf("正在删除... \n");
        if (DeleteArc(G, { v_id, w_id, weight })) {
            printf("删除成功 \n");
        } else {
            printf("抱歉，不存在该路径... \n");
        }
    } else {
        printf("放弃删除，即将退出删除路径界面 \n");
    }
}

// 修改路径长度
void ModifyPathWeight(UDN& G) {
    printf("现在是修改景点间路径长度界面 \n");
    printf("请输入第一个景点ID: \n");
    int v_id = -1;
    scanf("%d", &v_id);
    ClearBuffer();
    printf("请输入第二个景点ID: \n");
    int w_id = -1;
    scanf("%d", &w_id);
    ClearBuffer();
    printf("请输入原路径长度: \n");
    int weight = -1;
    scanf("%d", &weight);
    ClearBuffer();
    printf("请输入新的路径长度: \n");
    int newWeight = -1;
    scanf("%d", &newWeight);
    ClearBuffer();

    int v_loc = LocateVex(G, v_id);
    int w_loc = LocateVex(G, w_id);
    if (v_loc == -1 || w_loc == -1) {
        printf("存在无效ID，即将自动退出删除路径界面... \n");
        return;
    }

    printf("即将修改[%d.%s]和[%d.%s]间的路径，原长度为[%d]，新长度为[%d]，请确认 \n", v_id, G.vexs[v_loc].name, w_id, G.vexs[w_loc].name, weight, newWeight);
    printf("若确认无误，请输入1，否则放弃修改操作 \n");
    int choice = -1;
    scanf("%d", &choice);
    ClearBuffer();
    if (choice == 1) {
        printf("正在修改... \n");
        if (ModifyArc(G, { v_id, w_id, weight }, newWeight)) {
            printf("修改成功 \n");
        } else {
            printf("抱歉，不存在该路径... \n");
        }
    } else {
        printf("放弃删除，即将退出删除路径界面 \n");
    }
}

void PrintDesigner() {
	printf("姓名：王坤平\n");
	printf("学号：3123004758\n");
	printf("专业：计算机科学与技术\n");
	printf("班级：23级3班\n\n");
}

int main() {
    UDN G;
    // 初始化
    InitTouristGuideSystem(G);
    // 打印全部景点和路径
    PrintAllDestinationAndPath(G);
    PrintDesigner();
    while (1) {
        // 选择身份
        int identity = IdentityChoose();
        // 游客身份
        while (identity == 1) {
            // 游客操作选择
            int choice = TouristMenu();
            if (choice == 1) {
                // 查看全部景点
                OutputVexs(G);
            } else if (choice == 2) {
                // 查看全部景点及其邻接路径
                PrintAllDestinationAndPath(G);
            } else if (choice == 3) {
                // 搜索景点
                SearchDestination(G);
            } else if (choice == 4) {
                // 查找最短路径
                SearchShortestPath(G);
            } else if (choice == 5) {
                // 规划路径
                PlanPath(G);
            } else if (choice == 6) {
                // 查找两点间的所有路径
                SearchAllPaths(G);
            } else if (choice == 0) {
                break;
            }
        }
        // 管理员身份
        while (identity == 2) {
            // 管理员操作选择
            int choice = ManagerMenu();
            if (choice == 1) {
                // 查看全部景点
                OutputVexs(G);
            } else if (choice == 2) {
                // 查看全部景点及其邻接路径
                PrintAllDestinationAndPath(G);
            } else if (choice == 3) {
                // 搜索景点
                SearchDestination(G);
            } else if (choice == 4) {
                // 查找最短路径
                SearchShortestPath(G);
            } else if (choice == 5) {
                // 规划路径
                PlanPath(G);
            } else if (choice == 6) {
                // 查找两点间的全部路径
                SearchAllPaths(G);
            } else if (choice == 7) {
                // 随机生成景点之间的路径，并覆盖原有的路径信息
                GenerateRandomPaths(G);
            } else if (choice == 8) {
                // 添加景点
                AddDestination(G);
            } else if (choice == 9) {
                // 删除景点
                DeleteDestination(G);
            } else if (choice == 10) {
                // 修改景点信息
                ModifyDestinationInfo(G);
            } else if (choice == 11) {
                // 增加景点之间的路径
                AddPathById(G);
            } else if (choice == 12) {
                // 删除景点之间的路径
                DeletePathById(G);
            } else if (choice == 13) {
                // 修改景点之间的路径长度
                ModifyPathWeight(G);
            } else if (choice == 0) {
                break;
            }
        }
    }
    return 0;
}
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

    // int n = 5, e = 7;
    // VexType* vexs = (VexType*)malloc(sizeof(char) * 5);
    // UDN G;
    // for (int i = 0;i < 5; ++i) {
    //     vexs[i] = i + 1;
    // }
    // ArcInfo arcs[] = { {2,3,3}, {2,5,8}, {2,1,16}, {4,3,2}, {4,1,10}, {5,1,2}, {3,5,7} };
    // CreateUDN(G, vexs, NULL, n, arcs, e);
    
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

    // VexNode* nodes = G.vexs;
    // for (int i = 0; i < G.n; ++i) {
    //     printf("%d:", nodes[i].id - 1);
    //     for (AdjVexNode* p = nodes[i].firstArc; p; p = p->next) {
    //         printf("%d(%d) ", p->adjvex, p->weight);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    // DeleteVex(G, 2);

    // nodes = G.vexs;
    // for (int i = 0; i < G.n; ++i) {
    //     printf("%d:", nodes[i].id - 1);
    //     for (AdjVexNode* p = nodes[i].firstArc; p; p = p->next) {
    //         printf("%d(%d) ", p->adjvex, p->weight);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

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

    // int locs[] = {0, 1, 3};
    // LQueue Q;
    // PathPlanning(G, locs, 3, Q);
        // QueuePtr p = Q.front;
        // while (p->next) {
        //     printf("%d->",p->data);
        //     p = p->next;
        // }
    // PrintQueue_LQ(Q);
// }

// // 打印LQueue队列形式的路径
// void PrintQueuePath(UDN G, LQueue Q) {
//     if (Q.front == Q.rear) {
//         return;
//     }
//     QueuePtr p = Q.front;
//     printf("%d.%s", G.vexs[p->data].id, G.vexs[p->data].name);
//     p = p->next;
//     while (p->next) {
//         printf("------>%d.%s", G.vexs[p->data].id, G.vexs[p->data].name);
//         p = p->next;
//     }
//     printf("\n");
// }
