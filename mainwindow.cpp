#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <random>
#include <ctime>

using u32    = uint_least32_t;
using engine = std::mt19937;
std::random_device os_seed;
const u32 seed = os_seed();

engine generator( seed );

std::mt19937_64 rund(time(0));

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->gV->setScene(scene);
    GenerateFractal();
    ui->gV->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    ui->gV->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
}


int getRand(int a = 0, int b = 255){
    std::uniform_int_distribution< u32 > distribute( a, b );
    return distribute(generator);
}

QColor midColor(QColor c1, QColor c2){
    return QColor((c1.red() + c2.red()) / 2, (c2.green() + c1.green()) / 2, (c2.blue() + c1.blue()) / 2);
}

QColor randColor(){
    return QColor(rund() % 256, rund() % 256, rund() % 256);
}

QColor plusRand(QColor c, int rnd){
    return QColor((c.red() + rnd) % 256, (c.green() + rnd) % 256, (c.blue() + rnd) % 256);
}

void MainWindow::rec(cord clu, double w, QColor lu, QColor ru, QColor rd, QColor ld, QImage *image){
    if (w <= 0.6)
        return;
    int rnd = ((rund() % 4 + 120) *  w / 440);
    lu = plusRand(lu, rnd);
    ru = plusRand(ru, rnd);
    rd = plusRand(rd, rnd);
    ld = plusRand(ld, rnd);
    //image->setPixelColor(clu.x + width()/2, clu.y + width()/2, lu);
    auto ellipse = scene->addEllipse(clu.x, clu.y, 1, 1);
    //ellipse->setBrush(lu);
    ellipse->setPen(lu);
    //image->setPixelColor(clu.x + w + width()/2, clu.y + width()/2, ru);
    ellipse = scene->addEllipse(clu.x + w, clu.y, 1, 1);
    //ellipse->setBrush(ru);
    ellipse->setPen(ru);
    //image->setPixelColor(clu.x + w + width()/2, clu.y + w + width()/2, rd);
    ellipse = scene->addEllipse(clu.x + w, clu.y + w, 1, 1);
    //ellipse->setBrush(rd);
    ellipse->setPen(rd);
    //image->setPixelColor(clu.x + width()/2, clu.y + w + width()/2, ld);
    ellipse = scene->addEllipse(clu.x, clu.y + w, 1, 1);
    //ellipse->setBrush(ld);
    ellipse->setPen(ld);

    QColor midU = midColor(lu, ru);
    QColor midR = midColor(ru, rd);
    QColor midD = midColor(ld, rd);
    QColor midL = midColor(lu, ld);
    QColor mid = QColor((lu.red() + ru.red() + rd.red() + ld.red()) / 4,
                        (lu.green() + ru.green() + rd.green() + ld.green()) / 4,
                        (lu.blue() + ru.blue() + rd.blue() + ld.blue()) / 4);

    rec(clu, w / 2, lu, midU, mid, midL, image);
    rec(cord{clu.x + w / 2, clu.y}, w / 2, midU, ru, midR, mid, image);
    rec(cord{clu.x + w / 2, clu.y + w / 2}, w / 2, mid, midR, rd, midD, image);
    rec(cord{clu.x, clu.y + w / 2}, w / 2, midL, mid, midD, ld, image);
    return;
}

void MainWindow::GenerateFractal(){
    scene->addLine(0, 0, 1, 1, QColor(256, 256, 256));
    lu = randColor();
    ru = randColor();
    rd = randColor();
    ld = randColor();
    QImage *image = new QImage(width(), height(), QImage::Format_RGB32);
    rec(cord{-420, -420}, 440, lu, ru, rd, ld, image);
    //scene->addPixmap(QPixmap::fromImage(*image));
    //scene->setSceneRect(0, 0, width(), height());
    return;

}



MainWindow::~MainWindow()
{
    delete ui;
}

