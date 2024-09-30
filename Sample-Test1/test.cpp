#include "pch.h"
#include <gtest/gtest.h>
#include <vector>
#include "../display_protocol/display_protocol.h"

// Тест для некоректних параметрів команди ClearDisplay
TEST(DisplayProtocolTest, InvalidClearDisplayCommandParams) {
    uint8_t byte_array[] = { CLEAR_DISPLAY_OPCODE };
    Command* cmd = nullptr;

    DisplayProtocol protocol;
    EXPECT_THROW(protocol.parseCommand(std::vector<uint8_t>(byte_array, byte_array + sizeof(byte_array)), cmd), std::invalid_argument);
}

// Тест для коректної команди ClearDisplay
TEST(DisplayProtocolTest, ValidClearDisplayCommand) {
    uint8_t byte_array[] = { CLEAR_DISPLAY_OPCODE, 0xAA, 0xBB };
    Command* cmd = nullptr;

    DisplayProtocol protocol;
    EXPECT_NO_THROW(protocol.parseCommand(std::vector<uint8_t>(byte_array, byte_array + sizeof(byte_array)), cmd));

    ClearDisplay* clearDisplayCmd = dynamic_cast<ClearDisplay*>(cmd);
    ASSERT_NE(clearDisplayCmd, nullptr);
    EXPECT_EQ(clearDisplayCmd->color, 0xAABB); 

    delete cmd;
}

// Тест для некоректних параметрів команди DrawPixel
TEST(DisplayProtocolTest, InvalidDrawPixelCommandParams) {
    uint8_t byte_array[] = { DRAW_PIXEL_OPCODE };
    Command* cmd = nullptr;

    DisplayProtocol protocol;
    EXPECT_THROW(protocol.parseCommand(std::vector<uint8_t>(byte_array, byte_array + sizeof(byte_array)), cmd), std::invalid_argument);
}

// Тест для коректної команди DrawPixel
TEST(DisplayProtocolTest, ValidDrawPixelCommand) {
    uint8_t byte_array[] = { DRAW_PIXEL_OPCODE, 0x00, 0x02, 0x00, 0x04, 0x99, 0x88 };
    Command* cmd = nullptr;

    DisplayProtocol protocol;
    EXPECT_NO_THROW(protocol.parseCommand(std::vector<uint8_t>(byte_array, byte_array + sizeof(byte_array)), cmd));

    DrawPixel* drawPixelCmd = dynamic_cast<DrawPixel*>(cmd);
    ASSERT_NE(drawPixelCmd, nullptr);
    EXPECT_EQ(drawPixelCmd->x0, 0x0002); 
    EXPECT_EQ(drawPixelCmd->y0, 0x0004); 
    EXPECT_EQ(drawPixelCmd->color, 0x9988); 

    delete cmd;
}

// Тест для некоректних параметрів команди DrawLine
TEST(DisplayProtocolTest, InvalidDrawLineCommandParams) {
    uint8_t byte_array[] = { DRAW_LINE_OPCODE }; 
    Command* cmd = nullptr;

    DisplayProtocol protocol;
    EXPECT_THROW(protocol.parseCommand(std::vector<uint8_t>(byte_array, byte_array + sizeof(byte_array)), cmd), std::invalid_argument);
}

// Тест для коректної команди DrawLine
TEST(DisplayProtocolTest, ValidDrawLineCommand) {
    uint8_t byte_array[] = { DRAW_LINE_OPCODE, 0x00, 0x10, 0x00, 0x20, 0x00, 0x30, 0x00, 0x40, 0xCC, 0x05 };
    Command* cmd = nullptr;

    DisplayProtocol protocol;
    EXPECT_NO_THROW(protocol.parseCommand(std::vector<uint8_t>(byte_array, byte_array + sizeof(byte_array)), cmd));

    DrawLine* drawLineCmd = dynamic_cast<DrawLine*>(cmd);
    ASSERT_NE(drawLineCmd, nullptr);
    EXPECT_EQ(drawLineCmd->x0, 0x1000); 
    EXPECT_EQ(drawLineCmd->y0, 0x2000); 
    EXPECT_EQ(drawLineCmd->x1, 0x3000); 
    EXPECT_EQ(drawLineCmd->y1, 0x4000); 
    EXPECT_EQ(drawLineCmd->color, 0xCC05); 

    delete cmd;
}


// Тест для некоректних параметрів команди DrawRectangle
TEST(DisplayProtocolTest, InvalidDrawRectangleCommandParams) {
    uint8_t byte_array[] = { DRAW_RECTANGLE_OPCODE }; 
    Command* cmd = nullptr;

    DisplayProtocol protocol;
    EXPECT_THROW(protocol.parseCommand(std::vector<uint8_t>(byte_array, byte_array + sizeof(byte_array)), cmd), std::invalid_argument);
}

// Тест для коректної команди DrawRectangle
TEST(DisplayProtocolTest, ValidDrawRectangleCommand) {
    uint8_t byte_array[] = { DRAW_RECTANGLE_OPCODE, 0x00, 0x05, 0x00, 0x10, 0x00, 0x15, 0x00, 0x20, 0xEE, 0xFF };
    Command* cmd = nullptr;

    DisplayProtocol protocol;
    EXPECT_NO_THROW(protocol.parseCommand(std::vector<uint8_t>(byte_array, byte_array + sizeof(byte_array)), cmd));

    DrawRectangle* drawRectCmd = dynamic_cast<DrawRectangle*>(cmd);
    ASSERT_NE(drawRectCmd, nullptr); 
    EXPECT_EQ(drawRectCmd->x, 0x0005); 
    EXPECT_EQ(drawRectCmd->y, 0x0010); 
    EXPECT_EQ(drawRectCmd->width, 0x0015); 
    EXPECT_EQ(drawRectCmd->height, 0x0020);
    EXPECT_EQ(drawRectCmd->color, 0xEEFF); 

    delete cmd; 
}

// Тест для некоректних параметрів команди FillRectangle
TEST(DisplayProtocolTest, InvalidFillRectangleCommandParams) {
    uint8_t byte_array[] = { FILL_RECTANGLE_OPCODE };
    Command* cmd = nullptr;

    DisplayProtocol protocol;
    EXPECT_THROW(protocol.parseCommand(std::vector<uint8_t>(byte_array, byte_array + sizeof(byte_array)), cmd), std::invalid_argument);
}

// Тест для коректної команди FillRectangle
TEST(DisplayProtocolTest, ValidFillRectangleCommand) {
    uint8_t byte_array[] = { FILL_RECTANGLE_OPCODE, 0x00, 0x05, 0x00, 0x10, 0x00, 0x15, 0x00, 0x20, 0x11, 0x22 };
    Command* cmd = nullptr;

    DisplayProtocol protocol;
    EXPECT_NO_THROW(protocol.parseCommand(std::vector<uint8_t>(byte_array, byte_array + sizeof(byte_array)), cmd));

    FillRectangle* fillRectCmd = dynamic_cast<FillRectangle*>(cmd);
    ASSERT_NE(fillRectCmd, nullptr); 
    EXPECT_EQ(fillRectCmd->x, 0x0005); 
    EXPECT_EQ(fillRectCmd->y, 0x0010); 
    EXPECT_EQ(fillRectCmd->width, 0x0015); 
    EXPECT_EQ(fillRectCmd->height, 0x0020); 
    EXPECT_EQ(fillRectCmd->color, 0x1122); 

    delete cmd; 
}

// Тест для некоректних параметрів команди DrawEllipse
TEST(DisplayProtocolTest, InvalidDrawEllipseCommandParams) {
    uint8_t byte_array[] = { DRAW_ELLIPSE_OPCODE };
    Command* cmd = nullptr;

    DisplayProtocol protocol;
    EXPECT_THROW(protocol.parseCommand(std::vector<uint8_t>(byte_array, byte_array + sizeof(byte_array)), cmd), std::invalid_argument);
}

// Тест для коректної команди DrawEllipse
TEST(DisplayProtocolTest, ValidDrawEllipseCommand) {
    uint8_t byte_array[] = { DRAW_ELLIPSE_OPCODE, 0x00, 0x08, 0x00, 0x12, 0x00, 0x09, 0x00, 0x07, 0x33, 0x44 };
    Command* cmd = nullptr;

    DisplayProtocol protocol;
    EXPECT_NO_THROW(protocol.parseCommand(std::vector<uint8_t>(byte_array, byte_array + sizeof(byte_array)), cmd));

    DrawEllipse* drawEllipseCmd = dynamic_cast<DrawEllipse*>(cmd);
    ASSERT_NE(drawEllipseCmd, nullptr); 
    EXPECT_EQ(drawEllipseCmd->x, 0x0008); 
    EXPECT_EQ(drawEllipseCmd->y, 0x0012); 
    EXPECT_EQ(drawEllipseCmd->rx, 0x0009); 
    EXPECT_EQ(drawEllipseCmd->ry, 0x0007); 
    EXPECT_EQ(drawEllipseCmd->color, 0x3344); 

    delete cmd; 
}

// Тест для некоректних параметрів команди FillEllipse
TEST(DisplayProtocolTest, InvalidFillEllipseCommandParams) {
    uint8_t byte_array[] = { FILL_ELLIPSE_OPCODE }; 
    Command* cmd = nullptr;

    DisplayProtocol protocol;
    EXPECT_THROW(protocol.parseCommand(std::vector<uint8_t>(byte_array, byte_array + sizeof(byte_array)), cmd), std::invalid_argument);
}

// Тест для коректної команди FillEllipse
TEST(DisplayProtocolTest, ValidFillEllipseCommand) {
    uint8_t byte_array[] = { FILL_ELLIPSE_OPCODE, 0x00, 0x06, 0x00, 0x11, 0x00, 0x05, 0x00, 0x04, 0x55, 0x66 };
    Command* cmd = nullptr;

    DisplayProtocol protocol;
    EXPECT_NO_THROW(protocol.parseCommand(std::vector<uint8_t>(byte_array, byte_array + sizeof(byte_array)), cmd));

    FillEllipse* fillEllipseCmd = dynamic_cast<FillEllipse*>(cmd);
    ASSERT_NE(fillEllipseCmd, nullptr); 
    EXPECT_EQ(fillEllipseCmd->x, 0x0006); 
    EXPECT_EQ(fillEllipseCmd->y, 0x0011);
    EXPECT_EQ(fillEllipseCmd->rx, 0x0005); 
    EXPECT_EQ(fillEllipseCmd->ry, 0x0004); 
    EXPECT_EQ(fillEllipseCmd->color, 0x5566); 

    delete cmd; 
}
