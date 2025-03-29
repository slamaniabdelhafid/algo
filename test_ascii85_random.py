import random
import base64
import unittest
from ascii85 import encode, decode

class TestRandomData(unittest.TestCase):
    def test_random_correct_data(self):
        for _ in range(100):
            data = bytes(random.getrandbits(8) for _ in range(random.randint(1, 100)))
            encoded = encode(data)
            decoded = decode(encoded)
            self.assertEqual(decoded, data)

    def test_invalid_data(self):
        invalid_chars = [chr(c) for c in range(33)] + [chr(c) for c in range(118, 256)]
        for _ in range(10):
            invalid_data = ''.join(random.choices(invalid_chars, k=5)).encode()
            with self.assertRaises(ValueError):
                decode(invalid_data)

    def test_base64_comparison(self):
        data = b'This is a test string'
        encoded_ascii85 = encode(data)
        encoded_base64 = base64.b64encode(data)
        self.assertNotEqual(encoded_ascii85, encoded_base64)

if __name__ == '__main__':
    unittest.main()
