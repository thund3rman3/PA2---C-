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
    BinTree& add(const std::string& s, unsigned c = 1);
    BinTree& remove(const std::string& s);
    std::string toString() const;
    BinTree& clear();
    unsigned size();
    
    std::string toString2D();       //zobrazi strukturu stromu v konzoli
    
    unsigned operator[](const std::string& s) const;
    void operator+=(const std::string& s);            // pro string
    void operator-=(const std::string& s);            // pro string
    void operator+=(const BinTree& t2);            // slouceni se stromem
    
//cviceni 05
    BinTree( const BinTree& other );               // kopirovaci konstruktor
    BinTree& operator=( const BinTree& other );         // operator prirazeni
    BinTree operator+( const BinTree& t2 ) const;         // soucet svou stromu
    
    friend std::ostream& operator<<(std::ostream& os, const BinTree& t2);        // vypis do streamu
//    ... operator>>(...);        // vstup ze streamu

private:
    struct Leaf                 // struktura pro jeden list
    {
        Leaf(std::string s):m_left(nullptr), m_right(nullptr), m_id(s), m_count(0) {};           // konstruktor listu
        Leaf* m_left;
        Leaf* m_right;
        std::string m_id;
        unsigned m_count;
    };
    
//    ...                         // soukrome atributy stromu
    Leaf* m_root;
    unsigned m_size;

//    ...                         // pomocne funkce
    Leaf* find(const std::string& s, Leaf*& prev) const;
    void clearR(Leaf* leaf);
    void addR( BinTree::Leaf* leaf );
    void toStringR(Leaf *leaf, std::string &result) const;

        void toString2DR(Leaf *leaf, int space, std::string &result) const; // pomocna fce pro zobrazeni v konzoli
};

std::istream& operator>>(std::istream& is, BinTree& t2);

#endif // BINTREE_H
