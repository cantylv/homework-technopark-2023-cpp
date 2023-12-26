#include "igraph.h"
#include <queue>
#include <vector>

void bfsInternal(const IGraph &graph, const int& vertex,
                 std::vector<bool> &visited, std::function<void(uint32_t)> &func) {
    assert(0 <= vertex && vertex < graph.VerticesCount());
    std::queue<uint32_t> qu;
    qu.push(vertex);
    visited[vertex] = true;

    while (!qu.empty()) {
        uint32_t currentVertex = qu.front();
        qu.pop();

        func(currentVertex);

        for (const auto& nextVertex: graph.GetNextVertices(currentVertex)) {
            if (!visited[nextVertex]) {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

// Возвращает результат поиска в ширину графа. Работает на основе вектора посещенных узлов и очереди, содержащей
// узлы, которые нужно посетить.
void BFS(const IGraph &graph, std::function<void(uint32_t)> func) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i])
            bfsInternal(graph, i, visited, func);
    }
}