#include <iostream>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <sstream>

struct ClearDisplayCommand {
    uint16_t color;
};

struct DrawPixelCommand {
    int16_t x;
    int16_t y;
    uint16_t color;
};

struct DrawLineCommand {
    int16_t x0;
    int16_t y0;
    int16_t x1;
    int16_t y1;
    uint16_t color;
};

struct DrawRectangleCommand {
    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;
    uint16_t color;
};

struct FillRectangleCommand {
    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;
    uint16_t color;
};

struct DrawEllipseCommand {
    int16_t x;
    int16_t y;
    int16_t rx;
    int16_t ry;
    uint16_t color;
};

struct FillEllipseCommand {
    int16_t x;
    int16_t y;
    int16_t rx;
    int16_t ry;
    uint16_t color;
};

class DisplayProtocol {
public:
    std::string parseCommand(const std::vector<uint8_t>& byteArray) {
        if (byteArray.empty()) {
            throw std::invalid_argument("Empty byte array");
        }

        uint8_t opcode = byteArray[0];

        switch (opcode) {
        case 0x01: 
            return clearDisplay(byteArray);
        case 0x02: 
            return drawPixel(byteArray);
        case 0x03: 
            return drawLine(byteArray);
        case 0x04: 
            return drawRectangle(byteArray);
        case 0x05: 
            return fillRectangle(byteArray);
        case 0x06: 
            return drawEllipse(byteArray);
        case 0x07: 
            return fillEllipse(byteArray);
            
        default:
            throw std::invalid_argument("Unknown command opcode");
        }
    }

private:
    std::string clearDisplay(const std::vector<uint8_t>& params) {
        if (params.size() < 3) {
            throw std::invalid_argument("Invalid parameters for clear display");
        }

        std::string color = parseColor(params, 1);
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
        std::string color = parseColor(params, 5);

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
        std::string color = parseColor(params, 9);

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
        std::string color = parseColor(params, 9);

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
        std::string color = parseColor(params, 9);

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
        std::string color = parseColor(params, 9);

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
        std::string color = parseColor(params, 9);

        std::ostringstream result;
        result << "Filling ellipse centered at (" << x0 << ", " << y0 << ") with radii (" << rx << ", " << ry << ") and color " << color;
        return result.str();
    }

    int16_t parseInt16(const std::vector<uint8_t>& data, size_t offset) {
        return (data[offset + 1] << 8) | data[offset];
    }

    std::string parseColor(const std::vector<uint8_t>& data, size_t offset) {
        std::ostringstream result;
        result << "RGB565(" << std::hex << (int)data[offset] << (int)data[offset + 1] << ")";
        return result.str();
    }
};
int main() {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { 0x01, 0xF8, 0x00 };
    try {
        std::string result = protocol.parseCommand(command);
        std::cout << result << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
