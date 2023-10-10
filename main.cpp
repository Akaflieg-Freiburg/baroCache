
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

    return 0;
}
