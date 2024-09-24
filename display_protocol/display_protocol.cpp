#include <iostream>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <sstream>


enum CommandOpcode {
    CLEAR_DISPLAY_OPCODE,
    DRAW_PIXEL_OPCODE
};


struct Command {
    const CommandOpcode opcode;

    Command(const CommandOpcode opcode) : opcode(opcode) {};
};
struct ClearDisplay : Command {
    const uint16_t color;

    ClearDisplay(const uint16_t color) : Command(CLEAR_DISPLAY_OPCODE), color(color) {};
};

struct DrawPixel : Command {
    const int16_t x0;
    const int16_t y0;
    const uint16_t color;

    DrawPixel(const int16_t x0, const int16_t y0, const uint16_t color) :
        Command(DRAW_PIXEL_OPCODE), x0(x0), y0(y0), color(color) {};
};

struct DrawLine {
    int16_t x0;
    int16_t y0;
    int16_t x1;
    int16_t y1;
    uint16_t color;
};

struct DrawRectangle {
    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;
    uint16_t color;
};

struct FillRectangle {
    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;
    uint16_t color;
};

struct DrawEllipse {
    int16_t x;
    int16_t y;
    int16_t rx;
    int16_t ry;
    uint16_t color;
};

struct FillEllipse {
    int16_t x;
    int16_t y;
    int16_t rx;
    int16_t ry;
    uint16_t color;
};

class DisplayProtocol {
public:
    void parseCommand(const std::vector<uint8_t>& byteArray, Command*& command) {
        if (byteArray.empty()) {
            throw std::invalid_argument("Empty byte array");
        }
       //Зробив як в першому варіанті 
        uint8_t opcode = byteArray[0]; 
        switch (opcode) {
        
        case CLEAR_DISPLAY_OPCODE: {
            if (byteArray.size() < 3) {
                throw std::invalid_argument("Invalid parameters for clear display");
            }
            uint16_t color = parseColor(byteArray, 1);
            command = new ClearDisplay(color);
            break;
        }
        case DRAW_PIXEL_OPCODE: {
            if (byteArray.size() < 7) {
                throw std::invalid_argument("Invalid parameters for draw pixel");
            }
            int16_t x0 = parseInt16(byteArray, 1);
            int16_t y0 = parseInt16(byteArray, 3);
            uint16_t color = parseColor(byteArray, 5);
            command = new DrawPixel(x0, y0, color);
            break;
        }
        default:
            throw std::invalid_argument("Unknown command opcode");
        }
    }

private:
    //Видалив зайві функції
    int16_t parseInt16(const std::vector<uint8_t>& data, size_t offset) {
        return (data[offset + 1] << 8) | data[offset];
    }

    uint16_t parseColor(const std::vector<uint8_t>& data, size_t offset) {
        if (offset + 1 >= data.size()) {
            return 0;  
        }

        
        uint16_t color = (data[offset] << 8) | data[offset + 1];

        return color;
    }
};
int main() {
    DisplayProtocol protocol;
    std::vector<uint8_t> commandBytes = { 0x00, 0xFF, 0xFF };
    Command* command = nullptr; 

    try {
        protocol.parseCommand(commandBytes, command);

       
        if (command) {
          
            if (command->opcode == CLEAR_DISPLAY_OPCODE) {
                ClearDisplay* clearCommand = static_cast<ClearDisplay*>(command);
                std::cout << "Clearing display with color: " << clearCommand->color << std::endl;
            }
            
            delete command;
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

