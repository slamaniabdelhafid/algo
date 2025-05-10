# Shannon-Fano Encoder/Decoder

A C++ implementation of Shannon-Fano lossless compression algorithm.

## Features
- **Encoder**: Compresses binary files using Shannon-Fano coding
- **Decoder**: Reconstructs original files from compressed data
- **Dictionary**: Stores symbol-to-code mappings in human-readable format
- **Tests**: Roundtrip and precomputed tests verify correctness

## Build & Run
make        # Build the project
make test   # Run tests

## Usage
 **Encode a file**
./shannon_coder encode input.bin compressed.bin dict.txt

 **Decode a file**
./shannon_coder decode compressed.bin dict.txt output.bin
