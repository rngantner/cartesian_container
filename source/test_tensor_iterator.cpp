#include <iostream>
#include "tensor_container.hpp"


int main(int argc, const char *argv[])
{
    int dim = 4;
    typedef int value_type;
    std::vector<value_type> vec = {1,2,3,4};

    tensor_container<std::vector<value_type>> cont(vec, dim);

    for (auto tmp : cont) {
        std::copy(tmp.begin(), tmp.end(), std::ostream_iterator<value_type>(std::cout, ", "));
        std::cout << std::endl;
    }

    return 0;
}
