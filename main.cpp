#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <fstream>

#include <vector>
#include <iomanip>

#include <nlohmann/json.hpp>

#include "data-point.h"

using namespace units::literals;

bool readDataPoints(const std::string &filename, std::vector<ValueConvert::DataPoint> &dataPoints)
{
   bool success = true;

   try
   {
      std::ifstream dataPointsFile(filename);
      if (dataPointsFile.good())
      {
         nlohmann::json json;

         dataPointsFile >> json;
         dataPointsFile.close();

         std::vector<ValueConvert::DataPoint> dataPoints;
         json.at("dataPoints").get_to(dataPoints);
      }
      else
      {
         std::cerr << "Unable to open data points file (File: " << filename << ")" << std::endl;
         success = false;
      }
   }
   catch(const nlohmann::detail::exception& e)
   {
      std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
      success = false;
   }

   return success;
}

int main(int argc, char** argv)
{
   int result = EXIT_SUCCESS;

   if (argc == 2)
   {
      std::vector<ValueConvert::DataPoint> dataPoints;

      if (readDataPoints(argv[1], dataPoints))
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
