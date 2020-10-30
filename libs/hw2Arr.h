#pragma once

#include <memory>
#define template_T_Alloc template <typename T, typename Alloc>

namespace hw2Arr
{
    using size_type = size_t;
}

template <typename T, typename Alloc = std::allocator<T> >
class hw2Array
{
    public:
        using size_type = hw2Arr::size_type;
        using value_type = T;
        //using allocator_type = Alloc;
        using pointer = T*;
        using reference = T&;
        using Treference = reference;
        using r_reference = T&&;
        using const_reference = const T&;


    hw2Array();
    explicit hw2Array(size_type);
    hw2Array(size_type, value_type);
    hw2Array(const std::initializer_list<value_type>&);
    hw2Array(const_reference);
    hw2Array(value_type&&);
    ~hw2Array();
    hw2Array<T, Alloc>& operator = (const_reference);
    hw2Array<T, Alloc>& operator = (r_reference);
    bool operator == (const_reference) const;
    bool operator != (const_reference) const;
    size_type capacity ()const;
    size_type size() const;
    void push_back(const_reference);
    void pop_back();
    void swap (reference);
    reference front() const;
    reference back() const;
    reference operator [] (size_type pos);
    void resize(size_type size);
    void reserve(size_type size);
    void clear();

    struct iterator;
    using hw2ArrayIter = iterator;
    iterator begin() const;
    iterator end() const;

    private:
        void expand(size_type);

        size_type m_size;
        size_type m_nonempty_size;
        std::unique_ptr<Alloc> m_allocator;

        pointer m_data;
};


template_T_Alloc
hw2Array<T, Alloc>::~hw2Array(){
    // TODO : destructor
}

template_T_Alloc
hw2Array<T, Alloc>::hw2Array() : m_size{0},
                                m_nonempty_size{0},
                                m_allocator{std::make_unique<Alloc>()},
                                m_data{nullptr}  {}

template_T_Alloc
hw2Array<T, Alloc>::
hw2Array(size_type size_value) : m_size{size_value},
                                m_nonempty_size{0},
                                m_allocator{std::make_unique<Alloc>()},
                                m_data{m_allocator->allocate(size_value)}{
    for (size_type i=0; i<m_size; m_allocator->construct(&m_data[i++]));
}

template_T_Alloc
hw2Array<T, Alloc>::
hw2Array(size_type size_value, T value) : hw2Array(size_value){
    for (size_type i=0; i<m_size; m_allocator->construct(&m_data[++i], value));
}

template_T_Alloc
hw2Array<T, Alloc>::
hw2Array(const std::initializer_list<value_type>& value): m_size{value.size()},
                                                    m_nonempty_size{value.size()},
                                                    m_allocator{std::make_unique<Alloc>()},
                                                    m_data{m_allocator->allocate(m_size)} {
    for (size_type i=0; i<m_size; ++i)
        m_allocator->construct(&m_data[i], *(value.begin() + i));
}

template_T_Alloc
hw2Array<T, Alloc>::
hw2Array(const T& value):m_size{0},
                        m_nonempty_size{value.m_size},
                        m_allocator{std::make_unique<Alloc>()},
                        m_data{m_allocator->allocate(m_size)}{
    for (size_type i=1; i<m_size; ++i)
        m_allocator->construct(&m_data[i], value[i]);
}

template_T_Alloc
hw2Array<T, Alloc>::hw2Array(T&& value):m_size{0},
                                                    m_nonempty_size{0},
                                                    m_data{nullptr}{
    value.swap(*this);
}

//hw2Array& operator = (const_reference);

template_T_Alloc
hw2Array<T, Alloc>& hw2Array<T, Alloc>::
operator = (const T& cr){
    hw2Array<T, Alloc> temp(cr);
    temp.swap(*this);
    return *this;
}

template_T_Alloc
hw2Array<T, Alloc>&  hw2Array<T, Alloc>::
operator = (T&& rv){
    rv.swap(*this);
    return *this;
}

template_T_Alloc
bool hw2Array<T, Alloc>::
operator == (const T& val) const{
    if (val.m_nonempty_size != m_nonempty_size)
        return false;

    for (int i = 0; i<m_nonempty_size; ++i)
        if (m_data[i] != val.m_data[i])
            return false;

    return true;
}

template_T_Alloc
bool hw2Array<T, Alloc>::
operator != (const T& val) const{
    return !operator == (val);
}

template_T_Alloc
hw2Arr::size_type hw2Array<T, Alloc>::
capacity () const{
    return m_size ;
}

template_T_Alloc
hw2Arr::size_type hw2Array<T, Alloc>::
size() const{
   return m_nonempty_size;
}

template_T_Alloc
void hw2Array<T, Alloc>::
push_back(const T& value){
    (m_size == m_nonempty_size) ? expand(m_size*2) : (void)0;
    m_allocator->construct(&m_data[m_nonempty_size++], value);
}

template_T_Alloc
void hw2Array<T, Alloc>::pop_back(){
    (0 < m_nonempty_size) ? (m_allocator->destroy(m_data[m_nonempty_size--])) : (void)0;}

template_T_Alloc
void hw2Array<T, Alloc>::swap(reference ref1){
    std::swap(m_size,           ref1.m_size);
    std::swap(m_nonempty_size,  ref1.m_nonempty_size);
    std::swap(m_allocator,      ref1.m_allocator);
    std::swap(m_data,           ref1.m_data);
}

template_T_Alloc
T& hw2Array<T, Alloc>::front() const{
    if (m_size > 0)
        return m_data[0];
    else
        throw std::out_of_range("front call for empty hw2Array");
}

template_T_Alloc
T& hw2Array<T, Alloc>::back() const{
    if (m_size > 0)
        return m_data[0];
    else
        throw std::out_of_range("back call for empty hw2Array");
}

template_T_Alloc
T& hw2Array<T, Alloc>::operator [] (size_type pos){
    if (m_size > pos && 0 <= pos)
        return m_data[pos];
    else
       if (m_size >= pos)
            throw std::out_of_range("out_of_range: size of arr is less given number");
        else
            throw std::out_of_range("out_of_range: given number < 0");
}

template_T_Alloc
void hw2Array<T, Alloc>::
resize(size_type size){
    if (m_nonempty_size < size){
        for (size_type i = size; i < m_nonempty_size; m_allocator->destroy(&m_data[i++]));
        m_size = size;
    }
    else{
        (m_size < size) ? expand(size): (void)0;
        for (size_type i = m_size; i < m_nonempty_size; m_allocator->construct(&m_data[i++]));
    }
}

template_T_Alloc
void hw2Array<T, Alloc>::reserve(size_type size)
{
    (size > m_size) ? expand(size) : (void)0;
}

template_T_Alloc
void hw2Array<T, Alloc>::clear(){
   for (size_type i = 0; i < m_nonempty_size; m_allocator->destroy(&m_data[i++]));
   m_size = 0;
}

template_T_Alloc
struct hw2Array<T, Alloc>::iterator : std::iterator<std::bidirectional_iterator_tag, T>{
    explicit iterator(T*);
    iterator& operator ++();
    iterator operator ++(int);
    iterator& operator --();
    iterator operator --(int);
    bool operator == (iterator &val) const;
    bool operator != (iterator &val) const;
    private:
        pointer m_iterator_value;
};

template_T_Alloc
typename hw2Array<T, Alloc>::iterator hw2Array<T, Alloc>::begin() const{
    return m_data[0];
}

template_T_Alloc
typename hw2Array<T, Alloc>::iterator hw2Array<T, Alloc>::end() const{
    return m_data[m_size-1];
}

template_T_Alloc
hw2Array<T, Alloc>::iterator::
iterator(T* iter) : m_iterator_value{iter.m_iterator_value}{}

template_T_Alloc
typename hw2Array<T, Alloc>::iterator&
hw2Array<T, Alloc>::iterator::operator ++(){
    m_iterator_value++;
    return *this;
}

template_T_Alloc
typename hw2Array<T, Alloc>::iterator
hw2Array<T, Alloc>::iterator::operator ++(int){
    iterator temp {this};
    m_iterator_value++;
    return temp;
}

template_T_Alloc
typename hw2Array<T, Alloc>::iterator&
hw2Array<T, Alloc>::iterator::operator --(){
    m_iterator_value--;
    return *this;
}

template_T_Alloc
typename hw2Array<T, Alloc>::iterator
hw2Array<T, Alloc>::iterator::operator --(int){
    iterator temp {this};
    m_iterator_value--;
    return temp;
}


template_T_Alloc
bool hw2Array<T, Alloc>::iterator::operator == (iterator &val) const{
    return m_iterator_value == val.m_iterator_value;
}

template_T_Alloc
bool hw2Array<T, Alloc>::iterator::operator != (iterator &val) const{
    return !operator == (val);
}


