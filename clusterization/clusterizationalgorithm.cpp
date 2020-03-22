#include <QtMath>
#include "clusterizationalgorithm.h"

int ClusterizationAlgorithm::calcDistance(QPoint first, QPoint second)
{
    return qSqrt(qPow(qAbs(first.x() - second.x()), 2) + qPow(qAbs(first.y() - second.y()), 2));
}
