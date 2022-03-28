#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

enum Rarity {
  A_3_ITEM,
  A_4_ITEM,
  A_5_ITEM,
};

static const uint32_t BUFFER_SIZE = 1024;
static const uint16_t STAND_5_CHAR = 5;
static const uint16_t STAND_5_WEAP = 10;
static const uint16_t STAND_4_CHAR = 18;
static const uint16_t STAND_4_WEAP = 18;
static const uint16_t STAND_3_WEAP = 15;

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <event|weapon|standard>"
              << std::endl;
    return 1;
  }

  // rolls since the last pull of the particular item
  uint32_t stand_5_rolls[64] = {0};
  uint32_t stand_4_rolls[64] = {0};
  // rolls since the last pull of any 5* item
  uint32_t stand_5_any_rolls = 0;

  std::ifstream fin("rolls.bin", std::ios::in | std::ios::binary);
  std::ofstream fout5("rolls_freq_standard_5.bin",
                      std::ios::out | std::ios::binary);
  std::ofstream fout5any("rolls_freq_standard_5_any.bin",
                         std::ios::out | std::ios::binary);
  std::ofstream fout4("rolls_freq_standard_4.bin",
                      std::ios::out | std::ios::binary);

  uint8_t *buffer = new uint8_t[BUFFER_SIZE];
  while (fin.good() && !fin.eof()) {
    fin.read((char *)buffer, BUFFER_SIZE);
    for (uint16_t i = 0; i < BUFFER_SIZE; i++) {
      uint8_t rarity = (buffer[i] >> 6) & 0x3;
      uint8_t item = buffer[i] & 0x3f;

      if (rarity == Rarity::A_5_ITEM) {
        fout5 << stand_5_rolls[item] + 1 << std::endl;
        fout5any << stand_5_any_rolls + 1 << std::endl;
        stand_5_rolls[item] = 0;
        stand_5_any_rolls = 0;
      } else if (rarity == Rarity::A_4_ITEM) {
        fout4 << stand_4_rolls[item] + 1 << std::endl;
        stand_4_rolls[item] = 0;
      }

      for (uint16_t j = 0; j < 64; j++) {
        stand_5_rolls[j]++;
        stand_4_rolls[j]++;
      }
      stand_5_any_rolls++;
    }
  }
}
