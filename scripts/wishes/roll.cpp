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
  uint8_t eventPity;
};

static const uint32_t BUFFER_SIZE = 65536;
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
// event 5* rate up or standard
ui8dist eventRateUpDist(1, 2);
// event 5* standard
ui8dist event5Dist(1, STAND_5_CHAR);
// standard 5* characters + standard 5* weapons
// TODO factor in rate ups for flip flopping types
ui8dist stand5Dist(1, STAND_5_CHAR + STAND_5_WEAP);
// standard 4* characters + standard 4* weapons
ui8dist stand4Dist(1, STAND_4_CHAR + STAND_4_WEAP);
// standard 3* weapons
ui8dist stand3Dist(1, STAND_3_WEAP);

// Roll once on the event banner.
// Upper 2-bits: rarity
// Lower 6-bits: item
uint8_t rollEvent(Pity *pity) {
  Rarity rarity = Rarity::A_3_ITEM;
  if (pity->fiveStarPity >= 90) { // 5* item hard pity
    rarity = Rarity::A_5_ITEM;
  } else if (pity->fiveStarPity >= 75) { // 5* item soft pity
    uint16_t roll = rollDist(engine);
    if (roll <= 320) { // 5* item
      rarity = Rarity::A_5_ITEM;
    } else if (roll <= 320 + 51) { // 4* item
      rarity = Rarity::A_4_ITEM;
    } else if (pity->fourStarPity >= 10) { // 4* pity
      rarity = Rarity::A_4_ITEM;
    }
  } else { // normal rates
    uint16_t roll = rollDist(engine);
    if (roll <= 6) { // 5* item
      rarity = Rarity::A_5_ITEM;
    } else if (roll <= 6 + 51) { // 4* item
      rarity = Rarity::A_4_ITEM;
    }
  }

  switch (rarity) {
    case Rarity::A_5_ITEM: {
      uint8_t item = 0;
      if (pity->eventPity == 1) { // Guaranteed event character
        pity->eventPity = 0;
      } else { // Standard character
        item = stand5Dist(engine);
        pity->eventPity = 1;
      }
      pity->fiveStarPity = 0;
      pity->fourStarPity = 0;
      return (Rarity::A_5_ITEM << 6) | item;
    }
    case Rarity::A_4_ITEM: {
      uint8_t item = stand4Dist(engine);
      pity->fiveStarPity++;
      pity->fourStarPity = 0;
      return (Rarity::A_4_ITEM << 6) | item;
    }
    case Rarity::A_3_ITEM:
    default: {
      uint8_t item = stand3Dist(engine);
      pity->fiveStarPity++;
      pity->fourStarPity++;
      return (Rarity::A_3_ITEM << 6) | item;
    }
  }
}


// Roll once on the standard banner.
uint8_t rollStandard(Pity *pity) {
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

int main(int argc, char **argv) {
  if (argc < 4) {
    std::cout << "Usage: " << argv[0]
              << " <event|weapon|standard> <number of rolls> <seed>"
              << std::endl;
    return 1;
  }

  std::string banner(argv[1]);
  uint64_t rolls = (std::stol(argv[2]) / BUFFER_SIZE) * BUFFER_SIZE;
  std::string seed(argv[3]);

  std::cout << "Rolling " << rolls << " times on the " << banner << " banner"
            << std::endl;

  std::string output = "rolls_" + banner + ".bin";
  std::ofstream fout(output, std::ios::out | std::ios::binary);
  uint8_t *buffer = new uint8_t[BUFFER_SIZE];
  Pity *pity = new Pity{0, 0};

  uint8_t (*rollFn)(Pity*);
  if (banner == "event") {
    rollFn = &rollEvent;
  } else if (banner == "standard") {
    rollFn = &rollStandard;
  } else {
    std::cerr << "Unknown banner: " << banner << std::endl;
    return 1;
  }

  for (uint64_t roll = 0; roll < rolls; roll += BUFFER_SIZE) {
    for (uint32_t i = 0; i < BUFFER_SIZE; i++) {
      buffer[i] = rollFn(pity);
    }
    fout.write((char *)buffer, BUFFER_SIZE);
  }
  return 0;
}
