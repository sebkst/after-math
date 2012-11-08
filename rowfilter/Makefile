
all : sinuss-row test

sinuss-row :
	gimptool-2.0 --build $@.c && mv -v $@ ../bin/
	gimptool-2.0 --install $@.c
	gimptool-2.0 --install-script $@.scm 

test :
	gimp -i -b '(sinus-filter-row "../test/foo.png" "../test/foosinus-row.png")' -b '(gimp-quit 0)'
	gpicview ../test/foosinus-row.png

