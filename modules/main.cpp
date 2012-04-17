#include <QtGui/QApplication>
#include <QFile>
#include <QTextStream>
#include "QsLog.h"
#include "QsLogDest.h"
#include <QDir>
#include "clientinterface.h"
//#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialize the QS logger
    QsLogging::Logger& logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);

    // Set up the logging file
    const QString logFilePath(QDir(a.applicationDirPath()).filePath("clientLog.txt"));
    QsLogging::DestinationPtr fileDestination(QsLogging::DestinationFactory::MakeFileDestination(logFilePath));
    QsLogging::DestinationPtr debugDestination(QsLogging::DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(fileDestination.get());
    logger.addDestination(debugDestination.get());

    QLOG_TRACE() << "Tracer Initialized";

    QLOG_INFO() << "Program started";
    QLOG_INFO() << "Built with QT " << QT_VERSION_STR << "running on " << qVersion();

   // MainWindow w;
    ClientInterface w;

    QLOG_TRACE() << "Object of MainWindow called w created";

    w.show();

    QLOG_TRACE() << "Showing the client UI through MainWindow called w";
    
    if (a.exec() == 0)
    {
        QLOG_TRACE() << "Program exit successful";
        return 0;
    }
    else {
        QLOG_FATAL() << "Program exit successful";
        return -1;
    }
}
