build: scrycli.cc
	g++ -std=c++20 scrycli.cc -ldl -o scrycli

install: scrycli
	@mkdir -p /usr/bin/
	@mv scrycli /usr/bin/scrycli
