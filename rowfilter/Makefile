
all : sinuss-row sinuss-hue test-hue test-row

sinuss-row :
	gimptool-2.0 --build $@.c && mv -v $@ ../bin/
	gimptool-2.0 --install $@.c
	gimptool-2.0 --install-script $@.scm 

sinuss-hue :
	gimptool-2.0 --build $@.c && mv -v $@ ../bin/
	gimptool-2.0 --install $@.c
	gimptool-2.0 --install-script $@.scm 

cosinuss-hue :
	gimptool-2.0 --build $@.c && mv -v $@ ../bin/
	gimptool-2.0 --install $@.c
	gimptool-2.0 --install-script $@.scm 

test-row :
	gimp -i -b '(sinus-filter-row "../test/foo.png" "../test/foosinus-row.png")' -b '(gimp-quit 0)'
	gpicview ../test/foosinus-row.png

test-hue :
	gimp -i -b '(sinuss-hue-filter "../test/foo.png" "../test/foosinus-hue.png")' -b '(gimp-quit 0)'
	gimp -i -b '(cosinuss-hue-filter "../test/foo.png" "../test/foocosinus-hue.png")' -b '(gimp-quit 0)'
	gpicview ../test/foocosinus-hue.png

