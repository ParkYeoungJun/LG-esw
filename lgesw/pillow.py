from PIL import Image

img = Image.open("image.jpg")

print(img.size)
print(img.format)
img.show()
