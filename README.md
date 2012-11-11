gimp-math
=========

filters for The GIMP, using math models filter colors

* try out formulas plugin in the _prototype_ directory (same install rocedure as below) 
* download our filters in the _bin_ directory 

HOW TO INSTALL the filters without gimptool-2.0 :
simply copy the files from the bin/ directory into your own gimp plugin directory :
It shall be 
* on MACOSX   /Users/YOURUSERNAME/.gimp-2.8/plug-ins/
* on linux    /home/YOURUSERNAME/.gimp-2.6/plug-ins/

then start the gimp, and the filter should be inside the menu plugin->math, and appear in the about box.

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

==> sinus-hue & cosinus-hue <==

get the sinus (cosinus) of the HUE color component :
* pass from RGB to HSB (vector : Hue,S,B)
* then apply new_Hue = (180* (1+sin(2PI*Hue/360))) or (180* (1+cos(2PI*Hue/360)))
* then new_Hue,S,B in HSB to RGB.



in ITALIAN -- filtri per The GIMP, modificano il colore sulla base di modeli matematici

  i plugin per GIMP si inseriscono nel menu plugin->math
  Usano un modello già aposto (http://developer.gimp.org/writing-a-plug-in/1/index.html) part II,

  purpose:  trasformare i colori di ogni pixel secondo un processo matematico, una formula ad esempio 256*sinus(2PI*color/256),
  compile:  gimptool-2.0 su linux

. Gimp a anche possibilità di fare dei Batch, e automatizzare tutto il processo (apri file, applica fitro, salva newfile) che permette di fare il test sensa passare dal GUI. 
  test per adesso : con sinus, cosinus, log, exp, symetric che sono direttamente usabili.
  
  domanda retorica : come integrare un processo iterativo tipo fratale ? e quale fratale ?

  ad esempio Lyapunov http://plus.maths.org/content/extracting-beauty-chaos. 


   E fattibile anche in Ruby con RMagick o ImageRuby (independant) http://tario-project.blogspot.it/2011/04/released-imageruby-flexible-ruby-image.html 
   --------------------------------------- troppo vecchio



