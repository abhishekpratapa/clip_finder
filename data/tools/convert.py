from PIL import Image
import os, os.path
import json
from shutil import copy
from pathlib import Path

def get_images(path):
    imgs = []
    valid_images = [".jpg", ".gif", ".png", ".tga", ".bmp"]
    for f in os.listdir(path):
        ext = os.path.splitext(f)[1]
        if ext.lower() not in valid_images:
            continue
        imgs.append(os.path.join(path,f))
    return imgs

def get_config(path):
    for f in os.listdir(path):
        ext = os.path.splitext(f)[1]
        if ext.lower() == ".json":
            return os.path.join(path,f)

def process_vott(images, config):
    darknet_data = dict()
    with open(config) as f:
        data = json.load(f)
        darknet_classes = [t["name"] for t in data["tags"]]
        for k in data["assets"].keys():
            image_name = os.path.splitext(data["assets"][k]["asset"]["name"])[0]
            image_width = data["assets"][k]["asset"]["size"]["width"]
            image_height = data["assets"][k]["asset"]["size"]["height"]
            bounding_boxes = []
            for r in data["assets"][k]["regions"]:
                bb_height = r["boundingBox"]["height"] / image_height
                bb_width = r["boundingBox"]["width"] / image_width
                bb_y = r["boundingBox"]["top"] / image_height + bb_height / 2
                bb_x = r["boundingBox"]["left"] / image_width + bb_width / 2
                bb_classes = r["tags"]
                bb_indicies = [darknet_classes.index(c) for c in bb_classes]

                for i in bb_indicies:
                    bounding_boxes.append({
                        "class": i,
                        "width": bb_width,
                        "height": bb_height,
                        "x": bb_x,
                        "y": bb_y
                    })
            darknet_data[image_name] = bounding_boxes
    return darknet_data, darknet_classes

def save_darknet_labels(darknet_data, darknet_dir):
    label_dir = os.path.join(darknet_dir, "labels")
    image_dir = os.path.join(darknet_dir, "images")

    try:
        os.mkdir(label_dir)
    except OSError as error:
        print(error)

    try:
        os.mkdir(image_dir)
    except OSError as error:
        print(error)

    for dd in darknet_data.keys():
        label_path = os.path.join(label_dir, dd + ".txt")
        label_image_path = os.path.join(image_dir, dd + ".txt")
        label_file = open(label_path, "w")
        label_image_file = open(label_image_path, "w")
        label_data = darknet_data[dd]
        for ld in label_data:
            label_file.write(str(ld["class"]) + " " + str(ld["x"]) + " " + str(ld["y"]) + " " + str(ld["width"]) + " " + str(ld["height"]) + " \n")
            label_image_file.write(str(ld["class"]) + " " + str(ld["x"]) + " " + str(ld["y"]) + " " + str(ld["width"]) + " " + str(ld["height"]) + " \n")
        label_file.close()
        label_image_file.close()

def save_darknet_images(darknet_dir, images):
    images_dir = os.path.join(darknet_dir, "images")

    try:
        os.mkdir(images_dir)
    except OSError as error:
        print(error)

    for i in images:
        img = Image.open(i)
        img_filename = os.path.splitext(Path(i).name)[0] + ".png"
        img_path = os.path.join(images_dir, img_filename)
        img.save(img_path, 'png')


def save_darknet_config(darknet_classes, darknet_dir):
    config_dir = os.path.join(darknet_dir, "config")
    label_dir = os.path.join(darknet_dir, "labels")
    images_dir = os.path.join(darknet_dir, "images")

    darknet_images = get_images(images_dir)

    try:
        os.mkdir(config_dir)
    except OSError as error:
        print(error)

    train_path = os.path.join(config_dir, "train.txt")
    train_file = open(train_path, "w")

    for i in darknet_images:
        train_file.write(i + "\n")
    train_file.close()

    class_path = os.path.join(config_dir, "clip.names")
    class_file = open(class_path, "w")

    for c in darknet_classes:
        class_file.write(c + "\n")
    class_file.close()

    data_path = os.path.join(config_dir, "clip.data")
    data_file = open(data_path, "w")

    data_file.write("classes= " + str(len(darknet_classes)) + "\n")
    data_file.write("train = " + str(train_path) + "\n")
    data_file.write("valid = " + str(train_path) + "\n")
    data_file.write("names = " + str(class_path) + "\n")
    data_file.write("backup = backup \n")

    data_file.close()

def vott_darknet(vott_dir, darknet_dir):
    images = get_images(vott_dir)
    config = get_config(vott_dir)
    darknet_data, darknet_classes = process_vott(images, config)
    save_darknet_labels(darknet_data, darknet_dir)
    save_darknet_images(darknet_dir, images)
    save_darknet_config(darknet_classes, darknet_dir)
