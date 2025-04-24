import base64
import random
import subprocess
import sys

def compare_random_data():
    for _ in range(100):
        data_size = random.randint(1, 100)
        data = bytes(random.getrandbits(8) for _ in range(data_size))

        p = subprocess.run(['./ascii85', '-e'], input=data, capture_output=True)
        c_encoded = p.stdout.decode().strip()

        py_encoded = base64.a85encode(data).decode().strip()

        if c_encoded != py_encoded:
            print(f"Encoding mismatch for {data.hex()}")
            print("C++:", c_encoded)
            print("Python:", py_encoded)
            return False

        p = subprocess.run(['./ascii85', '-d'], input=c_encoded.encode(), capture_output=True)
        c_decoded = p.stdout

        py_decoded = base64.a85decode(c_encoded.encode())

        if c_decoded != py_decoded:
            print(f"Decoding mismatch for {c_encoded}")
            print("C++:", c_decoded.hex())
            print("Python:", py_decoded.hex())
            return False
    return True

if __name__ == "__main__":
    if compare_random_data():
        print("All Python tests passed!")
    else:
        sys.exit(1)
