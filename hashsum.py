import sys


def generate_binary_file(filename):
    data = bytearray([0xFF] * 0x80000)
    with open(filename, 'wb') as f:
        f.write(data)

    print(f"Файл {filename} сгенерирован")

def calculate_checksum(filename, start_addr=0x20000, end_addr=0x80000):
    try:
        with open(filename, 'rb') as f:
            f.seek(start_addr)
            data = f.read(end_addr - start_addr)
            checksum = sum(data)


        print(f"Контрольная сумма диапазона {hex(start_addr)} - {hex(end_addr)}: {checksum}")
        return checksum
    except FileNotFoundError:
        print(f"Файл {filename} не найден.")
        return None

if __name__ == "__main__":
    #generate_binary_file('foo.bin')
    calculate_checksum(sys.argv[1]) # 100142325
