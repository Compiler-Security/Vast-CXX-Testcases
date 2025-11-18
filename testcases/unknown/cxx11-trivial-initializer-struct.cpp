// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++17 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++98 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++03 %s %target -o %t%output-suffix && %filecheck

struct sAFSearchPos {
    unsigned char *pos;
    unsigned char count;
};

static volatile struct sAFSearchPos testPositions;

static volatile struct sAFSearchPos arrayPositions[100][10][5];

int main() {
  return testPositions.count + arrayPositions[10][4][3].count; 
}
