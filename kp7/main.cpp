#include <iomanip>
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using std::vector;

char Map(int index){
    return index + 'a';
}

template <size_t VertexCount>
struct ContiguityGraph{
    bool ContiguityMatrix[VertexCount][VertexCount] = {};

    void AddOrientedConnection(size_t src, size_t dst){
        ContiguityMatrix[src][dst] = 1;
    }

    void AddConnection(size_t f, size_t s){
        AddOrientedConnection(f, s);
        AddOrientedConnection(s, f);
    }

    void Print(){
        puts("Contiguity Matrix");
        puts("     a   b   c   d   e   f   g");
        puts("    ___________________________");

        for(int i = 0; i < VertexCount; i++){
            std::cout << Map(i) << " |";
            for(int j = 0; j < VertexCount; j++){
                std::cout << std::setw(3) << ContiguityMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

template <size_t VertexCount>
struct IncidenceGraph{
    vector<char> IncidenceMatrix[VertexCount] = {};

    void AddConnection(size_t f, size_t s){
        AddOrientedConnection(f, s);
        AddOrientedConnection(s, f);
    }
    void AddOrientedConnection(size_t src, size_t dst){

        for(int i = 0; i<VertexCount; i++){
            if(i == src)
                IncidenceMatrix[i].push_back(1);
            else if (i == dst)
                IncidenceMatrix[i].push_back(-1);
            else
                IncidenceMatrix[i].push_back(0);
        }
    }

    void Print(){
        puts("\nIncidence Matrix");
        for(int i = 0; i<VertexCount; i++){
            std::cout << Map(i) << " |";
            for(auto e: IncidenceMatrix[i]){
                std::cout << std::setw(3) << (int)e << " ";
            }
            std::cout << std::endl;
        }

    }
};

template<size_t VerticesCount>
struct EdgeListGraph{
    struct Edge{
        size_t src;
        size_t dst;
    };
    vector<Edge> EdgeList;

    void AddConnection(size_t f, size_t s){
        AddOrientedConnection(f, s);
        AddOrientedConnection(s, f);
    }

    void AddOrientedConnection(size_t src, size_t dst){
        EdgeList.push_back({src, dst});
    }

    void Print(){
        puts("\nEdge List");
        for(auto e: EdgeList){
            std::cout << "From: " << Map(e.src) << " To: " << Map(e.dst) << std::endl;
        }
    }
};

template<size_t VerticesCount>
struct ContiguityListGraph{
    vector<size_t> ContiguityList[VerticesCount];

    ContiguityListGraph() = default;

    ContiguityListGraph(const ContiguityListGraph &other) = default;

    void AddConnection(size_t f, size_t s){
        AddOrientedConnection(f, s);
        AddOrientedConnection(s, f);
    }

    void AddOrientedConnection(size_t src, size_t dst){
        ContiguityList[src].push_back(dst);
    }

    void Print(){
        puts("\nContiguity List");
        for(int i = 0; i<VerticesCount; i++){
            std::cout << Map(i) << " |";
            for(auto e: ContiguityList[i]){
                std::cout << std::setw(3) << Map(e) << " ";
            }
            std::cout << std::endl;
        }
    }

    void BFS(size_t begin)const{
        bool visited[VerticesCount] = {0};
        visited[begin] = true;
        std::cout << "BFS";
        std::queue<size_t> q;
        q.push(begin);

        while(!q.empty()){

            size_t e = q.front();
            q.pop();


            std::cout << " --> " << Map(e);

            for(auto edge: ContiguityList[e]){
                if(visited[edge] == false){
                    visited[edge] = true;
                    q.push(edge);
                }
            }

        }

        std::cout << std::endl;

        for(int i = 0; i<VerticesCount; i++){
            if(!visited[i])
                std::cout << Map(begin) << " can't visit " << Map(i) << std::endl;
        }
    }


    void DFS(size_t begin)const{
        bool visited[VerticesCount] = {0};
        std::cout << "DFS";
        DFSImpl(begin, visited);
        std::cout << std::endl;

        for(int i = 0; i<VerticesCount; i++){
            if(!visited[i])
                std::cout << Map(begin) << " can't visit " << Map(i) << std::endl;
        }
    }

    void DFSImpl(size_t index, bool visited[VerticesCount])const{
        visited[index] = true;

        std::cout << " --> " <<Map(index);

        for(auto e: ContiguityList[index]){
            if(!visited[e])
                DFSImpl(e, visited);
        }
    }
};

template<typename Graph, size_t V>
Graph To(ContiguityGraph<V> adjacency){
    Graph res;
    for(int i = 0; i<V; i++){
        for(int j = 0; j<V; j++)
            if(adjacency.ContiguityMatrix[i][j])
                res.AddOrientedConnection(i, j);
    }
    return res;
}

template<typename Graph, size_t V>
Graph To(IncidenceGraph<V> incidence){
    Graph res;
    int edges = incidence.IncidenceMatrix[0].size();
    for(int j = 0; j<edges; j++){
        int src = -1;
        int dst = -1;
        for(int i = 0; i<V; i++){
            if(incidence.IncidenceMatrix[i][j] == 1)
                src = i;
            else if(incidence.IncidenceMatrix[i][j] == -1)
                dst = i;
        }
        if(dst == -1)
            dst = src;
        res.AddOrientedConnection(src, dst);
    }
    return res;
}

template<typename Graph>
void Add(Graph &gr, char src, char dst){
    gr.AddConnection(src - 'a', dst - 'a');
}

template<typename Graph>
void AddToOriented(Graph &gr, char src, char dst){
    gr.AddOrientedConnection(src - 'a', dst - 'a');
}

void BFS(const ContiguityListGraph<7> &graph, char ch){
    graph.BFS(ch - 'a');
}

void DFS(const ContiguityListGraph<7> &graph, char ch){
    graph.DFS(ch - 'a');
}


int main(){
    {
        std::cout << "NonOriented Graph\n\n";
        ContiguityGraph<7> graph;
        Add(graph, 'a', 'b');
        Add(graph, 'a', 'c');
        Add(graph, 'b', 'd');
        Add(graph, 'c', 'f');
        Add(graph, 'c', 'g');
        Add(graph, 'd', 'f');
        Add(graph, 'd', 'g');
        Add(graph, 'e', 'f');
        Add(graph, 'f', 'g');

        To<ContiguityGraph<7>>(graph).Print();
        To<IncidenceGraph<7>>(graph).Print();
        To<EdgeListGraph<7>>(graph).Print();
        To<ContiguityListGraph<7>>(graph).Print();

        for(char ch = 'a'; ch <= 'g'; ch++){
            std::cout <<"\nStart from : "<< ch << std::endl;
            BFS(To<ContiguityListGraph<7>>(graph), ch);
            DFS(To<ContiguityListGraph<7>>(graph), ch);
            std::cout << std::endl;
        }
    }

    {
        std::cout << "Oriented Graph\n\n";
        IncidenceGraph<7> graph;
        AddToOriented(graph, 'a', 'b');
        AddToOriented(graph, 'a', 'c');
        AddToOriented(graph, 'b', 'd');
        AddToOriented(graph, 'c', 'a');
        AddToOriented(graph, 'c', 'f');
        AddToOriented(graph, 'c', 'g');
        AddToOriented(graph, 'd', 'b');
        AddToOriented(graph, 'd', 'g');
        AddToOriented(graph, 'f', 'd');
        AddToOriented(graph, 'f', 'e');
        AddToOriented(graph, 'g', 'f');

        To<ContiguityGraph<7>>(graph).Print();
        To<IncidenceGraph<7>>(graph).Print();
        To<EdgeListGraph<7>>(graph).Print();
        To<ContiguityListGraph<7>>(graph).Print();

        for(char ch = 'a'; ch <= 'g'; ch++){
            std::cout <<"\nStart from : "<< ch << std::endl;
            BFS(To<ContiguityListGraph<7>>(graph), ch);
            DFS(To<ContiguityListGraph<7>>(graph), ch);
            std::cout << std::endl;
        }
    }


}
