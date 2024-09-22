#include <iostream>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <sstream>

enum CommandOpcode {
    CLEAR_COMMAND_OPCODE = 0x01,
    DRAW_PIXEL_OPCODE = 0x02,
};

struct Command {
    uint8_t opcode;
   
};
struct ClearDisplay {
    uint16_t color;
};

struct DrawPixel {
    int16_t x;
    int16_t y;
    uint16_t color;
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
    void parseCommand(const std::vector<uint8_t>& byteArray, Command* command) {
        if (byteArray.empty()) {
            throw std::invalid_argument("Empty byte array");
        }

        command->opcode = byteArray[0];

        switch (command->opcode) {
        case CLEAR_COMMAND_OPCODE:
            clearDisplay(byteArray);
            break;
        case DRAW_PIXEL_OPCODE:
            drawPixel(byteArray);
            break;
        default:
            throw std::invalid_argument("Unknown command opcode");
        }
    }

private:
    std::string clearDisplay(const std::vector<uint8_t>& params) {
        if (params.size() < 3) {
            throw std::invalid_argument("Invalid parameters for clear display");
        }

        uint16_t color = parseColor(params, 1);
        std::ostringstream result;
        result << "Clearing display with color: " << color;
        return result.str();
    }

    std::string drawPixel(const std::vector<uint8_t>& params) {
        if (params.size() < 7) {
            throw std::invalid_argument("Invalid parameters for draw pixel");
        }

        int16_t x0 = parseInt16(params, 1);
        int16_t y0 = parseInt16(params, 3);
        uint16_t color = parseColor(params, 5);

        std::ostringstream result;
        result << "Drawing pixel at (" << x0 << ", " << y0 << ") with color " << color;
        return result.str();
    }

    std::string drawLine(const std::vector<uint8_t>& params) {
        if (params.size() < 11) {
            throw std::invalid_argument("Invalid parameters for draw line");
        }

        int16_t x0 = parseInt16(params, 1);
        int16_t y0 = parseInt16(params, 3);
        int16_t x1 = parseInt16(params, 5);
        int16_t y1 = parseInt16(params, 7);
        uint16_t color = parseColor(params, 9);

        std::ostringstream result;
        result << "Drawing line from (" << x0 << ", " << y0 << ") to (" << x1 << ", " << y1 << ") with color " << color;
        return result.str();
    }

    std::string drawRectangle(const std::vector<uint8_t>& params) {
        if (params.size() < 9) {
            throw std::invalid_argument("Invalid parameters for draw rectangle");
        }

        int16_t x0 = parseInt16(params, 1);
        int16_t y0 = parseInt16(params, 3);
        int16_t w = parseInt16(params, 5);
        int16_t h = parseInt16(params, 7);
        uint16_t color = parseColor(params, 9);

        std::ostringstream result;
        result << "Drawing rectangle at (" << x0 << ", " << y0 << ") with width " << w << " and height " << h << " with color " << color;
        return result.str();
    }

    std::string fillRectangle(const std::vector<uint8_t>& params) {
        if (params.size() < 9) {
            throw std::invalid_argument("Invalid parameters for fill rectangle");
        }

        int16_t x0 = parseInt16(params, 1);
        int16_t y0 = parseInt16(params, 3);
        int16_t w = parseInt16(params, 5);
        int16_t h = parseInt16(params, 7);
        uint16_t color = parseColor(params, 9);

        std::ostringstream result;
        result << "Filling rectangle at (" << x0 << ", " << y0 << ") with width " << w << " and height " << h << " with color " << color;
        return result.str();
    }

    std::string drawEllipse(const std::vector<uint8_t>& params) {
        if (params.size() < 11) {
            throw std::invalid_argument("Invalid parameters for draw ellipse");
        }

        int16_t x0 = parseInt16(params, 1);
        int16_t y0 = parseInt16(params, 3);
        int16_t rx = parseInt16(params, 5); 
        int16_t ry = parseInt16(params, 7); 
        uint16_t color = parseColor(params, 9);

        std::ostringstream result;
        result << "Drawing ellipse centered at (" << x0 << ", " << y0 << ") with radii (" << rx << ", " << ry << ") and color " << color;
        return result.str();
    }

    std::string fillEllipse(const std::vector<uint8_t>& params) {
        if (params.size() < 11) {
            throw std::invalid_argument("Invalid parameters for fill ellipse");
        }

        int16_t x0 = parseInt16(params, 1);
        int16_t y0 = parseInt16(params, 3);
        int16_t rx = parseInt16(params, 5); 
        int16_t ry = parseInt16(params, 7); 
        uint16_t color = parseColor(params, 9);

        std::ostringstream result;
        result << "Filling ellipse centered at (" << x0 << ", " << y0 << ") with radii (" << rx << ", " << ry << ") and color " << color;
        return result.str();
    }

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
    std::vector<uint8_t> commandBytes = { 0x01 }; 
    Command command;

    try {
        protocol.parseCommand(commandBytes, &command);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
