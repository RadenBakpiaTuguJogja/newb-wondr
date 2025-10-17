#ifndef INSTANCING
$input v_texcoord0, v_posTime
#endif

#include <bgfx_shader.sh>

#ifndef INSTANCING
  #include <newb/main.sh>
uniform vec4 FogColor;
  SAMPLER2D_AUTOREG(s_SkyTexture);
#endif
uniform vec4 env;
uniform vec4 FogAndDistanceControl;

void main() {
  #ifndef INSTANCING
    vec3 viewDir = normalize(v_posTime.xyz);
    vec4 diffuse = texture2D(s_SkyTexture, v_texcoord0);

    nl_environment env = nlDetectEnvironment(FogColor.rgb, FogAndDistanceControl.xyz);
    env.end = true;
    env.nether = false;
    env.underwater = false;
    env.rainFactor = 0.0;
      

    vec3 color = renderEndSky(getEndHorizonCol(), getEndZenithCol(), viewDir, v_posTime.w);
    

    #ifdef NL_END_GALAXY_STARS
      color.rgb += nlRenderGalaxy(viewDir, color, env, v_posTime.w);
    #endif

    vec4 bh = renderBlackhole(viewDir, v_posTime.w);
    color *= bh.a;
    color += bh.rgb;

    color = colorCorrection(color);

    gl_FragColor = vec4(color, 1.0);
  #else
    gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
  #endif
}