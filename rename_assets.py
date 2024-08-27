import os
import shutil

# Define the mapping for consistent naming
piece_names = {
    'w_pawn': 'w_pawn.png',
    'b_pawn': 'b_pawn.png',
    'w_king': 'w_king.png',
    'b_king': 'b_king.png',
    'w_queen': 'w_queen.png',
    'b_queen': 'b_queen.png',
    'w_bishop': 'w_bishop.png',
    'b_bishop': 'b_bishop.png',
    'w_knight': 'w_knight.png',
    'b_knight': 'b_knight.png',
    'w_rook': 'w_rook.png',
    'b_rook': 'b_rook.png',
    'square brown light': 'square_brown_light.png',
    'square brown dark': 'square_brown_dark.png',
    'square gray light': 'square_gray_light.png',
    'square gray dark': 'square_gray_dark.png',
}

# Define the source and output directories
source_dir = 'assets/PNGs'
output_dir = 'assets_output'

# Define the resolution folders and hard-coded paths
categories = {
    'With Shadow': {
        '128px': '128px',
        '256px': '256px',
        '512px': '512px',
        '1024px': '1024px'
    },
    'No shadow': {
        '1x': '128px',
        '2x': '256px',
        '512h': '512px',
        '1024h': '1024px'
    }
}

# Create the output directory structure
for category, resolutions in categories.items():
    for res in resolutions.values():
        os.makedirs(os.path.join(output_dir, category, res), exist_ok=True)

# Function to get the consistent name for a file
def get_consistent_name(filename):
    base_name = os.path.splitext(filename)[0]
    base_name = base_name.replace('_png', '').replace('_shadow', '').replace('_ns', '')

    for key in piece_names.keys():
        if key in base_name:
            return piece_names[key]
    return None

# Function to copy and rename files
def copy_and_rename_files():
    for old_category, resolutions in categories.items():
        for old_res, new_res in resolutions.items():
            source_path = os.path.join(source_dir, old_category, old_res)
            output_path = os.path.join(output_dir, old_category, new_res)

            if not os.path.exists(source_path):
                print(f"Source path not found: {source_path}")
                continue

            for filename in os.listdir(source_path):
                consistent_name = get_consistent_name(filename)
                if consistent_name:
                    shutil.copyfile(
                        os.path.join(source_path, filename),
                        os.path.join(output_path, consistent_name)
                    )
                else:
                    print(f"Filename {filename} did not match any key and was skipped.")

if __name__ == "__main__":
    copy_and_rename_files()
    print("Files copied and renamed successfully!")
