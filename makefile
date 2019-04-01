CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter -Wno-reorder -w 
CPPFLAGS += -I include

all : clean bin/yuck 

parser : src/parser.tab.cpp src/parser.tab.hpp

lexer : src/lexer.yy.cpp

yuck : bin/yuck

src/parser.tab.cpp src/parser.tab.hpp : src/parser.y
	bison -v --report=all -d src/parser.y -o src/parser.tab.cpp -g

src/lexer.yy.cpp : src/lexer.flex src/parser.tab.hpp
	flex -o src/lexer.yy.cpp  src/lexer.flex

bin/yuck : src/parser.tab.o src/lexer.yy.o include/ast/ast_translator.o include/ast/codegen/ast_compiler.o src/c_compiler.o 
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/c_compiler $^


clean :
	rm -f src/*.o
	rm -f bin/*
	rm -f src/*.tab.cpp
	rm -f src/*.yy.cpp
	rm -f src/*.output
	rm -f src/*.dot
	rm -f src/*.tab.hpp
	rm -f include/ast/*.o
	rm -f include/ast/codegen/*.o
	rm -f tmp/formative/*
	rm -f test/translator/outputs/*
	rm -f test/a_compiler/outputs/*
	rm -f test/a_compiler/returns/*
	rm -f test/b_compiler/assembly/*
	rm -f test/b_compiler/objects/*
	rm -f test/b_compiler/outputs/*
	rm -f test_deliverable/outputs/*

bin/c_compiler: all