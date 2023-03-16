#include <iostream>
#include <cassert>
#include <fstream>
#include <ctime>
#include "bintree.h"


#define LEVEL1
#define LEVEL2
#define LEVEL2_5
#define LEVEL3
#define LEVEL4
#define LEVEL5
#define LEVEL6
#define LEVEL7
#define LEVEL8
#define LEVEL9

constexpr unsigned RND_TEST  = 1000;
constexpr unsigned PROGRESS  = RND_TEST / 40;

int main() 
{
// *************************************************************************
// LEVEL 1: Pridavani prvku + pocet listu size();
// *************************************************************************
#ifdef LEVEL1
    std::cout << "Level 1:   " ;
    
    BinTree t1;
    
    t1.add("K");
    t1.add("F");
    t1.add("T");
    t1.add("B");
    t1.add("A");
    t1.add("C");
    t1.add("D");
    t1.add("R");
    t1.add("M");
    t1.add("A");
    
    assert(t1.size()==9);
    
    //std::cout << std::endl << t1.toString2D();
    assert(t1.toString2D() == "          T:1\n               R:1\n                    M:1\n     K:1\n          F:1\n                         D:1\n                    C:1\n               B:1\n                    A:2\n-----------------------------------------------\n");

    std::cout << "OK" << std::endl;
    
// *************************************************************************
// LEVEL 2: Odebrani prvku
// *************************************************************************
#ifdef LEVEL2
    std::cout << "Level 2:   ";
    
    t1.remove("B");
    //std::cout << t1.toString2D();
    assert(t1.toString2D() == "          T:1\n               R:1\n                    M:1\n     K:1\n          F:1\n                    D:1\n               C:1\n                    A:2\n-----------------------------------------------\n");
    
    t1.remove("T");
    //std::cout << std::endl << t1.toString2D();
    assert(t1.toString2D() == "          R:1\n               M:1\n     K:1\n          F:1\n                    D:1\n               C:1\n                    A:2\n-----------------------------------------------\n");
    
    t1.remove("A");
    //std::cout << std::endl << t1.toString2D();
    assert(t1.toString2D() == "          R:1\n               M:1\n     K:1\n          F:1\n                    D:1\n               C:1\n                    A:1\n-----------------------------------------------\n");
    
    t1.remove("K");
    //std::cout << std::endl << t1.toString2D();
    assert(t1.toString2D() == "          R:1\n     M:1\n          F:1\n                    D:1\n               C:1\n                    A:1\n-----------------------------------------------\n");
    
    t1.remove("M");
    //std::cout << std::endl  << t1.toString2D();
    assert(t1.toString2D() == "     R:1\n          F:1\n                    D:1\n               C:1\n                    A:1\n-----------------------------------------------\n");
    
    std::cout << "OK" << std::endl;
    
// *************************************************************************
// LEVEL 2.5: Random Data
// *************************************************************************
#ifdef LEVEL2_5
    std::cout << "Level 2.5: ";
    BinTree t1a;
    srand(time(NULL));
    std::string tmp = "AAA";
    for (int i=0; i<RND_TEST; i++)
    {
        tmp[0] = 65+rand()%26;
        tmp[1] = 65+rand()%26;
        tmp[2] = 65+rand()%26;
        
        if ( rand()%4) t1a.add(tmp); else t1a.remove(tmp);
        if (i%PROGRESS==0) std::cout << "." << std::flush;
    }
    t1a.clear();
    std::cout << " OK" << std::endl;

// *************************************************************************
// LEVEL 3: Pretizeny operator [] pro cteni
// *************************************************************************
#ifdef LEVEL3
    std::cout << "Level 3:   ";
    
    assert(t1["A"]==1);
    assert(t1["K"]==0);
    
    std::cout << "OK" << std::endl;
  
    
// *************************************************************************
// LEVEL 4: Zretezene pridani/mazani, operator += a -= pro pridani/mazani prvku
// *************************************************************************
#ifdef LEVEL4
    std::cout << "Level 4:   ";
    
    t1 += "A";
    t1 += "A";
    t1 -= "A";
    //std::cout << t1.toString2D();
    assert(t1["A"]==2);
    assert(t1["J"]==0);

    BinTree t2;
    t2 += "X"; t2 += "W";  t2 += "A"; t2 += "B"; t2 += "B"; t2 += "B";
    t2.add("X").add("D").add("R").add("A").add("A").add("A").remove("A").add("A");
    
    std::cout << "OK" << std::endl;

    
// *************************************************************************
// LEVEL 5: Operator pricteni stromu
// *************************************************************************
#ifdef LEVEL5
    std::cout << "Level 5:   ";
    t2 += t1;
    
    assert(t2["X"]==2);
    assert(t2["A"]==6);
    assert(t2["W"]==1);
    
    std::cout << "OK" << std::endl;
    
    std::cout << "Level 5 dosazen, skoc si pro 2 body!" << std::endl;
    
// *************************************************************************
// LEVEL 6: Kopirovaci konstruktor
// *************************************************************************
#ifdef LEVEL6
    std::cout << "Level 6:   ";
    
    BinTree t3a(t1);
    BinTree t3 = t3a;
    t3a.clear();
    assert(t3.toString2D() == "     R:1\n          F:1\n                    D:1\n               C:1\n                    A:2\n-----------------------------------------------\n");
    
    std::cout << "OK" << std::endl;
    

    
// *************************************************************************
// LEVEL 7: Operator prirazeni
// *************************************************************************
#ifdef LEVEL7
    std::cout << "Level 7:   ";
    
    BinTree *t4 = new BinTree;
    BinTree *t5 = new BinTree;
    BinTree *t6 = new BinTree(t1);
    
    *t4 = *t5 = t1;
    assert(t4->toString2D() == "     R:1\n          F:1\n                    D:1\n               C:1\n                    A:2\n-----------------------------------------------\n");
    assert(t5->toString2D() == "     R:1\n          F:1\n                    D:1\n               C:1\n                    A:2\n-----------------------------------------------\n");
    assert(t6->toString2D() == "     R:1\n          F:1\n                    D:1\n               C:1\n                    A:2\n-----------------------------------------------\n");
    t5->clear();
    assert(t4->toString2D() == "     R:1\n          F:1\n                    D:1\n               C:1\n                    A:2\n-----------------------------------------------\n");
    assert(t5->toString2D() == "-----------------------------------------------\n");
    
    std::cout << "OK" << std::endl;
    
    
// *************************************************************************
// LEVEL 8: Operator scitani stromu
// *************************************************************************
#ifdef LEVEL8
    std::cout << "Level 8:   ";
    
    BinTree t7 = t1 + t2 + t3 + *t5;
    
    assert(t7["A"]==10);
    assert(t7["W"]==1);
    
    //std::cout << t7.toString2D();
    
    delete t4;
    delete t5;
    delete t6;
    
    std::cout << "OK" << std::endl;
    
    
// *************************************************************************
// LEVEL 9: Pretizene operatory << a >> pro vstup a vystup ze streamu
// *************************************************************************
#ifdef LEVEL9
    std::cout << "Level 9:   " << std::endl;
    
    BinTree t1000;
    std::ifstream file("d1.txt");
    if (file.is_open())
    {
        file >> t1000;
        
        file.close();
        std::cout << t1000 << std::endl;
        assert(t1000["of"]==3);
        assert(t1000["then"]==2);
    }
    else 
    {
        std::cerr << "Cannot open file" << std::endl;
        std::abort();
    }
    
    std::cout << "OK" << std::endl;
    
    std::cout << "Vse je hotovo, skoc si pro dalsi 2 body!" << std::endl;

#endif //l9
#endif //l8
#endif //l7
#endif //l6
#endif //l5
#endif //l4
#endif //l3
#endif //l2.5 
#endif //l2
#endif //l1
    
    return 0;
}
    
