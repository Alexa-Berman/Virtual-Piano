#version 410 core

layout (location = 0) in vec3 frag_pos;
layout (location = 1) in vec2 frag_uv;
layout (location = 2) flat in uint instance;

layout (location = 0) out vec4 frag_color;

#define PASS_OUTLINE 0
#define PASS_BASE_COLOR 1

#define KEY_WHITE 0
#define KEY_BLACK 1

uniform int render_pass;
uniform int key_type;

uniform float white_key_fades[7];
uniform float black_key_fades[5];

//defining the colors of the keys
const vec3 key_outline = vec3(0.0, 0.0, 0.0);
const vec3 white_key_color = vec3(1.0, 1.0, 1.0);
const vec3 black_key_color = vec3(0.0, 0.0, 0.0);
const vec3 key_pressed = vec3(0.5, 0.5, 0.5);

//rainbow palette for the white keys
const vec3 palette[7] = vec3[7](
	vec3((230.0/255.0), (38.0/255.0),  (31.0/255.0)),
	vec3((235.0/255.0), (117.0/255.0), (50.0/255.0)),
	vec3((247.0/255.0), (208.0/255.0), (56.0/255.0)),
	vec3((163.0/255.0), (224.0/255.0), (72.0/255.0)),
	vec3((52.0/255.0), (187.0/255.0), (230.0/255.0)),
	vec3((67.0/255.0), (85.0/255.0), (219.0/255.0)),
	vec3((210.0/255.0), (59.0/255.0), (231.0/255.0))
);

// https://easings.net/#easeInExpo
float ease_in_cubic(in float x)
{
	return x * x * x;
}

//rainbow palette for the black keys
const vec3 black_palette[5] = vec3[5](
								vec3((180.0/255.0), (50.0/255.0), (9.0/255.0)),
								vec3((164.0/255.0), (93.0/255.0), (4.0/255.0)),
								vec3((20.0/255.0), (98.0/255.0), (65.0/255.0)),
								vec3((0.0/255.0), (65.0/255.0), (132.0/255.0)),
								vec3((61.0/255.0), (1.0/255.0), (128.0/255.0)));


void main()
{
	frag_color = vec4(key_outline, 1.0);

	if (render_pass == PASS_BASE_COLOR)
	{
		if (key_type == KEY_WHITE)
		{
			float t = ease_in_cubic(white_key_fades[instance]);
			frag_color = vec4(mix(white_key_color, palette[instance], t), 1.0);
		}
		else if (key_type == KEY_BLACK)
		{
			float t = ease_in_cubic(black_key_fades[instance]);
			frag_color = vec4(mix(vec3(0.0), black_palette[instance], t), 1.0);
			//frag_color = vec4(black_key_color, 1.0);
		}
	}
}