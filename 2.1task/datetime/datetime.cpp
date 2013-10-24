#include <iostream>
#include "datetime.h"
using namespace std;
int main()
{
    DateTime d1;
    DateTime d2(d1);
    DateTime d3(time(0));
    DateTime d4(2, 2, 2012, 10, 30, 30);
    DateTime d5(12, 11, 2013);
    string str;
    DateTime d8;
    cin>>d8;
    cout<<d8<<endl;
    cout<<d1<<endl<<d2<<endl<<d3<<endl<<d4<<endl<<d5<<endl;
    cout<<d4.getYear()<<" "<<d4.getMonth()<<" "<<d4.getDay()<<" "<<d4.getHour()<<" "<<d4.getMinute()<<" "<<d4.getSecond()<<endl;
    cin>>d1;
    cout<<d1<<endl;
    DateTime d7=DateTime::getCurrentDateTime();
    cout<<d7<<endl;
    cout<<d7.getDayOfWeek()<<endl;
    cout<<(d4<d5)<<endl;
    cout<<(d7==d3)<<endl;
    TimeSpan ts=d5-d4;
    cout<<(d7+ts)<<endl;

}
