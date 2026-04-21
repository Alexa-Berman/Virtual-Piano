#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;

layout (location = 0) out vec3 frag_pos;
layout (location = 1) out vec2 frag_uv;
layout (location = 2) flat out uint instance;

#define PASS_OUTLINE 0
#define PASS_BASE_COLOR 1

#define KEY_WHITE 0
#define KEY_BLACK 1

uniform int render_pass;
uniform int key_type;

void main()
{
	vec3 p = pos;
	if (render_pass == PASS_BASE_COLOR)
	{
		p *= 0.97;
		p.x *= 0.95;
	}

	if (key_type == KEY_WHITE)
	{
		p.y *= 1.5;
		p.x *= (2.0 / 7.0); // viewport is [-1,1], 7 white keys so we stretch it to fit
		vec2 transform = vec2(gl_InstanceID * (2.0 / 7.0) - 0.855, -0.5); // magic transformation to orient it horizontally lol
		p.xy += transform;
	}
	else if (key_type == KEY_BLACK)
	{
		p.y *= 0.8;
		p.x *= (2.0 / 7.0) * 0.6;
		vec2 transform = vec2(gl_InstanceID * (2.0 / 4.1) * 0.6 - 0.725, -0.15);
		p.xy += transform;
		float offset = gl_InstanceID > 1 ? 0.275 : 0.0;
		p.x += offset;
	}

	frag_pos = p;
	frag_uv = uv;
	instance = gl_InstanceID;
	gl_Position = vec4(p.xy, 0.0, 1.0);
}