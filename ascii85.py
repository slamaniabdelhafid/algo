import sys
import argparse

def encode(data):
    encoded = []
    i = 0
    while i < len(data):
        chunk = data[i:i+4]
        if len(chunk) < 4:
            chunk += b'\x00' * (4 - len(chunk))
        value = int.from_bytes(chunk, 'big')
        if value == 0:
            encoded.append(b'z')
            i += 4
            continue
        buffer = []
        for _ in range(5):
            buffer.append(value % 85 + 33)
            value = value // 85
        buffer.reverse()
        encoded_chunk = bytes(buffer)
        if i + 4 > len(data):
            # Remove trailing padding zeros
            encoded_chunk = encoded_chunk.rstrip(b'\x00')
        encoded.append(encoded_chunk)
        i += 4
    return b''.join(encoded)

def decode(data):
    decoded = []
    i = 0
    while i < len(data):
        if data[i] == ord('z'):
            decoded.append(b'\x00\x00\x00\x00')
            i += 1
            continue
        chunk = data[i:i+5]
        if len(chunk) != 5:
            raise ValueError("Invalid chunk length")
        values = [c - 33 for c in chunk]
        if any(v < 0 or v >= 85 for v in values):
            raise ValueError("Invalid character in chunk")
        value = 0
        for v in values:
            value = value * 85 + v
        decoded_chunk = value.to_bytes(4, 'big')
        decoded.append(decoded_chunk)
        i += 5
    return b''.join(decoded).rstrip(b'\x00')

def main():
    parser = argparse.ArgumentParser(description='ASCII85 encoder/decoder')
    parser.add_argument('-e', '--encode', action='store_true', help='Encode mode')
    parser.add_argument('-d', '--decode', action='store_true', help='Decode mode')
    args = parser.parse_args()

    if not (args.encode or args.decode):
        print("Error: Specify either -e or -d", file=sys.stderr)
        sys.exit(1)

    if args.encode and args.decode:
        print("Error: Cannot specify both -e and -d", file=sys.stderr)
        sys.exit(1)

    try:
        if args.encode:
            input_data = sys.stdin.buffer.read()
            output = encode(input_data)
            sys.stdout.buffer.write(output)
        else:
            input_data = sys.stdin.buffer.read().replace(b'<~', b'').replace(b'~>', b'')
            output = decode(input_data)
            sys.stdout.buffer.write(output)
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
