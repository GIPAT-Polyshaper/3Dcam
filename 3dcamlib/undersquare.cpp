#include "undersquare.h"
#include <iostream>
#include <algorithm>
#include <vector>

Undersquare::Undersquare(std::vector<double> y, std::vector<double> z)
    : ty()
    , tz()
{
    if (!y.empty())
    {
        int start = 0;
        double min = y[0];

        // find the minimun value in y
        for(int j=1; j<y.size();j++)
            {

            if(y[j] < min)

                min = y[j];
                start = j;

            }

        ty.resize(1);
        tz.resize(1);
        ty[0] = y[start];
        tz[0] = z[start];

        // start:y.size, 0:start

    for (auto i = 1; i < y.size(); ++i) {
        const auto j = (i + start) % y.size();


        if (y[j] >= y[j-1])
        {
            ty.push_back(y[j]);
            tz.push_back(z[j]);
        }


    }


    }


}


