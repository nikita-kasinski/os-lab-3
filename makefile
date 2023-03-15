f = -Iinclude
obj = obj/main.o
run: build
	./bin/main
build: dirs $(obj)
	g++ $(obj) -o bin/main
dirs:
	mkdir -p bin obj
obj/%.o: src/%.cpp
	g++ $(f) -c $< -o $@
clean:
	rm bin/main.exe || rm obj/*.o