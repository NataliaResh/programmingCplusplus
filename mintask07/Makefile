CC := g++ -Wall -Wextra -Werror
expr := Expression
cmake := cmake -DENABLE_SANITIZERS=ON -S . -B build
rm := rm -f

.PHONY: all test clean

test:
	$(cmake)
	cd build/ && make
	cd build/ && ./test_suite

$(expr): $(test)
	clear && $(CC) $(expr).cpp -o build/expr
	./build/expr

clean:
	rm -rf ./build/
