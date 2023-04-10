#include <iostream>

#include "data/DataGraph.hpp"
#include "data/Document.hpp"

#include <folly/futures/Future.h>
#include <folly/executors/ThreadedExecutor.h>

void ExampleMap() {
    folly::ThreadedExecutor executor;

    DataGraph graph;
    graph.Init();

    folly::Promise<DataGraph> p;

    folly::Future<DataGraph> f = p.getSemiFuture().via(&executor);

    auto final_future = std::move(f).thenValue([&executor](DataGraph data) -> DataGraph {
        std::cout << "execute first future" << std::endl;
        for (auto& element : data.documents_) {
            executor.add([element](){
                element.get()->information_.data_ += "bbb"; // TODO OK CODE
            });
        }
        return std::move(data);
    }).thenValue([&executor](DataGraph data) -> DataGraph {
        std::cout << "execute second future" << std::endl;
        for (auto& element : data.documents_) {
            executor.add([element](){
                element.get()->information_.data_ += "ccc"; // TODO OK CODE
            });
        }
        return std::move(data);
    }).thenValue([&executor](DataGraph data) -> DataGraph {
        std::cout << "execute third future" << std::endl;
        for (auto& element : data.documents_) {
            executor.add([element](){
                if (element.get()->information_.data_ != "aaabbbccc") {
                    assert("This is bad code!");
                }
            });
        }
        return std::move(data);
    });

    p.setValue(std::move(graph));

    std::move(final_future).get();
}

void ExampleReduce() {
    // TODO
}

void ExampleCombinators() {
    folly::ThreadedExecutor executor;

    DataGraph graph_1;
    graph_1.Init();

    DataGraph graph_2;
    graph_2.Init();

    folly::Promise<DataGraph> p_1;
    folly::Promise<DataGraph> p_2;

    folly::Future<DataGraph> f_1 = p_1.getSemiFuture().via(&executor);
    folly::Future<DataGraph> f_2 = p_2.getSemiFuture().via(&executor);

    auto final_1 = std::move(f_1).thenValue([&executor](DataGraph data) -> DataGraph {
        std::cout << "execute first one future" << std::endl;
        for (auto& element : data.documents_) {
            executor.add([element](){
                element.get()->information_.data_ += "bbb"; // TODO OK CODE
            });
        }
        return std::move(data);
    });

    auto final_2 = std::move(f_2).thenValue([&executor](DataGraph data) -> DataGraph {
        std::cout << "execute first one future" << std::endl;
        for (auto& element : data.documents_) {
            executor.add([element](){
                element.get()->information_.data_ = "ccc"; // TODO OK CODE
            });
        }
        return std::move(data);
    });

    std::vector<folly::Future<DataGraph>> futs;

    futs.emplace_back(std::move(final_1));
    futs.emplace_back(std::move(final_2));

    auto all = collectAll(futs.begin(), futs.end());

    std::move(all).get();
}

void ExampleCombinatinonMapReduce() {
    // TODO
}

int main() {
    ExampleMap();
//    ExampleReduce(); // TODO DON'T WORK
//    ExampleCombinators(); // TODO DON'T WORK
//    ExampleCombinatinonMapReduce(); // TODO DON'T WORK
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
