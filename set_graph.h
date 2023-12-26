// ListGraph
#pragma once

#include <vector>
#include "hashtable.h"

struct SetGraph : public IGraph {
public:
    // Создаем вектор векторов, заполненный нулями
    explicit SetGraph(const uint32_t &size) : table(size) {}

    // Конструктор копирования
    SetGraph(const IGraph &graph) : table(graph.VerticesCount()) {
        for (int from = 0; from < graph.VerticesCount(); from++) {
            for (const auto &to: graph.GetNextVertices(from)) {
                table[from].Add(to);
            }
        }
    }

    // Все построено на векторе, поэтому память чистить у SetGraph не нужно
    ~SetGraph() override = default;

    void AddEdge(const int64_t &from, const int64_t &to) override {
        assert(0 <= from && from < table.size());
        assert(0 <= to && to < table.size());
        table[from].Add(to);
    }

    [[nodiscard]] uint32_t VerticesCount() const override {
        return table.size();
    }

    [[nodiscard]] std::vector<uint32_t> GetNextVertices(const int64_t &vertex) const override {
        assert(0 <= vertex && vertex < table.size());
        return table[vertex].Data();
    }

    [[nodiscard]] std::vector<uint32_t> GetPrevVertices(const int64_t &vertex) const override {
        assert(0 <= vertex && vertex < table.size());
        std::vector<uint32_t> prevVertices;

        for (int from = 0; from < table.size(); from++) {
            for (const auto &to: table[from].Data()) {
                if (to == vertex) {
                    prevVertices.push_back(from);
                    break;
                }
            }
        }
        return prevVertices;
    }

private:
    // Вектор хэш-таблиц, где каждая хэш-таблица хранит вектор входящих вершин
    std::vector<HashTable<uint32_t>> table;
};


