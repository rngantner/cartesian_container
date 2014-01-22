#ifndef TENSOR_ITERATOR_H
#define TENSOR_ITERATOR_H
#pragma once

#include <vector>
#include <cmath>
#include <stdexcept>
#include <boost/iterator/iterator_facade.hpp>

typedef unsigned int size_type;

template<class Container>
class tensor_container {
public:
    tensor_container(Container cont, size_type dim) : m_cont(cont), m_dim(dim) {}

    class iterator : public boost::iterator_facade<iterator,
                                                   std::vector<typename Container::value_type>,
                                                   boost::forward_traversal_tag,
                                                   std::vector<typename Container::value_type>>
    {
    public:
        iterator(size_type dim) : dim_(dim), cont_(0), i_(-1) {}
        iterator(Container* cont, size_type dim) : dim_(dim), cont_(cont), i_(0) {}
        iterator(Container* cont, size_type dim, size_type index) : dim_(dim), cont_(cont), i_(index) {}
    private:
        friend class boost::iterator_core_access;
        /** converts linear index to a multiindex */
        std::vector<size_type> index_to_multiindex(size_type index) const {
            auto n = this->cont_->size();
            std::vector<size_type> ret(dim_);
            for (int k=dim_-1; k>=0; k--) {
                int dd = index/std::pow(n,k);
                index -= dd*std::pow(n,k);
                ret[dim_-1-k] = dd;
            }
            return ret;
        }
        void increment() {
            if (i_>=0) i_++;
            // set to one-past-the-end if size is reached.
            if (i_ == std::pow(cont_->size(),dim_))
                i_ = -1;
        }
        bool equal(iterator const& other) const {
            return (other.cont_ == cont_ && other.i_ == i_);
        }
        std::vector<typename Container::value_type> dereference() const {
            if (i_<0) throw std::runtime_error("Iterator is past-the-end; cannot dereference");
            // construct tensorization
            std::vector<typename Container::value_type> ret(dim_);
            auto indices = index_to_multiindex(i_);
            for (int k=0; k<dim_; ++k)
                ret[k] = (*cont_)[indices[k]];
            return ret;
        }

        size_type dim_;
        Container* cont_;
        int i_;
    }; // end class iterator

    // begin and end functions
    iterator begin(){ return iterator(&m_cont, m_dim, 0); }
    iterator end(){ return iterator(&m_cont, m_dim, -1); }

private:
    Container m_cont;
    size_type m_dim;
};






#endif /* end of include guard: TENSOR_ITERATOR_H */
