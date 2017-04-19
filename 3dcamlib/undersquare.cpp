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
        double min = y[start];

        // find the minimun value in y
        for(auto j=1u; j<y.size();j++)
            {


            if(y[j] < min){

                    min = y[j];
                    start = j;
                }

            }

        ty.resize(1);
        tz.resize(1);
        ty[0] = y[start];
        tz[0] = z[start];


        //std::cout << start << std::endl;
        //std::cout << y[start] << " - " << z[start] << std::endl;

    for (auto i = 1u; i < y.size(); ++i) {
        const auto j = (i + start) % y.size();


        if (y[j] >= y[j-1])
        {

            ty.push_back(y[j]);
            tz.push_back(z[j]);
        }
        else if (y[j] < y[j-1])
        {
            if (z[j] < z[j-1])
            {
                ty.push_back(y[j-1]);
                tz.push_back(z[j]);
            }

        }


    }

    /*
    for (auto i = 0; i < ty.size(); ++i)
    {

        std::cout << ty[i] << " - " << tz[i] << std::endl;

    }
    */





    }


}


