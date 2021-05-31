#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>
#include <stack>
using namespace std;

using std::vector;

struct Graph{
    size_t index;
    size_t weight;
};

constexpr int Infinity = 99999;

template<size_t VerticesCount>
struct AdjacencyListGraph{
    vector<Graph> AdjacencyList[VerticesCount];

    AdjacencyListGraph() = default;

    AdjacencyListGraph(const AdjacencyListGraph &other) = default;

    void AddElement(char src, char dst, size_t weight){
        AdjacencyList[src - 'a'].push_back({size_t(dst - 'a'), weight});
    }

    void Print(){
        puts("Adjacency List: ");
        for(int i = 0; i<VerticesCount; i++){
            std::cout << char(i + 'a') << " |";
            for(auto e: AdjacencyList[i]){
                std::cout << std::setw(2) << char(e.index + 'a') <<"[" <<e.weight<< "] ";
            }
            std::cout << std::endl;
        }
    }

    void DeikstraAlgorithm(char startVertex){
        int Weight[VerticesCount];
        for(int i = 0; i<VerticesCount; i++)
            Weight[i] = Infinity;

        int begin = startVertex - 'a';

        std::queue<int> q;
        std::vector<char> u;
        q.push(begin);
        u.push_back(startVertex);
        Weight[begin] = 0;

        while(!q.empty()){
            int v = q.front();
            q.pop();
            for(Graph e: AdjacencyList[v]){
                if(Weight[v] + e.weight < Weight[e.index]){
                    Weight[e.index] = Weight[v] + e.weight;
                    q.push(e.index);
                    u.push_back(e.index + 'a');
                }
            }
        }



        for(int i = 0; i<VerticesCount; i++){
            std::cout << "Start " << startVertex << " End " << char(i + 'a') << " Weight " << (Weight[i] == Infinity ? std::string("inf") : std::to_string(Weight[i])) << std::endl;

            std::stack<char> s;
            int cv = i;
            int w = Weight[cv];
            while (cv != startVertex - 'a'){
                for(int j = 0; j<VerticesCount; j++){
                    for(int k = 0; k<AdjacencyList[j].size(); k++){
                        if(AdjacencyList[j][k].index == cv && Weight[j] + AdjacencyList[j][k].weight == w){
                            s.push(cv + 'a');
                            cv = j;
                            w = Weight[cv];
                        }
                    }
                }
            }
            std::cout << startVertex;
            while(s.size()){
                std::cout << "-->" << s.top();
                s.pop();
            }
            std::cout << std::endl;
        }
    }

    void PrintMatrix(int matrix[VerticesCount][VerticesCount]){
        for(int i = 0; i<VerticesCount; i++){
            for(int j = 0; j<VerticesCount; j++)
                std::cout << std::setw(5) << (matrix[i][j] == Infinity ? std::string("inf"):  std::to_string(matrix[i][j]));
            std::cout << std::endl;
        }
    }

    void FloidAlgorithm(char startVertex) {
        int a[VerticesCount][VerticesCount] = {};
        for (int i = 0; i < VerticesCount; i++) {
            for (auto e: AdjacencyList[i]) {
                a[i][e.index] = e.weight;
            }
        }
        cout << "StartMatrix \n\n";

        PrintMatrix(a);

        int n = VerticesCount;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (a[i][j] == 0)
                {
                    a[i][j] = Infinity;
                }
            }
        }

        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
                }
            }
        }

        cout << "Result \n\n";
        PrintMatrix(a);
    }

};


int main(){
    AdjacencyListGraph<6> graph;

    graph.AddElement('a', 'b', 5);
    graph.AddElement('a', 'c', 3);
    graph.AddElement('b', 'd', 6);
    graph.AddElement('c', 'e', 2);
    graph.AddElement('c', 'f', 5);
    graph.AddElement('d', 'e', 7);
    graph.AddElement('d', 'f', 2);
    graph.AddElement('e', 'f', 1);

    graph.Print();

    graph.DeikstraAlgorithm('a');

    graph.FloidAlgorithm('a');
}
