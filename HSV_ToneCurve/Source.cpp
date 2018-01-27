#include "mainWindow.h"

#include "windows.h"
#include "stdio.h"
#include "stdlib.h"

#define SIZE 225

typedef struct{
	float H;
	float S;
	float V;
} HSV;

using namespace HSV_ToneCurve;

void convertHSVtoRGB(HSV hsv, char *R, char *G, char *B);
HSV convertRGBtoHSV(Color color);
float getMaxVal(float R, float G, float B, char *elem);
float getMinVal(float R, float G, float B);
float getH_in_HSV(float R, float G, float B);

System::Void mainWindow::button1_Click(System::Object^  sender, System::EventArgs^  e) {
	Bitmap^ img = gcnew Bitmap("lena.jpg");
	Bitmap^ img_out = gcnew Bitmap("lena.jpg");
	Color color;
	char Red[SIZE][SIZE];
	char Green[SIZE][SIZE];
	char Blue[SIZE][SIZE];

	for(int i = 0; i < SIZE ; i++){
		for(int j = 0; j < SIZE; j++){
			color = img->GetPixel(j, i);
			HSV hsv = convertRGBtoHSV(color);
			char R,G,B;
			convertHSVtoRGB(hsv, &R, &G, &B);

			Red[i][j] = R;
			Green[i][j] = G;
			Blue[i][j] = B;

		}
	}

	for(int i = 0; i < SIZE ; i++){
		for(int j = 0; j < SIZE; j++){
			img_out->SetPixel(j, i, Color::FromArgb(255, Red[i][j], Green[i][j], Blue[i][j]));
		}
	}
	pictureBox1->Image = img_out;
}



void convertHSVtoRGB(HSV hsv, char *R, char *G, char *B){
	
    float h = hsv.H;
    float s = hsv.S;
    float v = hsv.V;
    
    float r = v;
    float g = v;
    float b = v;
    
    if (s > 0.0f) {
		int flag = (int)(h / 60);
		float max = v * 2.55;
		float min = max * ( 1.0f - s );
		switch(flag){
		case 0:
			b = min;
			g = (h / 60) * (max-min) + min;
			r = max;
			break;
		case 1:
			b = min;
			g = max;
			r = ( (120 - h) / 60 )*(max - min) + min;
			break;
		case 2:
			r = min;
			b = ( (h - 120) / 60 )*(max - min) + min;
			g = max;
			break;
		case 3:
			r = min;
			b = max;
			g = ( (240 - h) / 60 )*(max - min) + min;
			break;
		case 4:
			r = ( (h - 240) / 60 )*(max - min) + min;
			g = min;
			b = max;
			break;
		case 5:
			r = max;
			g = ( (360 - h) / 60 )*(max - min) + min;
			b = min;
			break;
		default:
			break;
		}

    }


	*R = (unsigned char)r;
	*G = char(g);
	*B = char(b);

}

HSV convertRGBtoHSV(Color color){
	HSV hsv;
	char maxElem;

	float max = getMaxVal(color.R, color.G, color.B, &maxElem);
	float min = getMinVal(color.R, color.G, color.B);


	hsv.V = max/2.55;
	hsv.S = (max - min) / max;
	hsv.H = getH_in_HSV(color.R, color.G, color.B);
	

	//hsv.V = color.GetBrightness() * 255;
	//hsv.S = color.GetSaturation() * 100;
	//hsv.H = color.GetHue();

	return hsv;
}

float getMaxVal(float R, float G, float B, char *elem){
	if(R > G && R > B){
		*elem = 'R';
		return R;
	}else if(G > R && G > B){
		*elem = 'G';
		return G;
	}else{
		*elem = 'B';
		return B;
	}
}

float getMinVal(float R, float G, float B){
	if(R < G && R <B)
		return R;
	else if(G < R && G < B)
		return G;
	else
		return B;
}

float getH_in_HSV(float R, float G, float B){
	char Elem;
	float max = getMaxVal(R, G, B, &Elem);
	float min = getMinVal(R, G, B);
	float val;

	if(max == min)
		return 0;

	if(Elem == 'R')
		val = 60 * (G - B) / (max - min);
	else if(Elem == 'G')
		val = 60 * (B - R) / (max - min) + 120;
	else if(Elem == 'B')
		val = 60 * (R - G) / (max - min) + 240;
	
	if( val < 0)
		val += 360.0;

	return val;
}