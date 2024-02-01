import subprocess
import random
from PIL import Image

def compile_and_run_c_code(c_file, output_ppm, random_value1, random_value2, fractal_choice):
    
    compile_command = ["gcc", c_file, "-o", "mandelbrot"]
    subprocess.run(compile_command, check=True)
    

    run_command = ["./mandelbrot", str(random_value1), str(random_value2), str(fractal_choice)]
    subprocess.run(run_command, check=True)

def convert_ppm_to_jpeg(ppm_file, jpeg_file):
    with Image.open(ppm_file) as img:
        img.save(jpeg_file, "JPEG")

if __name__ == "__main__":
    random_value1 = random.randint(1, 10)
    random_value2 = random.randint(1, 30)
    fractal_choice = random.randint(1, 2)
    c_file = "mandelbrot.c" 
    output_ppm = "mandelbrot.ppm"  
    output_jpeg = "fractal.jpeg"  

    compile_and_run_c_code(c_file, output_ppm, random_value1, random_value2,  fractal_choice)
    convert_ppm_to_jpeg(output_ppm, output_jpeg)
