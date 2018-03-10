#include "applicationcontrol.h"
#include "toolpathgenerator.h"

double roundDouble(double d, int precision)
{
    double EPSILON = 1.0/pow(10, precision);
    double num = d / EPSILON;
    num = round(num);
    return num * EPSILON;
}

ApplicationControl::ApplicationControl()
{
}

void ApplicationControl::setViewer3D(Viewer3D *v)
{
    this->viewer3D = v;
    QObject::connect(gcodeGenerator, &GCodeGenerator::volumeXChanged, viewer3D, &Viewer3D::setVolumeX);
    QObject::connect(gcodeGenerator, &GCodeGenerator::volumeYChanged, viewer3D, &Viewer3D::setVolumeY);
    QObject::connect(gcodeGenerator, &GCodeGenerator::volumeZChanged, viewer3D, &Viewer3D::setVolumeZ);
}

void ApplicationControl::setGCodeGenerator(GCodeGenerator *g)
{
    this->gcodeGenerator = g;
}

void ApplicationControl::setStartingOffset(int x, int y, int z)
{
    gcodeGenerator->setStartingOffset(x, y, z);
}

int ApplicationControl::getObjectOffsetX() const
{
    return gcodeGenerator->getObjectOffsetX();
}

int ApplicationControl::getObjectOffsetY() const
{
    return gcodeGenerator->getObjectOffsetY();
}

void ApplicationControl::setAltezza(int a)
{
    gcodeGenerator->setAltezza(a);
}

void ApplicationControl::setDiametro(int d)
{
    gcodeGenerator->setDiametro(d);
}

void ApplicationControl::setForma(QString f)
{
    gcodeGenerator->setForma(f);
}

void ApplicationControl::setObjectOffsetX(int x)
{
    gcodeGenerator->setObjectOffsetX(x);
    viewer3D->setTrianglesDirty(true);
}

void ApplicationControl::setObjectOffsetY(int y)
{
    gcodeGenerator->setObjectOffsetY(y);
    viewer3D->setTrianglesDirty(true);
}

void ApplicationControl::setOverlap(int o)
{
    gcodeGenerator->setOverlap(o);
}

void ApplicationControl::setVelocita(int v)
{
    gcodeGenerator->setVelocita(v);
}

void ApplicationControl::setVolumeX(int x)
{
    gcodeGenerator->setVolumeX(x);
}

void ApplicationControl::setVolumeY(int y)
{
    gcodeGenerator->setVolumeY(y);
}

void ApplicationControl::setVolumeZ(int z)
{
    gcodeGenerator->setVolumeZ(z);
}

void ApplicationControl::setAzimuth(int az)
{
    viewer3D->setAzimuth(az);
}

void ApplicationControl::setDistance(float di)
{
    viewer3D->setDistance(di);
}

void ApplicationControl::setElevation(int el)
{
    viewer3D->setElevation(el);
}

bool ApplicationControl::openFile(QString path)
{
    if (path.contains("file://"))
    {
        filePath = path.mid(7,path.length());
    }
    else
    {
        filePath = path;
    }
    try
    {
        readAndGenerate3DModel();
    }
    catch (StlLoaderExceptions e)
    {
        lastError = e.what();
        return false;
    }
    return true;

}

void ApplicationControl::readAndGenerate3DModel()
{
    StlLoader loader(filePath);
    viewer3D->setGeometry(loader.triangles());
}

void ApplicationControl::createFile(QString path)
{
    if (path.contains("file://"))
    {
        fileWritePath = path.mid(7,path.length());
    }
    else
    {
        fileWritePath = path;
    }
    if (!fileWritePath.endsWith(".gcode",Qt::CaseInsensitive))
    {
        fileWritePath = fileWritePath.append(".gcode");
    }
    QtConcurrent::run(this, &ApplicationControl::generateCode);
}

QString ApplicationControl::getLastError()
{
    return lastError;
}

void ApplicationControl::generateCode()
{
    QFile file(fileWritePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        VerticesAndFacesGenerator v(viewer3D->getTriangles(), gcodeGenerator->getStartingoffsetX() + gcodeGenerator->getObjectOffsetX(), gcodeGenerator->getStartingOffsetY() + gcodeGenerator->getObjectOffsetY(), gcodeGenerator->getStartingOffsetZ());
        TriangularMeshGenerator t(v.vertices(), v.faces());

        ToolPathGenerator tg(t.polyhedron(),0.1,gcodeGenerator->getDiametroUtensile());
        tg.setVolume(gcodeGenerator->getVolumeX(), gcodeGenerator->getVolumeY(), gcodeGenerator->getVolumeZ());
        double currentY = 0.0;

        std::vector<std::list<Point>> toolPath;
        while(currentY <= gcodeGenerator->getVolumeY())
        {
            toolPath.push_back(tg.getToolPath(currentY));
            currentY += roundDouble(gcodeGenerator->getDiametroUtensile() * (1 - gcodeGenerator->getOverlapPassate()/100.0), 3);
        }

        out << gcodeGenerator->gCodeGeneration(toolPath);
    }
    if (file.isOpen())
    {
        file.close();
    }
}
