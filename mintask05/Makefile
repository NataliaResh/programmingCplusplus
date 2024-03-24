CC := g++ -Wall -Wextra -Werror
sp := ScopedPointer
cmake := cmake -S . -B build 
rm := rm -f

.PHONY: all test clean

test:
	$(cmake)
	cd build/ && make
	cd build/ && ./test_suite

$(sp): $(test)
	clear && $(CC) $(sp).cpp -o build/sp -fsanitize=address
	./build/sp

clean:
	rm -rf ./build/
