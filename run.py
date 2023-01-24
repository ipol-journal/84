#!/usr/bin/env python3

import subprocess
import argparse
import PIL.Image
from PIL import ImageDraw


# parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("L", type=float)
ap.add_argument("s", type=float)
args = ap.parse_args()

p1 = ['screened_poisson', str(args.L), 'input_0.png', 'inputSimplest.png', 'output.png', str(args.s)]
subprocess.run(p1)

# compute histograms of images
scale_h = 0
for im_basename in ('input_0', 'inputSimplest', 'output'):
    im = PIL.Image.open(im_basename + '.png')
    h = im.histogram()
    if 'input_0' == im_basename:
        # the scale is based on then input image, first to be computed
        scale_h = 127. / max(h)
        
    # define RGB colors and dark variants
    color = {'R' : (255, 0, 0), 'G' : (0, 255, 0), 'B' : (0, 0, 255)}
    dark = {'R' : (63, 0, 0), 'G' : (0, 63, 0), 'B' : (0, 0, 63)}
    # draw histograms of R, G, B values
    for channel in ('R', 'G', 'B'):
        # PIL stores the RGB histograms in a single array
        xoffset = {'R' : 0, 'G' : 256, 'B' : 512}[channel]
        # new histogram image
        him = PIL.Image.new('RGB', (256, 128), (255, 255, 255))
        draw = PIL.ImageDraw.Draw(him)
        for x in range(0, 256):
            hx = int(h[x+xoffset] * scale_h)
            if hx <= 127:
                draw.line([(x, 127), (x, 127 - hx)],
                                fill=color[channel])
            else:
                draw.line([(x, 127), (x, 0)],
                                fill=dark[channel])
        him.save(im_basename + '_%s.png' % channel)
