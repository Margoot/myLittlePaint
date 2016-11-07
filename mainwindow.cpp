#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controle.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  /* constructeur de notre MainWindow qui a comme parent une QMainWindow et
  une ui afin d'utiliser qt designer */
{
    ui->setupUi(this); //installation de notre ui
    scene = new Canvas(ui->graphicsView); // création d'une nouvelle scene qui sera définit dans notre graphicsView
    ui->graphicsView->setScene(scene); // mise en place de cette scene dans notre graphicsView avec setScene();
    scene->setWindow(this); //mise en place de notre scene dans la MainWindow
    scene->setSceneRect(ui->graphicsView->rect()); // mise en forme de notre zone de dessin (rectangle)
    //initalisation des variables toggle, des tailles et des couleurs
    checkLine=false;
    checkRect=false;
    checkEllipse=false;
    checkPen=false;
    checkErase=false;
    width = 1;
    color = Qt::black;
    widthErase = 4;

}

MainWindow::~MainWindow() //destructeur de notre MainWindow et donc de notre ui
{
    delete ui;
}

void MainWindow::on_color_clicked() //slot pour la couleur
{
    /* ouverture d'une fenetre de dialogue afin que l'utilisateur puisse choisir sa couleur */
    color = QColorDialog::getColor(Qt::white,this);
}

void MainWindow::on_new_3_triggered() //slot pour créer un nouveau fichier PNG
{
    //demande à l'utilisateur s'il veut enregistrer son dessin déjà existant*/
    int reponse = QMessageBox :: question (this,"Enregistrer", "Voulez-vous enregistrer votre oeuvre ?",
                                           QMessageBox::No|QMessageBox::Yes);
    if(reponse==QMessageBox::Yes) // si la réponse est oui
    {
        on_save_2_triggered(); //on lance la fonction de sauvegarde
        QMessageBox::information(this, "save", "sauvegardé ! "); //un message apparait
        // on crée une nouvelle scene rectangulaire qui se trouve dans notre graphicsView
        scene = new Canvas(ui->graphicsView);
        ui->graphicsView->setScene(scene);
        scene->setWindow(this);
        scene->setSceneRect(ui->graphicsView->rect());
    }
    else if (reponse==QMessageBox::No) //si la réponse est non
    {
        // on crée directement une nouvelle scene
        scene = new Canvas(ui->graphicsView);
        ui->graphicsView->setScene(scene);
        scene->setWindow(this);
        scene->setSceneRect(ui->graphicsView->rect());
    }

}

void MainWindow::on_save_2_triggered() //slot pour enregistrer un dessin en format PNG
{
    // une boite de dialogue apparait afin de saisir le nom et l'emplacement souhaité du fichier à enregistrer
    QString fileName = QFileDialog::getSaveFileName(this, "Sauverger sous", "", "Image (*.png)");
    //Nous definissons une pixmap qui va prendre la globalité de l'image, une sorte de screeshot de notre image PNG
    QPixmap pixMap = QPixmap::grabWidget(ui->graphicsView);
    //on enregistre cette pixmap sous le nom et l'emplacement désiré
    pixMap.save(fileName);
}

void MainWindow::on_open_2_triggered() // slot pour ouvrir un fichier PNG
{
    // une boite de dialogue apparait pour que l'utilisateur séléctionne son fichier
    QString file = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png)");
    QImage openImage(file); // ouverture de l'image
    if (openImage.load(file)) // si l'image est ouverte
    {
        /*nous créons une pixmapitem. Cette pixmapitem sera notre image que l'on souhaitait
        ouvrir dans notre scene ; nous l'ajoutons grâce à la fontion addPixMap.
  scaledToWidth permet de donner une taille par défaut*/

         QGraphicsPixmapItem* pi = scene->addPixmap(QPixmap::fromImage(openImage).scaledToWidth(200));
         /* Ces deux fonctions étaient réalisables avant de créer les fonctions du GraphicsSceneMouseEvent.
         Malheureusement, nous n'avons pas réussi à régler le problème par la suite. */
         pi->setFlag(QGraphicsItem::ItemIsMovable,true); //bouger l'image
         pi->setFlag(QGraphicsItem::ItemIsSelectable,true); //séléctionner l'image
         pi->setPos(qrand()*500/RAND_MAX,qrand()*500/RAND_MAX); //position aléatoire dans la fenetre
     }
}

void MainWindow::scale(int delta) //fonction de zoom
{
    //sert à savoir comment positionner et redimensionner notre scene quand il y a des changements de matrice
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    double scaleFactor = 1.1; //facteur de zoom

    if (delta > 0) // si delta est supérieur à 0 (delta est la position en x et en y)
    {
        ui->graphicsView->scale(scaleFactor, scaleFactor); //zoom vertical
    }
    else
    {
        ui->graphicsView->scale(1/scaleFactor, 1/scaleFactor); //zoom horizontal
    }
}


void MainWindow::on_print_2_triggered() // slot pour imprimer
{
    QPrinter printer(QPrinter::HighResolution); //définition d'une imprimante (haute défintion)

    QPrintDialog printDialog(&printer, this);
    // une fenetre de dialogue va s'ouvrir dans la mainWindow pour demander à l'utilisateur des options d'impression
    if (printDialog.exec() == QDialog::Accepted) { //si l'utilisateur a accepté la printdialog
        QPainter painter(&printer);
        /* nous créons un painter qui prendra en paramètre un pointeur par référence sur printer (notre QPrinter) */
        QRect rect = painter.viewport(); //notre image à imprimer sera de forme rectangulaire
        QSize size = image.size(); //la taille sera celle de l'image
        size.scale(rect.size(), Qt::KeepAspectRatio);
        /*on garde par défaut comme taille de zoom celle de notre scene même si l'image est plus petite. */
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        /* définit les coordonnes du rectangle à imprimer */
        painter.setWindow(image.rect()); //lie l'image avec le rectangle
        painter.drawImage(0, 0, image); //dessine l'image à partir des coordonnées 0,0.
    }
}

void MainWindow::on_pen_toggled(bool checked) //fonction lorsque le bouton crayon est appuyé
{
    if (ui->pen->isChecked()) //si le bouton crayon est appuyé
    {
        getCheckPen(); //getter car checkPen est une variable privée
        checkPen=true;//le bool prend la valeur true
    }
    else
    {
        checkPen=false;
    }
}


void MainWindow::on_line_toggled(bool checked) //bouton ligne
{
    if (ui->line->isChecked()) // si le bouton ligne est appuyé
    {
        getCheckLine(); //getter car checkLine est une varibale privée
        checkLine=true;//le bool prend la valeur true
    }
    else
    {
        checkLine=false;
    }
}


void MainWindow::on_rectangle_toggled(bool checked) //bouton rectangle
{
    if (ui->rectangle->isChecked()) //si le bouton rectangle est appuyé
    {
        getCheckRect(); //getter car checkRect est une variable privée
        checkRect=true;//le bool prend la valeur true
    }
    else
    {
        checkRect=false;
    }
}

void MainWindow::on_circle_toggled(bool checked) // bouton rond
{
    if (ui->circle->isChecked()) //si le bouton rond est appuyé
    {
        getCheckEllipse(); //getter car checkEllipse est une varible privée
        checkEllipse=true; //le bool prend la valeur true
    }
    else
    {
        checkEllipse=false;
    }
}

void MainWindow::on_erase_toggled(bool checked) //bouton gomme
{
    if (ui->erase->isChecked()) // si le bouton est appuyé
    {
        getCheckErase(); // getter car checkErase est une variable privée
        checkErase=true; //le bool prend la valeur true
        qDebug() << checkEllipse;
    }
    else
    {
        checkErase=false;
    }
}
void MainWindow::on_widthErase_valueChanged(int value) //slot pour définir la taille de la gomme
{
    getWidthErase(); //getter car widthErase est une variable privée
    widthErase=value+7; // la valeur entrée par l'utilisateur sera la valeur mise dans la fonction de gomme
}

void MainWindow::on_width_valueChanged(int arg1) // slot pour définir la taille des traits
{
    getWidth(); //getter car width est une variable privée
    width=arg1;// la valeur entrée par l'utilisateur sera la valeur mise dans les fonctions de dessin
}

void MainWindow::on_help_triggered() //slot pour afficher de l'aide à partir du menu Aide
{
    QMessageBox :: information(this,"Aide", "Mylittlepaint est une application pour créer ses propres images PNG. "
                               " Vous avez la possiilité de : "
                                            "dessiner librement à l'aide d'un crayon"
                                            " /tirer un trait, un rond ou un rectangle"
                                            "/gommer "
                                            "/choisir l'épaisseur du trait"
                                            "/choisir la taille de la gomme"
                                            "/zoomer");

}
