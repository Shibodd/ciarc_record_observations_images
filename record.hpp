#include <ciarcpp/types.hpp>

struct LogRecord {
  ciarcpp::Observation observation;
  std::string png_base64;

  // LogRecord(const ciarcpp::Observation& observation, std::string&& png_base64) : observation(observation), png_base64(png_base64) {}
};