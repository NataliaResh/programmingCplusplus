CC := g++ -Wall -Wextra -Werror
matrix := SquareMatrix
cmake := cmake -S . -B build 
rm := rm -f

.PHONY: all test clean

test:
	$(cmake)
	cd build/ && make
	cd build/ && ./test_suite

$(treap): $(test)
	clear && $(CC) $(matrix).cpp -o build/matrix -fsanitize=address
	./build/matrix

clean:
	rm -rf ./build/
