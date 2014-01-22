tensor_container
================

Generic tensorization of any STL-compliant container with itself in arbitrary dimensions with constant memory overhead. Stores only two iterators to the limits of the base container and generates the tensorized points on the fly when an iterator to the container is dereferenced.

Example
-------
The following code shows the features of the tensor_container.
More details can be found in `source/test_tensor_iterator.cpp`.

    // define a container, e.g. a std::vector
    std::vector<int> my_vec = {1,2,3};

    // represent its tensorization in 2 dimensions
    auto tensor_cont = make_tensor_container(my_vec.begin(), my_vec.end(), 2);

    // output all elements (which here are std::vector<int> of size 2)
    for (auto tmp : tensor_cont) {
        std::copy(tmp.begin(), tmp.end(), std::ostream_iterator<int>(std::cout, ", "));
        std::cout << std::endl;
    }

The output of this program is then:

    1, 1, 
    1, 2, 
    1, 3, 
    2, 1, 
    2, 2, 
    2, 3, 
    3, 1, 
    3, 2, 
    3, 3,


TODO
----
  - Support tensorization of different containers per dimension using variadic templates
