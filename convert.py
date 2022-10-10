from PIL import Image
im = Image.open('./textures/test.png')
pixels = list(im.getdata())