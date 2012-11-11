
/* FIRST DEFINE CAREFULLY ALL TH  FOLLOWING STRINGS  */ 

#define PLUGINFUNCNAME "a-lisp-name-like-plug-in-cosinuss-hue"

#define PLUGINMENUPATH "<Image>/Filters/Math"

#define PLUGINNAME "the name of the plug-in e.g. Cosinus-Hue"

#define PLUGINDESCRIPTION "describe here the plug-in e.g. get cosinus of HUE color code of the image"

#define PLUGINAUTHOR "Sebastien"

#define PLUGINLICENCE "GPL Sebastien"

#define PLUGINDATE "2012"

#define PLUGINMENUNAME "_Cosinus-Hue put an underscore before shortcut _Letter"

#define PLUGINPROGESSMESSAGE "a message diplayed in taskbar while waiting, e.g. Cosinus Hue..."

/* BASTA */


#include "skeleton.c"


/* if you need the  getrange function */
#include "../util/range.h"
#include "../util/range.c"

/* if needed functions like :  HSBtoRGB RGBtoHSG */
#include "../util/RGB_HSB.h"
#include "../util/RGB_HSB.c"


/* OTHER THING TODO : 

//////////////////////////
add the 2 couple of lines in the Makefile 

# replace MYPLUGINFILENAME with this file's name without the .c
# WARNING the 2,3,4 lines begin with a TABULATION symbol, NOT WITH ANY white spaces

MYPLUGINFILENAME :
	gimptool-2.0 --build $@.c && mv -v $@ ../bin/
	gimptool-2.0 --install $@.c
	gimptool-2.0 --install-script $@.scm


# in the test section, add following the line
# (replacing PLUGINFUNCNAME with its value without "" , and MYPLUGINFILENAME like above )

test-MYPLUGINFILENAME :
        gimp -i -b '(do-PLUGINFUNCNAME "../test/foo.png" "../test/fooMYPLUGINFILENAME.png")' -b '(gimp-quit 0)'


//////////////////////////
# add a new file named MYPLUGINFILENAME.scm with inside the following :
# (replace PLUGINFUNCNAME with its value without "")


(define (do-PLUGINFUNCNAME filename destinationfilename)
   (let* ((image (car (gimp-file-load RUN-NONINTERACTIVE filename filename)))
          (drawable (car (gimp-image-get-active-layer image))))
     (PLUGINFUNCNAME    RUN-NONINTERACTIVE    image drawable)
     (gimp-file-save RUN-NONINTERACTIVE image drawable destinationfilename destinationfilename)
     (gimp-image-delete image)))


*/


/* DESCRIBE also your plugin here : 



*/



/* this is the important function of  your filter */

static void dofilter (GimpDrawable *drawable)
{
  gint         i, j, k, channels;
  gint         x1, y1, x2, y2;
  GimpPixelRgn rgn_in, rgn_out;

   guchar      *inrow;
   guchar      *outrow;

  /* Gets upper left and lower right coordinates,
   * and layers number in the image */
  gimp_drawable_mask_bounds (drawable->drawable_id,
                             &x1, &y1,                             &x2, &y2);
  channels = gimp_drawable_bpp (drawable->drawable_id);

  /* Initialises two PixelRgns, one to read original data,
   * and the other to write output data. That second one will
   * be merged at the end by the call to
   * gimp_drawable_merge_shadow() */
  gimp_pixel_rgn_init (&rgn_in,        drawable,
                       x1, y1,        x2 - x1, y2 - y1,         FALSE, FALSE);
  gimp_pixel_rgn_init (&rgn_out,    drawable,
                       x1, y1,        x2 - x1, y2 - y1,         TRUE, TRUE);

 /* Initialise enough memory for inrow, outrow */
        inrow = g_new (guchar, channels * (x2 - x1));
        outrow = g_new (guchar, channels * (x2 - x1));




/* EXAMPLE USAGE of the functions to get the range */
//  guchar minp[4],maxp[4];
// getrange(drawable, minp, maxp, x1, x2, y1, y2);



  
  for (i = y1; i < y2; i++)
     {
         /* Get row i  into inrow array*/
         gimp_pixel_rgn_get_row (&rgn_in, inrow, x1, i, x2 - x1);

         for (j = x1; j < x2; j++)
              {
                /* For each layer get the color
                 * pixels */
            guchar rgb[4];
            for (k = 0; k < 4; k++) 
            {
                if (k<channels)
			rgb[k] = inrow[channels * (j - x1) + k];
		else	rgb[k] = 0;
	    }





/* YOUR MAIN CODE HERE : should modify the values inside the rgb array*/

/* EXAMPLE OF CODE : */
            float h,s,b;
            RGBtoHSB (rgb,&h,&s,&b);
	    h=180.0f*(1.0f + cos(h * M_2_PI / 360.0f));
	    HSBtoRGB(h,s,b,rgb);

/* END OF YOUR MAIN CODE HERE */





/* write the new rgb values to the pixels of the outrow */
            for (k = 0; k < channels; k++){ 
                outrow[channels * (j - x1) + k] = rgb[k];
            }

        } /*end for j each pixel of the row*/

      gimp_pixel_rgn_set_row (&rgn_out, outrow, x1, i, x2 - x1);

      if (i % 10 == 0)
        gimp_progress_update ((gdouble) (i - x1) / (gdouble) (x2 - x1));

    } /*end for i each row*/



  g_free (inrow);
  g_free (outrow);


  /* Update the modified region */
  gimp_drawable_flush (drawable);
  gimp_drawable_merge_shadow (drawable->drawable_id, TRUE);
  gimp_drawable_update (drawable->drawable_id,                  x1, y1,              x2 - x1, y2 - y1);

}

