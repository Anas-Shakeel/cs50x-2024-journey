# Lecture 06 - "Python"
# Program 14

import qrcode


image = qrcode.make("https://youtu.be/xvFZjo5PgG0")
image.save("qr.png", "PNG")
