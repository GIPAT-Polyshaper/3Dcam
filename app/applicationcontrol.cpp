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
    error = false;
    emit errorChanged(false);
    toolHeight = 40;
    toolWidth = 6;
    toolSpeed = 1000;
    toolShape = GCodeGenerator::Candela;
    overlap = 50;
    volumeXAxis = 100;
    volumeYAxis = 100;
    volumeZAxis = 100;
    startingOffsetX = 0;
    startingOffsetY = 0;
    startingOffsetZ = 0;
    objectOffsetX = 0;
    objectOffsetY = 0;
}

void ApplicationControl::setViewer3D(Viewer3D *v)
{
    this->viewer3D = v;
}

//void ApplicationControl::setGCodeGenerator(GCodeGenerator *g)
//{
//    this->gcodeGenerator = g;
//}

void ApplicationControl::setStartingOffset(int x, int y, int z)
{
    startingOffsetX = x;
    startingOffsetY = y;
    startingOffsetZ = z;
}

int ApplicationControl::getToolHeight() const
{
    return toolHeight;
}

int ApplicationControl::getToolWidth() const
{
    return toolWidth;
}

int ApplicationControl::getToolSpeed() const
{
    return toolSpeed;
}

QString ApplicationControl::getToolShape() const
{
    QString forma;
    forma = "Candela";
    return forma;
}

int ApplicationControl::getOverlap() const
{
    return overlap;
}

int ApplicationControl::getVolumeX() const
{
    return volumeXAxis;
}

int ApplicationControl::getVolumeY() const
{
    return volumeYAxis;
}

int ApplicationControl::getVolumeZ() const
{
    return volumeZAxis;
}

int ApplicationControl::getObjectOffsetX() const
{
    return objectOffsetX;
}

int ApplicationControl::getObjectOffsetY() const
{
    return objectOffsetY;
}

float ApplicationControl::getStartingoffsetX() const
{
    return startingOffsetX;
}

float ApplicationControl::getStartingOffsetY() const
{
    return startingOffsetY;
}

float ApplicationControl::getStartingOffsetZ() const
{
    return startingOffsetZ;
}

bool ApplicationControl::getError() const
{
    return error;
}

void ApplicationControl::setToolHeight(int h)
{
    if (toolHeight != h)
    {
        toolHeight = h;
        emit heightChanged(h);
    }
}

void ApplicationControl::setToolWidth(int w)
{
    if (toolWidth != w)
    {
        toolWidth = w;
        emit widthChanged(w);
    }
}

void ApplicationControl::setToolSpeed(int sp)
{
    if (toolSpeed != sp)
    {
        toolSpeed = sp;
        emit speedChanged(sp);
    }
}

void ApplicationControl::setToolShape(QString sh)
{
    if (getToolShape().compare(sh,Qt::CaseInsensitive) != 0)
    {
        toolShape = GCodeGenerator::Candela;
        emit shapeChanged(sh);
    }
}

void ApplicationControl::setOverlap(int o)
{
    if (overlap != o)
    {
        overlap = o;
        emit overlapChanged(o);
    }
}

void ApplicationControl::setVolumeX(int x)
{
    if (volumeXAxis != x)
    {
        volumeXAxis = x;
        viewer3D->setVolumeX(x);
        emit volumeXChanged(x);
    }
}

void ApplicationControl::setVolumeY(int y)
{
    if(volumeYAxis != y)
    {
        volumeYAxis = y;
        viewer3D->setVolumeY(y);
        emit volumeYChanged(y);
    }
}

void ApplicationControl::setVolumeZ(int z)
{
    if (volumeZAxis != z)
    {
        volumeZAxis = z;
        viewer3D->setVolumeZ(z);
        emit volumeZChanged(z);
    }
}

void ApplicationControl::setObjectOffsetX(int x)
{
    if (objectOffsetX != x)
    {
        objectOffsetX = x;
        emit objectOffsetXChanged(x);
        viewer3D->setTrianglesDirty(true);
    }
}

void ApplicationControl::setObjectOffsetY(int y)
{
    if (objectOffsetY != y)
    {
        objectOffsetY = y;
        emit objectOffsetYChanged(y);
        viewer3D->setTrianglesDirty(true);
    }
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

void ApplicationControl::openFile(QString path)
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
        setLastError(e.what());
        setError(true);
    }
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

QString ApplicationControl::getLastError() const
{
    return lastError;
}

void ApplicationControl::setError(bool e)
{
    if (error != e)
    {
        error = e;
        emit errorChanged(e);
    }
}

void ApplicationControl::setLastError(QString e)
{
    if (lastError.compare(e) != 0)
    {
        lastError = e;
        emit lastErrorChanged(e);
    }
}

void ApplicationControl::generateCode()
{
    QFile file(fileWritePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        try
        {
            QTextStream out(&file);
            VerticesAndFacesGenerator v(viewer3D->getTriangles(), getStartingoffsetX() + getObjectOffsetX(), getStartingOffsetY() + getObjectOffsetY(), getStartingOffsetZ());
            TriangularMeshGenerator t(v.vertices(), v.faces());

            ToolPathGenerator tg(t.polyhedron(), 0.1, getToolWidth());
            GCodeGenerator gcodeGenerator(toolHeight, toolWidth, toolSpeed, volumeXAxis, volumeYAxis, volumeZAxis);
            tg.setVolume(getVolumeX(), getVolumeY(), getVolumeZ());
            double currentY = 0.0;

            std::vector<std::list<Point>> toolPath;
            while(currentY <= getVolumeY())
            {
                toolPath.push_back(tg.getToolPath(currentY));
                currentY += roundDouble(getToolWidth() * (1 - getOverlap()/100.0), 3);
            }

            out << gcodeGenerator.gCodeGeneration(toolPath);
        }
        catch (std::exception e)
        {
            setLastError("An error occurred while generating G-Code, the model may contain some errors");
            setError(true);
            if (file.isOpen())
            {
                file.close();
            }
        }
    }
    if (file.isOpen())
    {
        file.close();
    }
}
