#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QTextItem>
#include <QListWidgetItem>
#include <string>
#include <string.h>
#include <stack>
#include <cmath>
#include <ctype.h>
#include <algorithm>
#include <QColor>
#include <QBrush>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cctype>
#include <random>

struct cord{
    double x, y;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    void GenerateFractal();
    void rec(cord, double, QColor, QColor, QColor, QColor, QImage*);
    QColor lu, ru, ld, rd;
};
#endif // MAINWINDOW_H
