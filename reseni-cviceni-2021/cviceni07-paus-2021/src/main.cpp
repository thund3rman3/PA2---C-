#include <cstdio>
#include <iostream>
#include <list>

//#define PRINTCONSTRDESTR  // print constructor and destructor calls

class PrintFormat
{
public:
    virtual std::string operator()(const std::string& s) const = 0;
    virtual PrintFormat* Clone() const = 0;
    virtual ~PrintFormat() {};
};

class NormalCaseFormat : public PrintFormat
{
public:
#ifdef PRINTCONSTRDESTR
    NormalCaseFormat() { std::cout << "Normal" << std::endl; }
    NormalCaseFormat(const NormalCaseFormat& other) { std::cout << "Normal copy" << std::endl; }
    ~NormalCaseFormat() { std::cout << "~Normal" << std::endl; };
#endif

    std::string operator()(const std::string &s) const
    {
        return s;
    }
    NormalCaseFormat* Clone() const
    {
        return new NormalCaseFormat(*this);
    }
};

class UpperCaseFormat: public PrintFormat
{
public:
#ifdef PRINTCONSTRDESTR
    UpperCaseFormat() { std::cout << "Upper" << std::endl; }
    UpperCaseFormat(const UpperCaseFormat &other) { std::cout << "Upper copy" << std::endl; }
    ~UpperCaseFormat() { std::cout << "~Upper" << std::endl; };
#endif
    std::string operator()(const std::string &s) const
    {
        std::string tmp = s;
        for (char& c : tmp) c = std::toupper(c);

        return tmp;
    }
    UpperCaseFormat *Clone() const
    {
        return new UpperCaseFormat(*this);
    }
};


class PrettyPrinter 
{
    std::list<std::string> l;
    PrintFormat *pf;

public:
    PrettyPrinter():pf(nullptr){}

    void AddWord(std::string s)
    {
        l.push_back(s);
    }

    void SetFormat(const PrintFormat& f)
    {
        if (pf) delete pf;
        pf = f.Clone();
    }
    ~PrettyPrinter()
    {
        if (pf) delete pf;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const PrettyPrinter& pp);
};

std::ostream &operator<<(std::ostream &os, const PrettyPrinter& pp)
{
    for ( const std::string& s : pp.l) os << pp.pf->operator()(s) << std::endl;
    return os;
}

int main()
{
    PrettyPrinter pp;
    pp.SetFormat(UpperCaseFormat());
    pp.AddWord("AbCdEffasda ASDS");
    pp.AddWord("sdfsdfsdfsd");
    pp.AddWord("ASDS");
    pp.AddWord("121651");
    std::cout << pp << std::endl;
    pp.SetFormat(NormalCaseFormat());
    std::cout << pp << std::endl;

    PrintFormat* pf = new NormalCaseFormat;
    pp.SetFormat(*pf);
    std::cout << pp << std::endl;

    delete pf;

    std::cout << pp << std::endl;

    return 0;
}