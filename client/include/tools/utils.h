#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <boost/asio.hpp>
#include "json.hpp"


enum RunStatus {
    RUNNING,
    STOPPED
};

enum VPNMode {
    TOTAL,
    OPTIONAL
};

enum VPNServer {
    NETHERLANDS,
    RUSSIA
};

struct VPNContext {
    RunStatus state;
    VPNMode mode;
    std::vector<std::string> urlList;
};

#endif  // _UTILS_H_
