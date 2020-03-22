#ifndef KMEANS_H
#define KMEANS_H

#include <QVector>
#include <QPoint>
#include "clusterizationalgorithm.h"

class KMeans : public ClusterizationAlgorithm
{
public:
    KMeans();

    void setCentroids(QVector<QPoint> &newCentroids) override;
    bool finished() const override;
    void start() override;
    void step() override;

private:
    QVector<QPoint> prevCentroid;

    void defineClusters();
    void calcCentroids();
};

#endif // KMEANS_H
