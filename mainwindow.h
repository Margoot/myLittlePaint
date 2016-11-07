#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controle.h"
#include <QMainWindow>
#include <QtWidgets>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QtCore>
#include <QtGui>
#include <QObject>
#include <QString>
#include <QtGlobal>
#include <QPrinter>
#include <QPrintDialog>
#include <QWheelEvent>
#include <QByteArray>

class Canvas; //Certaines fonctions de cette classe font référence à notre scene

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0); //contructeur de la classe avec comme parent une QWidget
    ~MainWindow();
    //void setCanvas(Canvas *canvas) { this->canvas = canvas; } -> MVC non aboutit
    void scale(int delta); //fonction de zoom
    bool getCheckLine() {return checkLine;} //getter pour la ligne
    bool getCheckRect() {return checkRect;} //getter pour le rectangle
    bool getCheckEllipse() {return checkEllipse;} //getter pour le rond
    bool getCheckPen() {return checkPen;} //getter pour la brosse
    bool getCheckErase() {return checkErase;} //getter pour la gomme
    QColor getColor() {return color;} //getter pour la palette de couleur
    int getWidth() {return width;} //getter pour l'épaisseur des traits
    int getWidthErase() {return widthErase;} //getter pour la taille de la gomme

private slots:
    void on_color_clicked(); //slot pour la couleur
    void on_new_3_triggered(); //slot pour créer un nouveau fichier
    void on_save_2_triggered(); //slot pour enregistrer en format PNG
    void on_open_2_triggered(); //slot pour ouvrir un nouveau fichier PNG
    void on_print_2_triggered(); //slot pour imprimer en format PDF
    void on_line_toggled(bool checked); //slot pour tracer une ligne
    void on_rectangle_toggled(bool checked); //slot pour tracer un rectangle
    void on_circle_toggled(bool checked); //slot pour tracer un rond
    void on_pen_toggled(bool checked); // slot pour dessiner librement avec la brosse
    void on_erase_toggled(bool checked); //slot pour la gomme
    void on_help_triggered(); //slot pour le fichier help
    void on_widthErase_valueChanged(int value); //slot pour définir la taille de la gomme
    void on_width_valueChanged(int arg1); //slot pour définir l'épaisseur des traits

private:
    Ui::MainWindow *ui; //création de notre mainwindow avec QtDesigner
    QGraphicsItem *item; // création d'un object item de type QGraphicsItem afin
    Canvas *scene; //création d'un object scene de notre classe canvas
    QImage image;
    bool checkLine;
    bool checkRect;
    bool checkEllipse;
    bool checkPen;
    bool checkErase;
    QColor color;
    int width;
    int widthErase;
};

#endif // MAINWINDOW_H
