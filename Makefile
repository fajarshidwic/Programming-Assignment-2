.default: all

all: ftt

clean:
	rm -rf ftt *.o *.dSYM

ftt: Coin.o Node.o LinkedList.o ftt.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^

purchasetest1: ftt
	./ftt foods.dat coins.dat < ./input/purchasetest/purchasetest1/input.txt > ./output/purchasetest/output1.txt

purchasetest2: ftt
	./ftt foods.dat coins.dat < ./input/purchasetest/purchasetest2/input.txt > ./output/purchasetest/output2.txt

purchasetest3: ftt
	./ftt foods.dat coins.dat < ./input/purchasetest/purchasetest3/input.txt > ./output/purchasetest/output3.txt

purchasetest4: ftt
	./ftt foods.dat coins.dat < ./input/purchasetest/purchasetest4/input.txt > ./output/purchasetest/output4.txt

purchasetest5: ftt
	./ftt foods.dat coins.dat < ./input/purchasetest/purchasetest5/input.txt > ./output/purchasetest/output5.txt

purchasetest6: ftt
	./ftt foods.dat coins.dat < ./input/purchasetest/purchasetest6/input.txt > ./output/purchasetest/output6.txt

purchasetest7: ftt
	./ftt foods.dat coins.dat < ./input/purchasetest/purchasetest7/input.txt > ./output/purchasetest/output7.txt

purchasetest8: ftt
	./ftt foods.dat coins.dat < ./input/purchasetest/purchasetest8/input.txt > ./output/purchasetest/output8.txt

purchasetest9: ftt
	./ftt foods.dat coins.dat < ./input/purchasetest/purchasetest9/input.txt > ./output/purchasetest/output9.txt
