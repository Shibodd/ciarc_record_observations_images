#include <ciarcpp/types.hpp>
#include <glaze/glaze.hpp>
#include "base64.hpp"

#include "enum_metas.hpp"

#include "record.hpp"

namespace glz::detail {

template<>
struct to<JSON, std::chrono::system_clock::time_point> {
  template <auto Opts, is_context Ctx, class... Args>
  static void op(std::chrono::system_clock::time_point& value, Ctx&& ctx, Args&&... args) {
    write<JSON>::op<Opts>(value.time_since_epoch().count(), std::forward<Ctx>(ctx), std::forward<Args>(args)...);
  }
};

} // namespace glz::detail

void serialize_record(const ciarcpp::Observation& obs, const std::string& png_data, std::string& buffer) {
  LogRecord record(obs, base64::to_base64(png_data));

  glz::error_ctx err = glz::write_json(std::move(record), buffer);
  assert(!bool(err));
}