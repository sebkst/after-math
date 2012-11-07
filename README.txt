==> exponential.c <==

 compile and install : 
        gimptool-2.0 --install exponential.c 
        gimptool-2.0 --install-script exponential.scm 

   run in bach mode :
        gimp -i -b '(exponential-filter "foo.png" "fooexponential.png")' -b '(gimp-quit 0)'
        gpicview fooexponential.png

   uninstall :
        gimptool-2.0 --uninstall-bin exponential
        gimptool-2.0 --uninstall-script exponential.scm 

 RESULT = the exponential color code (255*(-1 +exp(code))/(-1 +exp(255)) ) */




==> sinuss.c <==

  compile and install : 
        gimptool-2.0 --install sinuss.c 
        gimptool-2.0 --install-script sinus.scm 

   run in bach mode :
        gimp -i -b '(sinus-filter "foo.png" "foosinus.png")' -b '(gimp-quit 0)'
        gpicview foosinus.png

   uninstall :
        gimptool-2.0 --uninstall-bin sinuss
        gimptool-2.0 --uninstall-script sinus.scm 


RESULT = put the sinus color code (255*sin(2PI*code/255)) */



==> symmetric.c <==
 
  compile and install : 
	gimptool-2.0 --install symmetric.c 
	gimptool-2.0 --install-script symmetric.scm 

   run in bach mode :
	gimp -i -b '(symmetric-filter "foo.png" "foosymmetric.png")' -b '(gimp-quit 0)'
        gpicview foosymmetric.png

   uninstall :
	gimptool-2.0 --uninstall-bin symmetric
	gimptool-2.0 --uninstall-script symmetric.scm 

RESULT = the color code symmetric with regards to the point: (128,128,128,128) 



==> symmetricrange.c <==

   compile and install : 
        gimptool-2.0 --install symmetricrange.c 
        gimptool-2.0 --install-script symmetricrange.scm 

   run in bach mode :
        gimp -i -b '(symmetricrange-filter "foo.png" "foosymmetricrange.png")' -b '(gimp-quit 0)'
        gpicview foosymmetricrange.png

   uninstall :
        gimptool-2.0 --uninstall-bin symmetricrange
        gimptool-2.0 --uninstall-script symmetricrange.scm 

RESULT the color code symmetric with regards to the range  of the image
   the code should stay in the same range R G B A but the values are swaped min to max

  *** NOT the same as a NEGATIVE filter ***

