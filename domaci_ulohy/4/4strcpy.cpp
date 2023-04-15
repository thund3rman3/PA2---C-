#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
#endif /* __PROGTEST__ */

const int ADDRESS_LEN = 100;
const int EMAIL_LEN = 1024;

template <class T>
class CVector
{
public:
  CVector()
  {
    m_cap = 10;
    m_size = 0;
    m_array = new T[m_cap];
  }

  ~CVector()
  {
    delete[] m_array;
  }

  void emplace_back(const T &mail)
  {
    if (m_size >= m_cap)
    {
      m_cap = 2 * m_cap;
      T *tmp = new T[m_cap];
      for (size_t x = 0; x < m_size; x++)
      {
        cpy_strings(tmp[x], m_array[x]);
      }
      delete[] m_array;
      m_array = tmp;
    }
    cpy_strings(m_array[m_size], mail);
    m_size++;
  }

  size_t size() const
  {
    return m_size;
  }

  T *begin() const
  {
    return m_array;
  }

  T *end() const
  {
    return m_array + m_size;
  }

  T &operator[](size_t idx) const
  {
    return m_array[idx];
  }

  void free_and_initialize_array()
  {
    delete[] m_array;
    m_cap = 10;
    m_size = 0;
    m_array = new T[m_cap];
  }

private:
  size_t m_cap;
  size_t m_size;
  T *m_array;
};

class CMail
{
public:
  CMail() = default;

  CMail(const char *from,
        const char *to,
        const char *body)
  {
    memcpy(m_from, from, strlen(m_from)+1);
    memcpy(m_to, to,strlen(m_to)+1);
    memcpy(m_body, body,strlen(m_body)+1);
  }

  friend void cpy_strings(CMail &a, const CMail &b)
  {
    memcpy(a.m_from, b.m_from, strlen(a.m_from)+1);
    memcpy(a.m_to, b.m_to,strlen(a.m_to)+1);
    memcpy(a.m_body, b.m_body,strlen(a.m_body)+1);
  }

  bool operator==(const CMail &x) const
  {
    if (strcmp(this->m_body, x.m_body) == 0 &&
        strcmp(this->m_from, x.m_from) == 0 &&
        strcmp(this->m_to, x.m_to) == 0)
    {
      return true;
    }
    return false;
  }

  friend ostream &operator<<(ostream &os,
                             const CMail &m)
  {
    //"From: john, To: alice, Body: deadline notice"
    os << "From: " << m.m_from << ", To: " << m.m_to << ", Body: " << m.m_body;
    return os;
  }

  const char *get_from() const
  {
    return m_from;
  }

  const char *get_to() const
  {
    return m_to;
  }

  const char *get_body() const
  {
    return m_body;
  }

private:
  char m_from[ADDRESS_LEN];
  char m_to[ADDRESS_LEN];
  char m_body[EMAIL_LEN];
};

class CMailIterator
{
public:
  CMailIterator(const CVector<CMail> &vServer, const char *email, bool outbox)
      : idx(0)
  {
    for (const auto &x : vServer)
    {
      if (outbox == true && strcmp(x.get_from(), email) == 0)
        vMail.emplace_back(x);
      else if (outbox == false && strcmp(x.get_to(), email) == 0)
        vMail.emplace_back(x);
    }
  }
  explicit operator bool(void) const
  {
    if (idx < vMail.size())
      return true;
    return false;
  }
  bool operator!(void) const
  {
    if (idx >= vMail.size())
      return true;
    return false;
  }
  const CMail &operator*(void) const
  {
    return this->vMail[this->idx];
  }

  CMailIterator &operator++(void)
  {
    idx++;
    return *this;
  }

private:
  // todo
  CVector<CMail> vMail;
  size_t idx;
};

class CMailServer
{
public:
  CMailServer() = default;
  CMailServer(const CMailServer &src)
  {
    for (const auto &x : src.vMail)
    {
      vMail.emplace_back(x);
    }
  }
  CMailServer &operator=(const CMailServer &src)
  {
    vMail.free_and_initialize_array();
    for (const auto &x : src.vMail)
    {
      vMail.emplace_back(x);
    }
    return *this;
  }
  ~CMailServer()
  {
  }
  void sendMail(const CMail &m)
  {
    vMail.emplace_back(m);
  }
  CMailIterator outbox(const char *email) const
  {
    return CMailIterator(vMail, email, true);
  }
  CMailIterator inbox(const char *email) const
  {
    return CMailIterator(vMail, email, false);
  }

private:
  // todo
  CVector<CMail> vMail;
};

#ifndef __PROGTEST__
bool matchOutput(const CMail &m,
                 const char *str)
{
  ostringstream oss;
  oss << m;
  return oss.str() == str;
  // assert(matchOutput(*i0, "From: john, To: alice, Body: deadline notice"));
}

int main(void)
{
  char from[100], to[100], body[1024];

  assert(CMail("john", "peter", "progtest deadline") == CMail("john", "peter", "progtest deadline"));
  assert(!(CMail("john", "peter", "progtest deadline") == CMail("john", "progtest deadline", "peter")));
  assert(!(CMail("john", "peter", "progtest deadline") == CMail("peter", "john", "progtest deadline")));
  assert(!(CMail("john", "peter", "progtest deadline") == CMail("peter", "progtest deadline", "john")));
  assert(!(CMail("john", "peter", "progtest deadline") == CMail("progtest deadline", "john", "peter")));
  assert(!(CMail("john", "peter", "progtest deadline") == CMail("progtest deadline", "peter", "john")));
  CMailServer s0;
  s0.sendMail(CMail("john", "peter", "some important mail"));
  strncpy(from, "john", sizeof(from));
  strncpy(to, "thomas", sizeof(to));
  strncpy(body, "another important mail", sizeof(body));
  s0.sendMail(CMail(from, to, body));
  strncpy(from, "john", sizeof(from));
  strncpy(to, "alice", sizeof(to));
  strncpy(body, "deadline notice", sizeof(body));
  s0.sendMail(CMail(from, to, body));
  s0.sendMail(CMail("alice", "john", "deadline confirmation"));
  s0.sendMail(CMail("peter", "alice", "PR bullshit"));
  CMailIterator i0 = s0.inbox("alice");
  assert(i0 && *i0 == CMail("john", "alice", "deadline notice"));
  assert(matchOutput(*i0, "From: john, To: alice, Body: deadline notice"));
  assert(++i0 && *i0 == CMail("peter", "alice", "PR bullshit"));
  assert(matchOutput(*i0, "From: peter, To: alice, Body: PR bullshit"));
  assert(!++i0);

  CMailIterator i1 = s0.inbox("john");
  assert(i1 && *i1 == CMail("alice", "john", "deadline confirmation"));
  assert(matchOutput(*i1, "From: alice, To: john, Body: deadline confirmation"));
  assert(!++i1);

  CMailIterator i2 = s0.outbox("john");
  assert(i2 && *i2 == CMail("john", "peter", "some important mail"));
  assert(matchOutput(*i2, "From: john, To: peter, Body: some important mail"));
  assert(++i2 && *i2 == CMail("john", "thomas", "another important mail"));
  assert(matchOutput(*i2, "From: john, To: thomas, Body: another important mail"));
  assert(++i2 && *i2 == CMail("john", "alice", "deadline notice"));
  assert(matchOutput(*i2, "From: john, To: alice, Body: deadline notice"));
  assert(!++i2);

  CMailIterator i3 = s0.outbox("thomas");
  assert(!i3);

  CMailIterator i4 = s0.outbox("steve");
  assert(!i4);

  CMailIterator i5 = s0.outbox("thomas");
  s0.sendMail(CMail("thomas", "boss", "daily report"));
  assert(!i5);

  CMailIterator i6 = s0.outbox("thomas");
  assert(i6 && *i6 == CMail("thomas", "boss", "daily report"));
  assert(matchOutput(*i6, "From: thomas, To: boss, Body: daily report"));
  assert(!++i6);

  CMailIterator i7 = s0.inbox("alice");
  s0.sendMail(CMail("thomas", "alice", "meeting details"));
  assert(i7 && *i7 == CMail("john", "alice", "deadline notice"));
  assert(matchOutput(*i7, "From: john, To: alice, Body: deadline notice"));
  assert(++i7 && *i7 == CMail("peter", "alice", "PR bullshit"));
  assert(matchOutput(*i7, "From: peter, To: alice, Body: PR bullshit"));
  assert(!++i7);

  CMailIterator i8 = s0.inbox("alice");
  assert(i8 && *i8 == CMail("john", "alice", "deadline notice"));
  assert(matchOutput(*i8, "From: john, To: alice, Body: deadline notice"));
  assert(++i8 && *i8 == CMail("peter", "alice", "PR bullshit"));
  assert(matchOutput(*i8, "From: peter, To: alice, Body: PR bullshit"));
  assert(++i8 && *i8 == CMail("thomas", "alice", "meeting details"));
  assert(matchOutput(*i8, "From: thomas, To: alice, Body: meeting details"));
  assert(!++i8);

  CMailServer s1(s0);
  s0.sendMail(CMail("joe", "alice", "delivery details"));
  s1.sendMail(CMail("sam", "alice", "order confirmation"));
  CMailIterator i9 = s0.inbox("alice");
  assert(i9 && *i9 == CMail("john", "alice", "deadline notice"));
  assert(matchOutput(*i9, "From: john, To: alice, Body: deadline notice"));
  assert(++i9 && *i9 == CMail("peter", "alice", "PR bullshit"));
  assert(matchOutput(*i9, "From: peter, To: alice, Body: PR bullshit"));
  assert(++i9 && *i9 == CMail("thomas", "alice", "meeting details"));
  assert(matchOutput(*i9, "From: thomas, To: alice, Body: meeting details"));
  assert(++i9 && *i9 == CMail("joe", "alice", "delivery details"));
  assert(matchOutput(*i9, "From: joe, To: alice, Body: delivery details"));
  assert(!++i9);

  CMailIterator i10 = s1.inbox("alice");
  assert(i10 && *i10 == CMail("john", "alice", "deadline notice"));
  assert(matchOutput(*i10, "From: john, To: alice, Body: deadline notice"));
  assert(++i10 && *i10 == CMail("peter", "alice", "PR bullshit"));
  assert(matchOutput(*i10, "From: peter, To: alice, Body: PR bullshit"));
  assert(++i10 && *i10 == CMail("thomas", "alice", "meeting details"));
  assert(matchOutput(*i10, "From: thomas, To: alice, Body: meeting details"));
  assert(++i10 && *i10 == CMail("sam", "alice", "order confirmation"));
  assert(matchOutput(*i10, "From: sam, To: alice, Body: order confirmation"));
  assert(!++i10);

  CMailServer s2;
  s2.sendMail(CMail("alice", "alice", "mailbox test"));
  CMailIterator i11 = s2.inbox("alice");
  assert(i11 && *i11 == CMail("alice", "alice", "mailbox test"));
  assert(matchOutput(*i11, "From: alice, To: alice, Body: mailbox test"));
  assert(!++i11);

  s2 = s0;
  s0.sendMail(CMail("steve", "alice", "newsletter"));
  s2.sendMail(CMail("paul", "alice", "invalid invoice"));
  CMailIterator i12 = s0.inbox("alice");
  assert(i12 && *i12 == CMail("john", "alice", "deadline notice"));
  assert(matchOutput(*i12, "From: john, To: alice, Body: deadline notice"));
  assert(++i12 && *i12 == CMail("peter", "alice", "PR bullshit"));
  assert(matchOutput(*i12, "From: peter, To: alice, Body: PR bullshit"));
  assert(++i12 && *i12 == CMail("thomas", "alice", "meeting details"));
  assert(matchOutput(*i12, "From: thomas, To: alice, Body: meeting details"));
  assert(++i12 && *i12 == CMail("joe", "alice", "delivery details"));
  assert(matchOutput(*i12, "From: joe, To: alice, Body: delivery details"));
  assert(++i12 && *i12 == CMail("steve", "alice", "newsletter"));
  assert(matchOutput(*i12, "From: steve, To: alice, Body: newsletter"));
  assert(!++i12);

  CMailIterator i13 = s2.inbox("alice");
  assert(i13 && *i13 == CMail("john", "alice", "deadline notice"));
  assert(matchOutput(*i13, "From: john, To: alice, Body: deadline notice"));
  assert(++i13 && *i13 == CMail("peter", "alice", "PR bullshit"));
  assert(matchOutput(*i13, "From: peter, To: alice, Body: PR bullshit"));
  assert(++i13 && *i13 == CMail("thomas", "alice", "meeting details"));
  assert(matchOutput(*i13, "From: thomas, To: alice, Body: meeting details"));
  assert(++i13 && *i13 == CMail("joe", "alice", "delivery details"));
  assert(matchOutput(*i13, "From: joe, To: alice, Body: delivery details"));
  assert(++i13 && *i13 == CMail("paul", "alice", "invalid invoice"));
  assert(matchOutput(*i13, "From: paul, To: alice, Body: invalid invoice"));
  assert(!++i13);

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
