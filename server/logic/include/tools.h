#pragma once

#include <iostream>
#include <vector>
#include <string>

enum VPNMode {
    runTotal,
    runOptional,
    stopped
};

struct VPNContext {
    VPNMode state;
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
