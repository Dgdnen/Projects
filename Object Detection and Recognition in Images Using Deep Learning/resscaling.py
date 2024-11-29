import cv2
import os

# Define input and output directories
input_dir = r"D:\DL PROJECT\Dataset Amplification\myData\2"
output_dir = r"D:\DL PROJECT\Dataset Amplification\myData_224\2"
# Create output directory if it doesn't exist
os.makedirs(output_dir, exist_ok=True)

# Define the target size
target_size = (224, 224)

# Loop through each image in the input directory
for filename in os.listdir(input_dir):
    # Read the image
    image_path = os.path.join(input_dir, filename)
    image = cv2.imread(image_path)

    # Resize the image
    resized_image = cv2.resize(image, target_size)

    # Save the resized image to the output directory
    output_path = os.path.join(output_dir, filename)
    cv2.imwrite(output_path, resized_image)

    print(f"Resized {filename} to {target_size}")
