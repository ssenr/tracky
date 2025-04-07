#pragma once

#include <iostream>
#include <string>
#include <fstream>

#define CROW_DISABLE_JSON      // disables Crow's conflicting JSON
#include <crow.h>           // or "crow.h" if using modular
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
