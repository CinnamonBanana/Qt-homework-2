#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nodeitem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_menu_open_triggered()
{
    openedFile = QFileDialog::getOpenFileName(this, "Открыть файл...", "", "*.json");
    setWindowTitle(getFileName());
    JSONToData(openedFile);
}

QString MainWindow::getFileName()
{
    return openedFile.mid(openedFile.lastIndexOf("/")+1);
}

int MainWindow::findId(int id)
{
    for (int i=0; i<data.size(); i++) {
        if(id == data.at(i).id)
            return i;
    }
    return -1;
}

void MainWindow::maxLvl(MainWindow::node x, int level)
{
    if(level>maxlevel) maxlevel = level;
    if(x.left!=-1)
    {
        maxLvl(data.at(findId(x.left)), level+1);
    }
    if(x.right!=-1)
    {
        maxLvl(data.at(findId(x.right)), level+1);
    }
}

void MainWindow::paintChildren(MainWindow::node x, int level, int dir=0, int X=0)
{
    NodeItem *item = new NodeItem(x.value);
    int posX=0;
    switch (dir)
    {
        case 1: {posX=X-60*(maxlevel-level+1); break;}
        case 2: {posX=X+60*(maxlevel-level+1); break;}
    }
    item->setX(posX);
    item->setY(60*level);
    if(x.left!=-1)
    {

        paintChildren(data.at(findId(x.left)), level+1, 1, posX);
    }
    if(x.right!=-1)
    {
        paintChildren(data.at(findId(x.right)), level+1, 2, posX);
    }
    if(level>0)
        scene->addLine(X+15, (level-1)*60+15, posX+15, level*60+15);
    scene->addItem(item);
}




void MainWindow::JSONToData(QString fileName)
{
    scene->clear();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "Ошибка!", "Не удалось открыть файл. " + file.errorString());
            return;
        }
    else
    {
        QString val = file.readAll();
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8(), &error);
        qDebug() << "Error: " << error.errorString() << error.offset << error.error;
        if(doc.isArray())
        {
             qDebug() << doc.array() << " " << doc.isArray();
             QJsonArray arr = doc.array();
             for(QJsonValueRef arrItem: arr)
             {
                 int id = arrItem.toObject().toVariantMap()["id"].toInt();
                 int value = arrItem.toObject().toVariantMap()["value"].toInt();
                 int left = arrItem.toObject().toVariantMap()["left"].toInt();
                 int right = arrItem.toObject().toVariantMap()["right"].toInt();
                 node *temp = new node;
                 temp->value=value;
                 temp->id = id;
                 temp->left = left;
                 temp->right = right;
                 if(this->root==nullptr)
                 {
                     root = temp;
                 }
                 data.append(*temp);
             }
        }
    }
    maxLvl(*root,0);
    paintChildren(*root, 0);
}
