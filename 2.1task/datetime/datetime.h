#ifndef DATETIME_H_INCLUDED
#define DATETIME_H_INCLUDED
#include <iostream>
#include <time.h>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::cerr;
using std::runtime_error;
class TimeSpan;
void itoa_with_concat(int, string&);

class DateTime
{
private:
    int _year;
    int _month;
    int _day;
    int _hour;
    int _minute;
    int _second;
public:
    DateTime() : _year(1970), _month(1), _day(1), _hour(0), _minute(0), _second(0) {}
    DateTime(const DateTime& copy);
    explicit DateTime(time_t);
    DateTime(int, int, int, int, int, int);
    DateTime(int, int, int);
    DateTime(string);

    bool check() const;
    bool check(int, int, int, int, int, int) const;
    DateTime& add(const TimeSpan& diff) {(*this)=(*this)+diff; return (*this); }
    DateTime& addYear(int);
    DateTime& addMonth(int);
    DateTime& addDay(int);
    DateTime& addHour(int);
    DateTime& addMinute(int);
    DateTime& addSecond(int);

    int getYear() const {return _year; }
    int getMonth() const {return _month; }
    int getDay() const {return _day; }
    int getHour() const {return _hour; }
    int getMinute() const {return _minute; }
    int getSecond() const {return _second; }

    time_t getUnixtime() const;
    static DateTime getCurrentDateTime() { return DateTime(time(0)); }
    int getDayOfWeek() const;

    friend istream& operator>>(istream&, DateTime&);
    friend ostream& operator<<(ostream&, const DateTime&);

    bool operator<(const DateTime&) const;
    bool operator==(const DateTime&) const;
    bool operator<=(const DateTime& right) const { return (((*this)<right) && ((*this)==right)); }
    bool operator>(const DateTime& right) const { return (!((*this)<=right));}
    bool operator>=(const DateTime& right) const { return (!((*this)<right)); }
    bool operator!=(const DateTime& right) const { return (!((*this)==right)); }

    DateTime& operator=(const DateTime&);
    DateTime operator+(const TimeSpan&);
    friend TimeSpan operator-(const DateTime&, const DateTime&);
    DateTime operator-(const TimeSpan&);

    operator string() const;
};
class TimeSpan
{
private:
    time_t _second;
public:
    TimeSpan() : _second(0) {}
    TimeSpan(const TimeSpan & copy) : _second(copy._second) {}
    TimeSpan(time_t __second) : _second(__second) {}

    friend istream& operator>>(istream& s, TimeSpan& a) { s>>a._second; return s; }
    friend ostream& operator<<(ostream& s, const TimeSpan& a) { s<<a._second; return s; }

    time_t getSecond() const { return _second; }
    int getMinute() const { return (_second/60); }
    int getHour() const { return (_second/(60*60)); }
    int getDay() const { return (_second/(60*60*24)); }
    void add(time_t diff){ _second+=diff; }

    bool operator<(const TimeSpan& obj) const{ return (_second<obj._second); }
    bool operator<=(const TimeSpan& obj) const{ return (_second<=obj._second); }
    bool operator>(const TimeSpan& obj) const{ return (_second>obj._second); }
    bool operator>=(const TimeSpan& obj) const{ return (_second>=obj._second); }
    bool operator==(const TimeSpan& obj) const{ return (_second==obj._second); }
    bool operator!=(const TimeSpan& obj) const{ return (_second!=obj._second); }

    TimeSpan& operator=(const TimeSpan& copy){ _second=copy._second; return (*this); }
    TimeSpan& operator-(){ _second=-_second; return (*this); }
};

    /// Constructors
DateTime::DateTime(const DateTime& copy) :
_year(copy._year), _month(copy._month), _day(copy._day),
_hour(copy._hour), _minute(copy._minute), _second(copy._second){}

DateTime::DateTime(time_t unixtime) : _year(1970), _month(1), _day(1) {
    int day_ =unixtime/(60*24*60);
    int hour_=unixtime/(60*60);
    int minute_=unixtime/(60);
    _hour=hour_-day_*24;
    _minute=minute_-hour_*60;
    _second=unixtime%60;
    for (int i=0; i<day_; i++){
        _day++;
        if (!check()){
            _day=1;
            _month++;
            if (!check()){
                _month=1;
                _year++;
            }
        }
    }
}
DateTime::DateTime(int __day, int __month, int __year, int __hour, int __minute, int __second) {
    if (check(__year, __month, __day, __hour, __minute, __second)){
        _year=__year;
        _month=__month;
        _day=__day;
        _hour=__hour;
        _minute=__minute;
        _second=__second;
    }
    else{
        cerr<<"Bad DateTime input. Standart DateTime initialized."<<endl;
        (*this)=DateTime();
    }
}
DateTime::DateTime(int __day, int __month, int __year){
    if (check(__year, __month, __day, 0, 0, 0)){
        _year=__year;
        _month=__month;
        _day=__day;
        _hour=0;
        _minute=0;
        _second=0;
    }
    else{
        cerr<<"Bad DateTime input. Standart DateTime initialized."<<endl;
        (*this)=DateTime();
    }
}
DateTime::DateTime(string str){
    int i=0;
    while(str[i]!='.') i++;
    string buf;
    buf=str.substr(0,i+1);
    _day=atoi(buf.c_str());

    int j=i+1;
    while(str[j]!='.') j++;
    buf=str.substr(i+1,j-i);
    _month=atoi(buf.c_str());

    i=j+1;
    while(str[i]!=' ') i++;
    buf=str.substr(j+1,i-j);
    _year=atoi(buf.c_str());

    j=i+1;
    while(str[j]!=':') j++;
    buf=str.substr(i+1,j-i);
    _hour=atoi(buf.c_str());

    i=j+1;
    while(str[i]!=':') i++;
    buf=str.substr(j+1,i-j);
    _minute=atoi(buf.c_str());

    j=i+1;
    while(j<str.size()) j++;
    buf=str.substr(i+1,j-i);
    _second=atoi(buf.c_str());

    if (!check(_year, _month, _day, _hour, _minute, _second)){
        cerr<<"Bad DateTime input. Standart DateTime initialized."<<endl;
        (*this)=DateTime();
    }
}

    /// Checks
bool is_leap_year(int year_){
    bool leap=false;
    if ((year_%4==0 && !year_%100==0) || year_%400==0)
        leap=true;
    return leap;
}
int get_days_in_month(int year_, int month_){
    switch (month_){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
            break;
        case 4: case 6: case 9: case 11:
            return 30;
            break;
        case 2:
            if (is_leap_year(year_)==true)
                return 29;
            if (is_leap_year(year_)==false)
                return 28;
            break;
        default:
            break;
    }
}
bool DateTime::check(int year_, int month_, int day_, int hour_, int minute_, int second_) const{
    bool leap=is_leap_year(year_);
    if (!(month_>=1 && month_<=12))
        return false;
    switch (month_){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if (!(day_>=1 && day_<=31))
                return false;
            break;
        case 4: case 6: case 9: case 11:
            if (!(day_>=1 && day_<=30))
                return false;
            break;
        case 2:
            if (leap==true)
                if (!(day_>=1 && day_<=29))
                    return false;
            if (leap==false)
                if (!(day_>=1 && day_<=28))
                    return false;
            break;
        default:
            break;
    }
    if (!(hour_>=0 && hour_<=23))
        return false;
    if (!(minute_>=0 && minute_<=59))
        return false;
    if (!(second_>=0 && second_<=59))
        return false;
    return true;
}
bool DateTime::check() const{ return check(_year, _month, _day, _hour, _minute, _second); }

    /// Input and output
istream& operator>>(istream& s, DateTime& obj){
    char ch1, ch2, ch3, ch4;
    int day_, month_, year_, hour_, minute_, second_;
    s>>day_>>ch1>>month_>>ch2>>year_>>hour_>>ch3>>minute_>>ch4>>second_;
    if (ch1!='.' || ch2!='.' || !obj.check(year_, month_, day_, hour_, minute_, second_) || ch3!=':' || ch4!=':'){
        s.clear();
        cerr<<"Bad DateTime input. Standart DateTime initialized."<<endl;
        obj=DateTime();
        return s;
    }
    else {
        obj._year=year_;
        obj._month=month_;
        obj._day=day_;
        obj._hour=hour_;
        obj._minute=minute_;
        obj._second=second_;
    }
    return s;
}
ostream& operator<<(ostream& s, const DateTime& obj){
    if (obj.check(obj._year, obj._month, obj._day, obj._hour, obj._minute, obj._second))
        s<<obj._day<<'.'<<obj._month<<'.'<<obj._year<<' '
        <<obj._hour<<':'<<obj._minute<<':'<<obj._second;
    return s;
}

    /// Adders
DateTime& DateTime::addYear(int __year){
    _year+=__year;
    return (*this);
}
DateTime& DateTime::addMonth(int __month){
    if (__month>=0){
        while (__month>12-_month){
            ++_year;
            __month-=12;
        }
        _month+=__month;
        while (!check())
            _day--;
    }
    else {
        __month=_month+__month;
        if (__month<0){
            --_year;
            while (__month<-12){
                --_year;
                __month+=12;
            }
            _month=12+__month;
        }
        else _month=__month;
        while (!check())
            _day--;
    }
    return (*this);
}
DateTime& DateTime::addDay(int __day){
    (*this).addSecond(__day*24*60*60);
    return (*this);
}
DateTime& DateTime::addHour(int __hour){
    (*this).addSecond(__hour*60*60);
    return (*this);
}
DateTime& DateTime::addMinute(int __minute){
    (*this).addSecond(__minute*60);
    return (*this);
}
DateTime& DateTime::addSecond(int __second){
    time_t current=getUnixtime();
    (*this)=DateTime(current+__second);
    return (*this);
}

    /// Special functions
time_t DateTime::getUnixtime() const{
    time_t unixtime=946684800; // 1.1.2000 00:00:00
    int year_=2000;
    if (_year>year_){
        while (year_!=_year){
            if (is_leap_year(year_))
                unixtime+=366*24*60*60;
            else
                unixtime+=365*24*60*60;
            year_++;
        }
    }
    else {
        while (year_!=_year){
            if (is_leap_year(year_-1))
                unixtime-=366*24*60*60;
            else
                unixtime-=365*24*60*60;
            year_--;
        }
    }
    for (int i=_month-1; i>=1; i--)
    unixtime+=get_days_in_month(_year,i)*24*60*60;
    unixtime+=24*60*60*(_day-1);
    unixtime+=60*60*(_hour);
    unixtime+=60*(_minute);
    unixtime+=_second;
    return unixtime;
}
int DateTime::getDayOfWeek() const{
    // 3.1.2000 is Monday
    int res=1;
    TimeSpan diff=DateTime(_day, _month, _year)-DateTime(3, 1, 2000);
    if (diff<0){
        diff=-diff;
        res=(7*(diff.getDay()/7+1)-diff.getDay())%7+1;
    }
    else
        res=diff.getDay()%7+1;
    return res;
}
    /// Comparatives
bool DateTime::operator<(const DateTime& right) const{
    if (_year<right._year)
        return true;
    else if (_year==right._year){
        if (_month<right._month)
            return true;
        else if (_month==right._month){
            if (_day<right._day)
                return true;
            else if (_day==right._day){
                if (_hour<right._hour)
                    return true;
                else if (_hour==right._hour){
                    if (_minute<right._minute)
                        return true;
                    else if (_minute==right._minute){
                        if (_second<right._second)
                            return true;
                    }
                }
            }
        }
    }
    return false;
}
bool DateTime::operator==(const DateTime& right) const{
    if (_year==right._year)
        if (_month==right._month)
            if (_day==right._day)
                if (_hour==right._hour)
                    if (_minute==right._minute)
                        if (_second==right._second)
                            return true;
    return false;
}
    /// Ariphmetics
DateTime& DateTime::operator=(const DateTime& copy){
    _year=copy._year;
    _month=copy._month;
    _day=copy._day;
    _hour=copy._hour;
    _minute=copy._minute;
    _second=copy._second;
    return (*this);
}
DateTime DateTime::operator+(const TimeSpan& diff){
    time_t first=getUnixtime();
    return (DateTime(first+diff.getSecond()));
}
TimeSpan operator-(const DateTime& left, const DateTime& right){
    time_t first=left.getUnixtime();
    time_t second=right.getUnixtime();
    return (TimeSpan(first-second));
}
DateTime DateTime::operator-(const TimeSpan& diff){
    time_t first=getUnixtime();
    return (DateTime(first-diff.getSecond()));
}

DateTime::operator string() const{
    string res="";
    itoa_with_concat(_day, res);
    res+=".";
    itoa_with_concat(_month, res);
    res+=".";
    itoa_with_concat(_year, res);
    res+=" ";
    itoa_with_concat(_hour, res);
    res+=":";
    itoa_with_concat(_minute, res);
    res+=":";
    itoa_with_concat(_second, res);
    return res;
}
void reverse(string& s){
    int i, j;
    char c;
    for (i=0, j=s.length()-1; i<j; i++, j--) {
        c=s[i];
        s[i]=s[j];
        s[j]=c;
    }
}
void itoa(int n, string& s){
    int i, sign;
    if ((sign=n) < 0)
        n=-n;
    i=0;
    do {
        s[i++]=n%10+'0';
    } while ((n/=10)>0);
    if (sign<0)
        s[i++]='-';
    s[i]='\0';
    reverse(s);
}
void itoa_with_concat(int n, string& s){
    string str;
    str.resize(6);
    itoa(n, str);
    s=s+str;
}

#endif // DATETIME_H_INCLUDED
