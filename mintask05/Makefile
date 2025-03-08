CC := g++ -Wall -Wextra -Werror
pointer := pointer
cmake := cmake -DENABLE_SANITIZERS=ON -S . -B build
rm := rm -f

.PHONY: all test clean

test:
	$(cmake)
	cd build/ && make
	cd build/ && ./test_suite

$(pointer): $(test)
	clear && $(CC) *.cpp -o build/pointer
	./build/pointer

clean:
	rm -rf ./build/
