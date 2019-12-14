#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <fstream>

#include <vector>
#include <iomanip>

#include <nlohmann/json.hpp>

#include "DataPoint.h"
#include "ResultCodeEnum.h"

using namespace TakeHomeProblem;
using namespace units::literals;

ResultCode readDataPoints(const std::string &filename, std::vector<DataPoint> &dataPoints)
{
   ResultCode result = ResultCode::Success;

   try
   {
      std::ifstream dataPointsFile(filename);
      if (dataPointsFile.good())
      {
         nlohmann::json json;

         dataPointsFile >> json;
         dataPointsFile.close();

         json.at("dataPoints").get_to(dataPoints);
      }
      else
      {
         std::cerr << "Unable to open data points file (File: " << filename << ")" << std::endl;
         result = ResultCode::Error;
      }
   }
   catch(const nlohmann::detail::exception& e)
   {
      std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
      result = ResultCode::Error;
   }

   return result;
}

int main(int argc, char** argv)
{
   int result = EXIT_SUCCESS;

   if (argc == 2)
   {
      std::vector<DataPoint> dataPoints;

      if (readDataPoints(argv[1], dataPoints) == ResultCode::Success)
      {
      }
      else
      {
         std::cerr << "Unable to open data points file (File: " << argv[1] << ")" << std::endl;
         result = EXIT_FAILURE;
      }
   }
   else
   {
      std::cerr << "Provide data points file" << std::endl;
      result = EXIT_FAILURE;
   }

   return result;
}
