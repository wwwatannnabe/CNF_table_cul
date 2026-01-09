#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>

//#define TABLE_NUM 1
#define TABLE_SIZE 1025
//#define hit 1023
volatile uint8_t TARGET_KEY = 0xDEADBEEB;

int main(int argc, char *argv[]) {
    
    int hit = atoi(argv[1]);
    int TABLE_NUM = atoi(argv[2]);
    
    // テーブル初期化    
    volatile uint32_t table[TABLE_NUM][TABLE_SIZE];
    for(int j = 0; j < TABLE_NUM; j++){
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[j][i] = rand();  // 擬似ランダムな32bit値
        }
    }
    for(int j = 0; j < TABLE_NUM; j++){
        table[j][hit] = TARGET_KEY;
    }

    // 開始時間取得
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    //------------------------------------------------------------------

    //　テーブルマッチング処理
    for(int j = 0; j < TABLE_NUM; j++){
	    for (int i = 0; i < TABLE_SIZE; i++) {
            	if (table[j][i] == TARGET_KEY){
                	    break;                                                              }                                                                   }
    }

    // 終了時間取得
    clock_gettime(CLOCK_MONOTONIC, &end);
    // レイテンシ計算（ナノ秒）
    long latency_ns = (end.tv_sec - start.tv_sec) * 1000000000
                    + (end.tv_nsec - start.tv_nsec);

    printf("%ld\n", latency_ns);
    /*
    printf("=== Ethernet Header ===\n");
    printf("Dst MAC: "); print_mac(eth.dst_mac); printf("\n");
    printf("Src MAC: "); print_mac(eth.src_mac); printf("\n");
    printf("EtherType: 0x%04x\n", ntohs(eth.ether_type));
    printf("=== Output_port ===\n");
    printf("port : %d\n",output_port);
    */

    return 0;
}
