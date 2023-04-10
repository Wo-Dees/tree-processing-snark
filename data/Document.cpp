#include "Document.hpp"

Document::Document(std::string information) :
    information_(Information(std::move(information))) {
}
