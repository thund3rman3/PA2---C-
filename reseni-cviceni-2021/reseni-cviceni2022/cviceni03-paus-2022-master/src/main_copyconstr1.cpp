#include <iostream>
#include <cassert>
#include <memory>

/*
    Reseni pomoci unique_ptr a swap.
*/

#define LEVEL1
#define LEVEL2
#define LEVEL3
#define LEVEL4

template< typename T>
class Stack
{
    //using T = int;

public:
    Stack() {}
    // Stack() = default;
    Stack(const Stack& other)
    {
        for (size_t i = 0; i < other.m_size; ++i)
            push_back(other.m_data[i]);
    }
    Stack& operator=(Stack other)
    {
        using std::swap;
        swap(m_cap, other.m_cap);
        swap(m_size, other.m_size);
        swap(m_data, other.m_data); 
        
        return *this;
    }

    ~Stack()
    {

    }

    void push_back(const T& t)
    {
        if (m_size >= m_cap) grow(2*m_cap + 4);
        m_data[m_size++] = t;
    }

    T& at(size_t i)
    {
        assert( i < m_size );
        return m_data[i];
    }

    const T& at(size_t i) const
    {
        // assert( i < m_size );
        // return m_data[i];

        return (const_cast<Stack&>(*this)).at(i);
        //return (const_cast<Stack*>(this))->at(i);
    }

    T pop_back()
    {
        assert(m_size > 0);
        return m_data[--m_size];
    }

    friend std::ostream& operator<<(std::ostream& os, const Stack<T>& s)
    {
        os << s.m_size << "/" << s.m_cap << ": { ";
        for (size_t i = 0; i < s.m_size; ++i)
        {
            os << s.m_data[i] << " ";
        }
        os << "}";
        return os;
    }

private:
    void grow(size_t new_cap)
    {
        //T* new_data = new T[new_cap];
        std::unique_ptr<T[]> new_data(new T[new_cap]);

        for (size_t i = 0; i < m_size; ++i)
            new_data[i] = m_data[i];
        
        m_cap = new_cap;
        m_data = std::move(new_data);
    }

    //T* m_data = nullptr;
    std::unique_ptr<T[]> m_data;
    size_t m_cap = 0, m_size = 0;
};


int main()
{
#ifdef LEVEL1 
    Stack<int> s;
    s.push_back(1);
    s.push_back(2);
    s.push_back(3);

    assert(s.at(0)==1);
    assert(s.at(2)==3);
#ifdef LEVEL2
    std::cout << s << std::endl;

#ifdef LEVEL3
    s.at(1) = 5;
    assert(s.at(1) == 5);

    std::cout << s << std::endl;

    s.pop_back();
    std::cout << s << std::endl;

    s.push_back(10);
    s.push_back(11);
    s.push_back(12);

    std::cout << s << std::endl;

#ifdef LEVEL4

    const Stack<int>& s1 = s;

    Stack<int> s3(s);
    Stack<int> s4 = s;

    Stack<int> s2;
    s2.push_back(11111);
    s2 = s; 

    s = s;

    s.push_back(111);
    s2.push_back(222);
    s2.push_back(333);
    s3.push_back(444);

    std::cout << "s : " << s << std::endl;
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s3: " << s3 << std::endl;
    std::cout << "s4: " << s4 << std::endl;
    



#endif // level 4
#endif // level 3
#endif // level 2
#endif // level 1

}