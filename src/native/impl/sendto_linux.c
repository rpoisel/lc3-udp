#include <lcfu___sendto.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*                            Functions                        */
void  lcfu___SENDTO(LC_TD_Function_SENDTO* LC_this, LC_TD_BYTE (* LC_VD_BUF), LC_TD_UDINT LC_VD_BUFLEN, LC_TD_DataType_UDPENDPOINT LC_VD_DST, struct _lcoplck_epdb_1_impl* pEPDB)
{
    struct sockaddr_in host;
    int udp_socket;

    host.sin_family = AF_INET;
    host.sin_port = htons(LC_VD_DST.LC_VD_PORT);
    host.sin_addr.s_addr = inet_addr(LC_VD_DST.LC_VD_HOST);
    int success = (INADDR_NONE != host.sin_addr.s_addr);
    if (!success)
    {
        LC_this->LC_VD_SENDTO = -1;
        LC_this->LC_VD_ENO = LC_EL_false;
        return;
    }
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    success = udp_socket >= 0;
    if (!success)
    {
        LC_this->LC_VD_SENDTO = -2;
        LC_this->LC_VD_ENO = LC_EL_false;
        return;
    }
    LC_this->LC_VD_SENDTO = sendto(udp_socket, LC_VD_BUF, LC_VD_BUFLEN, 0, (struct sockaddr*) &host, sizeof(host));
    close(udp_socket);

    if (LC_this->LC_VD_SENDTO == -1)
    {
        LC_this->LC_VD_ENO = LC_EL_false;
    }
}
