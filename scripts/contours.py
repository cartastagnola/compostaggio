# Import required packages:
import cv2
import numpy as np
import json, os, sys

# processes masks and creates coco-like json file with all the annotations

coco = {
    "info" : {
        "description": "ImmersiveLimit Cigarette Butt Dataset", 
        "url": "http://www.immersivelimit.com", 
        "version": "0.1", 
        "year": 2018, 
        "contributor": "Adam Kelly", 
        "date_created": "2018/07/27"
    },
    "licenses": [{"url": "http://www.immersivelimit.com/noncommercial-educational-license-agreement", "id": 0, "name": "ImmersiveLimit.com Non-Commercial, Educational License Agreement"}],
    "annotations": [],
    "images": [], #{"license": 0, "file_name": "00000000.jpg", "width": 512, "height": 512, "id": 0}
    "categories": [{
        "supercategory": "architecture",
        "id": 1,
        "name": "finestra"
    }]
}

mask_dir = sys.argv[1]
output_dir = sys.argv[2]

for index, file_name in enumerate(os.listdir(mask_dir)):

    image_path = os.path.join(mask_dir, file_name)    
    name, ext = os.path.splitext(file_name)
    if(os.path.isdir(image_path)):
        continue

    name = name[:-2]
    print(file_name)
    print(index, name, ext)

    # Load the image and convert it to grayscale:
    # gray_image = cv2.imread(image_path, cv2.COLOR_BGR2GRAY)
    color_image = cv2.imread(image_path)
    color_image = cv2.cvtColor(color_image, cv2.COLOR_BGR2HSV)
    greenhsv = np.array([90, 255, 255])
    green2hsv=np.array([50, 0, 0])
    gray_image = cv2.inRange(color_image, green2hsv, greenhsv)

    height, width, channels = color_image.shape
    #im = cv2.resize(color_image, (900,500))
    #cv2.imshow("obj color", im)
    #cv2.waitKey(0)

    #im = cv2.resize(gray_image, (900,500))
    #cv2.imshow("obj shapeMask", im)
    #cv2.waitKey(0)

    coco_image = {"license": 0, "file_name": name + ".png", "width": width, "height": height, "id": index}

    print(name)
    print(coco_image)

    coco["images"].append(coco_image)

    # Find contours:
    contours, hierarchy = cv2.findContours(gray_image, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)    

    for i, c in enumerate(contours):
        # get the bounding rect
        x, y, w, h = cv2.boundingRect(c)
        # draw a green rectangle to visualize the bounding rect
        cv2.rectangle(gray_image, (x, y), (x+w, y+h), (0, 255, 0), 2)

        # get the min area rect
        rect = cv2.minAreaRect(c)
        box = cv2.boxPoints(rect)
        # convert all coordinates floating point values to int
        box = np.int0(box)

        annotation = {
            "segmentation": [c.flatten().tolist()],
            "area": cv2.contourArea(c),
            "iscrowd": 0,
            "image_id": index,
            "bbox": [x, y, w, h],
            "category_id": 1,
            "id": i
        }

        coco["annotations"].append(annotation)

with open(os.path.join(output_dir, "annotations.json"), 'w') as f:
    json.dump(coco, f, ensure_ascii=False)
