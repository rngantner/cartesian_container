//
// Copyright 2014 Robert Gantner
//

#ifndef TENSOR_CONTAINER_H
#define TENSOR_CONTAINER_H
#pragma once

#include <iterator>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <boost/iterator/iterator_facade.hpp>

typedef unsigned int size_type;

/**
 * This class is an STL-compatible implementation of the tensorization of a container
 * in `dim` dimensions. It only stores only the given iterators (no data) and forms the
 * tensor product on-the-fly.
 */
template<class Iterator>
class tensor_container {
public:
    tensor_container(Iterator begin, Iterator end, size_type dim) : m_begin(begin), m_end(end), m_dim(dim) {
        m_n = std::distance(begin, end);
    }

    class iterator : public boost::iterator_facade<iterator,
                                                   std::vector<typename Iterator::value_type>,
                                                   boost::forward_traversal_tag,
                                                   std::vector<typename Iterator::value_type>>
    {
    public:
        iterator(Iterator cont_it, size_type dim, size_type num_elem, size_type index) :
            cont_it_(cont_it), dim_(dim), n_(num_elem), i_(index) {}
    private:
        friend class boost::iterator_core_access;
        /** converts the given linear index to a multiindex */
        std::vector<size_type> index_to_multiindex(size_type index) const {
            std::vector<size_type> ret(dim_);
            for (int k=dim_-1; k>=0; k--) {
                int dd = index/std::pow(n_,k);
                index -= dd*std::pow(n_,k);
                ret[dim_-1-k] = dd;
            }
            return ret;
        }
        void increment() {
            if (i_>=0) i_++;
            // set to one-past-the-end if size is reached.
            if (i_ == std::pow(n_,dim_))
                i_ = -1;
        }
        bool equal(iterator const& other) const {
            return (other.cont_it_ == cont_it_ && other.i_ == i_);
        }
        /** Generates the tensor product. */
        std::vector<typename Iterator::value_type> dereference() const {
            if (i_<0) throw std::runtime_error("Iterator is past-the-end; cannot dereference");
            // construct tensorization.
            // since the returned value is a new object, the reference type must be vector<value_type>
            // (see fourth template argument of iterator_facade above)
            std::vector<typename Iterator::value_type> ret(dim_);
            auto indices = index_to_multiindex(i_);
            for (int k=0; k<dim_; ++k) {
                auto tmp_it = cont_it_;
                std::advance(tmp_it,indices[k]);
                ret[k] = *(tmp_it);
            }
            return ret;
        }

        size_type dim_;
        Iterator cont_it_;
        int i_, n_; // i: index, n: container size
    }; // end class iterator

    // begin and end functions
    iterator begin(){ return iterator(m_begin, m_dim, m_n, 0); }
    iterator end(){ return iterator(m_begin, m_dim, m_n, -1); }

private:
    Iterator m_begin, m_end;
    size_type m_dim, m_n;
};


/** Helper function: allows use of auto to not type template parameters. */
template<class Iterator>
tensor_container<Iterator> make_tensor_container(Iterator begin, Iterator end, size_t dim){
    return tensor_container<Iterator>(begin, end, dim);
}



#endif /* end of include guard: TENSOR_CONTAINER_H */

