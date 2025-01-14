#include "HeatSim.h"

#include <fstream>
#include <iostream>
#include <vector>

HeatSim::HeatSim(const double ALPHA){
    _alpha = ALPHA;
    _min = 0;
    _max = 1;
}

void HeatSim::setInitialProfile(const std::string& FILE){
    double val;
    int idx = 1;
    std::ifstream input(FILE);
    if (input.fail()){
        std::cout << "Error opening file " << FILE << std::endl;
        return;
    }
    input >> val;
    _min = val;
    _max = val;
    _temperatures[0] = val;

    while (input >> val){
        _temperatures[idx] = val;

        if (val > _max){
            _max = val;
        }
        if (val < _min){
            _min = val;
        }

        idx++;
    }

    if (_min >=0){
        _min = _max * -1;
    }
    input.close();
}

void HeatSim::simulate(const double ENDTEMP){
    double newTemps[101];
    newTemps[0] = _temperatures[0] + _alpha * (ENDTEMP - 2 * _temperatures[0] + _temperatures[1]);
    newTemps[100] = _temperatures[100] + _alpha * (_temperatures[99] - 2 * _temperatures[100] + ENDTEMP);
    for(unsigned int i = 1; i < 100; i++){
        newTemps[i] = _temperatures[i] + _alpha * (_temperatures[i-1] - 2 * _temperatures[i] + _temperatures[i +1]);
    }
    for (int i = 0; i < 101; i++) {
        _temperatures[i] = newTemps[i];
    }
}

const double* HeatSim::getTemperatures() const{
    return _temperatures;
}

double HeatSim::getMin() const{
    return _min;
}

double HeatSim::getMax() const{
    return _max;
}