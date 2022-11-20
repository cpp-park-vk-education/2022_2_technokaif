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
