#pragma once

#include <string>

class Information {
public:
    Information() = default;

    explicit Information(std::string);

// private:
    std::string data_;
};

