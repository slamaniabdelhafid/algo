import base64
import random
import subprocess

def compare_random_data():
    for _ in range(100):
        data_size = random.randint(1, 100)
        data = bytes(random.getrandbits(8) for _ in range(data_size))

        # Кодирование через C++
        result = subprocess.run(['./ascii85', '-e'], input=data, capture_output=True)
        c_encoded = result.stdout.decode().strip()

        # Кодирование через Python
        py_encoded = base64.a85encode(data).decode().strip()

        assert c_encoded == py_encoded, f"Ошибка кодирования: {data.hex()}"

        # Декодирование через C++
        decoded = subprocess.run(['./ascii85', '-d'], input=c_encoded.encode(), capture_output=True)
        c_decoded = decoded.stdout

        # Декодирование через Python
        py_decoded = base64.a85decode(c_encoded.encode())

        assert c_decoded == py_decoded, f"Ошибка декодирования: {c_encoded}"

    print("Все тесты пройдены!")

if __name__ == "__main__":
    compare_random_data()
