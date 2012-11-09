#include <libgimp/gimp.h>
/* #include "range.h" */

/* compile and install : 
        gimptool-2.0 --install sinuss-row.c 
        gimptool-2.0 --install-script sinuss-row.scm 

   run in bach mode :
        gimp -i -b '(sinus-filter-row "../test/foo.png" "../test/foosinusrow.png")' -b '(gimp-quit 0)'
        gpicview ../test/foosinusrow.png

   uninstall :
        gimptool-2.0 --uninstall-bin sinuss-row
        gimptool-2.0 --uninstall-script sinuss-row.scm 

*/

/* put the sinus color code (255* (1+sin(2PI*code/255))/2 )*/
/* row by row */

static void query (void);
static void run   (const gchar      *name,
                   gint              nparams,
                   const GimpParam  *param,
                   gint             *nreturn_vals,
                   GimpParam       **return_vals);

static void sinusrow  (GimpDrawable     *drawable);
static void getrange  (GimpDrawable     *drawable, guchar *mintab, guchar *maxtab,  gint x1, gint y1, gint x2, gint y2);

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
    "plug-in-sinuss-row",
    "Sinus-row",
    "get sinus color code of the image",
    "Sebastien",
    "GPL Sebastien",
    "2012",
    "_Sinus-row",
    "RGB*, GRAY*",
    GIMP_PLUGIN,
    G_N_ELEMENTS (args), 0,
    args, NULL);

  gimp_plugin_menu_register ("plug-in-sinuss-row",
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

  gimp_progress_init ("Sinus ...");

  /* Let's time blur
   **  GTimer timer = g_timer_new time();
  */

  sinusrow (drawable);

  /* g_print ("sinus() took %g seconds.\n", g_timer_elapsed (timer));
  g_timer_destroy (timer);
  */

  gimp_displays_flush ();
  gimp_drawable_detach (drawable);
}

/*
z-brush
avion
volumedic
lumion    (NL)
nemetech
*/

static void getrange  (GimpDrawable     *drawable, guchar *mintab, guchar *maxtab,  gint x1, gint y1, gint x2, gint y2)
{
    gint         i, j, k, channels;
    GimpPixelRgn rgn_in;
    guchar      *inrow;

  channels = gimp_drawable_bpp (drawable->drawable_id);
  gimp_pixel_rgn_init (&rgn_in,
                       drawable,
                       x1, y1,
                       x2 - x1, y2 - y1,
                       FALSE, FALSE);  
   inrow = g_new (guchar, channels * (x2 - x1));
 
  for (j = 0; j < 4; j++){
	mintab[j]=255;
	maxtab[j]=0;
  }
  for (i = y1; i < y2; i++)
     {
         /* Get row i */
         gimp_pixel_rgn_get_row (&rgn_in, inrow, x1, i, x2 - x1);
         for (j = x1; j < x2; j++)
           {
              for (k = 0; k < channels; k++){
                  mintab[k]=MIN ( inrow[channels * (j - x1) + k], mintab[k] ) ;
                  maxtab[k]=MAX ( inrow[channels * (j - x1) + k], maxtab[k] ) ;
              }
	   }
     }
}


static void
sinusrow (GimpDrawable *drawable)
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

  
  
  /*
  for (i = x1; i < x2; i++){
      for (j = y1; j < y2; j++){
          guchar pixel[4];
          gimp_pixel_rgn_get_pixel (&rgn_in, pixel, i, j);
          for (k = 0; k < channels; k++){
		if(minp[k]>pixel[k]) minp[k]=pixel[k];
		if(maxp[k]<pixel[k]) maxp[k]=pixel[k];
          }
  } }
  */


  guchar minp[4],maxp[4];
  getrange(drawable, minp, maxp, x1, x2, y1, y2);
  



  for (i = y1; i < y2; i++)
     {
         /* Get row i */
         gimp_pixel_rgn_get_row (&rgn_in, inrow, x1, i, x2 - x1);

         for (j = x1; j < x2; j++)
              {
                /* For each layer, compute the average of the nine
                 * pixels */
                for (k = 0; k < channels; k++) 
            {
                double angle = inrow[channels * (j - x1) + k], max=255;
                angle = M_2_PI * (angle / max ) ;
                outrow[channels * (j - x1) + k] = (guchar)(255*(1+sin(angle))/2);
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

