#include "supportclass.h"


QString SupportClass::convertoSiString(double number)
{
    if(number < 1e3){
        return QString::number(number);
    }else if (number/1e3 < 1e3) {
        return QString::number(number/1e3)+"к";
    }else if (number/1e6 < 1e3 ){
        return QString::number(number/1e6)+"М";
    }else {
        return QString::number(number/1e9)+"Г";
    }
}

double SupportClass::correctivAxisY(double number, int procent)
{
    return number + ((number * procent)/100);
}
double SupportClass::convertoMHz(double number)
{
    return number/1e6;
}
