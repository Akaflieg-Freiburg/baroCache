
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
    altitude_element element;
    element.pressureAltitude = pressureAltitude;
    element.geometricAltitude = Units::Distance::fromM(0);
    element.timestamp = QDateTime::currentDateTime();

    if(altitudeList.size() > 1)
    {
        // check every element
        for(unsigned int i = 0; i < altitudeList.size() - 1; i++)
        {
            //check if a element has the same time (+/- 20ms)
            if((altitudeList.at(i).timestamp.msecsTo(QDateTime::currentDateTime()) < TIME_WINDOW) &&
               (altitudeList.at(i).timestamp.msecsTo(QDateTime::currentDateTime()) > -TIME_WINDOW) &&
                    (altitudeList.at(i).pressureAltitude.toM() == 0))
            {
                altitudeList.operator[](i).pressureAltitude = element.pressureAltitude;
                break;
            }

            // check if the altitude is not in the list
            else if((altitudeList.at(i).pressureAltitude + Units::Distance::fromM(ALTITUDE_DISTANCE) <= pressureAltitude) &&
                    (pressureAltitude + Units::Distance::fromM(ALTITUDE_DISTANCE) <= altitudeList.at(i + 1).pressureAltitude))
            {
                altitudeList.insert(i + 1, element);
            }
        }

        //check last element
        if((altitudeList.last().pressureAltitude.toM() + ALTITUDE_DISTANCE) <= element.pressureAltitude.toM() && (altitudeList.last().pressureAltitude.toM() != 0))
        {
            altitudeList.append(element);
        }
        else if((altitudeList.last().timestamp.msecsTo(QDateTime::currentDateTime()) < TIME_WINDOW) && (altitudeList.last().pressureAltitude.toM() == 0))
        {
            altitudeList.last().pressureAltitude = element.geometricAltitude;
        }
    }
    else if(((altitudeList.size() == 1) && (element.pressureAltitude > (altitudeList.at(0).pressureAltitude + Units::Distance::fromM(ALTITUDE_DISTANCE)))) || (altitudeList.size() == 0))
    {
        altitudeList.append(element);
    }
}

void Navigation::BaroCache::onGeometricPositionInfoReceived(const QGeoPositionInfo& positionInfo)
{
#warning Implement
    altitude_element element;
    element.geometricAltitude = Units::Distance::fromM(positionInfo.coordinate().altitude());
    element.pressureAltitude = Units::Distance::fromM(0);
    element.timestamp = QDateTime::currentDateTime();

    if(altitudeList.size() > 1)
    {

        // check every element
        for(unsigned int i = 0; i < altitudeList.size() - 1; i++)
        {
            //check if a element has the same timestamp (+/- 20ms)
            if((altitudeList.at(i).timestamp.msecsTo(QDateTime::currentDateTime()) < TIME_WINDOW) &&
               (altitudeList.at(i).timestamp.msecsTo(QDateTime::currentDateTime()) > -TIME_WINDOW) &&
               (altitudeList.at(i).geometricAltitude.toM() == 0))
            {

                altitudeList.operator[](i).geometricAltitude = element.geometricAltitude;
//                qDebug() <<"time: " << altitudeList.at(i).timestamp.msecsTo(QDateTime::currentDateTime()) << " " << altitudeList.at(i).geometricAltitude.toM() << " " << altitudeList.at(i).pressureAltitude.toM();
                break;
            }

            // check if the altitude is not in the list
            else if((altitudeList.at(i).geometricAltitude + Units::Distance::fromM(ALTITUDE_DISTANCE) <= element.geometricAltitude) &&
                    (element.geometricAltitude + Units::Distance::fromM(ALTITUDE_DISTANCE) <= altitudeList.at(i + 1).geometricAltitude))
            {
                altitudeList.insert(i + 1, element);
                break;
            }
        }
        //check last element
        if((altitudeList.last().geometricAltitude.toM() + ALTITUDE_DISTANCE) <= element.geometricAltitude.toM() && (altitudeList.last().geometricAltitude.toM() != 0))
        {
            altitudeList.append(element);
        }
        else if((altitudeList.last().timestamp.msecsTo(QDateTime::currentDateTime()) < TIME_WINDOW) && (altitudeList.last().geometricAltitude.toM() == 0))
        {
            altitudeList.last().geometricAltitude = element.geometricAltitude;
        }
    }
    else if((altitudeList.size() == 1) &&
            (element.geometricAltitude > (altitudeList.at(0).geometricAltitude + Units::Distance::fromM(ALTITUDE_DISTANCE))) &&
            (altitudeList.at(0).pressureAltitude.toM() == 0) ||
            (altitudeList.size() == 0))
    {
        altitudeList.append(element);
    }
}


void Navigation::BaroCache::printAltitudeList()
{
    for(int i = 0; i < altitudeList.size(); i++)
    {
        qDebug()<< "pressureAltitude:" <<  altitudeList.value(i).pressureAltitude.toM() << " geometricAltitude:" << altitudeList.value(i).geometricAltitude.toM();
    }
}
