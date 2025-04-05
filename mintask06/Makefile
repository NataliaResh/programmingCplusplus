CC := g++ -Wall -Wextra -Werror
matrix := SquareMatrix
cmake := cmake -DENABLE_SANITIZERS=ON -S . -B build
rm := rm -f

.PHONY: all test clean

test:
	$(cmake)
	cd build/ && make
	cd build/ && ./test_suite

$(matrix): $(test)
	clear && $(CC) *.cpp -o build/matrix
	./build/matrix

clean:
	rm -rf ./build/
