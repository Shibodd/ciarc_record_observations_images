#include <glaze/glaze.hpp>
#include <ciarcpp/types.hpp>

#ifndef CIARCPP_PARSE_ENUMMETAS_HPP
#define CIARCPP_PARSE_ENUMMETAS_HPP

template <>
struct glz::meta<ciarcpp::MelvinState> {
  using enum ciarcpp::MelvinState;
  static constexpr auto value = enumerate(
    "deployment", Deployment,
    "charge", Charge,
    "acquisition", Acquisition,
    "communication", Communication,
    "safe", Safe,
    "transition", Transition,
    "none", None
  );
};

template <>
struct glz::meta<ciarcpp::CameraAngle> {
  using enum ciarcpp::CameraAngle;
  static constexpr auto value = enumerate(
    "narrow", Narrow,
    "normal", Normal,
    "wide", Wide
  );
};

#endif // !CIARCPP_PARSE_ENUMMETAS_HPP