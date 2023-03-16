#include <iostream>
#include <cassert>

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
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    ~Stack()
    {
        delete[] m_data;
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
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < m_size; ++i)
            new_data[i] = m_data[i];
        
        m_cap = new_cap;

        delete[] m_data;
        m_data = new_data;
    }

    T* m_data = nullptr;
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

    assert(s1.at(1)==5);
    //s1.at(0) = 2;  // nelze na const

    Stack<int> s2;
    //s2 = s; //nelze, pokud zrusime operator prirazeni

    Stack<std::string> s3;

    s3.push_back("Ahoj");
    s3.push_back("Cau");

    std::cout << s3 << std::endl;

    Stack<Stack<int>> s5;
    //s5.push_back(s);
    
#endif // level 4
#endif // level 3
#endif // level 2
#endif // level 1

}