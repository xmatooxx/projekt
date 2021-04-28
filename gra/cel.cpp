#include "cel.h"
#include <QDebug>

Cel::Cel()
{
    setPixmap(QPixmap(":/cel.png"));
    setScale(0.16);
}

void Cel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mousePressSignal();
}
