#include <iostream>
#include <vector>
#include <cstdint>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "../display_protocol/display_protocol.h"
#include <string>


#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 777
#define SERVER_IP "127.0.0.1"  

std::string getCommandName(CommandOpcode opcode) {
    switch (opcode) {
    case CLEAR_DISPLAY_OPCODE: return "CLEAR_DISPLAY";
    case DRAW_PIXEL_OPCODE: return "DRAW_PIXEL";
    case DRAW_LINE_OPCODE: return "DRAW_LINE";
    case DRAW_RECTANGLE_OPCODE: return "DRAW_RECTANGLE";
    case FILL_RECTANGLE_OPCODE: return "FILL_RECTANGLE";
    case DRAW_ELLIPSE_OPCODE: return "DRAW_ELLIPSE";
    case FILL_ELLIPSE_OPCODE: return "FILL_ELLIPSE";
    default: return "UNKNOWN_COMMAND";
    }
}


std::string getParametersString(const std::vector<uint8_t>& command) {
    std::string params;
    for (size_t i = 1; i < command.size(); ++i) { 
        params += "0x" + std::to_string(command[i]);
        if (i < command.size() - 1) {
            params += ", "; 
        }
    }
    return params;
}

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;

   
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return 1;
    }

    
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

   
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

   
    std::vector<std::vector<uint8_t>> commandBytes = {
        { CLEAR_DISPLAY_OPCODE, 0xFF, 0xFF },
        { DRAW_PIXEL_OPCODE, 0x00, 0x10, 0x00, 0x20, 0xAA, 0xBB },
        { DRAW_LINE_OPCODE, 0x00, 0x10, 0x00, 0x20, 0x00, 0x30, 0x00, 0x40, 0xCC, 0xDD },
        { DRAW_RECTANGLE_OPCODE, 0x00, 0x05, 0x00, 0x10, 0x00, 0x15, 0x00, 0x20, 0xEE, 0xFF },
        { FILL_RECTANGLE_OPCODE, 0x00, 0x05, 0x00, 0x10, 0x00, 0x15, 0x00, 0x20, 0x11, 0x22 },
        { DRAW_ELLIPSE_OPCODE, 0x00, 0x08, 0x00, 0x12, 0x00, 0x09, 0x00, 0x07, 0x33, 0x44 },
        { FILL_ELLIPSE_OPCODE, 0x00, 0x06, 0x00, 0x11, 0x00, 0x05, 0x00, 0x04, 1 },
    };

    for (const auto& command : commandBytes) {
        CommandOpcode opcode = static_cast<CommandOpcode>(command[0]);
        int sentBytes = sendto(clientSocket, reinterpret_cast<const char*>(command.data()), command.size(), 0,
            (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        if (sentBytes == SOCKET_ERROR) {
            std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
            continue;
        }

        
        std::cout << "Sent command: " << getCommandName(opcode)
            << ", parameters: " << getParametersString(command)
            << ", size: " << sentBytes << " bytes" << std::endl;
    }

    
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
