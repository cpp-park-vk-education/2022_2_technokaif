#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <boost/asio.hpp>
#include "json.hpp"


enum RunStatus {
    TOTAL,
    OPTIONAL,
    STOPPED
};

struct VPNContext {
    RunStatus state;
    std::vector<std::string> urlList;
};

#endif  // _UTILS_H_
