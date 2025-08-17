#pragma once
#include <memory>
#include <cstdint>

namespace cc::services { class FoodService; }
namespace cc::services { class AuthService; }

namespace cc::api {

class Server {
public:
  Server(int port,
         std::shared_ptr<cc::services::FoodService> service /*,
         std::shared_ptr<cc::services::AuthService> auth = nullptr*/);

  void run();
  void enableCors(bool enable);

private:
  int port_;
  bool cors_ = false;
  std::shared_ptr<cc::services::FoodService> foodService_;
  // std::shared_ptr<cc::services::AuthService> auth_;
};

} // namespace cc::api
