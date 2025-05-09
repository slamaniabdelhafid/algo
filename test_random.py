import base64
import random
import subprocess

def run_test(data: bytes):
    # Encode with C++
    p_encode = subprocess.run(['./ascii85', '-e'], input=data, capture_output=True)
    c_encoded = p_encode.stdout.decode().strip('\n<~>')
    
    # Encode with Python
    py_encoded = base64.a85encode(data).decode()
    
    # Compare
    assert c_encoded == py_encoded, f"Encode mismatch:\nC++: {c_encoded}\nPython: {py_encoded}"
    
    # Decode with C++
    p_decode = subprocess.run(['./ascii85', '-d'], input=c_encoded.encode(), capture_output=True)
    assert p_decode.stdout == data, f"Decode mismatch:\nInput: {data}\nOutput: {p_decode.stdout}"

def test_random_data():
    for _ in range(100):
        length = random.randint(0, 256)
        data = bytes(random.getrandbits(8) for _ in range(length))
        run_test(data)

if __name__ == "__main__":
    test_random_data()
    print("All random tests passed!")
