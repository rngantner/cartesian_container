cartesian_container
================

Generic cartesian product of any STL-compliant container with itself in arbitrary dimensions with constant memory overhead. Stores only two iterators to the limits of the base container and generates the elements of the cartesian product on the fly when an iterator to the container is dereferenced.

Example
------
The following code shows the features of the cartesian_container.
More details can be found in `source/test_cartesian_iterator.cpp`.

    // define a container, e.g. a std::vector
    std::vector<int> my_vec = {1,2,3};

    // represent its cartesian product in 2 dimensions
    auto cartesian_cont = make_cartesian_container(my_vec.begin(), my_vec.end(), 2);

    // output all elements (which here are std::vector<int> of size 2)
    for (auto tmp : cartesian_cont) {
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
  - Support cartesian product of different containers per dimension using variadic templates
