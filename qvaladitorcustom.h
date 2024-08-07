#ifndef QVALADITORCUSTOM_H
#define QVALADITORCUSTOM_H
#include <QDoubleValidator>

class ValaditorDoubleCustom: public QDoubleValidator
{
public:
    ValaditorDoubleCustom(QObject *parent = nullptr) : QDoubleValidator(parent) {}

    QValidator::State validate(QString &input, int &pos) const override {
        QValidator::State state = QDoubleValidator::validate(input, pos);

        if (state == QValidator::Acceptable) {
            if (!input.isEmpty()) {
                if (input.back().isLetter()) {
                    return QValidator::Acceptable;
                }

                if (input.back().isDigit() || input.back() == '.') {
                    return QValidator::Acceptable;
                }
            }
        }

        return QValidator::Invalid;
    }
};

#endif // QVALADITORCUSTOM_H
