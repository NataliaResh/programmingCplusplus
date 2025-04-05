CC := g++ -Wall -Wextra -Werror
expr := IO
cmake := cmake -DENABLE_SANITIZERS=ON -S . -B build
rm := rm -f

.PHONY: all test clean

test:
	$(cmake)
	cd build/ && make
	cd build/ && ./test_suite

$(io): $(test)
	clear && $(CC) $(io).cpp -o build/io
	./build/io

clean:
	rm -rf ./build/
