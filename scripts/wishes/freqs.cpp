#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum Rarity {
  A_3_ITEM,
  A_4_ITEM,
  A_5_ITEM,
};

static const uint32_t BUFFER_SIZE = 65536;
static const uint16_t STAND_5_CHAR = 5;
static const uint16_t STAND_5_WEAP = 10;
static const uint16_t STAND_4_CHAR = 18;
static const uint16_t STAND_4_WEAP = 18;
static const uint16_t STAND_3_WEAP = 15;

int main(int argc, char **argv) {
  // pity count at the last item
  uint64_t event_5_rolls[64] = {0};
  uint64_t event_4_rolls[64] = {0};

  std::ifstream fin("rolls_event.bin", std::ios::in | std::ios::binary);
  std::ofstream fout5r("rolls_freq_event_5_rateup.bin",
                      std::ios::out | std::ios::binary);
  std::ofstream fout5s("rolls_freq_event_5_standard.bin",
                      std::ios::out | std::ios::binary);
  std::ofstream fout4r("rolls_freq_event_4_rateup.bin",
                      std::ios::out | std::ios::binary);
  std::ofstream fout4s("rolls_freq_event_4_standard.bin",
                      std::ios::out | std::ios::binary);

  std::vector<uint64_t> buffer5r;
  std::vector<uint64_t> buffer5s;
  std::vector<uint64_t> buffer4r;
  std::vector<uint64_t> buffer4s;

  uint8_t *buffer = new uint8_t[BUFFER_SIZE];
  uint64_t pity = 0;
  while (fin.good() && !fin.eof()) {
    fin.read((char *)buffer, BUFFER_SIZE);
    for (uint64_t i = 0; i < BUFFER_SIZE; i++) {
      uint8_t rarity = (buffer[i] >> 6) & 0x3;
      uint8_t item = buffer[i] & 0x3f;
      pity++;

      if (rarity == Rarity::A_5_ITEM) {
        if (item == 0) {
          buffer5r.push_back(pity - event_5_rolls[item]);
        } else {
          buffer5s.push_back(pity - event_5_rolls[item]);
        }
        event_5_rolls[item] = pity;
      } else if (rarity == Rarity::A_4_ITEM) {
        buffer4s.push_back(pity - event_4_rolls[item]);
        event_4_rolls[item] = pity;
      }
    }

    if (buffer5r.size() > BUFFER_SIZE) {
      fout5r.write(reinterpret_cast<char*>(buffer5r.data()), buffer5r.size() * sizeof(uint64_t));
      fout5r.flush();
      buffer5r.clear();
    }
    if (buffer5s.size() > BUFFER_SIZE) {
      fout5s.write(reinterpret_cast<char*>(buffer5s.data()), buffer5s.size() * sizeof(uint64_t));
      fout5s.flush();
      buffer5s.clear();
    }
    if (buffer4s.size() > BUFFER_SIZE) {
      fout4s.write(reinterpret_cast<char*>(buffer4s.data()), buffer4s.size() * sizeof(uint64_t));
      fout4s.flush();
      buffer4s.clear();
    }
  }

  fout5r.close();
  fout5s.close();
  fout4r.close();
  fout4s.close();
}
