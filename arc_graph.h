#pragma once

#include <vector>

class ArcGraph : public IGraph {
public:
    explicit ArcGraph(const uint32_t &size) : sizeGraph(size) {}

    // Конструктор копирования
    ArcGraph(const IGraph &graph) : sizeGraph(graph.VerticesCount()) {
        for (int from = 0; from < graph.VerticesCount(); ++from) {
            for (const auto &to: graph.GetNextVertices(from)) {
                edges.push_back({from, to});
            }
        }
    }

    // Все построено на векторе, поэтому память чистить у ArcGraph не нужно
    ~ArcGraph() override = default;

    void AddEdge(const int64_t &from, const int64_t &to) override {
        assert(0 <= from && from < sizeGraph);
        assert(0 <= to && to < sizeGraph);
        edges.push_back({from, to});
    }

    [[nodiscard]] uint32_t VerticesCount() const override {
        return static_cast<uint32_t>(sizeGraph);
    }

    [[nodiscard]] std::vector<uint32_t> GetNextVertices(const int64_t &vertex) const override {
        assert(0 <= vertex && vertex < sizeGraph);
        std::vector<uint32_t> nextVertices;
        for (const auto &edge: edges) {
            if (edge.first == vertex) nextVertices.push_back(edge.second);
        }
        return nextVertices;
    }

    [[nodiscard]] std::vector<uint32_t> GetPrevVertices(const int64_t &vertex) const override {
        assert(0 <= vertex && vertex < sizeGraph);
        std::vector<uint32_t> prevVertices;
        for (const auto &edge: edges) {
            if (edge.second == vertex) prevVertices.push_back(edge.first);
        }
        return prevVertices;
    }

private:
    std::vector<std::pair<uint32_t, uint32_t>> edges;
    uint32_t sizeGraph;
};