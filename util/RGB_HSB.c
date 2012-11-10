#include <math.h>

void RGBtoHSB(guchar *rgb, float *hue , float *saturation, float *brightness)
{
    // TODO check arguments

    float r = rgb[0] / 255.0f;
    float g = rgb[1] / 255.0f;
    float b = rgb[2] / 255.0f;
    float max = fmaxf(fmaxf(r, g), b);
    float min = fminf(fminf(r, g), b);
    float delta = max - min;
    if (delta > 0.000000009f) // != 0)
    {
        //float hue;
        if (r == max)
        {
            *hue = (g - b) / delta;
        }
        else
        {
            if (g == max)
            {
                *hue = 2 + (b - r) / delta;
            }
            else
            {
                *hue = 4 + (r - g) / delta;
            }
        }
        *hue = *hue * 60;
        if (*hue < 0) *hue = *hue + 360;
    }
    else
    {
        *hue = 0;
    }
    *saturation = max == 0 ? 0 : (max - min) / max;
    *brightness = max;
}



void HSVtoRGB( float h, float s, float v, guchar *rgb)
{
	int i;
	float f, p, q, t;
	if( s == 0 ) {
		// achromatic (grey)
		rgb[0] = rgb[1] = rgb[2] = (guchar)(255.0f*v);
		return;
	}
	h /= 60;			// sector 0 to 5
	i = floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );
	switch( i ) {
		case 0:
			rgb[0] = (guchar)(255.0f*v);
			rgb[1] = (guchar)(255.0f*t);
			rgb[2] = (guchar)(255.0f*p);
			break;
		case 1:
			rgb[0] = (guchar)(255.0f*q);
			rgb[1] = (guchar)(255.0f*v);
			rgb[2] = (guchar)(255.0f*p);
			break;
		case 2:
			rgb[0] = (guchar)(255.0f*p);
			rgb[1] = (guchar)(255.0f*v);
			rgb[2] = (guchar)(255.0f*t);
			break;
		case 3:
			rgb[0] = (guchar)(255.0f*p);
			rgb[1] = (guchar)(255.0f*q);
			rgb[2] = (guchar)(255.0f*v);
			break;
		case 4:
			rgb[0] = (guchar)(255.0f*t);
			rgb[1] = (guchar)(255.0f*p);
			rgb[2] = (guchar)(255.0f*v);
			break;
		default:		// case 5:
			rgb[0] = (guchar)(255.0f*v);
			rgb[1] = (guchar)(255.0f*p);
			rgb[2] = (guchar)(255.0f*q);
			break;
	}
}
