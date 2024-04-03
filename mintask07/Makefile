CC := g++ -Wall -Wextra -Werror
expr := Expression
cmake := cmake -S . -B build 
rm := rm -f

.PHONY: all test clean

test:
	$(cmake)
	cd build/ && make
	cd build/ && ./test_suite

$(expr): $(test)
	clear && $(CC) $(expr).cpp -o build/expr -fsanitize=address
	./build/expr

clean:
	rm -rf ./build/
