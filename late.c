#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define TABLE_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;

    int hit = atoi(argv[1]);
    int TABLE_NUM = atoi(argv[2]);
    uint32_t TARGET_KEY = 0xDEADBEEB;
    
    // メモリ確保と初期化
    uint32_t (*table)[TABLE_SIZE] = malloc(sizeof(uint32_t) * TABLE_NUM * TABLE_SIZE);
    for(int j = 0; j < TABLE_NUM; j++) {
        for (int i = 0; i < TABLE_SIZE; i++) table[j][i] = rand();
        table[j][hit % TABLE_SIZE] = TARGET_KEY;
    }

    struct timespec start, end;
    uint32_t dummy_sum = 0; // 最適化防止用

    clock_gettime(CLOCK_MONOTONIC, &start);

    // 計測ループ
        for (int j = 0; j < TABLE_NUM; j++) {
            for (int i = 0; i < TABLE_SIZE; i++) {
                if (table[j][i] == TARGET_KEY) {
                    dummy_sum += i; // ヒットした位置を足していく
                    break;
                }
            }
        }

    clock_gettime(CLOCK_MONOTONIC, &end);

    long total_ns = (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);
    
    // 1回の試行（TABLE_NUM分）あたりの平均レイテンシ
    printf("Average Latency per set: %ld ns\n", total_ns);
    // 最適化で消されないための出力
    printf("(dummy check: %u)\n", dummy_sum);

    free(table);
    return 0;
}
