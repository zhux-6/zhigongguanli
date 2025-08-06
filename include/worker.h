#pragma once
#include <iostream>
#include <string>

using namespace std;

class worker {
  public:
    virtual void showinfo() = 0;
    virtual string getbumen() = 0;
    int m_id;
    string m_name;
    int bumen;
};
class putong : public worker {

  public:
    putong(int id, string name, int bumen);
    virtual void showinfo();
    virtual string getbumen();
};
class jingli : public worker {

  public:
    jingli(int id, string name, int bumen);
    virtual void showinfo();
    virtual string getbumen();
};
class boss : public worker {

  public:
    boss(int id, string name, int bumen);
    virtual void showinfo();
    virtual string getbumen();
};