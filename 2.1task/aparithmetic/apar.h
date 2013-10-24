#ifndef APAR_H_INCLUDED
#define APAR_H_INCLUDED
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "../vector/myvector.h"
#include <stdexcept>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

using std::max;
using std::exception;
using std::logic_error;

using std::istream;
using std::ostream;

using std::string;
using my::vector;

typedef long long int llint;
const static llint MAX64=1000000000;
const static int KARATSUBA_NUM=60;
int nearest_pow_of_2(int);
int pow_of_2(int);
class LongNum{
private:
    bool sign;
    int amount;
    llint radix;
    vector<llint> digits;
public:
    LongNum() : sign(1), amount(1), radix(MAX64), digits(vector<llint>(1,0)) {}
    LongNum(int value) : sign(1), amount(1), radix(MAX64), digits(vector<llint>(1,value)){}
    LongNum(const LongNum& rhs) : sign(rhs.sign), amount(rhs.amount), radix(rhs.radix), digits(rhs.digits) {}

    friend istream & operator>>(istream&, LongNum&);
    friend ostream & operator<<(ostream&, const LongNum&);

    friend const LongNum operator+(const LongNum&, const LongNum&);
    friend const LongNum operator-(const LongNum&, const LongNum&);
    friend const LongNum operator*(const LongNum&, const LongNum&);
    friend const LongNum operator/(const LongNum&, const LongNum&);
    friend const LongNum operator%(const LongNum&, const LongNum&);
    friend const LongNum operator*(const LongNum&, llint);
    friend const LongNum operator/(const LongNum&, int);
    friend const int operator%(const LongNum&, llint);

    LongNum& operator+=(const LongNum&);
    LongNum& operator-=(const LongNum&);
    LongNum& operator*=(const LongNum&);
    LongNum& operator/=(const LongNum&);
    LongNum& operator*=(llint);
    LongNum& operator/=(int);

    LongNum& operator++();
    LongNum operator++(int);
    LongNum& operator--();
    LongNum operator--(int);
    LongNum operator-() const;
    LongNum operator<<(int) const;
    LongNum operator>>(int) const;
    LongNum operator^(int) const;
    friend LongNum factorial(int);

    bool operator>=(const LongNum&) const;
    bool operator<=(const LongNum&) const;
    bool operator==(const LongNum&) const;
    bool operator!=(const LongNum&) const;
    bool operator>(const LongNum&) const;
    bool operator<(const LongNum&) const;

    operator int() const;
    void fit();
    void resize(int, int const value=0);
};

    ///Input & Output
istream& operator>>(istream& s, LongNum& rhs){
    rhs.digits.resize(2);
    int flag=0;
    string str;
    while (flag==0){
        s>>str;
        if (str[0]=='-'){
            rhs.sign=0;
            str=str.substr(1);
        }
        else
            rhs.sign=1;
        flag=str.size();
    }
    for (int j=0; j<(int)str.size(); j++){
       for (int i=rhs.amount-1; i>=0; i--){
           rhs.digits[i+1] = rhs.digits[i+1] + (rhs.digits[i]*10)/rhs.radix;
           rhs.digits[i] = (rhs.digits[i]*10) % rhs.radix;
       }
       rhs.digits[0]+=((int)str[j]-(int)'0');
       if (rhs.digits[rhs.amount]>0){
            rhs.amount++;
            rhs.digits.resize(rhs.amount+1);
       }
    }
    rhs.fit();
    return s;
}

inline int find_size(int x){
    if (x==0)
        return 1;
    int res=0;
    while(x!=0){ res++; x/=10; }
    return res;
}

ostream& operator<<(ostream& s, const LongNum& rhs){
    if (rhs.sign==0) s<<'-';
    s<<rhs.digits[rhs.amount-1];
    int cnt=find_size(rhs.radix/10);
    for (int i=rhs.amount-2; i>=0; i--){
        int temp=find_size(rhs.digits[i]);
        for (int j=temp; j<cnt; j++)
            s<<'0';
        s<<rhs.digits[i];
    }
    return s;
}


    ///Binary operators (Long & Long)
const LongNum operator+(const LongNum& lhs, const LongNum& rhs){
    if (rhs.sign==0 && lhs.sign==1)     return (lhs-(-rhs));
    if (lhs.sign==0 && rhs.sign==1)     return (rhs-(-lhs));
    if (lhs.sign==0 && rhs.sign==0)     return -((-lhs)+(-rhs));

    LongNum res;
    res.resize((max(lhs.amount, rhs.amount)+1));
    int reserve=0;
    for (int i=0; i<res.amount; i++){
        llint lea=0, rea=0;
        if (i<lhs.amount)  lea=lhs.digits[i]; else lea=0;
        if (i<rhs.amount)  rea=rhs.digits[i]; else rea=0;
        res.digits[i]=lea+rea+reserve;
        if (res.digits[i]>res.radix-1){
            reserve=1;
            res.digits[i]-=res.radix;
        }
        else reserve=0;
    }
    res.fit();
    return res;
}

const LongNum operator-(const LongNum& lhs, const LongNum& rhs){
    if (rhs==lhs)                       return (LongNum());
    if (rhs.sign==0 && lhs.sign==1)     return (lhs+(-rhs));
    if (lhs.sign==0 && rhs.sign==1)     return -(rhs+(-lhs));
    if (lhs.sign==0 && rhs.sign==0)     return -((-lhs)-(-rhs));
    if (rhs>lhs)                        return (-(rhs-lhs));

    LongNum res;
    res.resize(lhs.amount);
    int taken=0;
    for (int i=0; i<res.amount; i++){
        llint lea=lhs.digits[i];
        llint rea=0;
        if (i<rhs.amount) rea=rhs.digits[i];
        if ((lea-rea-taken)>=0){
            res.digits[i]=lea-rea-taken;
            taken=0;
        }
        else {
            res.digits[i]=res.radix+lea-rea-taken;
            taken=1;
        }
    }
    res.fit();
    return res;
}

const LongNum operator*(const LongNum& lhs, const LongNum& rhs){
    LongNum res;
    res=(((lhs+rhs)^2)-((lhs-rhs)^2))/4;
    if (lhs.sign!=rhs.sign)
        res.sign=0;
    return res;
}

const LongNum operator/(const LongNum& lhs, const LongNum& rhs){
    try{
        if (rhs!=LongNum()){
            if (lhs.sign!=rhs.sign){
                if (lhs.sign==0)    return (-((-lhs)/rhs));
                else                return (-(lhs/(-rhs)));
            }
            if (lhs<(rhs<<1)){
                llint l=0;
                llint r=lhs.radix;
                llint m=(r+l)/2;
                LongNum temp;
                while (r-l>1){
                    m=(r+l)/2;
                    temp=rhs*LongNum(m);
                    if (temp==lhs) return LongNum(m);
                    if (temp>lhs) r=m;
                    if (temp<lhs) l=m;
                }
                return (LongNum(l));
            }
            else {
                LongNum res, div, cur=lhs;
                res.resize(lhs.amount-rhs.amount+1);
                for (int i=res.amount-1; i>=0; i--){
                    div=(cur>>i)/rhs;
                    res.digits[i]=(int)div;
                    cur=cur-((rhs*LongNum(res.digits[i]))<<i);
                }
                res.fit();
                return res;
            }
        }
        else throw logic_error("Division by zero");
    }
    catch(logic_error i) { cerr<<i.what()<<endl; return LongNum(); }
}

const LongNum operator%(const LongNum& lhs, const LongNum& rhs){
    return (lhs-(lhs/rhs)*rhs);
}

LongNum& LongNum::operator+=(const LongNum& rhs){
    (*this)=(*this)+rhs;
    return (*this);
}

LongNum& LongNum::operator-=(const LongNum& rhs){
    (*this)=(*this)-rhs;
    return (*this);
}

LongNum& LongNum::operator*=(const LongNum& rhs){
    (*this)=(*this)*rhs;
    return (*this);
}

LongNum& LongNum::operator/=(const LongNum& rhs){
    (*this)=(*this)/rhs;
    return (*this);
}

    ///Binary operators (Long & Int)
const LongNum operator/(const LongNum& lhs, int rhs){
    try{
        if (rhs!=0){
            LongNum res(lhs);
            llint carry=0;
            for (int i=res.amount-1; i>=0; i--){
                llint cur=res.digits[i]+carry*res.radix;
                res.digits[i]=cur/rhs;
                carry= cur%rhs;
            }
            res.fit();
            return res;
        }
        else throw logic_error("Division by zero");
    }
    catch(logic_error i) { cerr<<i.what()<<endl; return LongNum(); }
}

const LongNum operator*(const LongNum& lhs, llint rhs){
    llint reserve=0;
    LongNum res;
    res.resize(lhs.amount+1, 0);
    for (int i=0; i<res.amount; i++){
        llint temp=0;
        if (i<lhs.amount)
            temp=lhs.digits[i]*rhs+reserve;
        else
            temp=reserve;
        reserve=temp/res.radix;
        res.digits[i]=temp%res.radix;
    }
    res.fit();
    return res;
}

const int operator%(const LongNum& lhs, llint rhs){
    if (rhs!=0){
        LongNum res(lhs);
        llint carry=0;
        for (int i=res.amount-1; i>=0; i--){
            int cur=res.digits[i]+carry*res.radix;
            res.digits[i]=cur/rhs;
            carry= cur%rhs;
        }
        return carry;
    }
    else return 0;
}

LongNum& LongNum::operator*=(llint rhs){
    (*this)=(*this)*rhs;
    return (*this);
}

LongNum& LongNum::operator/=(int rhs){
    (*this)=(*this)/rhs;
    return (*this);
}


    ///Unary operators
LongNum& LongNum::operator++(){
    if (sign==0) (*this)=-(--(-(*this)));
    else{
        if (++digits[0]==radix){
            digits[0]=0;
            resize(amount+1);
            int reserve=1;
            int i=1;
            while(reserve!=0){
                digits[i]++;
                if (digits[i]==radix){
                    digits[i]=0;
                    reserve=1;
                }
                else reserve=0;
                i++;
            }
            fit();
        }
    }
    return (*this);
}

LongNum& LongNum::operator--(){
    if (sign==0) (*this)=-(++(-(*this)));
    else
        if ((*this)==LongNum())
            (*this)=LongNum(-1);
        else
        if (--digits[0]<0){
            digits[0]=radix-1;
            int taken=1;
            int i=1;
            while(taken!=0){
                digits[i]--;
                if (digits[i]<0){
                    digits[i]=radix-1;
                    taken=1;
                }
                else taken=0;
                i++;
            }
            fit();
        }
    return (*this);
}

LongNum LongNum::operator++(int){
    LongNum temp(*this);
    ++(*this);
    return temp;
}

LongNum LongNum::operator--(int){
    LongNum temp(*this);
    --(*this);
    return temp;
}

LongNum LongNum::operator-() const{
    LongNum n(*this);
    n.sign=!sign;
    if (n==LongNum())
        n.sign=1;
    return n;
}

LongNum LongNum::operator<<(int cnt) const{
    LongNum res(*this);
    if (cnt>0){
        res.digits.resize(res.amount+cnt);
        for (int i=res.amount+cnt-1; i>=cnt; i--)
            res.digits[i]=res.digits[i-cnt];
        for (int i=0; i<cnt; i++)
            res.digits[i]=0;
        res.amount+=cnt;
    }
    if (cnt<0){
        if (-cnt<res.amount){
            for (int i=0; i<res.amount+cnt; i++)
                res.digits[i]=res.digits[i-cnt];
            res.resize(res.amount+cnt, 0);
        }
        else return (LongNum());
    }
    return res;
}

LongNum LongNum::operator>>(int cnt) const{
    return (operator<<(-cnt));
}

int nearest_pow_of_2(int cnt){
    if (cnt==0) return 0;
    int x=1;
    int k=0;
    while(x<=cnt){
        x*=2;
        k++;
    }
    k--;
    return k;
}

int pow_of_2(int cnt){
    int x=1;
    for (int i=0; i<cnt; i++)
        x*=2;
    return x;
}

LongNum LongNum::operator^(int cnt) const{
    if (cnt==0)
        return LongNum(1);
    LongNum res(*this);
    LongNum temp=LongNum(1);
    if (cnt==1)
        return res;
    res.sign=1;
    if (cnt==2){
        if(res.amount>KARATSUBA_NUM){
            LongNum res1;
            res1.amount=(res.amount+1)/2;
            res1.digits.resize(res1.amount);
            for (int i=0; i<res1.amount; i++)
                res1.digits[i]=res.digits[i];

            int m=res.amount/2;
            LongNum res2=res>>(res.amount-m);

            m=((res.amount+1)/2);
            LongNum res1q=(res1^2);
            LongNum res2q=(res2^2);
            res=(res1q)+((((res1+res2)^2)-(res1q)-(res2q))<<m)+((res2q)<<(2*m));
        }
        else if (res.amount<=KARATSUBA_NUM){
            res=LongNum();
            res.resize((*this).amount*2);
            for (int i=0; i<(*this).amount; i++){
                res=res+(((*this)*((*this).digits[i]))<<i);
            }
        }
        res.fit();
        return res;
    }
    int near=0;
    while(near!=1 && cnt!=1 && cnt!=0){
        int near=nearest_pow_of_2(cnt);
        for (int i=0; i<near; i++)
            res=res^2;
        temp=res*temp;
        res=LongNum(*this);
        cnt=cnt-pow_of_2(near);
    }
    if (cnt%2==1)
        temp=temp*res;
    temp.fit();
    return temp;
}

LongNum factorial(int cnt){
    LongNum res=LongNum(1);
    for (int i=1; i<=cnt; i++)
        res*=i;
    return res;
}
    ///Comparatives
bool LongNum::operator>=(const LongNum& rhs) const{
    if ((*this).amount>rhs.amount) return true;
    if ((*this).amount<rhs.amount) return false;
    if ((*this).amount==rhs.amount)
        for (int i=amount-1; i>=0; i--){
            if (digits[i]>rhs.digits[i])
                return true;
            if (digits[i]<rhs.digits[i])
                return false;
        }
    return true;
}

bool LongNum::operator<=(const LongNum& rhs) const{
    if ((*this).amount<rhs.amount) return true;
    if ((*this).amount>rhs.amount) return false;
    if ((*this).amount==rhs.amount)
        for (int i=amount-1; i>=0; i--){
            if (digits[i]<rhs.digits[i])
                return true;
            if (digits[i]>rhs.digits[i])
                return false;
        }
    return true;
}

bool LongNum::operator==(const LongNum& rhs) const{
    if ((*this).amount<rhs.amount) return false;
    if ((*this).amount>rhs.amount) return false;
    if ((*this).amount==rhs.amount)
        for (int i=amount-1; i>=0; i--)
            if (digits[i]!=rhs.digits[i])
                return false;
    return true;
}

bool LongNum::operator!=(const LongNum& rhs) const{
    if (!((*this)==rhs)) return true;
    else return false;
}

bool LongNum::operator<(const LongNum& rhs) const{
    if ((*this)<=rhs && !((*this)==rhs)) return true;
    else return false;
}

bool LongNum::operator>(const LongNum& rhs) const{
    if ((*this)>=rhs && !((*this)==rhs)) return true;
    else return false;
}


    ///Special functions
LongNum::operator int() const{
    return (*this).digits[0];
}

void LongNum::fit(){
    digits.resize(amount);
    while (amount>1 && digits[amount-1]==0){
        digits.pop_back();
        amount--;
    }
    if (digits[0]==0 && amount==1)
        sign=1;
}

void LongNum::resize(int n, int value){
    (*this).amount=n;
    (*this).digits.resize(n, value);
}
#endif // APAR_H_INCLUDED
