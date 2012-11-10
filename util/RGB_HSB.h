
#define RGBtoHSV RGBtoHSB

void RGBtoHSB( guchar *rgb, float *hue , float *saturation, float *brightness );

#define HSBtoRGB HSVtoRGB

void HSVtoRGB( float h, float s, float v, guchar *rgb);

