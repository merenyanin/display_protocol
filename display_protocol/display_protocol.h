#pragma once
#ifndef DISPLAY_PROTOCOL_H
#define DISPLAY_PROTOCOL_H

#include <vector>
#include <cstdint>
#include <stdexcept>




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
    virtual ~Command() {}
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
            if (byteArray.size() != 3) {
                throw std::invalid_argument("Invalid parameters for clear display");
            }
            uint16_t color = parseColor(byteArray, 1);
            command = new ClearDisplay(color);
            break;
        }
        case DRAW_PIXEL_OPCODE: {
            if (byteArray.size() != 7) {
                throw std::invalid_argument("Invalid parameters for draw pixel");
            }
            int16_t x0 = parseInt16(byteArray, 1);
            int16_t y0 = parseInt16(byteArray, 3);
            uint16_t color = parseColor(byteArray, 5);
            command = new DrawPixel(x0, y0, color);
            break;
        }
        case DRAW_LINE_OPCODE: {
            if (byteArray.size() != 11) {
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
            if (byteArray.size() != 11) {
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
            if (byteArray.size() != 11) {
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
            if (byteArray.size() != 11) {
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
            if (byteArray.size() != 11) {
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



#endif // DISPLAY_PROTOCOL_H
