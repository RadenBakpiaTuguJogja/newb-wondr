#ifndef DETECTION_H
#define DETECTION_H

struct nl_environment {
  bool end;
  bool nether;
  bool underwater;
  float rainFactor;
  float dayFactor;
};

uniform vec4 GameTimeOfDay;
   uniform vec4 DimensionID;

    #define dayTime GameTimeOfDay.w
    #define DAY smoothstep(0.77,0.82,dayTime)+(smoothstep(0.23, 0.18, dayTime))
    #define NIGHT smoothstep(0.22,0.27,dayTime) * (1.0 - smoothstep(0.73, 0.78, dayTime))
    #define SUNSET smoothstep(0.695, 0.745, dayTime) * (1.0 - smoothstep(0.78, 0.83, dayTime))
    #define SUNRISE smoothstep(0.16, 0.21, dayTime) * (1.0 - smoothstep(0.255, 0.305, dayTime))

    #define timeofday vec3(NIGHT, SUNSET + SUNRISE, DAY)
    
#define detectEnd (DimensionID.w == 2.0)

#define Nether (DimensionID.w == 1.0)

bool detectNether(vec3 FOG_COLOR, vec2 FOG_CONTROL) {
  // also consider underlava as nether
  bool underLava = FOG_CONTROL.x == 0.0 && FOG_COLOR.b == 0.0 && FOG_COLOR.g < 0.18 && FOG_COLOR.r-FOG_COLOR.g > 0.1;
  return Nether || underLava;
}

bool detectUnderwater(vec3 FOG_COLOR, vec2 FOG_CONTROL) {
  return FOG_CONTROL.x==0.0 && FOG_CONTROL.y<0.8 && (FOG_COLOR.b>FOG_COLOR.r || FOG_COLOR.g>FOG_COLOR.r);
}

float detectRain(vec3 FOG_CONTROL) {
  // clear fogctrl.x varies with render distance (z)
  // reverse plotted as 0.5 + 1.25/k (k is renderdistance in chunks, fogctrl.z = k*16)
  vec2 clear = vec2(0.5 + 20.0/FOG_CONTROL.z, 1.0); // clear fogctrl value
  vec2 rain = vec2(0.23, 0.70); // rain fogctrl value
  vec2 factor = clamp((FOG_CONTROL.xy-clear)/(rain-clear), vec2(0.0,0.0), vec2(1.0,1.0));
  float val = factor.x*factor.y;
  return val*val*(3.0 - 2.0*val);
}


nl_environment nlDetectEnvironment(float DIMENSION_ID, float TIME_OF_DAY, float DAY, vec3 FOG_COLOR, vec3 FOG_CONTROL) {
  nl_environment e;
<<<<<<< HEAD
  e.end = detectEnd;
  e.nether = detectNether(FOG_COLOR, FOG_CONTROL.xy);
=======
  e.end = detectEnd(DIMENSION_ID);
  e.nether = detectNether(DIMENSION_ID, FOG_COLOR, FOG_CONTROL.xy);
>>>>>>> 961ef4f65e3f18006ea54904670055bbeeb9fd7d
  e.underwater = detectUnderwater(FOG_COLOR, FOG_CONTROL.xy);
  e.rainFactor = detectRain(FOG_CONTROL.xyz);
  e.dayFactor = DAY;
  return e;
}

#endif
