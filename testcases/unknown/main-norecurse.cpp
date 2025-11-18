// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

int main(int argc, char **argv) {
    return 1;
}

