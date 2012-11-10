#include <libgimp/gimp.h>

#include "../util/range.h"
#include "../util/range.c"

#include "../util/RGB_HSB.h"
#include "../util/RGB_HSB.c"


/* compile and install : 
        gimptool-2.0 --build cosinuss-hue.c 
    interest :
    let functions in another file
    
    compiles the cosinus of HUE
*/

/* put the sinus color code (180* (1+cos(2PI*HUE/360))) */
/* row by row */

static void query (void);
static void run   (const gchar      *name,
                   gint              nparams,
                   const GimpParam  *param,
                   gint             *nreturn_vals,
                   GimpParam       **return_vals);

static void cosinusHue  (GimpDrawable     *drawable);

/*  given by range.c 
  *  static void getrange  (GimpDrawable     *drawable, guchar *mintab, guchar *maxtab,  gint x1, gint y1, gint x2, gint y2);  */

GimpPlugInInfo PLUG_IN_INFO =
{
  NULL,
  NULL,
  query,
  run
};

MAIN()

static void
query (void)
{
  static GimpParamDef args[] =
  {
    {
      GIMP_PDB_INT32,
      "run-mode",
      "Run mode"
    },
    {
      GIMP_PDB_IMAGE,
      "image",
      "Input image"
    },
    {
      GIMP_PDB_DRAWABLE,
      "drawable",
      "Input drawable"
    }
  };

  gimp_install_procedure (
    "plug-in-cosinuss-hue",
    "Cosinus-Hue",
    "get cosinus of HUE color code of the image",
    "Sebastien",
    "GPL Sebastien",
    "2012",
    "_Cosinus-Hue",
    "RGB*, GRAY*",
    GIMP_PLUGIN,
    G_N_ELEMENTS (args), 0,
    args, NULL);

  gimp_plugin_menu_register ("plug-in-cosinuss-hue",
                             "<Image>/Filters/Math");
}

static void
run (const gchar      *name,
     gint              nparams,
     const GimpParam  *param,
     gint             *nreturn_vals,
     GimpParam       **return_vals)
{
  static GimpParam  values[1];
  GimpPDBStatusType status = GIMP_PDB_SUCCESS;
  GimpRunMode       run_mode;
  GimpDrawable     *drawable;

  /* Setting mandatory output values */
  *nreturn_vals = 1;
  *return_vals  = values;

  values[0].type = GIMP_PDB_STATUS;
  values[0].data.d_status = status;

  /* Getting run_mode - we won't display a dialog if
   * we are in NONINTERACTIVE mode
   */
  run_mode = param[0].data.d_int32;

  /*  Get the specified drawable  */
  drawable = gimp_drawable_get (param[2].data.d_drawable);

  gimp_progress_init ("Cosinus Hue...");

  /* Let's time blur
   **  GTimer timer = g_timer_new time();
  */

  cosinusHue (drawable);

  /* g_print ("sinus() took %g seconds.\n", g_timer_elapsed (timer));
  g_timer_destroy (timer);
  */

  gimp_displays_flush ();
  gimp_drawable_detach (drawable);
}


static void cosinusHue (GimpDrawable *drawable)
{
  gint         i, j, k, channels;
  gint         x1, y1, x2, y2;
  GimpPixelRgn rgn_in, rgn_out;

   guchar      *inrow;
   guchar      *outrow;
 /* guchar       output[4];  */

  /* Gets upper left and lower right coordinates,
   * and layers number in the image */
  gimp_drawable_mask_bounds (drawable->drawable_id,
                             &x1, &y1,
                             &x2, &y2);
  channels = gimp_drawable_bpp (drawable->drawable_id);

  /* Initialises two PixelRgns, one to read original data,
   * and the other to write output data. That second one will
   * be merged at the end by the call to
   * gimp_drawable_merge_shadow() */
  gimp_pixel_rgn_init (&rgn_in,
                       drawable,
                       x1, y1,
                       x2 - x1, y2 - y1,
                       FALSE, FALSE);
  gimp_pixel_rgn_init (&rgn_out,
                       drawable,
                       x1, y1,
                       x2 - x1, y2 - y1,
                       TRUE, TRUE);

 /* Initialise enough memory for inrow, outrow */
        inrow = g_new (guchar, channels * (x2 - x1));
        outrow = g_new (guchar, channels * (x2 - x1));

  guchar minp[4],maxp[4];
  // getrange(drawable, minp, maxp, x1, x2, y1, y2);
  
  for (i = y1; i < y2; i++)
     {
         /* Get row i */
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
            float h,s,b;
            RGBtoHSB (rgb,&h,&s,&b);
	    h=180.0f*(1.0f + cos(h * M_2_PI / 360.0f));
	    HSBtoRGB(h,s,b,rgb);

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
  gimp_drawable_update (drawable->drawable_id,
                        x1, y1,
                        x2 - x1, y2 - y1);
}

