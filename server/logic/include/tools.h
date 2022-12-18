#pragma once

#include <iostream>
#include <vector>
#include <string>

enum VPNMode {
    TOTAL,
    OPTIONAL
};

enum RunStatus {
    RUNNING,
    STOPPED
};

struct VPNContext {
    VPNMode mode;
    RunStatus state;
    std::vector<std::string> urlList;
};

/* example
{
    "state" : runOptional,
    "urlList" : [
        "google.com,
        "https://google.com"
    ]
}

Serialization:

VPNContext context = {runTotal, {"google.com", "https://google.com"}}
nlohmann::json j{};
j["state"] = context.state;
j["urlList"] = context.urlList;

*/

struct OptionalUrl {
    std::string url;
    std::vector<std::string> ipList;
};
