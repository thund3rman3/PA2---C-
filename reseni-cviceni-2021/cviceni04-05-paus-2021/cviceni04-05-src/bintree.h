#ifndef BINTREE_H
#define BINTREE_H

#include <string>
#include <iostream>

class BinTree
{
public:
    BinTree();
    ~BinTree();
    
// cviceni 04
    BinTree& add( const std::string& s, unsigned c = 1 );
    BinTree& remove( const std::string&s );
    std::string toString() const;
    void clear();
    unsigned size() const;
    
    std::string toString2D() const;       //zobrazi strukturu stromu v konzoli
    
    unsigned operator[](const std::string& s) const;
    BinTree &operator+=(const std::string &s);        // pro string
    BinTree &operator-=(const std::string &s);        // pro string
    void operator+=(const BinTree& t2);            // slouceni se stromem

    //cviceni 05
    BinTree( const BinTree& other );               // kopirovaci konstruktor
    BinTree& operator=(const BinTree& other);         // operator prirazeni
    BinTree operator+(const BinTree& other) const;         // soucet svou stromu

private:
    struct Node                 // struktura pro jeden list
    {
        Node(const std::string &s) 
        : m_id(s), 
          m_right(nullptr),
          m_left(nullptr),
          m_count(0){}; // konstruktor listu
        std::string m_id;
        Node* m_right;
        Node* m_left;
        unsigned m_count;
    };
    
//    ...                         // soukrome atributy stromu
    Node* m_root;
    unsigned m_size;

//    ...                         // pomocne funkce
    Node* find(const std::string& s, Node*& prev) const;
    void toString2DR(Node* node, int space, std::string& result) const; // pomocna fce pro zobrazeni v konzoli
    void clearRecursive(Node* node);
    void addRecursive(Node *node);
    void toStringRecursive(Node *node, std::string &result) const;
};

std::istream& operator>>(std::istream& is, BinTree& other ); // vstup ze streamu
std::ostream& operator<<(std::ostream& os, const BinTree& other );        // vypis do streamu

#endif // BINTREE_H
