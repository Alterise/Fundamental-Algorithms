#include <iostream>
#include "compressor.h"
#include "decompressor.h"

int main() {
    compress("input.pgn", "output.bin");
    decompress("output.bin", "output.pgn");
}