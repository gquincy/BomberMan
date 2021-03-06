#include "launchsologame.h"
#include "ui_launchsologame.h"
#include <QMessageBox>
#include <QComboBox>
#include <QDialog>
#include <QFile>
#include <QTextStream>

#include "eltfactory.h"

LaunchSoloGame::LaunchSoloGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LaunchSoloGame)
{

    ui->setupUi(this);
    setWindowTitle(tr("Lancez la partie SOLO!"));

    connect (ui->exit,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->bt_Start,SIGNAL(clicked()),this,SLOT(LancerPartieSolo()));

    FillMap();
    connect(ui->ch_map,SIGNAL(currentIndexChanged(int)),this,SLOT(ChangeMap()));

    ChangeMap();
    connect(ui->diffNovice,SIGNAL(setChecked(bool)),this,SLOT(SetDiff()));
    connect(ui->diffNormal,SIGNAL(setChecked(bool)),this,SLOT(SetDiff()));
    connect(ui->diffVeteran,SIGNAL(setChecked(bool)),this,SLOT(SetDiff()));
   // diffNormal->setChecked(true);

}

LaunchSoloGame::~LaunchSoloGame()
{
    delete ui;

}

//bouton START!
void LaunchSoloGame::LancerPartieSolo()
{
    QMessageBox msg;
    msg.setText("La Partie Démarre!");
    msg.exec();
}

//choisir la MAP
void LaunchSoloGame::FillMap()
{
    ui->ch_map->addItem("Random");//à voir comment faire un random des maps
    ui->ch_map->addItem("Map1");
    ui->ch_map->addItem("Map2");
    ui->ch_map->addItem("Map3");
    ui->ch_map->addItem("Map4");
}

void LaunchSoloGame::ChangeMap()
{
    //TODO: Choisir la Map à charger

    // La map choisie corrrespond à un fichier text...
    // de type boardXXX.txt
    // Remplit avec:
    //
    // IIIIIIIIIIIIIIIIIIIII
    // I    D    I    D    I
    // I                   I
    // I    D    I    D    I
    // IIIIIIIIIIIIIIIIIIIII

    QFile fichier("../Bomberman/maps/board001.txt");

    if (fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux (&fichier);

        QString ligne;

        int lig = 0;

        while(! flux.atEnd())
        {
            ligne = flux.readLine();

            int col = 0;

            foreach (QChar c, ligne)
            {
                EltFactory::Get()->CreateElement('B', lig, col);

                if (c != ' ')
                    EltFactory::Get()->CreateElement(c.toLatin1(), lig, col);

                col++;
            }

            lig++;
        }
    }
}

//choisir la Difficulté
void LaunchSoloGame::SetDiff()
{
    //ui->diffNormal,Clicked(true);
    //ui->diffNovice;
    //ui->diffNormal;
    //ui->diffVeteran;
}


/*
void LaunchSoloGame::on_scrollLevel_destroyed()
{

}
*/
