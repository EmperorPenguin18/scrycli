build: scrycli.cc scrycli.1.md
	g++ -std=c++20 scrycli.cc -ldl -o scrycli
	pandoc scrycli.1.md -s -t man -o scrycli.1
	gzip -f scrycli.1

install: scrycli
	@mkdir -p /usr/bin/
	@mv scrycli /usr/bin/scrycli
	@mkdir -p /usr/share/man/man1
	@mv scrycli.1.gz /usr/share/man/man1/scrycli.1.gz

uninstall:
	@rm /usr/bin/scrycli
	@rm /usr/share/man/man1/scrycli.1.gz
