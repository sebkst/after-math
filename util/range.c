
/*
static void getrange  (GimpDrawable     *drawable, guchar *mintab, guchar *maxtab,  gint x1, gint y1, gint x2, gint y2);
*/

static void getrange  (GimpDrawable     *drawable, guchar *mintab, guchar *maxtab,  gint x1, gint y1, gint x2, gint y2)
{
    gint         i, j, k, channels;
    GimpPixelRgn rgn_in;
    guchar      *inrow;

  channels = gimp_drawable_bpp (drawable->drawable_id);

  gimp_pixel_rgn_init (&rgn_in,   drawable,   x1, y1,   x2 - x1, y2 - y1,  FALSE, FALSE);  

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
  g_free (inrow);
}
