// ListGraph
#pragma once

#include <vector>

struct ListGraph : public IGraph {
public:
    // Создаем вектор векторов, заполненный нулями
    explicit ListGraph(const uint32_t &size) : adjacencyLists(size) {}

    // Конструктор копирования
    ListGraph(const IGraph &graph) : adjacencyLists(graph.VerticesCount()) {
        for (int from = 0; from < graph.VerticesCount(); from++) {
            for (const auto &to: graph.GetNextVertices(from)) {
                adjacencyLists[from].push_back(to);
            }
        }
    }

    // Все построено на векторе, поэтому память чистить у ListGraph не нужно
    ~ListGraph() override = default;

    void AddEdge(const int64_t &from, const int64_t &to) override {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        // Если нужно будет сделать неориентированный граф, то можно просто добавить доп запись:
        // adjacencyLists[to].push_back(from);
        adjacencyLists[from].push_back(to);
    }

    [[nodiscard]] uint32_t VerticesCount() const override {
        return adjacencyLists.size();
    }

    [[nodiscard]] std::vector<uint32_t> GetNextVertices(const int64_t &vertex) const override {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }

    [[nodiscard]] std::vector<uint32_t> GetPrevVertices(const int64_t &vertex) const override {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<uint32_t> prevVertices;

        for (int from = 0; from < adjacencyLists.size(); from++) {
            for (const auto &to: adjacencyLists[from]) {
                if (to == vertex) {
                    prevVertices.push_back(from);
                    break;
                }
            }
        }
        return prevVertices;
    }

private:
    std::vector<std::vector<uint32_t>> adjacencyLists;
};


