#!/bin/bash

# 0から16までループ
for j in {1..10}
do
	printf "テーブル数：%d,\n" "$j"
	for i in {0..16}
	do
    	# $(( )) の中で計算を行う
   	 val=$((i * 64))
    
    	# 計算結果を引数として渡す
	printf ""
    	./late $val $j
	done
done
