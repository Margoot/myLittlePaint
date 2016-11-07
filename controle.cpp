#include "controle.h"
#include "modele.h"
#include "mainwindow.h"

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event)
/*Cette fonction aura pour but de définir quand est-ce que le clique gauche de la souris est pressé*/
{
    if (event->button() == Qt::LeftButton) //si le bouton gauche est appuyé ...
    {
            qDebug() << event->scenePos(); // test pour voir si notre zone de dessin est reconnue
            firstPoint = event->scenePos(); //première position prise lorsque l'utilisateur clique sur le bouton de la souris
            mouseArea = true; //zone de dessin
            qDebug() << "pressed" << firstPoint; //test pour voir si notre souris est reconnue dans la mouseArea

            if(window->getCheckPen()) //Si le bouton crayon est appuyé ...
            {
                myPath = new QGraphicsPathItem();
                /*myPath sera notre brosse. Nous avons utilisé QGraphicsPathItem
                car nous devons avoir tous les élèments du chemin pour tracer librement des traits avec la brosse.
                myPath sera l'objet de notre chemin */

                myPath->setPen(QPen(window->getColor(), window->getWidth(),
                                    Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                /* Nous utilisons la fonction setPen pour attriuer les caractériques de notre chemin.
                 Celui-ci prendra comme couleur celle défini par l'utlisateur. Notre getter, se trouvant
                 dans la window, nous devons utiliser une syntaxe comme celle-ci.
                 Pareil pour l'épaisseur du trait. Nos bords seront arrondis et joins.*/
                QPainterPath p; //le chemin sera tracé avec notre souris
                p.moveTo(firstPoint); // prendre comme premier point firstPoint
                myPath->setPath(p); //attribuer a myPath le chemin tracé p
                this->addItem(myPath);// ajout du chemin à la scene (d'un point - celui du départ)
            }

            if(window->getCheckErase()) //Si le bouton gomme est appuyé...
            {
            // même fonction que pour myPaint mais pour la gomme
            myPath = new QGraphicsPathItem();
            //on fixe la couleur à 1
            myPath->setPen(QPen(Qt::white, window->getWidthErase(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            QPainterPath p;
            p.moveTo(firstPoint);
            myPath->setPath(p);
            this->addItem(myPath);
            }

    }
}

void Canvas::mouseMoveEvent (QGraphicsSceneMouseEvent *event)
/*Cette fonction aura pour but de définir quand est-ce que le clique est maintenu tout en bougeant la souris*/
{
    if (mouseArea) // si le curseur se trouve dans notre zone de dessin
    {
        /* currentitem est un QGraphicsItem qui prend l'objet dessiné. Si le currentitem est crée (si un dessin est
         réalisé, nous supprimons cet objet. */
            if (currentitem)
                delete currentitem;

            if(window->getCheckPen()) //si le bouton crayon est appuyé ...
            {
                if(myPath)
                {
                    QPainterPath path = myPath->path(); // définition d'un nouveau chemin (quand on bouge la souris)
                    myPath->setPen(QPen(window->getColor(), window->getWidth(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                    firstPoint = event->scenePos();
                    path.lineTo(firstPoint); //dessine une ligne du firstPoint au dernier point (celui quand on relache la souris
                    myPath->setPath(path);//ajout du chemin complet à la scene
                }
            }

            if(window->getCheckLine()) //si le bouton ligne est appuyé
            /* Nous definissons ici notre ligne à l'aide de la fonction addLine qui prend en paramètre un point
qui sera définit par le premier point ainsi que event->scenePos() qui est la position actuelle de la souris.
Noter fonction prend égalament en paramètre un pen qui aura la couleur et la taille entrées par l'utilisateur
Les fonctions de ligne, de rectangle, de rond, sont mises dans cette fonction du mouseEvent pour un côté esthétique.
Nous pouvons ainsi visualiser le rendu avant de relacher le bouton. La forme géométrique n'apparait pas qu'à la
fin lorsque le bouton est relaché */
            {
                currentitem = addLine(QLineF(firstPoint, event->scenePos()),
                              QPen(window->getColor(), window->getWidth(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            }
            if(window->getCheckRect()) //si le bouton rectangle est appuyé
          /* Meme principe que pour la ligne sauf qu'au lieu de prendre un point en paramètre , elle prend un
rectangle définit par sa premiere position et celle actuelle */
            {
                currentitem = addRect(QRectF(firstPoint,event->scenePos()),
                        QPen(window->getColor(), window->getWidth(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            }
            if(window->getCheckEllipse()) //si le bouton rond est appuyé
                /*idem que pour la fonction addRect()*/
            {
                currentitem = addEllipse(QRectF(firstPoint,event->scenePos()),
                            QPen(window->getColor(), window->getWidth(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            }

            if (window->getCheckErase()) //si le bouton gomme est appuyé
            {
                if(myPath) //même fonction que pour myPen mais pour la gomme
                {

                    QPainterPath path = myPath->path();
                    //la couleur du trait sera fixée blanche
                    myPath->setPen(QPen(Qt::white, window->getWidthErase(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                    firstPoint = event->scenePos();
                    path.lineTo(firstPoint);
                    myPath->setPath(path);
                }
            }

    }
}

void Canvas::mouseReleaseEvent (QGraphicsSceneMouseEvent *event)
/*Cette fonction aura pour but de définir quand est-ce que le clique de la souris est relaché*/
{

    if (event->button()==Qt::LeftButton && mouseArea)
        /*si le bouton gauche de la souris est relaché et que le curseur se trouve dans notre zone de dessin */
    {
        if (currentitem) {
            delete currentitem;
            currentitem = NULL;
        }

        if(window->getCheckLine()) //si le bouton de la ligne est appuyé
        {
            addLine(QLineF(firstPoint, event->scenePos()),
                           QPen(window->getColor(), window->getWidth(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }
        if(window->getCheckRect()) //si le bouton rectangle est appuyé
        {
            addRect(QRectF(firstPoint,event->scenePos()),
                    QPen(window->getColor(), window->getWidth(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }
        if(window->getCheckEllipse()) // si le bouton rond est appuyé
        {
            addEllipse(QRectF(firstPoint,event->scenePos()),
                        QPen(window->getColor(), window->getWidth(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }

        mouseArea=false; //notre zone de dessin est mise à false car le bouton est relaché donc plus de dessin possible
    }
}

void Canvas::wheelEvent(QGraphicsSceneWheelEvent *event) // fonction de zoom avec wheelEvent
{
    window->scale(event->delta());
    /* le delta est selon les abscisses et les ordonnées. Scale est la fonction de zoom
     event -> delta() défnit notre x et notre y pour effecteur le zoom */
}

