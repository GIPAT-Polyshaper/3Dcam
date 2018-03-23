#ifndef APPLICATIONCONTROL_H
#define APPLICATIONCONTROL_H

#include <QObject>
#include <QTextStream>
#include "stlloader.h"
#include "triangularmeshgenerator.h"
#include "gcodegenerator.h"
#include "viewer3d.h"
#include <QtConcurrent>

class Viewer3D;
class ApplicationControl: public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool error READ getError NOTIFY errorChanged)
    Q_PROPERTY(QString lastError READ getLastError NOTIFY lastErrorChanged)
    Q_PROPERTY(int toolH READ getToolHeight NOTIFY heightChanged)
    Q_PROPERTY(int toolW READ getToolWidth NOTIFY widthChanged)
    Q_PROPERTY(int toolSp READ getToolSpeed NOTIFY speedChanged)
    Q_PROPERTY(QString toolSh READ getToolShape  NOTIFY shapeChanged)
    Q_PROPERTY(int overlap READ getOverlap NOTIFY overlapChanged)
    Q_PROPERTY(int volumeX READ getVolumeX NOTIFY volumeXChanged)
    Q_PROPERTY(int volumeY READ getVolumeY NOTIFY volumeYChanged)
    Q_PROPERTY(int volumeZ READ getVolumeZ NOTIFY volumeZChanged)
    Q_PROPERTY(int objectOffsetX READ getObjectOffsetX NOTIFY objectOffsetXChanged)
    Q_PROPERTY(int objectOffsetY READ getObjectOffsetY NOTIFY objectOffsetYChanged)

public:

    //Assicuriamoci che ci sia una sola istanza di ApplicationControl
    static ApplicationControl& get_instance()
    {
        static ApplicationControl instance;
        return instance;
    }

    void setViewer3D(Viewer3D* v);
    void setStartingOffset(int x, int y, int z);

    int getToolHeight() const;
    int getToolWidth() const;
    int getToolSpeed() const;
    QString getToolShape() const;
    int getOverlap() const;
    int getVolumeX() const;
    int getVolumeY() const;
    int getVolumeZ() const;
    int getObjectOffsetX() const;
    int getObjectOffsetY() const;
    float getStartingoffsetX() const;
    float getStartingOffsetY() const;
    float getStartingOffsetZ() const;

    QString getLastError() const;
    bool getError() const;
    void generateCode();

public slots:
    void setToolHeight(int h);
    void setToolWidth(int w);
    void setToolSpeed(int sp);
    void setToolShape(QString sh);
    void setOverlap(int o);
    void setVolumeX(int x);
    void setVolumeY(int y);
    void setVolumeZ(int z);
    void setAzimuth(int az);
    void setElevation(int el);
    void setDistance(float di);
    void setObjectOffsetX(int x);
    void setObjectOffsetY(int y);
    void openFile(QString path);
    void createFile(QString path);
    void setError(bool e);
    void setLastError(QString e);

signals:
    void errorChanged(bool e);
    void lastErrorChanged(QString e);

    void heightChanged(int newHeight);
    void widthChanged(int newWidth);
    void speedChanged(int newSpeed);
    void shapeChanged(QString newShape);
    void overlapChanged(int newOverlap);
    void volumeXChanged(int newVolumeX);
    void volumeYChanged(int newVolumeY);
    void volumeZChanged(int newVolumeZ);
    void objectOffsetXChanged(int newObjectOffX);
    void objectOffsetYChanged(int newObjectOffY);

protected:
    ApplicationControl();

private:
    void readAndGenerate3DModel();

//    GCodeGenerator* gcodeGenerator;
    Viewer3D* viewer3D;
    int toolHeight;
    int toolWidth;
    int toolSpeed;
    GCodeGenerator::Shape toolShape;
    int overlap;
    int volumeXAxis;
    int volumeYAxis;
    int volumeZAxis;

    float startingOffsetX;
    float startingOffsetY;
    float startingOffsetZ;

    int objectOffsetX;
    int objectOffsetY;

    QString filePath;
    QString fileWritePath;
    QString lastError;
    bool error;
};

#endif // APPLICATIONCONTROL_H
