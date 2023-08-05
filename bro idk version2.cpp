#include <iostream>
#include <fstream>
#include <string>
#include <Winsock2.h>
#include <WS2tcpip.h>
#include <array>
#include <optional>
#include <system_error>
#include <windows.h>  // For Sleep

#pragma comment(lib, "Ws2_32.lib")

// Function to print text with a delay
void slowType(const std::string& text, double delayInSeconds)
{
    for (const char c : text)
    {
        std::cout << c << std::flush;
        Sleep(static_cast<DWORD>(delayInSeconds * 1000));
    }
}

std::optional<std::string> getHostnameFromIP(const std::string& ipAddress)
{
    // ... (The existing code for getHostnameFromIP remains unchanged.)
}

void saveIPAndHostnameToFile(const std::string& ipAddress, const std::string& hostname)
{
    // ... (The existing code for saveIPAndHostnameToFile remains unchanged.)
}

int main()
{
    // Print the title card
    slowType(" ****     **** ******** ****     ** *******     *******  \n"
             "/**/**   **/**/**///// /**/**   /**/**////**   **/////** \n"
             "/**//** ** /**/**      /**//**  /**/**    /** **     /**\n"
             "/** //***  /**/******* /** //** /**/**    /**/**      /**\n"
             "/**  //*   /**/**////  /**  //**/**/**    /**/**      /**\n"
             "/**   /    /**/**      /**   //****/**    ** //**     ** \n"
             "/**        /**/********/**    //***/*******   //*******  \n"
             "//         // //////// //      /// ///////     ///////   \n", 0.02);

    Sleep(2000);  // Wait a few seconds

    // Print the owner name
    slowType("Owner: mendo\n", 0.02);

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
