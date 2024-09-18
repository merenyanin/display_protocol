
#include "pch.h"
#include <gtest/gtest.h>
#include <vector>
#include "../display_protocol/display_protocol.cpp"

TEST(DisplayProtocolTest, ClearDisplayCommand) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { 0x01, 0xF8, 0x00 }; 

    EXPECT_NO_THROW({
        std::string result = protocol.parseCommand(command);
        EXPECT_EQ(result, "Clearing display with color: RGB565(f800)");
        });
}


TEST(DisplayProtocolTest, DrawPixelCommand) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { 0x02, 0x00, 0x10, 0x00, 0x20, 0xF8, 0x00 };  // Draw pixel at (16, 32) with color 0xF800

    EXPECT_NO_THROW({
        std::string result = protocol.parseCommand(command);
        EXPECT_EQ(result, "Drawing pixel at (16, 32) with color RGB565(f800)");
        });
}


TEST(DisplayProtocolTest, DrawLineCommand) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { 0x03, 0x00, 0x10, 0x00, 0x20, 0x00, 0x30, 0x00, 0x40, 0xF8, 0x00 };  // Draw line

    EXPECT_NO_THROW({
        std::string result = protocol.parseCommand(command);
        EXPECT_EQ(result, "Drawing line from (16, 32) to (48, 64) with color RGB565(f800)");
        });
}


TEST(DisplayProtocolTest, InvalidOpcode) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { 0xFF };  

    EXPECT_THROW({
        protocol.parseCommand(command);
        }, std::invalid_argument);
}


TEST(DisplayProtocolTest, InvalidClearDisplayCommandParams) {
    DisplayProtocol protocol;
    std::vector<uint8_t> command = { 0x01 };  

    EXPECT_THROW({
        protocol.parseCommand(command);
        }, std::invalid_argument);
}


