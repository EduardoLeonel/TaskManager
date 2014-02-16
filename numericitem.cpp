#include "numericitem.h"


bool NumericItem::operator <(QTableWidgetItem *other){
    return text().toInt() < other->text().toInt();
}


bool NumericItem::operator >(QTableWidgetItem *other){
    return text().toInt() > other->text().toInt();
}
