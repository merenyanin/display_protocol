#include <iostream>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <sstream>


enum CommandOpcode {
    CLEAR_DISPLAY_OPCODE,
    DRAW_PIXEL_OPCODE,
    DRAW_LINE_OPCODE,
    DRAW_RECTANGLE_OPCODE,
    FILL_RECTANGLE_OPCODE,
    DRAW_ELLIPSE_OPCODE,
    FILL_ELLIPSE_OPCODE
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

struct DrawLine : Command {
    const int16_t x0;
    const int16_t y0;
    const int16_t x1;
    const int16_t y1;
    const uint16_t color;

    DrawLine(const int16_t x0, const int16_t y0, const int16_t x1, const int16_t y1, const uint16_t color) :
        Command(DRAW_LINE_OPCODE), x0(x0), y0(y0), x1(x1), y1(y1), color(color) {};
};

struct DrawRectangle : Command {
    const int16_t x;
    const int16_t y;
    const int16_t width;
    const int16_t height;
    const uint16_t color;

    DrawRectangle(const int16_t x, const int16_t y, const int16_t width, const int16_t height, const uint16_t color) :
        Command(DRAW_RECTANGLE_OPCODE), x(x), y(y), width(width), height(height), color(color) {};
};

struct FillRectangle : Command {
    const int16_t x;
    const int16_t y;
    const int16_t width;
    const int16_t height;
    const uint16_t color;

    FillRectangle(const int16_t x, const int16_t y, const int16_t width, const int16_t height, const uint16_t color) :
        Command(FILL_RECTANGLE_OPCODE), x(x), y(y), width(width), height(height), color(color) {};
};

struct DrawEllipse : Command {
    const int16_t x;
    const int16_t y;
    const int16_t rx;
    const int16_t ry;
    const uint16_t color;

    DrawEllipse(const int16_t x, const int16_t y, const int16_t rx, const int16_t ry, const uint16_t color) :
        Command(DRAW_ELLIPSE_OPCODE), x(x), y(y), rx(rx), ry(ry), color(color) {};
};

struct FillEllipse : Command {
    const int16_t x;
    const int16_t y;
    const int16_t rx;
    const int16_t ry;
    const uint16_t color;

    FillEllipse(const int16_t x, const int16_t y, const int16_t rx, const int16_t ry, const uint16_t color) :
        Command(FILL_ELLIPSE_OPCODE), x(x), y(y), rx(rx), ry(ry), color(color) {};
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
        case DRAW_LINE_OPCODE: {
            if (byteArray.size() < 11) {
                throw std::invalid_argument("Invalid parameters for draw line");
            }
            int16_t x0 = parseInt16(byteArray, 1);
            int16_t y0 = parseInt16(byteArray, 3);
            int16_t x1 = parseInt16(byteArray, 5);
            int16_t y1 = parseInt16(byteArray, 7);
            uint16_t color = parseColor(byteArray, 9);
            command = new DrawLine(x0, y0, x1, y1, color);
            break;
        }
        case DRAW_RECTANGLE_OPCODE: {
            if (byteArray.size() < 11) {
                throw std::invalid_argument("Invalid parameters for draw rectangle");
            }
            int16_t x = parseInt16(byteArray, 1);
            int16_t y = parseInt16(byteArray, 3);
            int16_t width = parseInt16(byteArray, 5);
            int16_t height = parseInt16(byteArray, 7);
            uint16_t color = parseColor(byteArray, 9);
            command = new DrawRectangle(x, y, width, height, color);
            break;
        }
        case FILL_RECTANGLE_OPCODE: {
            if (byteArray.size() < 11) {
                throw std::invalid_argument("Invalid parameters for fill rectangle");
            }
            int16_t x = parseInt16(byteArray, 1);
            int16_t y = parseInt16(byteArray, 3);
            int16_t width = parseInt16(byteArray, 5);
            int16_t height = parseInt16(byteArray, 7);
            uint16_t color = parseColor(byteArray, 9);
            command = new FillRectangle(x, y, width, height, color);
            break;
        }
        case DRAW_ELLIPSE_OPCODE: {
            if (byteArray.size() < 11) {
                throw std::invalid_argument("Invalid parameters for draw ellipse");
            }
            int16_t x = parseInt16(byteArray, 1);
            int16_t y = parseInt16(byteArray, 3);
            int16_t rx = parseInt16(byteArray, 5);
            int16_t ry = parseInt16(byteArray, 7);
            uint16_t color = parseColor(byteArray, 9);
            command = new DrawEllipse(x, y, rx, ry, color);
            break;
        }
        case FILL_ELLIPSE_OPCODE: {
            if (byteArray.size() < 11) {
                throw std::invalid_argument("Invalid parameters for fill ellipse");
            }
            int16_t x = parseInt16(byteArray, 1);
            int16_t y = parseInt16(byteArray, 3);
            int16_t rx = parseInt16(byteArray, 5);
            int16_t ry = parseInt16(byteArray, 7);
            uint16_t color = parseColor(byteArray, 9);
            command = new FillEllipse(x, y, rx, ry, color);
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

    std::vector<uint8_t> commandBytes[] = {
        { CLEAR_DISPLAY_OPCODE, 0xFF, 0xFF },
        { DRAW_PIXEL_OPCODE, 0x00, 0x10, 0x00, 0x20, 0xAA, 0xBB },
        { DRAW_LINE_OPCODE, 0x00, 0x10, 0x00, 0x20, 0x00, 0x30, 0x00, 0x40, 0xCC, 0xDD },
        { DRAW_RECTANGLE_OPCODE, 0x00, 0x05, 0x00, 0x10, 0x00, 0x15, 0x00, 0x20, 0xEE, 0xFF },
        { FILL_RECTANGLE_OPCODE, 0x00, 0x05, 0x00, 0x10, 0x00, 0x15, 0x00, 0x20, 0x11, 0x22 },
        { DRAW_ELLIPSE_OPCODE, 0x00, 0x08, 0x00, 0x12, 0x00, 0x09, 0x00, 0x07, 0x33, 0x44 },
        { FILL_ELLIPSE_OPCODE, 0x00, 0x06, 0x00, 0x11, 0x00, 0x05, 0x00, 0x04, 0x55, 0x66 }
    };

    for (const auto& commandBytes : commandBytes) {
        Command* command = nullptr;

        try {
            protocol.parseCommand(commandBytes, command);

            if (command) {
                switch (command->opcode) {
                    case CLEAR_DISPLAY_OPCODE: {
                        ClearDisplay* clearCommand = static_cast<ClearDisplay*>(command);
                        std::cout << "Clearing display with color: " << clearCommand->color << std::endl;
                        break;
                    }
                    case DRAW_PIXEL_OPCODE: {
                        DrawPixel* drawPixelCommand = static_cast<DrawPixel*>(command);
                        std::cout << "Drawing pixel at (" << drawPixelCommand->x0 << ", " << drawPixelCommand->y0 << ") with color: " << drawPixelCommand->color << std::endl;
                        break;
                    }
                    case DRAW_LINE_OPCODE: {
                        DrawLine* drawLineCommand = static_cast<DrawLine*>(command);
                        std::cout << "Drawing line from (" << drawLineCommand->x0 << ", " << drawLineCommand->y0 << ") to (" << drawLineCommand->x1 << ", " << drawLineCommand->y1 << ") with color: " << drawLineCommand->color << std::endl;
                        break;
                    }
                    case DRAW_RECTANGLE_OPCODE: {
                        DrawRectangle* drawRectCommand = static_cast<DrawRectangle*>(command);
                        std::cout << "Drawing rectangle at (" << drawRectCommand->x << ", " << drawRectCommand->y << ") with width: " << drawRectCommand->width << " and height: " << drawRectCommand->height << " with color: " << drawRectCommand->color << std::endl;
                        break;
                    }
                    case FILL_RECTANGLE_OPCODE: {
                        FillRectangle* fillRectCommand = static_cast<FillRectangle*>(command);
                        std::cout << "Filling rectangle at (" << fillRectCommand->x << ", " << fillRectCommand->y << ") with width: " << fillRectCommand->width << " and height: " << fillRectCommand->height << " with color: " << fillRectCommand->color << std::endl;
                        break;
                    }
                    case DRAW_ELLIPSE_OPCODE: {
                        DrawEllipse* drawEllipseCommand = static_cast<DrawEllipse*>(command);
                        std::cout << "Drawing ellipse at (" << drawEllipseCommand->x << ", " << drawEllipseCommand->y << ") with radius x: " << drawEllipseCommand->rx << " and radius y: " << drawEllipseCommand->ry << " with color: " << drawEllipseCommand->color << std::endl;
                        break;
                    }
                    case FILL_ELLIPSE_OPCODE: {
                        FillEllipse* fillEllipseCommand = static_cast<FillEllipse*>(command);
                        std::cout << "Filling ellipse at (" << fillEllipseCommand->x << ", " << fillEllipseCommand->y << ") with radius x: " << fillEllipseCommand->rx << " and radius y: " << fillEllipseCommand->ry << " with color: " << fillEllipseCommand->color << std::endl;
                        break;
                    }
                    default:
                        std::cerr << "Unknown command opcode: " << command->opcode << std::endl;
                        break;
                }

                delete command;
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}


