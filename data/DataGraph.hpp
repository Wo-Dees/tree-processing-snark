#pragma once

#include <memory>
#include <vector>

#include "Document.hpp"

class DataGraph {
public:
    DataGraph() = default;

    void Init();
// private:
//    size_t head_;
    std::vector<std::shared_ptr<Document>> documents_;
};
