#include <libgimp/gimp.h>


static void query (void);
static void run   (const gchar      *name,
                   gint              nparams,
                   const GimpParam  *param,
                   gint             *nreturn_vals,
                   GimpParam       **return_vals);

static void dofilter  (GimpDrawable     *drawable);

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
    PLUGINFUNCNAME  ,
    PLUGINNAME ,
    PLUGINDESCRIPTION ,
    PLUGINAUTHOR ,
    PLUGINLICENCE ,
    PLUGINDATE ,
    PLUGINMENUNAME ,
    "RGB*, GRAY*",
    GIMP_PLUGIN,
    G_N_ELEMENTS (args), 0,
    args, NULL);

  gimp_plugin_menu_register ( PLUGINFUNCNAME,  PLUGINMENUPATH );
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

  gimp_progress_init ( PLUGINPROGESSMESSAGE );

  /* not ready.... Let's time blur
   **  GTimer timer = g_timer_new time();
  */

 dofilter (drawable);

  /* g_print (" %s took %g seconds.\n", PLUGINFUNCNAME , g_timer_elapsed (timer));
  g_timer_destroy (timer);
  */

  gimp_displays_flush ();
  gimp_drawable_detach (drawable);
}

/* dofilter() code is in the filter file.c */ 
