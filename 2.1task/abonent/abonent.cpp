#include "abonent.h"

int main()
{
    Abonent a("Who", 2, 3000);
    cout<<a<<endl;
    Call c1(30890, (string)"2.2.2012 4:4:4", 500);
    Call c2(31211, (string)"2.2.2010 4:4:4", 400);
    Call c3(21652, (string)"2.2.2008 4:4:4", 300);
    for(int i=0; i<3; i++){
        a.addCall(c1);
        a.addCall(c2);
        a.addCall(c3);
        a.showHistory();
        cout<<endl;
        a.showHistoryFromNumber(30890);
        cout<<endl;
        a.showHistoryInTimeDuration((string)"1.1.2010 7:7:7", (string)"8.8.2011 9:9:9");
        cout<<endl;
        cout<<a.getBalance()<<endl;
    }
}
