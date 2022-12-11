#ifndef VPNCONTEXT_H
#define VPNCONTEXT_H

enum VPNMode {
    TOTAL,
    OPTIONAL
};

enum RunStatus {
    RUNNING,
    STOPPED
};

struct VPNContext {
    VPNMode state;
    std::vector<std::string> urlList;
};

#endif  // VPNCONTEXT_H
