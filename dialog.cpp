#include "dialog.h"

#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QDebug>
#include <QPixmap>

Dialog::Dialog(QWidget *parent) 
    : QDialog(parent), scene(new QGraphicsScene), m_string("Hello world!")
{
    config();
}

Dialog::Dialog(QString txt, QWidget *parent)
    : QDialog(parent), scene(new QGraphicsScene), m_string(txt)
{
    config();
}

Dialog::Dialog(const char *txt, QWidget *parent)
    : QDialog(parent), scene(new QGraphicsScene), m_string(QString(txt))
{
    config();
}

Dialog::~Dialog()
{
    m_timer.stop();
    delete scene;
}

void Dialog::config()
{
    this->resize(840,480);
    m_speed=2;
    
    
    
    m_pen.setColor(Qt::black);
    m_brush.setColor(Qt::cyan);
    m_brush.setStyle(Qt::SolidPattern);
    m_background.setColor(Qt::white);
    m_background.setStyle(Qt::SolidPattern);
    m_font=QFont("Times",32,57,false);
    
    speedLabel.setParent(this);
    speedLabel.setText("Speed:");
    speedLabel.setGeometry(660,20,160,20);
    
    speedSlider.setParent(this);
    speedSlider.setOrientation(Qt::Horizontal);
    speedSlider.setGeometry(660,speedLabel.y()+speedLabel.height()+10,160,20);
    speedSlider.setRange(1,50);
    connect(&speedSlider,SIGNAL(valueChanged(int)),this,SLOT(changeSpeed(int)));
    
    
    textLabel.setParent(this);
    textLabel.setText("Text:");
    textLabel.setGeometry(660,speedSlider.y()+speedSlider.height()+20,160,20);
    
    textBox.setParent(this);
    textBox.setText(m_string);
    textBox.setGeometry(660,textLabel.y()+textLabel.height()+10,160,60);
    connect(&textBox,SIGNAL(textChanged()),this,SLOT(changeText()));
    
    
    fontLabel.setParent(this);
    fontLabel.setText("Font:");
    fontLabel.setGeometry(660,textBox.y()+textBox.height()+20,160,20);
    
    fontButton.setParent(this);
    fontButton.setText("Set Font");
    fontButton.setGeometry(660,fontLabel.y()+fontLabel.height()+10,160,20);
    connect(&fontButton,SIGNAL(clicked()),this,SLOT(changeFont()));
    
    
    penLabel.setParent(this);
    penLabel.setText("Pen Color:");
    penLabel.setGeometry(660,fontButton.y()+fontButton.height()+20,60,20);
    
    penButton.setParent(this);
    penButton.setGeometry(penLabel.x()+penLabel.width()+10,penLabel.y(),20,20);
    QPixmap penColor(16,16); penColor.fill(m_pen.color());
    penButton.setIcon(penColor);
    connect(&penButton,SIGNAL(clicked()),this,SLOT(changePen()));
    
    
    brushLabel.setParent(this);
    brushLabel.setText("Brush Color:");
    brushLabel.setGeometry(660,penLabel.y()+penLabel.height()+20,penLabel.width(),20);
    
    brushButton.setParent(this);
    brushButton.setGeometry(brushLabel.x()+brushLabel.width()+10,brushLabel.y(),20,20);
    QPixmap brushColor(16,16); brushColor.fill(m_brush.color());
    brushButton.setIcon(brushColor);
    connect(&brushButton,SIGNAL(clicked()),this,SLOT(changeBrush()));
    
    
    backgroundLabel.setParent(this);
    backgroundLabel.setText("Background:");
    backgroundLabel.setGeometry(660,brushLabel.y()+brushLabel.height()+20,brushLabel.width(),20);
    
    backgroundButton.setParent(this);
    backgroundButton.setGeometry(backgroundLabel.x()+backgroundLabel.width()+10,backgroundLabel.y(),20,20);
    QPixmap backgroundColor(16,16); backgroundColor.fill(m_background.color());
    backgroundButton.setIcon(backgroundColor);
    connect(&backgroundButton,SIGNAL(clicked()),this,SLOT(changeBackground()));
    
    
    
    welcomeLabel.setParent(this);
    welcomeLabel.setText(QString("Cảm ơn cậu đã sử dụng cái\n"
                                 "app xàm xí này của tớ :))\n"
                                 "Facebook: fb.me/ktnuh\n"
                                 "Time: 11h31 - 7h55 30/1/2023"));
    welcomeLabel.setGeometry(660,400,160,70);
    
    
    
    graphicsView.setParent(this);
    graphicsView.setGeometry(0,0,640,480);
    graphicsView.setFrameShape(QFrame::NoFrame);
    graphicsView.setResizeAnchor(QGraphicsView::NoAnchor);
    graphicsView.setDragMode(QGraphicsView::NoDrag);
    
    
    graphicsView.setScene(scene);
    scene->setSceneRect(0,-240,640,480);
    

    
    updateText();
    m_text.setPos(0,m_text.boundingRect().bottomRight().y()/-2);
    
    scene->addItem(&m_text);
    scene->addItem(&m_text2);
//    scene->addRect(QRectF(0,0,50,50),QPen(Qt::black),Qt::lightGray);
    
//    m_timer.setTimerType(Qt::PreciseTimer);
    m_timer.start(20);
    
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(slide()));
}

void Dialog::updateText()
{
    qDebug() << m_brush << endl;
    
    m_text.setText(m_string);
    m_text.setFont(m_font);
    m_text.setBrush(m_brush);
    m_text.setPen(m_pen);
    
    m_text2.setText(m_string);
    m_text2.setFont(m_font);
    m_text2.setBrush(m_brush);
    m_text2.setPen(m_pen);
}

void Dialog::slide()
{
    int width=graphicsView.width();
    int twidth=m_text.boundingRect().width();
    m_text.setPos(m_text.x()+m_speed,m_text.boundingRect().bottomRight().y()/-2);
    
    if(m_text.x()>width*2-twidth) m_text.setX(-twidth);
    
    if(m_text.x()>=width-twidth) m_text2.setPos(m_text.x()-width,m_text.y());
    else if(m_text.x()>=-twidth) m_text2.setPos(m_text.x()+width,m_text.y());
}

void Dialog::changeSpeed(int speed)
{
    m_speed=speed;
}

void Dialog::changeText()
{
    m_string=textBox.toPlainText();
    updateText();
}

void Dialog::changeFont()
{
    bool ok;
    QFont font=QFontDialog::getFont(&ok,m_font,this);
    if(ok)
    {
        m_font=font;
        updateText();
    }
}

void Dialog::changePen()
{
    QColor color=QColorDialog::getColor(m_pen.color(),this);
    if(color!=QColor::Invalid)
    {
        m_pen.setColor(color);
        QPixmap penColor(16,16); penColor.fill(m_pen.color());
        penButton.setIcon(penColor);
        updateText();
    }
}

void Dialog::changeBrush()
{
    QColor color=QColorDialog::getColor(m_brush.color(),this);
    if(color!=QColor::Invalid)
    {
        m_brush.setColor(color);
        QPixmap brushColor(16,16); brushColor.fill(m_brush.color());
        brushButton.setIcon(brushColor);
        updateText();
    }
}

void Dialog::changeBackground()
{
    QColor color=QColorDialog::getColor(m_background.color(),this);
    if(color!=QColor::Invalid)
    {
        m_background.setColor(color);
        QPixmap backgroundColor(16,16); backgroundColor.fill(m_background.color());
        backgroundButton.setIcon(backgroundColor);
        scene->setBackgroundBrush(m_background);
    }
}



















