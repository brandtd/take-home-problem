#include "take_home_problem.h"

#include "i_temperature_voltage_converter.h"

using namespace units::temperature;
using namespace units::voltage;

namespace TakeHomeProblem
{

TakeHomeExample(ITemperatureVoltageConverter converter)
: converter_(converter)
{
}

double TakeHomeExample::convertmvToK(double millivolts) const
{
   return units::unit_cast<double>(converter_.convert(millivolt_t(millivolts)));
}

double TakeHomeExample::convertKtomV(double kelvin) const
{
   return units::unit_cast<double>(converter_.convert(kelvin_t(kelvin)));
}

}