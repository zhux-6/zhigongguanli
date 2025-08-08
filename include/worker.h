#pragma once
#include <iostream>
#include <string>

using namespace std;

class worker {
  public:
    virtual void showinfo() const = 0;
    virtual string getbumen() const = 0;
    virtual ~worker();

    friend std::ostream &operator<<(std::ostream &os, const worker &w);

    int m_id;
    string m_name;
    int bumen;
};
class putong : public worker {

  public:
    putong(int id, string name, int bumen);
    virtual void showinfo() const;
    virtual string getbumen() const;
};
class jingli : public worker {

  public:
    jingli(int id, string name, int bumen);
    virtual void showinfo() const;
    virtual string getbumen() const;
};
class boss : public worker {

  public:
    boss(int id, string name, int bumen);
    virtual void showinfo() const;
    virtual string getbumen() const;
};