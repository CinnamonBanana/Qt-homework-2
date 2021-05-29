#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonValue>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_menu_open_triggered();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString openedFile = "";
    QGraphicsScene *scene;
    int maxlevel=0;

    struct node{
        int value;
        int id;
        int left;
        int right;
    };
    QList<node> data;
    node *root=nullptr;
    QString getFileName();
    int findId(int id);
    void maxLvl(node x, int level);
    void paintChildren(node x, int level, int dir, int X);
    void JSONToData(QString fileName);
};
#endif // MAINWINDOW_H
