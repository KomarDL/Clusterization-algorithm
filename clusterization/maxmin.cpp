#include "maxmin.h"
#include <QRandomGenerator>
#include <QTime>
#include <QtMath>

Maxmin::Maxmin()
{
}

void Maxmin::setPoints(QVector<QPoint> &newPoints)
{
    points = newPoints;
    centroids.clear();
    clusters.clear();
    prevCentroidsCount = 0;
    criticalDistance = 0;
}

void Maxmin::start()
{
    if (points.length() < 2)
        return;

    centroids.clear();
    clusters.clear();
    prevCentroidsCount = 0;

    defineCentroids();
    defineClusters();
}

void Maxmin::step()
{
    if (points.length() < 2 || centroids.empty())
        return;

    prevCentroidsCount = centroids.length();
    defineCentroids();
    if (!finished())
        defineClusters();
}

void Maxmin::defineCentroids()
{
    if (centroids.empty())
    {
        centroids.push_back(points[QRandomGenerator::global()->generate() % points.length()]);
        return;
    }

    defineCriticalDistance();

    QVector<QPoint> newCentroids;
    QVector<int> distances;
    for (int i = 0; i < centroids.length(); ++i)
    {
        int maxIndex = 0;
        int maxDistance = calcDistance(centroids[i], clusters[i][0]);
        for (int j = 1; j < clusters[i].length(); ++j)
        {
            int currDistance = calcDistance(centroids[i], clusters[i][j]);
            if (currDistance > maxDistance)
            {
                maxIndex = j;
                maxDistance = currDistance;
            }
        }

        if (maxDistance >= criticalDistance)
        {
            newCentroids.push_back(clusters[i][maxIndex]);
            distances.push_back(maxDistance);
        }
    }

    if (!distances.empty())
    {

        int maxDistanceIndex = 0;
        for (int i = 1; i < distances.length(); ++i)
        {
            if (distances[i] > distances[maxDistanceIndex])
                maxDistanceIndex = i;

        }

        centroids.push_back(newCentroids[maxDistanceIndex]);
    }
}

void Maxmin::defineClusters()
{
    if (centroids.length() == 1)
    {
        clusters.push_back(points);
        return;
    }

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

void Maxmin::defineCriticalDistance()
{
    if(centroids.length() == 1)
    {
        criticalDistance = 0;
        return;
    }

    int count = 0, sum = 0;
    for(int i = 0; i < centroids.length(); ++i)
    {
        for (int j = i + 1; j < centroids.length(); j++)
        {
            sum += calcDistance(centroids[i], centroids[j]);
            ++count;
        }
    }

    criticalDistance = qRound(static_cast<double>(sum) / (count * 2));
}


