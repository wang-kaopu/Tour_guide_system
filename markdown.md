​```mermaid
graph TB
    start(开始) -->|初始化| Init[初始化系统]
    Init -->|打印景点和路径| Print[打印全部景点和路径]
    Print --> ChooseIdentity[选择身份]
    
    subgraph 游客操作
        TouristMenu[游客菜单]
        TouristMenu -->|1| ViewAll[查看全部景点及其介绍]
        TouristMenu -->|2| ViewPaths[查看全部景点及景点间的路径]
        TouristMenu -->|3| SearchDest[查找景点]
        TouristMenu -->|4| ShortestPath[查找两个景点之间的最短路径]
        TouristMenu -->|5| PlanRoute[规划一条经过多个景点的路径]
        TouristMenu -->|6| AllPaths[查找两个景点之间的所有路径]
        TouristMenu -->|0| ExitTourist[退出]
    end
    
    subgraph 管理员操作
        ManagerMenu[管理员菜单]
        ManagerMenu -->|1| ViewAllAdmin[查看全部景点及其介绍]
        ManagerMenu -->|2| ViewPathsAdmin[查看全部景点及景点间的路径]
        ManagerMenu -->|3| SearchDestAdmin[查找景点]
        ManagerMenu -->|4| ShortestPathAdmin[查找两个景点之间的最短路径]
        ManagerMenu -->|5| PlanRouteAdmin[规划一条经过多个景点的路径]
        ManagerMenu -->|6| AllPathsAdmin[查找两个景点之间的所有路径]
        ManagerMenu -->|7| RandomPaths[随机生成景点之间的路径并覆盖原有的路径信息]
        ManagerMenu -->|8| AddDest[增加景点]
        ManagerMenu -->|9| DeleteDest[删除景点]
        ManagerMenu -->|10| ModifyDestInfo[修改景点信息]
        ManagerMenu -->|11| AddPath[增加景点之间的路径]
        ManagerMenu -->|12| DeletePath[删除景点之间的路径]
        ManagerMenu -->|13| ModifyPathWeight[修改景点之间的路径长度]
        ManagerMenu -->|0| ExitManager[退出]
    end
    
    ChooseIdentity -->|游客| TouristMenu
    ChooseIdentity -->|管理员| ManagerMenu
    ExitTourist --> ChooseIdentity
    ExitManager --> ChooseIdentity
    ChooseIdentity -->|退出| End(结束)

​```