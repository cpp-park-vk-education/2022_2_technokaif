#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <boost/asio.hpp>
#include "json.hpp"

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

#endif  // _UTILS_H_
