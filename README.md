gimp-math
=========

filters for The GIMP, using math models filter colors

  i plugin per GIMP si inseriscono nel menu plugin->IMAGEMATH
  Usano un modello già aposto (http://developer.gimp.org/writing-a-plug-in/1/index.html) part II,

  purpose:  trasformare i colori di ogni pixel secondo un processo matematico, una formula ad esempio 256*sinus(2PI*color/256),
  compile:  gimptool-2.0 su linux

. Gimp a anche possibilità di fare dei Batch, e automatizzare tutto il processo (apri file, applica fitro, salva newfile) che permette di fare il test sensa passare dal GUI. Dunque partendo da foo.png, ho fatto tutti altri foo*png allegati. Cosa ti inspira?  
  test per adesso : con sinus, cosinus, log, exp, symetric che sono direttamente usabili.
  
  domanda retorica : come integrare un processo iterativo tipo fratale ? e quale fratale ?

  ad esempio Lyapunov http://plus.maths.org/content/extracting-beauty-chaos. 


   E fattibile anche in Ruby con RMagick o ImageRuby (independant) http://tario-project.blogspot.it/2011/04/released-imageruby-flexible-ruby-image.html 

