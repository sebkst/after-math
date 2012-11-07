TO INSTALL without gimptool-2.0 :
simply copy the files from the bin/ directory into your own gimp plugin directory :
It shall be 
* on MACOSX   /Users/YOURUSERNAME/.gimp-2.8/plug-ins/
* on linux    /home/YOURUSERNAME/.gimp-2.6/plug-ins/

then start the gimp, and the fiter should be inside the plugin menu, and appear in the about box.

To remove the plugins, delete the files from the plug-ins directory above mentionned.




==> exponential.c <==

 RESULT = the exponential color code (255*(-1 +exp(code))/(-1 +exp(255)) ) 


==> sinuss.c <==

RESULT = put the sinus color code (255*sin(2PI*code/255)) 


==> cosinuss.c <==

RESULT = put the cosinus color code (255*cos(2PI*code/255)) 


==> symmetric.c <==
 
RESULT = the color code symmetric with regards to the point: (128,128,128,128) 


==> symmetricrange.c <==

RESULT the color code symmetric with regards to the range  of the image
   the code should stay in the same range R G B A but the values are swaped min to max

  *** NOT the same as a NEGATIVE filter ***

