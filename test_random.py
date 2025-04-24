import base64
import random
import subprocess

def compare_random_data():
    for _ in range(100):
        data = bytes(random.getrandbits(8) for _ in range(random.randint(1, 100)))
        
        # Кодирование через C++
        p_encode = subprocess.run(['./ascii85', '-e'], input=data, capture_output=True)
        c_encoded = p_encode.stdout.decode().strip()
        
        # Удаление маркеров <~ и ~>
        if c_encoded.startswith('<~'):
            c_encoded = c_encoded[2:]
        if c_encoded.endswith('~>'):
            c_encoded = c_encoded[:-2]
        
        # Обработка случая 4 нулей (заменяем на 'z')
        if data == b'\x00\x00\x00\x00':
            py_encoded = 'z'
        else:
            py_encoded = base64.a85encode(data).decode().strip()
        
        # Сравнение
        assert c_encoded == py_encoded, f"Encoding mismatch: {data.hex()}"
        
        # Декодирование через C++
        p_decode = subprocess.run(['./ascii85', '-d'], input=c_encoded.encode(), capture_output=True)
        c_decoded = p_decode.stdout
        
        # Декодирование через Python
        if py_encoded == 'z':
            py_decoded = b'\x00\x00\x00\x00'
        else:
            py_decoded = base64.a85decode(py_encoded.encode())
        
        # Сравнение
        assert c_decoded == py_decoded, f"Decoding mismatch: {c_encoded}"

if __name__ == "__main__":
    compare_random_data()
    print("All tests passed!")
