#include "bintree.h"

// konstruktor bez parametru
BinTree::BinTree():m_root(nullptr), m_size(0)
{

}

// destruktor
BinTree::~BinTree()
{
    clearRecursive(m_root);
}

BinTree& BinTree::add(const std::string &s, unsigned c)
{
    Node* prev = nullptr;
    Node* tmp = find(s, prev);

    if (!tmp)       // if (tmp == nullptr)
    {
        tmp = new Node(s);
        m_size++;

        if (!m_root) m_root = tmp;
        else
        {
            if (s<prev->m_id) prev->m_left = tmp;
            else prev->m_right = tmp;
        }
    }
    
    tmp->m_count += c;

    return *this;
}

BinTree::Node* BinTree::find(const std::string &s, Node *&prev) const
{
    Node* tmp = m_root;
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

unsigned BinTree::size() const
{
    return m_size;
}

BinTree& BinTree::remove(const std::string &s)
{
    Node* prev = nullptr;
    Node* tmp = find(s, prev);

    if (!tmp) return *this;

    if (tmp->m_count > 1) tmp->m_count--;
    else
    {
        // mazani prvku se dvema nasledniky
        if (tmp->m_left && tmp->m_right)
        {
            Node* x = tmp->m_right;
            prev = tmp;
            while (x->m_left)
            {
                prev = x;
                x = x->m_left;
            }
            tmp->m_id = x->m_id;
            tmp->m_count = x->m_count;

            tmp = x;
        }

        // mazani listu (zadny naslednik)
        if (tmp->m_left == nullptr && tmp->m_right == nullptr)
        {
            if (tmp == m_root) m_root = nullptr;
            else
            {
                if (tmp == prev->m_left) prev->m_left = nullptr;
                else prev->m_right = nullptr;
            }
            delete tmp;
            m_size--;
        }
        else // mazani ve vetvi
        {
            if (tmp->m_right == nullptr)
            {
                if (tmp == m_root) m_root = tmp->m_left;
                else
                {
                    if (tmp == prev->m_left) prev->m_left = tmp->m_left;
                    else prev->m_right = tmp->m_left;
                }
            }
            else 
            {
                if (tmp->m_left == nullptr)
                {
                    if (tmp == m_root) m_root = tmp->m_right;
                    else
                    {
                        if (tmp==prev->m_left) prev->m_left = tmp->m_right;
                        else prev->m_right = tmp->m_right;
                    }
                }
            }
            delete tmp;
            m_size--;
        }
    }

    return *this;
}

void BinTree::clear()
{
    clearRecursive(m_root);
    m_root = nullptr;
    m_size = 0;
}

void BinTree::clearRecursive(Node *node)
{
    if (node)
    {
        clearRecursive(node->m_left);
        clearRecursive(node->m_right);
        delete node;
    }
}

unsigned BinTree::operator[](const std::string &s) const
{
    Node* prev = nullptr;
    Node* tmp = find(s, prev);

    if (tmp) return tmp->m_count;

    return 0;
}

BinTree &BinTree::operator+=(const std::string &s)
{
    return add(s);
}

BinTree &BinTree::operator-=(const std::string &s)
{
    return remove(s);
}

void BinTree::operator+=(const BinTree &t2)
{
     addRecursive(t2.m_root);  
}

void BinTree::addRecursive( Node* node )
{
    if (node)
    {
        add(node->m_id, node->m_count);
        addRecursive(node->m_left);
        addRecursive(node->m_right);
    }
}

BinTree::BinTree(const BinTree& other):m_root(nullptr),m_size(0)
{
    addRecursive(other.m_root);
}

BinTree& BinTree::operator=(const BinTree &other)
{
    if ( this == &other) return *this; 

    clear();
    addRecursive(other.m_root);

    return *this;
}

BinTree BinTree::operator+(const BinTree &other) const
{
    BinTree tree(*this);
    tree += other;

    return tree;
}

std::string BinTree::toString() const
{
    std::string result;

    toStringRecursive(m_root, result);

    return result;
}

void BinTree::toStringRecursive(Node *node, std::string &result) const
{
    if (node)
    {
        toStringRecursive(node->m_left, result);
        result += node->m_id + ":" + std::to_string(node->m_count) + " ";
        toStringRecursive(node->m_right, result);
    }
}

std::istream &operator>>(std::istream &is, BinTree &other)
{
    std::string str;

    while ( is >> str ) other.add(str);

    return is;
}

std::ostream &operator<<(std::ostream &os, const BinTree &other)
{
    return os << other.toString();
}

// vypis struktury stromu do konzole
// pomocna fce pro vyzualizaci stromu
// muzete pouzit jako inspiraci pro dalsi metody
void BinTree::toString2DR ( BinTree::Node* node, int space, std::string& result ) const
{
    if (!node) return;
    
    space += 5;
    
    toString2DR(node->m_right,space, result);
    
    for (int i=0; i<space; i++) result += " ";
    result += node->m_id + ":" + std::to_string(node->m_count) + "\n";
    
    toString2DR(node->m_left, space, result);
}

std::string BinTree::toString2D() const
{
    std::string result;
    toString2DR(m_root,0, result);
    result += "-----------------------------------------------\n";
    return result;
}
