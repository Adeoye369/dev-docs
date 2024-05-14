# Shader Learning Process

## Some kind of plot sample

```glsl
#ifdef GL_ES
precision mediump float;
#endif 

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

void main() {   
    
    vec2 st = gl_FragCoord.xy / u_resolution.xy;
    st.x *= u_resolution.x/u_resolution.y;
    
    // Base color of some sort
    vec3 color = vec3(st.x,st.y,abs(sin(u_time)));;
    
    // some kind of  value:
    //      (1) Linear: st.x
    //      (2) Linear: st.y - st.x
    //      (3) curve: st.y * st.x
  
    float x_val =   abs(smoothstep(0.2, 0.5, st.y * st.x)) ; 
    
    color = color + (sin(u_time +  (x_val)) ) ;
    
    gl_FragColor = vec4(color, 1.0);
}
```

Result: Is some kind of animation
![alt text](img/image001.png)

### Plot x an y axis in R and G color

```glsl
void main() {
    
    vec2 st = gl_FragCoord.xy / u_resolution.xy;
    
    vec3 color = vec3(st.xy, 0.0);
    gl_FragColor = vec4(color, 1.0);
}
```
Result: 
![alt text](img/image002.png)


### Draw some graph of sort

```glsl

void main() {
    
    vec2 st = gl_FragCoord.xy / u_resolution.xy;
 
    vec3 color = vec3(0.0);
    
    //when value is < 0.5 = 0, value > 0.5 = 1
    //The boundary is 0.5(a constant) along x axis
    float x = step(0.5, st.x);
    
    //when you do it like this plot an equation in boundary,
    
    //: Graph of x against y - diagonal
    float x1 = step(st.x, st.y);
    
    // Graph of x*x against y - a curve
    float x2 = step(st.x * st.x , st.y);
    
    color = vec3(x2);
    
    gl_FragColor = vec4(color, 1.0);
}
```

### Explaining Fract

![alt text](img/fract_exp.png)

![alt text](img/fract_001.png)

![alt text](img/fract_002.png)

![alt text](img/fract_003.png)

![alt text](img/fract_004.png)
