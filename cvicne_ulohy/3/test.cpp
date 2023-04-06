#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <cassert>
#include <sstream>
using namespace std;

class CTimeTester;
#endif /* __PROGTEST__ */

class CTime
{
private:
    int m_Hour;
    int m_Minute;
    int m_Second;

public:
    // constructor, destructor
    CTime() {}
    CTime(int hour, int minute)
    {
        if (hour > 23 || hour < 0 || minute > 59 || minute < 0)
            throw invalid_argument("invalid input");
        m_Hour = hour;
        m_Minute = minute;
        m_Second = 0;
    }
    CTime(int hour, int minute, int sec)
    {
        if (hour > 23 || hour < 0 || minute > 59 || minute < 0 || sec > 59 || sec < 0)
            throw invalid_argument("invalid input");
        m_Hour = hour;
        m_Minute = minute;
        m_Second = sec;
    }
    // arithmetic operators
    CTime operator+(int sec) const
    {
        CTime timer(m_Hour, m_Minute, m_Second);
        int secs = timer.total_sec() + sec;
        timer.get_time(secs);
        return timer;
    }

    friend CTime operator+(int sec,const CTime& a)
    {
        CTime timer(a.m_Hour, a.m_Minute, a.m_Second);
        int secs = timer.total_sec() + sec;
        timer.get_time(secs);
        return timer;
    }

    CTime &operator+=(int sec)
    {
        int secs = total_sec() + sec;
        get_time(secs);
        return *this;
    }
    CTime operator-(int sec) const  
    {
        CTime timer(m_Hour, m_Minute, m_Second);
        int secs = timer.total_sec() - sec;
        timer.get_time(secs);
        return timer;
    }

    friend CTime operator-(int sec, const CTime& a)
    {
        CTime timer(a.m_Hour, a.m_Minute, a.m_Second);
        int secs = timer.total_sec() - sec;
        timer.get_time(secs);
        return timer;
    }

    CTime &operator-=(int sec)
    {
        int secs = total_sec() - sec;
        get_time(secs);
        return *this;
    }

    friend int operator-(const CTime &a, const CTime &b)
    {
        int secs_a = a.total_sec();
        int secs_b = b.total_sec();
        if (secs_a == secs_b)
            return 0;
        if (secs_a > secs_b)
        {
            secs_a -= secs_b;
            return secs_a;
        }
        else
        {
            secs_b -= secs_a;
            return secs_b;
        }
    }
    CTime &operator++()
    {

        int secs = total_sec();
        secs++;
        get_time(secs);
        return *this;
    }
    const CTime operator++(int)
    {
        CTime tmp(this->m_Hour,this->m_Minute,this->m_Second);
        int secs = total_sec();
        secs++;
        this->get_time(secs);
        return tmp;
    }

    CTime &operator--()
    {
        int secs = total_sec();
        secs--;
        get_time(secs);
        return *this;
    }
    const CTime operator--(int)
    {
        CTime tmp(this->m_Hour,this->m_Minute,this->m_Second);
        int secs = total_sec();
        secs--;
        this->get_time(secs);
        return tmp;
    }

    // comparison operators
    bool operator<(const CTime& b) const
    {
        int secs_a = this->total_sec();
        int secs_b = b.total_sec();
        return secs_a < secs_b;
    }
    bool operator<=(const CTime& b) const
    {
        int secs_a = this->total_sec();
        int secs_b = b.total_sec();
        return secs_a <= secs_b;
    }
    bool operator>(const CTime& b) const
    {
        int secs_a = this->total_sec();
        int secs_b = b.total_sec();
        return secs_a > secs_b;
    }
    bool operator>=(const CTime& b) const
    {
        int secs_a = this->total_sec();
        int secs_b = b.total_sec();
        return secs_a >= secs_b;
    }
    friend bool operator==(const CTime& a,const CTime& b)
    {
        int secs_a = a.total_sec();
        int secs_b = b.total_sec();
        return secs_a == secs_b;
    }
    bool operator!=(const CTime& b) const
    {
        int secs_a = this->total_sec();
        int secs_b = b.total_sec();
        return secs_a != secs_b;
    }
    // output operator
    friend ostream& operator<<(ostream& oss,const CTime& a)
    {   
        oss<<setw(2)<<(a.m_Hour)<<":" <<setfill('0')<<setw(2)<<(a.m_Minute)<<":"<<setfill('0')<<setw(2)<<(a.m_Second); 
        return oss;
    }    

    //others
    friend class ::CTimeTester;

    int total_sec() const
    {
        return m_Hour * 60 * 60 + m_Minute * 60 + m_Second;
    }
    void get_time(int secs)
    {   
        int secs_in_day = 60*60*24;
        while(secs < 0)
            secs+=secs_in_day;

        if(secs >= secs_in_day)
            secs%=secs_in_day;
            
        m_Hour = secs / (60 * 60);
        secs -= m_Hour * 60 * 60;
        m_Minute = secs / 60;
        secs -= m_Minute * 60;
        m_Second = secs;
    }
};

#ifndef __PROGTEST__
struct CTimeTester
{
    static bool test(const CTime &time, int hour, int minute, int second)
    {
        return time.m_Hour == hour && time.m_Minute == minute && time.m_Second == second;
    }
};

int main()
{
    CTime a{12, 30};
    assert(CTimeTester::test(a, 12, 30, 0));

    CTime b{13, 30};
    assert(CTimeTester::test(b, 13, 30, 0));

    assert(b - a == 3600);

    assert(CTimeTester::test(a + 60, 12, 31, 0));
    assert(CTimeTester::test(a - 60, 12, 29, 0));

    assert(a < b);
    assert(a <= b);
    assert(a != b);
    assert(!(a > b));
    assert(!(a >= b));
    assert(!(a == b));

    while (++a != b)
        ;
    assert(a == b);

    std::ostringstream output;
    assert(static_cast<bool>(output << a));
    //cout<<output.str();
    assert(output.str() == "13:30:00");

    assert(a++ == b++);
    assert(a == b);

    assert(--a == --b);
    assert(a == b);

    assert(a-- == b--);
    assert(a == b);

    return 0;
}
#endif /* __PROGTEST__ */
