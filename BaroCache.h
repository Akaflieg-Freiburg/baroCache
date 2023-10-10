
#pragma once

#include <QGeoPositionInfo>

#include "Distance.h"


namespace Navigation
{

class BaroCache : public QObject
{
    Q_OBJECT

public:
    /*! \brief Standard constructor
     *
     * @param parent The standard QObject parent pointer
     */
    BaroCache(QObject* parent = nullptr);

    // Default destructor
    ~BaroCache() override = default;



    //
    // Methods
    //

    /*! \brief Estimate pressure altitude for a given geometric altitude
     *
     *  This method queries the cache, in order to estimate the pressure altitude for a given geometric altitude.
     *  If allowImpreciseEstimate is false, it will return an invalid Distance unless there exists a cache entry whose geometric
     *  altitude is within +/- 500ft from the geometricAltitude parameter.
     *
     *  Remember: pressure altitude is the barometric altitude above the 1013.2 hPa pressure surface
     *
     *  @param geometricAltitude Geometric altitude whose associated pressure altitude is to be estimated
     *
     *  @param allowImpreciseEstimate Return an estimate even if the cache is empty or contains little data.
     *
     *  @returns Estimated pressure altitude
     */
    [[nodiscard]] Units::Distance estimatedPressureAltitude(Units::Distance geometricAltitude, bool allowImpreciseEstimate=false);

    /*! \brief Estimate geometric altitude for a given pressure altitude
     *
     *  This method queries the cache, in order to estimate the geometric altitude for a given pressure altitude.
     *  If allowImpreciseEstimate is false, it will return an invalid Distance unless there exists a cache entry whose pressure
     *  altitude is within +/- 500ft from the pressureAltitude parameter.
     *
     *  Remember: pressure altitude is the barometric altitude above the 1013.2 hPa pressure surface
     *
     *  @param pressureAltitude Pressure altitude whose associated geometric altitude is to be estimated
     *
     *  @param allowImpreciseEstimate Return an estimate even if the cache is empty or contains little data.
     *
     *  @returns Estimated geometric altitude
     */
    Units::Distance estimatedGeometricAltitude(Units::Distance pressureAltitude, bool allowImpreciseEstimate=false);

public slots:
    /*! \brief This slot is called whenever a pressure altitude reading comes in from a traffic data receiver (e.g. FLARM)
     *
     *  @param pressureAltitude Pressure altitude (can be invalid)
     */
    void onPressureAltitudeReceived(Units::Distance pressureAltitude);

    /*! \brief  This slot is called whenever a geometric position reading comes in from the satnav system
     *
     *  @param positionInfo Position info (can be invalid)
     */
    void onGeometricPositionInfoReceived(const QGeoPositionInfo& positionInfo);

private:
    Q_DISABLE_COPY_MOVE(BaroCache)
};

} // namespace Navigation
