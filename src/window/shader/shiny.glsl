uniform sampler2D texture;
uniform float time;

vec3 lerp(vec3 a, vec3 b, float t)
{
	return a + t * (b - a);
}

void main()
{
    float speed = 3.0;
    vec3 col = texture2D(texture, gl_TexCoord[0].st).xyz;
    float max_val = max(max(col.x, col.y), col.z);
    float min_val = min(min(col.x, col.y), col.z);
    col.x = max_val + min_val - col.x;
    col.y = max_val + min_val - col.y;
    col.z = max_val + min_val - col.z;
    vec3 vividcol = col - vec3(0.2);
    gl_FragColor = vec4(lerp(vividcol, col, abs(sin(time * speed) - 1.0) / 8.0 + 0.75), texture2D(texture, gl_TexCoord[0].st).w);
}
