#include "kmeans.h"

KMeans::KMeans() : ClusterizationAlgorithm()
{

}

void KMeans::setCentroids(QVector<QPoint> &newCentroids)
{
    centroids = newCentroids;
    prevCentroid.clear();
}

bool KMeans::finished() const
{
    if (centroids.length() != prevCentroid.length())
        return false;

    bool result = true;
    for(int i = 0; i < centroids.length() && result; ++i)
        result = (centroids[i] == prevCentroid[i]);
    return result;
}

void KMeans::start()
{
    defineClusters();
    prevCentroid.clear();
    //prevCentroid.append(centroids);
}

void KMeans::step()
{
    if (centroids.length() > 1)
    {
        prevCentroid.clear();
        prevCentroid.append(centroids);
        calcCentroids();
        defineClusters();
    }
}

void KMeans::defineClusters()
{
    clusters.clear();
    for (int i = 0; i < centroids.length(); ++i)
    {
        clusters.push_back(QVector<QPoint>());
    }

    for (QPoint pnt : points)
    {
        int min = 0;
        int minDistance = calcDistance(pnt, centroids[0]);
        for (int i = 1; i < centroids.length(); ++i)
        {
            int currDistance = calcDistance(pnt, centroids[i]);
            if (currDistance < minDistance)
            {
                min = i;
                minDistance = currDistance;
            }
        }
        clusters[min].push_back(pnt);
    }
}

void KMeans::calcCentroids()
{
    centroids.clear();

    for(QVector<QPoint> pnts: clusters)
    {
        QPoint mathCenter(0, 0);
        for (QPoint pnt : pnts)
        {
            mathCenter += pnt;
        }
        centroids.push_back(mathCenter / pnts.length());
    }
}
