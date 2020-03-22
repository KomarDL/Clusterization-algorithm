#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QFrame>
#include <QVector>
#include <QPoint>
#include <QTimer>
#include "canvas.h"
#include "maxmin.h"
#include "kmeans.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startButton_clicked();

    void updMaxminClusters();
    void updMaxminCentroids();

    void updKMeansClusters();
    void updKMeansCentroids();

private:
    static constexpr int MAXMIN_DELAY = 500;
    static constexpr int KMEANS_DELAY = MAXMIN_DELAY / 4;

    void addLayouts();
    void configureControlls();
    QVector<QPoint> generatePoints(int amount, int xRange, int yRange);
    inline int generateFromRange(int begin, int end);
    void reconnectTimersToKMeans();
    void reconnectTimersToMaxmin();

    Ui::MainWindow *ui;
    QPushButton *startButton;
    QSpinBox *pointBox;
    QLabel *kmeans;
    QLabel *maxmin;
    Canvas *maxminCanvas;
    Canvas *kmeansCanvas;
    ClusterizationAlgorithm *maxminModel;
    ClusterizationAlgorithm *kmeansModel;
    QTimer *clusterUpdtimer;
    QTimer *centroidUpdTimer;
};
#endif // MAINWINDOW_H
