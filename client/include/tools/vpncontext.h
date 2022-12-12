#ifndef VPNCONTEXT_H
#define VPNCONTEXT_H

#include "utils.h"

enum RunStatus {
    TOTAL,
    OPTIONAL,
    STOPPED
};

struct VPNContext {
    VPNMode mode;
    RunStatus state;
    std::vector<std::string> urlList;
};

#endif  // VPNCONTEXT_H
