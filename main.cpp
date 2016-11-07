#include "controle.h" //on include la classe Controle, Modèle et MainWindow
#include "modele.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w; //on crée un objet de la class MainWindow
    //Modele m;
    //Controle (&m,w); //Dans le modèle MVC, la classe controle prend en paramètre modèle par référence et une MainWindow
    w.show();

    return a.exec();
}
