# ASCII85 Encoder/Decoder

A Python implementation of an ASCII85 encoder and decoder, similar to the `base64` utility. This tool converts binary data to ASCII85 format and vice versa.

---

## Что делает?
- **Кодирование**: Преобразует байтовые данные в ASCII85-строку.
- **Декодирование**: Преобразует ASCII85-строку обратно в байты.
- Поддерживает специальный символ `z` для кодирования 4 нулевых байт.
- Проверяет корректность данных при декодировании и завершается с ошибкой при проблемах.

---

## Как использовать
# Кодирование (stdin → stdout)
python ascii85.py -e < input.bin > output.txt

# Декодирование (stdin → stdout)
python ascii85.py -d < encoded.txt > decoded.bin

## Аргументы:

-e — режим кодирования (по умолчанию).
-d — режим декодирования.
## Тестирование
1. Unit-тесты (базовые случаи)
python -m unittest test_ascii85.py

## Проверяет:

Кодирование/декодирование нулей (z).
Обработку частичных блоков.
Проверку недопустимых символов и длин.

## 2. Тесты на случайные данные
python -m unittest test_ascii85_random.py

## Проверяет:

Корректность работы с рандомными данными.
Обработку ошибок для некорректных входных данных.
Файлы проекта
ascii85.py — основной код.
test_ascii85.py — unit-тесты.
test_ascii85_random.py — тесты на случайные данные.
