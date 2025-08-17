#pragma once
#include <string>
#include <vector>
#include <utility>
#include <curl/curl.h>
#include "utils/Result.hpp"

namespace cc::utils {

class HttpClient {
public:
  Result<std::string> get(
    const std::string& url,
    const std::vector<std::pair<std::string,std::string>>& headers = {}
  );

  Result<std::string> getJson(const std::string& url);

  void setTimeoutMs(int ms);
  void setUserAgents(const std::string& ua);

private:
  int timeoutMs_ = 10000;
  std::string userAgent_ = "CalorieCounter/1.0 (+https://example.com; anas@example.com)";
};

} // namespace cc::utils
