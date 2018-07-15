uniform sampler2D texture;

void main()
{
    vec4 pixelColour = texture2D(texture, gl_TexCoord[0].xy);

    float gray = (pixelColour.r + pixelColour.g + pixelColour.b) / 3.0;

    gl_FragColor = vec4(gray, gray, gray, pixelColour.a * 0.2);
}