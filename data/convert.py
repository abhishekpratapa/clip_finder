import os
from tools.convert import vott_darknet

dirname, filename = os.path.split(os.path.abspath(__file__))

VOTT_DIR = os.path.join(dirname, "vott")
DARKNET_DIR = os.path.join(dirname, "darknet")

if __name__ == "__main__":
    print("Converting VOTT to Darknet")
    vott_darknet(VOTT_DIR, DARKNET_DIR)
