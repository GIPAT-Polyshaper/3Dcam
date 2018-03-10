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

public:

    //Assicuriamoci che ci sia una sola istanza di ApplicationControl
    static ApplicationControl& get_instance()
    {
        static ApplicationControl instance;
        return instance;
    }

    void setViewer3D(Viewer3D* v);
    void setGCodeGenerator(GCodeGenerator* g);
    void setStartingOffset(int x, int y, int z);

    int getObjectOffsetX() const;
    int getObjectOffsetY() const;

    void generateCode();

public slots:
    void setAltezza(int a);
    void setDiametro(int d);
    void setVelocita(int v);
    void setForma(QString f);
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

protected:
    ApplicationControl();

private:
    void readAndGenerate3DModel();

    GCodeGenerator* gcodeGenerator;
    Viewer3D* viewer3D;

    QString filePath;
    QString fileWritePath;
};

#endif // APPLICATIONCONTROL_H
