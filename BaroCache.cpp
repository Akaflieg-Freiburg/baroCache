
#include "BaroCache.h"

Navigation::BaroCache::BaroCache(QObject* parent)
    : QObject(parent)
{
#warning Implement
}

Units::Distance Navigation::BaroCache::estimatedPressureAltitude(Units::Distance geometricAltitude, bool allowImpreciseEstimate)
{
#warning Implement
    return {};
}

Units::Distance Navigation::BaroCache::estimatedGeometricAltitude(Units::Distance pressureAltitude, bool allowImpreciseEstimate)
{
#warning Implement
    return {};
}

void Navigation::BaroCache::onPressureAltitudeReceived(Units::Distance pressureAltitude)
{
#warning Implement
}

void Navigation::BaroCache::onGeometricPositionInfoReceived(const QGeoPositionInfo& positionInfo)
{
#warning Implement
}
