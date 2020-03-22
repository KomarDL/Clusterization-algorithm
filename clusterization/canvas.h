#ifndef Canvas_H
#define Canvas_H

#include <QFrame>
#include <QVector>
#include <QPoint>
#include <QPen>
#include <QBrush>

class Canvas : public QFrame
{
    Q_OBJECT
public:
    Canvas(QWidget *parent = nullptr);
    void setCentroids(const QVector<QPoint> & centroids);
    void setClusters(const QVector<QVector<QPoint>> & clusters);
    void reset() { isStart = true; }
protected:
    void paintEvent(QPaintEvent *) override;
private:
    static constexpr int CENTROID_SIDE_LEN = 10;

    void paintCentroids(QPainter & painter);
    void paintClusters(QPainter & painter);


    QVector<QVector<QPoint>> clusters;
    QVector<QPoint> centroids;
    QVector<QPen> pen;
    QVector<QBrush> brush;
    QPen blackPen;
    QBrush background;
    bool isStart;
};

#endif // Canvas_H
