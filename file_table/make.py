import random

for i in range(10):
    filename = f"./tables/table_{i}.txt"
    with open(filename, "w") as f:
        for _ in range(1024):
            # 1 から 2^32-1 までの範囲で生成
            val = random.randint(1, 0xFFFFFFFF)
            f.write(f"{val}\n")
    print(f"Created {filename}")
