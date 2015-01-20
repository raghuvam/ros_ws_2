#ifndef __IPNC_CLIENT_H_
#define __IPNC_CLIENT_H_

namespace IPNC {

    int capture(const char *IPaddress, int PortNo, char *image); //captures RAW image
    void closeIPNC();

}

#endif
