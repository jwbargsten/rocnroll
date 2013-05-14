.PHONY: all

all:
	cd src && $(MAKE)
test:
	cd test && $(MAKE)
clean:
	cd src && $(MAKE) clean
	cd test && $(MAKE) clean
