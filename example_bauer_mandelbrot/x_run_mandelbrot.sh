gcc -o mandelbrot -O4 x_mandelbrot_bauer.c 

#./mandelbrot  <xmin>   <xmax>   <ymin>    <ymax>    <maxiter>  <xres>  <out.ppm>
  ./mandelbrot 0.27085  0.27100  0.004640  0.004810  75         100    pic.ppm

#  mimeopen -d pic.ppm
display pic.ppm