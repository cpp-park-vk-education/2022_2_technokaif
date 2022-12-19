#pragma once

#include "utils.h"

enum VPNMode {
    RunTotal = 1,
    RunOptional,
    Stopped
};

struct VPNContext {
    VPNMode state = VPNMode::RunTotal;
    std::vector<std::string> urlList;
};
