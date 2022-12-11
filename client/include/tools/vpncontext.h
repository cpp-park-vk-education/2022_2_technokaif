#ifndef VPNCONTEXT_H
#define VPNCONTEXT_H

#include "utils.h"

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

#endif  // VPNCONTEXT_H
