#include "pch.h"
#include <gtest/gtest.h>
#include <vector>
#include "../display_protocol/display_protocol.cpp"

// Тест для ClearDisplay
TEST(DisplayProtocolTest, ClearDisplayCommand) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { CLEAR_DISPLAY_OPCODE, 0xF8, 0x00 };

    EXPECT_NO_THROW({
        std::string result = protocol.parseCommand(command);
        EXPECT_EQ(result, "Clearing display with color: RGB565(f800)");
        });
}

// Тест для DrawPixel
TEST(DisplayProtocolTest, DrawPixelCommand) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { DRAW_PIXEL_OPCODE, 0x00, 0x10, 0x00, 0x20, 0xF8, 0x00 };

    EXPECT_NO_THROW({
        std::string result = protocol.parseCommand(command);
        EXPECT_EQ(result, "Drawing pixel at (16, 32) with color RGB565(f800)");
        });
}

// Тест для DrawLine
TEST(DisplayProtocolTest, DrawLineCommand) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { DRAW_LINE_OPCODE, 0x00, 0x10, 0x00, 0x20, 0x00, 0x30, 0x00, 0x40, 0xF8, 0x00 };

    EXPECT_NO_THROW({
        std::string result = protocol.parseCommand(command);
        EXPECT_EQ(result, "Drawing line from (16, 32) to (48, 64) with color RGB565(f800)");
        });
}

// Тест для DrawRectangle
TEST(DisplayProtocolTest, DrawRectangleCommand) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { DRAW_RECTANGLE_OPCODE, 0x00, 0x05, 0x00, 0x10, 0x00, 0x15, 0x00, 0x20, 0xEE, 0xFF };

    EXPECT_NO_THROW({
        std::string result = protocol.parseCommand(command);
        EXPECT_EQ(result, "Drawing rectangle at (5, 16) with width: 21 and height: 32 with color RGB565(eeff)");
        });
}

// Тест для FillRectangle
TEST(DisplayProtocolTest, FillRectangleCommand) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { FILL_RECTANGLE_OPCODE, 0x00, 0x05, 0x00, 0x10, 0x00, 0x15, 0x00, 0x20, 0x11, 0x22 };

    EXPECT_NO_THROW({
        std::string result = protocol.parseCommand(command);
        EXPECT_EQ(result, "Filling rectangle at (5, 16) with width: 21 and height: 32 with color RGB565(1122)");
        });
}

// Тест для DrawEllipse
TEST(DisplayProtocolTest, DrawEllipseCommand) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { DRAW_ELLIPSE_OPCODE, 0x00, 0x08, 0x00, 0x12, 0x00, 0x09, 0x00, 0x07, 0x33, 0x44 };

    EXPECT_NO_THROW({
        std::string result = protocol.parseCommand(command);
        EXPECT_EQ(result, "Drawing ellipse at (8, 18) with radius x: 9 and radius y: 7 with color RGB565(3344)");
        });
}

// Тест для FillEllipse
TEST(DisplayProtocolTest, FillEllipseCommand) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { FILL_ELLIPSE_OPCODE, 0x00, 0x06, 0x00, 0x11, 0x00, 0x05, 0x00, 0x04, 0x55, 0x66 };

    EXPECT_NO_THROW({
        std::string result = protocol.parseCommand(command);
        EXPECT_EQ(result, "Filling ellipse at (6, 17) with radius x: 5 and radius y: 4 with color RGB565(5566)");
        });
}


// Тест для некоректних параметрів ClearDisplay
TEST(DisplayProtocolTest, InvalidClearDisplayCommandParams) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { CLEAR_DISPLAY_OPCODE };

    EXPECT_THROW({
        protocol.parseCommand(command);
        }, std::invalid_argument);
}

// Тест для некоректних параметрів DrawPixel
TEST(DisplayProtocolTest, InvalidDrawPixelCommandParams) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { DRAW_PIXEL_OPCODE, 0x00, 0x10 };  

    EXPECT_THROW({
        protocol.parseCommand(command);
        }, std::invalid_argument);
}

// Тест для некоректних параметрів DrawLine
TEST(DisplayProtocolTest, InvalidDrawLineCommandParams) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { DRAW_LINE_OPCODE, 0x00, 0x10, 0x00, 0x20 };  

    EXPECT_THROW({
        protocol.parseCommand(command);
        }, std::invalid_argument);
}

// Тест для некоректних параметрів DrawRectangle
TEST(DisplayProtocolTest, InvalidDrawRectangleCommandParams) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { DRAW_RECTANGLE_OPCODE, 0x00, 0x05, 0x00, 0x10, 0x00, 0x15 };  

    EXPECT_THROW({
        protocol.parseCommand(command);
        }, std::invalid_argument);
}

// Тест для некоректних параметрів FillRectangle
TEST(DisplayProtocolTest, InvalidFillRectangleCommandParams) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { FILL_RECTANGLE_OPCODE, 0x00, 0x05, 0x00, 0x10, 0x00 };  

    EXPECT_THROW({
        protocol.parseCommand(command);
        }, std::invalid_argument);
}

// Тест для некоректних параметрів DrawEllipse
TEST(DisplayProtocolTest, InvalidDrawEllipseCommandParams) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { DRAW_ELLIPSE_OPCODE, 0x00, 0x08, 0x00, 0x12, 0x00 };  

    EXPECT_THROW({
        protocol.parseCommand(command);
        }, std::invalid_argument);
}

// Тест для некоректних параметрів FillEllipse
TEST(DisplayProtocolTest, InvalidFillEllipseCommandParams) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { FILL_ELLIPSE_OPCODE, 0x00, 0x06, 0x00, 0x11 };  

    EXPECT_THROW({
        protocol.parseCommand(command);
        }, std::invalid_argument);
}
