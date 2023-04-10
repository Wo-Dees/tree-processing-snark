#pragma once

#include <deque>

#include "Information.hpp"

class Document {
public:
    Document() = default;

    explicit Document(std::string);

//private:
    Information information_;
    std::deque<std::shared_ptr<Document>> documents_;
};

