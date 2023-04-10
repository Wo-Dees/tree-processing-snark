#include "DataGraph.hpp"

void DataGraph::Init() {
    for (size_t i = 0; i < 100; ++i) {
        documents_.emplace_back(std::make_shared<Document>("aaa"));
    }
}