#ifndef NUMERICITEM_H
#define NUMERICITEM_H

#include <QTableWidgetItem>

class NumericItem : public QTableWidgetItem{
public:
    NumericItem(QString val):QTableWidgetItem(val){}
    bool operator <(QTableWidgetItem *other);
    bool operator >(QTableWidgetItem *other);
};

#endif // NUMERICITEM_H
