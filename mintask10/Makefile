CC := g++ -Wall -Wextra -Werror
counter := Counter
cmake := cmake -S . -B build 
rm := rm -f

.PHONY: all test clean

test:
	$(cmake)
	cd build/ && make
	cd build/ && ./test_suite

$(counter): $(test)
	clear && $(CC) $(counter).cpp -o build/counter -fsanitize=address
	./build/counter

clean:
	rm -rf ./build/
