#include <algorithm>
#include <charconv>
#include <chrono>
#include <ciarcpp/types.hpp>
#include <cmath>
#include <cstring>
#include <iostream>

#include <ciarcpp/api.hpp>
#include <ostream>
#include <system_error>
#include <thread>

using namespace std::chrono_literals;
using namespace ciarcpp;

static inline double parse_freq(const char* arg) {
  double freq;

  // Parse string
  std::string_view sv = std::string_view(arg);
  std::from_chars_result r = std::from_chars(sv.data(), sv.data() + sv.size(), freq);
  if (r.ec != std::errc{}) {
    std::cerr << "While parsing frequency: " << std::generic_category().message((int)r.ec) << std::endl;
    exit(1);
    return NAN;
  }

  // Validate
  if (freq <= 0) {
    std::cerr << "Frequency must be > 0." << std::endl;
    exit(1);
    return NAN;
  }

  return freq;
}

void serialize_record(const ciarcpp::Observation& obs, const std::string& png_data, std::string& buffer);

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " base_url frequency";
    return 1;
  }

  const char* base_url = argv[1];
  std::chrono::nanoseconds interval = std::chrono::duration_cast<std::chrono::nanoseconds>(
    std::chrono::duration<double>(1.0 / parse_freq(argv[2]))
  );
  

  std::string buffer;
  buffer.reserve(1024 * 1024);

  std::optional<std::pair<int, int>> old_position;

  while (true) {
    // Tick start time
    auto tick_t = std::chrono::system_clock::now();

    // Download the observation from the API
    auto obs = ciarcpp::sync::get_observation(base_url);

    std::pair<int, int> position(obs.width_x, obs.height_y);

    // Was the observation updated?
    if (position != old_position) {
      std::string png = ciarcpp::sync::get_image(base_url);

      std::cerr << "Observation " << obs.timestamp.time_since_epoch() << std::endl;
      serialize_record(obs, png, buffer);
      std::cout << buffer << std::endl;

      old_position = position;
    }

    std::cerr << "Tick " << tick_t.time_since_epoch() << std::endl;
    std::this_thread::sleep_until(tick_t + interval);
  }
}