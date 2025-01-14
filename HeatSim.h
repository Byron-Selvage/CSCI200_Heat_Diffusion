#ifndef HEATSIM_H
#define HEATSIN_H

#include <fstream>
#include <iostream>
#include <vector>

class HeatSim {

public:

    /**
    * @brief Creates a HeatSim object
    * @desc Initializes _temperatures vector and sets _alpha value
    */
    HeatSim(const double ALPHA);

    /**
    * @brief Reads data from file
    * @desc Reads temp valules from file and stores them in _temperatures, finds min and max values
    */
    void setInitialProfile(const std::string& FILE);

    /**
    * @brief Updates _temperatures vector
    * @desc Uses the simple explicit finite difference method to calculate temperature at each position
    */
    void simulate(const double ENDTEMP);

    /**
    * @brief _temeratures getter
    */
    const double* getTemperatures() const;

    /**
    * @brief _min getter
    */
    double getMin() const;

    /**
    * @brief _max getter
    */
    double getMax() const;

private:
    double _temperatures[101];
    double _alpha;
    double _max;
    double _min;
};

#endif