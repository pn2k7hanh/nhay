#pragma once
#include <QDialog>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QTextEdit>
#include <QFontDialog>
#include <QColorDialog>
#include <QToolButton>
#include <QPixmap>

class QGraphicsScene;
class QGraphicsSimpleTextItem;

class Dialog : public QDialog
{
    Q_OBJECT
public:
    Dialog(QWidget *parent = nullptr);
    Dialog(QString txt,QWidget *parent = nullptr);
    Dialog(const char *txt,QWidget *parent = nullptr);
    ~Dialog();
    void config();
    void updateText();
private slots:
    void slide();
    void changeSpeed(int speed);
    void changeText();
    void changeFont();
    void changePen();
    void changeBrush();
    void changeBackground();
private:
    QGraphicsScene *scene;
    QGraphicsSimpleTextItem m_text;
    QGraphicsSimpleTextItem m_text2;
    QString m_string;
    QFont m_font;
    QBrush m_brush;
    QPen m_pen;
    QBrush m_background;
    QTimer m_timer;
    QGraphicsView graphicsView;
    
    qint8 m_speed;
    
    QLabel speedLabel;
    QSlider speedSlider;
    
    QLabel textLabel;
    QTextEdit textBox;
    
    QLabel fontLabel;
    QPushButton fontButton;
    
    QLabel penLabel;
    QToolButton penButton;
    
    QLabel brushLabel;
    QToolButton brushButton;
    
    QLabel backgroundLabel;
    QToolButton backgroundButton;
    
    QLabel welcomeLabel;
};





















