CC := g++ -Wall -Wextra -Werror
treap := Treap
cmake := cmake  -DENABLE_SANITIZERS=ON -S . -B build 
rm := rm -f

.PHONY: all test clean

test:
	$(cmake)
	cd build/ && make
	cd build/ && ./test_suite

$(treap): $(test)
	clear && $(CC) $(treap).cpp -o build/treap
	./build/treap

clean:
	rm -rf ./build/
