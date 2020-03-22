#ifndef CLUSTERIZATIONALGORITHM_H
#define CLUSTERIZATIONALGORITHM_H

#include <QVector>
#include <QPoint>

class ClusterizationAlgorithm
{
public:
    ClusterizationAlgorithm()
    {

    }

    virtual ~ClusterizationAlgorithm()
    {

    }

    virtual void setPoints(QVector<QPoint> & newPoints) { points = newPoints; };
    virtual void setCentroids(QVector<QPoint> & newCentroids) { centroids = newCentroids; }
    virtual QVector<QPoint> getPoints() const { return points; }
    virtual QVector<QPoint> getCentroids() const {return centroids; }
    virtual QVector<QVector<QPoint>> getClusters() const {return clusters; }
    virtual bool finished() const = 0;
    virtual void start() = 0;
    virtual void step() = 0;
protected:
    QVector<QPoint> points;
    QVector<QVector<QPoint>> clusters;
    QVector<QPoint> centroids;

    virtual int calcDistance(QPoint first, QPoint second);
};

#endif // CLUSTERIZATIONALGORITHM_H
