#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <boost/asio.hpp>

enum VPNMode {
    runTotal,
    runOptional,
    stopped
};

struct VPNContext {
    VPNMode state;
    std::vector<std::string> urlList; 
};