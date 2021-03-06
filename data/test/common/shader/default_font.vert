
attribute vec4 a_v4Position;
attribute vec4 a_v4Color;
attribute vec2 a_v2TexCoord;

uniform mat4 u_m4ModelViewProjectionMatrix;

varying vec2 v_v2TextCoord;
varying vec4 v_v4DestinationColor;

void main()
{	
	// the following three lines provide the same result
	gl_Position = u_m4ModelViewProjectionMatrix * a_v4Position;
	v_v4DestinationColor = a_v4Color;
	v_v2TextCoord = a_v2TexCoord;
}
