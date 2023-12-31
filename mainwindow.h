#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);

    void Radar_Detection_Display(QPainter *painter);
    void Group_Box_Coordinates(int *X1Coord, int *Y1Coord, int *X2Coord, int *Y2Coord);
    void Draw_The_Rectangle(QPainter *painter, QPen Pen, QBrush Brush,int iX1Coord, int iY1Coord, int iX2Coord, int iY2Coord);
    void Draw_The_Circle(QPainter *painter, QPen Pen, QBrush Brush, int iX1Coord, int iY1Coord, int iX2Coord, int iY2Coord);
    void Label_The_Angles(QPainter *painter, QPen Pen, QFont Font, int iCenterX, int iCenterY, int iRadius);
    void Draw_The_AngleLines(QPainter *painter, QPen Pen, int iCenterX, int iCenterY, int iRadius);
    void Draw_The_Line(QPainter *painter, QPen Pen, QPointF StartPoint, QPointF EndPoint);
    void Draw_The_InnerCircles(QPainter *painter, QPen Pen, QBrush Brush, int iCenterX, int iCenterY, int iRadius, int iNoOfCircles);
    void Draw_The_Circle_Float(QPainter *painter, QPen Pen, QBrush Brush, float fXCoord, float fYCoord, float fWidth, float fHeight);

    void Label_The_Frequency(QPainter *painter, QPen Pen, QFont Font, int iCenterX, int iCenterY, int iRadius, int iNoOfCircles);
    void Draw_The_Text(QPainter *painter, QPen Pen, QFont Font, int iXCoord, int iYCoord, QString qString);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
