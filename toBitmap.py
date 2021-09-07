from PIL import Image
import sys

img = Image.open(sys.argv[1])
img.save('data/result.bmp')