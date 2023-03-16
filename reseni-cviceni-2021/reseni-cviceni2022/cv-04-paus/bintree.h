#ifndef BINTREE_H
#define BINTREE_H

#include <string>

class BinTree
{
public:
    BinTree();
    ~BinTree();
    
// cviceni 04
    BinTree& add(const std::string& s, unsigned c = 1);
    BinTree& remove(const std::string& s);
//    ... toString();
    BinTree& clear();
    unsigned size();
    
    std::string toString2D();       //zobrazi strukturu stromu v konzoli
    
    unsigned operator[](const std::string& s) const;
    void operator+=(const std::string& s);            // pro string
    void operator-=(const std::string& s);            // pro string
    void operator+=(const BinTree& t2);            // slouceni se stromem
    
//cviceni 05
//    BinTree(...);               // kopirovaci konstruktor
//    ... operator=(...);         // operator prirazeni
//    ... operator+(...);         // soucet svou stromu
    
//    ... operator<<(...);        // vypis do streamu
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
    
    void toString2DR(Leaf* leaf, int space, std::string& result) const; // pomocna fce pro zobrazeni v konzoli
};

#endif // BINTREE_H
