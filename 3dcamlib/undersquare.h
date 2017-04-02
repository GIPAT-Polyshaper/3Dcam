#ifndef UNDERSQUARE_H
#define UNDERSQUARE_H

#include <QObject>

class Undersquare
{
public:
    Undersquare(std::vector<double> y, std::vector<double> z);

    const std::vector<double>& toolY() const
    {
        return ty;
    }

    const std::vector<double>& toolZ() const
    {
        return tz;
    }

private:
    std::vector<double> ty;
    std::vector<double> tz;
};

#endif // UNDERSQUARE_H
