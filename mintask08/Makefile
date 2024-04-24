CC := g++ -Wall -Wextra -Werror
expr := IO
cmake := cmake -S . -B build 
rm := rm -f

.PHONY: all test clean

test:
	$(cmake)
	cd build/ && make
	cd build/ && ./test_suite

$(io): $(test)
	clear && $(CC) $(io).cpp -o build/io -fsanitize=address
	./build/io

clean:
	rm -rf ./build/
