#ifndef MAXMIN_H
#define MAXMIN_H

#include <QVector>
#include <QPoint>
#include "clusterizationalgorithm.h"

class Maxmin : public ClusterizationAlgorithm
{
public:
    Maxmin();

    void setPoints(QVector<QPoint> &newPoints) override;
    bool finished() const override { return (centroids.length() == prevCentroidsCount) && (prevCentroidsCount != 0); };
    void start() override;
    void step() override;

private:
    int prevCentroidsCount;
    int criticalDistance;

    void defineCentroids();
    void defineClusters();
    void defineCriticalDistance();
};

#endif // MAXMIN_H
