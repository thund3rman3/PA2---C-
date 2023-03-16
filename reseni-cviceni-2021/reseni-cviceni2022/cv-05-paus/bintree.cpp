#include "bintree.h"

// konstruktor bez parametru
BinTree::BinTree()
{
    m_root = nullptr;
    m_size = 0;
}

// destruktor
BinTree::~BinTree()
{
    clearR(m_root);
}

BinTree::Leaf* BinTree::find(const std::string& s, Leaf*& prev) const
{
    Leaf* tmp = m_root;
    prev = nullptr;
    
    while (tmp)
    {
        if (s < tmp->m_id)
        {
            prev = tmp;
            tmp = tmp->m_left;
        }
        else
        if (s > tmp->m_id)
        {
            prev = tmp;
            tmp = tmp->m_right;
        }
        else break;
    }
    return tmp;
}

BinTree& BinTree::add(const std::string& s, unsigned c)
{
    Leaf* prev = nullptr;
    Leaf* tmp = find(s, prev);
    
    if (!tmp)
    {
        tmp = new Leaf(s);
        m_size++;
        if (!m_root) m_root = tmp;
        else
        {
            if ( s < prev->m_id ) prev->m_left = tmp;
            else prev->m_right = tmp;
        }
    }
    tmp->m_count += c;
    
    return *this;
}

unsigned BinTree::size()
{
    return m_size;
}

BinTree& BinTree::remove(const std::string& s)
{
    Leaf* prev = nullptr;
    Leaf* tmp = find(s, prev);
    
    if (!tmp) return *this;
    
    if (tmp->m_count > 1) tmp->m_count--;
    else
    {
        // mazani prvku se dvema nasledniky
        if (tmp->m_left && tmp->m_right)
        {
            Leaf* t1 = tmp->m_right;
            prev = tmp;
            while (t1->m_left)
            {
                prev = t1;
                t1 = t1->m_left;
            }
            tmp->m_id = t1->m_id;
            tmp->m_count = t1->m_count;
            
            tmp = t1;
        }
        
        //mazani listu
        if (tmp->m_left==nullptr && tmp->m_right==nullptr)
        {
            if (tmp == m_root) m_root = nullptr;
            else
                if (tmp == prev->m_left) prev->m_left = nullptr;
                else prev->m_right = nullptr;
            delete tmp;
            m_size--;
        }
        else
            // mazani v leve vetvi
        if (tmp->m_right == nullptr)
        {
            if (tmp == m_root) m_root = tmp->m_left;
            else
            {
                if (tmp == prev->m_left) prev->m_left = tmp->m_left; else prev->m_right = tmp->m_left;
            }
            
            delete tmp;
            m_size--;
        }
        else
        if (tmp->m_left == nullptr)
        {
            if (tmp == m_root) m_root = tmp->m_right;
            else
            {
                if (tmp == prev->m_left) prev->m_left = tmp->m_right; else prev->m_right = tmp->m_right;
            }
            
            delete tmp;
            m_size--;
        }
    }
    return *this;
}

BinTree& BinTree::clear()
{
    clearR(m_root);
    m_root = nullptr;
    m_size = 0;
    
    return *this;
}

void BinTree::clearR(Leaf* leaf)
{
    if (leaf)
    {
        clearR(leaf->m_left);
        clearR(leaf->m_right);
        delete leaf;
    }
}

unsigned BinTree::operator[](const std::string& s) const
{
    Leaf* prev = nullptr;
    Leaf* tmp = find(s, prev);
    
    if (tmp) return tmp->m_count;
    
    return 0;
}

void BinTree::operator+=(const std::string& s)
{
    add(s);
}

void BinTree::operator-=(const std::string& s)
{
    remove(s);
}

void BinTree::operator+=(const BinTree& t2)
{
    addR(t2.m_root);
}

void BinTree::addR( BinTree::Leaf* leaf )
{
    if (!leaf) return;
    
    add(leaf->m_id, leaf->m_count);
    addR(leaf->m_left);
    addR(leaf->m_right);
}

// vypis struktury stromu do konzole
// pomocna fce pro vyzualizaci stromu
// muzete pouzit jako inspiraci pro dalsi metody
void BinTree::toString2DR ( BinTree::Leaf* leaf, int space, std::string& result ) const
{
    if (!leaf) return;
    
    space += 5;
    
    toString2DR(leaf->m_right,space, result);
    
    for (int i=0; i<space; i++) result += " ";
    result += leaf->m_id + ":" + std::to_string(leaf->m_count) + "\n";
    
    toString2DR(leaf->m_left, space, result);
}

std::string BinTree::toString2D()
{
    std::string result;
    toString2DR(m_root,0, result);
    result += "-----------------------------------------------\n";
    return result;
}

void BinTree::toStringR(Leaf* leaf, std::string& result) const
{
    if (leaf)
    {
        toStringR(leaf->m_left, result);
        result += leaf->m_id + ":" + std::to_string(leaf->m_count) + " ";
        toStringR(leaf->m_right, result);
    }
}

std::string BinTree::toString() const
{
    std::string result = "";
    toStringR(m_root, result);

    return result;
}

BinTree::BinTree( const BinTree& other)
{
    m_root = nullptr;
    m_size = 0;

    addR(other.m_root);
}

BinTree& BinTree::operator=(const BinTree &other)
{
    clear();
    addR(other.m_root);

    return *this;
}

BinTree BinTree::operator+(const BinTree &t2) const
{
    BinTree t1(*this);

    t1 += t2;

    return t1;
}

std::ostream& operator<<(std::ostream &os, const BinTree &t2)
{
    return os << t2.toString();
}

std::istream &operator>>(std::istream &is, BinTree &t2)
{
    std::string word;

    while (is >> word) t2.add(word);

    return is;
}
