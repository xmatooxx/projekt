#ifndef CEL_H
#define CEL_H

#include <QObject>
#include<QGraphicsPixmapItem>

class Cel : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Cel();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void mousePressSignal();

};

#endif // CEL_H
