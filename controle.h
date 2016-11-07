#ifndef CONTROLE_H
#define CONTROLE_H

#include <controle.h>
#include <mainwindow.h>
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
#include <QFont>

class MainWindow;
/* Cette classe est notre fenêtre principale. La classe Canvas est la scène crée à l'intérieur de
celle ci.
*/


class Canvas : public QGraphicsScene
{
public:
    Canvas(QWidget *parent = 0) :
        QGraphicsScene(parent), mouseArea(false), currentitem(NULL) {}
    // Ce constructeur a comme parent une QGraphicsScene, en effet notre zone de dessin sera une QGraphicsScene

    void setWindow(MainWindow *window) { this->window = window; } // Setter de notre MainWindow
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    /* fonctionalités de notre paint lorsque la souris bouge
    Nous y trouverons les fonctions de dessins de lignes, de ronds, de carrés, etc. */

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    // fonctionnalités de notre paint lorsque le clique gauche de la souris presse

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //fonctionnalités de notre paint lorsque le bouton de la souris est relaché

    void wheelEvent(QGraphicsSceneWheelEvent *event);
    //fonctionnalité de zoom

private:
    bool mouseArea; //variable qui initialise et définit notre zone de dessin
    QPointF firstPoint; //première position de la souris (lorsqu'on clique)
    MainWindow *window; //création d'un objet window de ma MainWindow
    QGraphicsItem *currentitem; //création d'une QGraphicsItem pour définir le chemin en train de se créer
    QGraphicsPathItem *myPath; //chemin pour le tracer d'un trait
};
#endif // CONTROLE_H
