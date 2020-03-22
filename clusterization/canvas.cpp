#include "canvas.h"
#include <QPainter>

Canvas::Canvas(QWidget *parent)
    : QFrame(parent)
    , blackPen(QPen(Qt::white))
    , background(QBrush(Qt::black))
    , isStart(false)
{
    brush.push_back(QBrush(QColor::fromRgb(255, 0, 0)));
    brush.push_back(QBrush(QColor::fromRgb(255, 153, 51)));
    brush.push_back(QBrush(QColor::fromRgb(255, 255, 0)));
    brush.push_back(QBrush(QColor::fromRgb(0, 128, 0)));
    brush.push_back(QBrush(QColor::fromRgb(0, 255, 0)));
    brush.push_back(QBrush(QColor::fromRgb(0, 0, 255)));
    brush.push_back(QBrush(QColor::fromRgb(0, 255, 255)));
    brush.push_back(QBrush(QColor::fromRgb(192, 192, 192)));
    brush.push_back(QBrush(QColor::fromRgb(128, 128, 128)));
    brush.push_back(QBrush(QColor::fromRgb(128, 128, 0)));
    brush.push_back(QBrush(QColor::fromRgb(128, 0, 128)));
    brush.push_back(QBrush(QColor::fromRgb(0, 128, 128)));
    brush.push_back(QBrush(QColor::fromRgb(0, 0, 128)));
    brush.push_back(QBrush(QColor::fromRgb(255, 105, 180)));
    brush.push_back(QBrush(QColor::fromRgb(75, 0, 130)));
    brush.push_back(QBrush(QColor::fromRgb(127, 255, 212)));
    brush.push_back(QBrush(QColor::fromRgb(210, 105, 30)));
    brush.push_back(QBrush(QColor::fromRgb(220, 20, 60)));
    brush.push_back(QBrush(QColor::fromRgb(255, 0, 255)));
    brush.push_back(QBrush(QColor::fromRgb(128, 0, 0)));

    pen.push_back(QPen(QColor::fromRgb(255, 0, 0)));
    pen.push_back(QPen(QColor::fromRgb(255, 153, 51)));
    pen.push_back(QPen(QColor::fromRgb(255, 255, 0)));
    pen.push_back(QPen(QColor::fromRgb(0, 128, 0)));
    pen.push_back(QPen(QColor::fromRgb(0, 255, 0)));
    pen.push_back(QPen(QColor::fromRgb(0, 0, 255)));
    pen.push_back(QPen(QColor::fromRgb(0, 255, 255)));
    pen.push_back(QPen(QColor::fromRgb(192, 192, 192)));
    pen.push_back(QPen(QColor::fromRgb(128, 128, 128)));
    pen.push_back(QPen(QColor::fromRgb(128, 128, 0)));
    pen.push_back(QPen(QColor::fromRgb(128, 0, 128)));
    pen.push_back(QPen(QColor::fromRgb(0, 128, 128)));
    pen.push_back(QPen(QColor::fromRgb(0, 0, 128)));
    pen.push_back(QPen(QColor::fromRgb(255, 105, 180)));
    pen.push_back(QPen(QColor::fromRgb(75, 0, 130)));
    pen.push_back(QPen(QColor::fromRgb(127, 255, 212)));
    pen.push_back(QPen(QColor::fromRgb(210, 105, 30)));
    pen.push_back(QPen(QColor::fromRgb(220, 20, 60)));
    pen.push_back(QPen(QColor::fromRgb(255, 0, 255)));
    pen.push_back(QPen(QColor::fromRgb(128, 0, 0)));

    //    brush.push_back(QBrush(QColor::fromRgb(255, 0, 0)));
    //    brush.push_back(QBrush(QColor::fromRgb(231, 120, 0)));
    //    brush.push_back(QBrush(QColor::fromRgb(250, 255, 19)));
    //    brush.push_back(QBrush(QColor::fromRgb(14, 231, 0)));
    //    brush.push_back(QBrush(QColor::fromRgb(10, 255, 245)));
    //    brush.push_back(QBrush(QColor::fromRgb(31, 0, 255)));
    //    brush.push_back(QBrush(QColor::fromRgb(203, 0, 236)));
    //    brush.push_back(QBrush(QColor::fromRgb(255, 183, 183)));
    //    brush.push_back(QBrush(QColor::fromRgb(255, 201, 106)));
    //    brush.push_back(QBrush(QColor::fromRgb(255, 255, 159)));
    //    brush.push_back(QBrush(QColor::fromRgb(191, 255, 149)));
    //    brush.push_back(QBrush(QColor::fromRgb(255, 254, 217)));
    //    brush.push_back(QBrush(QColor::fromRgb(207, 219, 255)));
    //    brush.push_back(QBrush(QColor::fromRgb(240, 212, 255)));
    //    brush.push_back(QBrush(QColor::fromRgb(67, 19, 0)));
    //    brush.push_back(QBrush(QColor::fromRgb(140, 76, 0)));
    //    brush.push_back(QBrush(QColor::fromRgb(178, 164, 0)));
    //    brush.push_back(QBrush(QColor::fromRgb(34, 101, 0)));
    //    brush.push_back(QBrush(QColor::fromRgb(0, 161, 164)));
    //    brush.push_back(QBrush(QColor::fromRgb(0, 20, 91)));

    //    pen.push_back(QPen(QColor::fromRgb(255, 0, 0)));
    //    pen.push_back(QPen(QColor::fromRgb(231, 120, 0)));
    //    pen.push_back(QPen(QColor::fromRgb(250, 255, 19)));
    //    pen.push_back(QPen(QColor::fromRgb(14, 231, 0)));
    //    pen.push_back(QPen(QColor::fromRgb(10, 255, 245)));
    //    pen.push_back(QPen(QColor::fromRgb(31, 0, 255)));
    //    pen.push_back(QPen(QColor::fromRgb(203, 0, 236)));
    //    pen.push_back(QPen(QColor::fromRgb(255, 183, 183)));
    //    pen.push_back(QPen(QColor::fromRgb(255, 201, 106)));
    //    pen.push_back(QPen(QColor::fromRgb(255, 255, 159)));
    //    pen.push_back(QPen(QColor::fromRgb(191, 255, 149)));
    //    pen.push_back(QPen(QColor::fromRgb(255, 254, 217)));
    //    pen.push_back(QPen(QColor::fromRgb(207, 219, 255)));
    //    pen.push_back(QPen(QColor::fromRgb(240, 212, 255)));
    //    pen.push_back(QPen(QColor::fromRgb(67, 19, 0)));
    //    pen.push_back(QPen(QColor::fromRgb(140, 76, 02)));
    //    pen.push_back(QPen(QColor::fromRgb(178, 164, 0)));
    //    pen.push_back(QPen(QColor::fromRgb(34, 101, 0)));
    //    pen.push_back(QPen(QColor::fromRgb(0, 161, 164)));
    //    pen.push_back(QPen(QColor::fromRgb(0, 20, 91)));

}

void Canvas::setCentroids(const QVector<QPoint> &centroids)
{
    this->centroids = centroids;
}

void Canvas::setClusters(const QVector<QVector<QPoint> > &clusters)
{
    this->clusters = clusters;
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.setPen(blackPen);
    p.setBrush(background);
    p.drawRect(rect());

    if (!centroids.empty() && !clusters.empty())
    {
        paintClusters(p);
        paintCentroids(p);
        isStart = false;
    }
}

void Canvas::paintCentroids(QPainter & painter)
{
    for (int i = 0; i < centroids.length(); ++i)
    {
        painter.setBrush(brush[i]);
        painter.drawRect(centroids[i].x() - CENTROID_SIDE_LEN,
                         centroids[i].y() - CENTROID_SIDE_LEN,
                         CENTROID_SIDE_LEN * 2, CENTROID_SIDE_LEN * 2);
    }
}

void Canvas::paintClusters(QPainter & painter)
{
    painter.setPen(blackPen);
    for (int i = 0; i < clusters.length(); ++i)
    {
        if (!isStart)
            painter.setPen(pen[i]);
        painter.drawPoints(clusters[i].data(), clusters[i].length());
    }
    painter.setPen(blackPen);
}
