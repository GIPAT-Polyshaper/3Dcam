#ifndef GCODEGENERATOR_H
#define GCODEGENERATOR_H

#include <QObject>

class GCodeGenerator : public QObject
{
    Q_OBJECT

public:
    GCodeGenerator();

public slots:
    void readAndGenerate();
};

#endif // GCODEGENERATOR_H
