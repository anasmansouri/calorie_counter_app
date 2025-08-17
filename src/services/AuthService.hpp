#pragma once
#include <string>
#include "utils/Result.hpp"

namespace cc::services {
// for later , no need to implementet now 
class AuthService {
public:
  void setJwtSecret(std::string secret);
  cc::utils::Result<std::string> issueToken(const std::string& userId, int ttlSeconds);
  cc::utils::Result<std::string> verifyToken(const std::string& token); // returns userId

private:
  std::string secret_;
};

} // namespace cc::services
