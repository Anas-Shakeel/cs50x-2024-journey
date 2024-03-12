# Lecture 06 - "Python"
# Program 02

from PIL import Image, ImageFilter

image = Image.open("stadium.bmp")
after = image.filter(ImageFilter.BoxBlur(10))
after.save("out.bmp")