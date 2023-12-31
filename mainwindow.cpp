#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->obj_grpbox_radar->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    Radar_Detection_Display(&painter);
}

void MainWindow::Radar_Detection_Display(QPainter *painter)
{

    int iCenterX = 0, iCenterY = 0, iRadius = 0, iX1Coord = 0, iX2Coord = 0, iOuterCircleRadius = 0,
        iY1Coord = 0, iY2Coord = 0;

    QPen BluePen(QColor(0, 0, 40));
    QPen GreenPen(QColor(0, 200, 0));

    QBrush BlackBrush(QColor(0,0,0));
    QBrush NullBrush(Qt::NoBrush);

    QFont HelveticaFont;
    HelveticaFont.setFamily("Helvetica");
    HelveticaFont.setPointSize(7);

    QFont SmallVerdanaFont;
    SmallVerdanaFont.setFamily("Arial");
    SmallVerdanaFont.setPointSize(4);


    painter->setRenderHint(QPainter::Antialiasing, true);

    /**********         Get Group Box Coordinates and Get X1, Y1, X2, Y2 Coordinates          **********/
    Group_Box_Coordinates(&iX1Coord, &iY1Coord, &iX2Coord, &iY2Coord);


    /**********         Draw the Rectangle Using Blue Pen and Black Brush                    **********/
    Draw_The_Rectangle(painter, BluePen, BlackBrush, iX1Coord, iY1Coord, iX2Coord, iY2Coord);

    /**********        Calculate CenterX, CenterY, Radius Of the Rectangle                   **********/
    iCenterX = (iX1Coord + iX2Coord)/ 2;
    iCenterY = (iY1Coord + iY2Coord) / 2;
    iRadius  = (iX2Coord - iX1Coord) / 2;

    /**********                 Draw the Outer Circle                                        **********/
    Draw_The_Circle(painter, GreenPen, NullBrush, iX1Coord + 50, iY1Coord + 50, iX2Coord - 50, iY2Coord - 50);
    iOuterCircleRadius = (iX2Coord - iX1Coord - (2*50)) / 2;

    /**********                  Label the Frequency                                          **********/
    Label_The_Angles(painter, GreenPen, HelveticaFont, iCenterX, iCenterY, iRadius - 20);

    /**********                  Draw the angle lines                                         **********/
    Draw_The_AngleLines(painter, GreenPen, iCenterX, iCenterY, iOuterCircleRadius);

    /**********                 Draw the inner circle                                        **********/
    Draw_The_InnerCircles(painter, GreenPen, NullBrush, iCenterX, iCenterY, iOuterCircleRadius, 9);

   /**********                  label the frequency                                          **********/
    Label_The_Frequency(painter, GreenPen, SmallVerdanaFont, iCenterX, iCenterY, iOuterCircleRadius, 9);


}


void MainWindow:: Group_Box_Coordinates(int *out_X1Coord, int *out_Y1Coord, int *out_X2Coord, int *out_Y2Coord)
{
    int iWidth = 0, iHeight = 0, iXCoord = 0, iYCoord = 0, iAlterWidth = 0;
    QRect QGroupBox = ui->obj_grpbox_radar->geometry();

    iXCoord = QGroupBox.left();
    iYCoord = QGroupBox.top();

    iWidth = QGroupBox.width();
    iHeight = QGroupBox.height();

    if(iWidth == iHeight)
    {
        *out_X1Coord = iXCoord + 20;
        *out_Y1Coord = iYCoord + 20;
        *out_X2Coord = (iXCoord + iWidth) - 20;
        *out_Y2Coord = (iYCoord + iHeight) - 20;
    }
    else
    {
        iAlterWidth = qMin(iWidth, iHeight);

        *out_X1Coord = iXCoord + ((iWidth- iAlterWidth)/2);
        *out_Y1Coord = iYCoord + (iHeight - iAlterWidth)/2;

        *out_X2Coord = *out_X1Coord + iAlterWidth;
        *out_Y2Coord = *out_Y1Coord + iAlterWidth;


    }


}

void MainWindow :: Draw_The_Rectangle(QPainter *painter, QPen Pen, QBrush Brush, int iX1Coord, int iY1Coord, int iX2Coord, int iY2Coord)
{
    painter->setPen(Pen);
    painter->setBrush(Brush);
    painter->drawRect(iX1Coord, iY1Coord, iX2Coord - iX1Coord, iY2Coord - iY1Coord);

}

void MainWindow :: Draw_The_Circle(QPainter *painter, QPen Pen, QBrush Brush, int iX1Coord, int iY1Coord, int iX2Coord, int iY2Coord)
{
    painter->setPen(Pen);
    painter->setBrush(Brush);
    painter->drawEllipse(iX1Coord, iY1Coord, iX2Coord - iX1Coord, iY2Coord - iY1Coord);
}

void MainWindow :: Label_The_Angles(QPainter *painter, QPen Pen,  QFont Font, int iCenterX, int iCenterY, int iRadius)
{
    int iAngleIncrement = 0, iAngle = 0, iPosX = 0, iPosY = 0;
    double dRadians = 0;
    iAngle = 90;

    painter->setPen(Pen);
    painter->setFont(Font);

    for(iAngleIncrement = 0; iAngleIncrement < 360; iAngleIncrement = (iAngleIncrement + 10))
    {
        dRadians = (iAngleIncrement * 3.14) / 180.0;

        iPosX = (iCenterX - 5) + (int) ((iRadius) *  cos(dRadians));
        iPosY = (iCenterY)  + (int) ((iRadius) * sin(dRadians));

        QString QAngle =  QString::number(iAngle%360);
        painter->drawText(iPosX, iPosY, QAngle);

        iAngle += 10;

    }
}

void MainWindow :: Draw_The_AngleLines(QPainter *painter, QPen Pen, int iCenterX, int iCenterY, int iRadius)
{

    int iAngleIncrement = 0, iLine = 10;

    QPointF StartPoint, EndPoint;
    double dRadians = 0;

    painter->setPen(Pen);


    for(iAngleIncrement = 0; iAngleIncrement < 360; iAngleIncrement++)
    {
        dRadians = (iAngleIncrement * 3.14) / 180.0;

        if(iAngleIncrement % 10 == 0)
        {
            iLine = 15;
        }
        else
        {
            iLine = 10;
        }

        /*****              Starting Point of a Line                *****/
        StartPoint.setX((iCenterX) +  ((iRadius + 2) *  cos(dRadians)));
        StartPoint.setY((iCenterY)  +  ((iRadius + 2) * sin(dRadians)));

        /******              Ending Point of a Line                 *****/
        EndPoint.setX((iCenterX) +  ((iRadius + iLine) *  cos(dRadians)));
        EndPoint.setY( (iCenterY)  +  ((iRadius + iLine) * sin(dRadians)));

        /****          Draw the line using StartPoint , EndPoint    *****/
        Draw_The_Line(painter, Pen, StartPoint, EndPoint);


    }

}

 void MainWindow :: Draw_The_Line(QPainter *painter, QPen Pen, QPointF StartPoint, QPointF EndPoint)
{
     painter->setPen(Pen);

     painter->drawLine(StartPoint, EndPoint);
 }

void  MainWindow :: Draw_The_InnerCircles(QPainter *painter, QPen Pen, QBrush Brush, int iCenterX, int iCenterY, int iRadius, int iNoOfCircles)
{
    int iCircleIncrement  = 0;
    float fPerRadius = 0.0f, fRadius = 0.0f;

    fPerRadius = (iRadius / (float) (iNoOfCircles+1));

    for(iCircleIncrement = 1; iCircleIncrement < 10; iCircleIncrement++)
    {
        fRadius = (fPerRadius * iCircleIncrement);
        QRectF RectCircle(iCenterX - fRadius, iCenterY - fRadius,  (2 * fRadius) , (2 * fRadius));
        Draw_The_Circle_Float(painter, Pen, Brush, RectCircle.x(), RectCircle.y(), RectCircle.width(), RectCircle.height());
    }

}


void MainWindow :: Draw_The_Circle_Float(QPainter *painter, QPen Pen, QBrush Brush, float fXCoord, float fYCoord, float fWidth, float fHeight)
{
    painter->setPen(Pen);
    painter->setBrush(Brush);

    painter->drawEllipse(fXCoord, fYCoord, fWidth, fHeight);
}

void  MainWindow ::  Label_The_Frequency(QPainter *painter, QPen Pen, QFont Font, int iCenterX, int iCenterY, int iRadius, int iNoOfCircles)
{


    int iCircleIncrement  = 0, iFreQuency = 0;
    float fPerRadius = 0.0f, fRadius = 0.0f;

    iFreQuency = 1000;
    QString qFrequency = 0;

    fPerRadius = (iRadius / (float) (iNoOfCircles+1));

    for(iCircleIncrement = 2; iCircleIncrement <=10; iCircleIncrement++)
    {
        fRadius = (fPerRadius * iCircleIncrement);

        qFrequency = QString::number(iFreQuency);

        Draw_The_Text(painter, Pen, Font, (iCenterX-fRadius + 1), iCenterY, qFrequency);
        Draw_The_Text(painter, Pen, Font, (iCenterX + fRadius - fPerRadius + 1), iCenterY, qFrequency);

        iFreQuency += 1000;


    }

}

void MainWindow :: Draw_The_Text(QPainter *painter, QPen Pen, QFont Font, int iXCoord, int iYCoord, QString qString)
{
    painter->setPen(Pen);
    painter->setFont(Font);

    painter->drawText(iXCoord, iYCoord, qString);
}
