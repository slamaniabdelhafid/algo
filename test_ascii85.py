import unittest
from ascii85 import encode, decode

class TestASCII85(unittest.TestCase):
    def test_encode_zero(self):
        self.assertEqual(encode(b'\x00\x00\x00\x00'), b'z')

    def test_decode_zero(self):
        self.assertEqual(decode(b'z'), b'\x00\x00\x00\x00')

    def test_encode_partial_block(self):
        self.assertEqual(encode(b'\x01\x02'), b'!@#')

    def test_decode_partial_block(self):
        self.assertEqual(decode(b'!@#'), b'\x01\x02')

    def test_invalid_character(self):
        with self.assertRaises(ValueError):
            decode(b'abcde!')

    def test_invalid_length(self):
        with self.assertRaises(ValueError):
            decode(b'abcd')

if __name__ == '__main__':
    unittest.main()
