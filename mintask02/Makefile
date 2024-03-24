CC := g++ -Wall -Wextra -Werror
line := line
cmake := cmake -S . -B build 
rm := rm -f

.PHONY: all test clean

test:
	$(cmake)
	cd build/ && make
	cd build/ && ./test_suite

$(line): $(test)
	clear && $(CC) $(line).cpp -o build/line -fsanitize=address
	./build/line

clean:
	rm -rf ./build/
