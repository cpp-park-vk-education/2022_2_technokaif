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
    std::vector<std::string> ipList;
};

struct OptionalUrl {
    std::string url;
    std::vector<std::string> ipList;
};
