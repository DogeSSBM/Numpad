#pragma once

typedef union{
	float arr[2];
	struct{
		float x;
		float y;
	};
}Coordf, Vectorf;

typedef union{
	int arr[2];
	struct{
		int x;
		int y;
	};
}Coord, Vector;

static inline
float cfToRad(const Coordf coord)
{
	return atan2f(coord.y, coord.x);
}

static inline
float radToDeg(const float rad)
{
	return rad*(180.0f/PI);
}

static inline
float cfToDeg(const Coordf coord)
{
	return radToDeg(cfToRad(coord));
}

static inline
float degToRad(const float deg)
{
	return deg*(PI/180.0f);
}

static inline
Coordf radToCf(const float rad)
{
	return (Coordf){cosf(rad), sinf(rad)};
}

static inline
Coordf degToCf(const float deg)
{
	return radToCf(degToRad(deg));
}

static inline
Coordf CCf(const Coord coord)
{
	return (Coordf){(float)coord.x,(float)coord.y};
}

static inline
Coord CfC(const Coordf coordf)
{
	return (Coord){(int)coordf.x,(int)coordf.y};
}

static inline
float fclamp(const float n, const float min, const float max)
{
	if(n < min)
		return min;
	if(n >= max)
		return max-1;
	return n;
}

static inline
bool finBound(const float n, const float min, const float max)
{
	return !(n < min || n >= max);
}

static inline
float fwrap(const float n, const float min, const float max)
{
	const float size = max-min;
	if(n < min)
		return max-fabs(n);
	if(n >= max)
		return min+(float)((int)n%(int)size);
	return n;
}

static inline
Coordf cfMul(const Coordf coord, const float num)
{
	return (Coordf){coord.x*num, coord.y*num};
}

static inline
Coordf cfDiv(const Coordf coord, const float num)
{
	if(num==0.0f)
		return coord;
	return (Coordf){coord.x/num, coord.y/num};
}

static inline
float cfDist(const Coordf coord1, const Coordf coord2)
{
	return sqrtf(powf(coord2.x-coord1.x,2.0f)+powf(coord2.y-coord1.y,2.0f));
}

static inline
float cfMag(const Coordf coord)
{
	return sqrtf(coord.x*coord.x+coord.y*coord.y);
}

static inline
Coordf radMagToCf(const float rad, const float mag)
{
	return cfMul(radToCf(rad), mag);
}

static inline
Coordf cfNormalize(const Coordf coord)
{
	return cfDiv(coord, cfMag(coord));
}

static inline
Coordf cfTranslate(const Coordf coord, const Vectorf vec)
{
	return (Coordf){coord.x+vec.x, coord.y+vec.y};
}

static inline
Coordf cfTranslateRadMag(const Coordf coord, const float rad, const float mag)
{
	return cfTranslate(coord, radMagToCf(rad, mag));
}
