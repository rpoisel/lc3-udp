#include <lcfu___sendto.h>

#include <winsock2.h>

/*                            Functions                        */
void  lcfu___SENDTO(LC_TD_Function_SENDTO* LC_this, LC_TD_BYTE (* LC_VD_BUF), LC_TD_UDINT LC_VD_BUFLEN, LC_TD_DataType_UDPENDPOINT LC_VD_DST, struct _lcoplck_epdb_1_impl* pEPDB)
{
    int success;
    struct sockaddr_in host;
    static LC_TD_BOOL startedUp = LC_EL_false;
    int udp_socket;

    host.sin_family = AF_INET;
    host.sin_port = htons(LC_VD_DST.LC_VD_PORT);
    host.sin_addr.s_addr = inet_addr(LC_VD_DST.LC_VD_HOST);
    success = (INADDR_NONE != host.sin_addr.s_addr);

    if (!success)
    {
        LC_this->LC_VD_SENDTO = -1;
        LC_this->LC_VD_ENO = LC_EL_false;
        return;
    }

    if (!startedUp)
    {
        WSADATA wsaData;
        WORD wVersionRequested = MAKEWORD(2, 2);

        success = WSAStartup(wVersionRequested, &wsaData) == 0;
        if (!success)
        {
            LC_this->LC_VD_SENDTO = -2;
            LC_this->LC_VD_ENO = LC_EL_false;
            return;
        }
        startedUp = LC_EL_true;
    }

    udp_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    success = udp_socket != INVALID_SOCKET;

    if (!success)
    {
        LC_this->LC_VD_SENDTO = -3;
        LC_this->LC_VD_ENO = LC_EL_false;
        return;
    }

    LC_this->LC_VD_SENDTO = sendto(udp_socket, LC_VD_BUF, LC_VD_BUFLEN, 0, (struct sockaddr*) &host, sizeof(host));
    closesocket(udp_socket);

    if (LC_this->LC_VD_SENDTO == SOCKET_ERROR)
    {
        LC_this->LC_VD_ENO = LC_EL_false;
    }
}
