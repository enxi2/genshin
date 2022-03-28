#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

enum Rarity {
  A_3_ITEM,
  A_4_ITEM,
  A_5_ITEM,
};

struct Pity {
  uint8_t fourStarPity;
  uint8_t fiveStarPity;
};

static const uint32_t BUFFER_SIZE = 1024;
static const uint16_t STAND_5_CHAR = 5;
static const uint16_t STAND_5_WEAP = 10;
static const uint16_t STAND_4_CHAR = 18;
static const uint16_t STAND_4_WEAP = 18;
static const uint16_t STAND_3_WEAP = 15;

std::mt19937 engine;

// TODO https://bbs.nga.cn/read.php?tid=26754637&rand=397
typedef std::uniform_int_distribution<uint16_t> ui16dist;
typedef std::uniform_int_distribution<uint8_t> ui8dist;
// base probability of rolling
ui16dist rollDist(1, 1000);
// standard 5* characters + standard 5* weapons
// TODO factor in rate ups for flip flopping types
ui8dist stand5Dist(1, STAND_5_CHAR + STAND_5_WEAP);
// standard 4* characters + standard 4* weapons
ui8dist stand4Dist(1, STAND_4_CHAR + STAND_4_WEAP);
// standard 3* weapons
ui8dist stand3Dist(1, STAND_3_WEAP);

// Roll once on the standard banner.
// Results are encoded in a single byte. The upper 2 bits encode the rarity. The
// lower 6 bits encode the item (banner dependent).
uint8_t rollOnce(Pity *pity) {
  if (pity->fiveStarPity >= 90) { // 5* item hard pity

    uint8_t item = stand5Dist(engine);
    pity->fiveStarPity = 0;
    pity->fourStarPity = 0;
    return (Rarity::A_5_ITEM << 6) | item;

  } else if (pity->fourStarPity >= 10) { // 4* item hard pity

    uint8_t item = stand4Dist(engine);
    pity->fiveStarPity++;
    pity->fourStarPity = 0;
    return (Rarity::A_4_ITEM << 6) | item;

  } else if (pity->fiveStarPity >= 75) { // 5* item soft pity
    uint16_t roll = rollDist(engine);
    if (roll <= 320) { // 5* item

      uint8_t item = stand5Dist(engine);
      pity->fiveStarPity = 0;
      pity->fourStarPity = 0;
      return (Rarity::A_5_ITEM << 6) | item;

    } else if (roll <= 320 + 51) { // 4* item

      uint8_t item = stand4Dist(engine);
      pity->fiveStarPity++;
      pity->fourStarPity = 0;
      return (Rarity::A_4_ITEM << 6) | item;

    } else { // 3* item

      uint8_t item = stand3Dist(engine);
      pity->fiveStarPity++;
      pity->fourStarPity++;
      return (Rarity::A_3_ITEM << 6) | item;

    }
  } else { // standard rates
    uint16_t roll = rollDist(engine);
    if (roll <= 6) { // 5* item

      uint8_t item = stand5Dist(engine);
      pity->fiveStarPity = 0;
      pity->fourStarPity = 0;
      return (Rarity::A_5_ITEM << 6) | item;

    } else if (roll <= 6 + 51) { // 4* item

      uint8_t item = stand4Dist(engine);
      pity->fiveStarPity++;
      pity->fourStarPity = 0;
      return (Rarity::A_4_ITEM << 6) | item;

    } else { // 3* item

      uint8_t item = stand3Dist(engine);
      pity->fiveStarPity++;
      pity->fourStarPity++;
      return (Rarity::A_3_ITEM << 6) | item;

    }
  }
}

void rollTimes(const uint32_t times, uint8_t *results, Pity *pity) {
  for (uint32_t i = 0; i < times; i++) {
    results[i] = rollOnce(pity);
  }
}

int main(int argc, char **argv) {
  if (argc < 4) {
    std::cout << "Usage: " << argv[0]
              << " <event|weapon|standard> <number of rolls> <seed>"
              << std::endl;
    return 1;
  }

  std::string banner(argv[1]);
  uint32_t rolls = (atoi(argv[2]) / BUFFER_SIZE) * BUFFER_SIZE;
  std::string seed(argv[3]);

  std::cout << "Rolling " << rolls << " times on the " << banner << " banner"
            << std::endl;

  std::ofstream fout("rolls.bin", std::ios::out | std::ios::binary);
  uint8_t *buffer = new uint8_t[BUFFER_SIZE];
  Pity *pity = new Pity{0, 0};

  for (uint32_t roll = 0; roll < rolls; roll += BUFFER_SIZE) {
    rollTimes(BUFFER_SIZE, buffer, pity);
    fout.write((char *)buffer, BUFFER_SIZE);
  }
  return 0;
}
