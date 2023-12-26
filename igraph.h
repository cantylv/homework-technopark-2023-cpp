#include <vector>

// Абстрактный класс
struct IGraph {
    virtual ~IGraph() = default;

    // Добавляет ребра от узла from к to.
    virtual void AddEdge(const int64_t& from, const int64_t& to) = 0;

    // Возвращает кол-во узлов графа
    [[nodiscard]] virtual uint32_t VerticesCount() const = 0;

    // Возвращает вектор узлов, на которые указывает узел vertex
    [[nodiscard]] virtual std::vector<uint32_t> GetNextVertices(const int64_t& vertex) const = 0;

    // Возвращает вектор узлов, которые указывают на узел vertex
    [[nodiscard]] virtual std::vector<uint32_t> GetPrevVertices(const int64_t& vertex) const = 0;
};