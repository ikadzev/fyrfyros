import sys

def sum_of_bytes(file_path):
    try:
        with open(file_path, 'rb') as f:
            data = f.read(0x60000)  # Читаем первые 0x60000 байт
            total = sum(data)
        print("Сумма первых 0x60000 байтов:", total)
    except Exception as e:
        print("Ошибка:", e)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Использование: python script.py <имя_файла>")
    else:
        sum_of_bytes(sys.argv[1])
