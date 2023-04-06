#ifndef __PROGTEST__
#include <cstring>
using namespace std;

class CLinkedSetTester;
#endif /* __PROGTEST__ */

class CLinkedSet
{
private:
    struct CNode
    {
        CNode(const char* val, CNode* NEXT = nullptr):m_val(val),m_Next(NEXT){}
        CNode *m_Next;
        const char *Value() const
        {
            return m_val;
        }

    private:
        const char *m_val;
    };

    CNode *m_Begin;

public:
    // default constructor
    CLinkedSet();
    // copy constructor
    CLinkedSet(const CLinkedSet &ls);
    // operator=
    CLinkedSet &operator=(const CLinkedSet &ls);
    // destructor
    ~CLinkedSet();

    bool Insert(const char *value);

    bool Remove(const char *value);

    bool Empty() const;

    size_t Size() const;

    bool Contains(const char *value) const;

    friend class ::CLinkedSetTester;
};

// default constructor
CLinkedSet::CLinkedSet()
{
    m_Begin = nullptr;
}
// copy constructor
CLinkedSet::CLinkedSet(const CLinkedSet &ls)
{
    CNode *lsb;
    m_Begin = lsb = ls.m_Begin;
    for (; lsb != nullptr; lsb = lsb->m_Next)
    {
    }
}
// operator=
CLinkedSet &CLinkedSet::operator=(const CLinkedSet &ls)
{
}
// destructor
CLinkedSet::~CLinkedSet()
{
}

bool CLinkedSet::Insert(const char *value)
{
    char* str;
    strcpy(str,value);
    if(m_Begin == nullptr)
    {
        m_Begin = &CNode(str);
        return true;
    }   
    for (CNode *x = m_Begin; x != nullptr; x = x->m_Next)
    {
        if(strcmp(m_Begin->Value(), str) == 0)
            return false;
                
        else if(strcmp(m_Begin->Value(), str) < 0)
            continue;
        else if(strcmp(m_Begin->Value(), str) > 0)
        {
                
        }
    }
}

bool CLinkedSet::Remove(const char *value)
{
}

bool CLinkedSet::Empty() const
{
}

size_t CLinkedSet::Size() const
{
}

bool CLinkedSet::Contains(const char *value) const
{
}

#ifndef __PROGTEST__
#include <cassert>

struct CLinkedSetTester
{
    static void test0()
    {
        CLinkedSet x0;
        assert(x0.Insert("Jerabek Michal"));
        assert(x0.Insert("Pavlik Ales"));
        assert(x0.Insert("Dusek Zikmund"));
        assert(x0.Size() == 3);
        assert(x0.Contains("Dusek Zikmund"));
        assert(!x0.Contains("Pavlik Jan"));
        assert(x0.Remove("Jerabek Michal"));
        assert(!x0.Remove("Pavlik Jan"));
        assert(!x0.Empty());
    }

    static void test1()
    {
        CLinkedSet x0;
        assert(x0.Insert("Jerabek Michal"));
        assert(x0.Insert("Pavlik Ales"));
        assert(x0.Insert("Dusek Zikmund"));
        assert(x0.Size() == 3);
        assert(x0.Contains("Dusek Zikmund"));
        assert(!x0.Contains("Pavlik Jan"));
        assert(x0.Remove("Jerabek Michal"));
        assert(!x0.Remove("Pavlik Jan"));
        CLinkedSet x1(x0);
        assert(x0.Insert("Vodickova Saskie"));
        assert(x1.Insert("Kadlecova Kvetslava"));
        assert(x0.Size() == 3);
        assert(x1.Size() == 3);
        assert(x0.Contains("Vodickova Saskie"));
        assert(!x1.Contains("Vodickova Saskie"));
        assert(!x0.Contains("Kadlecova Kvetslava"));
        assert(x1.Contains("Kadlecova Kvetslava"));
    }

    static void test2()
    {
        CLinkedSet x0;
        CLinkedSet x1;
        assert(x0.Insert("Jerabek Michal"));
        assert(x0.Insert("Pavlik Ales"));
        assert(x0.Insert("Dusek Zikmund"));
        assert(x0.Size() == 3);
        assert(x0.Contains("Dusek Zikmund"));
        assert(!x0.Contains("Pavlik Jan"));
        assert(x0.Remove("Jerabek Michal"));
        assert(!x0.Remove("Pavlik Jan"));
        x1 = x0;
        assert(x0.Insert("Vodickova Saskie"));
        assert(x1.Insert("Kadlecova Kvetslava"));
        assert(x0.Size() == 3);
        assert(x1.Size() == 3);
        assert(x0.Contains("Vodickova Saskie"));
        assert(!x1.Contains("Vodickova Saskie"));
        assert(!x0.Contains("Kadlecova Kvetslava"));
        assert(x1.Contains("Kadlecova Kvetslava"));
    }
};

int main()
{
    CLinkedSetTester::test0();
    CLinkedSetTester::test1();
    CLinkedSetTester::test2();
    return 0;
}
#endif /* __PROGTEST__ */
