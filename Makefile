
all : sinuss cosinuss exponential exponentialrange symmetric symmetricrange test

sinuss :
	gimptool-2.0 --build $@.c 
	gimptool-2.0 --install $@.c 
	gimptool-2.0 --install-script $@.scm 

cosinuss :
	gimptool-2.0 --build $@.c 
	gimptool-2.0 --install $@.c 
	gimptool-2.0 --install-script $@.scm 

exponential :
	gimptool-2.0 --build $@.c 
	gimptool-2.0 --install $@.c 
	gimptool-2.0 --install-script $@.scm 

exponentialrange :
	gimptool-2.0 --build $@.c 
	gimptool-2.0 --install $@.c 
	gimptool-2.0 --install-script $@.scm 

symmetric :
	gimptool-2.0 --build $@.c 
	gimptool-2.0 --install $@.c 
	gimptool-2.0 --install-script $@.scm 

symmetricrange :
	gimptool-2.0 --build $@.c 
	gimptool-2.0 --install $@.c 
	gimptool-2.0 --install-script $@.scm 

test :
	gimp -i -b '(sinus-filter "test/foo.png" "test/foosinus.png")' -b '(gimp-quit 0)'
	gimp -i -b '(cosinus-filter "test/foo.png" "test/foocosinus.png")' -b '(gimp-quit 0)'
	gimp -i -b '(symmetric-filter "test/foo.png" "test/foosymmetric.png")' -b '(gimp-quit 0)'
	gimp -i -b '(symmetricrange-filter "test/foo.png" "test/foosymmetricrange.png")' -b '(gimp-quit 0)'
	gimp -i -b '(exponential-filter "test/foo.png" "test/fooexponential.png")' -b '(gimp-quit 0)'
	gimp -i -b '(exponentialrange-filter "test/foo.png" "test/fooexponentialrange.png")' -b '(gimp-quit 0)'
