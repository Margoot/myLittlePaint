#ifndef MODELE_H
#define MODELE_H

#include "controle.h"

/*
Je n'ai pas réussi à coder eun modèle parfait MVC du coup j'ai préféré laisser le fichier modèke vide.
La classe modèle serait reliée à la classe Controle. Cette dernière relié à la mainwindow(=view). Cependant,
la classe modèle et view ne doivent surtout pas être reliées ensemble.
*/

class Controle;

class Modele
{
    //Q_OBJECT
public:
    //Modele(QObject *parent=0) {;}

private:
    //Modele* modele;
    //Controle *controle;


signals:

public slots:
};


#endif // MODELE_H
