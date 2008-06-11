all:
	[ -d build ] || mkdir build; \
        cd build && cmake .. && $(MAKE)

install: all
	cd build && $(MAKE) install

clean:
	rm -Rf build

