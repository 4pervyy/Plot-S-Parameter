#ifndef SUPPORTCLASS_H
#define SUPPORTCLASS_H
#include <QString>


class SupportClass{
public:
    QString convertoSiString(double number);
    double correctivAxisY(double number, int procent = 20);
    double convertoMHz(double number);
};


#endif // SUPPORTCLASS_H
