#include <algorithm>
#include <array>
#include <cstddef>

#define template_T_size template <typename T, size_t N>

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

        ~allocatorHW2();
        allocatorHW2();
        allocatorHW2(const allocatorHW2& other) : m_data(other.m_data), m_flags(other.m_flags) {};
        allocatorHW2(allocatorHW2&&other ){other.swap(*this);}
       
        allocatorHW2& operator = (const allocatorHW2&) ;
        allocatorHW2& operator = (allocatorHW2&&) ;
        
        bool operator == (const allocatorHW2&) const {return false;};
        bool operator != (const allocatorHW2&) const {return true;};
        
        template< typename U, typename... Args >
        void construct( U* p, Args&&... args );
        void destroy(pointer ptr); 
        size_t max_size() const;

        T* allocate(size_type n, const void* = 0); 
        void deallocate(void* ptr, size_type n);

    private:

        std::array<uint8_t, N * sizeof(value_type)> m_data;
        std::array<bool, N> m_flags{{false}};

        void swap(allocatorHW2& other);
};

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
T* allocate(size_t n, const void* = 0){}

template_T_size 
void deallocate(void* ptr, size_t n){}