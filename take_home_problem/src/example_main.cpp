#include <stdlib.h>

#include <vector>

#include "calibration_point_file.h"
#include "result_code_enum.h"
#include "temperature_voltage_converter.h"

using namespace TakeHomeProblem;

int main(int argc, char** argv)
{
   int result = EXIT_SUCCESS;

   if (argc == 2)
   {
      std::vector<CalibrationPoint> calibration_points;
      if (CalibrationPointFile::LoadCalibrationPoints(argv[1], calibration_points) == ResultCode::Success)
      {
         TemperatureVoltageConverter converter(calibration_points);

         // ... do something with converter ...
      }
      else
      {
         std::cerr << "Unable to open calibration points file (File: " << argv[1] << ")" << std::endl;
         result = EXIT_FAILURE;
      }
   }
   else
   {
      std::cerr << "Provide calibration points file" << std::endl;
      result = EXIT_FAILURE;
   }

   return result;
}