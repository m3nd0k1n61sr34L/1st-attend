#include <iostream>
#include <fstream>
#include <string>
#include <Winsock2.h>
#include <WS2tcpip.h>
#include <array>
#include <optional>
#include <system_error>

#pragma comment(lib, "Ws2_32.lib")

std::optional<std::string> getHostnameFromIP(const std::string& ipAddress)
{
    WSADATA data;
    WORD version = MAKEWORD(2, 2);
    if (WSAStartup(version, &data) != 0)
    {
        std::cerr << "Failed to initialize Winsock. Error code: " << WSAGetLastError() << std::endl;
        return std::nullopt;
    }

    addrinfo hints{}, *res = nullptr;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(ipAddress.c_str(), nullptr, &hints, &res) != 0)
    {
        std::cerr << "Failed to get address info for IP: " << ipAddress << ". Error code: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return std::nullopt;
    }

    char host[NI_MAXHOST];
    DWORD size = NI_MAXHOST;
    if (getnameinfo(res->ai_addr, res->ai_addrlen, host, size, nullptr, 0, NI_NAMEREQD) != 0)
    {
        std::cerr << "Failed to get hostname. Error code: " << WSAGetLastError() << std::endl;
        freeaddrinfo(res);
        WSACleanup();
        return std::nullopt;
    }

    std::string hostname(host);
    freeaddrinfo(res);
    WSACleanup();
    return hostname;
}

void saveIPAndHostnameToFile(const std::string& ipAddress, const std::string& hostname)
{
    std::ofstream outFile("ip_hostname.txt", std::ios_base::app);
    if (outFile)
    {
        outFile << ipAddress << " " << hostname << std::endl;
        outFile.close();
    }
    else
    {
        std::cerr << "Failed to open the file for saving IP and hostname." << std::endl;
    }
}

int main()
{
    std::string ipAddress;
    std::cout << "Enter IP address: ";
    std::cin >> ipAddress;

    std::optional<std::string> hostname = getHostnameFromIP(ipAddress);
    if (hostname)
    {
        std::cout << "Hostname: " << *hostname << std::endl;
        saveIPAndHostnameToFile(ipAddress, *hostname);
    }
    else
    {
        std::cout << "Failed to get the hostname for the given IP address." << std::endl;
    }

    return 0;
}
