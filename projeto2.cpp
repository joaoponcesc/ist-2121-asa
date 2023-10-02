#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <set>

using namespace std;

struct node { 
    vector<int> adjNodes;
    int can_reach_v1 = 0;
    int can_reach_v2 = 0;
    int visited = 0;
    int nmr_parents = 0;
    int flag_can_add = 0;     
};

int V, E, v1, v2, size_poss_solutions = 0;
set<int> poss_solutions;

void readInfoGraph(){
    if(scanf("%d %d", &v1, &v2) != 2){printf("0\n");exit(0);}
    if(scanf("%d %d", &V, &E) != 2){printf("0\n");exit(0);}
}

void processGraph(node nodes_vector[]){
    int input1 = 0, input2 = 0;
    for(int i = 0; i < E; i++){
        if(scanf("%d %d", &input1, &input2) != 2){printf("0\n");exit(0);}
        nodes_vector[input1 - 1].adjNodes.push_back(input2 - 1);
        if(nodes_vector[input2 - 1].nmr_parents +1 > 2){
            printf("0\n");
            exit(0);
        }
    }
    nodes_vector[v1 - 1].can_reach_v1 = 1;
    nodes_vector[v2 - 1].can_reach_v2 = 1;
}

void process_Solution(){
    if(size_poss_solutions == 0){
        printf("-\n");
        return;
    }
    for(int i : poss_solutions){
        printf("%d ", i);
    }
    printf("\n");
}

int DFS_search(int index, node nodes_vector[]){
    nodes_vector[index].visited = -1;
    for(int N : nodes_vector[index].adjNodes){
        if(nodes_vector[N].visited == 0)
            DFS_search(N, nodes_vector);
        else if(nodes_vector[N].visited == -1){
            printf("0\n");
            exit(0);
        }
        if(nodes_vector[N].can_reach_v1 == 1)
            nodes_vector[index].can_reach_v1 = 1;
        if(nodes_vector[N].can_reach_v2 == 1)
            nodes_vector[index].can_reach_v2 = 1;
        if(nodes_vector[N].can_reach_v1 == 1 && nodes_vector[N].can_reach_v2 == 1)
            nodes_vector[index].flag_can_add = 1;
    }
    nodes_vector[index].visited = 1;
    if(nodes_vector[index].can_reach_v1 == 1 && nodes_vector[index].can_reach_v2 == 1 && nodes_vector[index].flag_can_add == 0){
        poss_solutions.insert(index + 1);
        size_poss_solutions++;
    }
    return 0;
}

int DFS(node nodes_vector[]){
    for(int i = 0; i < V; i++){
        if(nodes_vector[i].visited == 0)
            DFS_search(i, nodes_vector);
    }
    return 0;
}

int main(){
    readInfoGraph();
    node *nodes_vector = (node*)malloc(sizeof(node) * V);
    processGraph(nodes_vector);
    DFS(nodes_vector);
    process_Solution();
    return 0;
}