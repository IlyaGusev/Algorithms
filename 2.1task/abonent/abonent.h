#ifndef ABONENT_H_INCLUDED
#define ABONENT_H_INCLUDED
#include <iostream>
#include <cstring>
#include "../datetime/datetime.h"
#include "../flist/flist.h"

using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;
using my::forward_list;
using my::forward_list_iterator;
using my::forward_list_const_iterator;

class Abonent;
class Call{
private:
    DateTime _date;
    TimeSpan _time;
    long long int _number;
public:
    Call() : _date(DateTime()), _time(TimeSpan()), _number(0) {};
    Call(long long int __number , DateTime __date, TimeSpan __time) :
   _date(__date), _time(__time), _number(__number) {};

    friend ostream& operator<< (ostream&, const Call&);
    friend istream& operator>> (istream&, Call&);
    friend class Abonent;
};

class Abonent{
typedef forward_list_iterator<Call> iterator;
typedef forward_list_const_iterator<Call> const_iterator;
private:
    string _name;
    double _tariff;
    double _money;
    forward_list<Call> _history;
public:
    Abonent() : _name(string()), _tariff(0), _money(0), _history(forward_list<Call>()) {};
    Abonent(string __name, double __tariff, double __money) :
    _name(__name), _tariff(__tariff), _money(__money), _history(forward_list<Call>()) {};

    friend ostream& operator<< (ostream&, const Abonent&);
    friend istream& operator>> (istream&, Abonent&);

    void recharge(double);
    double getBalance() const;
    void addCall();
    void addCall(Call&);
    void showHistory() const;
    void showHistoryInTimeDuration(const DateTime&, const DateTime&) const;
    void showHistoryFromNumber(long long int) const;

};
ostream& operator<<(ostream & s, const Call& obj){
    s<<obj._number<<" | "<<obj._date<<" | "<<obj._time;
    return s;
}
istream& operator>>(istream & s, Call& obj){
    s>>obj._number;
    s>>obj._date;
    s>>obj._time;
    return s;
}
ostream& operator<<(ostream & s, const Abonent& obj){
    s<<obj._name<<" | "<<obj._tariff<<" | "<<obj._money;
    return s;
}
istream& operator>>(istream & s, Abonent& obj){
    string str1, str2, str3;
    s>>str1>>str2>>str3>>obj._tariff>>obj._money;
    obj._name=obj._name+str1;
    obj._name=obj._name+" ";
    obj._name=obj._name+str2;
    obj._name=obj._name+" ";
    obj._name=obj._name+str3;
    return s;
}

void Abonent::recharge(double __money){ _money=+abs(__money); }
double Abonent::getBalance() const{ return _money; }
void Abonent::addCall(){
    Call c;
    cin>>c;
    _history.push_front(c);
    _money-=(_tariff/60)*(c._time.getSecond());
}
void Abonent::addCall(Call& obj){
    _history.push_front(obj);
    _money-=(_tariff/60)*(obj._time.getSecond());
}
void Abonent::showHistory() const{
    const_iterator cur=_history.begin();
    for (int i=0; i<_history.size(); i++)
        cout<<*cur++<<endl;
}
void Abonent::showHistoryInTimeDuration(const DateTime& first, const DateTime& second) const{
    time_t unixtime1=first.getUnixtime();
    time_t unixtime2=second.getUnixtime();
    const_iterator cur=_history.begin();
    for (int i=0; i<_history.size(); i++){
        if ((*cur)._date.getUnixtime()>=unixtime1 && (*cur)._date.getUnixtime()<=unixtime2)
            cout<<*cur<<endl;
        cur++;
    }
}
void Abonent::showHistoryFromNumber(long long int num) const{
    const_iterator cur=_history.begin();
    for (int i=0; i<_history.size(); i++){
        if ((*cur)._number==num)
            cout<<*cur<<endl;
        cur++;
    }
}

#endif // ABONENT_H_INCLUDED
