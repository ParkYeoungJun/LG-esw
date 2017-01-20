from PIL import Image
from PIL import ImageFilter

size = 500,500

im = Image.open("image.jpg")

im.rotate(90).show()
im.thumbnail(size)
im = im.filter(ImageFilter.SHARPEN)

im.save("result.png")
