#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>

#define template_T_size template <typename T, size_t N>

namespace Homework2 {
template <typename T, size_t N = 0>
class allocatorHW2
{
    public:
        using size_type = size_t;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using value_type = T;
        using type = T;

        ~allocatorHW2(){
          delete [] m_data;
          delete [] m_flags;
        };
        allocatorHW2(){
          m_size = N * sizeof(value_type);
          m_data = new uint8_t[m_size];
          m_flags = new bool[m_size];
          std::fill(m_flags, m_flags+m_size, false);
        };
        allocatorHW2(const allocatorHW2& other);
        allocatorHW2(allocatorHW2&&other ){other.swap(*this);}
       
        allocatorHW2& operator = (const allocatorHW2&) ;
        allocatorHW2& operator = (allocatorHW2&&) ;
        
        bool operator == (const allocatorHW2&) const {return false;};
        bool operator != (const allocatorHW2&) const {return true;};
        
        template< typename U, typename... Args >
        void construct( U* p, Args&&... args );
        void destroy(pointer ptr); 
        size_t max_size() const;

        T* allocate(size_type n); 
        void deallocate(T* ptr, size_type n);


      template <class U>
      struct rebind {
        using other = allocatorHW2<U, N>;
      };
    private:
        uint8_t* m_data;
        bool* m_flags;
        size_t m_size;

        void swap(allocatorHW2& other);
};

template_T_size
allocatorHW2<T, N>::allocatorHW2(const allocatorHW2& other)
{
    m_size = other.m_size;
    m_data = new uint8_t[m_size];
    m_flags = new bool[m_size];

    for (size_t i = 0; i < m_size; ++i)
    {
        m_data[i] = other.m_data[i];
        m_flags[i] = other.m_flags[i];
    }
}

template_T_size
 allocatorHW2<T, N>&  allocatorHW2<T, N>::operator=(const allocatorHW2& other) { 
      allocatorHW2<T, N> tmp(other);
      tmp.swap(*this);
      return *this;
 }

template_T_size
 allocatorHW2<T, N>&  allocatorHW2<T, N>::operator = (allocatorHW2&& other) {
      other.swap(*this);
      return *this;
    }

template_T_size
void allocatorHW2<T, N>::swap(allocatorHW2& other){
      std::swap(m_data, other.m_data);
      std::swap(m_flags, other.m_flags);
    }

template_T_size
template<typename U, typename ...Args>
void allocatorHW2<T, N>::construct(U* ptr, Args &&...args) {
      new(ptr) U(std::forward<Args>(args)...);
}

template_T_size 
void allocatorHW2<T, N>::destroy(T* ptr) {
      ptr->~T();
}

template_T_size 
size_t allocatorHW2<T, N>::max_size() const {
    return size_t(-1);
}

template_T_size 
T* allocatorHW2<T, N>::allocate(size_t n){
    
    if (n == 0) return nullptr;
    if (n > static_cast<size_t>(-1) / sizeof(T)) throw std::bad_array_new_length();
    if (n > m_size) 
    {
        int new_m_size = m_size + ( N * sizeof(value_type));
        uint8_t* newm_data = new uint8_t[new_m_size];
        bool* newm_flags = new bool[new_m_size];

        for (size_t i = 0; i< m_size; ++i)
        {
          newm_data[i] = m_data[i];
          newm_flags[i] = m_flags[i];
        }
        m_size = new_m_size;
        
        delete [] m_data;
        delete [] m_flags;

        m_data = newm_data;
        m_flags = newm_flags;
    }

    auto first = m_flags;
    size_t cnt = 0;
    
    for(auto it = m_flags; it != (m_flags+m_size); ++it) {
        if(!it) cnt = 0;
        else
        {
          if(cnt == 0)
            first = it;

          if(++cnt == n) {
            std::fill(first, it+1, true);
            auto pos = static_cast<size_t>(std::distance(m_flags, first));
            auto p =  reinterpret_cast<T *>(&m_data[sizeof(T) * pos]);
            if (!p)
              throw std::bad_alloc(); // not enough memory
            return p;
          }
        }        
    }
    throw std::bad_alloc(); // not enough memory
}

template_T_size 
void allocatorHW2<T, N>::deallocate(T* ptr, size_t n){
  if (!ptr) return;
  int pos = ptr - reinterpret_cast<pointer>(&m_data[0]);
  if(pos >= 0 && pos + static_cast<int>(n) < static_cast<int>(N)) {
        auto first = m_flags + pos;
        auto last  = first + static_cast<int>(n);
        std::fill(first, last, false);
  }
}

}