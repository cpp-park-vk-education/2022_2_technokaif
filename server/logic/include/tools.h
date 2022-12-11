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

struct OptionalUrl {
    std::string url;
    std::vector<std::string> ipList;
};
