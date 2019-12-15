#pragma once

namespace TakeHomeProblem
{
   class ITemperatureVoltageConverter;

   class TakeHomeExample
   {
   public:
      TakeHomeExample(ITemperatureVoltageConverter converter);

      double convertmvToK(double millivolts) const;
      double convertKtomV(double kelvin) const;

   private:
      ITemperatureVoltageConverter &converter_;
   };
}