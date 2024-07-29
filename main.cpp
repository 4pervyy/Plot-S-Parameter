#include "mainwin.h"

#include <QApplication>

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWin w;
    w.setWindowTitle("Plot S-Parameters");
    w.show();
    return a.exec();
}

/* начальной частоты SENS:FREQ:STAR 100кГЦ до 9ГГц
 * конечной частоты SENS:FREQ:STOP 100кГЦ до 9ГГц
 * Мощность SOUR:POW 15 до -60
 * Число точек SENS:SWE:POIN 1 до 10000
 * Полоса ПЧ SENS:BAND 1 Гц до 1 МГц
 * S тип CALC:PAR:DEF S11
 *
 * SENS:DATA:RAWD?
 * SENS:DATA:CORR?
 *
 * SENS:FREQ:DATA?
 * CALC:DATA:FDAT?
*/
