import os
import cv2
import Augmentor

def augment_dataset(input_folder, output_folder, num_images):
    # Create an Augmentor pipeline
    p = Augmentor.Pipeline(input_folder, output_folder)

    # Add augmentation operations
    p.rotate(probability=0.7, max_left_rotation=10, max_right_rotation=10)
    p.flip_left_right(probability=0.5)
    p.zoom_random(probability=0.5, percentage_area=0.95)
    p.random_contrast(probability=0.5, min_factor=0.8, max_factor=1.2)
    p.random_brightness(probability=0.5, min_factor=0.8, max_factor=1.2)
    p.random_color(probability=0.5, min_factor=0.8, max_factor=1.2)
    p.shear(probability=0.3, max_shear_left=10, max_shear_right=10)  # Shear

    # Generate augmented images
    p.sample(num_images)

def main():
    # Set paths
    input_folder = r"D:\DL PROJECT\Dataset Amplification\myData\2"
    output_folder = r"D:\DL PROJECT\Dataset Amplification\myData_final\2"

    num_images = 3000  # Number of augmented images to generate

    # Check if input folder exists
    if not os.path.exists(input_folder):
        print("Input folder not found.")
        return

    # Check if output folder exists, if not create it
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # Augment the dataset
    augment_dataset(input_folder, output_folder, num_images)
    print("Dataset augmentation completed.")

if __name__ == "__main__":
    main()