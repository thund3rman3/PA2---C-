#include <stdexcept>
#include <string>
#include <iostream>

class BaseExcept
{
protected:
    std::string msg;
public:
    BaseExcept(const std::string& m): msg(m) {}
    //BaseExcept(const BaseExcept& other) = delete;
    virtual ~BaseExcept() {}
    virtual std::string what() const
    {
        return msg;
    };
};

class PasswordTooShortExcept : public BaseExcept
{
    size_t len;
public:
    PasswordTooShortExcept(const std::string& m, size_t l):BaseExcept(m), len(l) {  }
    std::string what() const
    {
        return msg + " len = " + std::to_string(len);
    }


};

class BadCharExcept : public BaseExcept
{
    char c;
public:
    BadCharExcept(const std::string& m, char cc):BaseExcept(m), c(cc) {}
    std::string what() const
    {
        return msg + " c = " + c;
    }
};

unsigned factorial(unsigned n)
{
    unsigned result = 1;

    if (n > 10) throw std::invalid_argument(std::to_string(n));

    for (unsigned i = 1; i<=n; i++)
    {
        result *= i;
    }
    return result;
}

void passwd(const std::string& p)
{
    if (p.length() < 5) throw PasswordTooShortExcept("Password too short!", p.length());
    
    size_t x = p.find_first_of(".,:;");
    if (x != std::string::npos ) throw BadCharExcept("Bad Char!", p[x]);

    if (p == "12345") throw std::string("Stupid user!");
}


int main()
{
    try 
    {
        std::cout << factorial(10) << std::endl;
        std::cout << factorial(11) << std::endl;
    }
    catch (unsigned& e)
    {
        std::cout << "Invalid argument, n = " << e << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Invalid argument, n = " << e.what() << std::endl;
    }

    try 
    { 
        passwd("12345");
    }
    catch (PasswordTooShortExcept &e)
    {
        std::cout << "Short " <<e.what() << std::endl;
    }
    catch (BaseExcept& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "error" << std::endl;
    }


    //passwd("12345:");
    //passwd("aaa222aaa");

    std::cout << "bla bla bla" << std::endl;

    return 0;
}