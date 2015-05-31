#ifndef QGRAPH_H
#define QGRAPH_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QString>

class qgraph : public QWidget
{
    Q_OBJECT
public:
    float cx,cy;
    explicit qgraph(QWidget *parent = 0);
    int lc(int k);
    int gc(float k);
    ~qgraph();
private:
    void paintEvent(QPaintEvent *event);
};

int check(float x, float y);
#endif // QGRAPH_H
