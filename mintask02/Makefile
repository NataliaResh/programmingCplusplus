CC := g++ -Wall -Wextra -Werror
line := line
cmake := cmake -DENABLE_SANITIZERS=ON -S . -B build
rm := rm -f

.PHONY: all test clean

test:
	$(cmake)
	cd build/ && make
	cd build/ && ./test_suite

$(line): $(test)
	clear && $(CC) *.cpp -o build/line 
	./build/line

clean:
	rm -rf ./build/
