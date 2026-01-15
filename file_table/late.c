#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define TABLE_SIZE 1024

int main(int argc, char *argv[]) {
    // 引数: <ファイル名> <テーブル数>
    if (argc < 3) {
        printf("Usage: %s <base_filename> <table_num>\n", argv[0]);
        printf("Example: %s tables/table_ 10\n", argv[0]);
        return 1;
    }

    char *base_filename = argv[1];
    int TABLE_NUM = atoi(argv[2]);
    uint32_t TARGET_KEY = 0; // 探索対象はファイルの末尾に仕込んだ「0」

    // 1. メモリ確保
    uint32_t (*table)[TABLE_SIZE] = malloc(sizeof(uint32_t) * TABLE_NUM * TABLE_SIZE);
    if (!table) return 1;

    // 2. ファイルからデータを読み込む (table_0.txt, table_1.txt...)
    for (int j = 0; j < TABLE_NUM; j++) {
        char filename[256];
       snprintf(filename, sizeof(filename), "./tables/%s.txt", base_filename);

        FILE *fp = fopen(filename, "r");
        if (!fp) {
            fprintf(stderr, "Could not open %s\n", filename);
            free(table);
            return 1;
        }

        for (int i = 0; i < TABLE_SIZE; i++) {
            if (fscanf(fp, "%u", &table[j][i]) != 1) break;
        }
        fclose(fp);
    }

    struct timespec start, end;
    uint32_t dummy_sum = 0;

    // 3. 計測開始 (Cold Cache状態を狙うためループは1回)
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int j = 0; j < TABLE_NUM; j++) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[j][i] == TARGET_KEY) {
                dummy_sum += i; // ヒットした位置(通常1023)を足す
                break;
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    // 4. 結果表示
    long total_ns = (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec);
    
    printf("Processing Time for %d tables: %ld ns\n", TABLE_NUM, total_ns);
    printf("(dummy check: %u)\n", dummy_sum);

    free(table);
    return 0;
}
