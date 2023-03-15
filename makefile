f = -Iinclude
obj = obj/main.o obj/marker.o
run: build
	./bin/main
build: dirs $(obj)
	g++ $(obj) -o bin/main
dirs:
	mkdir -p bin obj
obj/%.o: src/%.cpp
	g++ $(f) -c $< -o $@
clean:
	rm bin/main || rm obj/*.o