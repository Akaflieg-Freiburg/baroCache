
#include <QCommandLineParser>

#include "BaroCache.h"

auto main(int argc, char *argv[]) -> int
{
    QCoreApplication const app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription(u"Test for baroCache"_qs);
    parser.addHelpOption();
    parser.process(app);

#warning Implement. Need to set up a framework for tests here, feeding data into the cache and then trying out how it work.
    Navigation::BaroCache baroCache;
    QGeoCoordinate* coordinate = new QGeoCoordinate(1.0,1.0,1.0);
    QGeoPositionInfo* info = new QGeoPositionInfo(*coordinate, QDateTime::currentDateTime());

    for(double height_pressure = 0.0, height_geometric = 0.0; height_pressure <= 5000; height_pressure += 300, height_geometric += 500.0)
    {
        baroCache.onPressureAltitudeReceived(Units::Distance::fromM(height_pressure));

        coordinate = new QGeoCoordinate(0,0,height_geometric);
        info = new QGeoPositionInfo(*coordinate, QDateTime::currentDateTime());

//        qDebug() << info->coordinate().altitude();
        baroCache.onGeometricPositionInfoReceived(*info);
        usleep(50000UL);
    }

    for(double height = 0; height <= 5000; height += 100)
    {
        baroCache.onPressureAltitudeReceived(Units::Distance::fromM(height));
    }
    baroCache.printAltitudeList();

    qDebug() << "estimated pressure altitude: " << baroCache.estimatedPressureAltitude(Units::Distance::fromM(4660),false).toM();
    return 0;
}
