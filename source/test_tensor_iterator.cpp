//
// Copyright 2014 Robert Gantner
//
// Compile with e.g.
//   clang++ -std=c++11 -I ../include/ test_tensor_iterator.cpp
//

#include <iostream>
#include "tensor_container.hpp"

#include <set>

int main(int argc, const char *argv[])
{
    std::cout << "---------------------" << std::endl;
    std::cout << " for std::vector" << std::endl;
    std::cout << "---------------------" << std::endl;

    int dim = 2;
    typedef int value_type;
    std::vector<value_type> vec = {1,2,3};

    //tensor_container<std::vector<value_type>::iterator> cont(vec.begin(), vec.end(), dim);
    auto cont = make_tensor_container(vec.begin(), vec.end(), dim);

    for (auto tmp : cont) {
        std::copy(tmp.begin(), tmp.end(), std::ostream_iterator<value_type>(std::cout, ", "));
        std::cout << std::endl;
    }

    std::vector<double> vec2;
    for (auto v : vec)
        vec2.push_back(v);

    // std::set
    std::cout << "---------------------" << std::endl;
    std::cout << " now for std::set" << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << " adding element 7" << std::endl;
    std::cout << "---------------------" << std::endl;

    std::set<double> myset(vec2.begin(), vec2.end());
    myset.insert(7);
    auto cont2 = make_tensor_container(myset.begin(), myset.end(), dim);

    for (auto tmp : cont2) {
        std::copy(tmp.begin(), tmp.end(), std::ostream_iterator<value_type>(std::cout, ", "));
        std::cout << std::endl;
    }

    return 0;
}
