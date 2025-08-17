#pragma once
#include <string>
#include <optional>
#include "utils/Result.hpp"

namespace cc::services {
// implement later 
class UserService {
public:
  cc::utils::Result<void> createUser(const std::string& userId);
  cc::utils::Result<void> setPreference(const std::string& userId, const std::string& key, const std::string& value);
  cc::utils::Result<std::optional<std::string>> getPreference(const std::string& userId, const std::string& key);
};

} // namespace cc::services