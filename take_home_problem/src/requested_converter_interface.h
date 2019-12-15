#pragma once

namespace TakeHomeProblem
{
   class ITemperatureVoltageConverter;

   class RequestedConverterInterface
   {
   public:
      RequestedConverterInterface(const ITemperatureVoltageConverter &converter);

      double convertmvToK(double millivolts) const;
      double convertKtomV(double kelvin) const;

   private:
      const ITemperatureVoltageConverter &converter_;
   };
}