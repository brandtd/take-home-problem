#include "requested_converter_interface.h"

#include "i_temperature_voltage_converter.h"

using namespace units::temperature;
using namespace units::voltage;

namespace TakeHomeProblem
{

RequestedConverterInterface::RequestedConverterInterface(const ITemperatureVoltageConverter &converter)
: converter_(converter)
{
}

double RequestedConverterInterface::convertmvToK(double millivolts) const
{
   return units::unit_cast<double>(converter_.convert(millivolt_t(millivolts)));
}

double RequestedConverterInterface::convertKtomV(double kelvin) const
{
   return units::unit_cast<double>(converter_.convert(kelvin_t(kelvin)));
}

}