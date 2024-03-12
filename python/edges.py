# Lecture 06 - "Python"
# Program 03

from PIL import Image, ImageFilter

image = Image.open("stadium.bmp")
after = image.filter(ImageFilter.FIND_EDGES)
after.save("out.bmp")