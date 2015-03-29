#include "qgraph.h"

qgraph::qgraph(QWidget *parent) : QWidget(parent)
{
    cx=0;cy=0;
}

int qgraph::lc(int k)
{
   return (k-200)/100;
}

int qgraph::gc(float k)
{
    return (200+k*100);
}

void qgraph::paintEvent(QPaintEvent *event)
{
    QPainter p;
    p.begin(this);
    p.setPen(QPen(Qt::black,1,Qt::SolidLine));
    p.setRenderHint(QPainter::Antialiasing, true);
    p.drawLine(200,0,200,400);
    p.drawLine(0,200,400,200);
    p.drawText(gc(0)-10,gc(0)+10,QString("0"));
    p.drawText(390,gc(0)+10,QString("x"));
    p.drawText(gc(0)-10,10,QString("y"));
    p.drawText(gc(-0.5)+10,gc(0)-10,QString("-0.5"));
    p.drawText(gc(1)-10,gc(0)+10,QString("1"));
    p.drawText(gc(0)-10,gc(-1)+10,QString("1"));
    p.setPen(QPen(Qt::black,2,Qt::SolidLine));
    p.drawEllipse(QPoint(200,200),100,100);
    p.drawLine(gc(-0.5),50,gc(-0.5),350);
    p.setPen(QPen(Qt::red,5,Qt::SolidLine));
    p.drawPoint(gc(cx),gc(-cy));
    p.end();
}

int check(float x, float y)
{
    if((x<-0.5) || ((x*x+y*y)<1))
    {
        return -1;
    }
    else if (((x*x+y*y)==1) || (x==-0.5))
        {
        return 0;
        }
        else return 1;
}

qgraph::~qgraph()
{

}

