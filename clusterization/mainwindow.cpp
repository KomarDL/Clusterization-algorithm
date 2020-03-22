#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QRandomGenerator>
#include <QDebug>
#include <QThread>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , startButton(new QPushButton("Старт"))
    , pointBox(new QSpinBox)
    , kmeans(new QLabel("К-средних"))
    , maxmin(new QLabel("Максимин"))
    , maxminCanvas(new Canvas)
    , kmeansCanvas(new Canvas)
    , maxminModel(new Maxmin)
    , kmeansModel(new KMeans)
    , clusterUpdtimer(new QTimer(this))
    , centroidUpdTimer(new QTimer(this))
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowTitle("Максимин и К-средних");

    configureControlls();
    addLayouts();

    centroidUpdTimer->setSingleShot(true);
    clusterUpdtimer->setSingleShot(true);

    connect(startButton, SIGNAL(clicked()), this, SLOT(startButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startButton_clicked()
{
    QVector<QPoint> points = generatePoints(pointBox->value(),
                                            maxminCanvas->width(),
                                            maxminCanvas->height());

    kmeansModel->setPoints(points);
    maxminModel->setPoints(points);

    maxminModel->start();

    maxminCanvas->reset();
    maxminCanvas->setClusters(maxminModel->getClusters());
    maxminCanvas->setCentroids(maxminModel->getCentroids());
    maxminCanvas->repaint();

    reconnectTimersToMaxmin();
    centroidUpdTimer->start(MAXMIN_DELAY);
}

void MainWindow::updMaxminClusters()
{
    maxminCanvas->setClusters(maxminModel->getClusters());
    maxminCanvas->repaint();

    maxminModel->step();

    centroidUpdTimer->start(MAXMIN_DELAY);
}

void MainWindow::updMaxminCentroids()
{
    maxminCanvas->setCentroids(maxminModel->getCentroids());
    maxminCanvas->repaint();
    if (maxminModel->finished())
    {
        maxminCanvas->setClusters(maxminModel->getClusters());
        maxminCanvas->setCentroids(maxminModel->getCentroids());
        maxminCanvas->update();
        QMessageBox::information(this, "Максимин", "Готово");

        reconnectTimersToKMeans();
        QVector<QPoint> newCentroids = maxminModel->getCentroids(); /*generatePoints(maxminModel->getCentroids().length(),
                                                      kmeansCanvas->width(),
                                                      kmeansCanvas->height());*/
        kmeansModel->setCentroids(newCentroids);
        kmeansModel->start();
        kmeansCanvas->reset();
        kmeansCanvas->setClusters(kmeansModel->getClusters());
        kmeansCanvas->setCentroids(kmeansModel->getCentroids());
        kmeansCanvas->repaint();
        centroidUpdTimer->start(KMEANS_DELAY);
    }
    else
        clusterUpdtimer->start(MAXMIN_DELAY);
}

void MainWindow::updKMeansClusters()
{
    kmeansCanvas->setClusters(kmeansModel->getClusters());
    kmeansCanvas->repaint();

    kmeansModel->step();

    centroidUpdTimer->start(KMEANS_DELAY);
}

void MainWindow::updKMeansCentroids()
{
    kmeansCanvas->setCentroids(kmeansModel->getCentroids());
    kmeansCanvas->repaint();
    if (kmeansModel->finished())
    {
        kmeansCanvas->setCentroids(kmeansModel->getCentroids());
        kmeansCanvas->setClusters(kmeansModel->getClusters());
        kmeansCanvas->update();
        QMessageBox::information(this, "Максимин", "Готово");
    }
    else
        clusterUpdtimer->start(KMEANS_DELAY);
}

void MainWindow::addLayouts()
{
    QGridLayout *mainLayout = new QGridLayout(ui->centralwidget);
    QVBoxLayout *mainVertical = new QVBoxLayout;
    QHBoxLayout *canvases = new QHBoxLayout;
    QHBoxLayout *controlls = new QHBoxLayout;

    mainLayout->addLayout(mainVertical, mainLayout->rowCount(),
                          mainLayout->columnCount(), Qt::AlignJustify);

    mainVertical->addLayout(controlls);
    mainVertical->addLayout(canvases);

    controlls->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    controlls->addWidget(maxmin);
    controlls->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    controlls->addWidget(pointBox);
    controlls->addWidget(startButton);
    controlls->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    controlls->addWidget(kmeans);
    controlls->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    canvases->addWidget(maxminCanvas);
    canvases->addWidget(kmeansCanvas);

}

void MainWindow::configureControlls()
{
    maxminCanvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    maxminCanvas->setFrameShape(QFrame::Box);
    maxminCanvas->setFrameShadow(QFrame::Shadow::Plain);

    kmeansCanvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    kmeansCanvas->setFrameShape(QFrame::Box);
    kmeansCanvas->setFrameShadow(QFrame::Shadow::Plain);

    startButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pointBox->setRange(1000, 250000);
    pointBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pointBox->setWrapping(true);
}

QVector<QPoint> MainWindow::generatePoints(int amount, int xRange, int yRange)
{
    QVector<QPoint> result = QVector<QPoint>(amount);
    for (int i = 0; i < result.length(); ++i)
    {
        result[i].setX(generateFromRange(0, xRange));
        result[i].setY(generateFromRange(0, yRange));
    }
    return  result;
}

int MainWindow::generateFromRange(int begin, int end)
{
    return (QRandomGenerator::global()->generate() % ((end + 1) - begin) + begin);
}

void MainWindow::reconnectTimersToKMeans()
{
    disconnect(clusterUpdtimer, SIGNAL(timeout()), this, SLOT(updMaxminClusters()));
    disconnect(centroidUpdTimer, SIGNAL(timeout()), this, SLOT(updMaxminCentroids()));

    connect(clusterUpdtimer, SIGNAL(timeout()), this, SLOT(updKMeansClusters()));
    connect(centroidUpdTimer, SIGNAL(timeout()), this, SLOT(updKMeansCentroids()));
}

void MainWindow::reconnectTimersToMaxmin()
{
    disconnect(clusterUpdtimer, SIGNAL(timeout()), this, SLOT(updKMeansClusters()));
    disconnect(centroidUpdTimer, SIGNAL(timeout()), this, SLOT(updKMeansCentroids()));

    connect(clusterUpdtimer, SIGNAL(timeout()), this, SLOT(updMaxminClusters()));
    connect(centroidUpdTimer, SIGNAL(timeout()), this, SLOT(updMaxminCentroids()));
}

