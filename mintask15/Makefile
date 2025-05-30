CC := g++ -Wall -Wextra -Werror
main := main
cmake := cmake  -DENABLE_SANITIZERS=ON -S . -B build 
rm := rm -f

.PHONY: all test clean

test:
	$(cmake)
	cd build/ && make
	cd build/ && ./test_suite

$(main): $(test)
	clear && $(CC) -std=c++20  $(main).cpp -o build/main
	./build/main

clean:
	rm -rf ./build/
