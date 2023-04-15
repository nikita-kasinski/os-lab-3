EXECM = bin/main.exe
EXECT = bin/test.exe
objM = obj/main.o
obj = obj/utility.o obj/marker.o
objT = obj/test.o obj/tutility.o
CC = g++
CPPFLAGS = -std=c++17 -Wall -Iinclude
TESTLIB = -lgtest -lgtest_main -lgcov
COVERAGE = -fprofile-arcs -ftest-coverage
.PHONY = dirs run build clean test report clean_coverage
# run and build recipes
run: dirs $(EXECM)
	./$(EXECM)
build: dirs $(EXECM)
$(EXECM): $(objM) $(obj)
	$(CC) $(CPPFLAGS) $(objM) $(obj) -o $(EXECM)
obj/%.o: src/%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@
# test recipes
report: test
	-lcov -c --directory obj --output-file coverage.info
	-lcov --extract coverage.info *\src\* -o coverage.info
	-genhtml coverage.info -o cov
	-rm coverage.info
	start cov/index.html
test: dirs clean_coverage $(EXECT)
	./$(EXECT)
$(EXECT): $(objT)
	$(CC) $(CPPFLAGS) $(objT) -o $(EXECT) $(TESTLIB)
obj/%.o: test/%.cc
	$(CC) $(CPPFLAGS) -c $< -o $@ $(TESTLIB)
obj/t%.o: src/%.cpp
	$(CC) $(CPPFLAGS) $(COVERAGE) -c $< -o $@
# additional recipes
dirs:
	-mkdir -p obj bin cov
clean:
	-rm bin/*
	-rm obj/*
	-rm -fr cov/*
clean_coverage:
	-rm obj/*.gcda